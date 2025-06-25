#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>

ItemDataBase::ItemDataBase()
{
    initializeItemData();
}

void ItemDataBase::initializeItemData()
{
    // ��Ʈ �����͸� ������� ������ ���� �ʱ�ȭ

    itemDataList =
    {
        //����
        {"���ҵ�","����","�Ϲ�",5,0,0,0,0,50},
        {"������ ����","����","�߱�",10,0,0,0,0,100},
        {"�ٽ�Ÿ�� �ҵ�","����","���",15,0,0,0,0,200},

        //��
        {"õ ����","��","�Ϲ�",0,10,0,0,10,125},
        {"���� ����","��","�߱�",0,15,0,0,20,250},
        {"�Ǳ� ����","��","���",0,20,0,0,30,500},

        //�Ҹ�ǰ
        {"�ʱ� ����","�Ҹ�ǰ","�Ϲ�",0,0,2,50,0,50},
        {"�߱� ����","�Ҹ�ǰ","�߱�",0,0,4,100,0,100},
        {"���ݷ� ����","�Ҹ�ǰ","���",10,0,6,0,0,200}
    };

    //�̸����� ���� �˻��ϱ�
    nameToIndex.clear();
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        nameToIndex[itemDataList[i].name] = static_cast<int>(i);
    }
}

ItemType ItemDataBase::stringToItemType(const std::string& typeStr) const
{
    if (typeStr == "����") return ItemType::WEAPON;
    if (typeStr == "��") return ItemType::ARMOR;
    if (typeStr == "�Ҹ�ǰ") return ItemType::CONSUMABLE; // EDIBLE -> CONSUMABLE ����
    return ItemType::WEAPON;
}

ItemTier ItemDataBase::stringToItemTier(const std::string& tierStr) const
{
    if (tierStr == "�Ϲ�") return ItemTier::NORMAL; // NORAML -> NORMAL ��Ÿ ����
    if (tierStr == "�߱�") return ItemTier::RARE;
    if (tierStr == "���") return ItemTier::EPIC;
    return ItemTier::NORMAL; // NORAML -> NORMAL ��Ÿ ����
}

std::unique_ptr<Item> ItemDataBase::createItem(const std::string& itemName) const
{
    const ItemData* data = getItemData(itemName);
    if (!data)
    {
        std::cout << "�������� ã�� �� �����ϴ�: " << itemName << std::endl;
        return nullptr;
    }

    return createItem(nameToIndex.at(itemName));
}

std::unique_ptr<Item> ItemDataBase::createItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(itemDataList.size()))
    {
        std::cout << "�߸��� ������ �ε��� : " << index << std::endl;
        return nullptr;
    }

    const ItemData& data = itemDataList[index];
    ItemType type = stringToItemType(data.typeStr);
    ItemTier tier = stringToItemTier(data.tierStr);

    // ������ Ÿ�Կ� ���� ������ ��ü ���� (Ŭ������ ����)
    switch (type)
    {
    case ItemType::WEAPON:
        return std::make_unique<Weapon>(data.name, tier, data.attackBonus, data.price);
    case ItemType::ARMOR:
        return std::make_unique<Armor>(data.name, tier, data.defenseBonus, data.maxHealthBonus, data.price);
    case ItemType::CONSUMABLE: // EDIBLE -> CONSUMABLE ����
        return std::make_unique<Consumable>(data.name, tier, data.healthRecover, data.skillCharges, data.attackBonus, data.price);
    default:
        return nullptr;
    }
}

const ItemData* ItemDataBase::getItemData(const std::string& itemName) const
{
    auto it = nameToIndex.find(itemName);
    if (it != nameToIndex.end())
    {
        return &itemDataList[it->second];
    }
    return nullptr;
}

const ItemData* ItemDataBase::getItemData(int index) const
{
    if (index >= 0 && index < static_cast<int>(itemDataList.size()))
    {
        return &itemDataList[index];
    }
    return nullptr;
}

int ItemDataBase::getItemCount() const
{
    return static_cast<int>(itemDataList.size());
}

std::vector<std::unique_ptr<Item>> ItemDataBase::getItemsByType(ItemType type) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }

    return result;
}

std::vector<std::unique_ptr<Item>> ItemDataBase::getItemsByTier(ItemTier tier) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }
    return result;
}

void ItemDataBase::printAllItems() const // �Լ��� ����
{
    std::cout << "== ��ü ������ ��� ==" << std::endl;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        auto item = createItem(static_cast<int>(i));
        if (item)
        {
            std::cout << "[" << i << "] " << item->getItemInfo() << std::endl; // getIteminfo -> getItemInfo
        }
    }
}

std::vector<std::unique_ptr<Item>> ItemDataBase::getShopItems(int maxPrice) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }
    std::sort(result.begin(), result.end(),
        [](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b)
        {
            return a->getPrice() < b->getPrice();
        });

    return result;
}