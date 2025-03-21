#include "Game/Spirit/GoodSpirit.h"
#include <iostream>

GoodSpirit::GoodSpirit(Character* target) : Spirit(target) {}

void GoodSpirit::applyEffect()
{
    getTarget()->changeHealth(10);
    std::cout << "Удача! " << getTarget()->getName() << " повезло! Исцеляющий дух пришел на помощь!" << std::endl;
}