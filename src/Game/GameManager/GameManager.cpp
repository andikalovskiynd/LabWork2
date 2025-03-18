#include "Game/GameManager/GameManager.h"
#include <iostream>

GameManager::GameManager(Deck& d) : currentState(nullptr), deck(d) {}

GameManager::~GameManager()
{
    if (currentState)
    {
        currentState->exitState(*this);
        delete currentState;
    }
}

void GameManager::setState(GameState* state)
{
    if (currentState)
    {
        currentState->exitState(*this);
        delete currentState;
    }
    currentState = state;
    if (currentState)
    {
        currentState->enterState(*this);
    }
}

void GameManager::run()
{
    while (currentState)
    {
        currentState->updateState(*this);
    }
}

std::vector<Character*> GameManager::getPlayers()
{
    return players;
}

Deck& GameManager::getDeck()
{
    return deck;
}

void GameManager::clearPlayers()
{
    players.clear();
}

void GameManager::setCurrentPlayer(Character* player)
{
    currentPlayer = player;
}

int GameManager::getMagicPool()
{
    return magicPool;
}

void GameManager::updateMagicPool(int effect)
{
    if (currentPlayer == players[0])
    {
        magicPool -= effect;
    }
    else
    {
        magicPool += effect;
    }
}

bool GameManager::shouldAmplify()
{
    if(currentPlayer == players[0] && magicPool <= -10)
    {
        return true;
    }
    else if(currentPlayer == players[1] && magicPool >= 10)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void GameManager::resetMagicPool()
{
    magicPool = 0;
}

Character* GameManager::getCurrentPlayer()
{
    return currentPlayer;
}