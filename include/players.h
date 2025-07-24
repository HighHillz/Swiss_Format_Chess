#pragma once

#include <string>
#include <vector>

enum class Colour {
    white,
    black
};

class Player {
    public:
    Player(unsigned int lineCount, std::string _name, float _score, float _buchholz, float _sb);

    unsigned int id;
    float score;
    float buchholz;
    float sb;
    std::string name;
    std::vector<std::string> roundDetails;
    std::vector<Colour> colours; // Stores the details of colours played by the player in each round
    bool gotBye = false;
};