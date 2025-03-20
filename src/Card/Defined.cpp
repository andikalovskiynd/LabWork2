#include "Card/Card.h"
#include "Card/AttackCard/AttackCard.h"
#include "Card/HealCard/HealCard.h"
#include "Card/MagicCard/MagicCard.h"
#include "Card/RespectCard/RespectCard.h"
#include <vector>

std::vector<Card*> createCollection()
{
    return
    {
        // attack
        new AttackCard("Удар меча", 5, 3),
        new AttackCard("Огненный шар", 8, 5),
        new AttackCard("Ледяная стрела", 4, 2),
        new AttackCard("Кинжал тьмы", 6, 4),
        new AttackCard("Громовой удар", 7, 3),
        new AttackCard("Ядовитый шип", 3, 1),
        new AttackCard("Кровавый клинок", 9, 6),
        new AttackCard("Каменный кулак", 5, 3),
        new AttackCard("Вихрь", 4, 2),
        new AttackCard("Смертельный укус", 10, 7),

        // healing
        new HealCard("Малое исцеление", 6, 2),
        new HealCard("Божественный свет", 10, 5),
        new HealCard("Регенерация", 4, 1),
        new HealCard("Эликсир жизни", 12, 6),
        new HealCard("Ритуал восстановления", 8, 3),

        // magic
        new MagicCard("Взрыв маны", +7),
        new MagicCard("Поглощение", -4),
        new MagicCard("Магический щит", +5),
        new MagicCard("Искажение", -3),
        new MagicCard("Сфера хаоса", +10),
        new MagicCard("Проклятие пустоты", -8),
        new MagicCard("Энергетический вихрь", +6),
        
        // respect
        new RespectCard("Поклон", +4, 1),
        new RespectCard("Оскорбление", -3, 2),
        new RespectCard("Речь лидера", +7, 3),
        new RespectCard("Подкуп", +10, 5),
        new RespectCard("Благородный жест", +6, 2)
    };
}