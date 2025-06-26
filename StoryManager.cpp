#define NOMINMAX
#include "StoryManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include <limits>
#include <chrono>
#include <thread>
#include <locale>
#include <codecvt> // std::wstring_convert, std::codecvt_utf8_utf16
#define FORE_CYAN (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FORE_DEFAULT (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FORE_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
void set_console_color(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
StoryManager::StoryManager() {} //초기화 시켜주기
//나중에 startPrologue만 호출하면 됨
void StoryManager::startPrologue() { //전체 프롤로그 실행
	//showLogo();
	aaaaa();
	//showStory(); //이야기 보여줌
	//makeJobMap(); //totalnum으로 직업과 맵(던전) 결정
}
/*void StoryManager::showStory() {
	playPrologue(); //직업 선택 문제 5개
	askUsername(); // 유저 이름 입력
}
void printSlow(const std::string& text, int delay = 50) {
	for (char c : text) {
		std::cout << c;
		std::cout.flush(); // 즉시 출력
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << std::endl;
} */
// 테스트를 위해 다른거 다 주석 처리하고 이거만 실행
void StoryManager::aaaaa() {
	job = "도적";
	map = { "안개의 숲", "안개의 숲 초입", "짙은 안개의 숲", "괴물들의 숲 " , "폐허가 된 마을", "수상한 제단", "종말의 전당" };
	username = "hi";
}
/*  여기서 부터 주석 해제하면 됨
//*
// _____  _    _ _   _  _____ ______ ____  _   _   _____ _      _
//|  __ \| |  | | \ | |/ ____|  ____/ __ \| \ | | |  __ (_)    | |
//| |  | | |  | |  \| | |  __| |__ | |  | |  \| | | |__) |  ___| | __
//| |  | | |  | | . ` | | |_ |  __|| |  | | . ` | |  ___/ |/ __| |/ /
//| |__| | |__| | |\  | |__| | |___| |__| | |\  | | |   | | (__|   <
//|_____/ \____/|_| \_|\_____|______\____/|_| \_| |_|   |_|\___|_|\_\
//
void StoryManager::showLogo() {
	std::cout << "\n로딩 중";
	for (int i = 0; i < 3; ++i) {
		Sleep(500);
		std::cout << "." << std::flush;
	}
	Sleep(500);
	system("cls");
	set_console_color(FOREGROUND_INTENSITY);
	std::cout << "======================================================================\n" << std::endl;
	set_console_color(FORE_YELLOW);
	std::cout << R"( _____  _    _ _   _  _____ ______ ____  _   _    _____ _      _
|  __ \| |  | | \ | |/ ____|  ____/ __ \| \ | |  |  __ (_)    | |
| |  | | |  | |  \| | |  __| |__ | |  | |  \| |  | |__) |  ___| | __
| |  | | |  | | . ` | | |_ |  __|| |  | | . ` |  |  ___/ |/ __| |/ /
| |__| | |__| | |\  | |__| | |___| |__| | |\  |  | |   | | (__|   <
|_____/ \____/|_| \_|\_____|______\____/|_| \_|  |_|   |_|\___|_|\_\
																   )";
	set_console_color(FOREGROUND_INTENSITY);
	std::cout << "\n======================================================================\n" << std::endl;
	set_console_color(FORE_DEFAULT);
	std::cout << "\nPress 1 : 게임 시작\nPress 2 : 게임 종료 \n";
	int choice = 0;
	while (true) {
		std::cout << "\n번호를 입력하세요 : ";
		std::cin >> choice;
		if (choice == 1) {
			system("cls");
			break;
		}
		else if (choice == 2) {
			std::cout << "게임을 종료합니다. \n";
			exit(0);
		}
		else {
			std::cout << " 1 또는 2 중에 다시 입력해주세요. \n";
		}
	}
}
void StoryManager::playPrologue() {
	std::vector<std::string> prologue = {
		//그냥 이야기 + 선택지 3개
		"어둡고 낯선 숲 속을 헤매는 당신. \n\n기억은 흐릿하고, 어디서 왔는지, 왜 이곳에 있는지조차 알 수 없습니다. \n\n앙상한 나뭇가지들이 손짓하는 듯하고, 발밑의 마른 낙엽은 걷는 내내 스산한 소리를 냅니다. \n\n방향을 가늠하려 고개를 들지만, 빽빽한 나무들 사이로 보이는 것은 희미한 달빛뿐입니다.\n\n\n\n================================================================================\n" ,
		"얼마나 시간이 흘렀을까, 짙은 풀숲 너머로 무언가 보입니다.  \n\n본능적으로 발걸음을 멈추고 몸을 숨깁니다. \n가까이 다가가자 싸늘한 공기가 피부를 스칩니다.  \n잔뜩 웅크린 채 풀숲을 헤치고 나선 곳에는, 피 묻은 검을 움켜쥔 채 쓰러져 있는 시체 하나가 있었습니다.  \n\n고통스러운 표정, 낡은 가죽 갑옷… 이곳에서 무슨 일이 벌어진 걸까요?  \n\n심장이 불길하게 요동치기 시작합니다. \n\n================================================================================\n" ,
		"그 순간, 거친 발소리가 들려옵니다.  \n\n나뭇가지 꺾이는 소리, 욕설 섞인 대화가 점점 가까워집니다. \n\n도적떼였습니다.\n\n \"젠장, 쥐새끼 한 마리 놓쳤나 ? " "괜찮아, 이거나 챙겨가자고.\" \n\n그들은 시체를 뒤져 무언가를 챙기고는, 숲을 빠져나가려 합니다. \n\n================================================================================\n",
		"도적들이 막 숲을 벗어나려 할 때였습니다.  \n\n풀숲에서 끙끙거리는 소리가 들려옵니다.  \n\n한 사람이 쓰러져 있었습니다.  \n\n아마 도적들에게 당한 듯, 옷은 찢겨 있고 상처에서 피가 흐르고 있었습니다.  \n\n도적들은 그를 발견하지 못한 모양입니다. \n\n================================================================================\n",
		"얼마 후, 희미한 불빛이 보입니다.  \n\n마침내 작은 마을에 도착한 것입니다.  \n\n당신의 도움 덕분에 그는 무사히 마을 사람들에게 인계되었고, \n당신은 그들에게서 따뜻한 환대와 함께 잠시 쉴 곳을 얻게 됩니다.  \n\n모닥불의 온기, 사람들의 목소리가 불안했던 마음을 조금은 누그러뜨립니다. \n\n\n================================================================================\n",
		"\n\n\n\n 긴 여정 끝에 찾아온 짧은 평화. \n하지만 당신의 이야기는 이제 시작될 뿐입니다. \n잃어버린 기억을 찾고, 이 낯선 세계에서 당신의 운명을 개척해야 합니다.\n\n\n\n\n"
	};
	std::vector<std::string> answer = {
		"1) 나무 아래에 몸을 숨긴 채 주위를 살핀다.",
		"2) 조심스레 숲길을 따라 움직인다.",
		"3) 가방에서 횃불을 꺼내 앞으로 나아간다.",
		"1) 시체에게서 최대한 멀리 도망친다.",
		"2) 시체를 조사해본다.",
		"3) 시체를 덮고, 함정을 의심하며 주변을 경계한다.",
		"1) 이대로 지나가게 둔다.",
		"2) 돌을 던져 소란을 일으키고 도적들을 유인한다.",
		"3) 도적들의 뒤를 밟는다.",
		"1) 멀리서 상황을 지켜본다.",
		"2) 조용히 다가가 상태를 확인한다.",
		"3) 쓰러진 사람을 구하러간다.",
		"1) 마을을 지나친다.",
		"2) 여관으로 들어간다.",
		"3) 술집에 들어간다."
	};
	for (int i = 0; i < 5; ++i) {
		//문제 출력
		std::cout << "================================================================================" << std::endl;
		printSlow(".", 500);
		printSlow(".", 500);
		printSlow(".\n", 500);
		// 프롤로그 문장은 한 번에 출력
		std::cout << "\n" << prologue[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3)); // 3초 대기
		for (int j = 0; j < 3; j++) {
			std::cout << answer[i * 3 + j] << "\n"<<std::endl;
		}
		std::cout << "================================================================================" << std::endl;
		int userChoice = 0;
		std::cout << "\n번호를 입력하세요 : ";
		while (true)
		{	
			std::cin >> userChoice;
			if (std::cin.fail() || userChoice < 1 || userChoice > 3)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "1,2,3 중에서 다시 입력해주세요." << std::endl;
			}
			else
			{
				break;
			}
		}
		totalScore += userChoice;
		system("cls");
	}
	printSlow(prologue[5], 50);
}
void StoryManager::askUsername() {
	std::string input;
	while (true) {
		// 입력 버퍼에 남아있는 개행문자 및 공백을 무시합니다.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::cout << "당신의 이름은 ? : ";
		std::getline(std::cin, input);  // 공백 포함한 값 그대로 받기
		bool is_all_whitespace = true;
		if (input.empty()) {
			is_all_whitespace = true;
		}
		else {
			// 로케일 기준 공백 아닌 문자가 있는지 확인
			for (char c : input) {
				if (!std::isspace(static_cast<unsigned char>(c), std::locale())) {
					is_all_whitespace = false;
					break;
				}
			}
		}
		if (is_all_whitespace) {
			std::cout << "이름은 공백만 있을 수 없습니다. 다시 입력해주세요. Press Enter" << std::endl;
		}
		else if (input.find(' ') != std::string::npos) {
			std::cout << "이름에 공백을 포함할 수 없습니다. 다시 입력해주세요. Press Enter" << std::endl;
		}
		else {
			break;  // 유효한 이름
		}
	}
	username = input;
	system("cls"); // 화면 초기화
}
void StoryManager::makeJobMap() {
	if (totalScore <= 8) {
		job = "도적";
		map = { "안개의 숲", "안개의 숲 초입", "짙은 안개의 숲", "괴물들의 숲 " , "폐허가 된 마을", "수상한 제단", "종말의 전당" };
	}
	else if (totalScore <= 11) {
		job = "궁수";
		map = { "균형의 동굴" , "균형의 동굴초입", "균형의 동굴", "거미굴" , "핏빛 통로" , "둥지 입구" , "용의 안식처" };
	}
	else {
		job = "검사";
		map = { "망자의 감옥" , "망자의 감옥 초입", "망자의 감옥", "불안정한 균열" , "저주받은 통로", "저주받은 무덤 입구", " 망자의 무덤" };
	}
	std::cout << username << "님 환영합니다.\n" << std::endl;
	std::cout << "===================================" << std::endl;
	std::cout << "\n       당신의 직업 : " << job << std::endl;
	std::cout << "\n       던전        : " << map[0] << std::endl;
	std::cout << "\n===================================\n" << std::endl;
}
여기 까지 해제           */
std::string StoryManager::getJob() const {
	return job;
}
std::string StoryManager::getMap() const {
	if (!map.empty()) return map[0];
	else return "맵 없음";
}
std::string StoryManager::getName() const
{
	return username;
}