#pragma once
#pragma once

#include <iostream>

class ShopManager
{
public:
	ShopManager() = default;
	~ShopManager() = default;

	void openShop() {

		std::cout << "��������" << std::endl;
	}

	void buyItem();
	void sellItem();
};