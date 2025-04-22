#include "Game/State/PlayingState.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"

PlayingState::PlayingState(GameManager& game) : deck(game.getDeck())
{
    turnManager = std::make_unique<TurnManager>(game.getPlayers());
}

void PlayingState::updateState(GameManager& game)
{
    processTurn(game);
    if (isGameOver(game))
    {
        Character* winner = nullptr;
        const auto& players = game.getPlayers();

        for (const auto& playerPtr : players) 
        {
            if (playerPtr && playerPtr->IsAlive()) 
            {
                winner = playerPtr.get();
                break;
            }
        }

        game.setState(std::make_unique<EndGameState>(winner));
    }
}

void PlayingState::processTurn(GameManager& game)
{
    Character* currentPlayer = turnManager->getCurrentPlayer();

    if (currentPlayer == nullptr) {
        std::cerr << "Error: No current player in processTurn." << std::endl;
        game.setState(nullptr);
        return;
    }

    std::cout << "Ходит " << currentPlayer->getName() << std::endl;

    const auto& currentHand = currentPlayer->getHand();
    std::cout << "Карты " << currentPlayer->getName() << ":" << std::endl;
    for (size_t i = 0; i < currentHand.size(); ++i)
    {
        if (currentHand[i]) 
        { 
            std::cout << i << ") " << currentHand[i]->getName() << std::endl;
        } 
        else 
        {
            std::cout << i << ") [EMPTY]" << std::endl;
        }
    }

    std::unique_ptr<Card> playedCard = currentPlayer->takeTurn();

    if (playedCard)
    {
        std::cout << currentPlayer->getName() << " сыграл карту " << playedCard->getName() << std::endl;
        currentPlayer->ApplyCardEffect(*playedCard, game);
    }
    else
    {
        std::cerr << "Error: Player " << currentPlayer->getName() << " failed to play a card." << std::endl;
    }

    std::cout << "Пул магии: " << game.getMagicPool() << std::endl;
    std::cout << "Здоровье " << currentPlayer->getName() << ": " << currentPlayer->getHealth() << std::endl;

    if (currentPlayer->needsCards())
    {
        currentPlayer->drawInitCards(deck);
    }

    turnManager->nextTurn();
}

bool PlayingState::isGameOver(GameManager& game) const
{
    int alive = 0;
    const auto& players = game.getPlayers();
    for (const auto& playerPtr : players)
    {
        if (playerPtr && playerPtr->IsAlive())
        {
            ++alive;
        }
    }

    return alive <= 1;
}
void PlayingState::enterState(GameManager& game)
{
    std::cout << "Вход в игровое пространство.." << std::endl;
}

void PlayingState::exitState(GameManager& game)
{
    std::cout << "Игра окончена!" << std::endl;
}