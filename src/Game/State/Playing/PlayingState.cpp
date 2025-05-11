/**
 * @file PlayingState.cpp
 * @brief Implementation of class PlayingState methods.
*/

#include "Game/State/PlayingState.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Player.h"
#include "Game/State/MainMenuState.h"
#include "Utilities/Console.h"
#include "Card/Defined.h"
#include <algorithm>

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

/**
 * @details At start some checks, then printing the game information, then getting played card from player or bot and 
 * then, if turn counter is more than 10, getting random card from collection which is already not in the game. Then processing 
 * spirits and srtarting the next turn. 
*/
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
    std::unique_ptr<Card> playedCard = currentPlayer->takeTurn(game);

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

    if (counter > 10)
    {
        const auto& players = game.getPlayers();
        const auto& currentDeckCards = game.getDeck().getCards();

        const auto& player1Hand = players[0]->getHand();
        const auto& player2Hand = players[1]->getHand();

        std::vector<std::string> existingCards;

        for (const std::unique_ptr<Card>& card : currentDeckCards)
        {
            existingCards.push_back(card->getName());
        }

        for (const std::unique_ptr<Card>& card : player1Hand)
        {
            existingCards.push_back(card->getName());
        }

        for (const std::unique_ptr<Card>& card : player2Hand)
        {
            existingCards.push_back(card->getName());
        }

        std::vector<std::unique_ptr<Card>> allPossibleCards = createCollection();
        std::vector<std::unique_ptr<Card>> potentialNewCards;

        for (std::unique_ptr<Card>& card : allPossibleCards)
        {
            auto relevant = std::find(existingCards.begin(), existingCards.end(), card->getName());
            if (relevant == existingCards.end()) 
            {
                potentialNewCards.push_back(std::move(card));
            }
        }
        
        if (!potentialNewCards.empty())
        {
            std::random_device dev;
            std::mt19937 g(dev());
            std::shuffle(potentialNewCards.begin(), potentialNewCards.end(), g);
            std::unique_ptr<Card> newCard = std::move(potentialNewCards[0]);
            game.getDeck().addCard(std::move(newCard));
        }
    }

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
void PlayingState::enterState([[maybe_unused]]GameManager& game)
{
    Console::printEnterState("Playing state");
    counter = 1;
}

void PlayingState::exitState([[maybe_unused]]GameManager& game)
{
    Console::printExitState("Playing state");
}