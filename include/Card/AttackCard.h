#ifndef ATTACKCARD_H
#define ATTACKCARD_H
#include "Card/Card.h"

class AttackCard : public Card
{
public: // public bc we have separate file only with cards
    AttackCard(const std::string& n, int d, int m) : Card(n, d, 0, m, Type::ATTACK) {}
};

#endif