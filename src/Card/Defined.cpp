/**
 * @file Defined.cpp 
 * @brief Implementation of createCollection(). 
*/

#include "Card/Defined.h"

std::vector<std::unique_ptr<Card>> createCollection()
{
    std::vector<std::unique_ptr<Card>> collection;
    collection.reserve(26);

    // attack
    collection.push_back(std::make_unique<AttackCard>("Sword Attack", 5, 3));
    collection.push_back(std::make_unique<AttackCard>("Fireball", 8, 5));
    collection.push_back(std::make_unique<AttackCard>("Frost Arrow", 4, 2));
    collection.push_back(std::make_unique<AttackCard>("Dark Dagger", 6, 4));
    collection.push_back(std::make_unique<AttackCard>("Thunder Strike", 7, 3));
    collection.push_back(std::make_unique<AttackCard>("Poison Thorn", 3, 1));
    collection.push_back(std::make_unique<AttackCard>("Blood Blade", 9, 6));
    collection.push_back(std::make_unique<AttackCard>("Stone Fist", 5, 3));
    collection.push_back(std::make_unique<AttackCard>("Whirlwind", 4, 2));
    collection.push_back(std::make_unique<AttackCard>("Deadly Bite", 10, 7));

    // healing
    collection.push_back(std::make_unique<HealCard>("Minor Healing", 6, 2));
    collection.push_back(std::make_unique<HealCard>("Divine Light", 10, 5));
    collection.push_back(std::make_unique<HealCard>("Regeneration", 4, 1));
    collection.push_back(std::make_unique<HealCard>("Elixir of Life", 12, 6)); 
    collection.push_back(std::make_unique<HealCard>("Restoration Ritual", 8, 3)); 

    // magic
    collection.push_back(std::make_unique<MagicCard>("Mana Burst", 7));
    collection.push_back(std::make_unique<MagicCard>("Absorption", 4));
    collection.push_back(std::make_unique<MagicCard>("Magic Shield", 5));
    collection.push_back(std::make_unique<MagicCard>("Distortion", 3));
    collection.push_back(std::make_unique<MagicCard>("Sphere of Chaos", 10));
    collection.push_back(std::make_unique<MagicCard>("Curse of Emptiness", 8));
    collection.push_back(std::make_unique<MagicCard>("Energy Vortex", 6));

    // respect
    collection.push_back(std::make_unique<RespectCard>("Bow", 4, 1));
    collection.push_back(std::make_unique<RespectCard>("Insult", 3, 2));
    collection.push_back(std::make_unique<RespectCard>("Leader's Speech", 7, 3));
    collection.push_back(std::make_unique<RespectCard>("Bribe", 10, 5));
    collection.push_back(std::make_unique<RespectCard>("Noble Gesture", 6, 2));

    return collection;
}
