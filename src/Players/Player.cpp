#include "Players/Player.h"

Player::Player(const std::string &n, int h, int r) : Character(n, h, r) {}

// interactions with cards
std::unique_ptr<Card> Player::playCard(int index)
{
    if (index >= 0 && index < static_cast<int>(hand.size()))
    {
        std::unique_ptr<Card> chosenCard = std::move(hand[index]);
        hand.erase(hand.begin() + index);
        return chosenCard;
    }

    else
    {
        std::cout << "Вы выбрали карту, которой у вас нет. Думали обмануть систему? Смеется тот, кто смеется последний..." << std::endl;
        if (!hand.empty())
        {
            std::unique_ptr<Card> chosenCard = std::move(hand.front());
            hand.erase(hand.begin());
            return chosenCard;
        }
        return nullptr;
    }
}

std::unique_ptr<Card> Player::takeTurn()
{
    int index;
    std::cout << "Введите индекс карты: " << std::endl;
    // TODO: Добавить надежную проверку ввода (не число, выход за границы)
    std::cin >> index;
    return playCard(index);
}

void Player::drawCard(Deck& deck)
{
    if (!deck.isEmpty()) 
    {
        hand.push_back(deck.drawCard()); 
    }
}

bool Player::needsCards()
{
    return hand.size() < 5;
}

// interactions with hand
const std::vector<std::unique_ptr<Card>>& Player::getHand() const 
{
    return hand;
}

void Player::clearHand()
{
    hand.clear();
}

void Player::drawInitCards(Deck& deck)
{
    for(int i = 0; i < 5; ++i)
    {
        if(!deck.isEmpty())
        {
            hand.push_back(deck.drawCard());
        }
    }
}