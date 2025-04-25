#include "Game/State/SetupState.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include "Card/Defined.h"
#include <vector>
#include <thread>
#include <chrono>
#include "Utilities/Console.h"
#include "Utilities/Input.h"

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

    Console::print("Введите свое имя");
    playerName = InputManager::getStringInput();

    std::unique_ptr<Character> human = std::make_unique<Player>(playerName, 20, 10);
    game.addPlayer(std::move(human));

    Console::print("Выберите сложность (1-3 от легкого к сложному)");
    int difficulty = InputManager::getInt(1, 3);

    std::unique_ptr<Character> bot;
    Difficulty botDiff;
    switch (difficulty)
    {
        case 1: botDiff = Difficulty::EASY; bot = std::make_unique<Bot>("Валера", 15, 5, Difficulty::EASY); break;
        case 2: botDiff = Difficulty::MEDIUM; bot = std::make_unique<Bot>("Антон", 20, 10, Difficulty::MEDIUM); break;
        case 3: botDiff = Difficulty::HARD; bot = std::make_unique<Bot>("Богдан", 25, 20, Difficulty::HARD); break;
        default: 
            Console::printInvalidInput("Некорректный ввод. Выбрана легкая сложность. ");
            botDiff = Difficulty::EASY;
            bot = std::make_unique<Bot>("Анатолий", 15, 5, Difficulty::EASY);
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