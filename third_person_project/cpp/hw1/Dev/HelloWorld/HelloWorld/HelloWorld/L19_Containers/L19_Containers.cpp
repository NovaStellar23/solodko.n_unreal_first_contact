// L19_Containers.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector <string> commands(N);
    for (int i = 0; i < N; i++) {
        cin >> commands[i];
}
    int x , y ;
    cin >> x >> y;

    for (const string& cmd : commands) {
        if (cmd == "forward") {
            y++;
        }
        else if (cmd == "backward") {
            y--;
        }
        else if (cmd == "left") {
            x--;
        }
        else if (cmd == "right") {
            x++;
        }
        cout << x << " " << y << endl;

        return 0;
    }
}