#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "Deck/Deck.h"
#include <memory>

class Card;
class GameManager;

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
    std::string getName() const; // getter for character name
    int getHealth() const; // getter for character health
    int getRespect() const; // getter for character respect
    virtual const std::vector<std::unique_ptr<Card>>& getHand() const = 0; //

    // condition 
    bool IsAlive () const; // check if character is alive
    void changeHealth(int amount); // increase or reduce health of character
    void changeRespect(int amount); // increase or reduce respect of character

    // else
    void ApplyCardEffect (const Card& card, GameManager& game); // apply card effect 
    virtual std::unique_ptr<Card> takeTurn(GameManager& game) = 0; // to take a turn. used just to inherit because ways of bot's and player's turns are slightly different
    virtual void drawInitCards(Deck& deck) = 0; // only to inherit
    virtual bool needsCards() = 0; // only to inherit
    virtual bool wantsToQuit() const { return false; }
};

#endif