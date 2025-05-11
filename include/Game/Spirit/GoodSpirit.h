#ifndef GOODSPIRIT_H
#define GOODSPIRIT_H

/**
 * @file GoodSpirit.h 
 * @brief Good spirit declaration.
*/

#include "Game/Spirit/Spirit.h"

/// @brief Class that represents Good spirit and inherits from Spirit.
class GoodSpirit : public Spirit 
{
public:
    /**
     * @brief GoodSpirit constructor.
     * @param target Target which is going to be affected.
    */
    GoodSpirit(Character* target);

    /// Applying good spirit effect: healing the target.
    void applyEffect() override;
};

#endif