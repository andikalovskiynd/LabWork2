#include "Game/Spirit/Spirit.h"

Spirit::Spirit(Character* t) : target(t) {}
Spirit::~Spirit() = default;

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