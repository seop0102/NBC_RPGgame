#pragma once

#include "Character.h"
#include "Item.h"
#include <vector>

using namespace std;

class TradeManager
{

public :
	TradeManager();
	~TradeManager();
	void buyItem(Character &c, Item* item);
	void sellItem(Character &c);


};

