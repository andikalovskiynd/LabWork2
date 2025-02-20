#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Character.h"

class Player : public Character
{
    Player(const std::string &n, int h, int r) : Character(n, h, r) {}
    void ChooseCard () 
    {
        std::cout << "Игрок " << name << "выбирает карту ";
    }

    virtual void update() override 
    {
        ChooseCard();
    }
};

#endif