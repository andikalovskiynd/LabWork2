#include "Game/State/PlayingState.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Player.h"
#include "Game/State/MainMenuState.h"

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
        std::cerr << "Error: No current player in processTurn." << std::endl;
        game.setState(nullptr);
        return;
    }

    Character* player1 = players[0].get();
    Character* player2 = players[1].get();

    if (player1 == nullptr || player2 == nullptr) 
    {
        std::cerr << "Error: Player pointers are null in processTurn." << std::endl;
        game.setState(nullptr);
        return;
    }

    std::cout << std::endl;
    std::cout << "--- " << player1->getName() << " против " << player2->getName() << " --- ХОД " << counter << " за игроком "  << currentPlayer->getName() << " ---" << std::endl;
    std::cout << std::endl;
    std::cout << "Здоровье " << player1->getName() << ": " << player1->getHealth() << ",              Уважение: " << player1->getRespect() << std::endl;
    std::cout << "Здоровье " << player2->getName() << ": " << player2->getHealth() << ",              Уважение: " << player2->getRespect() << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Магия: " << game.getMagicPool() << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    const auto& currentHand = currentPlayer->getHand();
    std::cout << "Карты " << currentPlayer->getName() << " : " << std::endl;

    if (currentHand.empty()) 
    {
        std::cout << "    (Пусто)" << std::endl;
    }

    else 
    {
        for (size_t i = 0; i < currentHand.size(); ++i)
        {
            if (currentHand[i]) 
            {
                std::cout << "    " << i << ") " << currentHand[i]->getName() << std::endl;
            } 
            else 
            {
                std::cout << "    " << i << ") [Пустая ячейка]" << std::endl; // На всякий случай
            }
        }
    }
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Ход " << currentPlayer->getName() << "." << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::unique_ptr<Card> playedCard = currentPlayer->takeTurn();
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    Player* human = dynamic_cast<Player*>(currentPlayer);
    if (human && human->wantsToQuit())
    {
        std::cout << human->getName() << " запросил выход из игры." << std::endl;
        game.setState(std::make_unique<MainMenuState>());
        return;
    }

    if (playedCard)
    {
        std::cout << currentPlayer->getName() << " сыграл карту " << playedCard->getName() << std::endl;
        currentPlayer->ApplyCardEffect(*playedCard, game);
    }
    else
    {
        std::cerr << "Error: Player " << currentPlayer->getName() << " failed to play a card." << std::endl;
    }

    if (currentPlayer->needsCards())
    {
        currentPlayer->drawInitCards(deck);
    }

    counter = counter + 1;
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
    counter = 1;
}

void PlayingState::exitState(GameManager& game)
{
    std::cout << "Игра окончена!" << std::endl;
}