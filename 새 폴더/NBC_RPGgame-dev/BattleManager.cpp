#include "BattleManager.h"


bool BattleManager::doBattle(Character* player)
{
	Monster* monster = CreateMonster(player);

	if (player->getLevel() >= 10) {

		cout << "레벨 10 이상! 보스 몬스터가 등장합니다!" << endl;
		monster->setHealth(int(monster->getHealth() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장
		monster->setAttack(int(monster->getAttack() * 1.5)); // 레벨 10 이상일 때 보스 몬스터 등장

	}

	while (player->getHealth() > 0 && monster->getHealth() > 0)
	{

		//전투 구현
		monster->takeDamage(player->getAttack());

		player->takeDamage(monster->getAttack());
		//

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

		if (player->getHealth() <= 0) {
			std::cout << "플레이어가 쓰러졌습니다!" << std::endl;

			delete monster;

			return false; // 전투 실패 이 후 게임종료 함수 부르기
			break;
		}
	}
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