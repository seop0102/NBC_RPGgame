#include "GameManager.h"  
GameManager::GameManager() {
	battleManager = new BattleManager();
	shopManager = new ShopManager();
	storyManager = new StoryManager();
}
GameManager::~GameManager() {
	delete battleManager;
	delete shopManager;
	delete storyManager;
}
void GameManager::startGame()
{
	storyManager->askUsername();
	string job = storyManager->getJob();
	IClass* selectedClass = nullptr;
	if (job == "검사") {
		selectedClass = new Warrior();
	}
	else if (job == "궁수") {
		selectedClass = new Archer();
	}
	else if (job == "도적") {
		selectedClass = new Rogue();
	}
	else {
		// 예외 처리
	}
	player = new Character(storyManager->getName(), selectedClass);
	player->displayStat();
}
void GameManager::playGame()
{
	cout << "게임을 시작합니다!" << endl;
	if (battleManager->doBattle(player))
	{
		cout << "전투를 클리어 했습니다!" << endl;
		player->displayStat();
		shopManager->openShop();
	}
	else
	{
		cout << "전투에서 패배했습니다. 게임을 종료합니다." << endl;
		endGame();
		return;
	}
}
void GameManager::endGame()
{
	cout << "게임 종료!" << endl;
}