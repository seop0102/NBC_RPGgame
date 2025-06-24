#pragma once

#include <string> // std::string을 사용하므로 추가
#include <vector> // std::vector를 사용하므로 추가
#include "IClass.h"
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


private:
	// Rogue가 활성 스킬 이름을 저장할 벡터
	std::vector<std::string> activeSkills;
};