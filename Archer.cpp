#include "Archer.h"
#include "IClass.h"
#include "Character.h"
#include "Utils.h"
#include "Monster.h"



Archer::Archer() {
    activeSkills.push_back("�⺻ ����");
    SkillDescription.push_back(" (���ݷ��� 100% �������� �ݴϴ�)");

    activeSkills.push_back("ȭ�� ����");
    SkillDescription.push_back(" (���� ���¸� ȭ���� �ݵ�� �����ϸ� �߰� ���ظ� �����ϴ�)");

    activeSkills.push_back("����");
    SkillDescription.push_back(" (���� �մϴ�)");

    activeSkills.push_back("��ǳ ȭ��");
    SkillDescription.push_back(" (���ݷ��� 60% ���ط� ������ �����մϴ�)");

    activeSkills.push_back("���� ȭ��");
    SkillDescription.push_back(" (�����Ͽ� ū ���ظ� �ִ� ȭ���� �߻��մϴ�)");
}

namespace {
    // ���� ���� �Լ��鵵 SkillType ��� std::string ����ϵ��� ����
    void performArcher1(Character& self, Monster& target, bool isCrit); // ȭ�� ����
    void performArcher2(Character& self, Monster& target); // ����
    void performArcher3(Character& self, Monster& target, bool isCrit); // ��ǳ ȭ��
    void performArcher4(Character& self, Monster& target); // ���� ȭ��
}

std::vector<std::string> Archer::getActiveSkills() const {
    return activeSkills; // �����ڿ��� �ʱ�ȭ�� ��ų ��� ��ȯ
}

void Archer::applyPassiveSkill(Character& self) {
    self.setHitChance(self.getHitChance() + 15);
    std::cout << "[�нú� �ߵ�] " << self.getName() << "��(��) ���� ������ ���߷��� 15% �����߽��ϴ�! ���� ���߷�: " << self.getHitChance() << "%" << std::endl;
}

void Archer::showSkills() const
{
        int count = 1;
        for (int i = 0; i < activeSkills.size(); i++) {
                std::cout << count << ' ' << activeSkills[i] <<  ' ' << SkillDescription[i] << std::endl; // ��ų �̸� ���
                count++;
        }
        
}

// SkillType ��� const std::string&�� �Ű������� �޵��� ����
void Archer::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) {
    // switch �� ��� if-else if ������ ���ڿ� ��
    if (skillName == "ȭ�� ����") {
        performArcher1(self, target, isCrit);
    }
    else if (skillName == "����") {
        performArcher2(self, target);
    }
    else if (skillName == "��ǳ ȭ��") {
        performArcher3(self, target, isCrit);
    }
    else if (skillName == "���� ȭ��") {
        performArcher4(self, target);
    }
    else if (skillName == "�⺻ ����") { // �⺻ ���ݵ� ���⼭ ó���� �� �ֽ��ϴ�.
        std::cout << self.getName() << "��(��) " << target.getName() << "���� �⺻ ������ �����մϴ�!" << std::endl;
        int damage = self.getAttack();

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else {
        //std::cout << "�������� ���� ��ų�Դϴ�: " << skillName << std::endl;
    }
}

namespace {
    void performArcher1(Character& self, Monster& target, bool isCrit) {
        std::cout << self.getName() << "�� ȭ�� ����!" << std::endl;
        int damage = self.getAttack();

        // '����' ���¶�� �߰� ���� �� ���� ȿ��
        if (self.getIsAimed()) {
            damage = static_cast<int>(damage * 1.3); // ������ 30% ����
            self.setIsAimed(false); // ���� ȿ�� ��� �� �ʱ�ȭ
        }

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        std::cout << target.getName() << "���� " << damage << "�� ���ظ� �������ϴ�." << std::endl;
        target.takeDamage(damage);
    }

    void performArcher2(Character& self, Monster& target) {
        std::cout << self.getName() << "�� ����!" << std::endl;
        self.setIsAimed(true); // isAimed �÷��� Ȱ��ȭ
        
    }

    void performArcher3(Character& self, Monster& target, bool isCrit) {
        std::cout << self.getName() << "�� ��ǳ ȭ��!" << std::endl;
        int hitCount = Utils::getRandomInt(2, 4); // 2~4�� ���� �߻�
        int damagePerHit = static_cast<int>(self.getAttack() * 0.6); // �� �ߴ� ���ط��� 60%

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damagePerHit = static_cast<int>(damagePerHit * 1.5);
        }

        std::cout << "������ ȭ���� " << target.getName() << "��(��) " << hitCount << "�� �����մϴ�!" << std::endl;
        for (int i = 0; i < hitCount; ++i) {
            target.takeDamage(damagePerHit);
        }
    }

    void performArcher4(Character& self, Monster& target) {
        std::cout << self.getName() << "�� ���� ȭ��!" << std::endl;
        int delayedDamage = static_cast<int>(self.getAttack() * 2.5); // ���ݷ��� 200%�� �ش��ϴ� ���� ����
        // Character.h�� ����� wraithArrowDamage ������ ���ط� ����
        self.setWraithArrowDamage(delayedDamage);
        std::cout << "������ ����� ��� ȭ���� " << target.getName() << "���� �������ϴ�. ���� �Ͽ� �����մϴ�!" << std::endl;
    }
}