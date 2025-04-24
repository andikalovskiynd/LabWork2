#ifndef BOT_H
#define BOT_H
#include <iostream>
#include "Players/Character.h"
#include "Deck/Deck.h"
#include <memory>

enum class Difficulty { EASY, MEDIUM, HARD };

class Bot : public Character
{
private:
    std::vector<std::unique_ptr<Card>> hand;
    Difficulty botDifficulty;

public:
    Bot(const std::string &n, int h, int r, Difficulty d);

    // interactions with cards
    void drawCard(Deck& deck); // to take card from deck
    bool needsCards() override; // check if crads quantity is less than 5

    // interactions with hand
    void clearHand(); // clear 'hand' vector 
    const std::vector<std::unique_ptr<Card>>& getHand() const override; // to get 'hand' vector 

    // STUPID MOVE (JUST FOR NOW)
    std::unique_ptr<Card> playCard(int index);
    std::unique_ptr<Card> makeStupidMove(); // throw always first card
    std::unique_ptr<Card> takeTurn(GameManager& game) override; // use makeStupidMove. implied just to inherit for convinience in game organization

    virtual void drawInitCards(Deck& deck) override; // take first 'hand' from deck
    bool wantsToQuit() const override;
};

#endif