#include "Card.h"

Card::Card(const std::string &n, int hEffect, int rEffect, int mEffect) : name(n), baseHealthEffect(hEffect), baseRespectEffect(rEffect), baseMagicEffect(mEffect) {}

const std::string& Card::getName()
{
    return name;
}

int Card::getHealthEffect() const
{
    return baseHealthEffect;
}

int Card::getRespectEffect() const
{
    return baseRespectEffect;
}

int Card::getMagicEffect() const
{
    return baseMagicEffect;
}