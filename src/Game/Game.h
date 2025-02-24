#ifndef GAME_H 
#define GAME_H
#include "Character.h"
#include "Deck.h"
#include <iostream>

class Game
{
private: 
    Character* player;
    Character* bot;
    Deck deck;
    int magic;

public:
    Game(Player* p, Bot* b);
    void playTurn (Character* currentPlayer);
    void startGame();
    int getMagic() const { return magic; }
};

#endif