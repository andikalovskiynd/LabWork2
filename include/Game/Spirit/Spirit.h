#ifndef SPIRIT_H
#define SPIRIT_H
#include "../../Players/Character.h" 

class Character;

class Spirit 
{
private:
    Character* target;
    int duration;

public:
    Spirit(Character* target);
    virtual ~Spirit();

    virtual void applyEffect();
    bool decreaseDuration();
    Character* getTarget();
    bool update();
};

#endif