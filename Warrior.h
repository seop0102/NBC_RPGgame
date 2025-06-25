#pragma once

#include <string>
#include <vector>
#include "IClass.h"
#include "Monster.h"
#include "Character.h"


class Warrior : public IClass { // IClass 상속
public:
	Warrior();
	~Warrior() override = default;

	std::string getClassName() const override; // SkillType 대신 std::string 반환하도록 변경
	std::vector<std::string> getActiveSkills() const override; // SkillType 대신 const std::string& 매개변수 받도록 변경
	void useSkill(const std::string& skillName, Character& self, Monster& target) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; } // 스킬 인덱스 반환 함수 (필요시 구현)

private:
	// SkillType 대신 std::string을 저장하도록 변경
	std::vector<std::string> activeSkills; // 스킬 이름 목록 (std::string)
};