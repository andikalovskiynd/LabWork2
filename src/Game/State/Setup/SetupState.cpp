#include "../src/Game/State/Setup/SetupState.h"

SetupState::SetupState (Deck& d, std::vector<Character*> p) : deck(d), players(p) {}

void SetupState::enterState(GameManager& game)
{
    deck.shuffle();
    initPlayers();
    initHands();
    game.setState(new PlayingState(players, deck));
}

void SetupState::updateState(GameManager& game) {}
void SetupState::exitState(GameManager& game) {}

void SetupState::initPlayers()
{
    std::string playerName;
    int difficulty;

    std::cout << "Введите свое имя" << std::endl;
    std::cin >> playerName;

    Character* human = new Player(playerName, 20, 10);
    players.push_back(human);

    std::cout << "Выберите сложность (1-3 от легкого к сложному)" << std::endl;
    std::cin >> difficulty;

    Difficulty botDiff;
    switch (difficulty)
    {
        case 1: botDiff = Difficulty::EASY; break;
        case 2: botDiff = Difficulty::MEDIUM; break;
        case 3: botDiff = Difficulty::HARD; break;
        default: 
            std::cout << "Некорректный ввод. Выбрана легкая сложность. " << std::endl;
            botDiff = Difficulty::EASY;
    }

    Character* bot = new Bot("AI", 20, 10);
    players.push_back(bot);
}

void SetupState::initHands()
{
    for (Character* player : players)
    {
        for (int i = 0; i <=5; ++i)
        {
            player->drawInitCards(deck);
        }
    }
}