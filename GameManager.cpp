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
	if (job == "�˻�") {
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
		std::cout << "���� ������..." << endl;
		std::cout << "���� ����!" << endl;
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
	else if (choice == 2)
	{
		player->showInventory();
		return true;
	}
	else if (choice == 3)
	{
		Shop shop("���̳� ����");
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
		std::cout << "���� ����" << endl << endl;

	}

	delete player;

	std::cin.ignore();
	std::cin.get(); 

	exit(0);
}