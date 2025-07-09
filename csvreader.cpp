#include "csvreader.h"

#include <fstream>
#include <iostream>
#include <cmath>

// Constructor

CSVReader::CSVReader(std::string _filename) : filename(_filename) 
{};

// Reading data

std::vector<Player> CSVReader::readCSV() {
    std::vector<Player> players;

    std::string line;
    unsigned int lineCount = 1;

    std::ifstream file{filename};

    if (!file.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        throw std::exception{}; // Throw an expeption if file cannot be opened
    }

    std::getline(file, line); // Skip the header row
    while (std::getline(file, line)) {
        players.push_back(stringToPlayer(lineCount, line));
        lineCount++;
    }

    file.close();

    return players;
}

// Writing data

void CSVReader::addRounds(std::vector<Player> playersList) {
    unsigned int playersCount = playersList.size(); // Consider this to be N
    int rounds = logBBaseA(2, playersCount) + 1; // Formula to get correct number of rounds = (log N base 2) + 1
    
    std::string round_headers = "";

    for (int i = 1; i <= rounds; ++i) {
        round_headers += "Round " + std::to_string(i);
        round_headers += ",";
    }

    std::ofstream file{filename};
    
    if (!file.is_open()) {
        std::cout << "Error opening " << filename << std::endl;
        throw std::exception{}; // Throw an expeption if file cannot be opened
    }

    file << "Player,Score," << round_headers << "\n";

    for (const Player& player : playersList) {
        file << player.name << "," << player.score << "\n";
    }

    file.close();

    std::cout << "Calculated and added rounds on csv file successfully!" << std::endl;
}

// Conversion functions

std::vector<std::string> CSVReader::tokenise(std::string line, char sep) {
    std::vector<std::string> tokens;
    std::string token;

    int start, end;
    start = line.find_first_not_of(sep, 0);

    do {
        end = line.find_first_of(sep, start);

        if (start == end || start == line.length()) break; // If no charectar has been read, skip this token
        if (end == std::string::npos) token = line.substr(start, line.length() - start); // Take the line length if end is not defined
        else token = line.substr(start, end - start);

        tokens.push_back(token);
        start = end + 1; // Jump to the charectar that lies after the sep we just read (end)
    } while (end != std::string::npos);

    return tokens;
}

Player CSVReader::stringToPlayer(unsigned int lineCount, std::string line) {
    std::vector<std::string> tokens = tokenise(line, ',');

    float score = std::stof(tokens[1]); // Convert score string to a float

    Player player{lineCount, tokens[0], score};

    return player;
}

double CSVReader::logBBaseA(float A, float B) {
    double result = std::log(B) / std::log(A); // log B base A = log B base e / log A base e -- Logarithm base change rule
    return result;
}