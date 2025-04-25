#include "Game/State/MainMenuState.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/Gamestate.h"
#include "Game/State/SetupState.h"
#include "Utilities/Console.h"

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
    int choice;
    if (std::cin >> choice)
    
    {
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
            Console::printInvalidInput("Некорректный ввод. Пожалуйста, введите 1 или 2."); // Уточненное сообщение
        }
    }

    else 
    {
        Console::printInvalidInput("Некорректный ввод. Пожалуйста, введите число (1 или 2)."); // Сообщение об ошибке
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void MainMenuState::exitState(GameManager& game)
{
    Console::printExitState("Main menu");
}