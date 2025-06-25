#pragma once

#include "Character.h"
#include "Item.h"
#include "Shop.h" 
#include <vector>
#include <iostream>     
#include <limits>         

class TradeManager
{
private:

public:
    TradeManager();
    ~TradeManager();

    // ������ ����: ItemDataBase���� ������ Item*�� �޾ƿ�
    void buyItem(Character* c, Shop& shop, int maxPrice = INT_MAX);

    // ������ �Ǹ�
    void sellItem(Character* c);

    // ���� ������ ��� �����ֱ� 
    void showShopItems(Character* c, Shop& shop, int maxPrice = INT_MAX) const;
};

