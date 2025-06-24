#include "TradeManager.h"

TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character &c, Item* item)
{
	if (item->getPrice() > c.getGold())
	{
		cout << "gold가 부족합니다." << endl;
	}
	else if (c.getInventory().size() >= 10)
	{
		cout << "인벤토리가 가득 찼습니다." << endl;
	}
	else
	{
		c.getInventory().push_back(item);
		c.setGold(c.getGold() - item->getPrice());
		cout << "아이템 구매 완료" << endl;
	}
}

void TradeManager::sellItem(Character& c)
{
	c.showInventory();
	cout << "판매할 아이템의 번호를 입력해 주세요 : ";
	int invenIndex = -1;
	while (true)
	{
		cin >> invenIndex;
		if (cin.fail() || invenIndex >= c.getInventory().size())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
		}
		else
		{
			c.setGold(c.getGold() + c.getInventory()[invenIndex]->getPrice() * 0.6);
			c.getInventory().erase(c.getInventory().begin() + invenIndex);
			cout << "아이템 판매 완료" << endl;
			break;
		}
	}

}
