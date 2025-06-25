#pragma once

#include <string>
#include <vector> 
#include <iostream> 
#include "IClass.h"
#include "Monster.h"
#include "Character.h"

class Rogue : public IClass {
public:
	// isHiding은 Character 클래스 멤버로 이동했으므로 여기서 제거.
	// 도적 클래스 자체에 필요한 고유한 멤버가 있다면 여기에 추가.

	// 생성자 추가
	Rogue();
	// 소멸자
	~Rogue() override = default;

	std::string getClassName() const override { return "도적"; }
	// SkillType 대신 std::string을 반환하는 벡터로 변경
	std::vector<std::string> getActiveSkills() const override;
	// SkillType 대신 const std::string&을 매개변수로 받도록 변경
	void useSkill(const std::string& skillName, Character& self, Monster& target) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; } // 스킬 인덱스 반환 함수 (필요시 구현)


private:
	// Rogue가 활성 스킬 이름을 저장할 벡터
	std::vector<std::string> activeSkills;
};