#pragma once
#include "Monster.h"

class EvilSpirit : public Monster
{
public:
    EvilSpirit(int level);

    std::string getName() const override;
    int getHealth() const override;
    int getAttack() const override;
    void takeDamage(int damage) override;
};