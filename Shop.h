#pragma once

#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "ItemDataBase.h" // ItemDataBase Ŭ���� ���Ǹ� ���� �ʿ�
#include <vector>
#include <string>
#include <iostream>

class Shop {
private:
    std::string shopName;
    ItemDataBase itemDB; // ������ �Ǹ��� ������ �����͸� �����ϴ� �����ͺ��̽�

    ItemType stringToItemType(const std::string& typeStr) const { return itemDB.stringToItemType(typeStr); }
    ItemTier stringToItemTier(const std::string& tierStr) const { return itemDB.stringToItemTier(tierStr); }

public:
    Shop(std::string name);
    ~Shop();

    std::string getName() const;

    void displayShopItems(int maxPrice = INT_MAX) const;
    Item* getSelectedItemForPurchase(int index, int maxPrice = INT_MAX) const;
};