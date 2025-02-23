#ifndef BOT_H
#define BOT_H
#include <iostream>
#include "Character.h"

enum class Difficulty { EASY, MEDIUM, HARD };

class Bot : public Character
{
private:
    Difficulty difficulty;

public:
    Bot(const std::string &n, int h, int r, Difficulty diff);

    void MakeMove ();

    virtual void update() override;
};

#endif