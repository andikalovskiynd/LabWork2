#include "Game/Spirit/MagicWizard.h"
#include <iostream>
#include "Utilities/Console.h"

MagicWizard::MagicWizard(Character* target, GameManager& g) : Spirit(target, 1), game(g) {}
void MagicWizard::applyEffect()
{
    // Добавьте отладочные выводы здесь
    std::cout << "DEBUG MagicWizard applyEffect: Called." << std::endl;
    if (&game == nullptr) { std::cout << "DEBUG Error: game is null in MagicWizard::applyEffect!" << std::endl; return; }
    std::cout << "DEBUG MagicWizard applyEffect: game is valid." << std::endl;

    if (game.getPlayers().empty()) {
        std::cout << "DEBUG Error: Players vector is empty in MagicWizard::applyEffect!" << std::endl;
        return; // Нет игроков, не можем применить эффект
    }
     std::cout << "DEBUG MagicWizard applyEffect: Players vector is not empty. Size: " << game.getPlayers().size() << std::endl;


    if (game.getPlayers().size() < 2) {
         std::cout << "DEBUG Error: Not enough players (< 2) in MagicWizard::applyEffect!" << std::endl;
         return; // Меньше двух игроков, не можем применить эффект
    }
    std::cout << "DEBUG MagicWizard applyEffect: At least 2 players found." << std::endl;

    Character* spiritCreator = getTarget();
    if (spiritCreator == nullptr) {
        std::cout << "DEBUG Error: spiritCreator (target) is null in MagicWizard::applyEffect!" << std::endl;
        return; // Цель духа нулевая
    }
     std::cout << "DEBUG MagicWizard applyEffect: spiritCreator is valid: " << spiritCreator->getName() << std::endl;


    Character* playerOne = game.getPlayers()[0].get();
    Character* playerTwo = game.getPlayers()[1].get();

    if (playerOne == nullptr || playerTwo == nullptr) {
         std::cout << "DEBUG Error: playerOne or playerTwo is null in MagicWizard::applyEffect!" << std::endl;
         return; // Один из игроков нулевой
    }
     std::cout << "DEBUG MagicWizard applyEffect: playerOne: " << playerOne->getName() << ", playerTwo: " << playerTwo->getName() << std::endl;


    // Ваш код логики изменения магии:
    int magicChangeAmount = 5;

    if (spiritCreator == playerOne) // Если духа вызвал Игрок 1 (человек)
    {
        std::cout << "DEBUG MagicWizard applyEffect: spiritCreator is playerOne. Changing magic by: " << -magicChangeAmount << std::endl;
        game.updateMagicPool(-magicChangeAmount);
        Console::printSpiritEffect(*spiritCreator, "Кто это?.. Таинственный колдун забирает магию в ущерб " + spiritCreator->getName());
    }
    else if (spiritCreator == playerTwo) // Если духа вызвал Игрок 2 (бот)
    {
        std::cout << "DEBUG MagicWizard applyEffect: spiritCreator is playerTwo. Changing magic by: " << magicChangeAmount << std::endl;
        game.updateMagicPool(magicChangeAmount);
        Console::printSpiritEffect(*spiritCreator, "Кто это?.. Таинственный колдун добавляет магию в ущерб " + spiritCreator->getName());
    }
    else
    {
        std::cout << "DEBUG MagicWizard applyEffect: spiritCreator is neither playerOne nor playerTwo. No magic change applied." << std::endl;
    }

    // ... остальной код applyEffect (уменьшение длительности и т.д., это в Spirit::update)
}
