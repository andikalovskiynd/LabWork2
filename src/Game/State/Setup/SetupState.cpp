/**
 * @file SetupState.cpp 
 * @brief Implementation of class SetupState methods. 
*/

#include "Game/State/SetupState.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include "Card/Defined.h"
#include <vector>
#include <thread>
#include <chrono>
#include "Utilities/Console.h"
#include "Utilities/Input.h"

SetupState::SetupState (Deck& d) : deck(d) {}

/**
 * @details Using the Console::loadAnimation() to make loading process sharp.
*/
void SetupState::enterState(GameManager& game)
{
    Console::printEnterState("Setup state");
    std::vector<std::unique_ptr<Card>> collection = createCollection();
    game.getDeck().resetDeck(std::move(collection));
    initPlayers(game);
    initHands(game);
    Console::loadAnimation("Entering playing state...", 3, std::chrono::seconds(1));
    game.setState(std::make_unique<PlayingState>(game));
}

void SetupState::updateState([[maybe_unused]] GameManager& game) {}
void SetupState::exitState([[maybe_unused]] GameManager& game) {}

void SetupState::initPlayers(GameManager& game)
{
    game.clearPlayers();
    std::string playerName;

    Console::print("Enter your name");
    playerName = InputManager::getStringInput();

    std::unique_ptr<Character> human = std::make_unique<Player>(playerName, 20, 10);
    game.addPlayer(std::move(human));

    Console::print("Choose difficulty (1-3 from easy to hard)");
    int difficulty = InputManager::getInt(1, 3);

    std::unique_ptr<Character> bot;
    switch (difficulty)
    {
        case 1: bot = std::make_unique<Bot>("Valera", 15, 5, Difficulty::EASY); break;
        case 2: bot = std::make_unique<Bot>("Anton", 20, 10, Difficulty::MEDIUM); break;
        case 3: bot = std::make_unique<Bot>("Bogdan", 25, 20, Difficulty::HARD); break;
        default: 
            Console::printInvalidInput("Incorrect input. Difficulty is set to easy. ");
            bot = std::make_unique<Bot>("Anatoliy", 15, 5, Difficulty::EASY);
            break;
    }

    if (bot)
    {
        game.addPlayer(std::move(bot));
    }

    else
    {
        Console::printError("Failed to create bot");
    }
}

void SetupState::initHands(GameManager& game)
{
    const auto& playersInGame = game.getPlayers();
    for (const auto& playerPtr : playersInGame)
    {
        if (playerPtr) 
        {
            playerPtr->drawInitCards(deck);
        }
    }
}