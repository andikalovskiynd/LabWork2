#include "Game/GameManager/GameManager.h"
#include <utility>
#include <memory>
#include "Utilities/Console.h"
#include "Players/Character.h"

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
    activeSpirits.clear();
    magicPool = 0;
}

void GameManager::setCurrentPlayer(Character* player)
{
    currentPlayer = player;
}

int GameManager::getMagicPool() const
{
    return magicPool;
}

void GameManager::updateMagicPool(int amount)
{
    magicPool += amount;
}

bool GameManager::shouldAmplify() const
{
    if (currentPlayer == players[1].get() && magicPool <= -10)
    {
        std::cout << "MAGIC POOL IS <= 10, " << players[1].get() << "'s NEXT CARD IS AMPLIFIED" << std::endl;
        return true;
    }
    else if (currentPlayer == players[0].get() && magicPool >= 10)
    {
        std::cout << "MAGIC POOL IS >= 10, " << players[0].get() << "'s NEXT CARD IS AMPLIFIED" << std::endl;
        return true;
    }
    else
    {
        std::cout << "MAGIC IS IN APPROPRIATE STATE" << std::endl;
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
        Console::printError("Error: attempted to add empty spirit");
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
        Console::printError("Error: attempted to add empty player");
    }
}