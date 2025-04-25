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
    Console::print("Добро пожаловать!");
    Console::printEmptyLine();
    Console::printMenu({"1) Начать новую игру", "2) Выйти "});
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
        Console::print("Выход...");
        game.setState(nullptr);
    }

    else
    {
        Console::printInvalidInput("Некорректный выбор. Пожалуйста, введите 1 или 2.");
    }
}

void MainMenuState::exitState(GameManager& game)
{
    Console::printExitState("Main menu");
}