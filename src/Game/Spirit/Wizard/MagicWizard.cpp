#include "Game/Spirit/MagicWizard.h"
#include <iostream>
#include "Utilities/Console.h"

MagicWizard::MagicWizard(Character* target, GameManager& g) : Spirit(target, 1), game(g) {}
void MagicWizard::applyEffect()
{
    Character* creator = getTarget();
    if (creator == game.getPlayers()[0].get())
    {
        game.updateMagicPool(-5);
        Console::printSpiritEffect(*getTarget(), "Кто это?.. Таинственный колдун крадет магию у " + creator->getName());
    }
    else if (creator == game.getPlayers()[0].get())
    {
        game.updateMagicPool(5);
        Console::printSpiritEffect(*getTarget(), "Кто это?.. Таинственный колдун крадет магию у " + creator->getName());
    }
    else
    {
        Console::printError("MagicWizard::applyEffect error");
    }
}
