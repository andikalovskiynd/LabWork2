#include "../include/Player.h"

Player::Player(const std::string &n, int h, int r) : Character(n, h, r) {}
void Player::ChooseCard () 
{
    std::cout << "Игрок " << "выбирает карту " << std::endl;
}

void Player::update() 
{
    ChooseCard();
}