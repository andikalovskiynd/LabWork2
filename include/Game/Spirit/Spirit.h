#ifndef SPIRIT_H
#define SPIRIT_H
#include <memory>
#include "../../Players/Character.h" 

class Character;

class Spirit 
{
private:
    Character* target;
    int duration;

public:
    Spirit(Character* target, int duration);
    virtual ~Spirit() = default;

    virtual void applyEffect() = 0;
    bool decreaseDuration();
    Character* getTarget();
    bool update();
};

#endif