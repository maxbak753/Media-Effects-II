#include <iostream>
#include "player.hpp"

using namespace std;

int main() {
    Player::print_number_of_players(); // print # of players
    Player p1; // make a player
    Player::print_number_of_players();
    Player p2;
    p2.print_number_of_players();

    p2.number_of_players = 100;
    p1.print_number_of_players();

    return 0;
}