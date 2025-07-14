#pragma once

#include <string>
#include <vector>

class Player {
    public:
    Player(unsigned int lineCount, std::string _name, float _score, float _buchholz);

    unsigned int id;
    float score;
    float buchholz;
    std::string name;
    std::vector<std::string> roundDetails;
    bool gotBye = false;
};