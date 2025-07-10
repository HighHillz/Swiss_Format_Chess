#pragma once

#include "players.h"

class CSVReader {
    public:

    // Constructor
    CSVReader(std::string _filename);

    // Reading data
    /** Read the csv file passed */
    std::vector<Player> readCSV();

    // Writing data
    /** Add rounds to the header of the passed csv file */
    void addRounds(std::vector<Player> playersList);

    private:
    std::string filename;

    // Conversion functions
    /** Converts the passed line into tokens split by the passed sep charectar and returns it */
    static std::vector<std::string> tokenise(std::string line, char sep);
    /** Convert the passed string to a Player object and return it */
    static Player stringToPlayer(unsigned int lineCount, std::string line);
    /** Returns the result of log B base A */
    static double logBBaseA(float A, float B);
};