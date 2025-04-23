#include "Players/Character.h"
#include "Game/Spirit/EvilSpirit.h"
#include "Game/Spirit/GoodSpirit.h"
#include "Game/Spirit/MagicWizard.h"
#include <iostream>

Character::Character(const std::string &n, int h, int r) : name(n), health(h), respect (r) {}

// getters
int Character::getHealth() const
{
    return health; 
}

int Character::getRespect() const
{
    return respect;
}

std::string Character::getName () const
{
    return name;
}

// condition
bool Character::IsAlive () const
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

    if(isAmplified)
    {
        h *= 2;
        r *= 2;
        game.resetMagicPool();
    }
    
    this->changeHealth(h);
    this->changeRespect(r);

    switch(card.getType())
    {
        case Card::Type::ATTACK:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(std::make_unique<EvilSpirit>(this));
            }
            break;
        }
        
        case Card::Type::HEAL:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(std::make_unique<GoodSpirit>(this));
            }
            break;
        }

        case Card::Type::MAGIC:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(std::make_unique<MagicWizard>(this, game));
            }
            break;
        }

        case Card::Type::RESPECT:
        {
            if(rand() % 100 < 2)
            {
                std::cout << "Над вами посмеялись бродяги.. Ничего не поменялось, но осадочек остался.." << std::endl;
            }
            break;
        }

        default: break;
    }
}