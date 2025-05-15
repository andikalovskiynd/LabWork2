#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Players/Character.h"
#include "Players/Player.h" // Character is an abstract class so we can't make object of it
#include "Players/Bot.h" // opponent is neccesery

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
class MockGameManager : public GameManager
{
    private:
        StubDeck stubDeck_;

    public: 
        MockGameManager() : GameManager(stubDeck_), stubDeck_() {}

        // Mock methods
        MOCK_METHOD(bool, shouldAmplify, (), (const, override));
        MOCK_METHOD(const std::vector<std::unique_ptr<Character>>&, getPlayers, (), (const, override));
        MOCK_METHOD(void, updateMagicPool, (int amount), (override));
        MOCK_METHOD(Character*, getCurrentPlayer, (), (override));
        MOCK_METHOD(void, setCurrentPlayer, (Character* player), (override));
        MOCK_METHOD(void, resetMagicPool, (), (override));
        MOCK_METHOD(void, addSpirit, (std::unique_ptr<Spirit> spirit), (override));
};

// Character tests
// Constructor test
TEST(CharacterTestConstructor, Constructor_Initializes_Correctly)
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
TEST(CharacterTestGetters, BasicGetters_Return_CorrectValues)
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
TEST(CharacterTestChanges, ChangeHealth_Increases_Correctly)
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
TEST(CharacterTestChanges, ChangeHealth_ZeroDamage_NothingChanges)
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
TEST(CharacterTestChanges, ChangeRespect_Increases_Correctly)
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
TEST(CharacterTestChanges, ChangeRespect_Decreases_Correctly)
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
TEST(CharacterTestChanges, ChangeRespect_ZeroChange_NothingChanges)
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
TEST(CharacterTestIsAlive, IsAlive_ReturnsWhenPositiveHealth_True)
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
TEST(CharacterTestIsAlive, IsAlive_ReturnsWhenZeroOrNegative_False)
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
TEST(CharacterTestAttack, ApplyCardEffect_AttackCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    AttackCard stubAttackCard("Test Attack", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int magicEffect = stubAttackCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth - healthEffect, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock checks everything else 
}

// Attack card amplified
TEST(CharacterTestAttack, ApplyCardEffect_AttackCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    AttackCard stubAttackCard("Test Attack", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubAttackCard.getHealthEffect();
    int magicEffect = stubAttackCard.getMagicEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: shouldAmplify() must return true
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp

    // Act
    testCharPtr->ApplyCardEffect(stubAttackCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth - ampHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock checks everything else 
}

// Heal card not amplified 
TEST(CharacterTestHeal, ApplyCardEffect_HealCardNotAmplifed_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    HealCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubCard.getHealthEffect();
    int magicEffect = stubCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth + healthEffect, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Heal card amplified 
TEST(CharacterTestHeal, ApplyCardEffect_HealCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    HealCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int healthEffect = stubCard.getHealthEffect();
    int magicEffect = stubCard.getMagicEffect();

    int ampHealth = healthEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth + ampHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}


// Respect card not amplified
TEST(CharacterTestRespect, ApplyCardEffect_RespectCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    RespectCard stubCard("Test Respect", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int respectEffect = stubCard.getRespectEffect();
    int magicEffect = stubCard.getMagicEffect();

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect + respectEffect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Respect card amplified
TEST(CharacterTestRespect, ApplyCardEffect_RespectCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    RespectCard stubCard("Test Heal", 10, 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int respectEffect = stubCard.getRespectEffect();
    int magicEffect = stubCard.getMagicEffect();

    int ampRespect = respectEffect * 2;
    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reseting mp

    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect + ampRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Magic card not amplified
TEST(CharacterTestMagic, ApplyCardEffect_MagicCardNotAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    MagicCard stubCard("Test Magic", 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    // mock:
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so there is mustnt be a chance to reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Magic Card amplified 
TEST(CharacterTestMagic, ApplyCardEffect_MagicCardAmplified_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    MagicCard stubCard("Test Magic", 5);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    int ampMagic = magicEffect * 2;

    // mock: 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(true)); // shouldAmplify must be TRUE
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(ampMagic))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(1); // shouldAmplify must be TRUE so reset mp


    // Act
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}

// Zero changes card
TEST(CharacterTestZero, ApplyCardEffect_ZeroChangeCard_Correctly)
{
    // Arrange
    MockGameManager gameManager;
    std::unique_ptr<Player> testChar = std::make_unique<Player>("Test char", 25, 20);
    std::unique_ptr<Bot> opponent = std::make_unique<Bot>("Opponent", 25, 20, Difficulty::EASY); 

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testChar)); 
    playersMock.push_back(std::move(opponent));

    Character* testCharPtr = playersMock[0].get();
    Character* opponentPtr = playersMock[1].get();

    Card stubCard("Test", 0, 0, 0, Card::Type::ATTACK);

    int playerInitHealth = testCharPtr->getHealth();
    int playerInitRespect = testCharPtr->getRespect();

    int opponentInitHealth = opponentPtr->getHealth();
    int opponentInitRespect = opponentPtr->getRespect();

    int magicEffect = stubCard.getMagicEffect();

    // mock: shouldAmplify() may be called 0 or 1 time 
    EXPECT_CALL(gameManager, setCurrentPlayer(testCharPtr)).Times(1); // aef calls game.setCurrentPlayer
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock)); // aef calls getPlayers. must return mock players (playersMock)
    EXPECT_CALL(gameManager, shouldAmplify()).WillOnce(::testing::Return(false)); // shouldAmplify must be false
    EXPECT_CALL(gameManager, updateMagicPool(::testing::Eq(-magicEffect))).Times(1); // aef calls updateMagicPool
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(::testing::AtLeast(0)); // spirit might be called with little chance so
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0); // shouldAmplify must be false so do not reset mp


    // Act 
    testCharPtr->ApplyCardEffect(stubCard, gameManager);


    // Assert
    ASSERT_EQ(playerInitHealth, testCharPtr->getHealth());
    ASSERT_EQ(playerInitRespect, testCharPtr->getRespect());

    ASSERT_EQ(opponentInitHealth, opponentPtr->getHealth());
    ASSERT_EQ(opponentInitRespect, opponentPtr->getRespect());
    // mock will check expectations
}