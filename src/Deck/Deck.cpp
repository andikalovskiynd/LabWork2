#include <algorithm>
#include <random>
#include "Deck/Deck.h"

Deck::Deck() = default;

Deck::~Deck() = default;

void Deck::shuffle()
{
    std::random_device dev;
    std::mt19937 g(dev());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::unique_ptr<Card> Deck::drawCard()
{
    if (!cards.empty())
    {
        std::unique_ptr<Card> drawnCard = std::move(cards.back());
        cards.pop_back();
        return drawnCard;
    }
    throw std::runtime_error("Attempted to draw from an empty deck.");
}

bool Deck::isEmpty()
{
    return cards.empty();
}

void Deck::resetDeck(std::vector<std::unique_ptr<Card>> newCards)
{
    cards = std::move(newCards);
    shuffle();
}