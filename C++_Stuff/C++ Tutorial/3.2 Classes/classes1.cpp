#include <iostream>
#include <string>

using namespace std;

// CREATE CLASS
class Player { // definition & declaration at top unless in a multi-file program
    public:
        string gamerTag;
        int score;
        void identify() {
            cout << "My name is: " << gamerTag << endl;
            cout << "My score is: " << score << endl;
        }
};

int main() {
    // CREATE OBJECTS OF CLASS
    Player p1;
    Player p2;
    // ASSIGN CLASS VARIABLES FOR OBJECTS
    p1.gamerTag = "Maxwell_99";
    p2.gamerTag = "maxbak753";
    p1.score = 100;
    p2.score = 20;
    // RUN CLASS METHODS FOR OBJECTS
    p1.identify();
    p2.identify();
}