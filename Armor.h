#pragma once
#include"Item.h"
#include "Character.h"

class Armor:public Item
{
private:
	int defenseBonus;
	int maxHealthBonus;

public:
	//������
	Armor(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price);

	
	// ���� �����Լ�
	std::string getEffect() const override;
	bool canUse() const override;
	std::string getItemType() const override;

	// ����Լ�
	void use(Character& character)override;

	//Getter
	int getDefenseBonus() const;
	int getMaxHealthBonus() const;
	

};