#include "Item.h"
#include <iostream>

// ���� ����� Character Ŭ������ ���� include (�ʿ�� �߰�)
// #include "Character.h"

// ������
Item::Item(const std::string& name, ItemTier tier, int price)
    : name(name), tier(tier), price(price), isEquipped(false)
{
}

// Getter �Լ���
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

// Setter �Լ���
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

// ��ƿ��Ƽ �Լ���
std::string Item::getTierString() const
{
    switch (tier)
    {
    case ItemTier::NORMAL: return "�Ϲ�";
    case ItemTier::RARE: return "�߱�";
    case ItemTier::EPIC: return "���";
    default: return "�� �� ����";
    }
}

std::string Item::getItemInfo() const
{
    std::string info = name + "(" + getTierString() + ") - " + getItemType() + " - ";
    info += getEffect();
    info += " - " + std::to_string(price) + " gold";
    return info;
}