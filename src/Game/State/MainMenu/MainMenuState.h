#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "../src/Game/State/Gamestate.h"
#include <iostream>

class MainMenuState : public GameState
{
    void enterState(GameManager& game) override; // override of virtual methods. sense of those are in the names. 
    void updateState(GameManager& game) override; // transition to 'SetupState' or leaving the game
    void exitState(GameManager& game) override;
};

#endif