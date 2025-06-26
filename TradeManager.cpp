#include "TradeManager.h"
#include <iostream>
#include <limits>
TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}
void TradeManager::buyItem(Character* c, Shop& shop, int maxPrice)
{
	std::cout << "구매하실 아이템의 번호를 입력해 주세요 :        (나가기 : -1)" << std::endl;
	int itemListIndex = -1;
	while (true)
	{
		std::cin >> itemListIndex;
		if (std::cin.fail() || itemListIndex < -1 || itemListIndex > 8/*임시하드코딩사이즈*/)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else
		{
			break;
		}
	}
	if (itemListIndex == -1)
	{
		return;
	}
	Item* itemToBuy = shop.getSelectedItemForPurchase(itemListIndex);
	if (!itemToBuy) {
		std::cout << "유효하지 않은 아이템입니다." << std::endl;
		return;
	}
	if (itemToBuy->getPrice() > c->getGold())
	{
		std::cout << "골드가 부족합니다." << std::endl;
		delete itemToBuy;
	}
	else if (c->getInventory().size() >= 10)
	{
		std::cout << "인벤토리가 가득 찼습니다." << std::endl;
		delete itemToBuy;
	}
	else
	{
		c->removeGold(itemToBuy->getPrice());
		c->addItem(itemToBuy);
		std::cout << "아이템 구매 완료: " << itemToBuy->getName() << std::endl;
	}
}
void TradeManager::sellItem(Character* c)
{
	c->showInventory();
	if (c->getInventory().empty()) {
		std::cout << "판매할 아이템이 없습니다." << std::endl;
		return;
	}
	std::cout << "판매할 아이템의 번호를 입력해 주세요 (취소: -1): ";
	int invenIndex = -1;
	while (true)
	{
		std::cin >> invenIndex;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else if (invenIndex < -1 || invenIndex >= static_cast<int>(c->getInventory().size()))
		{
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else
		{
			break;
		}
	}
	if (invenIndex == -1)
	{
		std::cout << "아이템 판매를 취소했습니다." << std::endl;
	}
	else if (invenIndex >= 0 && invenIndex < static_cast<int>(c->getInventory().size()))
	{
		Item* itemToSell = c->getInventory()[invenIndex];
		double sellPrice = itemToSell->getPrice() * 0.6;
		c->addGold(static_cast<int>(sellPrice));
		c->removeItem(invenIndex);
		std::cout << "아이템 판매 완료! " << static_cast<int>(sellPrice) << " 골드를 얻었습니다." << std::endl;
	}
}
void TradeManager::showShopItems(Character* c, Shop& shop, int maxPrice) const {
	shop.displayShopItems(maxPrice);
	std::cout << "               보유 골드 : " << c->getGold() << " G" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
}