#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Players/Bot.h"
#include "Players/Character.h"
#include "Players/Player.h"


#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"

#include "Game/GameManager/GameManager.h"
#include "Deck/Deck.h"

#include <string>
#include <memory> 
#include <vector>  

// Deck stub
// needed only to init GameManager mock
class StubDeck : public Deck 
{
    public:
        StubDeck() : Deck() {}
};

// GameManager mock 
// Using it in Bot.cpp logic to make AI decisisons as accurate as possible
class MockGameManager : public GameManager
{
    private:
        StubDeck stubDeck_;
        std::vector<std::unique_ptr<Character>> testPlayers_;
        Character* currentPlayer_ = nullptr;
        int magicPool_ = 0;

    public: 
        MockGameManager() : GameManager(stubDeck_), stubDeck_() {}

        // shouldAmplify mock
        MOCK_METHOD(bool, shouldAmplify, (), (const));

        // Methods that are required for testing
        // setters
        void setTestPlayers(std::vector<std::unique_ptr<Character>> players)
        {
            testPlayers_ = std::move(players);
        }

        void mockSetCurrentPlayer(Character* player)
        {
            currentPlayer_ = player;
        }

        void setMagicPool(int value)
        {
            magicPool_ = value;
        }

        // getters
        const std::vector<std::unique_ptr<Character>>& getPlayers() const
        {
            return testPlayers_;
        }

        Character* getCurrentPlayer() const
        {
            return currentPlayer_;
        }

        int getMagicPool() const
        {
            return magicPool_;
        }
};

// Additive functions to make test more convinient and understandable 
std::unique_ptr<Bot> createTestBot(const std::string& name, int health, int respect, Difficulty difficulty)
{
    return std::make_unique<Bot>(name, health, respect, difficulty);
}

std::unique_ptr<Player> createTestPlayer(const std::string& name, int health, int respect)
{
    return std::make_unique<Player>(name, health, respect);
}

bool isCardInHand(const std::vector<std::unique_ptr<Card>>& hand, const std::string& cardName) 
{
    for (const auto& cardPtr : hand) 
    {
        if (cardPtr != nullptr && cardPtr->getName() == cardName) 
        {
            return true;
        }
    }
    return false;
}

// Bot tests 
// Conctructor test
TEST(BotTest, Constructor_Initializes_Correctly)
{
    Bot testBot("Bot", 10, 10, Difficulty::HARD);

    ASSERT_EQ("Bot", testBot.getName());
    ASSERT_EQ(10, testBot.getHealth());
    ASSERT_EQ(10, testBot.getRespect());
    ASSERT_EQ(Difficulty::HARD, testBot.getDifficulty());
}

// Take turn tests 
// Easy difficulty tests
// Test if bot plays first card in hand if it is easy difficulty
TEST(BotTest, TakeTurn_EasyDifficulty_PlaysFirstCard)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::EASY);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 5, 2)); 
    botHand.push_back(std::make_unique<HealCard>("Heal card", 10, 3));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 7));
    Card* expectedCard = botHand[0].get(); // it is expected to use first card in vector

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act 
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Medium difficulty tests
// Test if bot plays heal card if it's health is low
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysHealCardWhenLowHealth)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 10, 20, Difficulty::MEDIUM); // bot low health threshold is 15
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 40, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<HealCard>("HealCard", 10, 10));
    
    Card* expectedCard = botHand[3].get(); // expected to use heal card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot chooses heal card with the greatest heal
TEST(BotTest, TakeTurn_MediumDifficulty_ChoosesHealCardWithGreatestHeal)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 10, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 40, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal card with low heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<HealCard>("HealCard with high heal", 15, 10));

    Card* expectedCard = botHand[3].get(); // expected to use high heal card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot plays attack card when opponent health is low
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWhenOpponentHealthLow)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 10, 30); // opponent low health is 15 or less

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[3].get(); // expected to use attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot plays attack card with more damage 
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWithMoreDamage)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 10, 30); // opponent low health is 15 or less

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("Weak attack card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Strong attack card", 20, 10));

    Card* expectedCard = botHand[3].get(); // expected to use strong attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot plays magic card if magic is too high
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWhenMagicIsHigh)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;
    gameManager.setMagicPool(6);

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[1].get(); // expected to use magic card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot plays magic card with higher magic effect 
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWithHigherEffect)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;
    gameManager.setMagicPool(6);

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<MagicCard>("Weak magic card", 10));
    botHand.push_back(std::make_unique<MagicCard>("Strong magic card", 20));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[1].get(); // expected to use strong magic card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot plays attack card when there is no other triggers 
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWhenNoTriggers)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 10, 10));

    Card* expectedCard = botHand[3].get(); // expected to use attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot chooses heal card when there are no any other triggers and no attack card in the hand
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysHealCardWithoutOuterTriggersAndNoAttackCardInHand)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand = 
    {
        std::make_unique<HealCard>("Heal", 10, 10),
        std::make_unique<MagicCard>("Magic card", 10),
        std::make_unique<RespectCard>("Respect card", 10, 10),
    };
    Card* expectedCard = botHand[0].get(); // expected to use attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot chooses magic card when there are no any other triggers and no attack and heal card in the hand
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWithoutOuterTriggersAndNoAttackOrHealCardInHand)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    
    Card* expectedCard = botHand[0].get(); // expected to use attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}

// Test if bot chooses respect card when there are no any other triggers and no attack, heal and magic card in the hand
TEST(BotTest, TakeTurn_MediumDifficulty_PlaysRespectCardWithoutOuterTriggersAndNoAttackOrHealOrMagicCardInHand)
{
    // Arrange 
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    MockGameManager gameManager;

    std::vector<std::unique_ptr<Character>> players;
    players.push_back(std::move(testBot));
    players.push_back(std::move(testPlayer));
    gameManager.setTestPlayers(std::move(players));

    Character* botPtr = gameManager.getPlayers()[0].get();
    gameManager.mockSetCurrentPlayer(botPtr);

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card 2", 2, 2));
    
    Card* expectedCard = botHand[0].get(); // expected to use attack card

    static_cast<Bot*>(botPtr)->setHand(std::move(botHand));
    size_t initHandSize = static_cast<Bot*>(botPtr)->getHand().size();

    EXPECT_CALL(gameManager, shouldAmplify()).Times(::testing::AtLeast(0));

    // Act
    std::unique_ptr<Card> playedCard = static_cast<Bot*>(botPtr)->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, static_cast<Bot*>(botPtr)->getHand().size());
    ASSERT_FALSE(isCardInHand(static_cast<Bot*>(botPtr)->getHand(), playedCard->getName()));
}