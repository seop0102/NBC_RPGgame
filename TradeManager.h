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

    // 아이템 구매: ItemDataBase에서 생성된 Item*를 받아옴
    void buyItem(Character* c, Shop& shop, int maxPrice = INT_MAX);

    // 아이템 판매
    void sellItem(Character* c);

    // 상점 아이템 목록 보여주기 
    void showShopItems(Character* c, Shop& shop, int maxPrice = INT_MAX) const;
};

