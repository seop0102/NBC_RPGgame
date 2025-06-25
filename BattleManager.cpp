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


		std::cout << "���� ����!! �̸�: " << monster->getName() << " ���ݷ�: " << monster->getAttack() << " ü��: " << monster->getHealth() << std::endl;

		//���� ����
		// �÷��̾ ��ų�� �����ϴ� �Լ� ȣ��
		attackMonster(player, playerchoice(player), monster);

		if (monster->getHealth() <= 0) {

			std::cout << "���͸� óġ�߽��ϴ�!" << std::endl;

			player->addGold(monster->getGold()); // ���� óġ �� ��� �߰�

			Item* item= monster->dropItem();

			if (item != nullptr) {
				std::cout << "�������� ȹ���߽��ϴ�: " << item->getName() << std::endl;
				player->addItem(item); // �÷��̾�� ������ �߰�
			}

			player->addExp(EXP); // ���� óġ �� ����ġ �߰�

			player->setHealth(player->getMaxHealth());//ü��ȸ��

			player->initializeSkillUsages(); //��ų ��� Ƚ�� �ʱ�ȭ
			player->initializeSkillEffect(); // ��ų ȿ�� ����

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
	while (true)
	
	{
		IClass* Cclass = player->getCharacterClass();

		int ChoiceSize = Cclass->getActiveSkills().size() + 1;

		Cclass->showSkills(); // ĳ���� Ŭ������ ��ų ��� ���

		std::cout << ChoiceSize << " ������ ����ϱ�" << std::endl;

		int choice = 0;

		std::cout << "��ȣ�� �Է��� �����ϼ���:" << std::endl;

		std::cin >> choice;

		if (choice > 0 && choice < ChoiceSize)

		{
			return Cclass->getSkillbyIndex(choice);
			
		}
		else if(choice == ChoiceSize)

		{
			player->showInventory();
			if ((player->getInventory()).empty() != true)

			{
				std::cout << "����� �������� �����ϼ���" << std::endl;
				std::cin >> choice;

				Item* item = player->GetItemByIndex(choice);

				if (item != nullptr && item->getIsEquipped() == false)
				{
					item->use(*player);
				}
				else
				{
					std::cout << "����� �� ���� �������̰ų� �߸��� ���� �Դϴ�" << std::endl;
				}
			}
			else
			{
			}
		}

		else
		
		{
			std::cout << "�߸��� �Է��Դϴ� �ٽ� �Է��� �ּ���." << std::endl;
		}

		
	}
}

void BattleManager::UseItem(Character* player)
{
}

void BattleManager::attackMonster(Character* player, std::string skill, Monster* monster)
{
	bool crit = isCrit(player);

	if (skill == "����" || skill == "����" || skill == "��Ƽ��" || skill == "����") {

	}
	else if (isHit(player) != true && crit != true) {
		std::cout << "������ ���������ϴ�." << std::endl;

		std::cout << "���� ��ų Ƚ��: " << player->getRemainingSkillUsage(skill) << std::endl;
		
		return;
	}

	if (player->getWraithArrowDamage() > 0)

	{
		std::cout << "���� ȭ���� �����߽��ϴ�! ������ ���� " << player->getWraithArrowDamage() << std::endl;
		monster->takeDamage(player->getWraithArrowDamage());
		player->setWraithArrowDamage(0);
	}

	player->useSkill(skill, *player, *monster, crit); // ������ ��ų ���

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

void BattleManager::attackPlayer(Character* player, Monster* monster)

{
	if (player->getIsHiding())

	{
		std::cout << "������ ȸ���߽��ϴ�" << std::endl;
		player->setIsHiding(false);
		return;
	}
		
	int defense = player->getDefense();
	int damage = monster->getAttack();

	damage = damage - (damage * (defense / 100));

	

	player->takeDamage(damage); // ������ �������� �÷��̾� ����
}