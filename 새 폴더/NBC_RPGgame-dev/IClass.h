#pragma once

#include <string>
#include <iostream>
#include <vector>

class Character;
class Monster;

class IClass {
public:
	virtual ~IClass() = default; // 가상 소멸자

	virtual std::string getClassName() const = 0;
	// SkillType 대신 std::string 사용하도록 변경
	virtual std::vector<std::string> getActiveSkills() const = 0;
	// SkillType 대신 const std::string& 사용하도록 변경
	virtual void useSkill(const std::string& skillName, Character& self, Monster& target) = 0;
	virtual void applyPassiveSkill(Character& self) = 0;
};