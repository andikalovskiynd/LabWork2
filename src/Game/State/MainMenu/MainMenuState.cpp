#include "Game/State/MainMenu/MainMenuState.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/Gamestate.h"
#include "Game/State/Setup/SetupState.h"

void MainMenuState::enterState(GameManager& game)
{
    std::cout << "Добро пожаловать! Для продолжения нажмите 1. Для выхода нажмите 2." << std::endl;
}

void MainMenuState::updateState(GameManager& game)
{
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        game.setState(new SetupState(game.getDeck(), game.getPlayers())); // сделать переxод в setupstate
    }
    else if (choice == 2)
    {
        std::cout << "Выход..." << std::endl;
        game.setState(nullptr);
    }
    else 
    {
        std::cout << "Некорректный ввод. Попробуйте еще раз." << std::endl;
    }
}

void MainMenuState::exitState(GameManager& game)
{
    std::cout << "Выход..." << std::endl;
}