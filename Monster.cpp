#include "Monster.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include"Consumable.h"
#include <iostream>
#include <cstdlib>

// 받는 데미지
// 30%확률로 아이템 드랍 추가 해야 함



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

//몬스터 스텟
void Monster::status() const
{
    std::cout << "[ " << name << " ]\n"
        << "체력 : " << health
        << " 공격력 : " << attack << "\n";
}

// 1~100 사이의 랜덤 골드 반환(임시)
int Monster::getGold() const
{
    return rand() % 100 + 1;
}


Item* Monster::dropItem() const
{
    srand(time(0));
    int chance = rand() % 100;
    Item* item = nullptr;

    if (chance < 30)
    {
        int randItem = rand() % 3; // 0: 무기, 1: 방어구, 2: 소모품
        switch (randItem)
        {
        case 0:
        {
            int randWeapon = rand() % 2;
            if (randWeapon == 0)
            {
                item = new Weapon("철검", ItemTier::NORMAL, 3, 100);
            }
            else
            {
                item = new Weapon("지팡이", ItemTier::RARE, 4, 100);
            }
            return item;
        }
        case 1:
        {
            int randArmor = rand() % 2;
            if (randArmor == 0)
            {
                item = new Armor("방패", ItemTier::RARE, 5, 0, 100);
            }
            else
            {
                item = new Armor("갑옷", ItemTier::EPIC, 10, 3, 100);
            }
            return item;
        }
        case 2:
        {
            int randEdible = rand() % 2;
            if (randEdible == 0)
            {
                item = new Consumable("회복 물약", ItemTier::NORMAL, 50, 2, 0, 100);
            }
            else
            {
                item = new Consumable("회복 물약", ItemTier::RARE, 100, 4, 0, 100);
            }
            return item;
        }
        }
    }
    else
    {
        return item;
    }
}