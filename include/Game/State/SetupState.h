#ifndef SETUPSTATE_H
#define SETUPSTATE_H

/**
 * @file SetupState.h 
 * @brief Prepares the ground for the game.
*/

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/PlayingState.h"
#include "Players/Character.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include <iostream>
#include <vector>

/// @brief Setupstate class prepares the ground for upcoming game: initializes players, hands etc. Inherits from GameState.
class SetupState : public GameState
{
private: 
    Deck& deck; //< Personal SetupState deck which is going to be tansferred to GameManager.

public:
    /**
     * @brief SetupState constructor - just SetupState object with deck.
     * @param deck Personal SetupState deck which is going to be tansferred to GameManager.
    */
    SetupState (Deck& deck);

    /**
     * @brief Shuffles deck, then, using initExample methods, initializes Players and Hands, then transition to PlayingState.
     * @param game Used to take GameManager deck and make new.
    */
    void enterState(GameManager& game) override;

    /**
     * @brief Empty method. 
     * @param game May be unused.
    */
    void updateState([[maybe_unused]] GameManager& game) override;

    /**
     * @brief Empty method. 
     * @param game May be unused.
    */
    void exitState([[maybe_unused]] GameManager& game) override;


    /**
     * @brief Makes a vector for players, then takes in choice of difficulty and initializes the bot.
     * @param game Used to transfer bot and player.
    */
    void initPlayers(GameManager& game); 

    /**
     * @brief Using already existing in Character methods, makes hands for player and bot.
     * @param game Used to get players from GameManager.
    */
    void initHands(GameManager& game);
};

#endif