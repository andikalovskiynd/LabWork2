#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file Player.h
 * @brief Header which contains Player class declaration.
*/

#include <iostream>
#include "Players/Character.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"
#include <memory>

/// @brief Class Player represents the human being playing the game and inherits from Character.
class Player : public Character
{
private:
    std::vector<std::unique_ptr<Card>> hand; //< Player's cards.
    bool quitRequested = false; //< Wish to leave the game.

public:

    /**
     * @brief Player constructor, creates an object of Player. 
     * @param n Name. 
     * @param h Health. 
     * @param r Respect. 
    */
    Player(const std::string &n, int h, int r);

    // interactions with cards
    /**
     * @brief Play a card. 
     * @param index Indexs of needed card in the hand vector. 
     * @return Unique pointer on the object of Card representing the needed card.
    */
    std::unique_ptr<Card> playCard(int index); 

    /**
     * @brief Draw a card from deck using method from class Deck. 
     * @param deck Deck is needed to take card from it. 
    */
    void drawCard(Deck& deck);
    
    /**
     * @brief Check if cards amount in player's hand is less 5.
     * @return True if there are less than 5 cards in the hand, false otherwise.
    */
    bool needsCards() override; 

    // interactions with hand
    /**
     * @brief Clear the hand vector. 
    */
    void clearHand();

    /**
     * @brief Get player's hand vector. 
     * @return Constant link on vector containing the unique pointers on Card objects representing player's hand. 
    */
    const std::vector<std::unique_ptr<Card>>& getHand() const override; 

    /**
     * @brief Gets index and checks it, then uses playCard().
     * @param game May be unused. 
     * @return Unique pointer on Card object representing the return from playCard().
    */
    std::unique_ptr<Card> takeTurn([[maybe_unused]]GameManager& game) override; // to take turn using playCard method and card's index in vector 'hand'
    
    /**
     * @brief Initialize the starting hand. 
     * @param deck Deck from where the cards will be drawn. 
    */
    virtual void drawInitCards(Deck& deck) override; 

    /**
     * @brief Check if players wants to quit. 
     * @return True, if quitRequested = true, false otherwise.
    */
    bool wantsToQuit() const override;
};

#endif