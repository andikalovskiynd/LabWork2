#ifndef MAGICCARD_H
#define MAGICCARD_H
#include "Card/Card.h"

class MagicCard : public Card
{
public:
    MagicCard(const std::string& name, int magicChange) : Card(name, 0, 0, magicChange, Type::MAGIC) {}
};

#endif