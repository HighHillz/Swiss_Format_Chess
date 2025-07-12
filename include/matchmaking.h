#pragma once

#include "players.h"

class Matchmaker {
    public:
    Matchmaker();

    /** Make matches from the set of players passed */
    void makeMatches(std::vector<Player>& players);
    /** Displays all matches made with results */
    void listMatches(const unsigned int& round);
    
    std::string currentBYE; // Store current round's BYE here
    std::vector<std::vector<Player>> matches; // Store all match details here

    private:
    /** Compares the score of two players and return true or false */
    static bool compareScore(const Player& a, const Player& b);
    /** Checks and returns if the passed player has already been matched with the other player */
    bool matchedBefore(const Player& i, const Player& j);
};