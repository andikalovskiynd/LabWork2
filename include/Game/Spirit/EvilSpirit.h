#ifndef EVILSPIRIT_H
#define EVILSPIRIT_H
#include "Game/Spirit/Spirit.h"

class EvilSpirit : public Spirit
{
public:
    EvilSpirit(Character* target);
    void applyEffect() override;
};

#endif