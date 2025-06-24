#pragma once

#include "BattleManager.h"
#include "ShopManager.h"
#include "StoryManager.h"
#include "Character.h"
#include "IClass.h"
#include "Rogue.h"
#include "Archer.h"
#include "Warrior.h"
#include "Monster.h"

using namespace std;

class BattleManager;
class ShopManager;
class StoryManager;
class Character;

class GameManager {

public:

	BattleManager* battleManager = nullptr;
	ShopManager* shopManager = nullptr;
	StoryManager* storyManager = nullptr;

	Character* player = nullptr;

public:
	GameManager();
	~GameManager();

	void startGame();

	void playGame();

	void endGame();

};