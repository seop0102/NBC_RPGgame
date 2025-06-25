#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>
#include <random>


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
    if (index >= 0 && static_cast<size_t>(index) < itemDataList.size())
    {
        return &itemDataList[index];
    }
    return nullptr;
}

int ItemDataBase::getItemCount() const
{
    return static_cast<int>(itemDataList.size());
}

// ������ ���� �Լ� (�̸�)
Item* ItemDataBase::createItem(const std::string& itemName) const
{
    const ItemData* data = getItemData(itemName);

    if (!data)
    {
        std::cerr << "Error: Item data not found for name: " << itemName << std::endl;
        return nullptr;
    }

    ItemType type = stringToItemType(data->typeStr);
    ItemTier tier = stringToItemTier(data->tierStr);

    switch (type)
    {
    case ItemType::WEAPON:
        // Weapon ������
        return new Weapon(data->name, tier, data->attackBonus, data->price, true);
    case ItemType::ARMOR:
        // Armor ������
        return new Armor(data->name, tier, data->defenseBonus, data->maxHealthBonus, data->price, true);
    case ItemType::CONSUMABLE:
        // Consumable ������
        return new Consumable(data->name, tier, data->healthRecover, data->skillCharges, data->attackBonus, data->price, false);
    default:
        std::cerr << "Error: Unknown item type for: " << itemName << std::endl;
        return nullptr;
    }
}

// ������ ���� �Լ� (�ε�����)
Item* ItemDataBase::createItem(int index) const
{
    const ItemData* data = getItemData(index);
    if (!data)
    {
        std::cerr << "Error: Item data not found for index: " << index << std::endl;
        return nullptr;
    }

    ItemType type = stringToItemType(data->typeStr);
    ItemTier tier = stringToItemTier(data->tierStr);

    switch (type)
    {
    case ItemType::WEAPON:
        // Weapon ������: (name, tier, attackBonus, price)
        return new Weapon(data->name, tier, data->attackBonus, data->price, true);
    case ItemType::ARMOR:
        // Armor ������: (name, tier, defenseBonus, maxHealthBonus, price)
        return new Armor(data->name, tier, data->defenseBonus, data->maxHealthBonus, data->price, true);
    case ItemType::CONSUMABLE:
        // Consumable ������: (name, tier, healthRecover, skillCharges, attackBonus, price)
        return new Consumable(data->name, tier, data->healthRecover, data->skillCharges, data->attackBonus, data->price, false);
    default:
        std::cerr << "Error: Unknown item type for index: " << index << std::endl;
        return nullptr;
    }
}

std::vector<const ItemData*> ItemDataBase::getItemDatasByType(ItemType type) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            result.push_back(&itemDataList[i]); // ������ �ּ� ��ȯ
        }
    }
    return result;
}

std::vector<const ItemData*> ItemDataBase::getItemDatasByTier(ItemTier tier) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            result.push_back(&itemDataList[i]); // ������ �ּ� ��ȯ
        }
    }
    return result;
}
void ItemDataBase::printAllItemsData() const // �Լ� �̸� ����: printAllItems -> printAllItemsData
{
    std::cout << "== ��ü ������ ������ ��� ==" << std::endl;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        const ItemData& data = itemDataList[i];
        std::cout << "[" << i << "] �̸�: " << data.name
            << ", ����: " << data.typeStr
            << ", ���: " << data.tierStr
            << ", ���ݷ�: " << data.attackBonus
            << ", ����: " << data.defenseBonus
            << ", ü��ȸ��: " << data.healthRecover
            << ", ��ų����: " << data.skillCharges
            << ", �ִ�ü��: " << data.maxHealthBonus
            << ", ����: " << data.price << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

// ������ ������ '������' ����� �����ɴϴ�.
std::vector<const ItemData*> ItemDataBase::getShopItemDatas(int maxPrice) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            result.push_back(&itemDataList[i]); // ������ �ּ� ��ȯ
        }
    }
    // ���� �������� ����
    std::sort(result.begin(), result.end(),
        [](const ItemData* a, const ItemData* b)
        {
            return a->price < b->price;
        });
    return result;
}

// ���� ������ '������'�� �����ɴϴ�.
const ItemData* ItemDataBase::getRandomItemData() const
{

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dropChanceDist(0, 99); // 0-99 ����

    if (dropChanceDist(gen) < 30) // 30% Ȯ���� ������ ���
    {
        std::uniform_int_distribution<> itemIndexDist(0, itemDataList.size() - 1);
        int itemIndex = itemIndexDist(gen);
        return &itemDataList[itemIndex]; // ������ �ּ� ��ȯ
    }
    else
    {
        return nullptr; // 70% Ȯ���� �������� ������� ����
    }
}