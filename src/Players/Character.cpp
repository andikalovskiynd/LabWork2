#include "Players/Character.h"
#include "Game/Spirit/Evil/EvilSpirit.h"
#include "Game/Spirit/Good/GoodSpirit.h"
#include "Game/Spirit/Wizard/MagicWizard.h"
#include <iostream>

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

    switch(card.getType())
    {
        case Card::Type::ATTACK:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(new EvilSpirit(this));
            }
            break;
        }
        
        case Card::Type::HEAL:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(new GoodSpirit(this));
            }
            break;
        }

        case Card::Type::MAGIC:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(new MagicWizard(this, game));
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