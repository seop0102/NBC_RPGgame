#pragma once
#include <string>
#include "Item.h"
#include "Utils.h"

class Monster
{
protected:
    std::string name;
    int health;
    int attack;

public:

    virtual ~Monster() = default;

    virtual std::string getName() const { return name; }
    virtual int getHealth() const { return health; }
    virtual int getAttack() const { return attack; }
    virtual void takeDamage(int damage);
    virtual void setHealth(int health);
    virtual void setAttack(int attack);

    virtual void status() const;

    virtual int getGold() const;

    Item* dropItem() const;

    bool IsBoss = false;

};