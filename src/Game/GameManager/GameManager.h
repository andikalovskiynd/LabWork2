#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Game/State/Gamestate.h"
#include "Deck/Deck.h"
#include "Players/Character.h"

class GameManager
{
private:
    GameState* currentState; 
    Deck& deck;
    std::vector<Character*> players;

public: 
    GameManager(Deck& d);
    ~GameManager();

    void setState(GameState* state); // just to make transitions between states
    void run(); // set state to 'MainMenuState'
    std::vector<Character*> getPlayers();
    Deck& getDeck();
    void clearPlayers();
};

#endif