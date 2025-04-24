#include "Game/State/PlayingState.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Player.h"
#include "Game/State/MainMenuState.h"
#include "Utilities/Console.h"

PlayingState::PlayingState(GameManager& game) : deck(game.getDeck()), counter(0)
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
    const auto& players = game.getPlayers();
    Character* currentPlayer = turnManager->getCurrentPlayer();

    if (currentPlayer == nullptr || players.size() < 2) 
    {
        Console::printError("Error: No current player in processTurn.");
        game.setState(nullptr);
        return;
    }

    Character* player1 = players[0].get();
    Character* player2 = players[1].get();

    if (player1 == nullptr || player2 == nullptr) 
    {
        Console::printError("Error: Player pointers are null in processTurn.");
        game.setState(nullptr);
        return;
    }

    Console::printGameStatus(game, counter, *currentPlayer);
    Console::printTurn(*currentPlayer);
    std::unique_ptr<Card> playedCard = currentPlayer->takeTurn();

    Player* human = dynamic_cast<Player*>(currentPlayer);
    if (human && human->wantsToQuit())
    {
        Console::printQuitMessage(*human);
        game.setState(std::make_unique<MainMenuState>());
        return;
    }

    if (playedCard)
    {
        Console::printPlayedCard(*currentPlayer, *playedCard);
        currentPlayer->ApplyCardEffect(*playedCard, game);
    }
    else
    {
        Console::printFailedToPlayCard(*currentPlayer);
    }

    if (currentPlayer->needsCards())
    {
        Console::printNeedsCardsMessage(*currentPlayer);
        currentPlayer->drawInitCards(deck);
    }

    counter++;
    game.processSpirits();
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
    Console::printEnterState("Playing state");
    counter = 1;
}

void PlayingState::exitState(GameManager& game)
{
    Console::printExitState("Playing state");
}