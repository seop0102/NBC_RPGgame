#pragma once

#include<string>
#include<vector>
#include<iostream>
#include<map> 
#include "Item.h"
#include "Weapon.h"
#include "Consumable.h"
#include "ICombatant.h"

#include "IClass.h"

class Monster;
class Armor;

class Character : public ICombatant {
private:
	std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int defense;

	int criticalChance;
	int hitChance;
	int dodgeChance; // 회피율

	int exp;
	int gold;

	Weapon* equippedWeapon;
	Armor* equippedArmor; // 장착된 방어구

	std::vector<Item*> inventory;

	// 직업 객체 
	//std::unique_ptr<IClass> characterClass;
	IClass* characterClass;

	// 스킬 사용 횟수
	std::map<std::string, int> skillUsages;

	//스킬관련 변수
	bool isAimed; // 궁수, 조준 (다음 공격 명중률 증가)
	int wraithArrowDamage; // 궁수, 망령 화살 (다음 턴 공격 피해량 증가)

	bool isHiding; // 도적, 숨기 (1회성)

	bool isShielded; // 워리어, 방패 (턴당 1회)
	bool hasIndomitableWill; // 워리어 패시브 



public:
	Character(std::string name, IClass* selectedClass);
	virtual ~Character();
	IClass* getCharacterClass() const { return characterClass; }

	// ICombatant 인터페이스
	void takeDamage(int damage) override;
	int getAttack() const override { return attack; }
	int getHealth() const override { return health; }
	std::string getName() const override { return name; }
	int getDefense() const { return defense; } // 방어력 반환
	int getDodgeChance() const { return dodgeChance; } // 회피율 반환

	std::vector<std::string> getActiveSkills() const;
	void useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit);
	void applyPassiveSkill(Character& self);
	std::string getClassName() const;

	bool isAlive() const { return health > 0; } // 살았는지 죽었는지 확인

	// 캐릭터 기능
	void displayStat();
	void levelUp();

	// 골드 / 경험치 / 아이템 관리 
	void addGold(int amount);
	void addExp(int amount);
	void removeGold(int amount);

	// 인벤토리 관련
	void equipWeapon(Weapon* weapon);
	void equipArmor(Armor* armor);
	void useItem(int itemIndex); // 아이템 사용
	void addItem(Item* item);
	void removeItem(int index);
	void showInventory() const; // 인벤토리 출력

	// 트레이드매니저에서 인벤토리 접근할 수 있는 getter
	const std::vector<Item*>& getInventory() const { return inventory; } 
	Weapon* getEquippedWeapon() const { return equippedWeapon; }
	Armor* getEquippedArmor() const { return equippedArmor; }

	// 스킬 사용 횟수
	void initializeSkillUsages();
	void restoreSkillUsage(const std::string& skillName, int amount);
	void initializeSkillEffect();

	int getRemainingSkillUsage(const std::string& skillName) const;
	std::string getSkillName(const std::string& skillName) const; // 스킬 타입-> 이름 변환

	bool getIsAimed() const { return isAimed; } // 조준 상태 반환;
	void setIsAimed(bool aimed) { isAimed = aimed; } // 조준 상태 설정
	void setWraithArrowDamage(int val) { wraithArrowDamage = val; }
	int getWraithArrowDamage() const { return wraithArrowDamage; }

	void setIsHiding(bool val) { isHiding = val; }
	bool getIsHiding() const { return isHiding; } // 숨기 상태 설정

	void setIsShielded(bool val) { isShielded = val; }
	bool getIsShielded() const { return isShielded; }
	void setHasIndomitableWill(bool val) { hasIndomitableWill = val; }
	bool getHasIndomitableWill() const { return hasIndomitableWill; }


	// 게터 함수
	int getLevel() const { return level; }
	int getMaxHealth() const { return maxHealth; }
	int getExp() const { return exp; }
	int getGold() const { return gold; }
	int getHitChance() const { return hitChance; }
	int getCriticalChance() const { return criticalChance; }

	// 세터 함수
	void setHealth(int newHealth) { health = newHealth; }
	void setMaxHealth(int newMaxHealth) { maxHealth = newMaxHealth; }
	void setAttack(int newAttack) { attack = newAttack; }
	void setDefense(int newDefense) { defense = newDefense; }
	void setCriticalChance(int chance) { criticalChance = chance; }
	void setHitChance(int chance) { hitChance = chance; }
	void setDodgeChance(int chance) { dodgeChance = chance; }
	void setGold(int newGold) { gold = newGold; } // 도적 스킬에서 필요

};