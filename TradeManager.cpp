#include "TradeManager.h"
#include <iostream>
#include <limits>
TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}
void TradeManager::buyItem(Character* c, Shop& shop, int maxPrice)
{
	std::cout << "�����Ͻ� �������� ��ȣ�� �Է��� �ּ��� :        (������ : -1)" << std::endl;
	int itemListIndex = -1;
	while (true)
	{
		std::cin >> itemListIndex;
		if (std::cin.fail() || itemListIndex < -1 || itemListIndex > 8/*�ӽ��ϵ��ڵ�������*/)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
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
		std::cout << "��ȿ���� ���� �������Դϴ�." << std::endl;
		return;
	}
	if (itemToBuy->getPrice() > c->getGold())
	{
		std::cout << "��尡 �����մϴ�." << std::endl;
		delete itemToBuy;
	}
	else if (c->getInventory().size() >= 10)
	{
		std::cout << "�κ��丮�� ���� á���ϴ�." << std::endl;
		delete itemToBuy;
	}
	else
	{
		c->removeGold(itemToBuy->getPrice());
		c->addItem(itemToBuy);
		std::cout << "������ ���� �Ϸ�: " << itemToBuy->getName() << std::endl;
	}
}
void TradeManager::sellItem(Character* c)
{
	c->showInventory();
	if (c->getInventory().empty()) {
		std::cout << "�Ǹ��� �������� �����ϴ�." << std::endl;
		return;
	}
	std::cout << "�Ǹ��� �������� ��ȣ�� �Է��� �ּ��� (���: -1): ";
	int invenIndex = -1;
	while (true)
	{
		std::cin >> invenIndex;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
		}
		else if (invenIndex < -1 || invenIndex >= static_cast<int>(c->getInventory().size()))
		{
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
		}
		else
		{
			break;
		}
	}
	if (invenIndex == -1)
	{
		std::cout << "������ �ǸŸ� ����߽��ϴ�." << std::endl;
	}
	else if (invenIndex >= 0 && invenIndex < static_cast<int>(c->getInventory().size()))
	{
		Item* itemToSell = c->getInventory()[invenIndex];
		double sellPrice = itemToSell->getPrice() * 0.6;
		c->addGold(static_cast<int>(sellPrice));
		c->removeItem(invenIndex);
		std::cout << "������ �Ǹ� �Ϸ�! " << static_cast<int>(sellPrice) << " ��带 ������ϴ�." << std::endl;
	}
}
void TradeManager::showShopItems(Character* c, Shop& shop, int maxPrice) const {
	shop.displayShopItems(maxPrice);
	std::cout << "               ���� ��� : " << c->getGold() << " G" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
}