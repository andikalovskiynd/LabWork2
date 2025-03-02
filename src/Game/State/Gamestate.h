#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState 
{
public: 
    virtual void enterState(GameManager& game) = 0; // only virtual states to make transitions between states easily to modify and inherit
    virtual void updateState(GameManager& game) = 0;
    virtual void exitState(GameManager& game) = 0;
    virtual ~GameState() = default;
};

#endif