#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"
#include <vector>
#include <memory>

/**
 * @brief Function that creates collection from already defined cards.
 * @return Vector with unique pointers on 'Card' objects. 
*/
std::vector<std::unique_ptr<Card>> createCollection();