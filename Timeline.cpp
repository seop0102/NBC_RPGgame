#include "Timeline.h"

Timeline::Timeline() {}

Timeline::~Timeline() {}

void Timeline::KillMonsterTimeline(std::time_t now_time_t, Character* character, Monster* monster)
{
	std::tm local_time_struct;
	errno_t err = localtime_s(&local_time_struct, &now_time_t);

	if (err != 0)
	{
		std::cerr << "오류: 시간을 변환할 수 없습니다. 에러 코드: " << err << std::endl;
		return;
	}
	if (character == nullptr || monster == nullptr)
	{
		std::cerr << "캐릭터 또는 몬스터의 값이 nullptr 입니다." << std::endl;
		return;
	}
	std::stringstream ss;
	ss << std::put_time(&local_time_struct, "%Y-%m-%d %H:%M:%S");
	std::string time = ss.str();
	std::string monsterTimeline = "["+time+"]  "+character->getName()+"님이 "+monster->getName()+"을(를) 처치했습니다.";
	timelines.push_back(monsterTimeline);
}

void Timeline::GetItemTimeline(std::time_t now_time_t, Character* character, Item* item)
{
	std::tm local_time_struct;
	errno_t err = localtime_s(&local_time_struct, &now_time_t);

	if (err != 0)
	{
		std::cerr << "오류: 시간을 변환할 수 없습니다. 에러 코드: " << err << std::endl;
		return;
	}
	if (character == nullptr || item == nullptr)
	{
		std::cerr << "캐릭터 또는 몬스터의 값이 nullptr 입니다." << std::endl;
		return;
	}
	std::stringstream ss;
	ss << std::put_time(&local_time_struct, "%Y-%m-%d %H:%M:%S");
	std::string time = ss.str();
	std::string itemTimeline = "[" + time + "]  " + character->getName() + "님이 " + item->getName() + "을(를) 획득했습니다.";
	timelines.push_back(itemTimeline);
}

void Timeline::showTimeline()
{
	if (timelines.empty())
	{
		std::cout << "저장된 기록이 없습니다." << std::endl;
	}
	for (int i = 0; i < timelines.size(); i++)
	{
		std::cout << timelines[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "처치한 Goblin의 수 : " << CountTimeline("Goblin") << std::endl;
	std::cout << "처치한 Orc의 수 : " << CountTimeline("Orc") << std::endl;
	std::cout << "처치한 Slime의 수 : " << CountTimeline("Slime") << std::endl;
	std::cout << "처치한 Skeleton의 수 : " << CountTimeline("Skeleton") << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "                                              돌아가기(1)  ";
	int choice = 0;
	while (true)
	{
		std::cin >> choice;
		if (std::cin.fail() || choice != 1)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "잘못된 입력입니다. 다시 입력해 주세요." << std::endl;
		}
		else
		{
			break;
		}
	}
	system("cls");
}

int Timeline::CountTimeline(std::string s)
{	
	int count = 0;
	for (int i = 0; i < timelines.size(); i++)
	{
		size_t found_pos = timelines[i].find(s, 0);
		if(found_pos != std::string::npos)
		{
			count++;
		}
	}
	return count;
}