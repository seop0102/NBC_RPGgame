#pragma once

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

public:
	BattleManager() = default;
	~BattleManager() = default;


	bool doBattle(Character* player); //전투를 클리어 하면 true 아니면 false 반환

	Monster* CreateMonster(Character* player);
};