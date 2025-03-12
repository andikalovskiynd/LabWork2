#ifndef BOT_H
#define BOT_H
#include <iostream>
#include "Players/Character.h"
#include "Deck/Deck.h"

enum class Difficulty { EASY, MEDIUM, HARD };

class Bot : public Character
{
private:
    std::vector<Card> hand;

public:
    Bot(const std::string &n, int h, int r);

    // interactions with cards
    void drawCard(Deck& deck); // to take card from deck
    bool needsCards() override; // check if crads quantity is less than 5

    // interactions with hand
    void clearHand(); // clear 'hand' vector 
    std::vector<Card> getHand(); // to get 'hand' vector 

    // STUPID MOVE (JUST FOR NOW)
    Card makeStupidMove(); // throw always first card

    Card takeTurn() override; // use makeStupidMove. implied just to inherit for convinience in game organization

    virtual void drawInitCards(Deck& deck) override; // take first 'hand' from deck
};

#endif