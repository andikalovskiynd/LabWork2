#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Game/State/Gamestate.h"
#include "Deck/Deck.h"
#include "Players/Character.h"
#include "Game/Spirit/Spirit.h"
#include <vector>

class GameManager
{
private:
    GameState* currentState; 
    Deck& deck;
    std::vector<Character*> players;
    int magicPool = 0;
    Character* currentPlayer;
    std::vector<Spirit*> activeSpirits; 

public: 
    GameManager(Deck& d);
    ~GameManager();

    void setState(GameState* state); // just to make transitions between states
    void run(); // set state to 'MainMenuState'
    std::vector<Character*> getPlayers();
    Deck& getDeck();
    void clearPlayers();
    int getMagicPool();
    Character* getCurrentPlayer();
    void setCurrentPlayer(Character* player);
    void updateMagicPool(int effect);
    bool shouldAmplify();
    void resetMagicPool();
    void addSpirit(Spirit* spirit);
    void processSpirits();
};

#endif