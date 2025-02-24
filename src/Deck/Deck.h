#ifndef DECK_H
#define DECK_H
#include <vector>
#include <random>
#include "../src/Card/Card.h"

class Deck
{
private:
    std::vector<Card> cards;

public:
    Deck();
    void shuffle();
    Card drawCard();
    bool isEmpty();
    void resetDeck(const std::vector<Card> newCards);
};

#endif