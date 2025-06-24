#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
    Goblin(int level);

    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage) override;
};