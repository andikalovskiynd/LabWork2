#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Players/Character.h"
#include "Deck/Deck.h"

class Player : public Character
{
private:
    std::vector<Card> hand;

public:
    Player(const std::string &n, int h, int r); // constructor

    // interactions with cards
    Card playCard(int index); // to play a card with it's index in vector
    void drawCard(Deck& deck); // to draw a card from deck using method already implied in class Deck
    bool needsCards() override; // check if player's cards is less than 5

    // interactions with hand
    void clearHand(); // to clear the 'hand' vector 
    std::vector<Card> getHand(); // to get player's vector 'hand
    Card takeTurn() override; // to take turn using playCard method and card's index in vector 'hand'
    
    virtual void drawInitCards(Deck& deck) override; // to initialize the start hand
};

#endif