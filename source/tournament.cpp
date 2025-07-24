#include "../include/tournament.h"
#include "../include/csvreader.h"
#include "../include/round.h"
#include "../include/console_utils.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

Tournament::Tournament() {}

void Tournament::loadPlayersData() {
    std::string default_path = "../Data/players.csv";

    std::cout << "Enter path of CSV file with players (default: "<< default_path << "): ";
    std::string path;
    std::getline(std::cin, path);

    if (path == "") path = default_path;

    try {
        CSVReader reader{path};
        players = reader.readCSV();
    } catch (const std::exception& e) {
        Console::setColour(12);
        std::cout << "ERROR: " << path << " does not exist" << std::endl;
        Console::setColour(7);

        return;
    }
    
    Console::setColour(10);
    std::cout << "Number of players loaded: " << players.size() << std::endl;
    Console::setColour(7);
}

void Tournament::startTournament() {
    if (players.size() == 0) {
        Console::setColour(12);
        std::cout << "ERROR: Cannot find any player. Check whether the csv file has player data and you have loaded it." << std::endl;
        Console::setColour(7);
        return;
    }

    std::cout << "Starting tournament with " << players.size() << " players." << std::endl;

    int roundsCount = logBBaseA(2, players.size()); // Formula to get correct number of rounds = (log N base 2)
    if (players.size() >= 6) {
        roundsCount ++; 
    }
    
    std::cout << "Number of rounds: " << roundsCount << " (Based on number of players loaded)" << std::endl;
    std::cout << std::endl;

    for (int i = 1; i <= roundsCount; ++i) {
        Round round{i}; // Create a new round
        round.startRound(players); // Start the new round

        if (i != roundsCount) std::cout << " Going to the next round..." << std::endl;
        else std::cout << std::endl;
        std::cout << std::endl;
    }

    // Calculate and update the Buchholz score for every player
    for (Player& player : players) {
        setBuchholz(player);
        setSonnebornBerger(player);
    }

    std::cout << "Tournament is over! ";

    int choice;
    do {
        std::cout << "What next?" << std::endl;
        std::cout << "[1] View standings" << std::endl;
        std::cout << "[2] Export standings" << std::endl;
        std::cout << "[0] Back" << std::endl;
        std::cout << "Enter your choice: ";

        std::cin >> choice;
        std::cin.ignore();

        std::cout << std::endl;

        switch (choice) {
            case 1:
                displayStandings();
                break;
            case 2:
                exportStandings();
                break;
            default:
                if (choice != 0) {
                    Console::setColour(12);
                    std::cout << "ERROR: Invalid input " << choice << std::endl;
                    Console::setColour(7);
                }
        }

        std::cout << std::endl;
    } while (choice != 0);
}

void Tournament::displayStandings() {
    std::sort(players.begin(), players.end(), compareScore); // Sort players by score first

    // Header
    std::cout << "=================================================================================\n";
    std::cout << std::left << std::setw(8) << "Rank" << std::setw(30) << "Name";
    Console::setColour(6);
    std::cout << std::setw(8) << "Score";
    Console::setColour(14);
    std::cout << std::setw(10) << "Buchholz";
    std::cout << std::setw(20) << "Sonneborn-Berger" << "\n";
    Console::setColour(7);
    std::cout << "---------------------------------------------------------------------------------\n";
    
    unsigned int pos = 1;
    for (const Player& player : players) {
        std::cout << std::left << std::setw(8) << pos;

        std::cout << std::setw(30) << player.name;
        Console::setColour(6);
        std::cout << std::setw(8) << player.score;
        Console::setColour(14);
        std::cout << std::setw(10) << player.buchholz;
        std::cout << std::setw(20) << player.sb << "\n";
        Console::setColour(7);

        pos ++;
    }

    std::cout << "=================================================================================\n";
}

void Tournament::exportStandings() {
    std::string default_path = "../Data/standings.csv";

    std::cout << "Enter path of CSV file for standings (default: "<< default_path << "): ";
    std::string path;
    std::getline(std::cin, path);

    if (path == "") path = default_path;

    CSVReader::exportStandings(path, players);
    
    Console::setColour(10);
    std::cout << "Exported data to " << path << std::endl;
    Console::setColour(7);
}

bool Tournament::compareScore(const Player& a, const Player& b) {
    if (a.score == b.score) { // If main scores are equal, compare Buchholz score
        if (a.buchholz == b.buchholz) { // If Buchholz scores are also equal, compare Sonneborn-Berger score
            return a.sb > b.sb;
        }
        return a.buchholz > b.buchholz;
    }
    return a.score > b.score;
}

void Tournament::setBuchholz(Player& player) {
    float buchholz = player.buchholz;

    for (const std::string& detail : player.roundDetails) {
        if (detail == "bye") continue; // Skip this iteration if a round status is a BYE
        char matchStatus = detail[0];

        if (matchStatus == '+') {
            int id = std::stoi(detail.substr(1, detail.length() - 1));
            for (const Player& p : players) {
                if (p.id == id) {
                    buchholz += p.score; 
                    break;
                }
            }
        }
    }

    player.buchholz = buchholz;
}

void Tournament::setSonnebornBerger(Player& player) {
    float sb = player.sb;

    for (const std::string& detail : player.roundDetails) {
        if (detail == "bye") continue; // Skip this iteration if a round status is a BYE
        char matchStatus = detail[0];

        if (matchStatus == '+') {
            int id = std::stoi(detail.substr(1, detail.length() - 1));
            for (const Player& p : players) {
                if (p.id == id) {
                    sb += p.score; 
                    break;
                }
            }
        } else if (matchStatus == '=') {
            int id = std::stoi(detail.substr(1, detail.length() - 1));
            for (const Player& p : players) {
                if (p.id == id) {
                    sb += (p.score / 2); 
                    break;
                }
            }
        }
    }

    player.sb = sb;
}

double Tournament::logBBaseA(float A, float B) {
    double result = std::log(B) / std::log(A); // log B base A = log B base e / log A base e -- Logarithm base change rule
    return result;
}