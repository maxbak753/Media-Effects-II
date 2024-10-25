#include <iostream>
#include "player.hpp"

using namespace std;

int Player::number_of_players = 0;
Player::Player () {
    cout << "You've made a player" << endl; // print
    number_of_players++; // add player
    money = 10000; // initial money
}
void Player::print_number_of_players() {
    cout << "There are this many players: " << number_of_players << endl;
}

void Player::setGamerTag(string newTag) {
    // Check if the gamerTag is valid, and change if so
    if (newTag.length() >= 6) {
        gamerTag = newTag;
        cout << "GamerTag successfully saved." << endl;
    } else {
        cout << "GamerTag did not save. Check name length." <<endl;
    }
}

string Player::getGamerTag() {
    return gamerTag;
}

void Player::setGamerScore(int newScore) {
    gamerScore = newScore;
}

void Player::setPassword() {
    cout << "Hey, what is your new password? " <<endl;
    cout << "No spaces, imimum of 6 chars, max of 16" << endl;
    string newcode = "";
    cin >> newcode;

    if (newcode.length() >= 6 && newcode.length() <= 16) {
        cout << "Password saved" << endl;
        password = newcode;
    } else {
        cout << "Hey, that didn't work. Follow the instructions, dude." << endl;
    }
}

bool Player::validatePassword(string attempt) {
    if (attempt == password) {
        cout << "Access Granted" << endl;
        return true;
    } else {
        cout << "Acces Denied" << endl;
    }
}

bool Player::canTrade(int amount) {
    if (money - amount >= 0) {
        return true;
    } else {
        return false;
    }
}

// if you sent  positive amount, it will ADD
// if you send a negative amount, it will SUBTRACT
void Player::tradeMoney(int amount) {
    money += amount;
}

int Player::getMoney() {
    return money;
}