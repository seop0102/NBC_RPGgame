#pragma once

#include <string>
#include <vector>
#include "IClass.h"
#include "Monster.h"
#include "Character.h"


class Warrior : public IClass { // IClass ���
public:
	Warrior();
	~Warrior() override = default;

	std::string getClassName() const override; // SkillType ��� std::string ��ȯ�ϵ��� ����
	std::vector<std::string> getActiveSkills() const override; // SkillType ��� const std::string& �Ű����� �޵��� ����
	void useSkill(const std::string& skillName, Character& self, Monster& target) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; } // ��ų �ε��� ��ȯ �Լ� (�ʿ�� ����)

private:
	// SkillType ��� std::string�� �����ϵ��� ����
	std::vector<std::string> activeSkills; // ��ų �̸� ��� (std::string)
};