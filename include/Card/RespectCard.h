#ifndef RESPECTCARD_H
#define RESPECTCARD_H

/**
 * @file RespectCard.h
 * @brief Header file which contains respect card. 
*/

#include "Card/Card.h"

class RespectCard : public Card
{
public:
    /**
     * @brief Class RespectCard constructor.
     * @param name Card name.
     * @param respectChange Card respect effect.
     * @param magicCost Card magic cost (magic effect).
    */
    RespectCard(const std::string& name, int respectChange, int magicCost) : Card(name, 0, respectChange, magicCost, Type::RESPECT) {}
};

#endif