#include "Game/GameManager/GameManager.h"
#include <utility>
#include <iostream>
#include <memory>

GameManager::GameManager(Deck& d) : currentState(nullptr), deck(d) {}

void GameManager::setState(std::unique_ptr<GameState> state)
{
    currentState = std::move(state);
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

const std::vector<std::unique_ptr<Character>>& GameManager::getPlayers() const
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
    currentPlayer = nullptr;
}

void GameManager::setCurrentPlayer(Character* player)
{
    currentPlayer = player;
}

int GameManager::getMagicPool() const
{
    return magicPool;
}

void GameManager::updateMagicPool(int effect)
{
    std::cout << "DEBUG: Entering updateMagicPool. Effect: " << effect << std::endl;

    if (players.empty()) {
         std::cerr << "FATAL ERROR: GameManager::updateMagicPool - players container is empty!" << std::endl;
         abort();
    }

    if (currentPlayer == nullptr) {
        std::cerr << "FATAL ERROR: GameManager::updateMagicPool - currentPlayer is null!" << std::endl;
        abort();
    }

    std::cout << "DEBUG: Comparing currentPlayer (" << currentPlayer << ") with players[0].get() (" << players[0].get() << ")" << std::endl;
    if (currentPlayer == players[0].get())
    {
        magicPool -= effect;
    }
    else
    {
        magicPool += effect;
    }
}

bool GameManager::shouldAmplify() const
{
    if (players.size() < 2 || currentPlayer == nullptr) 
    {
        return false;
    }

    if (currentPlayer == players[0].get() && magicPool <= -10)
    {
        return true;
    }
    else if (currentPlayer == players[1].get() && magicPool >= 10)
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

void GameManager::addSpirit(std::unique_ptr<Spirit> spirit)
{
    if (spirit)
    {
        activeSpirits.push_back(std::move(spirit));
    }
    else
    {
        std::cerr << "Error: attempted to add empty spirit" << std::endl;
    }
}


void GameManager::processSpirits()
{
    for (const auto& spiritPtr : activeSpirits)
    {
        if (spiritPtr)
        {
            spiritPtr->applyEffect();
        }
    }

    std::vector<std::unique_ptr<Spirit>> nextActiveSpirits;
    nextActiveSpirits.reserve(activeSpirits.size());

    for (auto& spiritPtr : activeSpirits) 
    {
        if (spiritPtr && spiritPtr->update()) 
        {
            nextActiveSpirits.push_back(std::move(spiritPtr));
        }
    }

    activeSpirits = std::move(nextActiveSpirits);
}

void GameManager::addPlayer(std::unique_ptr<Character> player)
{
    if (player)
    {
        players.push_back(std::move(player));
    }
    else
    {
        std::cerr << "Error: attempted to add empty player" << std::endl;
    }
}