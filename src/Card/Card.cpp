#include "Card/Card.h"

Card::Card(const std::string &n, int hEffect, int rEffect, int mEffect, Type t) : name(n), baseHealthEffect(hEffect), baseRespectEffect(rEffect), baseMagicEffect(mEffect), cardType(t) {}

const std::string& Card::getName() const
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

bool Card::operator==(const Card& another) const
{
    return name == another.getName();
}