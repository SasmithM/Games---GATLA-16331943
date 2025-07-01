#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib> // Added for rand()

using namespace std;

// Helper function to create a deck
vector<Card> createDeck() {
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    vector<int> values = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
    vector<Card> deck;

    // Create 4 suits of each card
    for (int i = 0; i < 4; ++i) {
        for (size_t j = 0; j < ranks.size(); ++j) {
            deck.push_back({ ranks[j], values[j] });
        }
    }
    return deck;
}

// Helper function to calculate hand value
int calculateHandValue(const vector<Card>& hand) {
    int value = 0;
    int aces = 0;

    for (const auto& card : hand) {
        value += card.value;
        if (card.rank == "Ace") {
            aces++;
        }
    }

    // Adjust for aces if needed
    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }
    return value;
}

// Helper function to display a hand
void displayHand(const string& player, const vector<Card>& hand, bool hideFirstCard = false) {
    cout << player << "'s hand: ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (hideFirstCard && i == 0) {
            cout << "[Hidden] ";
        }
        else {
            cout << hand[i].rank << " ";
        }
    }
    if (!hideFirstCard) {
        cout << "(Total: " << calculateHandValue(hand) << ")";
    }
    cout << endl;
}

void playBlackjackGame() {
    char playAgain;
    cout << "\n--- Welcome to Blackjack! ---\n";

    do {
        vector<Card> deck = createDeck();
        random_shuffle(deck.begin(), deck.end());

        vector<Card> playerHand;
        vector<Card> dealerHand;

        // Deal initial cards
        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();
        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();

        // Show initial hands
        displayHand("Player", playerHand);
        displayHand("Dealer", dealerHand, true);

        // Player's turn
        bool playerBusted = false;
        while (true) {
            int playerValue = calculateHandValue(playerHand);
            if (playerValue > 21) {
                cout << "Player busts!\n";
                playerBusted = true;
                break;
            }
            if (playerValue == 21) {
                cout << "Player has Blackjack!\n";
                break;
            }

            cout << "Hit (H) or Stand (S)? ";
            char choice;
            cin >> choice;
            choice = tolower(choice);
            cin.ignore(10000, '\n');

            if (choice == 'h') {
                playerHand.push_back(deck.back());
                deck.pop_back();
                displayHand("Player", playerHand);
            }
            else if (choice == 's') {
                cout << "Player stands.\n";
                break;
            }
            else {
                cout << "Invalid choice. Please enter H or S.\n";
            }
        }

        // Dealer's turn (only if player didn't bust)
        if (!playerBusted) {
            cout << "\nDealer's turn:\n";
            displayHand("Dealer", dealerHand);

            while (calculateHandValue(dealerHand) < 17) {
                cout << "Dealer hits.\n";
                dealerHand.push_back(deck.back());
                deck.pop_back();
                displayHand("Dealer", dealerHand);
            }

            int dealerValue = calculateHandValue(dealerHand);
            int playerValue = calculateHandValue(playerHand);

            if (dealerValue > 21) {
                cout << "Dealer busts! Player wins!\n";
            }
            else if (dealerValue > playerValue) {
                cout << "Dealer wins with " << dealerValue << " vs player's " << playerValue << "!\n";
            }
            else if (playerValue > dealerValue) {
                cout << "Player wins with " << playerValue << " vs dealer's " << dealerValue << "!\n";
            }
            else {
                cout << "Push! It's a tie with " << playerValue << " each.\n";
            }
        }

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);
        cin.ignore(10000, '\n');
    } while (playAgain == 'y');

    cout << "Thanks for playing Blackjack!\n";
}