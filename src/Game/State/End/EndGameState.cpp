#include "Game/State/EndGameState.h"
#include "Game/State/SetupState.h"
#include "Game/State/MainMenuState.h"
#include <iostream>
#include "Utilities/Console.h"

EndGameState::EndGameState(Character* w) : winner(w) {}

void EndGameState::enterState(GameManager& game)
{
    Console::printEnterState("Setup state");
    Console::printGameOver(winner);
}

void EndGameState::updateState(GameManager& game)
{
    int choice;
    Console::printMenu({"1) Начать новую игру", "2) Выйти"});
    std::cin >> choice;
    if (choice == 2)
    {
        game.setState(nullptr);
    }
    else if (choice == 1)
    {
        game.clearPlayers();
        game.setState(std::make_unique<SetupState>(game.getDeck()));
    }
    else 
    {
        Console::printInvalidInput("Некорректный ввод");
    }
}

void EndGameState::exitState(GameManager& game)
{
    Console::print("Выход...");
}