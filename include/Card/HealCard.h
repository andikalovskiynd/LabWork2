#ifndef HEALCARD_H
#define HEALCARD_H

/**
 * @file HealCard.h 
 * @brief Header file which contains healing card.
*/

#include "Card/Card.h"

class HealCard : public Card
{
public:
    /**
     * @brief Class HealCard constructor.
     * @param name Card name.
     * @param heal Card heal (health effect).
     * @param magicCost Card magic cost (magic effect). 
    */
    HealCard(const std::string& name, int heal, int magicCost) : Card(name, heal, 0, magicCost, Type::HEAL) {}
};

#endif