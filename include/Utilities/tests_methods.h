#ifndef TESTS_METHODS_H
#define TESTS_METHODS_H

#include "Players/Player.h"
#include "Players/Bot.h"

#include <memory> 

std::unique_ptr<Bot> createTestBot(const std::string& name, int health, int respect, Difficulty difficulty);
std::unique_ptr<Player> createTestPlayer(const std::string& name, int health, int respect);

#endif