/**
 * @file GoodSpirit.cpp
 * @brief Implementation of class GoodSpirit methods.
*/

#include "Game/Spirit/GoodSpirit.h"
#include <iostream>
#include "Utilities/Console.h"

GoodSpirit::GoodSpirit(Character* target) : Spirit(target, 1) {}

/**
 * @details Adds 10 health to creator.
*/
void GoodSpirit::applyEffect()
{
    getTarget()->changeHealth(10);
    Console::printSpiritEffect(*getTarget(), "Wow! " + getTarget()->getName() + " is lucky! Healing spirit is here!");
}