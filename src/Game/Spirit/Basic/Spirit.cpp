#include "Game/Spirit/Spirit.h"

Spirit::Spirit(Character* t, int d) : target(t), duration(d) {}

void Spirit::applyEffect() {}

bool Spirit::decreaseDuration()
{
    return --duration > 0;
}

Character* Spirit::getTarget()
{
    return target;
}

bool Spirit::update()
{
    --duration;
    return duration > 0;
}