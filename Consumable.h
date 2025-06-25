#pragma once
#include"Item.h"
#include "Character.h"

class Consumable :public Item
{
private:
	int healthRecover;
	int skillCharges;
	int attackBonus; // �ӽ� ���ݷ� ������ ����
	
public:
    // ������
    Consumable(const std::string& name, ItemTier tier, int healthRecover,
        int skillCharges, int attackBonus, int price, bool isEquipped);

    // ���� ���� �Լ� ����
    std::string getEffect() const override;
    bool canUse() const override;
    std::string getItemType() const override;

    // ��� �Լ�
    void use(Character& character) override;

    // Getter
    int getHealthRecover() const;
    int getSkillCharges() const;
    int getAttackBonus() const;
};