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
	defense(0), // �⺻ ���� ���� (�ʿ��)
	criticalChance(5), // �⺻ ġ��Ÿ Ȯ�� (�ʿ��)
	hitChance(80), // �⺻ ���߷� ���� (�ʿ��)
	dodgeChance(5), // �⺻ ȸ���� ���� (�ʿ��)
	exp(0),
	gold(0),
	equippedWeapon(nullptr), equippedArmor(nullptr)
{
	characterClass = selectedClass;
	initializeSkillUsages();
}

Character::~Character() {
	// 1. ������ ���Ⱑ �ִٸ� ����
	if (equippedWeapon != nullptr) {
		delete equippedWeapon;
		equippedWeapon = nullptr;
	}
	// 2. ������ ���� �ִٸ� ����
	if (equippedArmor != nullptr) {
		delete equippedArmor;
		equippedArmor = nullptr;
	}
	// 3. �κ��丮 ���� ��� �������� ����
	for (Item* item : inventory) {
		if (item != nullptr) {
			delete item;
		}
	}
	inventory.clear();
	// 4. ĳ������ ���� ��ü�� ����
	if (characterClass != nullptr) {
		delete characterClass;
		characterClass = nullptr;
	}
	std::cout << name << " ĳ���Ͱ� �Ҹ�Ǿ����ϴ�. ���� �޸𸮰� �����Ǿ����ϴ�." << std::endl;
}

void Character::displayStat()
{
	std::cout << "--------���� â--------" << std::endl;
	std::cout << "�̸�: " << name << std::endl;
	std::cout << "����: " << level << std::endl;
	std::cout << "ü��: " << health << "/" << maxHealth << std::endl;
	std::cout << "���ݷ�: " << attack << std::endl;
	std::cout << "����: " << defense << std::endl;
	std::cout << "ġ��ŸȮ��: " << criticalChance << std::endl;
	std::cout << "���߷�: " << hitChance << std::endl;
	std::cout << "ȸ����: " << dodgeChance << std::endl;
	std::cout << "����ġ: " << exp << std::endl;
	std::cout << "���: " << gold << std::endl;
	std::cout << "----------------------" << std::endl;
}

void Character::levelUp()
{
	const int MAX_LEVEL = 10;

	if (level >= MAX_LEVEL) {
		std::cout << "10������ �����߽��ϴ�!" << std::endl;
		return;
	}

	while (level < MAX_LEVEL) {
		const int EXP_TO_NEXT_LEVEL = level * 100; // *����* ������ ������� ���

		if (exp >= EXP_TO_NEXT_LEVEL) {
			level++;
			exp -= EXP_TO_NEXT_LEVEL;

			maxHealth += 20;
			health = maxHealth;
			attack += 5;

			std::cout << "���� �� :" << level << "��(��) �Ǿ����ϴ�." << std::endl;
			std::cout << "�ִ� ü�� +20, ���ݷ� +5 ����" << std::endl;
		}
		else {
			// *����* ������ ����� ����ġ�� ������ ���� ����
			std::cout << "����ġ�� �����մϴ�. ���� ������ ���� " << (EXP_TO_NEXT_LEVEL - exp) << "����ġ�� �� �ʿ��մϴ�." << std::endl;
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
			std::cout << "������ ������ ���߳½��ϴ�!" << std::endl;
			health = 1;
			return;
		}
		health = 0;
	}
}

// ��� �߰� �Լ�
void Character::addGold(int amount)
{
	gold += amount;
	std::cout << amount << " G�� ȹ���߽��ϴ�. ���� ���: " << gold << std::endl;
}

// ����ġ �߰� �Լ�
void Character::addExp(int amount)
{
	exp += amount;
	std::cout << amount << " ����ġ�� ȹ���߽��ϴ�. ���� ����ġ: " << exp << std::endl;
	// ����ġ ȹ�� �� ������ üũ
	levelUp();
}

// ��� ���� �Լ�
void Character::removeGold(int amount)
{
	if (gold >= amount) {
		gold -= amount;
		std::cout << amount << " G�� ����߽��ϴ�. ���� ���: " << gold << std::endl;
	}
	else {
		std::cout << "��尡 �����մϴ�." << std::endl;
	}
}

// ������ �߰� �Լ�
void Character::addItem(Item* newItem)
{
	if (!newItem) {
		std::cout << "�߰��� �������� ��ȿ���� �ʽ��ϴ�." << std::endl;
		return;
	}

	if (inventory.size() >= 10) { // �κ��丮 �ִ� 10�� ������
		showInventory();
		std::cout << "�κ��丮�� ���� á���ϴ�. " << newItem->getName() << "��(��) ȹ���Ϸ��� ���� �������� ������ �մϴ�." << std::endl;
		std::cout << "� �������� �����ðڽ��ϱ�? (0-" << inventory.size() - 1 << ", ���: -1): ";

		int choice;
		while (!(std::cin >> choice) || (choice < -1 || choice >= inventory.size())) {
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ��� (0-" << inventory.size() - 1 << ", ���: -1): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (choice >= 0 && choice < inventory.size()) {
			Item* oldItem = inventory[choice]; // ���� ������ ������ ����
			inventory[choice] = newItem;        // �� ���������� ��ü (������ �Ҵ�)
			std::cout << oldItem->getName() << "��(��) ������ " << newItem->getName() << "��(��) ȹ���߽��ϴ�." << std::endl;
			delete oldItem; // ������ ������ �޸� ����
		}
		else { // ��Ҹ� ������ ���
			std::cout << newItem->getName() << " ȹ���� ����߽��ϴ�." << std::endl;
			delete newItem;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return; // �������� �߰��ߵ� �� �ߵ� �Լ� ����
	}

	// �κ��丮�� ���� ���� ���� ��� ������ �߰�
	inventory.push_back(newItem);
	std::cout << newItem->getName() << "��(��) �κ��丮�� �߰��߽��ϴ�." << std::endl;
}

// ������ ���� �Լ�
void Character::removeItem(int index)
{
	if (index >= 0 && index < inventory.size()) {
		Item* itemToRemove = inventory[index]; 
		inventory.erase(inventory.begin() + index); 
		delete itemToRemove;
	}
	else {
		std::cout << "�߸��� ������ �ε����Դϴ�." << std::endl;
	}
}

void Character::showInventory() const
{
	std::cout << "-------- �κ��丮 --------" << std::endl;
	if (inventory.empty()) {
		std::cout << "�κ��丮�� ��� �ֽ��ϴ�." << std::endl;
	}
	else {
		for (size_t i = 0; i < inventory.size(); ++i) { // size_t ���
			std::cout << "[" << i << "] " << inventory[i]->getName();

			Weapon* weapon = dynamic_cast<Weapon*>(inventory[i]);
			if (weapon) std::cout << " (���ݷ�: " << weapon->getAttackBonus() << ")";
			Armor* armor = dynamic_cast<Armor*>(inventory[i]);
			if (armor) std::cout << " (����: " << armor->getDefenseBonus() << ", �ִ� ü��: " << armor->getMaxHealthBonus() << ")";
			Consumable* consumable = dynamic_cast<Consumable*>(inventory[i]);
			if (consumable) {
				if (consumable->getHealthRecover() > 0) std::cout << " (ü�� ȸ��: " << consumable->getHealthRecover() << ")";
				if (consumable->getAttackBonus() > 0) std::cout << " (���ݷ� ����: " << consumable->getAttackBonus() << ")";
				if (consumable->getSkillCharges() > 0) std::cout << " (��ų ����: " << consumable->getSkillCharges() << ")";
			}

			std::cout << std::endl;
		}
	}
	std::cout << "--------------------------" << std::endl;
}

// ���� ����
void Character::equipWeapon(Weapon* newWeapon) {
	if (!newWeapon) {
		std::cout << "��ȿ���� ���� �����Դϴ�." << std::endl;
		return;
	}

	// 1. ������ ������ ���Ⱑ �ִٸ� �κ��丮�� ��������
	if (equippedWeapon != nullptr) {
		// ���� ������ ���� ���ʽ��� ĳ���� ���ȿ��� ����
		attack -= equippedWeapon->getAttackBonus();
		equippedWeapon->setEquipped(false);
		inventory.push_back(equippedWeapon);
		std::cout << equippedWeapon->getName() << "��(��) �κ��丮�� �ǵ��Ƚ��ϴ�." << std::endl;
	}

	// 2. �� ���⸦ �����ϰ� ������ ����
	equippedWeapon = newWeapon;
	equippedWeapon->setEquipped(true);
	// �� ������ ���� ���ʽ��� ĳ���� ���ȿ� �߰�
	attack += newWeapon->getAttackBonus();
	std::cout << newWeapon->getName() << "��(��) �����߽��ϴ�." << std::endl;

}
void Character::equipArmor(Armor* newArmor)
{
	if (!newArmor) {
		std::cout << "��ȿ���� ���� ���Դϴ�." << std::endl;
		return;
	}

	// 1. ������ ������ ���� �ִٸ� �κ��丮�� ����������
	if (equippedArmor != nullptr) {
		defense -= equippedArmor->getDefenseBonus();
		maxHealth -= equippedArmor->getMaxHealthBonus();
		equippedArmor->setEquipped(false);
		inventory.push_back(equippedArmor);
		std::cout << equippedArmor->getName() << "��(��) �κ��丮�� �ǵ��Ƚ��ϴ�." << std::endl;
	}

	// 2. �� ���� �����ϰ� ������ ����
	equippedArmor = newArmor;
	equippedArmor->setEquipped(true);
	maxHealth += newArmor->getMaxHealthBonus();
	defense += newArmor->getDefenseBonus();
	std::cout << newArmor->getName() << "��(��) �����߽��ϴ�." << std::endl;
}


void Character::useItem(int itemIndex) {
	if (inventory.empty() || itemIndex < 0 || itemIndex >= inventory.size())
	{
		std::cout << "�߸��� ������ �ε����Դϴ�." << std::endl;
		return;
	}

	Item* selectedItem = inventory[itemIndex];

	Consumable* consumable = dynamic_cast<Consumable*>(selectedItem);
	if (consumable)
	{
		// �Ҹ�ǰ ��� ����
		// ���� Consumable::use �Լ� ������ TODO �ּ��� �����ϰ� Character�� �޼��带 �߰��ؾ� �մϴ�.
		// ��: character.heal(healthRecover); character.addSkillCharges(skillCharges); etc.
		if (consumable->getHealthRecover() > 0) {
			health += consumable->getHealthRecover();
			if (health > maxHealth) health = maxHealth;
			std::cout << "ü���� " << consumable->getHealthRecover() << " ȸ���Ǿ����ϴ�. ���� ü��: " << health << std::endl;
		}
		if (consumable->getSkillCharges() > 0) {
			// ��� ��ų ��� Ƚ���� ȸ���Ѵٰ� ����
			initializeSkillUsages(); // ��� ��ų�� �ʱ�ȭ�ϴ� ������ �ӽ� ����
			std::cout << "��� ��ų ��� Ƚ���� ȸ���Ǿ����ϴ�." << std::endl;
		}
		if (consumable->getAttackBonus() > 0) {
			attack += consumable->getAttackBonus();
			std::cout << "�ӽ� ���ݷ��� " << consumable->getAttackBonus() << " �����߽��ϴ�." << std::endl;
			// TODO: �ӽ� ���ݷ� ���� ȿ���� �����ϴ� ���� (�� ���� �� ���� ��) �ʿ�
		}

		std::cout << selectedItem->getName() << "��(��) ����߽��ϴ�!" << std::endl;
		removeItem(itemIndex); // �Ҹ�ǰ�� ��� �� ����
		return;
	}

	Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
	if (weapon) {
		std::cout << weapon->getName() << "��(��) �����Ͻðڽ��ϱ�? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tolower(choice) == 'y') {
			equipWeapon(weapon);
			Item* itemToEraseFromInventory = inventory[itemIndex];
			inventory.erase(inventory.begin() + itemIndex); // �κ��丮���� ������ ������ ����
		}
		else {
			std::cout << "���� ������ ����߽��ϴ�." << std::endl;
		}
		return;
	}

	Armor* armor = dynamic_cast<Armor*>(selectedItem);
	if (armor) {
		std::cout << armor->getName() << "��(��) �����Ͻðڽ��ϱ�? (y/n): ";
		char choice;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tolower(choice) == 'y') {
			equipArmor(armor);
			inventory.erase(inventory.begin() + itemIndex); // �κ��丮���� ������ ������ ����
		}
		else {
			std::cout << "�� ������ ����߽��ϴ�." << std::endl;
		}
		return;
	}

	std::cout << "����� �� ���� �������Դϴ�." << std::endl;
}

void Character::unequipWeapon() {
	if (equippedWeapon != nullptr) {
		// ���� ������ ���� ���ʽ��� ĳ���� ���ȿ��� ����
		attack -= equippedWeapon->getAttackBonus();

		// ���� ���� ���·� �����ϰ� �κ��丮�� �ٽ� �߰�
		equippedWeapon->setEquipped(false);
		addItem(equippedWeapon); // addItem �Լ��� ����Ͽ� �κ��丮 ���� á�� �� ���� ó��
		equippedWeapon = nullptr; // ���� ���� ���
		std::cout << "���⸦ �����߽��ϴ�." << std::endl;
	}
	else {
		std::cout << "������ ���Ⱑ �����ϴ�." << std::endl;
	}
}

// �� ���� �Լ�
void Character::unequipArmor() {
	if (equippedArmor != nullptr) {
		defense -= equippedArmor->getDefenseBonus();
		maxHealth -= equippedArmor->getMaxHealthBonus();
		if (health > maxHealth) {
			health = maxHealth;
		}

		// ���� ���� ���·� �����ϰ� �κ��丮�� �ٽ� �߰�
		equippedArmor->setEquipped(false);
		addItem(equippedArmor); // addItem �Լ��� ����Ͽ� �κ��丮 ���� á�� �� ���� ó��
		equippedArmor = nullptr; // ���� ���� ���
		std::cout << "���� �����߽��ϴ�." << std::endl;
	}
	else {
		std::cout << "������ ���� �����ϴ�." << std::endl;
	}
}

std::vector<std::string> Character::getActiveSkills() const {
	if (characterClass) return characterClass->getActiveSkills();
	return {};
}

void Character::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) { 
	if (characterClass) {
		// ��ų ��� Ƚ�� Ȯ�� (��: 1ȸ�� ��ų)
		if (skillUsages.count(skillName) && skillUsages[skillName] > 0) { 
			characterClass->useSkill(skillName, self, target, isCrit); // ���� ��ų ȿ�� ����

			// 1ȸ�� ��ų�� ��� �� Ƚ�� ���� (��ų �̸��� string���� ��)
			if (skillName == "����" || skillName == "��Ƽ��" || skillName == "���� ȭ��") {
				skillUsages[skillName]--; 
				std::cout << skillName << " ���! ���� Ƚ��: " << skillUsages[skillName] << "ȸ." << std::endl;
			}
		}
		else if (skillUsages.count(skillName) && skillUsages[skillName] == 0) {
			std::cout << "��ų '" << skillName << "'�� ��� Ƚ���� ��� �����߽��ϴ�." << std::endl;
		}
		else { // ������ ��ų (�⺻ ���� ��)
			characterClass->useSkill(skillName, self, target, isCrit);
		}
	}
}
void Character::applyPassiveSkill(Character& self) {
	if (characterClass) characterClass->applyPassiveSkill(self);
}

std::string Character::getClassName() const {
	if (characterClass) return characterClass->getClassName();
	return "�˼� ����";
}

// ��ų ��� Ƚ�� �ʱ�ȭ �Լ�
void Character::initializeSkillUsages() {
	skillUsages.clear(); 

	// ���� ��ų
	skillUsages["�⺻ ����"] = 99; // ������

	// ���� ��ų
	skillUsages["����"] = 5;
	skillUsages["����"] = 1;
	skillUsages["��Ÿ"] = 3;
	skillUsages["��Ƽ��"] = 1; // 1ȸ ����

	// �ü� ��ų
	skillUsages["ȭ�� ����"] = 5;
	skillUsages["����"] = 5;
	skillUsages["��ǳ ȭ��"] = 3;
	skillUsages["���� ȭ��"] = 1; // 1ȸ ����

	// ���� ��ų
	skillUsages["����"] = 5;
	skillUsages["������ ��"] = 2;
	skillUsages["�޽�"] = 3;
	skillUsages["����"] = 1; // 1ȸ ����

	// �ʿ��ϴٸ� ���⿡ �� ���� ��ų�� ��� Ƚ���� �߰�
}

// ��ų ��� Ƚ�� ���� �Լ�
void Character::restoreSkillUsage(const std::string& skillName, int amount) {
	if (skillUsages.count(skillName)) { 
		if (skillUsages.at(skillName) != 99) { 
			skillUsages[skillName] += amount;
			std::cout << skillName << " ��ų ��� Ƚ���� " << amount << "��ŭ ȸ���Ǿ����ϴ�. ���� " << skillUsages[skillName] << "ȸ." << std::endl;
		}
		else {
			std::cout << skillName << " ��ų�� �������Դϴ�." << std::endl;
		}
	}
	else {
		std::cout << "�� �� ���� ��ų�̰ų� ��� Ƚ���� ������ �� ���� ��ų�Դϴ�." << std::endl;
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

// ���� ��ų ��� Ƚ�� ��ȯ �Լ�
int Character::getRemainingSkillUsage(const std::string& skillName) const {
	if (skillUsages.count(skillName)) { 
		return skillUsages.at(skillName); 
	}
	return 0; // �ش� ��ų�� ������ 0 ��ȯ (�Ǵ� ���� ó��)
}

// ��ų Ÿ�Կ� ���� �̸� ��ȯ �Լ�
std::string Character::getSkillName(const std::string& skillName) const {
	return skillName;
}