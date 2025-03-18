#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Card/Card.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"

class Character
{
private:
    std::string name;
    int health;
    int respect;

public: 
    Character(const std::string &n, int h, int r); // constructor
    virtual ~Character() = default; // destructor
    // getters
    std::string getName (); // getter for character name
    int getHealth(); // getter for character health
    int getRespect(); // getter for character respect

    // condition 
    bool IsAlive (); // check if character is alive
    void changeHealth(int amount); // increase or reduce health of character
    void changeRespect(int amount); // increase or reduce respect of character

    // else
    void ApplyCardEffect (const Card& card, GameManager& game); // apply card effect 
    virtual Card takeTurn() = 0; // to take a turn. used just to inherit because ways of bot's and player's turns are slightly different
    virtual void drawInitCards(Deck& deck) = 0; // only to inherit
    virtual bool needsCards() = 0; // only to inherit
};

#endif