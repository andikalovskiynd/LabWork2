#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>

class GameManager;
class Character;
class Card;
class Spirit;

namespace Console 
{
    // Formating functions
    void print(const std::string& message);
    void printError(const std::string& message);
    void printFatalError(const std::string& message);
    void printSeparator();
    void printEmptyLine();

    // Game process functions 
    void pause(std::chrono::milliseconds durations);
    void loadAnimation(const std::string& message, int steps, std::chrono::milliseconds delay);
    void printGameStatus(GameManager& game, int counter, Character& currentPlayer);
    void printPlayerHand(const Character& player);
    void printTurn(const Character& currentPlayer);
    void printPlayedCard(const Character& player, const Card& card);
    void printNeedsCardsMessage(const Character& player);
    void printQuitMessage(const Character& player);
    void printGameOver(const Character* winner);
    void printSpiritEffect(const Character& target, const std::string& effectMessage);
    void printFailedToPlayCard(const Character& player);

    // Input functions
    void printMenu(const std::vector<std::string>& options);
    void printInvalidInput(const std::string& message);

    // Game states functions
    void printEnterState(const std::string& stateName);
    void printExitState(const std::string& stateName);
}

#endif