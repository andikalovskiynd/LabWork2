#ifndef BOT_H
#define BOT_H

/**
 * @file Bot.h 
 * @brief Header which contains Bot class declaration. 
*/

#include <iostream>
#include "Players/Character.h"
#include "Deck/Deck.h"
#include <memory>

/// @brief Enumeration of Bot's difficulty.
enum class Difficulty { EASY, MEDIUM, HARD };

/// @brief Bot is the class that represents the AI opponent, inherits from Character.
class Bot : public Character
{
private:
    std::vector<std::unique_ptr<Card>> hand; //< Bot hand with cards.
    Difficulty botDifficulty; //< Difficulty of bot.

public:
    /**
     * @brief Bot constructor, creates a bot object. 
     * @param n Name. 
     * @param h Health. 
     * @param r Respect. 
     * @param d Difficulty.
    */
    Bot(const std::string &n, int h, int r, Difficulty d);

    // interactions with cards
    /**
     * @brief Take card from the deck. 
     * @param deck Deck from where bot will take card.
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
     * @brief Get bot's hand vector. 
     * @return Constant link on vector containing the unique pointers on Card objects representing bot's hand. 
    */   
    const std::vector<std::unique_ptr<Card>>& getHand() const override; 

    /**
     * @brief Play a card. 
     * @param index Indexs of needed card in the hand vector. 
     * @return Unique pointer on the object of Card representing the needed card.
    */
    std::unique_ptr<Card> playCard(int index);

    /**
     * @brief Play card that is first in the hand vector. 
     * @return Unique pointer on the object of Card representing the first card.
    */
    std::unique_ptr<Card> makeStupidMove(); 

    /**
     * @brief AI is here!
     * @param game Used to analyze all game context. 
     * @return Unique pointer on the object of Card which has largest score. 
     * 
     * Bot analyzes all the situation: how much health has itself and player, magic and respect too. Then it chooses between 12 different states from critically defensive to critically agressive and then applies different score to the card, then chooses largest. 
    */
    std::unique_ptr<Card> takeTurn(GameManager& game) override;

    /**
     * @brief Initialize the starting hand. 
     * @param deck Deck from where the cards will be drawn. 
    */
    virtual void drawInitCards(Deck& deck) override;

    /**
     * @brief Bot has no mind so it never wants to quit.
     * @return Always false. 
    */
    bool wantsToQuit() const override;
};

#endif