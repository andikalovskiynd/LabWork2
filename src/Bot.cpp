#include "../include/Bot.h"

Bot::Bot(const std::string &n, int h, int r, Difficulty diff) : Character(n, h, r), difficulty(diff) {}

void Bot::MakeMove ()
{
    std::cout << "Бот " << "(сложность: ";
    switch(difficulty)
    {
        case Difficulty::EASY: std::cout << "легкая"; break;
        case Difficulty::MEDIUM: std::cout << "средняя"; break;
        case Difficulty::HARD: std::cout << "сложная"; break;
    }
    std::cout << "), делает ход";
}

void  Bot::update()
{
    MakeMove();
}