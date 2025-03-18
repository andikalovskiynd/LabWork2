#include "Game/Spirit/Wizard/MagicWizard.h"
#include <iostream>

MagicWizard::MagicWizard(Character* target, GameManager& g) : Spirit(target), game(g) {}
void MagicWizard::applyEffect()
{
    int magicPool = game.getMagicPool();
    magicPool += (getTarget() == game.getCurrentPlayer()) ? -5 : +5;
    std::cout << "Кто это?.. Таинственный колдун крадет магию у " << getTarget()->getName() << std::endl;
}