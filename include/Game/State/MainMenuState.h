#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include <iostream>

class MainMenuState : public GameState
{
    MainMenuState() = default;
    void enterState(GameManager& game) override; // override of virtual methods. sense of those are in the names. 
    void updateState(GameManager& game) override; // transition to 'SetupState' or leaving the game
    void exitState(GameManager& game) override;
};

#endif