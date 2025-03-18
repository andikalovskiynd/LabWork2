#ifndef EVILSPIRIT_H
#define EVILSPIRIT_H
#include "Game/Spirit/Basic/Spirit.h"

class EvilSpirit : public Spirit
{
    EvilSpirit(Character* target);
    void applyEffect() override;
};

#endif