// L22_OPP.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
using namespace std;

struct Stats {
int strength;
int agility;
int intelligence;
};


class Character {
private:
    int health;
    Stats baseStats;
    Stats currentStats;

    Weapon* weapon;
    PassiveItem* passiveItems[3];
    int passiveItemCount;
    public:
        Character(int health, Stats baseStats) : health(health), baseStats(baseStats), currentStats(baseStats), weapon(nullptr), passiveItemCount(0) {}
        recalcStats();
}
void recalcStats() {
    currentStats = baseStats;

    if (weapon) {
        currentStats.strength += 5; 
    }
    for (int i = 0; i < passiveItemCount; i++) {
        Stats bonus = passiveItems[i]->getBonus();
        currentStats.strength += bonus.strength;
        currentStats.agility += bonus.agility;
        currentStats.intelligence += bonus.intelligence;
    }
}

void addPassiveItem(PassiveItem* item) {
    if (passiveItemCount < 3) {
        passiveItems[passiveItemCount++] = item;
        recalcStats();
    } else {
        cout << "Cannot equip more than 3 passive items!" << endl;
    }

    void pickWeapon(Weapon* newWeapon) {
        if(weapon) {
            cout << "Changing weapon from " << weapon->getIcon() << " to " << newWeapon->getIcon() << endl;
            } else {
            cout << "Equipping weapon: " << newWeapon->getIcon() << endl;
        }
        weapon = newWeapon;
    }

    void attack() {
        if (weapon) {
            weapon->attack();
        } else {
            cout << "No weapon equipped!" << endl;
        }
    }

    void update(float deltaTime) {
        if (weapon) {
            weapon->updateCooldown(deltaTime);
        }
};

class  Weapon {
private:
    int damage;
    float cooldown;
    float currentCooldown;
    string icon;
    public:
        Weapon(int damage, float cooldown, string icon) : damage(damage), cooldown(cooldown), currentCooldown(0), icon(icon) {}
        bool isReady() const { return currentCooldown <= 0; 
        }
        void attack() {
            if (isReady()) {
                cout << "Attacking with damage: " << damage << endl;
                currentCooldown = cooldown;
            } else {
                cout << "Weapon is on cooldown for " << currentCooldown << " seconds." << endl;
            }
        }
        void updateCooldown(float deltaTime) {
            if (currentCooldown > 0) {
                currentCooldown -= deltaTime;
                if (currentCooldown < 0) currentCooldown = 0;
            }
        }

};

class PassiveItem {
private:
    Stats bonus;
    string icon;

 public:
     PassiveItem(Stats bonus, string icon) : bonus(bonus), icon(icon) {}
     Stats getBonus() const { return bonus; }

};

int main()
{
    Stats heroStats = {10, 5, 3};
    Character hero(100, heroStats);

    Stats ringBonus = {2, 1, 0};
    PassiveItem ring(ringBonus, "RingIcon");
    hero.addPassiveItem(&ring);


    Weapon sword(15, 2.0f, "SwordIcon");
    hero.pickWeapon(&sword);
    hero.attack();
    hero.update(1.0f); // Simulate 1 second passing
    hero.attack();

    return 0;
}
