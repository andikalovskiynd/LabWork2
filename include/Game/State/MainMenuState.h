#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

/**
 * @file MainMenuState.h 
 * @brief Declaration of MainMenuState class.
*/

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include <iostream>
#include <memory>

/// @brief Class MainMenuState which represents state in main menu in the game inherits from GameState.
class MainMenuState : public GameState
{
public:
    /**
     * @brief Default constructor of class MainMenuState object.
    */
    MainMenuState() = default;

    /**
     * @brief Override of enterState method: prints welcome messages. 
     * @param game May be unused here.
    */
    void enterState([[maybe_unused]]GameManager& game) override; 

    /**
     * @brief Override of updateState method: takes an input and decides continue or not. 
     * @param game May be unused here.
    */
    void updateState([[maybe_unused]]GameManager& game) override; 

    /**
     * @brief Exits main menu state. 
     * @param game May be unused here.
    */
    void exitState([[maybe_unused]]GameManager& game) override;
};

#endif