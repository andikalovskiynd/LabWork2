#include "Players/Bot.h"

Bot::Bot(const std::string &n, int h, int r) : Character(n, h, r) {}

// interactions with cards
void Bot::drawCard(Deck& deck)
{
    if (!deck.isEmpty())
    {
        hand.push_back(deck.drawCard());
    }
}

bool Bot::needsCards()
{
    return hand.size() < 5;
}

// interactions with hand
std::vector<std::unique_ptr<Card>> Bot::getHand()
{
    return hand;
}

void Bot::clearHand()
{
    hand.clear();
}

// STUPID MOVE (JUST FOR NOW)
std::unique_ptr<Card> Bot::makeStupidMove()
{
    if (!hand.empty())
    {
        std::unique_ptr<Card> chosenCard = std::move(hand.front());
        hand.erase(hand.begin());
        return chosenCard;
    }
    return nullptr;
}

std::unique_ptr<Card> Bot::takeTurn()
{
    return makeStupidMove();
}

void Bot::drawInitCards(Deck& deck)
{
    for(int i = 0; i < 5; ++i)
    {
        if(!deck.isEmpty())
        {
            hand.push_back(deck.drawCard());
        }
    }
}