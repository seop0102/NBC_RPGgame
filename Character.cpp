#include "Character.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "IClass.h"
#include "Utils.h"
#include "Monster.h"
#include "ICombatant.h"


#include <iostream>
#include <limits>
#include <algorithm>
#include <map>

Character::Character(std::string name, IClass* selectedClass)
	: name(name),
	level(1),
	health(200),
	maxHealth(200),
	attack(30),
	defense(0), // 기본 방어력 설정 (필요시)
	criticalChance(5), // 기본 치명타 확률 (필요시)
	hitChance(85), // 기본 명중률 설정 (필요시)
	dodgeChance(5), // 기본 회피율 설정 (필요시)
	exp(0),
	gold(0),
	equippedWeapon(nullptr), equippedArmor(nullptr)
{
	characterClass = selectedClass;
}

void Character::displayStat()
{
	std::cout << "--------상태 창--------" << std::endl;
	std::cout << "이름: " << name << std::endl;
	std::cout << "레벨: " << level << std::endl;
	std::cout << "체력: " << health << "/" << maxHealth << std::endl;
	std::cout << "공격력: " << attack << std::endl;
	std::cout << "경험치: " << exp << std::endl;
	std::cout << "골드: " << gold << std::endl;
	std::cout << "----------------------" << std::endl;
}

void Character::levelUp()
{
	const int MAX_LEVEL = 10;
	const int EXP_TO_NEXT_LEVEL = level * 100;

	if (level >= MAX_LEVEL) {
		std::cout << "10레벨에 도달했습니다!" << std::endl;
		return;
	}

	if (exp >= EXP_TO_NEXT_LEVEL) {
		level++;
		exp -= EXP_TO_NEXT_LEVEL;

		maxHealth += 20; // 최대 체력 증가
		health = maxHealth; // 체력 회복
		attack += 5; // 공격력 증가

		std::cout << "레벨 업 :" << level << "이(가) 되었습니다." << std::endl;
		std::cout << "최대 체력 +20, 공격력 +5 증가" << std::endl;
	}
	else {
		std::cout << "경험치가 부족합니다. 다음 레벨업 까지 " << (EXP_TO_NEXT_LEVEL - exp) << "경험치가 더 필요합니다." << std::endl;
	}
}

void Character::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
	}
}

// 골드 추가 함수
void Character::addGold(int amount)
{
	gold += amount;
	std::cout << amount << " G를 획득했습니다. 현재 골드: " << gold << std::endl;
}

// 경험치 추가 함수
void Character::addExp(int amount)
{
	exp += amount;
	std::cout << amount << " 경험치를 획득했습니다. 현재 경험치: " << exp << std::endl;
	// 경험치 획득 후 레벨업 체크
	levelUp();
}

// 골드 제거 함수
void Character::removeGold(int amount)
{
	if (gold >= amount) {
		gold -= amount;
		std::cout << amount << " G를 사용했습니다. 현재 골드: " << gold << std::endl;
	}
	else {
		std::cout << "골드가 부족합니다." << std::endl;
	}
}

// 아이템 추가 함수
void Character::addItem(Item* item)
{
	if (inventory.size() >= 10) { // 인벤토리 최대 10개 아이템
		showInventory();
		std::cout << "인벤토리가 가득 찼습니다. 다른 아이템을 버리시겠습니까?" << std::endl;

		//선택지 추가 예정
		int index = 0;
		item; // 아이템 정보 출력
		swap(item, inventory[index]); // 마지막 아이템과 교체

		delete item;

	}

	inventory.push_back(item);
	std::cout << item->getName() << "을(를) 인벤토리에 추가했습니다." << std::endl;
}

// 아이템 제거 함수
void Character::removeItem(int index)
{
	if (index >= 0 && index < inventory.size()) {
		std::cout << inventory[index]->getName() << "을(를) 인벤토리에서 제거했습니다." << std::endl;
		inventory.erase(inventory.begin() + index);
	}
	else {
		std::cout << "잘못된 아이템 인덱스입니다." << std::endl;
	}
}

void Character::showInventory() const
{
	cout << "인벤토리 정보" << endl;
	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i << ". " << inventory[i]->getName() << " [가격 : " << inventory[i]->getPrice()<< "gold";
		cout << endl;
	}

}

void Character::equipWeapon(Weapon* weapon) {
	if (equippedWeapon != nullptr)
	{
		swap(equippedWeapon, weapon); // 기존 무기와 교체
	}
	else
	{
		equippedWeapon = weapon; // 무기 장착
	}
}

void Character::equipArmor(Armor* armor)
{
	if (equippedWeapon != nullptr)
	{
		swap(equippedArmor, armor); // 기존 방어구와 교체
	}
	else
	{
		equippedArmor = armor; // 방어구 장착
	}
}

void Character::useItem(int itemindex) {
	if (inventory.empty() || itemindex < 0 || itemindex >= inventory.size())
	{
		std::cout << "잘못된 아이템 인덱스입니다." << std::endl;
		return;
	}

	Consumable* consumable = dynamic_cast<Consumable*>(inventory[itemindex]);

	if (consumable)
	{
		consumable->use(*this); // 아이템 사용
	}
	else
	{
		std::cout << "사용할 수 없는 아이템입니다." << std::endl;
		return;

	}

	removeItem(itemindex); // 아이템 사용 후 인벤토리에서 제거
}



std::vector<std::string> Character::getActiveSkills() const {
	if (characterClass) return characterClass->getActiveSkills();
	return {};
}

void Character::useSkill(const std::string& skillName, Character& self, Monster& target) { // <-- std::string 받음 확인
	if (characterClass) {
		// 스킬 사용 횟수 확인 (예: 1회성 스킬)
		// 맵의 키는 std::string이므로, skillName으로 직접 접근
		if (skillUsages.count(skillName) && skillUsages[skillName] > 0) { // <-- std::string 키 접근 확인
			characterClass->useSkill(skillName, self, target); // 실제 스킬 효과 실행

			// 1회성 스킬은 사용 후 횟수 감소 (스킬 이름을 string으로 비교)
			if (skillName == "숨기" || skillName == "버티기" || skillName == "망령 화살") {
				skillUsages[skillName]--; // <-- std::string 키 접근 확인
				std::cout << skillName << " 사용! 남은 횟수: " << skillUsages[skillName] << "회." << std::endl;
			}
		}
		else if (skillUsages.count(skillName) && skillUsages[skillName] == 0) {
			std::cout << "스킬 '" << skillName << "'의 사용 횟수를 모두 소진했습니다." << std::endl;
		}
		else { // 무제한 스킬 (기본 공격 등)
			characterClass->useSkill(skillName, self, target);
		}
	}
}
void Character::applyPassiveSkill(Character& self) {
	if (characterClass) characterClass->applyPassiveSkill(self);
}

std::string Character::getClassName() const {
	if (characterClass) return characterClass->getClassName();
	return "알수 없음";
}

// 스킬 사용 횟수 초기화 함수
void Character::initializeSkillUsages() {
	skillUsages.clear(); // 기존 데이터를 깔끔하게 초기화

	// 스킬 이름과 초기 사용 횟수를 직접 문자열 키로 설정
	// 각 직업의 스킬을 여기에 명시적으로 추가합니다.
	// 기존 enum 값 대신 실제 스킬 이름을 사용합니다.

	// 공통 스킬
	skillUsages["기본 공격"] = 99; // 무제한

	// 전사 스킬
	skillUsages["베기"] = 99;
	skillUsages["방패"] = 99;
	skillUsages["강타"] = 99;
	skillUsages["버티기"] = 1; // 1회 제한

	// 궁수 스킬
	skillUsages["화살 명중"] = 99;
	skillUsages["조준"] = 99;
	skillUsages["폭풍 화살"] = 99;
	skillUsages["망령 화살"] = 1; // 1회 제한

	// 도적 스킬
	skillUsages["찢기"] = 99;
	skillUsages["날렵한 손"] = 99;
	skillUsages["급습"] = 99;
	skillUsages["숨기"] = 1; // 1회 제한

	// (필요하다면 여기에 더 많은 스킬과 사용 횟수를 추가)
}

// 스킬 사용 횟수 복원 함수
void Character::restoreSkillUsage(const std::string& skillName, int amount) {
	if (skillUsages.count(skillName)) { // skillUsages 맵에 skillName이 있는지 확인
		if (skillUsages.at(skillName) != 99) { // 무제한 스킬이 아닌 경우에만 복원
			skillUsages[skillName] += amount;
			std::cout << skillName << " 스킬 사용 횟수가 " << amount << "만큼 회복되었습니다. 현재 " << skillUsages[skillName] << "회." << std::endl;
		}
		else {
			std::cout << skillName << " 스킬은 무제한입니다." << std::endl;
		}
	}
	else {
		std::cout << "알 수 없는 스킬이거나 사용 횟수를 복원할 수 없는 스킬입니다." << std::endl;
	}
}

// 남은 스킬 사용 횟수 반환 함수
int Character::getRemainingSkillUsage(const std::string& skillName) const {
	if (skillUsages.count(skillName)) { // skillUsages 맵에 skillName이 있는지 확인
		return skillUsages.at(skillName); // 해당 스킬의 남은 횟수 반환
	}
	return 0; // 해당 스킬이 없으면 0 반환 (또는 오류 처리)
}

// 스킬 타입에 따른 이름 반환 함수
std::string Character::getSkillName(const std::string& skillName) const {
	// 스킬 이름이 이미 문자열이므로, 그대로 반환합니다.
	// 기존의 switch 문은 SkillType enum을 string으로 변환하는 역할을 했지만,
	// 이제 스킬 이름 자체가 string이므로 필요 없어집니다.
	return skillName;
}