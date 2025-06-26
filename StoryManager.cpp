#include "StoryManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <algorithm> // std::all_of
#include <limits> // std::numeric_limits
#include <chrono>
#include <thread>
#include<locale>
#include <codecvt> // std::wstring_convert, std::codecvt_utf8_utf16
StoryManager::StoryManager() {} //�ʱ�ȭ �����ֱ�
//���߿� startPrologue�� ȣ���ϸ� ��
void StoryManager::startPrologue() { //��ü ���ѷα� ����
	showStory(); //�̾߱� ������
	makeJobMap(); //totalnum���� ������ ��(����) ����
}
void StoryManager::showStory() {
	playPrologue(); //���� ���� ���� 5��
	askUsername(); // ���� �̸� �Է�
}
void printSlow(const std::string& text, int delay = 50) {
	for (char c : text) {
		std::cout << c;
		std::cout.flush(); // ��� ���
		//std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << std::endl;
}
void StoryManager::playPrologue() {
	std::vector<std::string> prologue = {
		//�׳� �̾߱� + ������ 3��
		"��Ӱ� ���� �� ���� ��Ŵ� ���. \n\n����� �帴�ϰ�, ��� �Դ���, �� �̰��� �ִ������� �� �� �����ϴ�. \n\n�ӻ��� ������������ �����ϴ� ���ϰ�, �߹��� ���� ������ �ȴ� ���� ������ �Ҹ��� ���ϴ�. \n\n������ �����Ϸ� ���� ������, ������ ������ ���̷� ���̴� ���� ����� �޺����Դϴ�.\n\n\n\n================================================================================\n\n\n" ,
		"�󸶳� �ð��� �귶����, £�� Ǯ�� �ʸӷ� ���� ���Դϴ�.  \n\n���������� �߰����� ���߰� ���� ����ϴ�. \n������ �ٰ����� �δ��� ���Ⱑ �Ǻθ� ��Ĩ�ϴ�.  \n�ܶ� ��ũ�� ä Ǯ���� ��ġ�� ���� ������, �� ���� ���� ������ ä ������ �ִ� ��ü �ϳ��� �־����ϴ�.  \n\n���뽺���� ǥ��, ���� ���� ���ʡ� �̰����� ���� ���� ������ �ɱ��?  \n\n������ �ұ��ϰ� �䵿ġ�� �����մϴ�. \n\n================================================================================\n\n\n" ,
		"�� ����, ��ģ �߼Ҹ��� ����ɴϴ�.  \n\n�������� ���̴� �Ҹ�, �弳 ���� ��ȭ�� ���� ��������ϴ�. \n\n�����������ϴ�.\n\n \"����, ����� �� ���� ���Ƴ� ? " "������, �̰ų� ì�ܰ��ڰ�.\" \n\n�׵��� ��ü�� ���� ���𰡸� ì����, ���� ���������� �մϴ�. \n\n================================================================================\n\n\n",
		"�������� �� ���� ����� �� �������ϴ�.  \n\nǮ������ �����Ÿ��� �Ҹ��� ����ɴϴ�.  \n\n�� ����� ������ �־����ϴ�.  \n\n�Ƹ� �����鿡�� ���� ��, ���� ���� �ְ� ��ó���� �ǰ� �帣�� �־����ϴ�.  \n\n�������� �׸� �߰����� ���� ����Դϴ�. \n\n================================================================================\n\n\n",
		"�� ��, ����� �Һ��� ���Դϴ�.  \n\n��ħ�� ���� ������ ������ ���Դϴ�.  \n\n����� ���� ���п� �״� ������ ���� ����鿡�� �ΰ�Ǿ���, \n����� �׵鿡�Լ� ������ ȯ��� �Բ� ��� �� ���� ��� �˴ϴ�.  \n\n��ں��� �±�, ������� ��Ҹ��� �Ҿ��ߴ� ������ ������ ���׷��߸��ϴ�. \n\n\n================================================================================\n\n\n",
		"\n\n\n\n �� ���� ���� ã�ƿ� ª�� ��ȭ. \n������ ����� �̾߱�� ���� ���۵� ���Դϴ�. \n�Ҿ���� ����� ã��, �� ���� ���迡�� ����� ����� ��ô�ؾ� �մϴ�.\n\n\n\n\n"
	};
	std::vector<std::string> answer = {
		"1)���� �Ʒ��� ���� ���� ä ������ ���ɴ�.",
		"2) ���ɽ��� ������ ���� �����δ�.",
		"3) ���濡�� ȶ���� ���� ������ ���ư���.",
		"1) ��ü���Լ� �ִ��� �ָ� ����ģ��.",
		"2) ��ü�� �����غ���.",
		"3) ��ü�� ����, ������ �ǽ��ϸ� �ֺ��� ����Ѵ�.",
		"1) �̴�� �������� �д�.",
		"2) ���� ���� �Ҷ��� ����Ű�� �������� �����Ѵ�.",
		"3) �������� �ڸ� ��´�.",
		"1) �ָ��� ��Ȳ�� ���Ѻ���.",
		"2) ������ �ٰ��� ���¸� Ȯ���Ѵ�.",
		"3) ������ ����� ���Ϸ�����.",
		"1) ������ ����ģ��.",
		"2) �������� ����.",
		"3) ������ ����."
	};
	for (int i = 0; i < 5; ++i) {
		//���� ���
		std::cout << "================================================================================ \n\n ����" << std::endl;
		std::cout << "\n\n\n" << prologue[i] << std::endl;
		//std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���
		for (int j = 0; j < 3; j++) {
			//std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���
			std::cout << answer[i * 3 + j] << std::endl; //�亯 ���
		}
		std::cout << "================================================================================" << std::endl;
		int userChoice = 0;
		while (true) {
			std::cout << "\n��ȣ�� �Է��ϼ��� : ";
			std::cin >> userChoice;
			if (userChoice >= 1 && userChoice <= 3) {
				break;
			}
			else {
				std::cout << "1,2,3 �߿��� �ٽ� �Է����ּ���." << std::endl;
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
		// �Է� ���ۿ� �����ִ� ���๮�� �� ������ �����մϴ�.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
		std::cout << "����� �̸��� ? : ";
		std::getline(std::cin, input);  // ���� ������ �� �״�� �ޱ�
		bool is_all_whitespace = true;
		if (input.empty()) {
			is_all_whitespace = true;
		}
		else {
			// ������ ���� ���� �ƴ� ���ڰ� �ִ��� Ȯ��
			for (char c : input) {
				if (!std::isspace(static_cast<unsigned char>(c), std::locale())) {
					is_all_whitespace = false;
					break;
				}
			}
		}
		if (is_all_whitespace) {
			std::cout << "�̸��� ���鸸 ���� �� �����ϴ�. �ٽ� �Է����ּ���. Press Enter" << std::endl;
		}
		else if (input.find(' ') != std::string::npos) {
			std::cout << "�̸��� ������ ������ �� �����ϴ�. �ٽ� �Է����ּ���. Press Enter" << std::endl;
		}
		else {
			break;  // ��ȿ�� �̸�
		}
	}
	username = input;
	system("cls"); // ȭ�� �ʱ�ȭ
}
void StoryManager::makeJobMap() {
	if (totalScore <= 8) {
		job = "����";
		map = { "�Ȱ��� ��", "�Ȱ��� �� ����", "£�� �Ȱ��� ��", "�������� �� " , "���㰡 �� ����", "������ ����", "������ ����" };
	}
	else if (totalScore <= 11) {
		job = "�ü�";
		map = { "������ ����" , "������ ��������", "������ ����", "�Ẕ́�" , "�ͺ� ���" , "���� �Ա�" , "���� �Ƚ�ó" };
	}
	else {
		job = "�˻�";
		map = { "������ ����" , "������ ���� ����", "������ ����", "�Ҿ����� �տ�" , "���ֹ��� ���", "���ֹ��� ���� �Ա�", " ������ ����" };
	}
	std::cout << username << "�� ȯ���մϴ�.\n" << std::endl;
	std::cout << "===================================" << std::endl;
	std::cout << "\n       ����� ���� : " << job << std::endl;
	std::cout << "\n       ����        : " << map[0] << std::endl;
	std::cout << "\n===================================\n" << std::endl;
}
std::string StoryManager::getJob() const {
	return job;
}
std::string StoryManager::getMap() const {
	if (!map.empty()) return map[0];
	else return "�� ����";
}
std::string StoryManager::getName() const
{
	return username;
}