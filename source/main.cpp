#include "../include/tournament.h"
#include "../include/console_utils.h"

#include <iostream>
#include <limits>

void displayMenu() {
    Console::setColour(11);
    std::cout << "------------------------------ Swiss Format Chess Tournament ------------------------------" << std::endl;
    Console::setColour(7);

    std::cout << "[1] Load players from a CSV file" << std::endl;
    std::cout << "[2] Start tournament" << std::endl;
    std::cout << "[0] Exit" << std::endl;

    std::cout << "Enter a choice: ";
}

int main() {
    Tournament agent{};
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Flush new line

        std::cout << std::endl;

        switch (choice) {
            case 1 :
                agent.loadPlayersData();
                break;
            case 2:
                agent.startTournament();
                break;
            default:
                if (choice != 0) {
                    Console::setColour(12);
                    std::cout << "ERROR: Invalid input " << choice << std::endl;
                    Console::setColour(7);
                }
        }

        std::cout << "Opening menu..." << std::endl;
        std::cout << std::endl; // Purely for neatness
    } while (choice != 0);

    return 0;
}