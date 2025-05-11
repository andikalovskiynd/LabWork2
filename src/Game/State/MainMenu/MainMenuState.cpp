#include "Game/State/MainMenuState.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/Gamestate.h"
#include "Game/State/SetupState.h"
#include "Utilities/Console.h"
#include "Utilities/Input.h"

void MainMenuState::enterState(GameManager& game)
{
    Console::printEmptyLine();
    Console::printEnterState("Main menu");
    Console::print("Welcome!");
    Console::printEmptyLine();
    Console::printMenu({"1) Start a new game", "2) Leave "});
    Console::printEmptyLine();
    Console::printSeparator();
}

void MainMenuState::updateState(GameManager& game)
{
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

void MainMenuState::exitState(GameManager& game)
{
    Console::printExitState("Main menu");
}