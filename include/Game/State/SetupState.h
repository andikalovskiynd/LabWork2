#ifndef SETUPSTATE_H
#define SETUPSTATE_H

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/PlayingState.h"
#include "Players/Character.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include <iostream>
#include <vector>

class SetupState : public GameState
{
private: 
    Deck& deck;

public:
    SetupState (Deck& deck);
    void enterState(GameManager& game) override; // shuffles deck, then, using initExample methods, initializes Players and Hands, then transition to PlayingState
    void updateState([[maybe_unused]] GameManager& game) override;
    void exitState([[maybe_unused]] GameManager& game) override;

    void initPlayers(GameManager& game); // makes a vector for players, then takes in choice of difficulty and initializes the bot
    void initHands(GameManager& game); // using 'drawInitCards' makes hands for player and bot
};

#endif