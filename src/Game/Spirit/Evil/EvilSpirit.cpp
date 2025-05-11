#include "Game/Spirit/EvilSpirit.h"
#include <iostream>
#include <Utilities/Console.h>

EvilSpirit::EvilSpirit(Character* target) : Spirit(target, 1) {}

void EvilSpirit::applyEffect()
{
    getTarget()->changeHealth(-10);
    Console::printSpiritEffect(*getTarget(), "Unluck! Evil spirit attacks " + getTarget()->getName());
}