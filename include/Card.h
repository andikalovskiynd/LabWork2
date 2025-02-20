#ifndef CARD_H
#define CARD_H

#include <string>
#include "Character.h"

class Card 
{
protected:
    std::string name;
    int level;
    int baseHealthEffect;
    int baseRespectEffect;
    int baseMagicEffect;

public:
    Card(const std::string &n, int lvl, int hEffect, int rEffect, int mEffect) : name(n), level(lvl), baseHealthEffect(hEffect), baseRespectEffect(rEffect), baseMagicEffect(mEffect) {}

    virtual void applyEffect(Character &user, Character &opponent) const 
    {
        user.ApplyCardEffect(baseHealthEffect * level, baseRespectEffect * level, baseMagicEffect * level);
    }

    const std::string& getName() const {return name;}
    virtual ~Card() = default;
};

#endif