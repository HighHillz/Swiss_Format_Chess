#pragma once

#include "players.h"

#include <vector>

class Tournament {
    public:

    // Constructor
    Tournament();

    private:
    std::vector<Player> players;

    void loadPlayersData();
    void makeMatches();
};