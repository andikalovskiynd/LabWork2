#ifndef CARD_H
#define CARD_H
#include <string>
#include "GameObject.h"

class Card 
{
protected:
    std::string name;
    int baseHealthEffect;
    int baseRespectEffect;
    int baseMagicEffect;

public:
    Card(const std::string &n, int hEffect, int rEffect, int mEffect) : name(n), baseHealthEffect(hEffect), baseRespectEffect(rEffect), baseMagicEffect(mEffect) {}

    virtual ~Card() = default;
    const std::string& getName() const {return name;}
    int getHealthEffect() const {return baseHealthEffect;}
    int getRespectEffect() const {return baseRespectEffect;}
    int getMagicEffect() const {return baseMagicEffect;}

    virtual void update() {}
};

#endif