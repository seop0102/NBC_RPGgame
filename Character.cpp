#include "Character.h"
#include "Item.h"
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
	defense(10), // �⺻ ���� ���� (�ʿ��)
	criticalChance(10), // �⺻ ġ��Ÿ Ȯ�� (�ʿ��)
	hitChance(85), // �⺻ ���߷� ���� (�ʿ��)
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
        Item* itemToRemove = inventory[index]; // ������ ������ ������ ����
        std::cout << itemToRemove->getName() << "��(��) �κ��丮���� �����߽��ϴ�." << std::endl;
        inventory.erase(inventory.begin() + index); // ���Ϳ��� ������ ����
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

			// �߰����� ������ ���� ���
			WeaponItem* weapon = dynamic_cast<WeaponItem*>(inventory[i]);
			if (weapon) std::cout << " (���ݷ�: " << weapon->getAttackBonus() << ")";
			ArmorItem* armor = dynamic_cast<ArmorItem*>(inventory[i]);
			if (armor) std::cout << " (����: " << armor->getDefenseBonus() << ")";
			std::cout << std::endl;
		}
	}
	std::cout << "--------------------------" << std::endl;
}

void Character::equipWeapon(WeaponItem* newWeapon) {
	if (newWeapon == nullptr) {
		std::cout << "��ȿ���� ���� �����Դϴ�." << std::endl;
		return;
	}

	// 1. ������ ������ ���Ⱑ �ִٸ� �κ��丮�� ���������ϴ�.
	if (equippedWeapon != nullptr) {
		// ���� ������ ���� ���ʽ��� ĳ���� ���ȿ��� �����ϴ� ���� �߰�
		attack -= equippedWeapon->getAttackBonus(); 
		inventory.push_back(equippedWeapon);
		std::cout << equippedWeapon->getName() << "��(��) �κ��丮�� �ǵ��Ƚ��ϴ�." << std::endl;
	}

	// 2. �� ���⸦ �����ϰ� ������ ����
	equippedWeapon = newWeapon;
	// �� ������ ���� ���ʽ��� ĳ���� ���ȿ� �߰��ϴ� ���� �߰�
	attack += newWeapon->getAttackBonus(); 
	std::cout << newWeapon->getName() << "��(��) �����߽��ϴ�." << std::endl;

	// 3. �κ��丮���� ������ �������� ���� (���� �κ��丮�� �־��ٸ�)
	for (size_t i = 0; i < inventory.size(); ++i) {
		if (inventory[i] == newWeapon) {
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}
void Character::equipArmor(ArmorItem* newArmor)
{
	if (newArmor == nullptr) {
		std::cout << "��ȿ���� ���� ���Դϴ�." << std::endl;
		return;
	}

	// 1. ������ ������ ���� �ִٸ� �κ��丮�� ���������ϴ�.
	if (equippedArmor != nullptr) { 
		// ���� ���� ���� ���ʽ��� ĳ���� ���ȿ��� �����ϴ� ���� �߰�
		defense -= equippedArmor->getDefenseBonus(); 
		inventory.push_back(equippedArmor);
		std::cout << equippedArmor->getName() << "��(��) �κ��丮�� �ǵ��Ƚ��ϴ�." << std::endl;
	}

	// 2. �� ���� �����ϰ� ������ �����մϴ�.
	equippedArmor = newArmor;
	// �� ���� ���� ���ʽ��� ĳ���� ���ȿ� �߰��ϴ� ���� �߰�
	defense += newArmor->getDefenseBonus(); 
	std::cout << newArmor->getName() << "��(��) �����߽��ϴ�." << std::endl;

	// 3. �κ��丮���� ������ �������� ���� (���� �κ��丮�� �־��ٸ�)
	for (size_t i = 0; i < inventory.size(); ++i) {
		if (inventory[i] == newArmor) {
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

void Character::useItem(int itemindex) {
	if (inventory.empty() || itemindex < 0 || itemindex >= inventory.size())
	{
		std::cout << "�߸��� ������ �ε����Դϴ�." << std::endl;
		return;
	}

	EdibleItem* edible = dynamic_cast<EdibleItem*>(inventory[itemindex]);

	if (edible)
	{
		edible->use(*this); // ���� Character ��ü�� �Ѱ��־� �Ҹ�ǰ�� ������ ������ �� �ְ�
	}
	else // �Ҹ�ǰ�� �ƴ� ��� (����/�� ��)
	{
		// ���⳪ ���� ������ ���, ���� ���θ� ����� ������ �߰��� �� �ֽ��ϴ�.
		WeaponItem* weapon = dynamic_cast<WeaponItem*>(inventory[itemindex]);
		if (weapon) {
			std::cout << weapon->getName() << "��(��) �����Ͻðڽ��ϱ�? (y/n): ";
			char choice;
			std::cin >> choice;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� ����
			if (tolower(choice) == 'y') {
				equipWeapon(weapon);
				// equipWeapon ���ο��� �κ��丮���� ���ŵǹǷ� ���⼭ removeItem ȣ�� ���ʿ�
			}
			else {
				std::cout << "���� ������ ����߽��ϴ�." << std::endl;
			}
			return; // ó�� �Ϸ�
		}
		
		ArmorItem* armor = dynamic_cast<ArmorItem*>(inventory[itemindex]);
		if (armor) {
			std::cout << armor->getName() << "��(��) �����Ͻðڽ��ϱ�? (y/n): ";
			char choice;
			std::cin >> choice;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� ����
			if (tolower(choice) == 'y') {
				equipArmor(armor);
				// equipArmor ���ο��� �κ��丮���� ���ŵǹǷ� ���⼭ removeItem ȣ�� ���ʿ�
			}
			else {
				std::cout << "�� ������ ����߽��ϴ�." << std::endl;
			}
			return; // ó�� �Ϸ�
		}

		std::cout << "����� �� ���� �������Դϴ�." << std::endl;
		return;
	}

	// �Ҹ�ǰ�� ����� ��쿡�� �κ��丮���� ����
	removeItem(itemindex);
}

std::vector<std::string> Character::getActiveSkills() const {
	if (characterClass) return characterClass->getActiveSkills();
	return {};
}

void Character::useSkill(const std::string& skillName, Character& self, Monster& target) { // <-- std::string ���� Ȯ��
	if (characterClass) {
		// ��ų ��� Ƚ�� Ȯ�� (��: 1ȸ�� ��ų)
		// ���� Ű�� std::string�̹Ƿ�, skillName���� ���� ����
		if (skillUsages.count(skillName) && skillUsages[skillName] > 0) { // <-- std::string Ű ���� Ȯ��
			characterClass->useSkill(skillName, self, target); // ���� ��ų ȿ�� ����

			// 1ȸ�� ��ų�� ��� �� Ƚ�� ���� (��ų �̸��� string���� ��)
			if (skillName == "����" || skillName == "��Ƽ��" || skillName == "���� ȭ��") {
				skillUsages[skillName]--; // <-- std::string Ű ���� Ȯ��
				std::cout << skillName << " ���! ���� Ƚ��: " << skillUsages[skillName] << "ȸ." << std::endl;
			}
		}
		else if (skillUsages.count(skillName) && skillUsages[skillName] == 0) {
			std::cout << "��ų '" << skillName << "'�� ��� Ƚ���� ��� �����߽��ϴ�." << std::endl;
		}
		else { // ������ ��ų (�⺻ ���� ��)
			characterClass->useSkill(skillName, self, target);
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
	skillUsages.clear(); // ���� �����͸� ����ϰ� �ʱ�ȭ

	// ��ų �̸��� �ʱ� ��� Ƚ���� ���� ���ڿ� Ű�� ����
	// �� ������ ��ų�� ���⿡ ��������� �߰��մϴ�.
	// ���� enum �� ��� ���� ��ų �̸��� ����մϴ�.

	// ���� ��ų
	skillUsages["�⺻ ����"] = 99; // ������

	// ���� ��ų
	skillUsages["����"] = 99;
	skillUsages["����"] = 99;
	skillUsages["��Ÿ"] = 99;
	skillUsages["��Ƽ��"] = 1; // 1ȸ ����

	// �ü� ��ų
	skillUsages["ȭ�� ����"] = 99;
	skillUsages["����"] = 99;
	skillUsages["��ǳ ȭ��"] = 99;
	skillUsages["���� ȭ��"] = 1; // 1ȸ ����

	// ���� ��ų
	skillUsages["����"] = 99;
	skillUsages["������ ��"] = 99;
	skillUsages["�޽�"] = 99;
	skillUsages["����"] = 1; // 1ȸ ����

	// (�ʿ��ϴٸ� ���⿡ �� ���� ��ų�� ��� Ƚ���� �߰�)
}

// ��ų ��� Ƚ�� ���� �Լ�
void Character::restoreSkillUsage(const std::string& skillName, int amount) {
	if (skillUsages.count(skillName)) { // skillUsages �ʿ� skillName�� �ִ��� Ȯ��
		if (skillUsages.at(skillName) != 99) { // ������ ��ų�� �ƴ� ��쿡�� ����
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

// ���� ��ų ��� Ƚ�� ��ȯ �Լ�
int Character::getRemainingSkillUsage(const std::string& skillName) const {
	if (skillUsages.count(skillName)) { // skillUsages �ʿ� skillName�� �ִ��� Ȯ��
		return skillUsages.at(skillName); // �ش� ��ų�� ���� Ƚ�� ��ȯ
	}
	return 0; // �ش� ��ų�� ������ 0 ��ȯ (�Ǵ� ���� ó��)
}

// ��ų Ÿ�Կ� ���� �̸� ��ȯ �Լ�
std::string Character::getSkillName(const std::string& skillName) const {
	// ��ų �̸��� �̹� ���ڿ��̹Ƿ�, �״�� ��ȯ�մϴ�.
	// ������ switch ���� SkillType enum�� string���� ��ȯ�ϴ� ������ ������,
	// ���� ��ų �̸� ��ü�� string�̹Ƿ� �ʿ� �������ϴ�.
	return skillName;
}