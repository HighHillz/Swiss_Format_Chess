#include "csvreader.h"
#include "players.h"

#include <iostream>

int main() {
    CSVReader reader{"test.csv"};
    std::vector<Player> players;
    players = reader.readCSV();

    reader.addRounds(players);
    
    for (const Player& player : players) {
        std::cout << player.name << " : " << player.score << std::endl;
    }

    return 0;
}