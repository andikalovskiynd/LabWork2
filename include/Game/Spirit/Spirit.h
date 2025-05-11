#ifndef SPIRIT_H
#define SPIRIT_H

/**
 * @file Spirit.h 
 * @brief Spirit basic class declaration. 
*/

#include <memory>
#include "../../Players/Character.h" 

/// @brief Class that repesents spirit.
class Spirit 
{
private:
    Character* target; //< Target of spirit actions.
    int duration; //< Amount of turns which is used as a lifetime of spirit.

public:
    /**
     * @brief Spirit class constructor. 
     * @param target Target. 
     * @param duration Spirit lifetime in the turns quantity. 
    */
    Spirit(Character* target, int duration);

    /**
     * @brief Virtual destructor of class Spirit.
    */
    virtual ~Spirit() = default;

    /**
     * @brief Virtual method that applies spirit effect.
    */
    virtual void applyEffect() = 0;

    /**
     * @brief Get target of the spirit. 
     * @return Pointer on class Character object which represents the target of spirit.
    */
    Character* getTarget();

    /**
     * @brief Decrease duration and check if spirit is alive.
     * @return True, if duration > 0, false otherwise. 
    */
    bool update();
};

#endif