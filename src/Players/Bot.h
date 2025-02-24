#ifndef BOT_H
#define BOT_H
#include <iostream>
#include "../src/Players/Character.h"
#include "../src/Deck/Deck.h"

enum class Difficulty { EASY, MEDIUM, HARD };

class Bot : public Character
{
private:
    std::vector<Card> hand;

public:
    Bot(const std::string &n, int h, int r);

    // interactions with cards
    void drawCard(Deck& deck);
    bool needsCards();

    // interactions with hand
    void clearHand();
    std::vector<Card> getHand();

    // STUPID MOVE (JUST FOR NOW)
    Card makeStupidMove();
};

#endif