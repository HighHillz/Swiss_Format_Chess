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
    /** Compares two players by score and returns whether the score of 'a' is the greatest. Compares Buchholz score if scores are equal. */
    static bool compareScore(const Player& a, const Player& b);
    /** Calculates and sets the Buchholz score of the passed player */
    void setBuchholz(Player& player);
    /** Calculates and sets the Sonneborn-Berger score of the passed player */
    void setSonnebornBerger(Player& player);
    
    /** Lists all players sorted by score in descending order */
    void displayStandings();
    /** Export all standings to passed files */
    void exportStandings();

    std::vector<Player> players;
};