#include "../src/Players/Player.h"

Player::Player(const std::string &n, int h, int r) : Character(n, h, r) {}

// interactions with cards
Card Player::playCard(int index)
{
    if (index >= 0 && index < hand.size())
    {
        Card chosenCard = hand[index];
        hand.erase(hand.begin() + index);
        return chosenCard;
    }
}

Card Player::takeTurn()
{
    return playCard(int index);
}

void Player::drawCard(Deck& deck)
{
    if (!deck.isEmpty()) { hand.push_back(deck.drawCard()); }
}

bool Player::needsCards()
{
    return hand.size() < 5;
}

// interactions with hand
std::vector<Card> Player::getHand()
{
    return hand;
}

void Player::clearHand()
{
    hand.clear();
}