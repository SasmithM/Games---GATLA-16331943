#include "Hangman.h"
#include <iostream>
#include <algorithm>
#include <cctype>

void displayHangmanGallows(int incorrectGuesses) {
    std::cout << " +---+\n";
    std::cout << " |   |\n";
    std::cout << " " << (incorrectGuesses > 0 ? "O" : " ") << "   |\n";
    std::cout << " " << (incorrectGuesses > 2 ? "/" : " ")
        << (incorrectGuesses > 1 ? "|" : " ")
        << (incorrectGuesses > 3 ? "\\" : " ") << "  |\n";
    std::cout << " " << (incorrectGuesses > 4 ? "/" : " ") << " "
        << (incorrectGuesses > 5 ? "\\" : " ") << "  |\n";
    std::cout << "     |\n";
    std::cout << "=======>\n";
}

void playHangmanGame() {
    std::vector<std::string> words = { "programming", "computer", "keyboard", "algorithm", "developer" };
    std::string secretWord = words[rand() % words.size()];
    std::string guessedWord(secretWord.length(), '-');
    std::string guessedLetters;
    int incorrectGuesses = 0;
    const int maxIncorrectGuesses = 6;

    std::cout << "\n--- Hangman ---\nGuess the word: " << guessedWord << "\n";

    while (incorrectGuesses < maxIncorrectGuesses && guessedWord != secretWord) {
        displayHangmanGallows(incorrectGuesses);
        std::cout << "Guessed letters: " << guessedLetters << "\n";
        std::cout << "Enter a letter: ";
        char guess;
        std::cin >> guess;
        guess = tolower(guess);
        std::cin.ignore(10000, '\n');

        if (guessedLetters.find(guess) != std::string::npos) {
            std::cout << "You already guessed '" << guess << "'.\n";
            continue;
        }

        guessedLetters += guess;
        bool found = false;
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == guess) {
                guessedWord[i] = guess;
                found = true;
            }
        }

        if (!found) {
            incorrectGuesses++;
            std::cout << "Incorrect! " << (maxIncorrectGuesses - incorrectGuesses) << " tries left.\n";
        }
        else {
            std::cout << "Good guess!\n";
        }
    }

    if (guessedWord == secretWord) {
        std::cout << "You won! The word was: " << secretWord << "\n";
    }
    else {
        std::cout << "Game over! The word was: " << secretWord << "\n";
    }
}