/**
 * @file EvilSpirit.cpp
 * @brief Implementation of class EvilSpirit methods.
*/

#include "Game/Spirit/EvilSpirit.h"
#include <iostream>
#include <Utilities/Console.h>

EvilSpirit::EvilSpirit(Character* target) : Spirit(target, 1) {}

/**
 * @details Deals 10 damage to the creator.
*/
void EvilSpirit::applyEffect()
{
    getTarget()->changeHealth(-10);
    Console::printSpiritEffect(*getTarget(), "Unluck! Evil spirit attacks " + getTarget()->getName());
}