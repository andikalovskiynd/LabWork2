#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Players/Character.h"
#include "Players/Player.h" // Character is an abstract class so we can't make object of it

#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"
#include "Deck/Deck.h"
#include "Game/GameManager/GameManager.h"

#include <string>
#include <memory> 
#include <vector>

// Using Player as inherit of Character and its representative
// A lot of AAA comments for my personal covinience and logic separation of code

// Deck stub
// needed only to init GameManager mock
class StubDeck : public Deck 
{
    public:
        StubDeck() : Deck() {}
};

// GameManager mock
// Need to control its behavour and check how it works with ApplyCardEffect()
class MockGameManager : public GameManager
{
    private:
        StubDeck stubDeck_;

    public:
        MockGameManager() : GameManager(stubDeck_) {}

        // Mock methods
        MOCK_METHOD(void, updateMagicPool, (int amount), ());
        MOCK_METHOD(bool, shouldAmplify, (), (const));
};

// Character tests
// Constructor test
TEST(CharacterTest, Constructor_Initializes_Correctly)
{
    // Arrange 
    Player testChar("Test char", 10, 15);

    // Act EMPTY

    // Assert
    ASSERT_EQ("Test char", testChar.getName());
    ASSERT_EQ(10, testChar.getHealth());
    ASSERT_EQ(15, testChar.getRespect());
}

// Basic Getters (name, health, respect) test
TEST(CharacterTest, BasicGetters_Return_CorrectValues)
{
    // Arrange 
    Player testChar("Test char", 10, 15);
    
    // Act EMPTY

    // Assert 
    ASSERT_EQ("Test char", testChar.getName());
    ASSERT_EQ(10, testChar.getHealth());
    ASSERT_EQ(15, testChar.getRespect());


    // NEW Arrange NOT NEEDED


    // NEW Act 
    testChar.changeHealth(10);
    testChar.changeRespect(10);


    // NEW Assert 
    ASSERT_EQ(20, testChar.getHealth());
    ASSERT_EQ(25, testChar.getRespect());
}

// changeHealth() tests
// Test for healing
TEST(CharacterTest, ChangeHealth_Increases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int healing = 10;


    // Act
    testChar.changeHealth(healing);


    // Assert
    ASSERT_EQ(initialHealth + healing, testChar.getHealth());
}

// Damage test
TEST(CharacterTest, ChangeHealth_Decreases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int damage = -10;


    // Act
    testChar.changeHealth(damage);


    // Assert
    ASSERT_EQ(initialHealth + damage, testChar.getHealth());
}

// Zero changes test
TEST(CharacterTest, ChangeHealth_ZeroDamage_NothingChanges)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialHealth = 20;
    int damage = 0;


    // Act
    testChar.changeHealth(damage);


    // Assert
    ASSERT_EQ(initialHealth, testChar.getHealth());
}

// changeRespect() tests 
// Test for increasing respect
TEST(CharacterTest, ChangeRespect_Increases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = 10;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect + change, testChar.getRespect());
}

// Damage test
TEST(CharacterTest, ChangeRespect_Decreases_Correctly)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = -10;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect + change, testChar.getRespect());
}

// Zero changes test
TEST(CharacterTest, ChangeRespect_ZeroChange_NothingChanges)
{
    // Arrange 
    Player testChar("Test char", 20, 20);
    int initialRespect = 20;
    int change = 0;


    // Act
    testChar.changeRespect(change);


    // Assert
    ASSERT_EQ(initialRespect, testChar.getRespect());
}

// IsAlive() tests
// Positive test
TEST(CharacterTest, IsAlive_ReturnsWhenPositiveHealth_True)
{
    // Arrange 
    Player testChar1("Test char 1", 20, 20);
    Player testChar2("Test char 2", 20, 20);

    // Act EMPTY

    // Assert
    ASSERT_TRUE(testChar1.IsAlive());
    ASSERT_TRUE(testChar2.IsAlive());
}

// Zero or negative 
TEST(CharacterTest, IsAlive_ReturnsWhenZeroOrNegative_False)
{
    // Arrange 
    Player testChar1("Test char 1", 0, 20);
    Player testChar2("Test char 2", -10, 20);

    // Act EMPTY

    // Assert
    ASSERT_FALSE(testChar1.IsAlive());
    ASSERT_FALSE(testChar2.IsAlive());
}

// ApplyCardEffect() tests using mock and stub 
// Attack card not amplified
TEST(CharacterTest, ApplyCardEffect_AttackCardNotAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 25, 20);
    MockGameManager gameManager;
    AttackCard stubAttackCard("Test Attack", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int respectEffect = stubAttackCard.getRespectEffect();
    int magicEffect = stubAttackCard.getMagicEffect();

    // mock: shouldAmplify() must return false
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false));
    // mock: updateMagicPool() must be called only once with argument magicEffect
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth - healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect + respectEffect, testChar.getRespect());
    // mock will check expectations
}

// Attack card amplified
TEST(CharacterTest, ApplyCardEffect_AttackCardAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    AttackCard stubAttackCard("Test Attack", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int magicEffect = stubAttackCard.getMagicEffect();
    int respectEffect = stubAttackCard.getRespectEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;
    int ampRespect = respectEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true));
    // mock: updateMagicPool() must be called only once with argument ampMagic
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth - ampHealth, testChar.getHealth());
    ASSERT_EQ(initRespect + ampRespect, testChar.getRespect());
    // mock will check expectations
}

// Heal card not amplified 
TEST(CharacterTest, ApplyCardEffect_HealCardNotAmplifed_Correctly)
{
    // Arrange
    Player testChar("Test char", 25, 20);
    MockGameManager gameManager;
    HealCard stubHealCard("Test Heal", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubHealCard.getHealthEffect();
    int respectEffect = stubHealCard.getRespectEffect();
    int magicEffect = stubHealCard.getMagicEffect();

    // mock: shouldAmplify() must return false
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false));
    // mock: updateMagicPool() must be called only once with argument magicEffect
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubHealCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth + healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect - respectEffect, testChar.getRespect());
    // mock will check expectations
}

// Heal card amplified 
TEST(CharacterTest, ApplyCardEffect_HealCardAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 25, 20);
    MockGameManager gameManager;
    HealCard stubHealCard("Test Heal", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubHealCard.getHealthEffect();
    int respectEffect = stubHealCard.getRespectEffect();
    int magicEffect = stubHealCard.getMagicEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;
    int ampRespect = respectEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true));
    // mock: updateMagicPool() must be called only once with argument ampMagic
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubHealCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth + healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect - respectEffect, testChar.getRespect());
    // mock will check expectations
}


// Respect card not amplified
TEST(CharacterTest, ApplyCardEffect_RespectCardNotAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    RespectCard stubRespectCard("Test Respect", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubRespectCard.getHealthEffect();
    int respectEffect = stubRespectCard.getRespectEffect();
    int magicEffect = stubRespectCard.getMagicEffect();  

    // mock: shouldAmplify() must return false
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false));
    // mock: updateMagicPool() must be called only once with argument magicEffect
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1);


    // Act 
    testChar.ApplyCardEffect(stubRespectCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth + healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect + respectEffect, testChar.getRespect());
    // mock will check expectations
}

// Respect card amplified
TEST(CharacterTest, ApplyCardEffect_RespectCardAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    RespectCard stubRespectCard("Test Respect", 10, 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int respectEffect = stubRespectCard.getRespectEffect();
    int magicEffect = stubRespectCard.getMagicEffect();  
    int healthEffect = stubRespectCard.getHealthEffect();

    int ampRespect = respectEffect * 2;
    int ampMagic = magicEffect * 2;
    int ampHealth = healthEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true));
    // mock: updateMagicPool() must be called only once with argument ampMagic
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1);


    // Act 
    testChar.ApplyCardEffect(stubRespectCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth + ampHealth, testChar.getHealth());
    ASSERT_EQ(initRespect + ampRespect, testChar.getRespect());
    // mock will check expectations
}

// Magic card not amplified
TEST(CharacterTest, ApplyCardEffect_MagicCardNotAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    MagicCard stubMagicCard("Test Magic", 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();
    
    int healthEffect = stubMagicCard.getHealthEffect();
    int respectEffect = stubMagicCard.getRespectEffect();
    int magicEffect = stubMagicCard.getMagicEffect();

    // mock: shouldAmplify() must return false
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false));
    // mock: updateMagicPool() must be called only once with argument magicEffect
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubMagicCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth - healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect - respectEffect, testChar.getRespect());
    // mock will check expectations
}

// Magic Card amplified 
TEST(CharacterTest, ApplyCardEffect_MagicCardAmplified_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    MagicCard stubMagicCard("Test Magic", 5);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();
    
    int healthEffect = stubMagicCard.getHealthEffect();
    int respectEffect = stubMagicCard.getRespectEffect();
    int magicEffect = stubMagicCard.getMagicEffect();

    int ampRespect = respectEffect * 2;
    int ampMagic = magicEffect * 2;
    int ampHealth = healthEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true));
    // mock: updateMagicPool() must be called only once with argument ampMagic
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1);


    // Act
    testChar.ApplyCardEffect(stubMagicCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth - healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect - respectEffect, testChar.getRespect());
    // mock will check expectations
}

// Zero changes card
TEST(CharacterTest, ApplyCardEffect_ZeroChangeCard_Correctly)
{
    // Arrange
    Player testChar("Test char", 30, 20);
    MockGameManager gameManager;
    Card stubZeroChangeCard("Test empty", 0, 0, 0, Card::Type::ATTACK);

    int initHealth = testChar.getHealth();
    int initRespect = testChar.getRespect();

    int healthEffect = stubZeroChangeCard.getHealthEffect();
    int respectEffect = stubZeroChangeCard.getRespectEffect();
    int magicEffect = stubZeroChangeCard.getMagicEffect();

    // mock: shouldAmplify() may be called 0 or 1 time 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));
    // mock: updateMagicPool() must be called only once with argument 0
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(0))).Times(1); 


    // Act 
    testChar.ApplyCardEffect(stubZeroChangeCard, gameManager);


    // Assert
    ASSERT_EQ(initHealth + healthEffect, testChar.getHealth());
    ASSERT_EQ(initRespect + respectEffect, testChar.getRespect());
    // mock will check expectations
}