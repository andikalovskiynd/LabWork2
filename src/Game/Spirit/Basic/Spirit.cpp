#include "Game/Spirit/Basic/Spirit.h"

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