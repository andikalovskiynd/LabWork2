#include "gtest/gtest.h"

#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"

// Basic Card class tests
// Constrcutor and getters
TEST(BasicCardTest, ConstructorAndGetters)
{
    Card testCard("Basic card", 10, 5, 3, Card::Type::ATTACK);

    ASSERT_EQ("Basic card", testCard.getName());
    ASSERT_EQ(10, testCard.getHealthEffect());
    ASSERT_EQ(5, testCard.getRespectEffect());
    ASSERT_EQ(3, testCard.getMagicEffect());
    ASSERT_EQ(Card::Type::ATTACK, testCard.getType());

    EXPECT_EQ("Basic Card", testCard.getName());
    EXPECT_EQ(10, testCard.getHealthEffect());
    EXPECT_EQ(5, testCard.getRespectEffect());
    EXPECT_EQ(3, testCard.getMagicEffect());
    EXPECT_EQ(Card::Type::ATTACK, testCard.getType());
}

// '==' test
TEST(BasicCardTest, EqualityOperator)
{
    Card card1("Name", 0, 0, 0, Card::Type::ATTACK);
    Card card2("Name", 1, 1, 1, Card::Type::HEAL);
    Card card3("Not name", 0, 0, 0, Card::Type::ATTACK);

    ASSERT_TRUE(card1 == card2);
    ASSERT_FALSE(card1 == card3);
    ASSERT_FALSE(card2 == card3);
}

// Inherits tests
// Attack card
TEST(AttackCardTest, ConstructorGettersEffects)
{
    AttackCard attackCard("Fireball", 8, 5);

    ASSERT_EQ("Fireball", attackCard.getName());
    ASSERT_EQ(Card::Type::ATTACK, attackCard.getType());

    // effects
    ASSERT_EQ(8, attackCard.getHealthEffect());
    ASSERT_EQ(5, attackCard.getMagicEffect());
    ASSERT_EQ(0, attackCard.getRespectEffect());
}

// Heal card
TEST(HealCardTest, ConstructorGettersEffects)
{
    HealCard healCard("Minor healing", 6, 2);

    ASSERT_EQ("Minor healing", healCard.getName());
    ASSERT_EQ(Card::Type::HEAL, healCard.getType());

    // effects
    ASSERT_EQ(6, healCard.getHealthEffect());
    ASSERT_EQ(2, healCard.getMagicEffect());
    ASSERT_EQ(0, healCard.getRespectEffect());
}

// Magic card
TEST(MagicCardTest, ConstructorGettersEffects)
{
    MagicCard magicCard("Mana burst", 7);

    ASSERT_EQ("Mana burst", magicCard.getName());
    ASSERT_EQ(Card::Type::MAGIC, magicCard.getType());

    // effects
    ASSERT_EQ(0, magicCard.getHealthEffect());
    ASSERT_EQ(7, magicCard.getMagicEffect());
    ASSERT_EQ(0, magicCard.getRespectEffect());
}

// Respect card
TEST(RespectCardTest, ConstructorGettersEffects)
{
    RespectCard respectCard("Bow", 4, 1);

    ASSERT_EQ("Bow", respectCard.getName());
    ASSERT_EQ(Card::Type::RESPECT, respectCard.getType());

    // effects
    ASSERT_EQ(0, respectCard.getHealthEffect());
    ASSERT_EQ(1, respectCard.getMagicEffect());
    ASSERT_EQ(4, respectCard.getRespectEffect());
}