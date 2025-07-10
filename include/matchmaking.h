#pragma once

#include "players.h"

class Matchmaker {
    public:
    Matchmaker();

    /** Make matches and return them from the set of players passed */
    std::vector<std::vector<Player>> makeMatches(std::vector<Player>& players);

    private:
    /** Compares the score of two players and return true or false */
    static bool compareScore(const Player& a, const Player& b);
};