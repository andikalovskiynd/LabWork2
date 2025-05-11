/**
 * @file TurnManager.cpp 
 * @brief Implementation of class TurnManager methods. 
*/

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
    if (players.empty())
    {
        return nullptr;
    }

    if (currentPlayerIndex < 0 || static_cast<size_t>(currentPlayerIndex) >= players.size())
    {
        return nullptr;
    }
    return players[currentPlayerIndex].get();
}

bool TurnManager::isGameOver()
{
    int alive = 0;
    for (const auto& playerPtr : players)
    {
        if (playerPtr && playerPtr->IsAlive())
        {
            ++alive;
        }
    }
    return alive <= 1;
}
