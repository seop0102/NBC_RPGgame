#include "Slime.h"
#include "Monster.h"

Slime::Slime(int level)
{
    name = "Slime";
    health = 40 + (level * 10);
    attack = 17 + (level * 3);
}

std::string Slime::getName() const { return name; }
int Slime::getHealth() const { return health; }
int Slime::getAttack() const { return attack; }

void Slime::takeDamage(int damage) { Monster::takeDamage(damage); }
