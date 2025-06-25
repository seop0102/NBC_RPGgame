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
	cout << "��--------------------------------------------------��" << endl;
	cout << "������Ž��[1], �κ��丮[2], �����湮[3], ��������[4]��" << endl;
	cout << "��--------------------------------------------------��" << endl;
	int choice = 0;
	cout << "���� �Է� ����� : ";
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
	if (choice == 1)
	{
		if (battleManager->doBattle(player))
		{
			cout << "������ Ŭ���� �߽��ϴ�!" << endl;
			player->displayStat();
		}
		else
		{
			cout << "�������� �й��߽��ϴ�." << endl;	
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
		// ��������
		return true;
	}
	else
	{
		return false;
	}
	
}
void GameManager::endGame()
{
	cout << "���� ����!" << endl;
}