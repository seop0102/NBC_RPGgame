#include "BattleManager.h"

bool BattleManager::doBattle(Character* player)
{
	assert(player);
	IClass* Cclass = player->getCharacterClass();

	Monster* monster = CreateMonster(player);

	if (player->getLevel() >= 10) {

		std::cout << "레벨 10 이상! 보스 몬스터가 등장합니다!" << std::endl;
		monster->setHealth(int(monster->getHealth() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장
		monster->setAttack(int(monster->getAttack() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장
		monster->IsBoss = true;
	}

	while (player->getHealth() > 0 && monster->getHealth() > 0)
	{


		std::cout << "몬스터 정보 - 이름:  " << monster->getName() << " 공격력: " << monster->getAttack() << " 체력: " << monster->getHealth() << std::endl << std::endl;

		//전투 구현
		// 플레이어가 스킬을 선택하는 함수 호출
		attackMonster(player, playerchoice(player), monster);

		if (monster->getHealth() <= 0) {

			std::cout << "몬스터를 처치했습니다!" << std::endl;


			if (monster->IsBoss == true) ClearBoss = true;

			player->addGold(monster->getGold()); // 몬스터 처치 시 골드 추가

			Item* item= monster->dropItem();

			if (item != nullptr) {
				std::cout << "아이템을 획득했습니다: " << item->getName() << std::endl;
				player->addItem(item); // 플레이어에게 아이템 추가
			}

			player->addExp(EXP); // 몬스터 처치 시 경험치 추가

			player->setHealth(player->getMaxHealth());//체력회복

			player->initializeSkillUsages(); //스킬 사용 횟수 초기화
			player->initializeSkillEffect(); // 스킬 효과 제거

			delete monster;

			return true;
			break;
		}

		player->takeDamage(monster->getAttack()); // 몬스터의 공격으로 플레이어 피해
		std::cout << monster->getName() << "에게" << monster->getAttack() << "의 피해를 받았습니다." << std::endl << std::endl;

		if (player->getHealth() <= 0) {
			std::cout << "플레이어가 쓰러졌습니다!" << std::endl;

			delete monster;

			return false; // 전투 실패 이 후 게임종료 함수 부르기
			break;
		}
	}
}

std::string BattleManager::playerchoice(Character* player)
{
	while (true)
	{

		player->displayStat();

		IClass* Cclass = player->getCharacterClass();

		int ChoiceSize = Cclass->getActiveSkills().size() + 1;

		std::cout << "================================" << std::endl;
		Cclass->showSkills(); // 캐릭터 클래스의 스킬 목록 출력
		std::cout << ChoiceSize << " 아이템 사용하기" << std::endl << std::endl;
		std::cout << "================================" << std::endl;

		int choice = 0;
		std::cout << "번호를 입력해 선택하세요:" << std::endl;
		std::cout << "================================" << std::endl;
		while (true)
		{
			std::cin >> choice;
			if (std::cin.fail() || choice <= 0 || choice > ChoiceSize)
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


		if (choice > 0 && choice < ChoiceSize)


		{
			return Cclass->getSkillbyIndex(choice);

		}
		else if (choice == ChoiceSize) // "아이템 사용하기" 선택 시
		{
			player->showInventory();
			if (!(player->getInventory()).empty()) // 인벤토리가 비어있지 않다면
			{
				std::cout << "사용할 아이템을 선택하세요" << std::endl;
				while (true)
				{
					std::cin >> choice;
					if (std::cin.fail() || choice < 0 || choice >= static_cast<int>(player->getInventory().size()))
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
				Item* selectedItem = player->GetItemByIndex(choice);

				Consumable* consumable = dynamic_cast<Consumable*>(selectedItem);
				if (consumable != nullptr) {
					// 소모품이라면 Character::useItem 함수를 호출하여 사용
					player->useItem(choice);
					std::cout << "아이템을 사용했습니다." << std::endl;
					return "아이템 사용"; // 아이템 사용을 반환하여 전투 로직에 반영
				}
				else {
					// 소모품이 아니라면 전투 중 사용할 수 없음을 알림
					std::cout << "전투 중에는 소모품만 사용할 수 있습니다." << std::endl;
				}

			}
			else
			{
				std::cout << "사용할 수 없는 아이템이거나 잘못된 아이템 번호 입니다" << std::endl;
			}
		}
		else

		{
			// 당장은 처리할 것이 없음. (예: 잘못된 입력 후 재입력 대기)
		}


	}

}
void BattleManager::attackMonster(Character* player, std::string skill, Monster* monster)
{
	assert(player); assert(monster);
	bool crit = isCrit(player);

	if (skill == "조준" || skill == "방패" || skill == "버티기" || skill == "숨기") {

	}
	else if (isHit(player) != true && crit != true) {
		std::cout << "공격이 빗나갔습니다." << std::endl;

		std::cout << "남은 스킬 횟수: " << player->getRemainingSkillUsage(skill) << std::endl;
		
		return;
	}

	if (player->getWraithArrowDamage() > 0)

	{
		std::cout << "망령 화살이 폭발했습니다! 적에게 피해 " << player->getWraithArrowDamage() << std::endl;
		monster->takeDamage(player->getWraithArrowDamage());
		player->setWraithArrowDamage(0);
	}

	player->useSkill(skill, *player, *monster, crit); // 선택한 스킬 사용

	//std::cout << "몬스터의 남은 체력" << monster->getHealth() << std::endl;

	//std::cout << "남은 스킬 횟수: " << player->getRemainingSkillUsage(skill) << std::endl;
}

bool BattleManager::isCrit(Character* player)
{
	assert(player);
	return Utils::checkChance(player->getCriticalChance() * Utils::rollDice());
}

bool BattleManager::isDodge(Character* player)
{
	assert(player);
	return Utils::checkChance(player->getDodgeChance() * Utils::rollDice());
}

bool BattleManager::isHit(Character* player)
{
	assert(player);
	return Utils::checkChance(player->getHitChance());
}

Monster* BattleManager::CreateMonster(Character* player)
{
	assert(player);
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
	assert(player); assert(monster);
	if (player->getIsHiding())

	{
		std::cout << "공격을 회피했습니다" << std::endl;
		player->setIsHiding(false);
		return;
	}
		
	int defense = player->getDefense();
	int damage = monster->getAttack();

	damage = damage - (damage * (defense / 100));

	

	player->takeDamage(damage); // 몬스터의 공격으로 플레이어 피해
}