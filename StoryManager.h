#pragma once
#include <string>
#include <vector>
class StoryManager
{
public:
	StoryManager();
	~StoryManager() = default;
	void startPrologue();
	void askUsername(); // 이름 입력
	std::string getJob() const; //직업 반환
	std::string getMap() const; //맵 반환
	std::string getName() const; //유저 이름 반환

private:
	int totalScore = 0; //유저가 고른 정답의 점수 합 담을 변수
	std::string job = "";
	std::vector<std::string> map;
	std::string username = "";
	void showStory(); //흐름 관리
	void playPrologue();//이야기 시작
	void makeJobMap(); // 직업 맵 결정 + 출력
};