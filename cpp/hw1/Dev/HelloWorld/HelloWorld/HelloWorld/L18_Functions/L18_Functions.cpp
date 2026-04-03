// L18_Functions.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>

struct Player
    {
    std::string name;
    int health = 0;
    };
std::vector<Player> players;

bool InitializePlayers();
void ApplyDamage();
int GetMinHealthPlayerIndex();
int GetMaxHealthPlayerIndex();
void GetDeadPlayersIndexes(std::vector<int>& deadPlayersIndexes);



void main()
{
    if (!InitializePlayers()) {
        std::cout << "Fehler bei der Initialisierung der Spieler! \n" ;
        return;
}
    ApplyDamage();

    int menuPoint = 0;
    while(menuPoint != 4) {
        std::cout << "To get player with min health press 1 \n";
        std::cout << "To get player with max health press 2 \n";
        std::cout << "To get dead players names press 3 \n";
        std::cout << "To exit press 4 \n";
        if (!(std:: cin >> menuPoint)) {
            std::cout << "Fehler bei der Initialisierung.";
            continue;
        }
        switch (menuPoint) 
            {
            case 1: {
                int minHealthPlayerIndex = GetMinHealthPlayerIndex();
                if (minHealthPlayerIndex < 0 || minHealthPlayerIndex >= players.size()) {
                    std::cout << "Kein Spieler gefunden mit minimaler Gesundheit. \n";
                }
                else {
                    std::cout << players[minHealthPlayerIndex].name << " get min health ";
                }
                break;
    }
                  case 2: {
                int maxHealthPlayerIndex = GetMaxHealthPlayerIndex();
                if (maxHealthPlayerIndex < 0 || maxHealthPlayerIndex >= players.size()) {
                    std::cout << "Kein Spieler gefunden mit maximaler Gesundheit. \n";
                }
                else {
                    std::cout << players[maxHealthPlayerIndex].name << " get max health ";
                }
                break;
            }
            case 3: {
                std::vector<int> deadPlayersIndexes;
                GetDeadPlayersIndexes(deadPlayersIndexes);

                for (auto& deadPlayersIndexes : deadPlayersIndexes) {
                    std::cout << players[deadPlayersIndexes].name << " is dead \n";
                }
                break;
            }
                  case 4:
                  {
                      return;
                  }
                  default:
                      break;
        }
    }

}

bool InitializePlayers()
{
    std::cout << "Please write a number of players: \n";
    int numberOfPlayers;
    if (!(std::cin >> numberOfPlayers)) {
        return false;
}
    Player player;
    for (int i = 0; i < numberOfPlayers; i++) {
        std::cout << "Please write a name of the player: \n";
            std::cin >> player.name;
        std::cout << "health: \n";
        if (!(std::cin >> player.health)) {
            continue;

}
        players.push_back(player);
    }
    return true;
    }

void ApplyDamage()
{
    std::cout << "Apply damage to players: \n";
    int damageValue = 0;
    std:: cin >> damageValue;
    for (auto& player : players) {
        player.health -= damageValue;
    }
}
int GetMinHealthPlayerIndex() 
{
    if (players.size() ==0) {
    return -1;
}
    int minHealthIndex = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].health < players[minHealthIndex].health) {
            minHealthIndex = i;
        }
    }
    return minHealthIndex;
    }

int GetMaxHealthPlayerIndex()
{
    if (players.size() == 0) {
        return -1;
        }
    int maxHealthIndex = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].health > players[maxHealthIndex].health) {
            maxHealthIndex = i;
        }
    }
    return maxHealthIndex;
}

void GetDeadPlayersIndexes(std::vector<int>& deadPlayersIndexes)
{
    for (int i = 0; i < players.size(); i++) {
        if (players[i].health <= 0) {
            deadPlayersIndexes.push_back(i);
        }
    }
}
