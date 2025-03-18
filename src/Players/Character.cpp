#include "Players/Character.h"

Character::Character(const std::string &n, int h, int r) : name(n), health(h), respect (r) {}

// getters
int Character::getHealth() 
{
    return health; 
}

int Character::getRespect() 
{
    return respect;
}

std::string Character::getName () 
{
    return name;
}

// condition
bool Character::IsAlive ()
{
    return health > 0;
}

void Character::changeHealth(int amount)
{
    health += amount;
}
void Character::changeRespect(int amount)
{
    respect += amount;
}

// else 
void Character::ApplyCardEffect (const Card& card, GameManager& game)
{
    game.setCurrentPlayer(this);
    game.updateMagicPool(card.getMagicEffect());
    
    bool isAmplified = game.shouldAmplify();
    int h = card.getHealthEffect();
    int r = card.getRespectEffect();
    int m = card.getMagicEffect();

    if(isAmplified)
    {
        h *= 2;
        r *= 2;
        m *= 2;
        game.resetMagicPool();
    }

    this->changeHealth(h);
    this->changeRespect(r);
    game.updateMagicPool(m);
}