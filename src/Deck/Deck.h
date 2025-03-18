#ifndef DECK_H
#define DECK_H
#include <vector>
#include <random>
#include "Card/Card.h" 

class Deck
{
private:
    std::vector<Card> cards;

public:
    Deck(); // constructor
    void shuffle(); // shuffles all cards in deck
    Card drawCard(); // method to take card from the dack
    bool isEmpty(); // check if is deck is empty
    void resetDeck(const std::vector<Card> newCards); // refill card deck
};

#endif