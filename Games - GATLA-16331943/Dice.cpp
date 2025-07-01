#include "Dice.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int rollDice() {
    return (rand() % 6) + 1; // Rolls a die (1-6)
}

void playDiceGame() {
    char choice;
    std::cout << "\n--- Dice Rolling Game ---\n";
    do {
        std::cout << "You rolled: " << rollDice() << "\nRoll again? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(10000, '\n'); // Clear input buffer
    } while (tolower(choice) == 'y');
}