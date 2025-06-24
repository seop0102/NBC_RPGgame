#pragma once

#include "Item.h"
#include <vector>

using namespace std;

class Shop {



private:
	vector<Item*> items;





public:
	Shop();
	~Shop();
	Item* displayItems();





};