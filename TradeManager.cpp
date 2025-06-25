#include "TradeManager.h"
#include <iostream>
#include <limits>

TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character& c, Shop& shop, int itemIndex, int maxPrice)
{
	Item* itemToBuy = shop.getSelectedItemForPurchase(itemIndex);

	if (!itemToBuy) {
		std::cout << "��ȿ���� ���� �������Դϴ�." << std::endl;
		return;
	}

	if (itemToBuy->getPrice() > c.getGold())
	{
		std::cout << "��尡 �����մϴ�." << std::endl;
		delete itemToBuy;
	}
	else if (c.getInventory().size() >= 10)
	{
		std::cout << "�κ��丮�� ���� á���ϴ�." << std::endl;
		delete itemToBuy;
	}
	else
	{
		c.removeGold(itemToBuy->getPrice());
		c.addItem(itemToBuy);
		std::cout << "������ ���� �Ϸ�: " << itemToBuy->getName() << std::endl;
	}
}

void TradeManager::sellItem(Character& c)
{
	c.showInventory();
	if (c.getInventory().empty()) {
		std::cout << "�Ǹ��� �������� �����ϴ�." << std::endl;
		return;
	}

	std::cout << "�Ǹ��� �������� ��ȣ�� �Է��� �ּ��� (���: -1): ";
	int invenIndex = -1;
	while (true)
	{
		std::cin >> invenIndex;
		if (std::cin.fail() || (invenIndex < -1 || invenIndex >= c.getInventory().size()))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
		}
		else if (invenIndex == -1) {
			std::cout << "������ �ǸŸ� ����߽��ϴ�." << std::endl;
			break;
		}
		else
		{
			Item* itemToSell = c.getInventory()[invenIndex];
			double sellPrice = itemToSell->getPrice() * 0.6;
			c.addGold(static_cast<int>(sellPrice));
			c.removeItem(invenIndex);
			std::cout << "������ �Ǹ� �Ϸ�! " << static_cast<int>(sellPrice) << " ��带 ������ϴ�." << std::endl;
			break;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void TradeManager::showShopItems(Shop& shop, int maxPrice) const {
	shop.displayShopItems(maxPrice);
}