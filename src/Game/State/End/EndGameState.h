#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "../src/Game/State/Gamestate.h"
#include "../src/Game/GameManager/GameManager.h"
#include "../src/Players/Character.h"

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