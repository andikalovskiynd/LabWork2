#ifndef TURNMANAGER_H
#define TURNMANAGER_H

/**
 * @file TurnManager.h 
 * @brief Manages turns and everything that is related to it.
*/

#include <vector>
#include "Players/Character.h"

/// @brief Class TurnManager provides flex manager of turns, current players etc. 
class TurnManager 
{
private:
    const std::vector<std::unique_ptr<Character>>& players; //< Current players.
    int currentPlayerIndex; //< Index of current player in vector containing players.

public:
    /**
     * @brief TurnManager constructor which creates an object with players and current player index. 
     * @param playerList List of all players. 
    */
    TurnManager(const std::vector<std::unique_ptr<Character>>& playerList);

    /**
     * @brief Increases currentPlayerIndex by 1 so it is basicaly just change of focus from one participant to another.
    */
    void nextTurn(); 

    /**
     * @brief Gets current player. 
     * @return Pointer on class Character object which represents the current player. 
    */
    Character* getCurrentPlayer();

    /**
     * @brief Checks if game should be over. 
     * @return True, if there is 1 or less alive players, false otherwise.
    */
    bool isGameOver();
};

#endif