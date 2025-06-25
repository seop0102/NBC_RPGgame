#include "Monster.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "ItemDataBase.h"
#include <iostream>
#include <cstdlib>

// �޴� ������
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

// ���� ����
void Monster::status() const
{
    std::cout << "[ " << name << " ]\n"
        << "ü�� : " << health
        << " ���ݷ� : " << attack << "\n";
}

// 10 ~ 20 ������ ���� ��� ��ȯ
int Monster::getGold() const
{
    return rand() % 10 + 10;
}

// ���Ͱ� �������� ����ϴ� �Լ�
Item* Monster::dropItem() const
{
	return ItemDataBase().getRandomItem();
}