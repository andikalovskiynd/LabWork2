#ifndef CARD_H
#define CARD_H
#include <string>
#include "Players/Character.h"

class Card 
{
private:
    std::string name;
    int baseHealthEffect;
    int baseRespectEffect;
    int baseMagicEffect;

public:
    Card(const std::string &n, int hEffect, int rEffect, int mEffect); // constructor
    ~Card(); // destructor 
    const std::string& getName(); // getter for card name
    int getHealthEffect() const; // getter for card health effect
    int getRespectEffect() const; // getter for card respect effect
    int getMagicEffect() const; // getter for card magic effect
};

#endif