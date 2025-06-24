#pragma once

#include "BattleManager.h"
#include "StoryManager.h"
#include "Character.h"
#include "IClass.h"
#include "Rogue.h"
#include "Archer.h"
#include "Warrior.h"
#include "Monster.h"

using namespace std;

class BattleManager;
class StoryManager;
class Character;

class GameManager {

public:

	BattleManager* battleManager = nullptr;
	StoryManager* storyManager = nullptr;

	Character* player = nullptr;

public:
	GameManager();
	~GameManager();

	void startGame();

	void playGame();

	void endGame();

};