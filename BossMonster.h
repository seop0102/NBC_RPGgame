#pragma once
#include "Monster.h"

class Drake : public Monster
{
public:
    Drake(int level);

    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage) override;
};