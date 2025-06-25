#pragma once

#include <string>
#include <vector> 
#include <iostream> 
#include "IClass.h"
#include "Monster.h"
#include "Character.h"

class Rogue : public IClass {
public:
	// isHiding�� Character Ŭ���� ����� �̵������Ƿ� ���⼭ ����.
	// ���� Ŭ���� ��ü�� �ʿ��� ������ ����� �ִٸ� ���⿡ �߰�.

	// ������ �߰�
	Rogue();
	// �Ҹ���
	~Rogue() override = default;

	std::string getClassName() const override { return "����"; }
	// SkillType ��� std::string�� ��ȯ�ϴ� ���ͷ� ����
	std::vector<std::string> getActiveSkills() const override;
	// SkillType ��� const std::string&�� �Ű������� �޵��� ����
	void useSkill(const std::string& skillName, Character& self, Monster& target) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; } // ��ų �ε��� ��ȯ �Լ� (�ʿ�� ����)


private:
	// Rogue�� Ȱ�� ��ų �̸��� ������ ����
	std::vector<std::string> activeSkills;
};