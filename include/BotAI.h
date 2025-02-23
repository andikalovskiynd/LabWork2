#ifndef BOTAI_H
#define BOTAI_H
#include "Bot.h"
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

class BotAI 
{
private:
    Bot* bot;
    Game* game;
    Deck* deck;

public:
    BotAI (Bot* b, Game* g, Deck* d) : bot(b), game(g), deck(d) {}

    std::vector<Card> analyzeDeck ()
    {
        return deck->getAvailableCards();
    }

    int analyzeOpponentHealth(Player* opponent)
    {
        return opponent
    }
}
#endif