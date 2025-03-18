#include "Game/State/Playing/PlayingState.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"

PlayingState::PlayingState(std::vector<Character*>& p, Deck& d) : deck(d)
{
    turnManager = new TurnManager(p);
}

PlayingState::~PlayingState()
{
    delete turnManager;
}

void PlayingState::updateState(GameManager& game)
{
    processTurn(game);
    if (isGameOver())
    {
        game.setState(new EndGameState(turnManager->getCurrentPlayer()));
    }
}

void PlayingState::processTurn(GameManager& game)
{
    Character* currentPlayer = turnManager->getCurrentPlayer();
    std::cout << "Ходит " << currentPlayer->getName() << std::endl;

    Card playedCard = currentPlayer->takeTurn();
    std::cout << currentPlayer->getName() << " сыграл карту " << playedCard.getName() << std::endl;

    currentPlayer->ApplyCardEffect(playedCard, game);

    std::cout << "Пул магии: " << game.getMagicPool() << std::endl;
    std::cout << "Здоровье игрока " << currentPlayer->getHealth() << std::endl;

    if (currentPlayer->needsCards())
    {
        currentPlayer->drawInitCards(deck);
    }

    turnManager->nextTurn();
}

bool PlayingState::isGameOver()
{
    Character* currentPlayer = turnManager->getCurrentPlayer();
    if (currentPlayer->IsAlive())
    {
        return false;
    }
    return true;
}

void PlayingState::enterState(GameManager& game)
{
    std::cout << "Вход в игровое пространство.." << std::endl;
}

void PlayingState::exitState(GameManager& game)
{
    std::cout << "Игра окончена!" << std::endl;
}