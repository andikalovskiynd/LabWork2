#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"
#include <vector>
#include <memory>

/**
 * @file Defined.h
 * @brief Includes method that creates collection of all existing cards. 
*/

/**
 * @brief Function that creates collection from already defined cards.
 * @return Vector with unique pointers on 'Card' objects. 
*/
std::vector<std::unique_ptr<Card>> createCollection();