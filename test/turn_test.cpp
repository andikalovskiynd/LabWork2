#include "gtest/gtest.h"

#include "Game/Turn/TurnManager.h"
#include "Players/Character.h"
#include "Players/Player.h" 
#include "Players/Bot.h" 

#include <vector>
#include <memory>

// Function for making list of players
std::vector<std::unique_ptr<Character>> createTestPlayersList(int quantity)
{
    std::vector<std::unique_ptr<Character>> players;
    for (int i = 0; i < quantity; ++i)
    {
        if(i % 2 == 0)
        {
            players.push_back(std::make_unique<Player>("Human" + i, 10, 10));
        }
        else
        {
            players.push_back(std::make_unique<Bot>("Bot" + i, 15, 15, Difficulty::MEDIUM));
        }
    }
    return players;
}

// TurnManager tests
// Constructor and getter
// Constructor init
TEST(TurnManagerTests, ConstructorInitTest)
{
    std::vector<std::unique_ptr<Character>> players = createTestPlayersList(2);
    Character* p0 = players[0].get();

    TurnManager turnManager(players);

    ASSERT_NE(nullptr, turnManager.getCurrentPlayer());
    ASSERT_EQ(p0, turnManager.getCurrentPlayer());
}

// Constructor throw on empt list check
TEST(TurnManagerTest, ConstructorThrowsOnEmptyList) 
{
    std::vector<std::unique_ptr<Character>> emptyPlayers;
    EXPECT_THROW(TurnManager turnManager(emptyPlayers), std::runtime_error);
}

// getCurrentPlayer() check
TEST(TurnManagerTests, GetCurrentPlayerTest)
{
    std::vector<std::unique_ptr<Character>> players = createTestPlayersList(2);
    Character* p0 = players[0].get();
    Character* p1 = players[1].get();

    TurnManager turnManager(players);
    ASSERT_EQ(p0, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(p1, turnManager.getCurrentPlayer());

    // Go back to first player
    turnManager.nextTurn();
    ASSERT_EQ(p0, turnManager.getCurrentPlayer());
}

// Next turn
// Test nextTurn() for goig through cycle
TEST(TurnManagerTest, NextTurnCycleTest)
{
    std::vector<std::unique_ptr<Character>> players = createTestPlayersList(3); // 3 игрока
    Character* p0 = players[0].get();
    Character* p1 = players[1].get();
    Character* p2 = players[2].get();

    TurnManager turnManager(players);

    ASSERT_EQ(p0, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(p1, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(p2, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(p0, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(p1, turnManager.getCurrentPlayer());
}

// Test nextTurn() if there is only 1 player
TEST(TurnManagerTest, NextTurnForSinglePlayerTest)
{
    std::vector<std::unique_ptr<Character>> player = createTestPlayersList(1);
    Character* _player = player[0].get();

    TurnManager turnManager(player);

    ASSERT_EQ(_player, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(_player, turnManager.getCurrentPlayer());

    turnManager.nextTurn();
    ASSERT_EQ(_player, turnManager.getCurrentPlayer());
}

// isGameOver() tests
// Check if isGameOver() return false in right conditions
TEST(TurnManagerTest, IsGameOverReturnsFalse)
{
    // todo 
}