#include <iostream>
#include "player.hpp"

using namespace std;

class Transactions {
    public:
        // p1 is paying p2
        static void exchangeMoney(Player*p1, Player *p2, int amount) {
            // use "->" as the "." for pointers when in a class
            if (p1->canTrade(amount)) {
                p1->tradeMoney(-amount);
                p2->tradeMoney(amount);
                cout << "Transaction successful." << endl;
            } else {
                cout << "Player 1 does not have enough money!" << endl;
            }
        }
};

int main() {
    Player p1;
    Player p2;

    // use pointers or else it won't work! (without more complicated code)
    Transactions::exchangeMoney(&p1, &p2, 100);

    cout << "Player 1 money: " << p1.getMoney() << endl;
    cout << "Player 2 money: " << p2.getMoney() << endl;

    return 0;
}