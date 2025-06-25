#include "BattleManager.h"

bool BattleManager::doBattle(Character* player)
{
	IClass* Cclass = player->getCharacterClass();

	Monster* monster = CreateMonster(player);

	if (player->getLevel() >= 10) {

		std::cout << "���� 10 �̻�! ���� ���Ͱ� �����մϴ�!" << std::endl;
		monster->setHealth(int(monster->getHealth() * 1.5)); // ���� 10 �̻��� �� ���� ���� ����
		monster->setAttack(int(monster->getAttack() * 1.5)); // ���� 10 �̻��� �� ���� ���� ����

	}

	while (player->getHealth() > 0 && monster->getHealth() > 0)
	{


		//���� ����
		playerchoice(player); // �÷��̾ ��ų�� �����ϴ� �Լ� ȣ��

		if (monster->getHealth() <= 0) {

			std::cout << "���͸� óġ�߽��ϴ�!" << std::endl;

			player->addGold(monster->getGold()); // ���� óġ �� ��� �߰�

			if (monster->dropItem() != nullptr) {
				std::cout << "�������� ȹ���߽��ϴ�: " << monster->dropItem()->getName() << std::endl;
				player->addItem(monster->dropItem()); // �÷��̾�� ������ �߰�
			}

			player->addExp(EXP); // ���� óġ �� ����ġ �߰�

			delete monster;

			return true; // ���� Ŭ����
			break;
		}

		player->takeDamage(monster->getAttack()); // ������ �������� �÷��̾� ����

		player->displayStat();

		if (player->getHealth() <= 0) {
			std::cout << "�÷��̾ ���������ϴ�!" << std::endl;

			delete monster;

			return false; // ���� ���� �� �� �������� �Լ� �θ���
			break;
		}
	}
}

std::string BattleManager::playerchoice(Character* player)
{
	IClass* Cclass = player->getCharacterClass();

	Cclass->showSkills(); // ĳ���� Ŭ������ ��ų ��� ���

	int choice = 0;

	std::cout << "����� ��ų�� �����ϼ���:" << std::endl;

	std::cin >> choice;

	return Cclass->getSkillbyIndex(choice);
}

void BattleManager::attackMonster(Character* player, std::string skill, Monster* monster)
{
	IClass* Cclass = player->getCharacterClass();

	if(isCrit(player)) {

	}
	else if (isHit(player)) {
		std::cout << "������ ���������ϴ�." << std::endl;
		return;
	}

	Cclass->useSkill(skill, *player, *monster); // ������ ��ų ���

	std::cout << "������ ���� ü��" << monster->getHealth() << std::endl;

	std::cout << "���� ��ų Ƚ��: " << player->getRemainingSkillUsage(skill) << std::endl;
}

bool BattleManager::isCrit(Character* player)
{
	return Utils::checkChance(player->getCriticalChance() * Utils::rollDice());
}

bool BattleManager::isDodge(Character* player)
{
	return Utils::checkChance(player->getDodgeChance() * Utils::rollDice());
}

bool BattleManager::isHit(Character* player)
{
	return Utils::checkChance(player->getHitChance());
}

Monster* BattleManager::CreateMonster(Character* player)
{
	MonsterType monster = static_cast<MonsterType>(Utils::getRandomInt(0, 1));

	switch (monster) {
	case MonsterType::Orc:
		return new Orc(player->getLevel());
	case MonsterType::Goblin:
		return new Goblin(player->getLevel());
	default:
		return nullptr;
	}
}