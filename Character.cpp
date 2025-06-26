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
	hitChance(80), // 기본 명중률 설정 (필요시)
	dodgeChance(5), // 기본 회피율 설정 (필요시)
	exp(0),
	gold(0),
	equippedWeapon(nullptr), equippedArmor(nullptr)
{
	characterClass = selectedClass;
	initializeSkillUsages();
}

Character::~Character() {
	// 1. 장착된 무기가 있다면 해제
	if (equippedWeapon != nullptr) {
		delete equippedWeapon;
		equippedWeapon = nullptr;
	}
	// 2. 장착된 방어구가 있다면 해제
	if (equippedArmor != nullptr) {
		delete equippedArmor;
		equippedArmor = nullptr;
	}
	// 3. 인벤토리 내의 모든 아이템을 해제
	for (Item* item : inventory) {
		if (item != nullptr) {
			delete item;
		}
	}
	inventory.clear();
	// 4. 캐릭터의 직업 객체를 해제
	if (characterClass != nullptr) {
		delete characterClass;
		characterClass = nullptr;
	}
	std::cout << name << " 캐릭터가 소멸되었습니다. 관련 메모리가 해제되었습니다." << std::endl;
}

void Character::displayStat()
{
	std::cout << "--------상태 창--------" << std::endl;
	std::cout << "이름: " << name << std::endl;
	std::cout << "레벨: " << level << std::endl;
	std::cout << "체력: " << health << "/" << maxHealth << std::endl;
	std::cout << "공격력: " << attack << std::endl;
	std::cout << "방어력: " << defense << std::endl;
	std::cout << "치명타확률: " << criticalChance << std::endl;
	std::cout << "명중률: " << hitChance << std::endl;
	std::cout << "회피율: " << dodgeChance << std::endl;
	std::cout << "경험치: " << exp << std::endl;
	std::cout << "골드: " << gold << std::endl;
	std::cout << "----------------------" << std::endl;
}

void Character::levelUp()
{
	const int MAX_LEVEL = 10;

	if (level >= MAX_LEVEL) {
		std::cout << "10레벨에 도달했습니다!" << std::endl;
		return;
	}

	while (level < MAX_LEVEL) {
		const int EXP_TO_NEXT_LEVEL = level * 100; // *현재* 레벨을 기반으로 계산

		if (exp >= EXP_TO_NEXT_LEVEL) {
			level++;
			exp -= EXP_TO_NEXT_LEVEL;

			maxHealth += 20;
			health = maxHealth;
			attack += 5;

			std::cout << "레벨 업 :" << level << "이(가) 되었습니다." << std::endl;
			std::cout << "최대 체력 +20, 공격력 +5 증가" << std::endl;
		}
		else {
			// *현재* 레벨에 충분한 경험치가 없으면 루프 종료
			std::cout << "경험치가 부족합니다. 다음 레벨업 까지 " << (EXP_TO_NEXT_LEVEL - exp) << "경험치가 더 필요합니다." << std::endl;
			break;
		}
	}
}

void Character::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		if (getHasIndomitableWill())
		{
			std::cout << "몬스터의 공격을 버텨냈습니다!" << std::endl;
			health = 1;
			return;
		}
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
void Character::addItem(Item* newItem)
{
	if (!newItem) {
		std::cout << "추가할 아이템이 유효하지 않습니다." << std::endl;
		return;
	}

	if (inventory.size() >= 10) { // 인벤토리 최대 10개 아이템
		showInventory();
		std::cout << "인벤토리가 가득 찼습니다. " << newItem->getName() << "을(를) 획득하려면 기존 아이템을 버려야 합니다." << std::endl;
		std::cout << "어떤 아이템을 버리시겠습니까? (0-" << inventory.size() - 1 << ", 취소: -1): ";

		int choice;
		while (!(std::cin >> choice) || (choice < -1 || choice >= inventory.size())) {
			std::cout << "잘못된 입력입니다. 다시 입력해주세요 (0-" << inventory.size() - 1 << ", 취소: -1): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (choice >= 0 && choice < inventory.size()) {
			Item* oldItem = inventory[choice]; // 버릴 아이템 포인터 저장
			inventory[choice] = newItem;        // 새 아이템으로 교체 (포인터 할당)
			std::cout << oldItem->getName() << "을(를) 버리고 " << newItem->getName() << "을(를) 획득했습니다." << std::endl;
			delete oldItem; // 버려진 아이템 메모리 해제
		}
		else { // 취소를 선택한 경우
			std::cout << newItem->getName() << " 획득을 취소했습니다." << std::endl;
			delete newItem;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return; // 아이템을 추가했든 안 했든 함수 종료
	}

	// 인벤토리가 가득 차지 않은 경우 아이템 추가
	inventory.push_back(newItem);
	std::cout << newItem->getName() << "을(를) 인벤토리에 추가했습니다." << std::endl;
}

// 아이템 제거 함수
void Character::removeItem(int index)
{
	if (index >= 0 && index < inventory.size()) {
		Item* itemToRemove = inventory[index]; 
		inventory.erase(inventory.begin() + index); 
		delete itemToRemove;
	}
	else {
		std::cout << "잘못된 아이템 인덱스입니다." << std::endl;
	}
}

void Character::showInventory() const
{
	std::cout << "-------- 인벤토리 --------" << std::endl;
	if (inventory.empty()) {
		std::cout << "인벤토리가 비어 있습니다." << std::endl;
	}
	else {
		for (size_t i = 0; i < inventory.size(); ++i) { // size_t 사용
			std::cout << "[" << i << "] " << inventory[i]->getName();

			Weapon* weapon = dynamic_cast<Weapon*>(inventory[i]);
			if (weapon) std::cout << " (공격력: " << weapon->getAttackBonus() << ")";
			Armor* armor = dynamic_cast<Armor*>(inventory[i]);
			if (armor) std::cout << " (방어력: " << armor->getDefenseBonus() << ", 최대 체력: " << armor->getMaxHealthBonus() << ")";
			Consumable* consumable = dynamic_cast<Consumable*>(inventory[i]);
			if (consumable) {
				if (consumable->getHealthRecover() > 0) std::cout << " (체력 회복: " << consumable->getHealthRecover() << ")";
				if (consumable->getAttackBonus() > 0) std::cout << " (공격력 증가: " << consumable->getAttackBonus() << ")";
				if (consumable->getSkillCharges() > 0) std::cout << " (스킬 충전: " << consumable->getSkillCharges() << ")";
			}

			std::cout << std::endl;
		}
	}
	std::cout << "--------------------------" << std::endl;
}

// 무기 장착
void Character::equipWeapon(Weapon* newWeapon) {
	if (!newWeapon) {
		std::cout << "유효하지 않은 무기입니다." << std::endl;
		return;
	}

	// 1. 기존에 장착된 무기가 있다면 인벤토리로 돌려보냄
	if (equippedWeapon != nullptr) {
		// 기존 무기의 스탯 보너스를 캐릭터 스탯에서 제거
		attack -= equippedWeapon->getAttackBonus();
		equippedWeapon->setEquipped(false);
		inventory.push_back(equippedWeapon);
		std::cout << equippedWeapon->getName() << "을(를) 인벤토리에 되돌렸습니다." << std::endl;
	}

	// 2. 새 무기를 장착하고 스탯을 조정
	equippedWeapon = newWeapon;
	equippedWeapon->setEquipped(true);
	// 새 무기의 스탯 보너스를 캐릭터 스탯에 추가
	attack += newWeapon->getAttackBonus();
	std::cout << newWeapon->getName() << "을(를) 장착했습니다." << std::endl;

}
void Character::equipArmor(Armor* newArmor)
{
	if (!newArmor) {
		std::cout << "유효하지 않은 방어구입니다." << std::endl;
		return;
	}

	// 1. 기존에 장착된 방어구가 있다면 인벤토리로 돌려보내기
	if (equippedArmor != nullptr) {
		defense -= equippedArmor->getDefenseBonus();
		maxHealth -= equippedArmor->getMaxHealthBonus();
		equippedArmor->setEquipped(false);
		inventory.push_back(equippedArmor);
		std::cout << equippedArmor->getName() << "을(를) 인벤토리에 되돌렸습니다." << std::endl;
	}

	// 2. 새 방어구를 장착하고 스탯을 조정
	equippedArmor = newArmor;
	equippedArmor->setEquipped(true);
	maxHealth += newArmor->getMaxHealthBonus();
	defense += newArmor->getDefenseBonus();
	std::cout << newArmor->getName() << "을(를) 장착했습니다." << std::endl;
}


void Character::useItem(int itemIndex) {
	if (inventory.empty() || itemIndex < 0 || itemIndex >= inventory.size())
	{
		std::cout << "잘못된 아이템 인덱스입니다." << std::endl;
		return;
	}

	Item* selectedItem = inventory[itemIndex];

	Consumable* consumable = dynamic_cast<Consumable*>(selectedItem);
	if (consumable)
	{
		// 소모품 사용 로직
		// 현재 Consumable::use 함수 내부의 TODO 주석을 해제하고 Character에 메서드를 추가해야 합니다.
		// 예: character.heal(healthRecover); character.addSkillCharges(skillCharges); etc.
		if (consumable->getHealthRecover() > 0) {
			health += consumable->getHealthRecover();
			if (health > maxHealth) health = maxHealth;
			std::cout << "체력이 " << consumable->getHealthRecover() << " 회복되었습니다. 현재 체력: " << health << std::endl;
		}
		if (consumable->getSkillCharges() > 0) {
			// 모든 스킬 사용 횟수를 회복한다고 가정
			initializeSkillUsages(); // 모든 스킬을 초기화하는 것으로 임시 구현
			std::cout << "모든 스킬 사용 횟수가 회복되었습니다." << std::endl;
		}
		if (consumable->getAttackBonus() > 0) {
			attack += consumable->getAttackBonus();
			std::cout << "임시 공격력이 " << consumable->getAttackBonus() << " 증가했습니다." << std::endl;
			// TODO: 임시 공격력 증가 효과를 관리하는 로직 (턴 종료 시 감소 등) 필요
		}

		std::cout << selectedItem->getName() << "을(를) 사용했습니다!" << std::endl;
		removeItem(itemIndex); // 소모품은 사용 후 제거
		return;
	}

	Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
	if (weapon) {
		std::cout << weapon->getName() << "을(를) 장착하시겠습니까? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tolower(choice) == 'y') {
			equipWeapon(weapon);
			Item* itemToEraseFromInventory = inventory[itemIndex];
			inventory.erase(inventory.begin() + itemIndex); // 인벤토리에서 장착된 아이템 제거
		}
		else {
			std::cout << "무기 장착을 취소했습니다." << std::endl;
		}
		return;
	}

	Armor* armor = dynamic_cast<Armor*>(selectedItem);
	if (armor) {
		std::cout << armor->getName() << "을(를) 장착하시겠습니까? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tolower(choice) == 'y') {
			equipArmor(armor);
			inventory.erase(inventory.begin() + itemIndex); // 인벤토리에서 장착된 아이템 제거
		}
		else {
			std::cout << "방어구 장착을 취소했습니다." << std::endl;
		}
		return;
	}

	std::cout << "사용할 수 없는 아이템입니다." << std::endl;
}

void Character::unequipWeapon() {
	if (equippedWeapon != nullptr) {
		// 기존 무기의 스탯 보너스를 캐릭터 스탯에서 제거
		attack -= equippedWeapon->getAttackBonus();

		// 장착 해제 상태로 변경하고 인벤토리에 다시 추가
		equippedWeapon->setEquipped(false);
		addItem(equippedWeapon); // addItem 함수를 사용하여 인벤토리 가득 찼을 때 로직 처리
		equippedWeapon = nullptr; // 장착 슬롯 비움
		std::cout << "무기를 해제했습니다." << std::endl;
	}
	else {
		std::cout << "장착된 무기가 없습니다." << std::endl;
	}
}

// 방어구 해제 함수
void Character::unequipArmor() {
	if (equippedArmor != nullptr) {
		defense -= equippedArmor->getDefenseBonus();
		maxHealth -= equippedArmor->getMaxHealthBonus();
		if (health > maxHealth) {
			health = maxHealth;
		}

		// 장착 해제 상태로 변경하고 인벤토리에 다시 추가
		equippedArmor->setEquipped(false);
		addItem(equippedArmor); // addItem 함수를 사용하여 인벤토리 가득 찼을 때 로직 처리
		equippedArmor = nullptr; // 장착 슬롯 비움
		std::cout << "방어구를 해제했습니다." << std::endl;
	}
	else {
		std::cout << "장착된 방어구가 없습니다." << std::endl;
	}
}

std::vector<std::string> Character::getActiveSkills() const {
	if (characterClass) return characterClass->getActiveSkills();
	return {};
}

void Character::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) { 
	if (characterClass) {
		// 스킬 사용 횟수 확인 (예: 1회성 스킬)
		if (skillUsages.count(skillName) && skillUsages[skillName] > 0) { 
			characterClass->useSkill(skillName, self, target, isCrit); // 실제 스킬 효과 실행

			// 1회성 스킬은 사용 후 횟수 감소 (스킬 이름을 string으로 비교)
			if (skillName == "숨기" || skillName == "버티기" || skillName == "망령 화살") {
				skillUsages[skillName]--; 
				std::cout << skillName << " 사용! 남은 횟수: " << skillUsages[skillName] << "회." << std::endl;
			}
		}
		else if (skillUsages.count(skillName) && skillUsages[skillName] == 0) {
			std::cout << "스킬 '" << skillName << "'의 사용 횟수를 모두 소진했습니다." << std::endl;
		}
		else { // 무제한 스킬 (기본 공격 등)
			characterClass->useSkill(skillName, self, target, isCrit);
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
	skillUsages.clear(); 

	// 공통 스킬
	skillUsages["기본 공격"] = 99; // 무제한

	// 전사 스킬
	skillUsages["베기"] = 5;
	skillUsages["방패"] = 1;
	skillUsages["강타"] = 3;
	skillUsages["버티기"] = 1; // 1회 제한

	// 궁수 스킬
	skillUsages["화살 명중"] = 5;
	skillUsages["조준"] = 5;
	skillUsages["폭풍 화살"] = 3;
	skillUsages["망령 화살"] = 1; // 1회 제한

	// 도적 스킬
	skillUsages["찢기"] = 5;
	skillUsages["날렵한 손"] = 2;
	skillUsages["급습"] = 3;
	skillUsages["숨기"] = 1; // 1회 제한

	// 필요하다면 여기에 더 많은 스킬과 사용 횟수를 추가
}

// 스킬 사용 횟수 복원 함수
void Character::restoreSkillUsage(const std::string& skillName, int amount) {
	if (skillUsages.count(skillName)) { 
		if (skillUsages.at(skillName) != 99) { 
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

void Character::initializeSkillEffect()
{
	setIsAimed(false);
	setIsHiding(false);
	setHasIndomitableWill(false);
	setWraithArrowDamage(0);

	if (getIsShielded())

	{
		setDefense(getDefense() - 10);
		setIsShielded(false);
	}
	
}

// 남은 스킬 사용 횟수 반환 함수
int Character::getRemainingSkillUsage(const std::string& skillName) const {
	if (skillUsages.count(skillName)) { 
		return skillUsages.at(skillName); 
	}
	return 0; // 해당 스킬이 없으면 0 반환 (또는 오류 처리)
}

// 스킬 타입에 따른 이름 반환 함수
std::string Character::getSkillName(const std::string& skillName) const {
	return skillName;
}