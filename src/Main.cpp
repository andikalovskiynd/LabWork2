#include <iostream>
#include "../include/Game.h"
#include "../include/Bot.h"
#include "../include/Player.h"

int main ()
{
    std::cout << "Выберите имя персонажа." << std::endl;
    std::string playerName;
    std::cin >> playerName;

    Player player(playerName, 18, 9);
    Bot bot("вован", 18, 9, Difficulty::MEDIUM);
    Game game(&player, &bot);

    while (true)
    {
        std::cout << "Xод игрока" << std::endl;
        game.playTurn(&player);

        if (player.getHealth() <= 0)
        {
            std::cout << "Вы проиграли..." << std::endl;
            break;
        }

        game.playTurn(&bot);
        if (bot.getHealth() <= 0)
        {
            std::cout << "Вы победили!" << std::endl;
            break;
        }
    }
    return 0;
}