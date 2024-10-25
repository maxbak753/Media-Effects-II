#include <iostream>
#include <string>

using namespace std;

// CREATE CLASS
class Player { // definition & declaration at top unless in a multi-file program
    public: // ACCESS SPECIFIER
        // ATTRIBUTES
        string gamerTag;
        int score;
        // CONSTRUCTORS (functions that automatically run when an object is created)
        Player() {
            cout << "Default contructor ran" << endl;
            gamerTag = "Default";
            score = 0;
        }
        // you can overload contructors
        Player(string gt, int sc) {
            cout << "Parameter contructor ran" << endl;
            gamerTag = gt;
            score = sc;
        }
        
        // METHOD
        void identify() {
            cout << "My name is: " << gamerTag << endl;
            cout << "My score is: " << score << endl;
        }
};

int main() {
    // CREATE OBJECTS OF CLASS
    Player p1("Maxwell_99", 100);
    Player p2;

    // RUN CLASS METHODS FOR OBJECTS
    p1.identify();
    p2.identify();
}