#include "Game/Turn/TurnManager.h"
#include <iostream>

TurnManager::TurnManager(const std::vector<Character*>& playerList) : players(playerList), currentPlayerIndex(0) {}

void TurnManager::startTurns()
{
    while (!isGameOver())
    {
        Character* currentPlayer = getCurrentPlayer();
        std::cout << "Ход " << currentPlayer->getName() << std::endl;
        currentPlayer->takeTurn();

        if (!currentPlayer->IsAlive())
        {
            std::cout << currentPlayer->getName() << " проиграл" << std::endl;
            break;
        }

        nextTurn();
    }
}

void TurnManager::nextTurn()
{
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

Character* TurnManager::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

bool TurnManager::isGameOver()
{
    int alive = 0;
    for (Character* player : players)
    {
        if (player->IsAlive())
        {
            ++alive;
        }
    }

    return alive <= 1;
}
