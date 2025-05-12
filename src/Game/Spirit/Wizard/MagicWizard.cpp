/**
 * @file MagicWizard.cpp
 * @brief Implementation of class MagicWizard methods.
*/

#include "Game/Spirit/MagicWizard.h"
#include <iostream>
#include "Utilities/Console.h"

/**
 * @details Checks who is the creator, if it is a human, magic reduces by 5, if it is bot, magic increases by 5. 
*/
MagicWizard::MagicWizard(Character* target, GameManager& g) : Spirit(target, 1), game(g) {}
void MagicWizard::applyEffect()
{
    Character* creator = getTarget();
    if (creator == game.getPlayers()[0].get())
    {
        game.updateMagicPool(-5);
        Console::printSpiritEffect(*getTarget(), "Who is that? Magic wizard steals magic from " + creator->getName());
    }
    else if (creator == game.getPlayers()[1].get())
    {
        game.updateMagicPool(5);
        Console::printSpiritEffect(*getTarget(), "Who is that? Magic wizard steals magic from " + creator->getName());
    }
    else
    {
        Console::printError("MagicWizard::applyEffect error");
    }
}
