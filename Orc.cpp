#include "Orc.h"
#include "Monster.h"

Orc::Orc(int level)
{
    name = "Orc";
    health = 40 + (level * Utils::getRandomInt(15, 30));
    attack = 17 + (level * Utils::getRandomInt(10, 15));
}

std::string Orc::getName() const { return name; }
int Orc::getHealth() const { return health; }
int Orc::getAttack() const { return attack; }

void Orc::takeDamage(int damage) { Monster::takeDamage(damage); }