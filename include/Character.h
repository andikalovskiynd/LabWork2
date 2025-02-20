#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "GameObject.h"

class Character : public GameObject
{
protected:
    std::string name;
    int health;
    int respect;
    int magic;
public: 
    Character(const std::string &n, int h, int r) : name(n), health(h), respect (r), magic (0) {}
    virtual void ApplyCardEffect (int healthEffect, int respectEffect, int magicEffect) 
    {
        int multiplier = 1;
        if (magic == 5)
        {
            multiplier = 2;
            magic = 0;
        }
        health += healthEffect * multiplier;
        respect += respectEffect * multiplier;
        magic += magicEffect * multiplier;
    }
    virtual bool IsAlive () const 
    { 
        return health > 0;
    }

    void update() override {}

    virtual ~Character() = default;
};

#endif