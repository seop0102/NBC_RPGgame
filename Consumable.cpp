#include "Consumable.h"
#include <iostream>

// 생성자
Consumable::Consumable(const std::string& name, ItemTier tier, int healthRecover,
    int skillCharges, int attackBonus, int price, bool isEquipped)
    : Item(name, tier, price, isEquipped), healthRecover(healthRecover), skillCharges(skillCharges), attackBonus(attackBonus)
{
}

// 순수 가상 함수 구현
std::string Consumable::getEffect() const
{
    std::string effect = "";
    if (healthRecover > 0) effect += "체력 회복 +" + std::to_string(healthRecover) + " ";
    if (skillCharges > 0) effect += "스킬 사용 횟수 +" + std::to_string(skillCharges) + " ";
    if (attackBonus > 0) effect += "임시 공격력 +" + std::to_string(attackBonus) + " ";
    return effect;
}

bool Consumable::canUse() const
{
    return true; // 소모품은 항상 사용 가능
}

std::string Consumable::getItemType() const
{
    return "소모품";
}

// 사용 함수
void Consumable::use(Character& character)
{
    std::cout << name << "을(를) 사용했습니다!" << std::endl;

    // TODO: Character 클래스의 메서드들이 구현되면 아래 주석을 해제하고 사용
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