#include "../include/Game.h"

Game::Game(Character* p, Character* b) : player(p), bot(b), magic(0) {}

void Game::playTurn (Character* currentPlayer)
{
    Card drawnCard = deck.drawCard();
    drawnCard = deck.checkForUpgrade(drawnCard);
    std::cout << currentPlayer->getName() << " играет карту: " << drawnCard.getName() << std::endl;
    currentPlayer->ApplyCardEffect(drawnCard, magic);
    if (magic >= 5)
    {
        std::cout << "Магия у " << currentPlayer->getName() << " достигла 5! Эффекты удвиваются" << std::endl;
        magic = 0;
    }
}