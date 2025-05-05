#include "Players/Character.h"
#include "Game/Spirit/EvilSpirit.h"
#include "Game/Spirit/GoodSpirit.h"
#include "Game/Spirit/MagicWizard.h"
#include "Utilities/Console.h"

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
    
    Character* opponent = nullptr;
    const auto& allPlayers = game.getPlayers();
    for (const auto& playerPtr : allPlayers)
    {
        if (playerPtr.get() != this)
        {
            opponent = playerPtr.get();
            break;
        }
    }

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

    switch(card.getType())
    {
        case Card::Type::ATTACK:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(std::make_unique<EvilSpirit>(this));
            }
            opponent->changeHealth(-h);
            this->changeRespect(-r);
            game.updateMagicPool(-std::abs(m));
            break;
        }
        
        case Card::Type::HEAL:
        {
            if(rand() %  100 < 7)
            {
                game.addSpirit(std::make_unique<GoodSpirit>(this));
            }
            this->changeHealth(h);
            opponent->changeRespect(r);
            game.updateMagicPool(-std::abs(m));
            break;
        }

        case Card::Type::MAGIC:
        {
            if(rand() % 100 < 7)
            {
                game.addSpirit(std::make_unique<MagicWizard>(this, game));
            }
            game.updateMagicPool(m);
            this->changeHealth(-h);
            this->changeRespect(-r);
            break;
        }

        case Card::Type::RESPECT:
        {
            if(rand() % 100 < 7)
            {
                Console::print("Над вами посмеялись бродяги.. Ничего не поменялось, но осадочек остался..");
            }
            this->changeRespect(r);
            this->changeHealth(-h);
            game.updateMagicPool(-std::abs(m));
            break;
        }

        default: break;
    }
}