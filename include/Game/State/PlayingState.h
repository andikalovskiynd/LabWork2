#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/Turn/TurnManager.h"
#include "Game/State/EndGameState.h"
#include <iostream>
#include <memory>

class PlayingState : public GameState
{
private:
    std::unique_ptr<TurnManager> turnManager;
    Deck& deck;
    int counter;

public:
    PlayingState(GameManager& game);
    ~PlayingState() = default;

    void enterState(GameManager& game) override;
    void updateState([[maybe_unused]] GameManager& game) override; // with 'isGameOver' checks if there is need to get to the 'EndGameState'
    void exitState([[maybe_unused]] GameManager& game) override;

    void processTurn(GameManager& game); // processing a turn using turn manager 
    bool isGameOver(GameManager& game) const; // check if at least one of the players is dead
};


#endif