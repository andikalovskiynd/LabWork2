#ifndef DECK_H
#define DECK_H

/**
 * @file Deck.h 
 * @brief Header file which contains deck. 
*/

#include <vector>
#include <random>
#include <memory>
#include "Card/Card.h" 

/**
 * @brief Class representing the playing deck. 
 * 
 * Deck has cards in it and different methods for interacting with other playing elements.
*/
class Deck
{
private:
    std::vector<std::unique_ptr<Card>> cards; //< Cards which deck contains.

public:
    /// @brief Class Deck constructor.
    Deck();

    /// @brief Class Deck destructor.
    ~Deck() = default;

    /**
     * @brief Randomly shuffles cards in the deck.
    */
    void shuffle();

    /**
     * @brief Taking one card from the deck. 
     * @return Unique pointer on object of class Card.
    */
    std::unique_ptr<Card> drawCard();

    /**
     * @brief Checking if the deck is empty.
     * @return True if 'cards' vector is empty, false otherwise.
    */
    bool isEmpty();

    /**
     * @brief Refills cards with new ones. 
     * @param newCards Vector of pointers on class Card objects representing new cards which is wanted to use for refilling. 
    */
    void resetDeck(std::vector<std::unique_ptr<Card>> newCards); 

    /**
     * @brief Get cards from the vector. 
     * @return Constant link on 'Card' pointers which are contained in 'cards' vector.
    */
    const std::vector<std::unique_ptr<Card>>& getCards() const;

    /**
     * @brief Adds card in the deck.
     * @param card Pointer on the 'Card' object which is wanted to be added.
    */
    void addCard(std::unique_ptr<Card> card);
};

#endif