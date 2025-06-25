#pragma once

#include "Character.h"
#include "Item.h"
#include "ItemDataBase.h" // ItemDataBase를 사용하므로 추가
#include <vector>
#include <iostream>       // std::cout, std::cin 사용을 위해 추가
#include <limits>         // std::numeric_limits를 위해 추가

class TradeManager
{
private:
    ItemDataBase itemDB; // 아이템 데이터베이스 객체

public:
    TradeManager();
    ~TradeManager();

    // 아이템 구매: ItemDataBase에서 생성된 Item*를 받아옴
    void buyItem(Character& c, Item* item); // raw pointer

    // 아이템 판매
    void sellItem(Character& c);

    // 상점 아이템 목록 보여주기 (여기서 생성된 아이템은 호출자가 책임지고 해제해야 함)
    void showShopItems(int maxPrice = INT_MAX) const;
};

