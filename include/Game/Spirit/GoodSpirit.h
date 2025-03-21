#ifndef GOODSPIRIT_H
#define GOODSPIRIT_H
#include "Game/Spirit/Spirit.h"

class GoodSpirit : public Spirit 
{
public:
    GoodSpirit(Character* target);
    void applyEffect() override;
};

#endif