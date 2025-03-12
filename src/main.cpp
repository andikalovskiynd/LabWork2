#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include "Game/State/MainMenu/MainMenuState.h"
#include <iostream>

int main()
{
    Deck deck;
    GameManager game(deck);
    game.setState(new MainMenuState());
    game.run();
    return 0;
}