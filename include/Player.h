#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Character.h"

class Player : public Character
{
    Player(const std::string &n, int h, int r);
    void ChooseCard ();

    virtual void update() override;
};

#endif