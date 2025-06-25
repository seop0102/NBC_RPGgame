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


		//전투 구현
		// 플레이어가 스킬을 선택하는 함수 호출
		attackMonster(player, playerchoice(player), monster);

		if (monster->getHealth() <= 0) {

			std::cout << "몬스터를 처치했습니다!" << std::endl;

			player->addGold(monster->getGold()); // 몬스터 처치 시 골드 추가

			if (monster->dropItem() != nullptr) {
				std::cout << "아이템을 획득했습니다: " << monster->dropItem()->getName() << std::endl;
				player->addItem(monster->dropItem()); // 플레이어에게 아이템 추가
			}

			player->addExp(EXP); // 몬스터 처치 시 경험치 추가

			player->initializeSkillUsages(); //스킬 사용 횟수 초기화
			player->initializeSkillEffect(); // 스킬 효과 제거

			delete monster;

			return true; // 전투 클리어
			break;
		}

		player->takeDamage(monster->getAttack()); // 몬스터의 공격으로 플레이어 피해

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
	IClass* Cclass = player->getCharacterClass();

	Cclass->showSkills(); // 캐릭터 클래스의 스킬 목록 출력

	int choice = 0;

	std::cout << "사용할 스킬을 선택하세요:" << std::endl;

	std::cin >> choice;

	return Cclass->getSkillbyIndex(choice);
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