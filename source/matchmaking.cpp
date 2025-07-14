#include "../include/matchmaking.h"
#include "../include/console_utils.h"

#include <iostream>
#include <algorithm>

Matchmaker::Matchmaker() {};

void Matchmaker::makeMatches(std::vector<Player>& players) {
    std::sort(players.begin(), players.end(), compareScore); // Sort the players by score
    std::vector<bool> paired(players.size(), false);

    for (unsigned int i = 0; i < players.size(); ++i) {
        if (paired[i]) continue; // Go to next player if current player has been matched
        bool matched = false; // Flag to check if matchmaking is done in this iteration

        for (unsigned int j = i + 1; j < players.size(); ++j) { // Skip players above j in the leaderboard
            if (!paired[j] && !matchedBefore(players[i], players[j])) {
                matches.push_back({players[i], players[j]});
                paired[i] = paired[j] = true; // Players i and j have been marked paired
                matched = true;
                break;
            }
        }

        // Logic to detect a BYE
        if (!matched && !players[i].gotBye) {
            players[i].gotBye = true;
            players[i].roundDetails.push_back("bye");
            paired[i] = true;
            currentBYE = players[i].name;
        }
    }
}

bool Matchmaker::compareScore(const Player& a, const Player& b) {
    return a.score > b.score;
}

void Matchmaker::listMatches(const unsigned int& round) {
    unsigned int tableNumber = 1;
    for (std::vector<Player>& match : matches) {
        std::cout << "[" << tableNumber << "] ";
        std::cout << match[0].name << " " ;

        Console::setColour(6);
        std::cout << match[0].score << " ";
        Console::setColour(7);

        if (match[0].roundDetails.size() < round) {
            std::cout << "     ";
        } else {
            Console::setColour(10);
            if (match[0].roundDetails[round - 1][0] == '=') std::cout << " 0.5 ";
            else if (match[0].roundDetails[round - 1][0] == '+') std::cout << " 1-0 ";
            else if (match[0].roundDetails[round - 1][0] == '-') std::cout << " 0-1 ";
            Console::setColour(7);
        }

        Console::setColour(6);
        std::cout << " " << match[1].score << " ";
        Console::setColour(7);

        std::cout << match[1].name << std::endl;

        tableNumber ++;
    }
    if (currentBYE != "") {
        std::cout << "[BYE] " << currentBYE << " gets a BYE" << std::endl;
    }
}

bool Matchmaker::matchedBefore(const Player& i, const Player& j) {
    for (const std::string& detail : i.roundDetails) {
        if (detail == "bye") continue; // Skip this iteration if a round status is a BYE
        int id = std::stoi(detail.substr(1, detail.length() - 1));
        if (j.id == id) return true; // Player i has already played with player j before
    }
    return false;
}