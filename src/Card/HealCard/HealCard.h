#ifndef HEALCARD_H
#define HEALCARD_H
#include "Card/Card.h"

class HealCard : public Card
{
public:
    HealCard(const std::string& name, int heal, int magicCost) : Card(name, heal, 0, -magicCost, Type::HEAL) {}
};

#endif