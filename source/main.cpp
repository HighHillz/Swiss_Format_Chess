#include "../include/tournament.h"

#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "------------------------------ Swiss Format Chess Tournament ------------------------------" << std::endl;

    std::cout << "[1] Load players from a CSV file" << std::endl;
    std::cout << "[2] Start tournament" << std::endl;
    std::cout << "[3] View standings" << std::endl;
    std::cout << "[4] Export standings" << std::endl;
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

        switch (choice) {
            case 1 :
                agent.loadPlayersData();
                break;
            case 2:
                agent.startTournament();
                break;
        }

        std::cout << std::endl; // Purely for neatness
    } while (choice != 0);

    return 0;
}