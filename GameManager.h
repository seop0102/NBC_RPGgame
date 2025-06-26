#pragma once

#include "BattleManager.h"
#include "StoryManager.h"
#include "Character.h"
#include "IClass.h"
#include "Rogue.h"
#include "Archer.h"
#include "Warrior.h"
#include "Monster.h"
#include "TradeManager.h"
#include "Shop.h"

using namespace std;

class BattleManager;
class StoryManager;
class Character;

class GameManager {

public:

	BattleManager* battleManager = nullptr;
	StoryManager* storyManager = nullptr;
	TradeManager* tradeManager = nullptr;
	Character* player = nullptr;

public:
	GameManager();
	~GameManager();

	void startGame();

	bool playGame();

	void endGame(bool IsClear);

};