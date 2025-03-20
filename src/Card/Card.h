#ifndef CARD_H
#define CARD_H
#include <string>
#include "Players/Character.h"

class Card 
{
public: // to init 'Type'
    enum class Type 
    {
        ATTACK,
        HEAL,
        MAGIC,
        RESPECT
    };

private:
    std::string name;
    int baseHealthEffect;
    int baseRespectEffect;
    int baseMagicEffect;
    Type cardType;

public:
    Card(const std::string &n, int hEffect, int rEffect, int mEffect, Type type); // constructor
    ~Card(); // destructor 
    const std::string& getName(); // getter for card name
    int getHealthEffect() const; // getter for card health effect
    int getRespectEffect() const; // getter for card respect effect
    int getMagicEffect() const; // getter for card magic effect
    Type getType() const;
};

#endif