#include "Warrior.h"
#include "IClass.h"
#include "Character.h"
#include "Utils.h"
#include "Monster.h"

#include <iostream>

Warrior::Warrior() {
    // activeSkills ���Ϳ� ���� ��ų �̸��� ���ڿ��� �߰�
    activeSkills.push_back("�⺻ ����");
    SkillDescription.push_back(" (���ݷ��� 100% �������� �ݴϴ�)");

    activeSkills.push_back("����");
    SkillDescription.push_back(" (���ݷ��� 120% �������� �ݴϴ�)");

    activeSkills.push_back("����");
    SkillDescription.push_back(" (���и� �÷� ������ �ø��ϴ�)");

    activeSkills.push_back("��Ÿ");
    SkillDescription.push_back(" (ġ��Ÿ ���ذ� ���� ������ �մϴ�)");

    activeSkills.push_back("��Ƽ��");
    SkillDescription.push_back(" (���� ���ݿ� ���ظ� �޾Ƶ� �������� �ʽ��ϴ�)");
}

std::string Warrior::getClassName() const {
    return "����";
}

// std::vector<std::string>�� ��ȯ�ϵ��� ����
std::vector<std::string> Warrior::getActiveSkills() const {
    return activeSkills;
}

void Warrior::showSkills() const
{
        int count = 1;
        for (int i = 0; i < activeSkills.size(); i++) {
                std::cout << count << ' ' << activeSkills[i] << ' ' << SkillDescription[i] << std::endl; // ��ų �̸� ���
                count++;
        }

}

// �Ű������� const std::string&���� �����ϰ� ���� ������ ���ڿ� �񱳷� ����
void Warrior::useSkill(const std::string& skillName, Character& self, Monster& target, bool isCrit) {
    if (skillName == "�⺻ ����") {
        std::cout << self.getName() << "��(��) " << target.getName() << "���� �⺻ ������ �����մϴ�!" << std::endl;
        int damage = self.getAttack();

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "����") {
        std::cout << self.getName() << "��(��) " << target.getName() << "���� ���⸦ �����մϴ�!" << std::endl;
        int damage = self.getAttack() * 1.2; // ���÷� ���ݷ��� 120%

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damage = static_cast<int>(damage * 1.5);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "����") {
        std::cout << self.getName() << "��(��) ���и� ��� ��� �¼��� ���մϴ�!" << std::endl;
        self.setIsShielded(true); // Character Ŭ������ isShielded ���� �߰� �� ���� �ʿ�
        self.setDefense(self.getDefense() + 10); // �ӽ÷� ���� ���� ����
    }
    else if (skillName == "��Ÿ") {
        std::cout << self.getName() << "��(��) " << target.getName() << "���� ��Ÿ�� �����մϴ�!" << std::endl;
        int damage = self.getAttack() * 1.5; // ���� ����

        if (isCrit)
        {
                std::cout << "ġ��Ÿ!!" << std::endl;
                damage = static_cast<int>(damage * 2);
        }

        target.takeDamage(damage);
    }
    else if (skillName == "��Ƽ��") {
        // Character.cpp�� useSkill���� Ƚ�� ������ �̹� ó����
        self.setHasIndomitableWill(true); // Character�� hasIndomitableWill ���� �߰� �� ���� �ʿ�
    }
    else {
        std::cout << "�� �� ���� ���� ��ų�Դϴ�: " << skillName << std::endl;
    }
}

void Warrior::applyPassiveSkill(Character& self) {
    std::cout << "������ �нú� ��ų '������'�� ����˴ϴ�. �ִ� ü�� +50." << std::endl;
    self.setMaxHealth(self.getMaxHealth() + 50);
    self.setHealth(self.getMaxHealth()); // ü�µ� �ִ�ġ�� ȸ��
}