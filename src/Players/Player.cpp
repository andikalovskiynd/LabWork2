/**
 * @file Player.cpp 
 * @brief Implementation of class Player methods. 
*/

#include "Players/Player.h"
#include "Game/GameManager/GameManager.h"
#include "Utilities/Console.h"
#include "Utilities/Input.h"

Player::Player(const std::string &n, int h, int r) : Character(n, h, r) {}

// interactions with cards
/**
 * @details Despite that this is almost impossible there is additive check if the index is in range to avoid UB.
*/
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
        Console::print("You chose card that are not in your hand! You think you're the smart one?..");
        if (!hand.empty())
        {
            std::unique_ptr<Card> chosenCard = std::move(hand.front());
            hand.erase(hand.begin());
            return chosenCard;
        }
        return nullptr;
    }
}

/**
 * @details Processing of different inputs, such as played card index, quit or help.
*/
std::unique_ptr<Card> Player::takeTurn([[maybe_unused]]GameManager& game)
{
    quitRequested = false;  
    int index = -1;
    bool validInput = false;
    bool quitAttempt = false;

    const auto& currentHand = getHand();
    if (currentHand.empty()) 
    {
        Console::print("You don't have cards!");
        return nullptr;
    }

    while (!validInput && !quitAttempt)
    {
        Console::print("Enter card index (0-" + std::to_string(currentHand.size() - 1) + "), 'quit' to quit or 'help i' for additional card information: ");
        std::string input = InputManager::getStringInput();

        if (input == "quit" || input == "exit") 
        {
            quitAttempt = true; 
            quitRequested = true;
        }
        else if (input == "help 0")
        {
            Console::printAdditionalInfo(*currentHand[0]);
        }
        else if (input == "help 1")
        {
            Console::printAdditionalInfo(*currentHand[1]);
        }
        else if (input == "help 2")
        {
            Console::printAdditionalInfo(*currentHand[2]);
        }
        else if (input == "help 3")
        {
            Console::printAdditionalInfo(*currentHand[3]);
        }
        else if (input == "help 4")
        {
            Console::printAdditionalInfo(*currentHand[4]);
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
                    Console::printInvalidInput("Incorrect index. Choose in range from 0 to " + std::to_string(currentHand.size() - 1) + ".");
                }

                else
                {
                    validInput = true;
                }
            }

            catch (const std::invalid_argument& i) 
            {
                Console::printInvalidInput("Incorrect input.");
            }

            catch (const std::out_of_range& i)
            {
                Console::printInvalidInput("Entered number is too small or too big. Try again!");
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