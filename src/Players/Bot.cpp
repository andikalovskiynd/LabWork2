#include "Players/Bot.h"
#include <thread>
#include <chrono>

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
const std::vector<std::unique_ptr<Card>>& Bot::getHand() const
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
    std::cout << "Думает..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Все еще думает" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return makeStupidMove();
}

void Bot::drawInitCards(Deck& deck)
{
    while (hand.size() < 5 && !deck.isEmpty())
    {
        hand.push_back(deck.drawCard());
    }
}

bool Bot::wantsToQuit() const
{
    return false;
}