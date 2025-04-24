#include "Players/Bot.h"
#include <thread>
#include <chrono>
#include "Utilities/Console.h"
#include "Game/GameManager/GameManager.h"

enum class BotAIState { Normal, Defensive, Aggressive, MagicFocus, RespectFocus, Default };

Bot::Bot(const std::string &n, int h, int r, Difficulty d) : Character(n, h, r), botDifficulty(d) {}

// interactions with cards
void Bot::drawCard(Deck& deck)
{
    if (!deck.isEmpty())
    {
        hand.push_back(deck.drawCard());
    }
}

bool Bot::needsCards()
{
    return hand.size() < 5;
}

// interactions with hand
const std::vector<std::unique_ptr<Card>>& Bot::getHand() const
{
    return hand;
}

void Bot::clearHand()
{
    hand.clear();
}

// STUPID MOVE (JUST FOR NOW)
std::unique_ptr<Card> Bot::makeStupidMove()
{
    if (!hand.empty())
    {
        std::unique_ptr<Card> chosenCard = std::move(hand.front());
        hand.erase(hand.begin());
        return chosenCard;
    }
    return nullptr;
}

std::unique_ptr<Card> Bot::takeTurn(GameManager& game)
{
    Console::print("Думает");
    Console::pause(std::chrono::milliseconds(200));
    Console::print("Все еще думает..");
    Console::pause(std::chrono::milliseconds(100));
    
    const auto& players = game.getPlayers();
    Character* opponent = nullptr;
    Character* bot = this;

    for (const auto& playerPtr : players)
    {
        if(playerPtr && playerPtr.get() != bot)
        {
            opponent = playerPtr.get();
            break;
        }
    }

    if(!opponent)
    {
        Console::printError("Bot couldn't find an opponent!");
        return nullptr;
    }

    int botHealth = bot->getHealth();
    int opponentHealth = opponent->getHealth();
    int magic = game.getMagicPool();
    int respect = bot->getRespect();
    int opponentRespect = opponent->getRespect();

    std::unique_ptr<Card> bestcard = nullptr;
    int bestScore = -1;
    int bestCardIndex = -1;
    const auto& currentHand = bot->getHand();

    if(currentHand.empty())
    {
        Console::printFailedToPlayCard(*this);
        return nullptr;
    }

    for (size_t i = 0; i < currentHand.size(); ++i)
    {
        const auto& cardPtr = currentHand[i];
        if(!cardPtr)
        {
            continue;
        }

        const Card& card = *cardPtr;
        int currentCardScore = 0;

        // porogi 

        //  bot health  //
        int CRITICAL_LOW_HEALTH_THRESHOLD = 7; // очень мало
        int LOW_HEALTH_THRESHOLD = 13; // 13 - есть смысл лечиться
        int OKAY_HEALTH_THRESHOLD = 15; // нормальное количество здоровья
        int HIGH_HEALTH_THRESHOLD = 18; // можно подумать о применении магии
        int CRITICAL_HIGH_HEALTH_THRESHOLD = 24; // опасности нет, нужно атаковать

        //  player health  //
        int P_CRITICAL_LOW_HEALTH_THRESHOLD = 6; // стоит давить игрока 
        int P_LOW_HEALTH_THRESHOLD = 12; // возможно, стоит атаковать 
        int P_OKAY_HEALTH_THRESHOLD = 16; // нормальное количество здоровья
        int P_HIGH_HEALTH_THRESHOLD = 19; // очень много здоровья 
        int P_CRITICAL_HIGH_HEALTH_THRESHOLD = 24; // слишком много здоровья у игрока       

        //   magic    //
        int CRITICAL_HIGH_MAGIC_THRESHOLD = 8; // 10 в сторону игрока ведет к удвоению его карты и обнулению магии
        int HIGH_MAGIC_THRESHOLD = 5; // 5 - это в сторону игрока, достаточно плохо
        int OKAY_MAGIC_THRESHOLD = 0; // start
        int LOW_MAGIC_THRESHOLD = -5; // можно задуматься о применении магии, чтобы усилить следующую карту
        int CRITICAL_LOW_MAGIC_THRESHOLD = -8; // всего 2 магии до усиления, важно использовать возможность

        //  respect  //
        const int B_LOW_RESPECT_THRESHOLD = 5;
        const int B_HIGH_RESPECT_THRESHOLD = 15;
        const int P_LOW_RESPECT_THRESHOLD = 5;
        const int P_HIGH_RESPECT_THRESHOLD = 15;

        // immediate priorities
        if (botHealth <= CRITICAL_HIGH_HEALTH_THRESHOLD)
        {
            if (card.getType() == Card::Type::HEAL)
            {
                currentCardScore = card.getHealthEffect() * 5000;
            }
        }

        else if (magic >= CRITICAL_HIGH_MAGIC_THRESHOLD)
        {
            if (card.getType() == Card::Type::MAGIC)
            {
                currentCardScore = std::max(0, -card.getMagicEffect()) * 4000;
            }
        }

        else if (opponentHealth <= P_CRITICAL_HIGH_HEALTH_THRESHOLD)
        {
            if (card.getType() == Card::Type::ATTACK)
            {
                currentCardScore == card.getHealthEffect() * 4000;
            }
        }

        else if (respect <= B_LOW_RESPECT_THRESHOLD)
        {
            // logic later
        }

        // not that immediate 
        else if (botHealth <= LOW_HEALTH_THRESHOLD)
        {
            if (card.getType() == Card::Type::HEAL)
            {
                currentCardScore = card.getHealthEffect() * 3000;
            }
        }

        else if (opponentHealth <= P_LOW_HEALTH_THRESHOLD)
        {
            if (card.getType() == Card::Type::ATTACK)
            {
                currentCardScore = card.getHealthEffect() * 2500;
            }
        }

        else if (magic >= HIGH_MAGIC_THRESHOLD)
        {
            if (card.getType() == Card::Type::MAGIC)
            {
                currentCardScore = std::max(0, -card.getMagicEffect()) * 2500;
            }
        }
        // etc.
    }
}

void Bot::drawInitCards(Deck& deck)
{
    while (hand.size() < 5 && !deck.isEmpty())
    {
        hand.push_back(deck.drawCard());
    }
}

bool Bot::wantsToQuit() const
{
    return false;
}