#include "Game/State/SetupState.h"
#include "Players/Player.h"
#include "Players/Bot.h"
#include "Card/Defined.h"
#include <vector>

SetupState::SetupState (Deck& d) : deck(d) {}

void SetupState::enterState(GameManager& game)
{
    std::vector<std::unique_ptr<Card>> collection = createCollection();
    game.getDeck().resetDeck(std::move(collection));
    initPlayers(game);
    initHands(game);
    game.setState(std::make_unique<PlayingState>(game));
}

void SetupState::updateState([[maybe_unused]] GameManager& game) {}
void SetupState::exitState([[maybe_unused]] GameManager& game) {}

void SetupState::initPlayers(GameManager& game)
{
    std::string playerName;
    int difficulty;

    std::cout << "Введите свое имя" << std::endl;
    std::cin >> playerName;

    std::unique_ptr<Character> human = std::make_unique<Player>(playerName, 20, 10);
    game.addPlayer(std::move(human));

    std::cout << "Выберите сложность (1-3 от легкого к сложному)" << std::endl;
    std::cin >> difficulty;

    std::unique_ptr<Character> bot;
    Difficulty botDiff;
    switch (difficulty)
    {
        case 1: botDiff = Difficulty::EASY; bot = std::make_unique<Bot>("Valera", 15, 5); break;
        case 2: botDiff = Difficulty::MEDIUM; bot = std::make_unique<Bot>("Anton", 20, 10); break;
        case 3: botDiff = Difficulty::HARD; bot = std::make_unique<Bot>("Bogdan", 25, 20); break;
        default: 
            std::cout << "Некорректный ввод. Выбрана легкая сложность. " << std::endl;
            botDiff = Difficulty::EASY;
            bot = std::make_unique<Bot>("Valera", 15, 5);
            break;
    }
    game.addPlayer(std::move(bot));
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