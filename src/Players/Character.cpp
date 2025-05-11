/**
 * @file Character.cpp 
 * @brief Implementation of class Character methods. 
*/

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
/**
 * @details Here the spirit is being created. Important because respect plays a huge part here. Difference between players and personal respect 
 * directly depend on chance of spirit appearance. 
*/
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

    int respectRatio = std::abs(this->getRespect() - opponent->getRespect());
    
    switch(card.getType())
    {
        case Card::Type::ATTACK:
        {
            int chance = 11 - this->getRespect() / respectRatio;
            if (chance < 5) chance = 6;
            if (chance < 0) chance = 1;
            if(rand() % 100 < chance)
            {
                game.addSpirit(std::make_unique<EvilSpirit>(this));
            }
            opponent->changeHealth(-h);
            this->changeRespect(-r);
            game.updateMagicPool(-m);
            break;
        }
        
        case Card::Type::HEAL:
        {
            int chance = 9 + this->getRespect() / respectRatio;
            if (chance > 21) chance = 21;
            if(rand() % 100 < chance)
            {
                game.addSpirit(std::make_unique<GoodSpirit>(this));
            }
            this->changeHealth(h);
            this->changeRespect(-r);
            game.updateMagicPool(-m);
            break;
        }

        case Card::Type::MAGIC:
        {
            int chance = 11 - this->getRespect() / respectRatio;
            if (chance < 5) chance = 6;
            if (chance < 0) chance = 1;
            if(rand() % 100 < chance)
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
            int chance = 12 - this->getRespect() / respectRatio;
            if (chance < 5) chance = 6;
            if (chance < 0) chance = 1;
            if(rand() % 100 < chance)
            {
                Console::print("Vagabonds.. Their laughter will be imprinted in your mind.. ");
            }
            this->changeRespect(r);
            this->changeHealth(-h);
            game.updateMagicPool(-m);
            break;
        }

        default: break;
    }
}