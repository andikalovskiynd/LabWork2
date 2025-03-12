#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/Turn/TurnManager.h"
#include "Game/State/End/EndGameState.h"
#include <iostream>

class PlayingState : public GameState
{
private:
    TurnManager* turnManager;
    Deck& deck;

public:
    PlayingState(std::vector<Character*>& players, Deck& deck);
    ~PlayingState();

    void enterState(GameManager& game) override;
    void updateState(GameManager& game) override; // with 'isGameOver' checks if there is need to get to the 'EndGameState'
    void exitState(GameManager& game) override;

    void processTurn(GameManager& game); // processing a turn using turn manager 
    bool isGameOver(); // check if at least one of the players is dead
};


#endif