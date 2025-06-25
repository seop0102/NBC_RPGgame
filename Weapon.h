#pragma once
#include "Item.h"

class Character;

class Weapon:public Item
{
private:
	int attackBonus;

public:
	// 생성자
	Weapon(const std::string& name, ItemTier tier, int attackBonus, int price, bool isEquipped);

	//순수 가상함수
	std::string getEffect() const override;
	bool canUse() const override;
	std::string getItemType() const override;

	
	// 사용 함수
	void use(Character& character) override;
	
	//Getter 함수
	int getAttackBonus() const;

};