#include <algorithm>
#include <random>
#include "Deck/Deck.h"

Deck::Deck() = default;

Deck::~Deck()
{
    for (Card* card : cards)
    {
        delete card;
    }
}

void Deck::shuffle()
{
    std::random_device dev;
    std::mt19937 g(dev());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card* Deck::drawCard()
{
    if (!cards.empty())
    {
        Card* drawnCard = cards.back();
        cards.pop_back();
        return drawnCard;
    }
    throw std::runtime_error("");
}

bool Deck::isEmpty()
{
    return cards.empty();
}

void Deck::resetDeck(const std::vector<Card*>& newCards)
{
    cards = newCards;
    shuffle();
}