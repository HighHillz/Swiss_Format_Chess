#include "../include/tournament.h"
#include "../include/csvreader.h"
#include "../include/matchmaking.h"

#include <iostream>

Tournament::Tournament() { // Load players data
    loadPlayersData();
    makeMatches();
};

void Tournament::loadPlayersData() {
    CSVReader reader{"../Data/test.csv"};
    players = reader.readCSV();

    reader.addRounds(players);
}

void Tournament::makeMatches() {
    std::vector<std::vector<Player>> matches;

    Matchmaker matchmaker{};
    matches = matchmaker.makeMatches(players);

    for (const std::vector<Player>& match : matches) {
        std::cout << match[0].name << " (" << match[0].score << ")   (" << match[1].score << ") " << match[1].name << std::endl;
    }
}