#include "EvilSpirit.h"
#include "Monster.h"

EvilSpirit::EvilSpirit(int level)
{
    name = "EvilSpirit";
    health = 40 + (level * 10);
    attack = 17 + (level * 3);
}

std::string EvilSpirit::getName() const { return name; }
int EvilSpirit::getHealth() const { return health; }
int EvilSpirit::getAttack() const { return attack; }

void EvilSpirit::takeDamage(int damage) { Monster::takeDamage(damage); }