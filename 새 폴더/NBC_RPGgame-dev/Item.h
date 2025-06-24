#pragma once
#include<string>

enum class ItemType //아이템 종류
{
	WEAPON,// 무기
	ARMOR, // 방어구
	EDIBLE // 소모품(체력 포션이나 공격력 포션)
};

enum class ItemTier // 아이템 등급
{
	NORAML, // 일반
	RARE,  // 중급
	EPIC   // 고급
};

class Item
{
protected: // private>protected 로 해서 상속가능하게끔
	std::string name;
	std::string description;
	ItemType type;
	ItemTier tier;
	int price;

	//효과 관련(회복,공격력,방어력,스킬사용횟수, 장비 착용여부)
	int healthRecover; // 회복물약의 체력 회복
	int attackBonus;  // 공격력( 무기나 attack boost)
	int defenseBonus;  //방어력
	int skillCharges;   // 스킬 사용 횟수
	int maxHealthBonus; // 최대 체력 증가
	bool isEquipped;   // 장비 장착 했는지 여부

public:
	//생성자
	Item(const std::string& name, ItemType type, ItemTier tier,
		int healthRecover = 0, int skillCharges = 0, int attackBonus = 0,
		int defenseBonus = 0, int maxHealthBonus = 0, int price = 0);

	// 가상 소멸자
	virtual~Item() = default;

	//순수가상함수(인터페이스)
	virtual void use() = 0; // 아이템 사용
	virtual std::string getEffect() const = 0; // 아이템 효과 설명
	virtual bool canUse() const = 0; // 사용 가능 여부

	//getter 함수
	std::string getName()const;
	std::string getDescription()const;
	ItemType getType()const;
	ItemTier getTier()const;
	int getPrice()const;
	int getHealthRecover()const;
	int getAttackBonus()const;
	int getDefenseBonus()const;
	int getSkillCharges()const;
	int getMaxHealthBonus()const;
	bool getIsEquipped()const;

	//setter 함수
	void setName(const std::string& name);
	void setEquipped(bool equipped);
	void setPrice(int price);

	// 유틸리티? 아이템정보 및 가격 함수
	std::string getTypeString()const;
	std::string getTierString()const;
	std::string getIteminfo()const; // 상점에서 보여줄 아이템 정보
};

//구체적인 아이템 클래스
// 소모품
class EdibleItem : public Item
{
public: // 소모품에서 방어력 증가와 최대 체력 증가 없음
	EdibleItem(const std::string& name, ItemTier tier, int healthRecover, int skillCharges,
		int attakBonus, int price);

	//순수가상함수 부분
	void use() override;
	std::string getEffect() const override;
	bool canUse() const override;
};

// 아이템-무기
class WeaponItem :public Item
{
public:
	WeaponItem(const std::string& name, ItemTier tier, int attackBonus, int price);

	// 순수가상함수 부분
	void use() override;
	std::string getEffect()const override;
	bool canUse() const override;
};

// 아이템-방어구
class ArmorItem :public Item
{
public:
	ArmorItem(const std::string& name, ItemTier tier, int defenseBonus, int maxHealthBonus, int price);

	//순수가상함수 부분
	void use() override;
	std::string getEffect() const override;
	bool canUse() const override;
};