#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "../src/Players/Character.h"
#include "../src/Deck/Deck.h"

class Player : public Character
{
private:
    std::vector<Card> hand;

public:
    Player(const std::string &n, int h, int r);

    // interactions with cards
    Card playCard(int index);
    void drawCard(Deck& deck);
    bool needsCards();

    // interactions with hand
    void clearHand();
    std::vector<Card> getHand();
};

#endif