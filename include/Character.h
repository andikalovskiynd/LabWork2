#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "GameObject.h"
#include "Card.h"

class Character : public GameObject
{
protected:
    std::string name;
    int health;
    int respect;
    int magic;

public: 
    Character(const std::string &n, int h, int r) : name(n), health(h), respect (r), magic (0) {}
    void ApplyCardEffect (const Card& card, int& globalMagic) 
    {
        health += card.getHealthEffect();
        respect += card.getRespectEffect();
        magic += card.getMagicEffect();
        if (health <=0)
        {
            health = 0; // add death 
        }
    }
    virtual bool IsAlive () const 
    { 
        return health > 0;
    }

    void update() override = 0;

    virtual ~Character() = default;
};

#endif