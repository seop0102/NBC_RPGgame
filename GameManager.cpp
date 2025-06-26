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
	player->applyPassiveSkill(*player);
	player->displayStat();

}
bool GameManager::playGame()
{
	std::cout << "┌--------------------------------------------------┐" << endl;
	std::cout << "│던전탐색[1], 인벤토리[2], 상점방문[3], 게임종료[4]│" << endl;
	std::cout << "└--------------------------------------------------┘" << endl;
	int choice = 0;
	std::cout << "선택 입력 대기중 : ";
	while (true)
	{
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > 4)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else
		{
			break;
		}
	}
	system("cls");
	if (choice == 1)
	{
		std::cout << "던전 입장중..." << endl;
		std::cout << "전투 시작!" << endl;
		if (battleManager->doBattle(player))
		{
			std::cout << "전투를 클리어 했습니다!" << endl;
			if (battleManager->GetIsClearBoss() == true)
			{
				endGame(battleManager->GetIsClearBoss());
			}

			player->displayStat();
		}
		else
		{
			std::cout << "전투에서 패배했습니다." << endl;
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
		Shop shop("혁이네 상점");
		TradeManager tradeManager;
		tradeManager.showShopItems(player,shop);
		std::cout << "구매[1], 판매[2], 나가기[3]" << endl;
		int choose = 0;
		while (true)
		{
			std::cin >> choose;
			if (std::cin.fail() || choice < 1 || choice > 3)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
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
			//cout 상점닫기
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
		std::cout << endl  << "게임을 클리어 했습니다!" << endl;

	}
	else
	{
		std::cout <<  endl << endl << "플레이어가 쓰러졌습니다!" << endl << endl;
		std::cout << "게임 오버" << endl << endl;

	}

	delete player;

	std::cin.ignore();
	std::cin.get(); 

	exit(0);
}