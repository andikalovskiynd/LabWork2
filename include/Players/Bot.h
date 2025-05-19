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

/**
 * @brief Enumeration of different states of hard bot.
*/
enum class BotState 
{
    Normal, // обычное состояние
    CriticallyDefensive, // критически мало здоровья у бота
    Defensive, // просто мало здоровья у бота
    CriticallyAggressive, // критически мало здоровья у противника
    Aggressive, // просто мало здоровья у противника
    MagicCrisis, // критически много магии у противника
    MagicAdvantageOpponent, // просто много магии у противника
    MagicAdvantageBot, // магия в пользу бота (для усиления)
    RespectCrisisBot, // критически мало уважения у бота
    RespectCrisisOpponent, // критически много уважения у противника
    RespectFocus, // фокус на уважении (менее срочно)
    Default // на всякий
};

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
     * @brief Getting the best card from hand. 
     * @details Using chooseState to analyze current situation in the game, then applies different score to the card, then chooses largest. 
     * @param game Used to analyze all game context. 
     * @return Unique pointer on the object of Card which has largest score. 
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

    /**
     * @brief Chooses current bot state relying on the current game situation. 
     * @param game Used to analyze game situation. 
     * @return Chosen state of Bot (BotState).
     */
    BotState chooseState(GameManager& game);

    const Difficulty getDifficulty() const;

    /**
     * @brief Sets bot's hand for test purposes.
     * @details This method available ONLY if TEST_BUILD used.
     * @param cards Vector of unique pointers on class Cards objects which will be set in bot's hand.
    */
    void setHand(std::vector<std::unique_ptr<Card>> cards);
};

#endif