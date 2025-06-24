#pragma once
#include"Item.h"
#include "Character.h"

class Armor:public Item
{
private:
	int defenseBonus;
	int maxHealthBonus;

public:
	//생성자
	Armor(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price);

	
	// 순수 가상함수
	std::string getEffect() const override;
	bool canUse() const override;
	std::string getItemType() const override;

	// 사용함수
	void use(Character& character)override;

	//Getter
	int getDefenseBonus() const;
	int getMaxHealthBonus() const;
	

};