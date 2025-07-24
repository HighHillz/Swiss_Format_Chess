#include "../include/players.h"

Player::Player(unsigned int lineCount, std::string _name, float _score, float _buchholz, float _sb) : id(lineCount), name(_name), score(_score), buchholz(_buchholz), sb(_sb)
{}