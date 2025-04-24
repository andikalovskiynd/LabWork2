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
    void pause(std::chrono::milliseconds duration)
    {
        std::this_thread::sleep_for(duration);
    }

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
        const auto& players = game.getPlayers();

        Character* player1 = players[0].get();
        Character* player2 = players[1].get();

        printEmptyLine();
        std::cout << "--- " << player1->getName() << " против " << player2->getName() << " --- ХОД " << counter << " за игроком "  << currentPlayer.getName() << " ---" << std::endl;
        printEmptyLine();

        std::cout << "Здоровье " << player1->getName() << " : " << player1->getHealth() << std::endl;
        std::cout << "Здоровье " << player2->getName() << " : " << player2->getHealth() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();

        std::cout << "Уважение " << player1->getName() << ": " << player1->getRespect() << std::endl;
        std::cout << "Уважение " << player2->getName() << ": " << player2->getRespect() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();

        std::cout << "Магия: " << game.getMagicPool() << std::endl;

        printEmptyLine();
        printSeparator();
        printEmptyLine();

        printPlayerHand(currentPlayer); 

        printSeparator();
        printEmptyLine();
    }

    void printPlayerHand(const Character& player)
    {
        const auto& hand = player.getHand(); 
        std::cout << "Карты " << player.getName() << " : " << std::endl;

        if (hand.empty())
        {
            std::cout << "    (Пусто)" << std::endl;
        }
        else
        {
            for (size_t i = 0; i < hand.size(); ++i)
            {
                std::cout << "      " << i << ") " << hand[i]->getName() << std::endl;
            }
        }
        printEmptyLine();
    }

    void printTurn(const Character& currentPlayer)
    {
        printEmptyLine();
        std::cout << "Ход " << currentPlayer.getName() << "." << std::endl;
        printEmptyLine();
        printSeparator();
        printEmptyLine();
    }

    void printPlayedCard(const Character& player, const Card& card)
    {
        printEmptyLine();
        printSeparator();
        std::cout << player.getName() << " сыграл карту " << card.getName() << std::endl;
        printSeparator();
        printEmptyLine();
    }

    void printNeedsCardsMessage(const Character& player)
    {
        std::cout << player.getName() << " добирает карты." << std::endl;
    }

    void printQuitMessage(const Character& player)
    {
        std::cout << player.getName() << " запросил выход в главное меню." << std::endl;
    }

    void printGameOver(const Character* winner)
    {
        if (winner)
        {
            std::cout << "Игра окончена. Победитель: " << winner->getName() << std::endl;
        }
        else
        {
            std::cout << "Ничья. Не выжил никто..." << std::endl;
        }
    }

    void printSpiritEffect(const Character& target, const std::string& effectMessage)
    {
        std::cout << effectMessage << std::endl;
    }

    void printFailedToPlayCard(const Character& player)
    {
        std::cout << player.getName() << " не сыграл карту." << std::endl;
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
        std::cout << "--- Вход в состояние: " << stateName << " ---" << std::endl;
    }

    void printExitState(const std::string& stateName)
    {
        std::cout << "--- Выход из состояния: " << stateName << " ---" << std::endl;
    }
}