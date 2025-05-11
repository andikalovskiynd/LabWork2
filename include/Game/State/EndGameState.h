#ifndef ENDSTATE_H
#define ENDSTATE_H

/**
 * @file EndGameState.h 
 * @brief Declaration of end game state. 
*/

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Character.h"
#include <memory>

/// @brief Class EndGameState provides opportunity to leave or start game again.
class EndGameState : public GameState
{
private:
    Character* winner; //< Current game winner. 

public:
    /**
     * @brief EndGameState constructor which contains winner. 
     * @param winner Current game winner. 
    */
    EndGameState(Character* winner);

    /// @brief EndGameState default destructor.
    ~EndGameState() = default;

    /**
     * @brief Prints winner. 
     * @param game May be unused.
    */
    virtual void enterState([[maybe_unused]]GameManager& game) override;

    /**
     * @brief Similar mechanic as main menu: decides to continue or not based on user's choice. 
     * @param game Used to set game states. 
    */
    virtual void updateState(GameManager& game) override;

    /**
     * @brief Print that game is over. 
     * @param game May be unused.
    */
    virtual void exitState([[maybe_unused]]GameManager& game) override;
};

#endif