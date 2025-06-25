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
	
public:
	BattleManager() = default;
	~BattleManager() = default;


	bool doBattle(Character* player); //������ Ŭ���� �ϸ� true �ƴϸ� false ��ȯ

	std::string playerchoice(Character* player); //�÷��̾ ��ų�� �����ϴ� �Լ�

	void attackMonster(Character* player, std::string skill, Monster* monster);

	bool isCrit(Character* player);

	bool isDodge(Character* player);

	bool isHit(Character* player);


	Monster* CreateMonster(Character* player);
};