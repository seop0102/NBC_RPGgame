#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IClass.h"
#include "Monster.h"
#include "Character.h"

class Archer : public IClass {
public:
	// isAimed와 wraithArrowDamage는 Character 클래스 멤버로 이동했으므로 여기서 제거.
	// 궁수 클래스 자체에 필요한 고유한 멤버가 있다면 여기에 추가.

	// 생성자 추가 (선택 사항이지만, 명시적으로 비어있는 생성자라도 두는 것이 좋음)
	Archer();
	// 소멸자도 필요하다면 추가 (기본 소멸자 사용 시 = default)
	~Archer() override = default;



	std::string getClassName() const override { return "궁수"; }
	// SkillType 대신 std::string을 반환하는 벡터로 변경
	std::vector<std::string> getActiveSkills() const override;
	// SkillType 대신 const std::string&을 매개변수로 받도록 변경
	void useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) override;
	void applyPassiveSkill(Character& self) override;
	void showSkills() const override;
	std::string getSkillbyIndex(int index) const override { return activeSkills[index-1]; }


private:
	// Archer가 활성 스킬 이름을 저장할 벡터
	std::vector<std::string> activeSkills;
};