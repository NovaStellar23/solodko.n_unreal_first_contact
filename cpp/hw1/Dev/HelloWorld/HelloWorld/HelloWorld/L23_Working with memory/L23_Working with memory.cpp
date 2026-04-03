// L23_Working with memory.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Stats {
    int strength;
    int agility;
    int intelligence;
};

class Weapon {
private:
    int damage;
    float cooldown;
    float currentCooldown;
    string icon;

public:
    Weapon(int damage, float cooldown, string icon)
        : damage(damage), cooldown(cooldown), currentCooldown(0), icon(icon) {
    }

    bool isReady() const {
        return currentCooldown <= 0;
    }

    void attack() {
        if (isReady()) {
            cout << "Attacking with damage: " << damage << endl;
            currentCooldown = cooldown;
        }
        else {
            cout << "Weapon cooldown: " << currentCooldown << endl;
        }
    }

    void updateCooldown(float deltaTime) {
        if (currentCooldown > 0) {
            currentCooldown -= deltaTime;
            if (currentCooldown < 0) currentCooldown = 0;
        }
    }

    string getIcon() const {
        return icon;
    }
};

class Item {
private:
    float speedBonus;
    string name;

public:
    Item(float speedBonus, string name)
        : speedBonus(speedBonus), name(name) {
    }

    float getSpeedBonus() const {
        return speedBonus;
    }

    string getName() const {
        return name;
    }
};

class Character {
private:
    int health;
    float baseSpeed;
    float currentSpeed;

    Stats baseStats;
    Stats currentStats;

    shared_ptr<Weapon> weapon;

    vector<shared_ptr<Item>> inventory;

public:
    Character(int health, Stats baseStats, float speed)
        : health(health),
        baseStats(baseStats),
        currentStats(baseStats),
        baseSpeed(speed),
        currentSpeed(speed) {
    }

    void pickWeapon(shared_ptr<Weapon> newWeapon) {
        if (weapon) {
            cout << "Changing weapon from "
                << weapon->getIcon()
                << " to "
                << newWeapon->getIcon() << endl;
        }
        else {
            cout << "Equipping weapon: "
                << newWeapon->getIcon() << endl;
        }

        weapon = newWeapon;
    }

    void attack() {
        if (weapon) {
            weapon->attack();
        }
        else {
            cout << "No weapon equipped!" << endl;
        }
    }

    void update(float deltaTime) {
        if (weapon) {
            weapon->updateCooldown(deltaTime);
        }
    }

    // ITEM INS INVENTAR
    void addItem(shared_ptr<Item> item) {
        inventory.push_back(item);
        cout << "Added item: " << item->getName() << endl;
        recalcSpeed();
    }

    // GESCHWINDIGKEIT NEU BERECHNEN
    void recalcSpeed() {
        currentSpeed = baseSpeed;

        for (auto& item : inventory) {
            currentSpeed += item->getSpeedBonus();
        }

        cout << "Current Speed: " << currentSpeed << endl;
    }
};

int main() {

    Stats heroStats = { 10,5,3 };

    Character hero(100, heroStats, 5.0f);

    auto sword = make_shared<Weapon>(15, 2.0f, "SwordIcon");

    hero.pickWeapon(sword);

    hero.attack();

    hero.update(1.0f);

    hero.attack();

    auto boots = make_shared<Item>(2.5f, "Speed Boots");
    auto ring = make_shared<Item>(1.5f, "Wind Ring");

    hero.addItem(boots);
    hero.addItem(ring);

    return 0;
}

