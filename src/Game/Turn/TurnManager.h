#ifndef TURNMANAGER_H
#define TURNMANAGER_H
#include <vector>
#include "../src/Players/Character.h"

class TurnManager 
{
private:
    std::vector<Character*> players;
    int currentPlayerIndex;

public:
    TurnManager(const std::vector<Character*>& playerList);
    void startTurns(); // uses 'takeTurn' method and 'isAlive' method and 'nextTurn' (from here) to make a queue of continious turns
    void nextTurn(); // makes currentPlayerIndex more so it is basicaly just change of focus from one participant to another
    Character* getCurrentPlayer(); // returns current player
    bool isGameOver(); // for all players checks if they're alive
};

#endif