#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
public:
    Skeleton(int level);

    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage) override;
};