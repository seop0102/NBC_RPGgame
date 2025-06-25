#include "TradeManager.h"
#include <iostream>
#include <limits>

TradeManager::TradeManager() : itemDB() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character &c, Item* item)
{
	if (!item) { // 유효한 아이템인지 확인
		std::cout << "유효하지 않은 아이템입니다." << std::endl;
		return;
	}

	if (item->getPrice() > c.getGold())
	{
		std::cout << "골드가 부족합니다." << std::endl;
		delete item; 
	}
	else if (c.getInventory().size() >= 10)
	{
		std::cout << "인벤토리가 가득 찼습니다." << std::endl;
		delete item; 
	}
	else
	{
		c.removeGold(item->getPrice()); // 골드 먼저 차감
		c.addItem(item); // Character가 아이템 포인터의 소유권을 가집니다.
		std::cout << "아이템 구매 완료: " << item->getName() << std::endl;
	}
}

void TradeManager::sellItem(Character& c)
{
	c.showInventory();
	if (c.getInventory().empty()) {
		std::cout << "판매할 아이템이 없습니다." << std::endl;
		return;
	}

	std::cout << "판매할 아이템의 번호를 입력해 주세요 (취소: -1): ";
	int invenIndex = -1;
	while (true)
	{
		std::cin >> invenIndex;
		if (std::cin.fail() || (invenIndex < -1 || invenIndex >= c.getInventory().size()))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else if (invenIndex == -1) {
			std::cout << "아이템 판매를 취소했습니다." << std::endl;
			break;
		}
		else
		{
			Item* itemToSell = c.getInventory()[invenIndex];
			double sellPrice = itemToSell->getPrice() * 0.6;
			c.addGold(static_cast<int>(sellPrice));
			c.removeItem(invenIndex); 
			std::cout << "아이템 판매 완료! " << static_cast<int>(sellPrice) << " 골드를 얻었습니다." << std::endl;
			break;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TradeManager::showShopItems(int maxPrice) const {
	std::cout << "-------- 상점 아이템 --------" << std::endl;
	std::vector<Item*> shopItems = itemDB.getShopItems(maxPrice); // ItemDataBase에서 아이템 생성

	if (shopItems.empty()) {
		std::cout << "현재 상점에 아이템이 없습니다." << std::endl;
	}
	else {
		for (size_t i = 0; i < shopItems.size(); ++i) {
			std::cout << "[" << i << "] " << shopItems[i]->getItemInfo() << std::endl;
		}
	}
	std::cout << "--------------------------" << std::endl;

	// showShopItems에서 생성된 아이템들은 이 함수가 끝나면 메모리 해제해야 합니다.
	for (Item* item : shopItems) {
		delete item;
	}
	shopItems.clear();
}
