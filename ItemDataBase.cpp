#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>

#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"

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

Item* ItemDataBase::createItem(const std::string& itemName) const
{
    auto it = nameToIndex.find(itemName);
    if (it == nameToIndex.end())
    {
        std::cout << "�������� ã�� �� �����ϴ�: " << itemName << std::endl;
        return nullptr;
    }
    return createItem(it->second);
}

Item* ItemDataBase::createItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(itemDataList.size()))
    {
        std::cout << "�߸��� ������ �ε��� : " << index << std::endl;
        return nullptr;
    }

    const ItemData& data = itemDataList[index];
    ItemType type = stringToItemType(data.typeStr);
    ItemTier tier = stringToItemTier(data.tierStr);

    // new�� ����Ͽ� ���� �Ҵ�
    switch (type)
    {
    case ItemType::WEAPON:
        return new Weapon(data.name, tier, data.attackBonus, data.price);
    case ItemType::ARMOR:
        return new Armor(data.name, tier, data.defenseBonus, data.maxHealthBonus, data.price);
    case ItemType::CONSUMABLE:
        return new Consumable(data.name, tier, data.healthRecover, data.skillCharges, data.attackBonus, data.price);
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

std::vector<Item*> ItemDataBase::getItemsByType(ItemType type) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            Item* item = createItem(static_cast<int>(i)); // ���� ����
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<Item*> ItemDataBase::getItemsByTier(ItemTier tier) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            Item* item = createItem(static_cast<int>(i)); // ���� ����
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    return result;
}

void ItemDataBase::printAllItems() const
{
    std::cout << "== ��ü ������ ��� ==" << std::endl;
    std::vector<Item*> allItems; // �ӽ÷� ������ �������� ������ ����
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        Item* item = createItem(static_cast<int>(i)); // ���� ����
        if (item)
        {
            std::cout << "[" << i << "] " << item->getItemInfo() << std::endl;
            allItems.push_back(item); // �ӽ� ���Ϳ� �߰��Ͽ� ���߿� ����
        }
    }
    // �Լ� ���� �� �ӽ÷� ������ ������ �޸� ����
    for (Item* item : allItems) {
        delete item;
    }
}

std::vector<Item*> ItemDataBase::getShopItems(int maxPrice) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            Item* item = createItem(static_cast<int>(i)); // ���� ����
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    std::sort(result.begin(), result.end(),
        [](const Item* a, const Item* b)
        {
            return a->getPrice() < b->getPrice();
        });

    return result;
}

Item* ItemDataBase::getRandomItem() const
{
    int chance = rand() % 100;

    if (chance < 30)
    {
        int itemIndex = std::rand() % itemDataList.size();
        return createItem(itemIndex);
    }
    else
    {
        return nullptr; // 30% Ȯ���� �������� ������� ����
    }
}