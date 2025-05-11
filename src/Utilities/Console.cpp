/**
 * @file Console.cpp 
 * @brief Implementation of class Console methods. 
*/

#include "Utilities/Console.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Character.h"
#include "Card/Card.h"                  
#include "Game/Spirit/Spirit.h"          
#include <iostream>
#include <vector> 
#include <memory> 
#include <chrono>
#include <thread>
#include <limits> 
#include <ios>    

namespace Console
{
    void pause(std::chrono::milliseconds duration)
    {
        std::this_thread::sleep_for(duration);
    }

    // Formating functions
    void print(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    void printError(const std::string& message)
    {
        std::cerr << "Error: " << message << std::endl;
    }

    void printFatalError(const std::string& message)
    {
        std::cerr << "FATAL ERROR: " << message << std::endl;
    }

    void printSeparator()
    {
        std::cout << "---------------------------------------------------------------------" << std::endl;
    }

    void printEmptyLine()
    {
        std::cout << std::endl;
    }

    // Game process
    void loadAnimation(const std::string& message, int steps, std::chrono::milliseconds delay)
    {
        std::cout << message;
        std::cout.flush();

        for (int i = 0; i < steps; ++i)
        {
            std::cout << "...";
            std::cout.flush();
            std::this_thread::sleep_for(delay);
        }
        std::cout << std::endl;
    }

    void printGameStatus(GameManager& game, int counter, Character& currentPlayer)
    {
        pause(std::chrono::milliseconds(1000));
        const auto& players = game.getPlayers();

        Character* player1 = players[0].get();
        Character* player2 = players[1].get();

        printEmptyLine();
        std::cout << "--- " << player1->getName() << " versus " << player2->getName() << " --- STEP " << counter << " , Turn: "  << currentPlayer.getName() << " ---" << std::endl;
        printEmptyLine();

        pause(std::chrono::milliseconds(250));

        std::cout << "Health " << player1->getName() << " : " << player1->getHealth() << std::endl;
        std::cout << "Health " << player2->getName() << " : " << player2->getHealth() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();
        pause(std::chrono::milliseconds(250));

        std::cout << "Respect " << player1->getName() << ": " << player1->getRespect() << std::endl;
        std::cout << "Respect " << player2->getName() << ": " << player2->getRespect() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();
        pause(std::chrono::milliseconds(250));

        std::cout << "Magic: " << game.getMagicPool() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();
        pause(std::chrono::milliseconds(250));

        printPlayerHand(currentPlayer); 

        printSeparator();
        printEmptyLine();
    }

    void printPlayerHand(const Character& player)
    {
        const auto& hand = player.getHand(); 
        std::cout << player.getName() << "'s cards: " << std::endl;

        if (hand.empty())
        {
            std::cout << "    (Empty)" << std::endl;
        }
        else
        {
            for (size_t i = 0; i < hand.size(); ++i)
            {
                pause(std::chrono::milliseconds(250));
                std::cout << "      " << i << ") " << hand[i]->getName() << " (health: " << hand[i]->getHealthEffect() << ", magic: " << hand[i]->getMagicEffect() << ", respect: " << hand[i]->getRespectEffect() << ", type: "<< typeToString(hand[i]->getType()) << ")" << std::endl;
            }
        }
        printEmptyLine();
    }

    void printTurn(const Character& currentPlayer)
    {
        printEmptyLine();
        std::cout << "Turn for " << currentPlayer.getName() << "." << std::endl;
        printEmptyLine();
        printSeparator();
        printEmptyLine();
    }

    void printPlayedCard(const Character& player, const Card& card)
    {
        printEmptyLine();
        printSeparator();
        std::cout << player.getName() << " played card " << card.getName() << std::endl;
        printSeparator();
        printEmptyLine();
    }

    void printNeedsCardsMessage(const Character& player)
    {
        std::cout << player.getName() << " gathers cards." << std::endl;
    }

    void printQuitMessage(const Character& player)
    {
        std::cout << player.getName() << " asked to quit." << std::endl;
    }

    void printGameOver(const Character* winner)
    {
        if (winner)
        {
            std::cout << "Game over! Winner: " << winner->getName() << std::endl;
        }
        else
        {
            std::cout << "Draw! No one left the battlefield.." << std::endl;
        }
    }

    void printSpiritEffect([[maybe_unused]]const Character& target, const std::string& effectMessage)
    {
        std::cout << effectMessage << std::endl;
    }

    void printFailedToPlayCard(const Character& player)
    {
        std::cout << player.getName() << " failed to play a card." << std::endl;
    }

    // Input 
    void printMenu(const std::vector<std::string>& options)
    {
        for(const auto& option : options)
        {
            std::cout << option << std::endl;
        }
    }

    void printInvalidInput(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    // Game state functions
    void printEnterState(const std::string& stateName)
    {
        printEmptyLine();
        std::cout << "--- Entering: " << stateName << " ---" << std::endl;
        printEmptyLine();
    }

    void printExitState(const std::string& stateName)
    {
        printEmptyLine();
        std::cout << "--- Leaving: " << stateName << " ---" << std::endl;
        printEmptyLine();
    }

    std::string typeToString(Card::Type type)
    {
        switch(type)
        {
            case Card::Type::ATTACK: return "Attack";
            case Card::Type::HEAL: return "Heal";
            case Card::Type::MAGIC: return "Magic";
            case Card::Type::RESPECT: return "Respect";
            default: return "UNKNOWN TYPE";
        }
    }

    void printAdditionalInfo(const Card& card)
    {
        printSeparator();
        printEmptyLine();
        std::cout << "--- Information for " << card.getName() << " ---" << std::endl;
        printEmptyLine();
        std::cout << "Type: " << typeToString(card.getType()) << std::endl;
        printEmptyLine();
        std::cout << "Effects: " << std::endl;
        switch(card.getType())
        {
            case Card::Type::ATTACK:
            std::cout << "  Damage to opponent: " << card.getHealthEffect() << std::endl;
            std::cout << "  Magic in favor of opponent: " << card.getMagicEffect() << std::endl;
            std::cout << "  Your respect loss: " << card.getRespectEffect() << std::endl;
            break;

            case Card::Type::HEAL:
            std::cout << "  Healing: " << card.getHealthEffect() << std::endl;
            std::cout << "  Magic in favor of opponent: " << card.getMagicEffect() << std::endl;
            std::cout << "  Your respect loss: " << card.getRespectEffect() << std::endl;
            break;

            case Card::Type::MAGIC:
            std::cout << "  Damage to you: " << card.getHealthEffect() << std::endl;
            std::cout << "  Magic in your favor: " << card.getMagicEffect() << std::endl;
            std::cout << "  Your respect loss: " << card.getRespectEffect() << std::endl;
            break;

            case Card::Type::RESPECT:
            std::cout << "  Damage to you: " << card.getHealthEffect() << std::endl;
            std::cout << "  Magic in favor of opponent: " << card.getMagicEffect() << std::endl;
            std::cout << "  Your respect increase: " << card.getRespectEffect() << std::endl; 
            break;

            default:
            print("Information is unavailable.");
            break;
        }
        printEmptyLine();
        printSeparator();
        printEmptyLine();
    }
}