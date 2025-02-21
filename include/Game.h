#ifndef GAME_H 
#define GAME_H
#include "Character.h"
#include "Deck.h"
#include <iostream>

class Game : public GameObject
{
private: 
    Character* player;
    Character* bot;
    Deck deck;
    int magic;

public:
    Game(Character* p, Character* b) : player(p), bot(b), magic(0) {}

    void playTurn (Character* currentPlayer)
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
};

#endif