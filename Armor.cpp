#include "Armor.h"
#include <iostream>

// 생성자
Armor::Armor(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price)
    : Item(name, tier, price), defenseBonus(defenseBonus), maxHealthBonus(maxHealthBonus)
{
}

// 순수 가상 함수 구현
std::string Armor::getEffect() const
{
    std::string effect = "";
    if (defenseBonus > 0) effect += "방어력 +" + std::to_string(defenseBonus) + " ";
    if (maxHealthBonus > 0) effect += "최대 체력 +" + std::to_string(maxHealthBonus) + " ";
    return effect;
}

bool Armor::canUse() const
{
    return !isEquipped; // 장착되지 않았을 때만 사용 가능
}

std::string Armor::getItemType() const
{
    return "방어구";
}

// 사용 함수
void Armor::use(Character& character)
{
    if (!isEquipped)
    {
        isEquipped = true;
        std::cout << name << "을(를) 장착했습니다!" << std::endl;
        // TODO: character.equipArmor(this) 등의 로직 추가
    }
    else
    {
        std::cout << name << "은(는) 이미 장착중입니다!" << std::endl;
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