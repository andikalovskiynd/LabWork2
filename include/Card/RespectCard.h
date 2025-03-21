#ifndef RESPECTCARD_H
#define RESPECTCARD_H
#include "Card/Card.h"

class RespectCard : public Card
{
public:
    RespectCard(const std::string& name, int respectChange, int magicCost) : Card(name, 0, respectChange, -magicCost, Type::RESPECT) {}
};

#endif