#include "Game/Turn/TurnManager.h"
#include <iostream>

TurnManager::TurnManager(const std::vector<std::unique_ptr<Character>>& playerList) : players(playerList), currentPlayerIndex(0)
{
    if (players.empty()) 
    {
        throw std::runtime_error("TurnManager initialized with empty player list");
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
