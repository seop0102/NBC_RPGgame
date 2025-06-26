#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Monster.h"
#include "Orc.h"
#include "Goblin.h"
#include "Character.h"
#include "Item.h"

class Timeline
{

private :
	std::time_t now_time_t;
	Character* character = nullptr;
	Monster* monster = nullptr;
	Item* item = nullptr;
	std::vector<std::string> timelines;

public :
	Timeline();
	~Timeline();

	void KillMonsterTimeline(std::time_t now_time_t, Character* character, Monster* monster);
	void GetItemTimeline(std::time_t now_time_t, Character* character, Item* item);


	void showTimeline();

	int CountTimeline(std::string s);

};

