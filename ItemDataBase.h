#pragma once
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include <vector>
#include <unordered_map>
#include <limits>
// Item 초안 시트 데이터와 같게해서 만들었습니다
struct ItemData
{
    std::string name; // 아이템 이름
    std::string typeStr; // 아이템 종류
    std::string tierStr; // 아이템 등급
    int attackBonus;
    int defenseBonus;
    int skillCharges;
    int healthRecover;
    int maxHealthBonus;
    int price;
};
// 아이템 타입 enum (ItemDataBase 내부 사용용)
enum class ItemType
{
    WEAPON,  // 무기
    ARMOR,   // 방어구
    CONSUMABLE // 소모품 (EDIBLE에서 변경)
};
class ItemDataBase
{
private:
    std::vector<ItemData> itemDataList;
    std::unordered_map<std::string, int> nameToIndex; // 이름으로 빠른 검색

public:
    //생성자
    ItemDataBase();
    //시트 데이터 초기화
    void initializeItemData();

    // 아이템 생성 함수
    Item* createItem(const std::string& itemName) const;
    Item* createItem(int index) const;

    ItemType stringToItemType(const std::string& typeStr) const;
    ItemTier stringToItemTier(const std::string& tierStr) const;

    //아이템 데이터 조회
    const ItemData* getItemData(const std::string& itemName) const;
    const ItemData* getItemData(int index) const;
    int getItemCount() const;

    //특정 타입의 아이템들 가져오는 코드
    std::vector<Item*> getItemsByType(ItemType type) const;
    std::vector<Item*> getItemsByTier(ItemTier tier) const;

    std::vector<const ItemData*> getShopItemDatas(int maxPrice = INT_MAX) const;
    std::vector<const ItemData*> getItemDatasByType(ItemType type) const;
    std::vector<const ItemData*> getItemDatasByTier(ItemTier tier) const;
    const ItemData* getRandomItemData() const;

    // 전체 아이템 목록 출력(디버깅용)
    void printAllItemsData() const;
};