#pragma once

#include "players.h"
#include "matchmaking.h"

class Round {
    public:
    // Constructor : Define current round
    Round(unsigned int _round);

    /** Starts the current pointing round with the passed set of players */
    void startRound(std::vector<Player>& players);
    
    private:
    /** A small menu regarding result setting for the passed match details */
    void displayResultsMenu(const int& index);
    /** Sets winners, losers and draws */
    void updateMatchState(Player& winner, Player& loser, const int& index, bool draw = false);
    /** Returns true if all players have their games finished */
    bool roundOver(const std::vector<std::vector<Player>>& matches);

    unsigned int round;
    Matchmaker matchmaker{};
    std::vector<bool> match_status;
};