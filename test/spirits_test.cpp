#include "gtest/gtest.h"

#include "Game/Spirit/Spirit.h"
#include "Game/Spirit/EvilSpirit.h"
#include "Game/Spirit/GoodSpirit.h"
#include "Game/Spirit/MagicWizard.h"
#include "Game/GameManager/GameManager.h"
#include "Deck/Deck.h"
#include "Players/Player.h" // we will use Player as Character imolementation for tests

#include <memory>

// Basic spirit tests is impossible because Spirit is abstract class

// EvilSpirit test
TEST(EvilSpiritTest, ApplyEffectTest)
{
    std::unique_ptr<Player> target = std::make_unique<Player>("Test subject", 15, 10);
    int initHealth = target->getHealth();

    EvilSpirit evilSpirit(target.get()); 
    evilSpirit.applyEffect();
    int damageExpected = 10;

    ASSERT_EQ(initHealth - damageExpected, target->getHealth());
}

// GoodSpirit test
TEST(GoodSpiritTest, ApplyEffectTest)
{
    std::unique_ptr<Player> target = std::make_unique<Player>("Test subject", 15, 10);
    int initHealth = target->getHealth();

    GoodSpirit goodSpirit(target.get()); 
    goodSpirit.applyEffect();
    int healExpected = 10;

    ASSERT_EQ(initHealth + healExpected, target->getHealth());
}

// MagicWizard test
TEST(MagicWizardTest, ApplyEffectTest)
{
    Deck deck;
    GameManager game(deck);

    std::unique_ptr<Player> player1 = std::make_unique<Player>("Test subject1", 15, 10);
    std::unique_ptr<Player> player2 = std::make_unique<Player>("Test subject2", 20, 15);
    game.addPlayer(std::move(player1));
    game.addPlayer(std::move(player2));

    Character* creatorPlayer = game.getPlayers()[0].get(); 
    Character* creatorBot = game.getPlayers()[1].get();

    MagicWizard magicWizardPlayer(creatorPlayer, game);
    MagicWizard magicWizardBot(creatorBot, game);

    // Test when creator is player
    int initMagicPool1 = game.getMagicPool();

    magicWizardPlayer.applyEffect();

    int expectMagicChange = -5;
    ASSERT_EQ(initMagicPool1 + expectMagicChange, game.getMagicPool());

    // reset for next test
    game.resetMagicPool();
    ASSERT_EQ(0, game.getMagicPool());

    // Test when creator is bot
    int initMagicPool2 = game.getMagicPool();

    magicWizardBot.applyEffect();

    int expectMagicChange = 5;
    ASSERT_EQ(initMagicPool1 + expectMagicChange, game.getMagicPool());

    // Check update() for both spirits
    ASSERT_TRUE(magicWizardPlayer.update());
    ASSERT_FALSE(magicWizardPlayer.update());

    ASSERT_TRUE(magicWizardBot.update());
    ASSERT_TRUE(magicWizardBot.update());
}