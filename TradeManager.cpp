#include "TradeManager.h"

TradeManager::TradeManager() {}
TradeManager::~TradeManager() {}

void TradeManager::buyItem(Character &c, Item* item)
{
	if (item->getPrice() > c.getGold())
	{
		cout << "gold�� �����մϴ�." << endl;
	}
	else if (c.getInventory().size() >= 10)
	{
		cout << "�κ��丮�� ���� á���ϴ�." << endl;
	}
	else
	{
		c.getInventory().push_back(item);
		c.setGold(c.getGold() - item->getPrice());
		cout << "������ ���� �Ϸ�" << endl;
	}
}

void TradeManager::sellItem(Character& c)
{
	c.showInventory();
	cout << "�Ǹ��� �������� ��ȣ�� �Է��� �ּ��� : ";
	int invenIndex = -1;
	while (true)
	{
		cin >> invenIndex;
		if (cin.fail() || invenIndex >= c.getInventory().size())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
		}
		else
		{
			c.setGold(c.getGold() + c.getInventory()[invenIndex]->getPrice() * 0.6);
			c.getInventory().erase(c.getInventory().begin() + invenIndex);
			cout << "������ �Ǹ� �Ϸ�" << endl;
			break;
		}
	}

}
