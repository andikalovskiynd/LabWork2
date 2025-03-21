#ifndef MAGICWIZARD_H
#define MAGICWIZARD_H
#include "Game/Spirit/Spirit.h"
#include "Game/GameManager/GameManager.h"

class MagicWizard : public Spirit 
{
private:
    GameManager& game;

public:
    MagicWizard(Character* target, GameManager& game);
    void applyEffect() override;
};

#endif