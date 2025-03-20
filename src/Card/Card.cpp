#include "Card/Card.h"

Card::Card(const std::string &n, int hEffect, int rEffect, int mEffect, Type t) : name(n), baseHealthEffect(hEffect), baseRespectEffect(rEffect), baseMagicEffect(mEffect), cardType(t) {}

Card::~Card() = default;

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

Card::Type Card::getType() const
{
    return cardType;
}