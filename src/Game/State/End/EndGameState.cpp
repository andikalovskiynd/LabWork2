#include "Game/State/EndGameState.h"
#include "Game/State/SetupState.h"
#include "Game/State/MainMenuState.h"
#include <iostream>
#include "Utilities/Console.h"
#include "Utilities/Input.h"

EndGameState::EndGameState(Character* w) : winner(w) {}

void EndGameState::enterState(GameManager& game)
{
    Console::printEnterState("Setup state");
    Console::printGameOver(winner);
}

void EndGameState::updateState(GameManager& game)
{
    Console::printMenu({"1) Start a new game", "2) Leave"});
    int choice = InputManager::getMenuChoice();

    if (choice == 1)
    {
        game.setState(std::make_unique<SetupState>(game.getDeck()));
    }

    else if (choice == 2)
    {
        Console::print("Leaving...");
        game.setState(nullptr);
    }

    else
    {
        Console::printInvalidInput("Incorrect choice. Please enter 1 or 2.");
    }
}

void EndGameState::exitState(GameManager& game)
{
    Console::print("Leaving...");
}