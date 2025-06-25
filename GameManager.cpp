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
	player->displayStat();
}
void GameManager::playGame()
{
	cout << "������ �����մϴ�!" << endl;

	while (true) {
		
		if (battleManager->doBattle(player))
		{
			cout << "������ Ŭ���� �߽��ϴ�!" << endl;
			player->displayStat();
			//����Ŭ������ �����Լ��� �ٽ� �߰�
		}
		else
		{
			cout << "�������� �й��߽��ϴ�." << endl;
			break;
		}
	}
}
void GameManager::endGame()
{
	cout << "���� ����!" << endl;
}