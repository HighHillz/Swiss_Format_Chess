#include "../include/tournament.h"
#include "../include/csvreader.h"
#include "../include/round.h"

#include <iostream>
#include <cmath>

Tournament::Tournament() {}

void Tournament::loadPlayersData() {
    std::string default_path = "../Data/test.csv";

    std::cout << "Enter path of CSV file with players (default: "<< default_path <<"): ";
    std::string path;
    std::getline(std::cin, path);

    if (path == "") path = default_path;

    CSVReader reader{path};
    players = reader.readCSV();

    std::cout << "Number of players loaded: " << players.size() << std::endl;
}

void Tournament::startTournament() {
    std::cout << "Starting tournament with " << players.size() << " players." << std::endl;
    int roundsCount = logBBaseA(2, players.size());  // Formula to get correct number of rounds = (log N base 2) + 1
    std::cout << "Number of rounds: " << roundsCount << " (Based on number of players loaded)" << std::endl;
    std::cout << std::endl;

    for (int i = 1; i <= roundsCount; ++i) {
        Round round{i}; // Create a new round
        round.startRound(players); // Start the new round
        if (i != roundsCount) std::cout << std::endl;
    }
}

double Tournament::logBBaseA(float A, float B) {
    double result = std::log(B) / std::log(A); // log B base A = log B base e / log A base e -- Logarithm base change rule
    return result;
}