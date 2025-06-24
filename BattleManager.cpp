#include "BattleManager.h"


bool BattleManager::doBattle(Character* player)
{
	IClass* Cclass = player->getCharacterClass();

	Monster* monster = CreateMonster(player);

	if (player->getLevel() >= 10) {

		cout << "레벨 10 이상! 보스 몬스터가 등장합니다!" << endl;
		monster->setHealth(int(monster->getHealth() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장
		monster->setAttack(int(monster->getAttack() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장

	}

	while (player->getHealth() > 0 && monster->getHealth() > 0)
	{


		//전투 구현
		playerchoice(player, monster); // 플레이어가 스킬을 선택하는 함수 호출

		if (monster->getHealth() <= 0) {

			std::cout << "몬스터를 처치했습니다!" << std::endl;

			player->addGold(monster->getGold()); // 몬스터 처치 시 골드 추가

			if (monster->dropItem() != nullptr) {
				std::cout << "아이템을 획득했습니다: " << monster->dropItem()->getName() << std::endl;
				player->addItem(monster->dropItem()); // 플레이어에게 아이템 추가
			}

			player->addExp(EXP); // 몬스터 처치 시 경험치 추가

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

void BattleManager::playerchoice(Character* player, Monster* monster)
{
	IClass* Cclass = player->getCharacterClass();

	Cclass->showSkills(); // 캐릭터 클래스의 스킬 목록 출력

	int choice = 0;

	cout << "사용할 스킬을 선택하세요:" << endl;

	cin >> choice;

	Cclass->useSkill((Cclass->getSkillbyIndex(choice)), *player, *monster); // 선택한 스킬 사용
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