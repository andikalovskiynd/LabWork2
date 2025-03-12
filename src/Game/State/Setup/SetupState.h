#ifndef SETUPSTATE_H
#define SETUPSTATE_H

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/Playing/PlayingState.h"
#include "Players/Character.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include <iostream>
#include <vector>

class SetupState : public GameState
{
private: 
    Deck& deck;
    std::vector<Character*> players;

public:
    SetupState (Deck& deck, std::vector<Character*> players);
    void enterState(GameManager& game) override; // shuffles deck, then, using initExample methods, initializes Players and Hands, then transition to PlayingState
    void updateState(GameManager& game) override;
    void exitState(GameManager& game) override;

    void initPlayers(); // makes a vector for players, then takes in choice of difficulty and initializes the bot
    void initHands(); // using 'drawInitCards' makes hands for player and bot
};

#endif