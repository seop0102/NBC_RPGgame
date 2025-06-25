#pragma once
#include "Item.h"

class Character;

class Weapon:public Item
{
private:
	int attackBonus;

public:
	// ������
	Weapon(const std::string& name, ItemTier tier, int attackBonus, int price, bool isEquipped);

	//���� �����Լ�
	std::string getEffect() const override;
	bool canUse() const override;
	std::string getItemType() const override;

	
	// ��� �Լ�
	void use(Character& character) override;
	
	//Getter �Լ�
	int getAttackBonus() const;

};