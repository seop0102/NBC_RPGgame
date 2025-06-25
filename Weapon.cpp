#include "Weapon.h"
#include <iostream>
#include "Character.h"

// 생성자
Weapon::Weapon(const std::string& name, ItemTier tier, int attackBonus, int price, bool isEquipped)
    : Item(name, tier, price, isEquipped), attackBonus(attackBonus)
{
}

// 순수 가상 함수 구현
std::string Weapon::getEffect() const
{
    return "공격력 +" + std::to_string(attackBonus);
}

bool Weapon::canUse() const
{
    return !isEquipped; // 장착되지 않았을 때만 사용 가능
}

std::string Weapon::getItemType() const
{
    return "무기";
}

// 사용 함수
void Weapon::use(Character& character)
{
    if (!isEquipped)
    {
        isEquipped = true;
        std::cout << name << "을(를) 장착했습니다!" << std::endl;
        // TODO: character.equipWeapon(this) 등의 로직 추가
    }
    else
    {
        std::cout << name << "은(는) 이미 장착중입니다!" << std::endl;
    }
}

// Getter
int Weapon::getAttackBonus() const
{
    return attackBonus;
}