#include "TradeManager.h"
#include <iostream>
#include <limits>

TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character& c, Shop& shop, int itemIndex, int maxPrice)
{
	Item* itemToBuy = shop.getSelectedItemForPurchase(itemIndex);

	if (!itemToBuy) {
		std::cout << "유효하지 않은 아이템입니다." << std::endl;
		return;
	}

	if (itemToBuy->getPrice() > c.getGold())
	{
		std::cout << "골드가 부족합니다." << std::endl;
		delete itemToBuy;
	}
	else if (c.getInventory().size() >= 10)
	{
		std::cout << "인벤토리가 가득 찼습니다." << std::endl;
		delete itemToBuy;
	}
	else
	{
		c.removeGold(itemToBuy->getPrice());
		c.addItem(itemToBuy);
		std::cout << "아이템 구매 완료: " << itemToBuy->getName() << std::endl;
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

void TradeManager::showShopItems(Shop& shop, int maxPrice) const {
	shop.displayShopItems(maxPrice);
}