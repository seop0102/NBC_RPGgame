#include "BattleManager.h"

bool BattleManager::doBattle(Character* player)
{
	IClass* Cclass = player->getCharacterClass();

	Monster* monster = CreateMonster(player);

	if (player->getLevel() >= 10) {

		std::cout << "레벨 10 이상! 보스 몬스터가 등장합니다!" << std::endl;
		monster->setHealth(int(monster->getHealth() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장
		monster->setAttack(int(monster->getAttack() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장

	}

	while (player->getHealth() > 0 && monster->getHealth() > 0)
	{


		std::cout << "몬스터 정보 - 이름:  " << monster->getName() << " 공격력: " << monster->getAttack() << " 체력: " << monster->getHealth() << std::endl;

		//전투 구현
		// 플레이어가 스킬을 선택하는 함수 호출
		attackMonster(player, playerchoice(player), monster);

		if (monster->getHealth() <= 0) {

			std::cout << "몬스터를 처치했습니다!" << std::endl;

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

			return true; // 전투 클리어
			break;
		}

		player->takeDamage(monster->getAttack()); // 몬스터의 공격으로 플레이어 피해
		std::cout << monster->getName() << "에게" << monster->getAttack() << "의 피해를 받았습니다." << std::endl;
		std::cout << player->getName() << "의 남은 체력 " << player->getHealth() << std::endl;

		player->displayStat();

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
		IClass* Cclass = player->getCharacterClass();

		int ChoiceSize = Cclass->getActiveSkills().size() + 1;

		Cclass->showSkills(); // 캐릭터 클래스의 스킬 목록 출력

		std::cout << ChoiceSize << " 아이템 사용하기" << std::endl;

		int choice = 0;

		std::cout << "번호를 입력해 선택하세요:" << std::endl;

		std::cin >> choice;

		system("cls");


		if (choice > 0 && choice < ChoiceSize)
			

		{
			return Cclass->getSkillbyIndex(choice);

		}
		else if (choice == ChoiceSize)

		{
			player->showInventory();
			if ((player->getInventory()).empty() != true)

			{
				std::cout << "사용할 아이템을 선택하세요" << std::endl;
				std::cin >> choice;

				Item* item = player->GetItemByIndex(choice);

				if (item != nullptr && item->getIsEquipped() == false)
				{
					item->use(*player);
				}
				else
				{
					std::cout << "사용할 수 없는 아이템이거나 잘못된 아이템 번호 입니다" << std::endl;
				}
			}
			else
			{
			}
		}

		else

		{
			std::cout << "잘못된 선택입니다" << std::endl;
		}


	}
}


	


void BattleManager::attackMonster(Character* player, std::string skill, Monster* monster)
{
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

	std::cout << "몬스터의 남은 체력" << monster->getHealth() << std::endl;

	std::cout << "남은 스킬 횟수: " << player->getRemainingSkillUsage(skill) << std::endl;
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
		std::cout << "공격을 회피했습니다" << std::endl;
		player->setIsHiding(false);
		return;
	}
		
	int defense = player->getDefense();
	int damage = monster->getAttack();

	damage = damage - (damage * (defense / 100));

	

	player->takeDamage(damage); // 몬스터의 공격으로 플레이어 피해
}