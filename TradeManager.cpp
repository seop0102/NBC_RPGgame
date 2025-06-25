#include "TradeManager.h"
#include <iostream>
#include <limits>

TradeManager::TradeManager() : itemDB() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character &c, Item* item)
{
	if (!item) { // ��ȿ�� ���������� Ȯ��
		std::cout << "��ȿ���� ���� �������Դϴ�." << std::endl;
		return;
	}

	if (item->getPrice() > c.getGold())
	{
		std::cout << "��尡 �����մϴ�." << std::endl;
		delete item; 
	}
	else if (c.getInventory().size() >= 10)
	{
		std::cout << "�κ��丮�� ���� á���ϴ�." << std::endl;
		delete item; 
	}
	else
	{
		c.removeGold(item->getPrice()); // ��� ���� ����
		c.addItem(item); // Character�� ������ �������� �������� �����ϴ�.
		std::cout << "������ ���� �Ϸ�: " << item->getName() << std::endl;
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

void TradeManager::showShopItems(int maxPrice) const {
	std::cout << "-------- ���� ������ --------" << std::endl;
	std::vector<Item*> shopItems = itemDB.getShopItems(maxPrice); // ItemDataBase���� ������ ����

	if (shopItems.empty()) {
		std::cout << "���� ������ �������� �����ϴ�." << std::endl;
	}
	else {
		for (size_t i = 0; i < shopItems.size(); ++i) {
			std::cout << "[" << i << "] " << shopItems[i]->getItemInfo() << std::endl;
		}
	}
	std::cout << "--------------------------" << std::endl;

	// showShopItems���� ������ �����۵��� �� �Լ��� ������ �޸� �����ؾ� �մϴ�.
	for (Item* item : shopItems) {
		delete item;
	}
	shopItems.clear();
}
