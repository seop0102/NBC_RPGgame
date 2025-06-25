#pragma once
#include"Item.h"
#include "Character.h"

class Consumable :public Item
{
private:
	int healthRecover;
	int skillCharges;
	int attackBonus; // 임시 공격력 증가도 포함
	
public:
    // 생성자
    Consumable(const std::string& name, ItemTier tier, int healthRecover,
        int skillCharges, int attackBonus, int price, bool isEquipped);

    // 순수 가상 함수 구현
    std::string getEffect() const override;
    bool canUse() const override;
    std::string getItemType() const override;

    // 사용 함수
    void use(Character& character) override;

    // Getter
    int getHealthRecover() const;
    int getSkillCharges() const;
    int getAttackBonus() const;
};