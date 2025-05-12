#include "gtest/gtest.h"

#include "Game/GameManager/GameManager.h"
#include "Deck/Deck.h"
#include "Players/Character.h"
#include "Players/Player.h" 
#include "Players/Bot.h"
#include "Game/Spirit/Spirit.h" 

#include <memory>
#include <vector> 
#include <string> 

// GameManager tests

// Constructor test
TEST(GameManagerTest, ConstructorTest)
{
    Deck deck;
    GameManager game(deck);

    ASSERT_EQ(0, game.getMagicPool());
    ASSERT_EQ(nullptr, game.getCurrentPlayer());
    ASSERT_EQ(0, game.getPlayers().size());
}

// Test if getDeck() returns right deck
TEST(GameManagerTest, GetDeckTest)
{
    Deck originalDeck;
    GameManager game(originalDeck);

    Deck& gotDeck = game.getDeck();
    ASSERT_EQ(&originalDeck, &gotDeck);
}

// addPlayer() accuracy check
TEST(GameManagerTest, AddPlayerTest)
{
    Deck deck;
    GameManager game(deck);

    ASSERT_EQ(0, game.getPlayers().size());

    // 1 player for start
    std::unique_ptr<Character> player1 = std::make_unique<Player>("PlayerTest1", 10, 10);
    game.addPlayer(std::move(player1));

    ASSERT_EQ(1, game.getPlayers().size());

    // 2 players then
    std::unique_ptr<Character> player2 = std::make_unique<Player>("PlayerTest2", 15, 15);
    game.addPlayer(std::move(player2));

    ASSERT_EQ(2, game.getPlayers().size());
}

// getPlayers() accuracy check
TEST(GameManagerTest, GetPlayersTest)
{
    Deck deck;
    GameManager game(deck);

    std::unique_ptr<Character> player1 = std::make_unique<Player>("Human", 10, 10);
    std::unique_ptr<Character> player2 = std::make_unique<Bot>("Bot", 10, 10, Difficulty::HARD);

    Character* p1Ptr = player1.get();
    Character* p2Ptr = player2.get();

    game.addPlayer(std::move(player1));
    game.addPlayer(std::move(player2));

    const std::vector<std::unique_ptr<Character>>& players = game.getPlayers();

    ASSERT_EQ(2, players.size());
    ASSERT_EQ(p1Ptr, players[0].get());
    ASSERT_EQ(p2Ptr, players[1].get());

    ASSERT_EQ("Human", players[0]->getName());
    ASSERT_EQ("Bot", players[1]->getName());
}

// clearPlayers() accuracy check
TEST(GameManagerTest, ClearPlayersTest)
{
    Deck deck;
    GameManager game(deck);

    game.addPlayer(std::make_unique<Player>("Human", 10, 10));
    game.addPlayer(std::make_unique<Bot>("Bot", 10, 10, Difficulty::EASY));

    game.setCurrentPlayer(game.getPlayers()[0].get());
    ASSERT_NE(nullptr, game.getCurrentPlayer());

    ASSERT_GT(game.getPlayers().size(), 0);

    game.clearPlayers();
    ASSERT_EQ(0, game.getPlayers().size());
    ASSERT_EQ(nullptr, game.getCurrentPlayer());
    ASSERT_EQ(0, game.getMagicPool());
}

// setCurrentPlayer() and get accuracy check
TEST(GameManaegrTest, GetSetCurrentPlayerTest)
{
    Deck deck;
    GameManager game(deck);

    game.addPlayer(std::make_unique<Player>("Play test", 10, 10));
    Character* testPlayerPtr = game.getPlayers()[0].get();

    ASSERT_EQ(nullptr, game.getCurrentPlayer());

    game.setCurrentPlayer(testPlayerPtr);

    ASSERT_EQ(testPlayerPtr, game.getCurrentPlayer());

    game.setCurrentPlayer(nullptr);

    ASSERT_EQ(nullptr, game.getCurrentPlayer());
}

// Magic pool tests
// Correct initialization of magic pool test
TEST(GameManagerTest, InitMagicPoolTest)
{
    Deck deck;
    GameManager game(deck);

    ASSERT_EQ(0, game.getMagicPool());
}

// Correct updateMagicPool() check
TEST(GameManagerTest, UpdateMagicPoolTest)
{
    Deck deck;
    GameManager game(deck);

    ASSERT_EQ(0, game.getMagicPool());

    // positive check
    game.updateMagicPool(5);
    ASSERT_EQ(5, game.getMagicPool());

    game.updateMagicPool(10);
    ASSERT_EQ(15, game.getMagicPool());

    // negative check
    game.updateMagicPool(-7);
    ASSERT_EQ(8, game.getMagicPool());

    game.updateMagicPool(-12);
    ASSERT_EQ(-4, game.getMagicPool());
}

// resetMagicPool() test
TEST(GameManagerTest, ResetMagicPoolTest)
{
    Deck deck;
    GameManager game(deck);

    // positive value check 
    game.updateMagicPool(20);
    ASSERT_EQ(20, game.getMagicPool());
    
    game.resetMagicPool();
    ASSERT_EQ(0, game.getMagicPool());

    // negative value check
    game.updateMagicPool(-20);
    ASSERT_EQ(-20, game.getMagicPool());

    game.resetMagicPool();
    ASSERT_EQ(0, game.getMagicPool());
}

// shouldAmplify() check for different players and magic pool
TEST(GameManagerTest, ShouldAmplifyTest)
{
    Deck deck;
    GameManager game(deck);

    std::unique_ptr<Character> player = std::make_unique<Player>("Human", 10, 10);
    std::unique_ptr<Character> bot = std::make_unique<Bot>("Bot", 10, 10, Difficulty::HARD);

    game.addPlayer(std::move(player));
    game.addPlayer(std::move(bot));

    // Test 1: magic pool in range between -10 and 10
    game.updateMagicPool(5);
    game.setCurrentPlayer(player.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.setCurrentPlayer(bot.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.resetMagicPool();
    game.updateMagicPool(-5);

    game.setCurrentPlayer(player.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.setCurrentPlayer(bot.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.resetMagicPool();

    // Test 2: magic pool >= 10, current player is Player
    game.updateMagicPool(10);
    game.setCurrentPlayer(player.get());
    ASSERT_TRUE(game.shouldAmplify());

    game.updateMagicPool(5);
    ASSERT_TRUE(game.shouldAmplify());

    game.setCurrentPlayer(bot.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.resetMagicPool();

    // Test 3: magic pool <= -10, current player is Bot
    game.updateMagicPool(-10);
    game.setCurrentPlayer(bot.get());
    ASSERT_TRUE(game.shouldAmplify());

    game.updateMagicPool(-5);
    ASSERT_TRUE(game.shouldAmplify());

    game.setCurrentPlayer(player.get());
    ASSERT_FALSE(game.shouldAmplify());

    game.resetMagicPool();
}

// Spirit tests are too hard to implement. 