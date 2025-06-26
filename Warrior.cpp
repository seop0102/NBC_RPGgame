#include "Warrior.h"
#include "IClass.h"
#include "Character.h"
#include "Utils.h"
#include "Monster.h"

#include <iostream>

Warrior::Warrior() {
    // activeSkills 벡터에 직접 스킬 이름을 문자열로 추가
    activeSkills.push_back("기본 공격");
    SkillDescription.push_back(" (공격력의 100% 데미지를 줍니다)");

    activeSkills.push_back("베기");
    SkillDescription.push_back(" (공격력의 120% 데미지를 줍니다)");

    activeSkills.push_back("방패");
    SkillDescription.push_back(" (방패를 올려 방어력을 올립니다)");

    activeSkills.push_back("강타");
    SkillDescription.push_back(" (치명타 피해가 높은 공격을 합니다)");

    activeSkills.push_back("버티기");
    SkillDescription.push_back(" (다음 공격에 피해를 받아도 쓰러지지 않습니다)");
}

std::string Warrior::getClassName() const {
    return "전사";
}

// std::vector<std::string>을 반환하도록 변경
std::vector<std::string> Warrior::getActiveSkills() const {
    return activeSkills;
}

void Warrior::showSkills() const
{
        int count = 1;
        for (int i = 0; i < activeSkills.size(); i++) {
                std::cout << count << ' ' << activeSkills[i] << ' ' << SkillDescription[i] << std::endl; // 스킬 이름 출력
                count++;
        }

}

// 매개변수를 const std::string&으로 변경하고 내부 로직도 문자열 비교로 변경
void Warrior::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) {
    if (skillName == "기본 공격") {
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 기본 공격을 시전합니다!" << std::endl;
        int damage = self.getAttack();

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "베기") {
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 베기를 시전합니다!" << std::endl;
        int damage = self.getAttack() * 1.2; // 예시로 공격력의 120%

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "방패") {
        std::cout << self.getName() << "이(가) 방패를 들어 방어 태세를 취합니다!" << std::endl;
        self.setIsShielded(true); // Character 클래스에 isShielded 상태 추가 및 세터 필요
        self.setDefense(self.getDefense() + 10); // 임시로 방어력 증가 예시
    }
    else if (skillName == "강타") {
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 강타를 시전합니다!" << std::endl;
        int damage = self.getAttack() * 1.5; // 강한 공격

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage * 2);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "버티기") {
        // Character.cpp의 useSkill에서 횟수 차감이 이미 처리됨
        self.setHasIndomitableWill(true); // Character에 hasIndomitableWill 상태 추가 및 세터 필요
    }
    else {
        std::cout << "알 수 없는 전사 스킬입니다: " << skillName << std::endl;
    }
}

void Warrior::applyPassiveSkill(Character& self) {
    std::cout << "전사의 패시브 스킬 '강인함'이 적용됩니다. 최대 체력 +50." << std::endl;
    self.setMaxHealth(self.getMaxHealth() + 50);
    self.setHealth(self.getMaxHealth()); // 체력도 최대치로 회복
}