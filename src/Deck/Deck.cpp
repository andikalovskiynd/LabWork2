/**
 * @file Deck.cpp
 * @brief Implementation of class Deck methods.
*/

#include <algorithm>
#include <random>
#include <utility>
#include "Deck/Deck.h"
#include "Utilities/Console.h"

Deck::Deck() = default;

/**
 * @brief Implementation of shuffling the deck. 
 * @details Randomly renumbers indexes of cards in the deck. 
*/
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
    else
    {
        Console::printFatalError("Attempted to draw a card from an empty deck");
        return nullptr;
    }
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

const std::vector<std::unique_ptr<Card>>& Deck::getCards() const
{
    return cards;
}

void Deck::addCard(std::unique_ptr<Card> card)
{
    cards.push_back(std::move(card));
}