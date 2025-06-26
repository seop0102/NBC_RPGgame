#include "GameManager.h"  
GameManager::GameManager() {
	battleManager = new BattleManager();
	storyManager = new StoryManager();
	tradeManager = new TradeManager();
}
GameManager::~GameManager() {
	delete battleManager;
	delete storyManager;
	delete tradeManager;
}
void GameManager::startGame()
{
	storyManager->startPrologue();
	string job = storyManager->getJob();
	IClass* selectedClass = nullptr;
	if (job == "����") {
		selectedClass = new Warrior();
	}
	else if (job == "�ü�") {
		selectedClass = new Archer();
	}
	else if (job == "����") {
		selectedClass = new Rogue();
	}
	else {
		// ���� ó��
	}
	player = new Character(storyManager->getName(), selectedClass);
	player->initializeSkillUsages();
	player->applyPassiveSkill(*player);
	player->displayStat();
	player->setGold(10000);
}
bool GameManager::playGame()
{
	std::cout << "��--------------------------------------------------��" << endl;
	std::cout << "������Ž��[1], �κ��丮[2], �����湮[3], ��������[4]��" << endl;
	std::cout << "��--------------------------------------------------��" << endl;
	int choice = 0;
	std::cout << "���� �Է� ����� : ";
	while (true)
	{
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > 4)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
		}
		else
		{
			break;
		}
	}
	system("cls");
	if (choice == 1)
	{
		std::cout << "================================" << endl;
		std::cout << "���� ������..." << endl;
		std::cout << "================================" << endl;
		std::cout <<  endl << endl << "���� ����!" << endl;
		if (battleManager->doBattle(player))
		{
			std::cout << "������ Ŭ���� �߽��ϴ�!" << endl;
			if (battleManager->GetIsClearBoss() == true)
			{
				endGame(battleManager->GetIsClearBoss());
			}

			player->displayStat();
		}
		else
		{
			std::cout << "�������� �й��߽��ϴ�." << endl;
			endGame(battleManager->GetIsClearBoss());
		}
		return true;
	}
	else if (choice == 2) // �κ��丮Add commentMore actions
	{
		while (true) // �κ��丮 �޴� �ݺ�
		{
			system("cls"); // ȭ�� �����
			player->showInventory(); // �κ��丮 ��� �����ֱ�

			std::cout << "��------------------------------------------------------------��" << endl;
			std::cout << "�������� ���/����[1], ��� ����[2], ����â ����[3], ������[4]��" << endl;
			std::cout << "��------------------------------------------------------------��" << endl;
			int inventoryChoice = 0;
			std::cout << "���� �Է� ����� : ";

			while (true)
			{
				std::cin >> inventoryChoice;
				if (std::cin.fail() || inventoryChoice < 1 || inventoryChoice > 4)
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
				}
				else
				{
					break;
				}
			}

			if (inventoryChoice == 1) // ������ ���/����
			{
				if (player->getInventory().empty()) {
					std::cout << "�κ��丮�� ��� �ֽ��ϴ�." << std::endl;
					// sleep(1); // ��� ��� �� �޴��� ���ư� �� �ֵ���
					continue; // �κ��丮 �޴��� �������� ���ư�
				}

				std::cout << "����ϰų� ������ �������� ��ȣ�� �Է��ϼ���: ";
				int itemIndex = 0;
				while (true)
				{
					std::cin >> itemIndex;
					if (std::cin.fail() || itemIndex < 0 || itemIndex >= player->getInventory().size())
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "�߸��� ������ ��ȣ�Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
					}
					else
					{
						break;
					}
				}
				player->useItem(itemIndex);
				// sleep(1);
			}
			else if (inventoryChoice == 2) // ��� ����
			{
				std::cout << "��-----------------------------------------��" << endl;
				std::cout << "������ ����[1], �� ����[2], ���ư���[3]��" << endl;
				std::cout << "��-----------------------------------------��" << endl;
				int unequipChoice = 0;
				std::cout << "���� �Է� ����� : ";

				while (true)
				{
					std::cin >> unequipChoice;
					if (std::cin.fail() || unequipChoice < 1 || unequipChoice > 3)
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
					}
					else
					{
						break;
					}
				}
				system("cls"); // ���� �� ȭ�� �����

				if (unequipChoice == 1) {
					player->unequipWeapon();
				}
				else if (unequipChoice == 2) {
					player->unequipArmor();
				}
				else {
					std::cout << "��� ������ ����մϴ�." << std::endl;
				}
				// sleep(1);
			}
			else if (inventoryChoice == 3) // ����â ����
			{
				player->displayStat();
				std::cout << "����Ϸ��� �ƹ� Ű�� ��������..." << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���� �Է� ���� ����
				std::cin.get(); // ����� �Է� ���
				// sleep(1);
			}
			else if (inventoryChoice == 4) // ������
			{
				break; // �κ��丮 �޴��� �������� �� �޴��� ���ư�
			}
		}
		return true; // �κ��丮 �޴� ������ ������ ���� ���� ������ ���ư�Add commentMore actions
	}
	else if (choice == 3)
	{
		Shop shop("������ ������ ����");
		TradeManager tradeManager;
		tradeManager.showShopItems(player,shop);
		std::cout << "����[1], �Ǹ�[2], ������[3]" << endl;
		int choose = 0;
		while (true)
		{
			std::cin >> choose;
			if (std::cin.fail() || choice < 1 || choice > 3)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
			}
			else
			{
				break;
			}
		}
		if (choose == 1)
		{
			tradeManager.buyItem(player, shop);
		}
		else if (choose == 2)
		{
			tradeManager.sellItem(player);
		}
		else
		{
			//cout �����ݱ�
		}

		return true;
	}
	else
	{
		return false;
	}
	
}
void GameManager::endGame(bool IsClear)
{
	if (IsClear)
	{
		std::cout << endl  << "������ Ŭ���� �߽��ϴ�!" << endl;

	}
	else
	{
		std::cout <<  endl << endl << "�÷��̾ ���������ϴ�!" << endl << endl;
		std::cout << endl << endl <<  "[Game Over]" << endl << endl;

	}

	delete player;

	exit(0);
}