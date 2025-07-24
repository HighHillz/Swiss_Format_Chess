#include "../include/matchmaking.h"
#include "../include/console_utils.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

std::string ColourToString(Colour colour) {
    switch (colour) {
        case Colour::white: return "White";
        case Colour::black: return "Black";
        default: return "Unknown";
    }
}

Matchmaker::Matchmaker() {};

void Matchmaker::makeMatches(std::vector<Player>& players) {
    std::cout << "Match making in progress..." << std::endl;
    std::sort(players.begin(), players.end(), compareScore); // Sort the players by score
    std::vector<bool> paired(players.size(), false);
    std::vector<Player> match;

    for (unsigned int i = 0; i < players.size(); ++i) {
        if (paired[i]) continue; // Go to next player if current player has been matched
        bool matched = false; // Flag to check if matchmaking is done in this iteration

        for (unsigned int j = i + 1; j < players.size(); ++j) { // Skip players above j in the leaderboard
            if (!paired[j] && !matchedBefore(players[i], players[j])) {
                match = {players[i], players[j]};
                assignColours(match);
                
                // Swap players to match colours header while displaying
                if (match[0].colours.back() == Colour::black) {
                    std::swap(match[0], match[1]);
                }

                matches.push_back(match);
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
    
    std::cout << "Number of matches made: " << matches.size() << std::endl;
}

bool Matchmaker::compareScore(const Player& a, const Player& b) {
    return a.score > b.score;
}

void Matchmaker::listMatches(const unsigned int& round) {
    unsigned int tableNumber = 1;

    std::cout << std::left << std::setw(8) << "Table" << "|"
              << std::setw(30) << "White" << "|"
              << std::setw(8) << "Score" << "|"
              << std::setw(7) << "Result" << "|"
              << std::setw(8) << "Score" << "|"
              << "Black" << std::endl;
    std::cout << std::string(8 + 30 + 8 + 7 + 8 + 30, '-') << std::endl;

    for (std::vector<Player>& match : matches) {
        std::cout << std::left << std::setw(8) << tableNumber << "|";
        std::cout << std::setw(30) << match[0].name << "|";

        Console::setColour(6);
        std::cout << std::setw(8) << match[0].score;
        Console::setColour(7);
        std::cout << "|";

        if (match[0].roundDetails.size() < round) {
            std::cout << std::setw(7) << "      " << "|";
        } else {
            Console::setColour(10);
            std::string result;
            char resChar = match[0].roundDetails[round - 1][0];
            if (resChar == '=') result = "0.5";
            else if (resChar == '+') result = "1-0";
            else if (resChar == '-') result = "0-1";
            std::cout << std::setw(7) << result;
            Console::setColour(7);
            std::cout << "|";
        }

        Console::setColour(6);
        std::cout << std::setw(8) << match[1].score;
        Console::setColour(7);
        std::cout << "|";

        std::cout << match[1].name << std::endl;

        tableNumber ++;
    }
    if (currentBYE != "") {
        std::cout << "BYE: " << currentBYE << " gets a BYE" << std::endl;
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

void Matchmaker::assignColours(std::vector<Player>& match) {
    if (match[0].roundDetails.size() == 0 && match[1].roundDetails.size() == 0) { // Case: If round 1
        match[0].colours.push_back(Colour::white);
        match[1].colours.push_back(Colour::black);
    } else {
        if (match[0].roundDetails.back() == "bye" || match[1].roundDetails.back() == "bye") { // Case: A player got a BYE last round
            Player& byePlayer = (match[0].roundDetails.back() == "bye") ? match[0] : match[1];
            Player& otherPlayer = (byePlayer.id == match[0].id) ? match[1] : match[0];
            Colour lastColour = otherPlayer.colours.back();
            if (lastColour == Colour::white) {
                byePlayer.colours.push_back(Colour::white);
                otherPlayer.colours.push_back(Colour::black);
            } else {
                byePlayer.colours.push_back(Colour::black);
                otherPlayer.colours.push_back(Colour::white);
            }
        } else { // Case: Both players have played in the previous round
            Colour lastColour0 = match[0].colours.back();
            Colour lastColour1 = match[1].colours.back();
            if (lastColour0 != lastColour1) { // Case: Both players have played different colours last time
                match[0].colours.push_back(lastColour1);
                match[1].colours.push_back(lastColour0);
            } else { // Case: Both players have played the same colours last time
                if (getColourCount(match[0], Colour::black) > getColourCount(match[1], Colour::black)) {
                    match[0].colours.push_back(Colour::white);
                    match[1].colours.push_back(Colour::black);
                } else if (getColourCount(match[0], Colour::black) < getColourCount(match[1], Colour::black)) {
                    match[1].colours.push_back(Colour::white);
                    match[0].colours.push_back(Colour::black);
                } else { // Case: Both players played black equal number of times, then check id
                    if (match[0].id < match[1].id) {
                        match[0].colours.push_back(Colour::white);
                        match[1].colours.push_back(Colour::black);
                    } else {
                        match[1].colours.push_back(Colour::white);
                        match[0].colours.push_back(Colour::black);
                    }
                }
            }
        }
    }
}

int Matchmaker::getColourCount(const Player& player, Colour colour) {
    return std::count(player.colours.begin(), player.colours.end(), colour);
}