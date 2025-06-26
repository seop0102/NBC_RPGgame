#pragma once

#include <string>

#include "Character.h"
#include "Monster.h"
#include "Orc.h"
#include "Goblin.h"
#include "Utils.h"

enum class MonsterType {
	Orc,
	Goblin
};

class BattleManager
{
private:
	const int EXP = 50;
	bool ClearBoss = false;
	
public:
	BattleManager() = default;
	~BattleManager() = default;


	bool doBattle(Character* player); //전투를 클리어 하면 true 아니면 false 반환

	std::string playerchoice(Character* player); //플레이어가 스킬을 선택하는 함수

	void attackMonster(Character* player, std::string skill, Monster* monster);

	void attackPlayer(Character* player, Monster* monster);

	bool isCrit(Character* player);

	bool isDodge(Character* player);

	bool isHit(Character* player);

	bool GetIsClearBoss() { return ClearBoss; }


	Monster* CreateMonster(Character* player);
};