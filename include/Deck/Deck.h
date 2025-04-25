#ifndef DECK_H
#define DECK_H
#include <vector>
#include <random>
#include <memory>
#include "Card/Card.h" 

class Card;

class Deck
{
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    Deck(); // constructor
    ~Deck() = default;
    void shuffle(); // shuffles all cards in deck
    std::unique_ptr<Card> drawCard(); // method to take card from the dack
    bool isEmpty(); // check if is deck is empty
    void resetDeck(std::vector<std::unique_ptr<Card>> newCards); // refill card deck
    const std::vector<std::unique_ptr<Card>>& getCards() const;
    void addCard(std::unique_ptr<Card> card);
};

#endif