#pragma once

#include <string>
#include <vector>
#include "IClass.h"
#include "Character.h"


class Warrior : public IClass { // IClass 상속
public:
	Warrior();
	~Warrior() override = default;

	std::string getClassName() const override; // SkillType 대신 std::string 반환하도록 변경
	std::vector<std::string> getActiveSkills() const override; // SkillType 대신 const std::string& 매개변수 받도록 변경
	void useSkill(const std::string& skillName, Character& self, Monster& target) override;
	void applyPassiveSkill(Character& self) override;

private:
	// SkillType 대신 std::string을 저장하도록 변경
	std::vector<std::string> activeSkills; // 스킬 이름 목록 (std::string)
};