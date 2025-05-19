/**
 * @file Bot.cpp 
 * @brief Implementation of class Bot methods. 
*/

#include "Players/Bot.h"
#include <thread>
#include <chrono>
#include "Utilities/Console.h"
#include "Game/GameManager/GameManager.h"
#include <cstdlib>
#include <ctime>

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

std::unique_ptr<Card> Bot::playCard(int index)
{
    if (index >= 0 && index < static_cast<int>(hand.size()))
    {
        std::unique_ptr<Card> chosenCard = std::move(hand[index]);
        hand.erase(hand.begin() + index);
        return chosenCard;
    }

    else
    {
        Console::printFailedToPlayCard(*this);
        return nullptr;
    }
}

// Play first card in the vector. 
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

/**
 * @details Choosing state relying on bot health, respect, opponent health, respect and magic.
*/
BotState Bot::chooseState(GameManager& game)
{
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

    int botHealth = bot->getHealth();
    int opponentHealth = opponent->getHealth();
    int magic = game.getMagicPool();
    int botRespect = bot->getRespect();
    int opponentRespect = opponent->getRespect();

    int CRITICAL_LOW_HEALTH_THRESHOLD = 7; 
    int LOW_HEALTH_THRESHOLD = 13;
    [[maybe_unused]]int OKAY_HEALTH_THRESHOLD = 15; 
    [[maybe_unused]]int HIGH_HEALTH_THRESHOLD = 18; 
    [[maybe_unused]]int CRITICAL_HIGH_HEALTH_THRESHOLD = 24; 

    //  player health  //
    int P_CRITICAL_LOW_HEALTH_THRESHOLD = 6; 
    int P_LOW_HEALTH_THRESHOLD = 12; 
    [[maybe_unused]]int P_OKAY_HEALTH_THRESHOLD = 16; 
    [[maybe_unused]]int P_HIGH_HEALTH_THRESHOLD = 19; 
    [[maybe_unused]]int P_CRITICAL_HIGH_HEALTH_THRESHOLD = 24; 

    //   magic    //
    int CRITICAL_HIGH_MAGIC_THRESHOLD = 8; 
    [[maybe_unused]]int HIGH_MAGIC_THRESHOLD = 5; 
    int OKAY_MAGIC_THRESHOLD = 0;
    int LOW_MAGIC_THRESHOLD = -5;
    [[maybe_unused]]int CRITICAL_LOW_MAGIC_THRESHOLD = -8;

    //  respect  //
    const int B_LOW_RESPECT_THRESHOLD = 5;
    const int B_HIGH_RESPECT_THRESHOLD = 15;
    const int P_LOW_RESPECT_THRESHOLD = 5;
    const int P_HIGH_RESPECT_THRESHOLD = 15;

    BotState currentState = BotState::Default;

    if (botHealth <= CRITICAL_LOW_HEALTH_THRESHOLD)
    {
        currentState = BotState::CriticallyDefensive;
    }
            
    else if (opponentHealth <= P_CRITICAL_LOW_HEALTH_THRESHOLD || botHealth - opponentHealth >= 20)
    {
        currentState = BotState::CriticallyAggressive;
    }

    else if (magic >= CRITICAL_HIGH_MAGIC_THRESHOLD)
    {
        currentState = BotState::MagicCrisis;
    }

    else if (botRespect <= B_LOW_RESPECT_THRESHOLD)
    {
        currentState = BotState::RespectCrisisBot;
    }

    else if (opponentRespect >= P_HIGH_RESPECT_THRESHOLD)
    {
        currentState = BotState::RespectCrisisOpponent;
    }

    else if (botHealth <= LOW_HEALTH_THRESHOLD)
    {
        currentState = BotState::Defensive;
    }

    else if (opponentHealth <= P_LOW_HEALTH_THRESHOLD)
    {
        currentState = BotState::Aggressive;
    }

    else if (magic >= OKAY_MAGIC_THRESHOLD)
    {
        currentState = BotState::MagicAdvantageOpponent;
    }

    else if (magic <= OKAY_MAGIC_THRESHOLD && magic > LOW_MAGIC_THRESHOLD)
    {
        currentState = BotState::MagicAdvantageBot;
    }

    else if (botRespect < B_HIGH_RESPECT_THRESHOLD || opponentRespect > P_LOW_RESPECT_THRESHOLD)
    {
        currentState = BotState::RespectFocus;
    }
    return currentState;
}

/**
 * @details Fitsly we use chooseState, then bot makes more specialized for state 
 * checks which will eventually give a score to every card. Then bot chooses card with highest score and returns it. 
*/
std::unique_ptr<Card> Bot::takeTurn(GameManager& game)
{
    Console::print("Thinking..");
    Console::pause(std::chrono::milliseconds(200));
    
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

    std::unique_ptr<Card> bestCard = nullptr;
    int bestScore = -1;
    int bestCardIndex = -1;
    const auto& currentHand = bot->getHand();

    if(currentHand.empty())
    {
        Console::printFailedToPlayCard(*this);
        return nullptr;
    }

    std::unique_ptr<Card> playedCard = nullptr;

    switch (botDifficulty)
    {
        case Difficulty::EASY: 
        {
            playedCard = makeStupidMove();
            break;
        }

        case Difficulty::MEDIUM:
        {
            const int M_BOT_LOW_HEALTH = 15;
            const int M_OPPONENT_LOW_HEALTH = 15;
            const int M_HIGH_MAGIC = 5;

            for (size_t i = 0; i < currentHand.size(); ++i)
                {
                    const auto& cardPtr = currentHand[i];
                    if (!cardPtr)
                    {
                        continue;
                    }

                    const Card& card = *cardPtr;
                    int currentCardScore = 0;
                    
                    if (botHealth <= M_BOT_LOW_HEALTH && card.getType() == Card::Type::HEAL)
                    {
                        currentCardScore = card.getHealthEffect() * 100;
                    }

                    else if (magic >= M_HIGH_MAGIC && card.getType() == Card::Type::MAGIC)
                    {
                        currentCardScore = card.getMagicEffect() * 80;
                    }

                    else if (opponentHealth <= M_OPPONENT_LOW_HEALTH && card.getType() == Card::Type::ATTACK)
                    {
                        currentCardScore = card.getHealthEffect() * 60;
                    }

                    else if (card.getType() == Card::Type::ATTACK)
                    {
                        currentCardScore = card.getHealthEffect() * 10; 
                    }

                    else if (card.getType() == Card::Type::HEAL)
                    {
                        currentCardScore = card.getHealthEffect() * 7;
                    }

                    else if (card.getType() == Card::Type::MAGIC)
                    {
                        currentCardScore = card.getMagicEffect() * 6;
                    }

                    else if (card.getType() == Card::Type::RESPECT)
                    {
                        currentCardScore = card.getMagicEffect() * 5;
                    }

                    if (currentCardScore > bestScore)
                    {
                        bestScore = currentCardScore;
                        bestCardIndex = static_cast<int>(i);
                    }
                }
                
            if (bestCardIndex != -1)
            {
                playedCard = playCard(bestCardIndex);
            }

            else 
            {
                Console::printFailedToPlayCard(*this);

                if (!currentHand.empty())
                {   
                    Console::print("MEDIUM: stupid move!");
                    playedCard = makeStupidMove();
                }

                else 
                {
                    playedCard = nullptr;
                }
            }
                break;
        }

        case Difficulty::HARD:
        {
            //   bot health   //
            [[maybe_unused]]int CRITICAL_LOW_HEALTH_THRESHOLD = 7; 
            int LOW_HEALTH_THRESHOLD = 13; 
            int OKAY_HEALTH_THRESHOLD = 15;
            [[maybe_unused]]int HIGH_HEALTH_THRESHOLD = 18;
            [[maybe_unused]]int CRITICAL_HIGH_HEALTH_THRESHOLD = 24;

            //  player health  //
            [[maybe_unused]]int P_CRITICAL_LOW_HEALTH_THRESHOLD = 6;  
            int P_LOW_HEALTH_THRESHOLD = 12; 
            int P_OKAY_HEALTH_THRESHOLD = 16;
            [[maybe_unused]]int P_HIGH_HEALTH_THRESHOLD = 19;
            [[maybe_unused]]int P_CRITICAL_HIGH_HEALTH_THRESHOLD = 24;    

            //   magic    //
            int CRITICAL_HIGH_MAGIC_THRESHOLD = 8; 
            int HIGH_MAGIC_THRESHOLD = 5; 
            [[maybe_unused]]int OKAY_MAGIC_THRESHOLD = 0; 
            [[maybe_unused]]int LOW_MAGIC_THRESHOLD = -5;
            [[maybe_unused]]int CRITICAL_LOW_MAGIC_THRESHOLD = -8; 

            //  respect  //
            [[maybe_unused]]const int B_LOW_RESPECT_THRESHOLD = 5;
            [[maybe_unused]]const int B_HIGH_RESPECT_THRESHOLD = 15;
            [[maybe_unused]]const int P_LOW_RESPECT_THRESHOLD = 5;
            [[maybe_unused]]const int P_HIGH_RESPECT_THRESHOLD = 15;

            BotState currentState = chooseState(game);

            int bestScore = -1;
            int bestCardIndex = -1;

            for (size_t i = 0; i < currentHand.size(); ++i)
            {
                const auto& cardPtr = currentHand[i];
                if (!cardPtr)
                {
                    continue;
                }
                const Card& card = *cardPtr;
                int currentCardScore = 0;

                // pognali
                switch (currentState)
                {
                    case BotState::CriticallyDefensive:
                    {
                        if (card.getType() == Card::Type::HEAL)
                        {
                            currentCardScore = card.getHealthEffect() * 10000;
                        }

                        else if (magic >= CRITICAL_HIGH_MAGIC_THRESHOLD && card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = card.getMagicEffect() * 5000;
                        }

                        break;
                    }

                    case BotState::Defensive:
                    {
                        if (card.getType() == Card::Type::HEAL)
                        {
                            currentCardScore = card.getHealthEffect() * 5000;
                        }

                        else if (magic >= HIGH_MAGIC_THRESHOLD && card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 2000;
                        }

                        else if (card.getType() == Card::Type::ATTACK && opponentHealth <= P_OKAY_HEALTH_THRESHOLD)
                        {
                            currentCardScore = (card.getHealthEffect()) * 350;
                        }

                        break;
                    }

                    case BotState::Aggressive:
                    {
                        if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = (card.getHealthEffect()) * 5000;
                        }

                        else if (magic >= HIGH_MAGIC_THRESHOLD && card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 2000;
                        }

                        else if (botHealth < OKAY_HEALTH_THRESHOLD && card.getType() == Card::Type::HEAL)
                        {
                            currentCardScore = card.getHealthEffect() * 350;
                        }

                        break;
                    }

                    case BotState::CriticallyAggressive:
                    {
                        if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = (card.getHealthEffect()) * 10000;
                        }

                        else if (magic >= CRITICAL_HIGH_MAGIC_THRESHOLD && card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 5000;
                        }

                        break;
                    }

                    case BotState::MagicCrisis:
                    {
                        if (card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 10000;
                        }

                        else if (botHealth <= LOW_HEALTH_THRESHOLD && card.getType() == Card::Type::HEAL)
                        {
                            currentCardScore = card.getHealthEffect() * 3000;
                        }

                        break;
                    }

                    case BotState::RespectCrisisOpponent:
                    {
                        if (card.getType() == Card::Type::RESPECT && card.getRespectEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getRespectEffect()) * 10000;
                        }
                        
                        else if (card.getType() == Card::Type::ATTACK && opponentHealth < P_LOW_HEALTH_THRESHOLD)
                        {
                            currentCardScore = (card.getHealthEffect()) * 3000;
                        }

                        break;
                    }

                    case BotState::RespectCrisisBot:
                    {
                        if (card.getType() == Card::Type::RESPECT && card.getRespectEffect() > 0)
                        {
                            currentCardScore = card.getRespectEffect() * 10000;
                        }
                        
                        else if (card.getType() == Card::Type::HEAL && botHealth < LOW_HEALTH_THRESHOLD)
                        {
                            currentCardScore = card.getHealthEffect() * 3000;
                        }

                        break;
                    }

                    case BotState::MagicAdvantageBot:
                    {
                        if (card.getType() == Card::Type::MAGIC && card.getMagicEffect() > 0)
                        {
                            currentCardScore = card.getMagicEffect() * 5000;
                        }

                        else if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = card.getHealthEffect() * 1000;
                        }

                        break;
                    }

                    case BotState::MagicAdvantageOpponent:
                    {
                        if (card.getType() == Card::Type::MAGIC && card.getMagicEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 5000;
                        }

                        else if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = (card.getHealthEffect()) * 1000;
                        }

                        break;
                    }

                    case BotState::RespectFocus:
                    {
                        if (card.getType() == Card::Type::RESPECT && card.getRespectEffect() > 0)
                        {
                            currentCardScore = card.getRespectEffect() * 3000;
                        }

                        else if (card.getType() == Card::Type::RESPECT && card.getRespectEffect() < 0)
                        {
                            currentCardScore = std::max(0, card.getRespectEffect()) * 3000;
                        }

                        else if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = (card.getHealthEffect()) * 300;
                        }

                        break;
                    }

                    case BotState::Normal:
                    case BotState::Default:
                    {
                        if (card.getType() == Card::Type::ATTACK)
                        {
                            currentCardScore = (card.getHealthEffect()) * 1000;
                        }

                        else if (card.getType() == Card::Type::HEAL)
                        {
                            currentCardScore = card.getHealthEffect() * 800;
                        }

                        else if (card.getType() == Card::Type::MAGIC)
                        {
                            currentCardScore = std::max(0, card.getMagicEffect()) * 700;
                        }

                        else if (card.getType() == Card::Type::RESPECT)
                        {
                            currentCardScore = std::abs(card.getRespectEffect()) * 500;
                        }

                        break;
                    }
                }
                
                if (currentCardScore > bestScore)
                {
                    bestScore = currentCardScore;
                    bestCardIndex = static_cast<int>(i);
                }

                else if (currentCardScore == bestScore && currentCardScore > -1) 
                {
                    if (rand() % 2 == 0) 
                    {
                        bestCardIndex = static_cast<int>(i);
                    }
                }
            }

            if (bestCardIndex != -1)
            {
                playedCard = playCard(bestCardIndex);
            }

            else 
            {
                Console::printFailedToPlayCard(*this);
                if (!currentHand.empty())
                {
                    playedCard = makeStupidMove();
                }

                else
                {
                    playedCard = nullptr;
                }
            }

            break;
        }
    }

    return playedCard;
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

const Difficulty Bot::getDifficulty() const
{
    return botDifficulty;
}

void Bot::setHand(std::vector<std::unique_ptr<Card>> cards) 
{
    hand = std::move(cards); 
}