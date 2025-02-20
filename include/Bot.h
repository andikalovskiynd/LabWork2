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
    Bot(const std::string &n, int h, int r, Difficulty diff) : Character(n, h, r), difficulty(diff) {}

    void MakeMove ()
    {
        std::cout << "Бот " << name << "(сложность: ";
        switch(difficulty)
        {
            case Difficulty::EASY: std::cout << "легкая"; break;
            case Difficulty::MEDIUM: std::cout << "средняя"; break;
            case Difficulty::HARD: std::cout << "сложная"; break;
        }
        std::cout << "), делает ход";
    }

    virtual void update() override
    {
        MakeMove();
    }
};

#endif