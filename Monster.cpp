#include "Monster.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "ItemDataBase.h"
#include <iostream>
#include <cstdlib>

// 받는 데미지
void Monster::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
    }
}

void Monster::setHealth(int health)
{
    this->health = health;
}

void Monster::setAttack(int attack)
{
    this->attack = attack;
}

// 몬스터 스텟
void Monster::status() const
{
    std::cout << "[ " << name << " ]\n"
        << "체력 : " << health
        << " 공격력 : " << attack << "\n";
}

// 10 ~ 20 사이의 랜덤 골드 반환
int Monster::getGold() const
{
    return rand() % 10 + 10;
}

// 몬스터가 아이템을 드랍하는 함수
Item* Monster::dropItem() const
{
	return ItemDataBase().getRandomItem();
}