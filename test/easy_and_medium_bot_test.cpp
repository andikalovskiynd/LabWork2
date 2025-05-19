#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Utilities/mock_class.h"

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
#include "Utilities/tests_methods.h"

#include <string>
#include <memory> 
#include <vector>  

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
TEST(EasyBotTest, TakeTurn_EasyDifficulty_PlaysFirstCard)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::EASY);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 5, 2)); 
    botHand.push_back(std::make_unique<HealCard>("Heal card", 10, 3));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 7));
    Card* expectedCard = botHand[0].get(); // it is expected to use first card in vector

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); // Bot::takeTurn doesn't getCurrentPlayer
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);


    // Act 
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert 
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Medium difficulty tests
// Test if bot plays heal card if it's health is low
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysHealCardWhenLowHealth)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 5, 20, Difficulty::MEDIUM);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("First card", 5, 2));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 4));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 3, 5));
    botHand.push_back(std::make_unique<HealCard>("HealCard", 15, 5));
    Card* expectedCard = botHand[3].get(); // expected to use heal card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0);
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0); 
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}


// Test if bot chooses heal card with the greatest heal
TEST(MediumBotTest, TakeTurn_MediumDifficulty_ChoosesHealCardWithGreatestHeal)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 5, 20, Difficulty::MEDIUM);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal card with low heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<HealCard>("HealCard with high heal", 15, 10));

    Card* expectedCard = botHand[3].get(); // expected to use high heal card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot plays attack card when opponent health is low
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWhenOpponentHealthLow)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 10, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[3].get(); // expected to use attack card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot plays attack card with more damage 
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWithMoreDamage)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 10, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<AttackCard>("Weak attack card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Strong attack card", 20, 10));
 
    Card* expectedCard = botHand[3].get(); // expected to use strong attack card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot plays magic card if magic is too high
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWhenMagicIsHigh)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[1].get(); // expected to use magic card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(8)); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));
    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot plays magic card with higher magic effect 
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWithHigherEffect)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); 

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<MagicCard>("Weak magic card", 10));
    botHand.push_back(std::make_unique<MagicCard>("Strong magic card", 20));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 5));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 20, 10));
    
    Card* expectedCard = botHand[1].get(); // expected to use strong magic card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(8)); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));
    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot plays attack card when there is no other triggers 
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysAttackCardWhenNoTriggers)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    botHand.push_back(std::make_unique<AttackCard>("Attack card", 10, 10));

    Card* expectedCard = botHand[3].get(); // expected to use attack card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot chooses heal card when there are no any other triggers and no attack card in the hand
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysHealCardWithoutOuterTriggersAndNoAttackCardInHand)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<HealCard>("Heal card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));

    Card* expectedCard = botHand[0].get(); // expected to use heal card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot chooses magic card when there are no any other triggers and no attack and heal card in the hand
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysMagicCardWithoutOuterTriggersAndNoAttackOrHealCardInHand)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    botHand.push_back(std::make_unique<MagicCard>("Magic card", 10));
    
    Card* expectedCard = botHand[1].get(); // expected to use magic card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
}

// Test if bot chooses respect card when there are no any other triggers and no attack, heal and magic card in the hand
TEST(MediumBotTest, TakeTurn_MediumDifficulty_PlaysRespectCardWithoutOuterTriggersAndNoAttackOrHealOrMagicCardInHand)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::MEDIUM); 
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30); // opponent low health is 15 or less

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    std::vector<std::unique_ptr<Card>> botHand;
    botHand.push_back(std::make_unique<RespectCard>("Respect card", 10, 10));
    botHand.push_back(std::make_unique<RespectCard>("Respect card 2", 2, 2));
    
    Card* expectedCard = botHand[0].get(); // expected to use higher profit respect card

    botPtr->setHand(std::move(botHand));
    size_t initHandSize = botPtr->getHand().size();

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    EXPECT_CALL(gameManager, getCurrentPlayer()).Times(0); 
    EXPECT_CALL(gameManager, setCurrentPlayer(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, shouldAmplify()).Times(0);
    EXPECT_CALL(gameManager, updateMagicPool(::testing::_)).Times(0); 
    EXPECT_CALL(gameManager, addSpirit(::testing::_)).Times(0);
    EXPECT_CALL(gameManager, resetMagicPool()).Times(0);

    // Act
    std::unique_ptr<Card> playedCard = botPtr->takeTurn(gameManager);

    // Assert    
    ASSERT_NE(nullptr, playedCard);
    ASSERT_EQ(expectedCard->getName(), playedCard->getName());
    ASSERT_EQ(initHandSize - 1, botPtr->getHand().size());
    ASSERT_FALSE(isCardInHand(botPtr->getHand(), playedCard->getName()));
} 