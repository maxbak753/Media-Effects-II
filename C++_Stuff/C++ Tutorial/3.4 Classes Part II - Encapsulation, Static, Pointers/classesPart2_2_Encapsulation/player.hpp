// header guard
#ifndef PLAYER_HPP
#define PLAYER_HPP

// Player Class
class Player {
    public:
        static int number_of_players; // define in player.hpp
        Player(); // constructor
        static void print_number_of_players(); // define in player.hpp

    void setGamerTag(std::string newTag);
    std::string getGamerTag();

    void setGamerScore(int newScore);
    int getGamerScore();

    void setPassword();
    bool validatePassword(std::string attempt);

    private:
        std::string password;
        std::string gamerTag;
        int gamerScore;
};

#endif