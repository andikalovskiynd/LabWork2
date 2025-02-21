#include "../include/Character.h"

Character::Character(const std::string &n, int h, int r) : name(n), health(h), respect (r), magic (0) {}
void Character::ApplyCardEffect (const Card& card, int& globalMagic) 
{
    health += card.getHealthEffect();
    respect += card.getRespectEffect();
    magic += card.getMagicEffect();
    if (health <=0)
    {
        health = 0;
    }
}

bool Character::IsAlive () const 
{ 
    return health > 0;
}