#include "../include/matchmaking.h"

#include <iostream>
#include <algorithm>

Matchmaker::Matchmaker() {};

std::vector<std::vector<Player>> Matchmaker::makeMatches(std::vector<Player>& players) {
    std::vector<std::vector<Player>> matches;

    std::sort(players.begin(), players.end(), compareScore); // Sort the players by score
    std::vector<bool> paired(players.size(), false);

    for (unsigned int i = 0; i < players.size(); ++i) {
        if (paired[i]) continue; // Go to next player if current player has been matched
        bool matched = false; // Flag to check if matchmaking is done in this iteration

        for (unsigned int j = i + 1; j < players.size(); ++j) { // Skip players above j in the leaderboard
            if (!paired[j]) {
                matches.push_back({players[i], players[j]});
                paired[i] = paired[j] = true; // Players i and j have been marked paired
                matched = true;
                break;
            }
        }

        // Logic to detect a BYE
        if (!matched && !players[i].gotBye) {
            players[i].score += 1;
            players[i].gotBye = true;
            paired[i] = true;
            std::cout << players[i].name << " got a BYE.";
            std::cout << " New score is " << players[i].score << std::endl;
        }
    }

    return matches;
}

bool Matchmaker::compareScore(const Player& a, const Player& b) {
    return a.score > b.score;
}