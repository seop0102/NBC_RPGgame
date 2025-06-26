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
	if (job == "전사") {
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
	player->setGold(10000);
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
		std::cout << "================================" << endl;
		std::cout << "던전 입장중..." << endl;
		std::cout << "================================" << endl;
		std::cout <<  endl << endl << "전투 시작!" << endl;
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
	else if (choice == 2) // 인벤토리Add commentMore actions
	{
		while (true) // 인벤토리 메뉴 반복
		{
			system("cls"); // 화면 지우기
			player->showInventory(); // 인벤토리 목록 보여주기

			std::cout << "┌------------------------------------------------------------┐" << endl;
			std::cout << "│아이템 사용/장착[1], 장비 해제[2], 상태창 보기[3], 나가기[4]│" << endl;
			std::cout << "└------------------------------------------------------------┘" << endl;
			int inventoryChoice = 0;
			std::cout << "선택 입력 대기중 : ";

			while (true)
			{
				std::cin >> inventoryChoice;
				if (std::cin.fail() || inventoryChoice < 1 || inventoryChoice > 4)
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

			if (inventoryChoice == 1) // 아이템 사용/장착
			{
				if (player->getInventory().empty()) {
					std::cout << "인벤토리가 비어 있습니다." << std::endl;
					// sleep(1); // 잠시 대기 후 메뉴로 돌아갈 수 있도록
					continue; // 인벤토리 메뉴의 시작으로 돌아감
				}

				std::cout << "사용하거나 장착할 아이템의 번호를 입력하세요: ";
				int itemIndex = 0;
				while (true)
				{
					std::cin >> itemIndex;
					if (std::cin.fail() || itemIndex < 0 || itemIndex >= player->getInventory().size())
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "잘못된 아이템 번호입니다. 다시 입력해 주세요." << std::endl;
					}
					else
					{
						break;
					}
				}
				player->useItem(itemIndex);
				// sleep(1);
			}
			else if (inventoryChoice == 2) // 장비 해제
			{
				std::cout << "┌-----------------------------------------┐" << endl;
				std::cout << "│무기 해제[1], 방어구 해제[2], 돌아가기[3]│" << endl;
				std::cout << "└-----------------------------------------┘" << endl;
				int unequipChoice = 0;
				std::cout << "선택 입력 대기중 : ";

				while (true)
				{
					std::cin >> unequipChoice;
					if (std::cin.fail() || unequipChoice < 1 || unequipChoice > 3)
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
				system("cls"); // 선택 후 화면 지우기

				if (unequipChoice == 1) {
					player->unequipWeapon();
				}
				else if (unequipChoice == 2) {
					player->unequipArmor();
				}
				else {
					std::cout << "장비 해제를 취소합니다." << std::endl;
				}
				// sleep(1);
			}
			else if (inventoryChoice == 3) // 상태창 보기
			{
				player->displayStat();
				std::cout << "계속하려면 아무 키나 누르세요..." << std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 이전 입력 버퍼 비우기
				std::cin.get(); // 사용자 입력 대기
				// sleep(1);
			}
			else if (inventoryChoice == 4) // 나가기
			{
				break; // 인벤토리 메뉴를 빠져나와 주 메뉴로 돌아감
			}
		}
		return true; // 인벤토리 메뉴 루프가 끝나면 메인 게임 루프로 돌아감Add commentMore actions
	}
	else if (choice == 3)
	{
		Shop shop("떠돌이 장사꾼의 상점");
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
		std::cout << endl << endl <<  "[Game Over]" << endl << endl;

	}

	delete player;

	exit(0);
}