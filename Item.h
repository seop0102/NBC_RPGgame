#pragma once
#include<string>

class Character;

enum class ItemTier // 아이템 등급
{
	NORMAL, // 일반
	RARE,  // 중급
	EPIC   // 고급
};

class Item
{
protected: // private>protected 로 해서 상속가능하게끔
	std::string name;
	std::string description;
	ItemTier tier;
	int price;
	bool isEquipped;

public:
	//생성자
	Item(const std::string& name, ItemTier tier, int price);

	// 가상 소멸자
	virtual~Item() = default;

	//순수가상함수(인터페이스)
	virtual std::string getEffect() const = 0; // 아이템 효과 설명
	virtual bool canUse() const = 0;
	virtual std::string getItemType() const = 0; // 아이탬 타입 문자열 
	//virtual void use() = 0; // 아이템 사용->캐릭터에서 한다고함

	//사용함수
	virtual void use(Character& character) = 0;

	//getter 함수
	std::string getName() const;
	std::string getDescription() const;
	ItemTier getTier() const;
	int getPrice() const;
	bool getIsEquipped() const;

	//setter 함수
	void setName(const std::string& name);
	void setPrice(int price);
	void setEquipped(bool equipped);

	// 유틸리티? 아이템정보 및 가격 함수
	std::string getTierString() const;
	std::string getItemInfo() const;


};