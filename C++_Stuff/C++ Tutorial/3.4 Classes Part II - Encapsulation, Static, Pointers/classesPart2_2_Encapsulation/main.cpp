#include <iostream>
#include "player.hpp"

using namespace std;

int main() {
    Player p1;
    p1.setGamerTag("Mike"); // <-- fail: not long enough
    p1.setGamerTag("Maxwell_99");// <-- success

    cout << p1.getGamerTag() << endl;

    // user types a password
    p1.setPassword();

    // check if the password we entered matches this
    p1.validatePassword("1234567");

    return 0;
}