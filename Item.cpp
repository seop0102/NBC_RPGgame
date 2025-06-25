#include "Item.h"
#include <iostream>

// 전방 선언된 Character 클래스를 위한 include (필요시 추가)
// #include "Character.h"

// 생성자
Item::Item(const std::string& name, ItemTier tier, int price)
    : name(name), tier(tier), price(price), isEquipped(false)
{
}

// Getter 함수들
std::string Item::getName() const
{
    return name;
}

std::string Item::getDescription() const
{
    return description;
}

ItemTier Item::getTier() const
{
    return tier;
}

int Item::getPrice() const
{
    return price;
}

bool Item::getIsEquipped() const
{
    return isEquipped;
}

// Setter 함수들
void Item::setName(const std::string& name)
{
    this->name = name;
}

void Item::setEquipped(bool equipped)
{
    this->isEquipped = equipped;
}

void Item::setPrice(int price)
{
    this->price = price;
}

// 유틸리티 함수들
std::string Item::getTierString() const
{
    switch (tier)
    {
    case ItemTier::NORMAL: return "일반";
    case ItemTier::RARE: return "중급";
    case ItemTier::EPIC: return "고급";
    default: return "알 수 없음";
    }
}

std::string Item::getItemInfo() const
{
    std::string info = name + "(" + getTierString() + ") - " + getItemType() + " - ";
    info += getEffect();
    info += " - " + std::to_string(price) + " gold";
    return info;
}