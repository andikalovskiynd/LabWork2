#include "Game/State/SetupState.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include "Card/Defined.h"
#include <vector>
#include <thread>
#include <chrono>
#include "Utilities/Console.h"

SetupState::SetupState (Deck& d) : deck(d) {}

void SetupState::enterState(GameManager& game)
{
    Console::printEnterState("Setup state");
    std::vector<std::unique_ptr<Card>> collection = createCollection();
    game.getDeck().resetDeck(std::move(collection));
    initPlayers(game);
    initHands(game);
    Console::loadAnimation("Вход в игровое пространство...", 3, std::chrono::seconds(1));
    game.setState(std::make_unique<PlayingState>(game));
}

void SetupState::updateState([[maybe_unused]] GameManager& game) {}
void SetupState::exitState([[maybe_unused]] GameManager& game) {}

void SetupState::initPlayers(GameManager& game)
{
    std::string playerName;
    int difficulty;

    Console::print("Введите свое имя");
    std::cin >> playerName;

    std::unique_ptr<Character> human = std::make_unique<Player>(playerName, 20, 10);
    game.addPlayer(std::move(human));

    Console::print("Выберите сложность (1-3 от легкого к сложному)");
    std::cin >> difficulty;

    std::unique_ptr<Character> bot;
    Difficulty botDiff;
    switch (difficulty)
    {
        case 1: botDiff = Difficulty::EASY; bot = std::make_unique<Bot>("Валера", 15, 5); break;
        case 2: botDiff = Difficulty::MEDIUM; bot = std::make_unique<Bot>("Антон", 20, 10); break;
        case 3: botDiff = Difficulty::HARD; bot = std::make_unique<Bot>("Богдан", 25, 20); break;
        default: 
            Console::printInvalidInput("Некорректный ввод. Выбрана легкая сложность. ");
            botDiff = Difficulty::EASY;
            bot = std::make_unique<Bot>("Valera", 15, 5);
            break;
    }

    if (bot)
    {
        game.addPlayer(std::move(bot));
    }
    
    else
    {
        Console::printError("Failed to create bot");
    }
}

void SetupState::initHands(GameManager& game)
{
    const auto& playersInGame = game.getPlayers();
    for (const auto& playerPtr : playersInGame)
    {
        if (playerPtr) 
        {
            playerPtr->drawInitCards(deck);
        }
    }
}