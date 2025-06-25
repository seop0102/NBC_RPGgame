#pragma once
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include <vector>
#include <unordered_map>
#include <limits>
// Item �ʾ� ��Ʈ �����Ϳ� �����ؼ� ��������ϴ�
struct ItemData
{
    std::string name; // ������ �̸�
    std::string typeStr; // ������ ����
    std::string tierStr; // ������ ���
    int attackBonus;
    int defenseBonus;
    int skillCharges;
    int healthRecover;
    int maxHealthBonus;
    int price;
};
// ������ Ÿ�� enum (ItemDataBase ���� ����)
enum class ItemType
{
    WEAPON,  // ����
    ARMOR,   // ��
    CONSUMABLE // �Ҹ�ǰ (EDIBLE���� ����)
};
class ItemDataBase
{
private:
    std::vector<ItemData> itemDataList;
    std::unordered_map<std::string, int> nameToIndex; // �̸����� ���� �˻�
    ItemType stringToItemType(const std::string& typeStr) const;
    ItemTier stringToItemTier(const std::string& tierStr) const;
    // ���ڿ��� enum���� ��ȯ�ϴ� ���� �Լ�
public:
    //������
    ItemDataBase();
    //��Ʈ ������ �ʱ�ȭ
    void initializeItemData();

    // ������ ���� �Լ�
    Item* createItem(const std::string& itemName) const;
    Item* createItem(int index) const;

    //������ ������ ��ȸ
    const ItemData* getItemData(const std::string& itemName) const;
    const ItemData* getItemData(int index) const;
    int getItemCount() const;

    //Ư�� Ÿ���� �����۵� �������� �ڵ�
    std::vector<Item*> getItemsByType(ItemType type) const;
    std::vector<Item*> getItemsByTier(ItemTier tier) const;

    // ��ü ������ ��� ���(������)
    void printAllItems() const; // ��Ÿ ����: pritntAllItems -> printAllItems
    // ������
    std::vector<Item*> getShopItems(int maxPrice = INT_MAX) const;

    Item* getRandomItem() const; // ���� ������ ���� �Լ�(���� �����)
};