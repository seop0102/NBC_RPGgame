#include "Item.h"
#include<iostream>

// 생성자
Item::Item(const std::string& name, ItemType type, ItemTier tier,
	int healthRecover, int skillCharges, int attackBonus,
	int defenseBonus, int maxHealthBonus, int price)
	:name(name), type(type), tier(tier), healthRecover(healthRecover), skillCharges(skillCharges),
	attackBonus(attackBonus), defenseBonus(defenseBonus), maxHealthBonus(maxHealthBonus),
	price(price), isEquipped(false) {
}
// getter 함수
std::string Item::getName()const
{
	return name;
}
std::string Item::getDescription()const
{
	return description;
}
ItemType Item::getType() const
{
	return type;
}
ItemTier Item::getTier() const
{
	return tier;
}
int Item::getHealthRecover() const
{
	return healthRecover;
}
int Item::getAttackBonus() const
{
	return attackBonus;
}

int Item::getDefenseBonus() const
{
	return defenseBonus;
}

int Item::getSkillCharges() const
{
	return skillCharges;
}

int Item::getMaxHealthBonus()const
{
	return maxHealthBonus;
}

int Item::getPrice() const
{
	return price;
}

bool Item::getIsEquipped() const
{
	return isEquipped;
}

// setter 함수
void Item::setName(const std::string& name)
{
	this->name = name;
}
void Item::setEquipped(bool equipped)
{
	this->isEquipped = equipped;
}
void Item::setPrice(int price)
{
	this->price = price;
}

//유틸리티? 아이템 상점 정보 관련 함수

std::string Item::getTypeString()const
{
	switch (type)
	{
	case ItemType::WEAPON:return "무기";
	case ItemType::ARMOR:return"방어구";
	case ItemType::EDIBLE:return "소모품";
	default:return "알 수 없음";
	}

}

std::string Item::getTierString()const
{
	switch (tier)
	{
	case ItemTier::NORAML:return"일반";
	case ItemTier::RARE:return"중급";
	case ItemTier::EPIC:return"고급";
	default:return "알 수 없음";

	}
}
std::string Item::getIteminfo() const
{
	std::string info = name + "(" + getTierString() + ")-";

	if (type == ItemType::EDIBLE)// 소모품인 경우(회복물약,공격력 부스트)
	{
		if (healthRecover > 0)info += "체력 회복 +" + std::to_string(healthRecover) + " ";
		if (skillCharges > 0) info += "스킬 사용 횟수 +" + std::to_string(skillCharges) + " ";
		if (attackBonus > 0)info += "임시 공격력 +" + std::to_string(attackBonus) + " ";
	}
	else // 장비(무기, 방어구인 경우)
	{
		if (attackBonus > 0)info += "공격력 +" + std::to_string(attackBonus) + " ";
		if (defenseBonus > 0)info += "방어력 +" + std::to_string(defenseBonus) + " ";
		if (maxHealthBonus > 0)info += "최대 체력 +" + std::to_string(maxHealthBonus) + " ";
	}

	info += "- " + std::to_string(price) + " gold";
	return info;
}
// Edible Item 상세
EdibleItem::EdibleItem(const std::string& name, ItemTier tier, int healthRecover, int skilCharges,
	int attackBonus, int price)
	:Item(name, ItemType::EDIBLE, tier, healthRecover, skillCharges, attackBonus, 0, 0, price)
	// tier 이후부터 각각 healthRecover, skillCharges, attackBonus, defenseBonus, maxHealthBonus, price
	// 소모품은 방어력, 최대 체력 증가 없음!
{
}
void EdibleItem::use()
{
	std::cout << name << "을(를) 사용했습니다!" << std::endl;
	// 실제 사용 효과는 게임매니저나 캐릭터에서 하셔야할듯..
}
std::string EdibleItem::getEffect()const
{
	std::string effect = "";
	if (healthRecover > 0) effect += "체력 회복 +" + std::to_string(healthRecover) + " ";
	if (skillCharges > 0) effect += "스킬 사용 횟수 +" + std::to_string(skillCharges) + " ";
	if (attackBonus > 0) effect += "임시 공격력+" + std::to_string(attackBonus) + " ";
	return effect;
}
bool EdibleItem::canUse()const
{
	return true; // 소모품은 항상 사용 가능하게끔
}
// Weapon Item 상세
WeaponItem::WeaponItem(const std::string& name, ItemTier tier, int attackBonus, int price)
	:Item(name, ItemType::WEAPON, tier, 0, 0, attackBonus, 0, 0, price)
	// 무기는 체력 회복, 스킬사용횟수,방어력,최대체력 증가 없음!
{
}
void WeaponItem::use()
{
	if (!isEquipped)
	{
		isEquipped = true;
		std::cout << name << "을(를) 장착했습니다!" << std::endl;
	}
	else
	{
		std::cout << name << "은(는) 이미 장착중입니다!" << std::endl;
	}
}
std::string WeaponItem::getEffect()const
{
	return"공격력 +" + std::to_string(attackBonus);
}
bool WeaponItem::canUse()const
{
	return !isEquipped;//무기는 장착되지 않았을 때만 사용 가능
}

// Armor Item 상세
ArmorItem::ArmorItem(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price)
	:Item(name, ItemType::ARMOR, tier, 0, 0, 0, defenseBonus, maxHealthBonus, price)
	// 방어구는 체력 회복, 스킬사용횟수,공격력 없음!
{
}
void ArmorItem::use()
{
	if (!isEquipped)
	{
		isEquipped = true;
		std::cout << name << "을(를) 장착했습니다!" << std::endl;
	}
	else
	{
		std::cout << name << "은(는) 이미 장착중입니다!" << std::endl;
	}
}
std::string ArmorItem::getEffect()const
{
	std::string effect = "";
	if (defenseBonus > 0) effect += "방어력 +" + std::to_string(defenseBonus) + " ";
	if (maxHealthBonus > 0) effect += "최대 체력+" + std::to_string(maxHealthBonus) + " ";
	return effect;
}
bool ArmorItem::canUse() const
{
	return !isEquipped; //방어구는 장착되지 않았을 ??만 사용 가능
}
//
// 사용 예시
// EdibleItem* healthPotion = new EdibleItem("체력 물약", ItemTier::NORMAL, 100, 2, 0, 1100)
// WeaponItem* sword = new WeaponItem("철검", ItemTier::RARE, 15, 2000);
// ArmorItem* lightArmor= nwe ArmorItem("가죽",ItemTier::EPIC,10,3,6000);
// 
// 