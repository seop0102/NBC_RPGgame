#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IClass.h"
#include "Monster.h"
#include "Character.h"

class Archer : public IClass {
public:
	// isAimed�� wraithArrowDamage�� Character Ŭ���� ����� �̵������Ƿ� ���⼭ ����.
	// �ü� Ŭ���� ��ü�� �ʿ��� ������ ����� �ִٸ� ���⿡ �߰�.

	// ������ �߰� (���� ����������, ��������� ����ִ� �����ڶ� �δ� ���� ����)
	Archer();
	// �Ҹ��ڵ� �ʿ��ϴٸ� �߰� (�⺻ �Ҹ��� ��� �� = default)
	~Archer() override = default;



	std::string getClassName() const override { return "�ü�"; }
	// SkillType ��� std::string�� ��ȯ�ϴ� ���ͷ� ����
	std::vector<std::string> getActiveSkills() const override;
	// SkillType ��� const std::string&�� �Ű������� �޵��� ����
	void useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; }


private:
	// Archer�� Ȱ�� ��ų �̸��� ������ ����
	std::vector<std::string> activeSkills;
};