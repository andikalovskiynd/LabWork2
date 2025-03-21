#include "Game/Spirit/EvilSpirit.h"
#include <iostream>

EvilSpirit::EvilSpirit(Character* target) : Spirit(target) {}

void EvilSpirit::applyEffect()
{
    getTarget()->changeHealth(-10);
    std::cout << "Неудача! Злой дух решил атаковать " << getTarget()->getName() << std::endl;
}