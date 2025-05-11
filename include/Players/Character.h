#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * @file Character.h 
 * @brief Header for Character class. 
*/

#include <string>
#include "Deck/Deck.h"
#include <memory>

/// @brief Card forward declaration used to avoid conflicts with circular include.
class Card;

/// @brief GameManager forward declaration used to avoid conflicts with circular include.
class GameManager;

/// @brief Character class is basic class for game participant (AI or human).
class Character
{
private:
    std::string name; //< Name of participant.
    int health; //< Health of participant.
    int respect; //< Respect of participant.

public: 

    /**
     * @brief Character constructor which creates an object of Character. 
     * @param n Name. 
     * @param h Health. 
     * @param r Respect. 
    */
    Character(const std::string &n, int h, int r);

    /**
     * @brief Virtual default Character destructor.
    */
    virtual ~Character() = default;

    // getters
    /**
     * @brief Get name. 
     * @return String which represents name of the character.
    */
    std::string getName() const;

    /**
     * @brief Get health. 
     * @return Integer which represents the health of the character.
    */
    int getHealth() const; 

    /**
     * @brief Get respect.
     * @return Integer which represents the respect of the character.
    */
    int getRespect() const; 

    /**
     * @brief Virtual method that will allow to get character's hand. 
     * @return Constant link on the vector containing the unique pointers on Card objects which represents the Character's hand.
    */
    virtual const std::vector<std::unique_ptr<Card>>& getHand() const = 0; //

    // condition 
    /**
     * @brief Check if character is alive. 
     * @return True, if character is alive, false otherwise.
    */
    bool IsAlive () const;

    /**
     * @brief Increase or decrease character's health by amount. 
     * @param amount Quantity of health that is going to be changed.
    */
    void changeHealth(int amount); 

    /**
     * @brief Increase or decraese character's respect by amount. 
     * @param amount Quantity of respect that is going to be changed.
    */
    void changeRespect(int amount); 

    // else
    /**
     * @brief Applies card effect. Getting basic effects, checking if it should be amplified and then use changeHealth/Respect.
     * @param card Played card with effects that are going to be applied. 
     * @param game Used to get and set players. 
    */
    void ApplyCardEffect (const Card& card, GameManager& game);

    /**
     * @brief Virtual method used to make game more abstract. Ways of taking turn of bot and player are significantly different.
     * @param game Used later. 
    */
    virtual std::unique_ptr<Card> takeTurn(GameManager& game) = 0; // to take a turn. used just to inherit because ways of bot's and player's turns are slightly different
    
    /**
     * @brief Virtual method drawing cards to character from the deck. 
     * @param deck Deck.
    */
    virtual void drawInitCards(Deck& deck) = 0;

    /**
     * @brief Check if cards amount in character's hand is < 5.
    */
    virtual bool needsCards() = 0;

    /**
     * @brief Virtual method only for character checking if he wants to leave.
     * @return Always false here.
    */
    virtual bool wantsToQuit() const { return false; }
};

#endif