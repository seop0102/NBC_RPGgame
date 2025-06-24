#include "BossMonster.h"
#include "Monster.h"

Drake::Drake(int level)
{
    name = "Drake";
    health = 450;
    attack = 120;
}

std::string Drake::getName() const { return name; }
int Drake::getHealth() const { return health; }
int Drake::getAttack() const { return attack; }

void Drake::takeDamage(int damage) { Monster::takeDamage(damage); }