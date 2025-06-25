#include "Consumable.h"
#include <iostream>

// ������
Consumable::Consumable(const std::string& name, ItemTier tier, int healthRecover,
    int skillCharges, int attackBonus, int price, bool isEquipped)
    : Item(name, tier, price, isEquipped), healthRecover(healthRecover), skillCharges(skillCharges), attackBonus(attackBonus)
{
}

// ���� ���� �Լ� ����
std::string Consumable::getEffect() const
{
    std::string effect = "";
    if (healthRecover > 0) effect += "ü�� ȸ�� +" + std::to_string(healthRecover) + " ";
    if (skillCharges > 0) effect += "��ų ��� Ƚ�� +" + std::to_string(skillCharges) + " ";
    if (attackBonus > 0) effect += "�ӽ� ���ݷ� +" + std::to_string(attackBonus) + " ";
    return effect;
}

bool Consumable::canUse() const
{
    return true; // �Ҹ�ǰ�� �׻� ��� ����
}

std::string Consumable::getItemType() const
{
    return "�Ҹ�ǰ";
}

// ��� �Լ�
void Consumable::use(Character& character)
{
    std::cout << name << "��(��) ����߽��ϴ�!" << std::endl;

    // TODO: Character Ŭ������ �޼������ �����Ǹ� �Ʒ� �ּ��� �����ϰ� ���
    // if (healthRecover > 0) character.heal(healthRecover);
    // if (skillCharges > 0) character.addSkillCharges(skillCharges);
    // if (attackBonus > 0) character.addTemporaryAttack(attackBonus);
}

// Getter
int Consumable::getHealthRecover() const
{
    return healthRecover;
}

int Consumable::getSkillCharges() const
{
    return skillCharges;
}

int Consumable::getAttackBonus() const
{
    return attackBonus;
}