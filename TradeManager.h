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
    void buyItem(Character& c, Shop& shop, int itemIndex, int maxPrice);

    // ������ �Ǹ�
    void sellItem(Character& c);

    // ���� ������ ��� �����ֱ� 
    void showShopItems(Shop& shop, int maxPrice) const;
};

