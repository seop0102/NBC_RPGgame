#include "Rogue.h"
#include "IClass.h"
#include "Character.h"
#include "Monster.h"
#include "Utils.h"
#include <iostream>

// Rogue 생성자에서 스킬 목록 초기화
Rogue::Rogue() {
    activeSkills.push_back("기본 공격");
    SkillDescription.push_back(" (공격력의 100% 데미지를 줍니다)");

    activeSkills.push_back("찢기");
    SkillDescription.push_back(" (추가 공격력을 더해 피해를 줍니다)");

    activeSkills.push_back("날렵한 손");
    SkillDescription.push_back(" (적에게 적은 피해를 주고 골드를 훔칩니다)");

    activeSkills.push_back("급습");
    SkillDescription.push_back(" (높은 치명타 확률로 적을 공격합니다)");

    activeSkills.push_back("숨기");
    SkillDescription.push_back(" (재빨리 숨어 다음 공격을 회피 합니다)");
}

namespace {
    // 내부 헬퍼 함수들도 SkillType 대신 std::string 사용하도록 수정
    void performRogue1(Character& self, Monster& target, bool isCrit); // 찢기
    void performRogue2(Character& self, Monster& target); // 날렵한 손
    void performRogue3(Character& self, Monster& target); // 급습
    void performRogue4(Character& self, Monster& target); // 숨기
}

// std::vector<SkillType> 대신 std::vector<std::string> 반환
std::vector<std::string> Rogue::getActiveSkills() const {
    return activeSkills; // 생성자에서 초기화된 스킬 목록 반환
}

void Rogue::applyPassiveSkill(Character& self) {
    // 전투 시작 시 회피율 보너스를 얻는 패시브
    self.setDodgeChance(self.getDodgeChance() + 20);
    std::cout << "[패시브 발동] " << self.getName() << "은(는) 날렵한 몸놀림으로 회피율이 20% 증가했습니다! 현재 회피율: " << self.getDodgeChance() << "%" << std::endl;
}

void Rogue::showSkills() const
{
        int count = 1;
        for (int i = 0; i < activeSkills.size(); i++) {
                std::cout << count << ' ' << activeSkills[i] << ' ' << SkillDescription[i] << std::endl; // 스킬 이름 출력
                count++;
        }

}

// SkillType 대신 const std::string&을 매개변수로 받도록 변경
void Rogue::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) {
    // switch 문 대신 if-else if 문으로 문자열 비교
    if (skillName == "찢기") {
        performRogue1(self, target, isCrit);
    }
    else if (skillName == "날렵한 손") {
        performRogue2(self, target);
    }
    else if (skillName == "급습") {
        performRogue3(self, target);
    }
    else if (skillName == "숨기") {
        performRogue4(self, target);
    }
    else if (skillName == "기본 공격") { // 기본 공격도 여기서 처리
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
        //std::cout << "도적은 사용할 수 없는 스킬입니다: " << skillName << std::endl;
    }
}

namespace {
    void performRogue1(Character& self, Monster& target, bool isCrit) {
        std::cout << self.getName() << "의 찢기!" << std::endl;
        int damage = self.getAttack() + 15;

        if (isCrit)
        {       
                std::cout << "치명타!!" << std::endl;
                damage = static_cast<int>(damage *1.5);
        }

        std::cout << "날카로운 단검이 " << target.getName() << "에게 상처를 입혀 " << damage << "의 피해!" << std::endl;

        target.takeDamage(damage);
    }

    void performRogue2(Character& self, Monster& target) {
        std::cout << self.getName() << "의 날렵한 손!" << std::endl;
        int stolenGold = Utils::getRandomInt(10, 30) * self.getLevel();
        self.addGold(stolenGold); // Character의 골드 획득 함수 호출
        std::cout << target.getName() << "에게서 " << stolenGold << " G를 훔쳤습니다!" << std::endl;

        int damage = static_cast<int>(self.getAttack() * 0.5); // 훔치는 동안 약간의 피해
        target.takeDamage(damage);
    }

    void performRogue3(Character& self, Monster& target) {
        std::cout << self.getName() << "의 급습!" << std::endl;
        // 치명타 확률이 높은 공격
        int dice = Utils::rollDice();
        int damage = 0;
        if (Utils::checkChance(self.getCriticalChance())) { // Character::getCriticalChance()를 사용
            damage = static_cast<int>(self.getAttack() * 2.0); // 200% 피해
            std::cout << "치명타! " << target.getName() << "의 약점을 정확히 노렸습니다! " << damage << "의 피해!" << std::endl;
        }
        else {
            damage = self.getAttack();
            std::cout << "공격이 빗나가 약한 피해를 입혔습니다. " << damage << "의 피해." << std::endl;
        }
        target.takeDamage(damage);
    }

    void performRogue4(Character& self, Monster& target) {
        std::cout << self.getName() << "의 숨기!" << std::endl;
        self.setIsHiding(true); // isHiding 플래그 활성화
        std::cout << "그림자 속으로 사라집니다. 다음 턴 공격을 반드시 회피합니다." << std::endl;
    }
}