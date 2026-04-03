// L21_Classes.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Character class
class Character {
private:
    string name;
    int health;
    int x;
    int y;
    int speed;

public:
    // Constructor
    Character(string n, int h, int spd)
        : name(n), health(h), speed(spd), x(0), y(0) {
    }

    // Move method
    void move(int deltaX, int deltaY) {
        x += deltaX * speed;
        y += deltaY * speed;
    }

    // Display position
    void printPosition() const {
        cout << name << " Position: (" << x << ", " << y << ")\n";
    }
};

int main() {
    int n;
    cout << "Number of characters: ";
    cin >> n;

    vector<Character> characters;

    for (int i = 0; i < n; ++i) {
        string name;
        int health;
        int speed;

        cout << "\nName: ";
        cin >> name;

        cout << "Health: ";
        cin >> health;

        cout << "Speed: ";
        cin >> speed;

        characters.emplace_back(name, health, speed);
    }

    cout << "\nCharacter positions after movement:\n";

    for (auto& character : characters) {
        character.move(1, 1);
        character.printPosition();
    }

    return 0;
}

