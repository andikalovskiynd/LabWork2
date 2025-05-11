# Laboratory work 2
## Author
Andikalovskiy Nikita Dmitrievich, 24.B-82mm
## Contacts
st131335@stdudent.spbu.ru
## Description
Lab work 2. Card RPG game core with hierarchy of charcters and items based on inheritance.
## Requirements 
* C++ 17, install if not installed yet:
``` 
sudo apt update
sudo apt install build-essential
```
* `make`, install if not installed yet:
```
sudo apt update
sudo apt install make
```
* `Doxygen`, install if not installed yet:
```
sudo apt update
sudo apt install doxygen
```
* `LaTeX`, install if not installed yet:
```
sudo apt update
sudo apt install texlive-full
```
## Build
make
## Run
./game
## Additional info (Rules)
**Attributes**

The game features three attributes you will be interacting with. The first is Health, the most straightforward attribute: the higher it is, the better. The second is Respect. It influences the chance of spirits appearing (more details below). The third is Magic. Unlike the previous two, this attribute is not personal to the player. Magic is shared across the board and has no amplifying effects while it is between -10 and +10. If it reaches +10 or higher, your card effects (including detrimental ones) will be doubled. Similarly for your AI opponent, their effects are doubled when the magic pool reaches -10 or lower.

--- 

**Gameplay**

You will engage in a 1-on-1 card game against an AI opponent. At the beginning of the game, you can choose the difficulty level. The deck is infinite, however, the types of cards are limited (you can view the list of existing cards at docs/cards.md).
Your goal is to reduce the opponent's Health to zero, but you should also keep in mind the other attributes that influence the game.

---

**Cards and Spirits**

There are 4 types of cards:

    1. Attack
    2. Heal
    3. Magic
    4. Respect

An important paradigm in this game is that to gain one attribute, you must sacrifice two others. For example, if you want to deal damage to the opponent (using an Attack card) or gain healing (using a Heal card), you will have to incur losses in Magic (from the shared pool) and/or Respect.

When playing each card type, there is a small, variable chance for a spirit to appear. Depending on the card type, the spirit can deal damage to the card's user, heal the user, alter the magic pool, or simply have no effect (for Attack, Heal, Magic, and Respect cards, respectively). Probability of Spirit appearance directively depends on your personal respect and difference between your and opponent's respect.