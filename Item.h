#pragma once
#include<string>

class Character;

enum class ItemTier // ������ ���
{
	NORMAL, // �Ϲ�
	RARE,  // �߱�
	EPIC   // ���
};

class Item
{
protected: // private>protected �� �ؼ� ��Ӱ����ϰԲ�
	std::string name;
	std::string description;
	ItemTier tier;
	int price;
	bool isEquipped;

public:
	//������
	Item(const std::string& name, ItemTier tier, int price);

	// ���� �Ҹ���
	virtual~Item() = default;

	//���������Լ�(�������̽�)
	virtual std::string getEffect() const = 0; // ������ ȿ�� ����
	virtual bool canUse() const = 0;
	virtual std::string getItemType() const = 0; // ������ Ÿ�� ���ڿ� 
	//virtual void use() = 0; // ������ ���->ĳ���Ϳ��� �Ѵٰ���

	//����Լ�
	virtual void use(Character& character) = 0;

	//getter �Լ�
	std::string getName() const;
	std::string getDescription() const;
	ItemTier getTier() const;
	int getPrice() const;
	bool getIsEquipped() const;

	//setter �Լ�
	void setName(const std::string& name);
	void setPrice(int price);
	void setEquipped(bool equipped);

	// ��ƿ��Ƽ? ���������� �� ���� �Լ�
	std::string getTierString() const;
	std::string getItemInfo() const;


};