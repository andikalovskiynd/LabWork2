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
std::vector<Card> Bot::getHand()
{
    return hand;
}

void Bot::clearHand()
{
    hand.clear();
}

// STUPID MOVE (JUST FOR NOW)
Card Bot::makeStupidMove()
{
    Card chosenCard = hand.front();
    hand.erase(hand.begin());
    return chosenCard;
}

Card Bot::takeTurn()
{
    return makeStupidMove();
}

void Bot::drawInitCards(Deck& deck)
{
    drawCard(deck);
}