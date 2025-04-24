#include "Game/Spirit/GoodSpirit.h"
#include <iostream>
#include "Utilities/Console.h"

GoodSpirit::GoodSpirit(Character* target) : Spirit(target, 1) {}

void GoodSpirit::applyEffect()
{
    getTarget()->changeHealth(10);
    Console::printSpiritEffect(*getTarget(), "Удача! " + getTarget()->getName() + " повезло! Исцеляющий дух пришел на помощь!");
}