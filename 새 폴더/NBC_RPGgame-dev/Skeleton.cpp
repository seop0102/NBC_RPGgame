#include "Skeleton.h"
#include "Monster.h"

Skeleton::Skeleton(int level)
{
    name = "Skeleton";
    health = 40 + (level * 10);
    attack = 17 + (level * 3);
}

std::string Skeleton::getName() const { return name; }
int Skeleton::getHealth() const { return health; }
int Skeleton::getAttack() const { return attack; }

void Skeleton::takeDamage(int damage) { Monster::takeDamage(damage); }
