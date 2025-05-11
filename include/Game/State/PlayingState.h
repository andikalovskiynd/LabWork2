#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

/**
 * @file PlayingState.h 
 * @brief Declaration of all methods used to manage the playing process.
*/

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/Turn/TurnManager.h"
#include "Game/State/EndGameState.h"
#include <iostream>
#include <memory>


/// @brief Playing state class that contains methods used to control the playing process. Inherits from GameState.
class PlayingState : public GameState
{
private:
    std::unique_ptr<TurnManager> turnManager; //< Object used to control everything related to turns.
    Deck& deck; //< Deck link.
    int counter; //< Counter of turns.

public:
    /**
     * @brief PlayingState constructor: initializes deck and counter = 0. 
     * @param game Used to get players.
    */
    PlayingState(GameManager& game);

    /**
     * @brief Default PlayingState destructor.
    */
    ~PlayingState() = default;


    /**
     * @brief Enters the playing state, makes counter = 1. 
     * @param game May be unused.
    */
    void enterState([[maybe_unused]]GameManager& game) override;

    /**
     * @brief Updates playing state to End Game. 
     * @param game used to get the players and set the winner. 
    */
    void updateState(GameManager& game) override;

    /**
     * @brief Prints that you left the playing state. 
     * @param game May be unused. 
    */
    void exitState([[maybe_unused]] GameManager& game) override;


    /**
     * @brief Processimg a turn using turn manager.
     * @param game Used to get players and control the current game state. 
    */
    void processTurn(GameManager& game);

    /**
     * @brief Checks how much players are alive
     * @param game Used to get players. 
     * @return True, if there is one or less alive players, false otherwise. 
    */
    bool isGameOver(GameManager& game) const; 
};


#endif