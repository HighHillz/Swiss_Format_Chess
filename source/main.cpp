#include "../include/tournament.h"

#include <iostream>
#include <limits>

int main() {
    while (true) {
        Tournament app{};

        char ans = '\0';
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            std::cout << "Do you want to start again [y/n]: ";
            std::cin >> ans;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        }

        if (ans == 'n' || ans == 'N') {
            std::cout << "Exiting the program..." << std::endl;
            break;
        }
    }

    return 0;
}