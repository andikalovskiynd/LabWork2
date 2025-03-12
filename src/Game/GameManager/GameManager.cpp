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