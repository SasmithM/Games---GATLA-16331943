#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Dice.h"
#include "Hangman.h"
#include "Blackjack.h"


int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    while (true) {
        std::cout << "\n=== Game Collection ===\n"
            << "1. Dice Roll\n"
            << "2. Hangman\n"
            << "3. Blackjack\n"
            << "4. Exit\n"
            << "Choose a game (1-4): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        switch (choice) {
        case 1: playDiceGame(); break;
        case 2: playHangmanGame(); break;
        case 3: playBlackjackGame(); break;
        case 4: return 0;
        default: std::cout << "Invalid choice!\n";
        }
    }
}