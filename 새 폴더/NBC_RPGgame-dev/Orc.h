#pragma once
#include "Monster.h"

class Orc : public Monster
{
public:
    Orc(int level);

    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage) override;
};