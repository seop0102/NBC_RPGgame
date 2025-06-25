#pragma once

#include "Character.h"
#include "Item.h"
#include "ItemDataBase.h" // ItemDataBase�� ����ϹǷ� �߰�
#include <vector>
#include <iostream>       // std::cout, std::cin ����� ���� �߰�
#include <limits>         // std::numeric_limits�� ���� �߰�

class TradeManager
{
private:
    ItemDataBase itemDB; // ������ �����ͺ��̽� ��ü

public:
    TradeManager();
    ~TradeManager();

    // ������ ����: ItemDataBase���� ������ Item*�� �޾ƿ�
    void buyItem(Character& c, Item* item); // raw pointer

    // ������ �Ǹ�
    void sellItem(Character& c);

    // ���� ������ ��� �����ֱ� (���⼭ ������ �������� ȣ���ڰ� å������ �����ؾ� ��)
    void showShopItems(int maxPrice = INT_MAX) const;
};

