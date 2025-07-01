#pragma once
#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include <string>

struct Card {
    std::string rank;
    int value;
};

void playBlackjackGame();

#endif