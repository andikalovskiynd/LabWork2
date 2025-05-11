#ifndef CONSOLE_H
#define CONSOLE_H

/**
 * @file Console.h 
 * @brief Namespace for output declaration.
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "Card/Card.h"

/// @brief Forward declaration of GameManager to avoid circular include.
class GameManager;

/// @brief Forward declaration of Character to avoid circular include.
class Character;

/// @brief Forward declaration of Card to avoid circular include.
class Card;

/// @brief Forward declaration of Spirit to avoid circular include.
class Spirit;

/// @brief Output manager. 
namespace Console 
{
    // Formating functions
    /**
     * @brief Prints the message. 
     * @param message String which is wanted to be printed.
    */
    void print(const std::string& message);

    /**
     * @brief Print an error. 
     * @param message String representing the error message.
    */
    void printError(const std::string& message);

    /**
     * @brief Print fatal error. 
     * @param message String representing the fatal error message.
    */
    void printFatalError(const std::string& message);

    /**
     * @brief Print a lot of '-'.
    */
    void printSeparator();

    /**
     * @brief Print empty line.
    */
    void printEmptyLine();

    // Game process functions 
    /**
     * @brief Pause for some time. 
     * @param durations The amount of milliseconds that pause will last.
    */
    void pause(std::chrono::milliseconds durations);

    /**
     * @brief Loading animation. 
     * @param message Message that will be animated. 
     * @param steps How much steps will be in loading. 
     * @param delay How much milliseconds will be between steps. 
    */
    void loadAnimation(const std::string& message, int steps, std::chrono::milliseconds delay);

    /**
     * @brief Print framed status of game including counter, players, health etc. 
     * @param game Used to get players, health etc. 
     * @param counter Counter of turns. 
     * @param currentPlayer Current player. 
    */
    void printGameStatus(GameManager& game, int counter, Character& currentPlayer);

    /**
     * @brief Print framed cards hand of exact player. 
     * @param player Player whose hand is wanted to be printed. 
    */
    void printPlayerHand(const Character& player);

    /**
     * @brief Print whose turn is now. 
     * @param currentPlayer Player whose turn is now. 
    */
    void printTurn(const Character& currentPlayer);

    /**
     * @brief Print who played and which card. 
     * @param player Player who plays the card. 
     * @param card Card which is being played. 
    */
    void printPlayedCard(const Character& player, const Card& card);

    /**
     * @brief Print a message that player needs cards. 
     * @param player Player who needs cards. 
    */
    void printNeedsCardsMessage(const Character& player);

    /**
     * @brief Print a message that player wants wants to quit game. 
     * @param player Player who wants to quit. 
    */
    void printQuitMessage(const Character& player);

    /**
     * @brief Print a game over message with winner's name. 
     * @param winner Player who won the game. 
    */
    void printGameOver(const Character* winner);

    /**
     * @brief Print effect that spirit applied on the target. 
     * @param target Player who is being affected by the spirit. 
     * @param effectMessage Some message which comes with spirit. 
    */
    void printSpiritEffect(const Character& target, const std::string& effectMessage);

    /**
     * @brief Print a card that is being failed to play and player's name. 
     * @param player Player who failed to play a card. 
    */
    void printFailedToPlayCard(const Character& player);

    // Input functions
    /**
     * @brief Print various menu with options in every new line. 
     * @param options Any options that will be printed.  
    */
    void printMenu(const std::vector<std::string>& options);

    /**
     * @brief Print that error occured at input stage. Parted from just error to make logic more abstract. 
     * @param message Message that is wanted to be said. 
    */
    void printInvalidInput(const std::string& message);

    // Game states functions
    /**
     * @brief Print message with entering the state. 
     * @param stateName State name. 
    */
    void printEnterState(const std::string& stateName);
    /**
     * @brief Print message with leaving the state. 
     * @param stateName State name. 
    */
    void printExitState(const std::string& stateName);

    /**
     * @brief Specialized method that simplifies output of Card::Type. Makes std::string from Card::Type. 
     * @param type Type which is being transformed to string.
     * @return String which represents the card type. 
    */
    std::string typeToString(Card::Type type);

    /**
     * @brief Print additional information about cards: damage, magic respect etc. 
     * @param card Card which is being described. 
    */
    void printAdditionalInfo(const Card& card);
}

#endif