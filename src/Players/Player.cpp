#include "Players/Player.h"
#include "Game/GameManager/GameManager.h"

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
    quitRequested = false; 
    std::string input; 
    int index = -1;
    bool validInput = false;
    bool quitAttempt = false;

    const auto& currentHand = getHand();
    if (currentHand.empty()) 
    {
        std::cout << "У вас нет карт!" << std::endl;
        return nullptr;
    }

    while (!validInput && !quitAttempt)
    {
        std::cout << "Введите индекс карты (0-" << currentHand.size() - 1 << ") или 'quit' для выхода: " << std::endl;
        std::cin >> input;

        if (input == "quit") 
        {
            quitAttempt = true; 
            quitRequested = true;
        }
        else
        {
            try 
            {
                size_t pos;
                index = std::stoi(input, &pos);

                if (pos != input.size()) 
                {
                    throw std::invalid_argument("Error: Invalid input");
                }

                if (index < 0 || index >= static_cast<int>(currentHand.size()))
                {
                    std::cout << "Некорректный индекс. Выберите карту из диапазона от 0 до " << currentHand.size() - 1 << "." << std::endl;
                }

                else
                {
                    validInput = true;
                }
            }

            catch (const std::invalid_argument& i) 
            {
                std::cout << "Некорректный ввод. Пожалуйста, введите число или 'quit'." << std::endl;
            }
        }
    }

    if (quitAttempt) 
    {
        return nullptr;
    }

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
    while (hand.size() < 5 && !deck.isEmpty())
    {
        hand.push_back(deck.drawCard());
    }
}

bool Player::wantsToQuit() const
{
    return quitRequested;
}