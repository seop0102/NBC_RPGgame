#include "Warrior.h"
#include "IClass.h"
#include "Character.h"
#include "Utils.h"
#include "Monster.h"

#include <iostream>

Warrior::Warrior() {
    // activeSkills 벡터에 직접 스킬 이름을 문자열로 추가
    activeSkills.push_back("기본 공격");
    activeSkills.push_back("베기");
    activeSkills.push_back("방패");
    activeSkills.push_back("강타");
    activeSkills.push_back("버티기");
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
        for (const auto& skill : activeSkills) {
                std::cout << count << ' ' << skill << std::endl; // 스킬 이름 출력
                count++;
        }

}

// 매개변수를 const std::string&으로 변경하고 내부 로직도 문자열 비교로 변경
void Warrior::useSkill(const std::string& skillName, Character& self, Monster& target) {
    if (skillName == "기본 공격") {
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 기본 공격을 시전합니다!" << std::endl;
        int damage = self.getAttack();
        target.takeDamage(damage);
    }
    else if (skillName == "베기") {
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 베기를 시전합니다!" << std::endl;
        int damage = self.getAttack() * 1.2; // 예시로 공격력의 120%
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
        if (Utils::checkChance(self.getCriticalChance())) { // Utils::checkChance는 예시 함수
            damage *= 2; // 치명타
            std::cout << "치명타 발동!" << std::endl;
        }
        target.takeDamage(damage);
    }
    else if (skillName == "버티기") {
        // Character.cpp의 useSkill에서 횟수 차감이 이미 처리됨
        std::cout << self.getName() << "이(가) 인내심으로 버티기를 사용합니다! 다음 턴에 죽지 않습니다." << std::endl;
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