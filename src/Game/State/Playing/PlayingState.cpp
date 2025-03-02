#include "../src/Game/State/Playing/PlayingState.h"
#include "../src/Game/State/End/EndState.h"
#include "../src/Deck/Deck.h"

PlayingState::PlayingState(std::vector<Character*>& players)
{
    turnManager = new TurnManager(players);
}

void PlayingState::updateState(GameManager& game)
{
    processTurn(game);
    if (isGameOver)
    {
        game.setState(new EndGameState());
    }
}

void PlayingState::processTurn(GameManager& game)
{
    Character* currentPlayer = turnManager->getCurrentPlayer();
    std::cout << "Ходит " << currentPlayer->getName() << std::endl;

    Card playedCard = currentPlayer->takeTurn();
    std::cout << currentPlayer->getName() << " сыграл карту " << playedCard.getName() << std::endl;

    Character* opponent = (turnManager->getCurrentPlayer() == turnManager->getCurrentPlayer())
        ? turnManager->getCurrentPlayer()
        : turnManager->getCurrentPlayer(); //chto eto
    opponent->ApplyCardEffect(playedCard);

    if (currentPlayer->needsCards())
    {
        currentPlayer->drawInitCards(deck);
    }

    turnManager->nextTurn();
}

bool PlayingState::isGameOver()
{
    koki 
}