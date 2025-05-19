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

// ChooseState tests
// Test if bot chooses cr defensive state if his hp is very low 
TEST(HardBot_ChooseState_Test, ChooseState_VeryLowHealthBot_CriticallyDefensive)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 6, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::CriticallyDefensive, state);
}

// Test if bot chooses cr agressive  state if his hp is low 
TEST(HardBot_ChooseState_Test, ChooseState_VeryLowHealthPlayer_CriticallyAgressive)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 5, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::CriticallyAggressive, state);
}

// Test if bot chooses cr agressive  state if difference between players' health is too massive
TEST(HardBot_ChooseState_Test, ChooseState_HealthDifferenceMassive_CriticallyAgressive)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 50, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::CriticallyAggressive, state);
}

// Test if bot chooses magic crisis state if magic is too high for player
TEST(HardBot_ChooseState_Test, ChooseState_MagicTooHigh_MagicCrisis)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(9));
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::MagicCrisis, state);
}

// Test if bot chooses respect crisis state if bot respect is too low 
TEST(HardBot_ChooseState_Test, ChooseState_BotRespectTooLow_RespectCrisisBot)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 3, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 20);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::RespectCrisisBot, state);
}

// Test if bot chooses respect crisis state if player respect is too high
TEST(HardBot_ChooseState_Test, ChooseState_PlayerRespectTooHigh_RespectCrisisOpponent)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 30);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::RespectCrisisOpponent, state);
}

// Test if bot chooses defensive state if bot health is low
TEST(HardBot_ChooseState_Test, ChooseState_LowHealthBot_Defensive)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 12, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 20, 10);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::Defensive, state);
}

// Test if bot chooses agressive state if player's health is low
TEST(HardBot_ChooseState_Test, ChooseState_PlayerHealthLow_Agressive)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 12, 10);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).Times(1); 
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::Aggressive, state);
}

// Test if bot chooses magic advantage opponent state if magic is okay
TEST(HardBot_ChooseState_Test, ChooseState_MagicOkay_MagicAdvantageOpponent)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 15, 10);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(2));
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::MagicAdvantageOpponent, state);
}

// Test if bot chooses magic advantage bot state if magic is betwwen okay and low magic threshold
TEST(HardBot_ChooseState_Test, ChooseState_MagicBetweenLowAndOkay_MagicAdvantageBot)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 20, 20, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 15, 10);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(-3));
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::MagicAdvantageBot, state);
}

// Test if bot chooses respect focus state if bot has kinda low respect
TEST(HardBot_ChooseState_Test, ChooseState_BotKindaLowRespect_RespectFocus)
{
    // Arrange 
    MockGameManager gameManager;
    std::unique_ptr<Bot> testBot = createTestBot("Bot", 15, 6, Difficulty::HARD);
    std::unique_ptr<Player> testPlayer = createTestPlayer("Player", 14, 12);

    Bot* botPtr = testBot.get();

    std::vector<std::unique_ptr<Character>> playersMock;
    playersMock.push_back(std::move(testBot)); 
    playersMock.push_back(std::move(testPlayer));

    EXPECT_CALL(gameManager, getMagicPool()).WillOnce(::testing::Return(-7));
    EXPECT_CALL(gameManager, getPlayers()).WillOnce(::testing::ReturnRef(playersMock));

    // Act
    BotState state = botPtr->chooseState(gameManager);

    // Assert    
    ASSERT_EQ(BotState::RespectFocus, state);
}
