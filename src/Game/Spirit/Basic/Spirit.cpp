#include "Game/Spirit/Spirit.h"

Spirit::Spirit(Character* t, int d) : target(t), duration(d) {}

void Spirit::applyEffect() {}

Character* Spirit::getTarget()
{
    return target;
}

bool Spirit::update()
{
    --duration;
    return duration > 0;
}