#ifndef MAGICWIZARD_H
#define MAGICWIZARD_H

/**
 * @file MagicWizard.h 
 * @brief Magic wizard declaration.
*/

#include "Game/Spirit/Spirit.h"
#include "Game/GameManager/GameManager.h"

/// @brief Class that represents Magic spirit (wizard) and inherits from Spirit.
class MagicWizard : public Spirit 
{
private:
    GameManager& game; //< Link on the GameManager object which represents the game currently played.

public:
    /**
     * @brief Magic wizard constructor.
     * @param target Target which is going to be affected.
     * @param game Link on the GameManager object which represents the game currently played.
    */
    MagicWizard(Character* target, GameManager& game);

    /// @brief Applying magic wizard effect: changes magic relying on the target's disadvantage.
    void applyEffect() override;
};

#endif