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
    std::unique_ptr<GameState> currentState; 
    Deck& deck;
    std::vector<std::unique_ptr<Character>> players;
    int magicPool = 0;
    Character* currentPlayer;
    std::vector<std::unique_ptr<Spirit>> activeSpirits; 

public: 
    GameManager(Deck& d);
    ~GameManager() = default;

    void addPlayer(std::unique_ptr<Character> player);
    void setState(std::unique_ptr<GameState> state); // just to make transitions between states
    void run(); // set state to 'MainMenuState'

    const std::vector<std::unique_ptr<Character>>& getPlayers() const;
    Deck& getDeck();
    void clearPlayers();

    int getMagicPool() const;
    Character* getCurrentPlayer();
    void setCurrentPlayer(Character* player);

    void updateMagicPool(int effect);
    bool shouldAmplify() const;
    void resetMagicPool();
    void addSpirit(std::unique_ptr<Spirit> spirit);
    void processSpirits();
};

#endif