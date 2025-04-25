#include "Card/Defined.h"

std::vector<std::unique_ptr<Card>> createCollection()
{
    std::vector<std::unique_ptr<Card>> collection;
    collection.reserve(26);

    // attack
    collection.push_back(std::make_unique<AttackCard>("Удар меча", 5, 3));
    collection.push_back(std::make_unique<AttackCard>("Огненный шар", 8, 5));
    collection.push_back(std::make_unique<AttackCard>("Ледяная стрела", 4, 2));
    collection.push_back(std::make_unique<AttackCard>("Кинжал тьмы", 6, 4));
    collection.push_back(std::make_unique<AttackCard>("Громовой удар", 7, 3));
    collection.push_back(std::make_unique<AttackCard>("Ядовитый шип", 3, 1));
    collection.push_back(std::make_unique<AttackCard>("Кровавый клинок", 9, 6));
    collection.push_back(std::make_unique<AttackCard>("Каменный кулак", 5, 3));
    collection.push_back(std::make_unique<AttackCard>("Вихрь", 4, 2));
    collection.push_back(std::make_unique<AttackCard>("Смертельный укус", 10, 7));

    // healing
    collection.push_back(std::make_unique<HealCard>("Малое исцеление", 6, 2));
    collection.push_back(std::make_unique<HealCard>("Божественный свет", 10, 5));
    collection.push_back(std::make_unique<HealCard>("Регенерация", 4, 1));
    collection.push_back(std::make_unique<HealCard>("Эликсир жизни", 12, 6));
    collection.push_back(std::make_unique<HealCard>("Ритуал восстановления", 8, 3));

    // magic
    collection.push_back(std::make_unique<MagicCard>("Взрыв маны", +7));
    collection.push_back(std::make_unique<MagicCard>("Поглощение", -4));
    collection.push_back(std::make_unique<MagicCard>("Магический щит", +5));
    collection.push_back(std::make_unique<MagicCard>("Искажение", -3));
    collection.push_back(std::make_unique<MagicCard>("Сфера хаоса", +10));
    collection.push_back(std::make_unique<MagicCard>("Проклятие пустоты", -8));
    collection.push_back(std::make_unique<MagicCard>("Энергетический вихрь", +6));

    // respect
    collection.push_back(std::make_unique<RespectCard>("Поклон", +4, 1));
    collection.push_back(std::make_unique<RespectCard>("Оскорбление", -3, 2));
    collection.push_back(std::make_unique<RespectCard>("Речь лидера", +7, 3));
    collection.push_back(std::make_unique<RespectCard>("Подкуп", +10, 5));
    collection.push_back(std::make_unique<RespectCard>("Благородный жест", +6, 2));

    return collection;
}