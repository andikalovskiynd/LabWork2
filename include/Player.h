#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Character.h"

class Player : public Character
{
public:
    Player(const std::string &n, int h, int r) : Character(n, h, r) {};
    void ChooseCard ();

    virtual void update() override;
};

#endif