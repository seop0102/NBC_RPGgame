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
	player->initializeSkillUsages();
	player->displayStat();
}
void GameManager::playGame()
{
	cout << "게임을 시작합니다!" << endl;

	while (true) {
		
		if (battleManager->doBattle(player))
		{
			cout << "전투를 클리어 했습니다!" << endl;
			player->displayStat();
			//상점클래스의 오픈함수로 다시 추가
		}
		else
		{
			cout << "전투에서 패배했습니다." << endl;
			break;
		}
	}
}
void GameManager::endGame()
{
	cout << "게임 종료!" << endl;
}