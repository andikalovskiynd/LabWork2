#include "Card/Card.h"
#include "Card/AttackCard.h"
#include "Card/HealCard.h"
#include "Card/MagicCard.h"
#include "Card/RespectCard.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<Card>> createCollection();