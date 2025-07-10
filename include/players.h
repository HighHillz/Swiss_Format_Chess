#pragma once

#include <string>
#include <vector>

class Player {
    public:
    Player(unsigned int lineCount, std::string _name, float _score);

    unsigned int id;
    float score;
    std::string name;
    std::vector<std::string> rounds;
    bool gotBye = false;
};