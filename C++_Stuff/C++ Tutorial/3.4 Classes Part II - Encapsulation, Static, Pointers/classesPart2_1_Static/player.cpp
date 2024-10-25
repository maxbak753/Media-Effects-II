#include <iostream>
#include "player.hpp"

using namespace std;

int Player::number_of_players = 0;
Player::Player () {
    cout << "You've made a player" << endl; // print
    number_of_players++; // add player
}
void Player::print_number_of_players() {
    cout << "There are this many players: " << number_of_players << endl;
}