#include <algorithm>
#include <random>
#include "Deck/Deck.h"
#include "Utilities/Console.h"

Deck::Deck() = default;

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
    Console::printFatalError("Attempted to draw a card from an empty deck");
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