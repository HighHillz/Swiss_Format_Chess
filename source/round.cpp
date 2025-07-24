#include "../include/round.h"
#include "../include/console_utils.h"

#include <iostream>

Round::Round(unsigned int _round) : round(_round) 
{}

void Round::startRound(std::vector<Player>& players) {
    Console::setColour(3);
    std::cout << "========= Round " << round << " =========" << std::endl;
    Console::setColour(7);
    std::cout << std::endl;

    // Matchmaking
    matchmaker.makeMatches(players);
    match_status.resize(matchmaker.matches.size(), false);

    do {
        std::cout << std::endl;
        std::cout << "Matches:" << std::endl;

        // Display matches
        matchmaker.listMatches(round);

        // Setting results
        std::cout << std::endl;
        std::cout << "Enter match number to update its status: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Flush new line

        if (choice < 1 || choice > matchmaker.matches.size()) {
            Console::setColour(12);
            std::cout << "ERROR: Invalid input " << choice << std::endl;
            Console::setColour(7);
            continue;
        }

        std::cout << std::endl;
        std::cout << "Match " << choice << ": " << std::endl;
        displayResultsMenu(choice - 1);
        int result;
        std::cin >> result;
        std::cin.ignore();

        if (match_status[choice - 1]) {
            switch (result) {
                case 1:
                    updateMatchState(matchmaker.matches[choice - 1][0], matchmaker.matches[choice - 1][1], choice - 1);
                    match_status[choice - 1] = false;
                    break;
                default:
                    Console::setColour(12);
                    std::cout << "ERROR: Invalid input " << result << std::endl;
                    Console::setColour(7);
            }
        } else {
            switch (result) {
                case 1:
                    updateMatchState(matchmaker.matches[choice - 1][0], matchmaker.matches[choice - 1][1], choice - 1);
                    match_status[choice - 1] = true;
                    break;
                case 2:
                    updateMatchState(matchmaker.matches[choice - 1][1], matchmaker.matches[choice - 1][0], choice - 1);
                    match_status[choice - 1] = true;
                    break;
                case 3:
                    updateMatchState(matchmaker.matches[choice - 1][0], matchmaker.matches[choice - 1][1], choice - 1, true);
                    match_status[choice - 1] = true;
                    break;
                default:
                    Console::setColour(12);
                    std::cout << "ERROR: Invalid input " << result << std::endl;
                    Console::setColour(7);
            }
        }
    } while (!roundOver(matchmaker.matches));

    std::cout << std::endl;
    std::cout << "Final results for round " << round << std::endl;
    matchmaker.listMatches(round); // Display final results for the round

    for (const std::vector<Player>& match : matchmaker.matches) {
        for (const Player& player : match) {
            for (Player& p : players) {
                if (p.id == player.id) {
                    p = player;
                }
            }
        }
    }

    for (Player& player : players) {
        if (player.roundDetails[round - 1][0] == '=') player.score += 0.5;
        else if (player.roundDetails[round - 1][0] == '+') player.score += 1;
        else if (player.roundDetails[round - 1] == "bye") player.score += 1;
    }
    
    std::cout << std::endl;
    std::cout << "Round " << round << " is over!";
}

void Round::updateMatchState(Player& winner, Player& loser, const int& index, bool draw) {
    std::string winner_code, loser_code;
    if (match_status[index]) {
        winner.roundDetails.pop_back();
        loser.roundDetails.pop_back();
    } else {
        if (draw) {
            winner_code = "=" + std::to_string(loser.id);
            loser_code = "=" + std::to_string(winner.id);
        } else {
            winner_code = "+" + std::to_string(loser.id);
            loser_code = "-" + std::to_string(winner.id);
        }
        winner.roundDetails.push_back(winner_code);
        loser.roundDetails.push_back(loser_code);
    }
}

void Round::displayResultsMenu(const int& index) {
    const std::vector<Player>& match = matchmaker.matches[index];
    if (!match_status[index]) {
        std::cout << "[1] " << match[0].name << " wins" << std::endl;
        std::cout << "[2] " << match[1].name << " wins" << std::endl;
        std::cout << "[3] Draw" << std::endl;
        std::cout << "What is the match result: ";
    } else {
        std::cout << "[1] Reset" << std::endl;
        
        std::cout << "Enter a choice: ";
    }
}

bool Round::roundOver(const std::vector<std::vector<Player>>& matches) {
    for (const std::vector<Player>& match : matches) {
        for (const Player& player : match) {
            if (player.roundDetails.size() != round) return false;
        }
    }

    return true;
}