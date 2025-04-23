#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "Game/State/Gamestate.h"
#include "Game/GameManager/GameManager.h"
#include "Players/Character.h"
#include <memory>

class EndGameState : public GameState
{
private:
    Character* winner;

public:
    EndGameState(Character* winner);
    ~EndGameState() = default;
    virtual void enterState(GameManager& game) override;
    virtual void updateState(GameManager& game) override;
    virtual void exitState(GameManager& game) override;
};

#endif