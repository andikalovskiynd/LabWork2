#ifndef CARD_H
#define CARD_H

/**
 * @file Card.h
 * @brief Header file which contains card and all of its characteristics. 
*/

#include <string>

/**
 * @brief Class that represents playing card.
 * 
 * Every card has it's own name, atribute effects and type.
*/
class Card 
{
public:
    /// @brief Enumeration of cards types.
    enum class Type 
    {
        ATTACK, //< Attacking card, deals damage to opponent.
        HEAL, //< Healing card, heals tone who played it.
        MAGIC, //< Magic card, overflows magic to benefit of one who played it.
        RESPECT //< Respect card, adds respect to one who played it.
    };

private:
    std::string name; //< Card name.
    int baseHealthEffect; //< Basic health effect, may be boosted.
    int baseRespectEffect; //< Basic respect effect, may be boosted.
    int baseMagicEffect; //< Basic magic effect, may be boosted
    Type cardType; //< Card type.

public:
    /**
     * @brief Class Card constructor.
     * @param n Card name.
     * @param hEffect Basic health effect.
     * @param rEffect Basic respect effect.
     * @param mEffect Basic magic effect.
     * @param type Card type.
     */
    Card(const std::string &n, int hEffect, int rEffect, int mEffect, Type type);

    /// @brief Card destructor.
    ~Card() = default;

    /**
     * @brief Card name getter.
     * @return Constant link with string containing the card name.
    */
    const std::string& getName() const; 

    /**
     * @brief Card basic health effect getter.
     * @return Integer representing health change that card causes.
    */
    int getHealthEffect() const;

    /**
     * @brief Card basic respect effect getter.
     * @return Integer representing respect change that card causes.
    */  
    int getRespectEffect() const;

    /**
     * @brief Card basic magic effect getter.
     * @return Integer representing magic change that card causes.
    */ 
    int getMagicEffect() const;

    /**
     * @brief Card type getter.
     * @return Type enumeration value.
    */
    Type getType() const;

    /**
     * @brief '==' operator overload for cards comparsion.
     * @param another Card which is being compared with present.
     * @return True if names match, false otherwise.
    */
    bool operator==(const Card& another) const;
};

#endif