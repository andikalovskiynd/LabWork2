#include <algorithm>
#include <random>
#include "../include/Deck.h"

Deck::Deck() : counter(0)
{
    cards.push_back(Card("example", 0, 0, 0));
    //cards 
    shuffleDeck();
}

void Deck::shuffleDeck()
{
    std::random_device dev;
    std::mt19937 g(dev());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::drawCard()
{
    if (cards.empty())
    {
        //
    }

    counter++;
    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

Card Deck::checkForUpgrade (Card baseCard)
{
    if (counter >= 10)
    {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<int> dist(1, 100);
        if(dist(gen) <= 25)
        {
            return getHighLevelCard(baseCard);
        }
    }
    return baseCard;
}

Card Deck::getHighLevelCard (const Card& baseCard)
{
    if (baseCard.getName() == "NAME EXAMPLE") 
    {return Card("NAME EXAMPLE (strengthened)", 0, 0, 0);}
    // также с другими картами
    return baseCard;
}