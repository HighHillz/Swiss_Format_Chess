#include "../include/csvreader.h"
#include "../include/console_utils.h"

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
        throw std::exception{}; // Throw an expeption if file cannot be opened
    }

    std::getline(file, line); // Skip the header row
    while (std::getline(file, line)) {
        try {
            players.push_back(stringToPlayer(lineCount, line));
        } catch (const std::exception& e) {
            Console::setColour(12);
            std::cout << "ERROR: Bad data read at line " << lineCount << std::endl;
            Console::setColour(7);
            return players;
        }
        
        lineCount++;
    }

    file.close();

    return players;
}

// Writing data

void CSVReader::exportStandings(std::string filename, std::vector<Player>& players) {
    std::ofstream file{filename};

    std::cout << std::endl;

    std::cout << "Exporting data..." << std::endl;

    // Write headers
    std::string line = "Position,Name,Score,Buchholz,SB";
    file << line << "\n";

    unsigned int pos = 1;
    // Write data
    for (const Player& player : players) {
        line = std::to_string(pos) + "," + player.name + "," + std::to_string(player.score) + "," + std::to_string(player.buchholz) + "," + std::to_string(player.sb);
        file << line << "\n";
        pos ++;
    }
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
    float buchholz = std::stof(tokens[2]); // Convert Buchholz score string to a float
    float sb = std::stof(tokens[3]); // Convert Sonneborn-Berger score string to a float

    Player player{lineCount, tokens[0], score, buchholz, sb};

    return player;
}