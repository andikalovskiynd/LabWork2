#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/MainMenuState.h"
#include <iostream>

int main()
{
    Deck deck;
    GameManager game(deck);
    game.setState(std::make_unique<MainMenuState>());
    game.run();
    return 0;
}