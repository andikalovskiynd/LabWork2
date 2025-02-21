#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "GameObject.h"
#include "Card.h"

class Character : public GameObject
{
private:
    std::string name;
    int health;
    int respect;
    int magic;

public: 
    Character(const std::string &n, int h, int r);
    void ApplyCardEffect (const Card& card, int& globalMagic);
    virtual bool IsAlive () const;

    void update() override = 0;
    virtual ~Character() = default;
    std::string getName () const { return name; }
    int getHealth() const { return health; }
    int getRespect() const { return respect; }
};

#endif