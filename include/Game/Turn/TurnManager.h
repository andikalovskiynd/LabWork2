#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#include <vector>
#include "Players/Character.h"

class TurnManager 
{
private:
    const std::vector<std::unique_ptr<Character>>& players;
    int currentPlayerIndex;

public:
    TurnManager(const std::vector<std::unique_ptr<Character>>& playerList);
    void nextTurn(); // makes currentPlayerIndex more so it is basicaly just change of focus from one participant to another
    Character* getCurrentPlayer(); // returns current player
    bool isGameOver(); // for all players checks if they're alive
    void reset();
};

#endif