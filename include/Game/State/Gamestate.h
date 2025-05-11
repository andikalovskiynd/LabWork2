#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @file Gamestate.h 
 * @brief Basic game state declaration. 
*/

class GameManager;

/// @brief Class that represents the virtual game state.
class GameState 
{
public: 
    /**
     * @brief Virtual method that enters state. 
     * @param game Link on the game.
    */
    virtual void enterState(GameManager& game) = 0;

    /**
     * @brief Virtual method that updates state. 
     * @param game Link on the game.
    */
    virtual void updateState(GameManager& game) = 0;

    /**
     * @brief Virtual method that exits state. 
     * @param game Link on the game.
    */
    virtual void exitState(GameManager& game) = 0;

    /**
     * @brief GameState destructor.
    */
    virtual ~GameState() = default;
};

#endif