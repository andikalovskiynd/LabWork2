#ifndef ATTACKCARD_H
#define ATTACKCARD_H
#include "Card/Card.h"

class AttackCard : public Card
{
public:
    /**
     * @brief Class AttackCard constructor.
     * @param n Card name.
     * @param d Card damage (health effect).
     * @param m Card magic effect.
    */
    AttackCard(const std::string& n, int d, int m) : Card(n, d, 0, m, Type::ATTACK) {}
};

#endif