#pragma once

#include <string>

// 전투 시 캐릭터가 상속받는 인터페이스 
class ICombatant {
public:
	virtual void takeDamage(int damage) = 0; // 받는 피해
	virtual int getAttack() const = 0; // 공격력 반환
	virtual int getHealth() const = 0; // 체력 반환
	virtual std::string getName() const = 0; // 이름 반환
	virtual bool isAlive() const = 0; // 살았는지 죽었는지 확인
	virtual int getDefense() const = 0; // 방어력 반환
	virtual int getDodgeChance() const = 0; // 회피율
	virtual ~ICombatant() = default; // 가상 소멸자
};