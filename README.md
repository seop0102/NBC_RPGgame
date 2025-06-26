# ⚔ DUNGEON Pick

프로젝트 제작 기간 : 2025.6.15(월) ~ 2024.6.26.(목)

# 📕 프로젝트 소개

## DUNGEON Pick이란?

> 직업 선택부터 전투까지! 이 프로젝트는 "선택"을 중심으로 구성된 로그라이크 텍스트 RPG입니다.
플레이어는 직업 선택부터 전투, 아이템 사용 등 모든 상황을 직접 선택을 하며 게임을 진행합니다.

> 신중하게 선택하여 강력한 마지막 보스를 해치워보세요!


## 주요 기능

![Image](https://github.com/user-attachments/assets/ea276826-3efe-458b-b3cd-814852897560)

게임 실행 시 프롤로그를 통해 **플레이어의 성향**을 파악합니다.

프롤로그에는 여러 선택지가 있으며, 해당 **선택지를 통해 직업과 지역이 선택**됩니다.

직업과 지역이 선택된 후 플레이어는 모험 화면을 통해 인벤토리, 상점, 던전 입장을 할 수 있습니다.

모험 화면에는 현재 플레이어 캐릭터의 상세한 정보와 함께 현재 던전의 층 수 등 중요한 정보를 알 수 있습니다.

인벤토리에서는 모험을 하며 얻은 각종 포션과 장비들의 정보를 확인할 수 있으며, 장착이 가능합니다.

상점에서는 모험에서 필요한 아이템을 구매, 판매할 수 있습니다.

던전 입장 시 전투가 시작되며 전투는 **턴제**로 시작됩니다. 캐릭터는 본인의 상황에 맞춰 공격, 아이템 사용, 스킬을 사용할 수 있으며, 체력이 0이 되면 패배하게 됩니다.

목표는 10레벨이며, 10레벨이 되면 등장하는 보스 몬스터를 처치할 시 게임은 클리어 됩니다.

---

# 🕹 팀원 소개

| **이름** | 역할 |
| --- | --- |
| 김선우(팀장) | Monster 클래스 담당 및 발표 |
| 김예준 | Item, ItemDataBase 클래스 담당 |
| 고건희 | GameManager, BattleManager 클래스 담당 |
| 김동권 | GameManager, BattleManager, Character 클래스 담당 |
| 변혁 | Character, Shop 클래스 담당 및 게임 기획 |
| 김채현 | main, StoryManager 클래스 담당 및 GitHub 관리 |

---

# 📁 프로젝트 구조

```cpp
NBC_RPGGame
┣ main.cpp // 메인 함수
┣ GameManager.h // 게임 매니저 헤더
┣ GameManager.cpp // 게임 매니저 구현
┃┣ BattleManager.h // 전투 매니저 헤더
┃┣ BattleManager.cpp // 전투 매니저 구현
┃┃┣ ICombatant.h // 전투 데이터 헤더
┃┣ StoryManager.h // 프롤로그 매니저 헤더
┃┣ StoryManager.cpp // 프롤로그 매니저 구현
┃┣ Utils.h // 각종 유틸 헤더
┃┣ ShopManager.h // 상점 매니저 헤더
┃┣ ShopManager.cpp // 상점 매니저 구현
┃┃┣ Shop.h // 상점 헤더
┃┃┣ Shop.cpp // 상점 구현
┃┣ TradeManager.h // 아이템 교환 매니저 헤더
┃┣ TradeManager.cpp // 아이템 교환 구현
┃┣ Character.h // 캐릭터 헤더
┃┣ Character.cpp // 캐릭터 구현
┃┃┣ IClass.h // 직업 헤더
┃┃┣ IClass.cpp // 직업 구현
┃┃┃┣ Archer.h // 궁수 직업 헤더
┃┃┃┣ Archer.cpp // 궁수 직업 구현
┃┃┃┣ Rogue.h // 도적 직업 헤더
┃┃┃┣ Rogue.cpp // 도적 직업 구현
┃┃┃┣ Warrior.h // 전사 직업 헤더
┃┃┃┣ Warrior.cpp // 전사 직업 구현
┃┣ Monster.h // 몬스터 헤더
┃┣ Monster.cpp // 몬스터 구현
┃┃┣ Goblin.h // 몬스터 고블린 헤더
┃┃┣ Goblin.cpp // 몬스터 고블린 구현
┃┃┣ Orc.h // 몬스터 오크 헤더
┃┃┣ Orc.cpp // 몬스터 오크 구현
┃┃┣ Skeleton.h // 몬스터 스켈레톤 헤더
┃┃┣ Skeleton.cpp // 몬스터 스켈레톤 구현
┃┃┣ Slime.h // 몬스터 슬라임 헤더
┃┃┣ Slime.cpp // 몬스터 슬라임 구현
┃┃┣ EvilSpirit.h // 몬스터 마수 헤더
┃┃┣ EvilSpirit.cpp // 몬스터 마수 구현
┃┃┣ BossMonster.h // 보스 몬스터 헤더
┃┃┣ BossMonster.cpp // 보스 몬스터 구현
┃┣ Item.h // 아이템 헤더
┃┣ Item.cpp // 아이템 구현
┃┃┣ ItemDataBase.h // 아이템 정보 헤더
┃┃┣ ItemDataBase.cpp // 아이템 정보 구현
┃┃┣ Weapon.h // 무기 아이템 헤더
┃┃┣ Weapon.cpp // 무기 아이템 구현
┃┃┣ Armor.h // 방어구 아이템 헤더
┃┃┣ Armor.cpp // 방어구 아이템 구현
┃┃┣ Consumable.h // 소모품 헤더
┃┃┣ Consumable.cpp // 소모품 구현
┃┃┃┣ ItemDataBase.h // 전체 아이템 데이터 헤더
┃┃┃┣ ItemDataBase.cpp // 전체 아이템 데이터 구현
```

### 📚 클래스 구조도

![Image](https://github.com/user-attachments/assets/f30074b8-bbb4-43fb-9617-2323701c694c)

---

# 🎥 시연 영상

https://youtu.be/Sw0QNnCA2ms
