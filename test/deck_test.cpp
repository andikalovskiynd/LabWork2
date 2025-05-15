#include "gtest/gtest.h"

#include "Deck/Deck.h"
#include "Card/Card.h"
#include "Card/AttackCard.h" 
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"

#include <vector>
#include <memory>
#include <algorithm> 
#include <random> 

// Deck tests
TEST(DeckTest, EmptyTest)
{
    Deck deck;
    ASSERT_TRUE(deck.isEmpty());
}

TEST(DeckTest, AddCardsTest)
{
    Deck deck; 
    std::unique_ptr<Card> testCard = std::make_unique<AttackCard>("Test Attack", 10, 5);
    deck.addCard(std::move(testCard));

    ASSERT_FALSE(deck.isEmpty());
    ASSERT_EQ(1, deck.getCards().size());
}

// drawcards, emptiness check
TEST(DeckTest, DrawCardFromNotEmptyDeck)
{
    Deck deck;
    std::unique_ptr<Card> card1 = std::make_unique<AttackCard>("Card 1", 1, 1);
    std::unique_ptr<Card> card2 = std::make_unique<HealCard>("Card 2", 2, 2);

    deck.addCard(std::move(card1));
    deck.addCard(std::move(card2));

    ASSERT_FALSE(deck.isEmpty()); // false empty check

    std::unique_ptr<Card> drawnCard = deck.drawCard();

    ASSERT_NE(nullptr, drawnCard); // check if 1st drawn card is not nullptr

    Card expectedCard("Card 2", 2, 0, 2, Card::Type::HEAL);

    ASSERT_EQ(drawnCard->getName(), expectedCard.getName()); // check if we took right card
    ASSERT_FALSE(deck.isEmpty()); // again false empty check 

    std::unique_ptr<Card> drawnCard2 = deck.drawCard();

    ASSERT_NE(nullptr, drawnCard2);

    Card expectedCard2("Card 1", 1, 0, 1, Card::Type::ATTACK);

    ASSERT_EQ(drawnCard2->getName(), expectedCard2.getName());
    ASSERT_TRUE(deck.isEmpty()); // now true 
}

// drawing card from empty deck test
TEST(DeckTest, DrawCardFromEmptyDeck)
{
    Deck deck;
    ASSERT_TRUE(deck.isEmpty());

    std::unique_ptr<Card> card = deck.drawCard();

    ASSERT_EQ(nullptr, card);
    ASSERT_TRUE(deck.isEmpty());
}

// resetDeck() test : resetDeck() uses shuffle() so we'll compare sorted names and quantity of cards
TEST(DeckTest, ResetDeckTest)
{
    Deck deck;
    deck.addCard(std::make_unique<AttackCard>("Init 1", 1, 1));
    deck.addCard(std::make_unique<HealCard>("Init 2", 2, 2));

    ASSERT_FALSE(deck.isEmpty());
    ASSERT_EQ(2, deck.getCards().size());

    std::vector<std::unique_ptr<Card>> newCards;
    newCards.push_back(std::make_unique<AttackCard>("New 1", 11, 11));
    newCards.push_back(std::make_unique<HealCard>("New 2", 22, 22));
    newCards.push_back(std::make_unique<MagicCard>("New 3", 33));

    std::vector<std::string> expectedNames = {"New 1", "New 2", "New 3"};

    deck.resetDeck(std::move(newCards));

    std::vector<std::string> drawnNames;
    for (const std::unique_ptr<Card>& cardPtr : deck.getCards())
    {
        drawnNames.push_back(cardPtr->getName());
    }

    std::sort(expectedNames.begin(), expectedNames.end());
    std::sort(drawnNames.begin(), drawnNames.end());

    ASSERT_EQ(expectedNames, drawnNames);
}

// Check if shuffle keeps all cards 
TEST(DeckTest, ShuffleKeepsAllCards)
{
    Deck deck1; // before shuffle 
    Deck deck2; // will be used for after shuffle

    std::vector<std::string> initNames = {"Card A", "Card B", "Card C", "Card D", "Card E"};
    for (const std::string& name : initNames)
    {
        deck1.addCard(std::make_unique<AttackCard>(name, 0, 0));
        deck2.addCard(std::make_unique<AttackCard>(name, 0, 0));
    }

    ASSERT_EQ(deck1.getCards().size(), deck2.getCards().size());
    ASSERT_EQ(initNames.size(), deck1.getCards().size()); 

    deck2.shuffle();

    ASSERT_EQ(initNames.size(), deck2.getCards().size());

    std::vector<std::string> namesBeforeShuffle;
    for (const std::unique_ptr<Card>& cardPtr : deck1.getCards())
    {
        namesBeforeShuffle.push_back(cardPtr->getName());
    }

    std::vector<std::string> namesAfterShuffle;
    for (const std::unique_ptr<Card>& cardPtr : deck2.getCards())
    {
        namesAfterShuffle.push_back(cardPtr->getName());
    }

    // need sort because ASSERT_EQ will check order too
    std::sort(namesBeforeShuffle.begin(), namesBeforeShuffle.end());
    std::sort(namesAfterShuffle.begin(), namesAfterShuffle.end());

    ASSERT_EQ(namesBeforeShuffle, namesAfterShuffle);
}