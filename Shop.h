#pragma once

#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "ItemDataBase.h" // ItemDataBase 클래스 정의를 위해 필요
#include <vector>
#include <string>
#include <iostream>

class Shop {
private:
    std::string shopName;
    ItemDataBase itemDB; // 상점이 판매할 아이템 데이터를 제공하는 데이터베이스

    ItemType stringToItemType(const std::string& typeStr) const { return itemDB.stringToItemType(typeStr); }
    ItemTier stringToItemTier(const std::string& tierStr) const { return itemDB.stringToItemTier(tierStr); }

public:
    Shop(std::string name);
    ~Shop();

    std::string getName() const;

    void displayShopItems(int maxPrice = INT_MAX) const;
    Item* getSelectedItemForPurchase(int index, int maxPrice = INT_MAX) const;
};