#ifndef MAGICCARD_H
#define MAGICCARD_H

/**
 * @file MagicCard.h
 * @brief Header file which contains magic card.
*/

#include "Card/Card.h"

class MagicCard : public Card
{
public:
    /**
     * @brief Class MagicCard constructor.
     * @param name Card name. 
     * @param magicChange Card magic change (magic effect).
    */
    MagicCard(const std::string& name, int magicChange) : Card(name, 0, 0, magicChange, Type::MAGIC) {}
};

#endif