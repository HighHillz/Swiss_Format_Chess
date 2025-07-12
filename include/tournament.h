#pragma once

#include "players.h"

#include <vector>

class Tournament {
    public:

    // Constructor
    Tournament();

    // Tournament functionalities
    /** Loads player data after recieving csv file */
    void loadPlayersData();
    /** Starts the tournament */
    void startTournament();

    private:
    /** Returns the result of log B base A */
    static double logBBaseA(float A, float B);

    std::vector<Player> players;
};