#include "Game/Spirit/MagicWizard.h"
#include <iostream>

MagicWizard::MagicWizard(Character* target, GameManager& g) : Spirit(target, 1), game(g) {}
void MagicWizard::applyEffect()
{
    game.updateMagicPool((getTarget() == game.getCurrentPlayer()) ? -5 : +5); // fixed
    std::cout << "Кто это?.. Таинственный колдун крадет магию у " << getTarget()->getName() << std::endl;
}
