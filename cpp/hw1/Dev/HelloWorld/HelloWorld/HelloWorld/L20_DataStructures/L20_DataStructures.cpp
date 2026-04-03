// L20_DataStructures.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Character {
    string name;
    int health;
    int x;
    int y;
};

int main()
{
    int n;
    cout << "enter the number of characters: ";
    cin >> n;
    vector<Character> characters(n);

    for (int i = 0; i < n; ++i) {
        cout << "\nCharacter " << i << "\n";
        cout << "enter name " << i << ": ";
        cin >> characters[i].name;

        cout << "enter health " << i  << ": ";
        cin >> characters[i].health;
        cout << "enter position x,y " << i << ": ";
        cin >> characters[i].x >> characters[i].y;
    }

    int meteorX, meteorY;
    int damage;
    int power;

    cout << "\nEnter meteor position (x y): ";
    cin >> meteorX >> meteorY;
    cout << "enter meteor damage: ";
    cin >> damage;
    cout << "enter meteor power: ";
    cin >> power;

    double radius = 3.0 * power;
    bool hasDead = false;

    cout << "\nDamaged characters:\n";

    // Distance check and apply damage
    for (int i = 0; i < n; i++) {
        double distance = sqrt(
            pow(characters[i].x - meteorX, 2) +
            pow(characters[i].y - meteorY, 2)
        );

        if (distance <= radius) {
            characters[i].health -= damage;
            cout << "- " << characters[i].name << endl;

            if (characters[i].health <= 0) {
                hasDead = true;
            }
        }
    }
    if (hasDead) {
        cout << "\nIs there a dead characters\n";
    }
    else {
        cout << "\nNo dead characters find.\n";
    }

    return 0;
}