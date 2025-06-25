#include "Weapon.h"
#include <iostream>
#include "Character.h"

// ������
Weapon::Weapon(const std::string& name, ItemTier tier, int attackBonus, int price, bool isEquipped)
    : Item(name, tier, price, isEquipped), attackBonus(attackBonus)
{
}

// ���� ���� �Լ� ����
std::string Weapon::getEffect() const
{
    return "���ݷ� +" + std::to_string(attackBonus);
}

bool Weapon::canUse() const
{
    return !isEquipped; // �������� �ʾ��� ���� ��� ����
}

std::string Weapon::getItemType() const
{
    return "����";
}

// ��� �Լ�
void Weapon::use(Character& character)
{
    if (!isEquipped)
    {
        isEquipped = true;
        std::cout << name << "��(��) �����߽��ϴ�!" << std::endl;
        // TODO: character.equipWeapon(this) ���� ���� �߰�
    }
    else
    {
        std::cout << name << "��(��) �̹� �������Դϴ�!" << std::endl;
    }
}

// Getter
int Weapon::getAttackBonus() const
{
    return attackBonus;
}