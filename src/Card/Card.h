#ifndef CARD_H
#define CARD_H
#include <string>

class Card 
{
private:
    std::string name;
    int baseHealthEffect;
    int baseRespectEffect;
    int baseMagicEffect;

public:
    Card(const std::string &n, int hEffect, int rEffect, int mEffect);
    ~Card() = default;
    const std::string& getName();
    int getHealthEffect() const;
    int getRespectEffect() const;
    int getMagicEffect() const;
};

#endif