#include "Archer.h"
#include "IClass.h"
#include "Character.h"
#include "Utils.h"
#include "Monster.h"



Archer::Archer() {
    activeSkills.push_back("기본 공격");
    SkillDescription.push_back(" (공격력의 100% 데미지를 줍니다)");

    activeSkills.push_back("화살 명중");
    SkillDescription.push_back(" (조준 상태면 화살이 반드시 명중하며 추가 피해를 입힙니다)");

    activeSkills.push_back("조준");
    SkillDescription.push_back(" (조준 합니다)");

    activeSkills.push_back("폭풍 화살");
    SkillDescription.push_back(" (공격력의 60% 피해로 여러번 공격합니다)");

    activeSkills.push_back("망령 화살");
    SkillDescription.push_back(" (다음턴에 큰 피해를 주는 화살을 발사합니다)");
}

namespace {
    // 내부 헬퍼 함수들도 SkillType 대신 std::string 사용하도록 수정
    void performArcher1(Character& self, Monster& target, bool isCrit); // 화살 명중
    void performArcher2(Character& self, Monster& target); // 조준
    void performArcher3(Character& self, Monster& target, bool isCrit); // 폭풍 화살
    void performArcher4(Character& self, Monster& target); // 망령 화살
}

std::vector<std::string> Archer::getActiveSkills() const {
    return activeSkills; // 생성자에서 초기화된 스킬 목록 반환
}

void Archer::applyPassiveSkill(Character& self) {
    self.setHitChance(self.getHitChance() + 15);
    std::cout << "[패시브 발동] " << self.getName() << "은(는) 매의 눈으로 명중률이 15% 증가했습니다! 현재 명중률: " << self.getHitChance() << "%" << std::endl;
}

void Archer::showSkills() const
{
        int count = 1;
        for (int i = 0; i < activeSkills.size(); i++) {
                std::cout << count << ' ' << activeSkills[i] <<  ' ' << SkillDescription[i] << std::endl; // 스킬 이름 출력
                count++;
        }
        
}

// SkillType 대신 const std::string&을 매개변수로 받도록 변경
void Archer::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) {
    // switch 문 대신 if-else if 문으로 문자열 비교
    if (skillName == "화살 명중") {
        performArcher1(self, target, isCrit);
    }
    else if (skillName == "조준") {
        performArcher2(self, target);
    }
    else if (skillName == "폭풍 화살") {
        performArcher3(self, target, isCrit);
    }
    else if (skillName == "망령 화살") {
        performArcher4(self, target);
    }
    else if (skillName == "기본 공격") { // 기본 공격도 여기서 처리할 수 있습니다.
        std::cout << self.getName() << "이(가) " << target.getName() << "에게 기본 공격을 시전합니다!" << std::endl;
        int damage = self.getAttack();

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else {
        //std::cout << "지정되지 않은 스킬입니다: " << skillName << std::endl;
    }
}

namespace {
    void performArcher1(Character& self, Monster& target, bool isCrit) {
        std::cout << self.getName() << "의 화살 명중!" << std::endl;
        int damage = self.getAttack();

        // '조준' 상태라면 추가 피해 및 필중 효과
        if (self.getIsAimed()) {
            damage = static_cast<int>(damage * 1.3); // 데미지 30% 증가
            self.setIsAimed(false); // 조준 효과 사용 후 초기화
        }

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        std::cout << target.getName() << "에게 " << damage << "의 피해를 입혔습니다." << std::endl;
        target.takeDamage(damage);
    }

    void performArcher2(Character& self, Monster& target) {
        std::cout << self.getName() << "의 조준!" << std::endl;
        self.setIsAimed(true); // isAimed 플래그 활성화
        
    }

    void performArcher3(Character& self, Monster& target, bool isCrit) {
        std::cout << self.getName() << "의 폭풍 화살!" << std::endl;
        int hitCount = Utils::getRandomInt(2, 4); // 2~4발 랜덤 발사
        int damagePerHit = static_cast<int>(self.getAttack() * 0.6); // 한 발당 피해량은 60%

        if (isCrit)
        {
                std::cout << "치명타!!" << std::endl;
                damagePerHit = static_cast<int>(damagePerHit * 1.5);
        }

        std::cout << "수많은 화살이 " << target.getName() << "을(를) " << hitCount << "번 가격합니다!" << std::endl;
        for (int i = 0; i < hitCount; ++i) {
            target.takeDamage(damagePerHit);
        }
    }

    void performArcher4(Character& self, Monster& target) {
        std::cout << self.getName() << "의 망령 화살!" << std::endl;
        int delayedDamage = static_cast<int>(self.getAttack() * 2.5); // 공격력의 200%에 해당하는 지연 피해
        // Character.h에 선언된 wraithArrowDamage 변수에 피해량 저장
        self.setWraithArrowDamage(delayedDamage);
        std::cout << "망령의 기운이 담긴 화살이 " << target.getName() << "에게 박혔습니다. 다음 턴에 폭발합니다!" << std::endl;
    }
}