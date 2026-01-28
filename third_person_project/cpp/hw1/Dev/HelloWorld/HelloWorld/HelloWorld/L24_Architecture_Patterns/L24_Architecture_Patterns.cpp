// L24_Architecture_Patterns.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Observer {
    public:
    virtual void update(int x) = 0;
    };

class Subject {
    vector<Observer*> observers;
    int state = 0;
    public:
    void add(Observer* observer) {
        observers.push_back(observer);
    }
    void set(int x) {
        state = x;
        for (auto observer : observers) {
            observer->update(state);
    }

};

class ConcreteObserver : public Observer {
    string name;
    public:
        ConcreteObserver(string n) : name(n) {}
    void update(int x) override {
        cout << "Observer "  << name
            << " updated with state " << x << endl;
    }
};

int main()
{
    Subject subject;

    ConcreteObserver observer1("A");
    ConcreteObserver observer2("B");

    subject.add(&observer1);
    subject.add(&observer2);

    subject.set(10);
}

};

