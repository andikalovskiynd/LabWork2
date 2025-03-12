#include "Game/State/End/EndGameState.h"
#include "Game/State/Setup/SetupState.h"
#include <iostream>

EndGameState::EndGameState(Character* w) : winner(w) {}

void EndGameState::enterState(GameManager& game)
{
    std::cout << "Игра окончена. Победитель: " << winner->getName() << std::endl;
    for (Character* player : game.getPlayers())
    {
        delete player;
    }
    game.clearPlayers();
}

void EndGameState::updateState(GameManager& game)
{
    int choice;
    std::cout << "Введите 0, чтобы выйти" << std::endl;
    std::cin >> choice;
    if (choice == 0)
    {
        game.setState(nullptr);
    }
    else 
    {
        std::cout << "Некорректный ввод" << std::endl;
    }
}

void EndGameState::exitState(GameManager& game)
{
    std::cout << "Выход..." << std::endl;

}