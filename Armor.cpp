#include "Armor.h"
#include <iostream>

// ������
Armor::Armor(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price)
    : Item(name, tier, price), defenseBonus(defenseBonus), maxHealthBonus(maxHealthBonus)
{
}

// ���� ���� �Լ� ����
std::string Armor::getEffect() const
{
    std::string effect = "";
    if (defenseBonus > 0) effect += "���� +" + std::to_string(defenseBonus) + " ";
    if (maxHealthBonus > 0) effect += "�ִ� ü�� +" + std::to_string(maxHealthBonus) + " ";
    return effect;
}

bool Armor::canUse() const
{
    return !isEquipped; // �������� �ʾ��� ���� ��� ����
}

std::string Armor::getItemType() const
{
    return "��";
}

// ��� �Լ�
void Armor::use(Character& character)
{
    if (!isEquipped)
    {
        isEquipped = true;
        std::cout << name << "��(��) �����߽��ϴ�!" << std::endl;
        // TODO: character.equipArmor(this) ���� ���� �߰�
    }
    else
    {
        std::cout << name << "��(��) �̹� �������Դϴ�!" << std::endl;
    }
}

// Getter
int Armor::getDefenseBonus() const
{
    return defenseBonus;
}

int Armor::getMaxHealthBonus() const
{
    return maxHealthBonus;
}