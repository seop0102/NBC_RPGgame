#include "Goblin.h"
#include "Monster.h"

Goblin::Goblin(int level)
{
    name = "Goblin";
    health = 40 + (level * 10);
    attack = 17 + (level * 3);
}

std::string Goblin::getName() const { return name; }
int Goblin::getHealth() const { return health; }
int Goblin::getAttack() const { return attack; }

void Goblin::takeDamage(int damage) { Monster::takeDamage(damage); }