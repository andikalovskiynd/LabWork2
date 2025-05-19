#include "Utilities/tests_methods.h"

std::unique_ptr<Bot> createTestBot(const std::string& name, int health, int respect, Difficulty difficulty)
{
    return std::make_unique<Bot>(name, health, respect, difficulty);
}

std::unique_ptr<Player> createTestPlayer(const std::string& name, int health, int respect)
{
    return std::make_unique<Player>(name, health, respect);
}