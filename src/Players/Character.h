#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "../src/Card/Card.h"

class Character
{
private:
    std::string name;
    int health;
    int respect;

public: 
    Character(const std::string &n, int h, int r);
    ~Character() = default;
    // getters
    std::string getName ();
    int getHealth();
    int getRespect();

    // condition 
    bool IsAlive ();
    void changeHealth(int amount);
    void changeRespect(int amount);

    // else
    void ApplyCardEffect (const Card& card);
};

#endif