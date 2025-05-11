#ifndef EVILSPIRIT_H
#define EVILSPIRIT_H

/**
 * @file EvilSpirit.h 
 * @brief Evil spirit declaration.
*/

#include "Game/Spirit/Spirit.h"

/// @brief Class that represents the Evil spirit and inherits from Spirit.
class EvilSpirit : public Spirit
{
public:
    /**
     * @brief EvilSpirit constructor.
     * @param target Target which is going to be affected. 
    */
    EvilSpirit(Character* target);

    /// @brief Applying evil spirit effect: dealing damage to target.
    void applyEffect() override;
};

#endif