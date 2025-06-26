#include "Timeline.h"

Timeline::Timeline() {}

Timeline::~Timeline() {}

void Timeline::KillMonsterTimeline(std::time_t now_time_t, Character* character, Monster* monster)
{
	std::tm local_time_struct;
	errno_t err = localtime_s(&local_time_struct, &now_time_t);

	if (err != 0)
	{
		std::cerr << "����: �ð��� ��ȯ�� �� �����ϴ�. ���� �ڵ�: " << err << std::endl;
		return;
	}
	if (character == nullptr || monster == nullptr)
	{
		std::cerr << "ĳ���� �Ǵ� ������ ���� nullptr �Դϴ�." << std::endl;
		return;
	}
	std::stringstream ss;
	ss << std::put_time(&local_time_struct, "%Y-%m-%d %H:%M:%S");
	std::string time = ss.str();
	std::string monsterTimeline = "["+time+"]  "+character->getName()+"���� "+monster->getName()+"��(��) óġ�߽��ϴ�.";
	timelines.push_back(monsterTimeline);
}

void Timeline::GetItemTimeline(std::time_t now_time_t, Character* character, Item* item)
{
	std::tm local_time_struct;
	errno_t err = localtime_s(&local_time_struct, &now_time_t);

	if (err != 0)
	{
		std::cerr << "����: �ð��� ��ȯ�� �� �����ϴ�. ���� �ڵ�: " << err << std::endl;
		return;
	}
	if (character == nullptr || item == nullptr)
	{
		std::cerr << "ĳ���� �Ǵ� ������ ���� nullptr �Դϴ�." << std::endl;
		return;
	}
	std::stringstream ss;
	ss << std::put_time(&local_time_struct, "%Y-%m-%d %H:%M:%S");
	std::string time = ss.str();
	std::string itemTimeline = "[" + time + "]  " + character->getName() + "���� " + item->getName() + "��(��) ȹ���߽��ϴ�.";
	timelines.push_back(itemTimeline);
}

void Timeline::showTimeline()
{
	if (timelines.empty())
	{
		std::cout << "����� ����� �����ϴ�." << std::endl;
	}
	for (int i = 0; i < timelines.size(); i++)
	{
		std::cout << timelines[i] << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "óġ�� Goblin�� �� : " << CountTimeline("Goblin") << std::endl;
	std::cout << "óġ�� Orc�� �� : " << CountTimeline("Orc") << std::endl;
	std::cout << "óġ�� Slime�� �� : " << CountTimeline("Slime") << std::endl;
	std::cout << "óġ�� Skeleton�� �� : " << CountTimeline("Skeleton") << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "                                              ���ư���(1)  ";
	int choice = 0;
	while (true)
	{
		std::cin >> choice;
		if (std::cin.fail() || choice != 1)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
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