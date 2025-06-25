#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>
#include <random>


ItemDataBase::ItemDataBase()
{
    initializeItemData();
}

void ItemDataBase::initializeItemData()
{
    // 시트 데이터를 기반으로 아이템 정보 초기화

    itemDataList =
    {
        //무기
        {"숏소드","무기","일반",5,0,0,0,0,50},
        {"컴포짓 보우","무기","중급",10,0,0,0,0,100},
        {"바스타드 소드","무기","고급",15,0,0,0,0,200},

        //방어구
        {"천 갑옷","방어구","일반",0,10,0,0,10,125},
        {"가죽 갑옷","방어구","중급",0,15,0,0,20,250},
        {"판금 갑옷","방어구","고급",0,20,0,0,30,500},

        //소모품
        {"초급 물약","소모품","일반",0,0,2,50,0,50},
        {"중급 물약","소모품","중급",0,0,4,100,0,100},
        {"공격력 물약","소모품","고급",10,0,6,0,0,200}
    };

    //이름으로 빠른 검색하기
    nameToIndex.clear();
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        nameToIndex[itemDataList[i].name] = static_cast<int>(i);
    }
}

ItemType ItemDataBase::stringToItemType(const std::string& typeStr) const
{
    if (typeStr == "무기") return ItemType::WEAPON;
    if (typeStr == "방어구") return ItemType::ARMOR;
    if (typeStr == "소모품") return ItemType::CONSUMABLE; // EDIBLE -> CONSUMABLE 변경
    return ItemType::WEAPON;
}

ItemTier ItemDataBase::stringToItemTier(const std::string& tierStr) const
{
    if (tierStr == "일반") return ItemTier::NORMAL; // NORAML -> NORMAL 오타 수정
    if (tierStr == "중급") return ItemTier::RARE;
    if (tierStr == "고급") return ItemTier::EPIC;
    return ItemTier::NORMAL; // NORAML -> NORMAL 오타 수정
}

const ItemData* ItemDataBase::getItemData(const std::string& itemName) const
{
    auto it = nameToIndex.find(itemName);
    if (it != nameToIndex.end())
    {
        return &itemDataList[it->second];
    }
    return nullptr;
}

const ItemData* ItemDataBase::getItemData(int index) const
{
    if (index >= 0 && static_cast<size_t>(index) < itemDataList.size())
    {
        return &itemDataList[index];
    }
    return nullptr;
}

int ItemDataBase::getItemCount() const
{
    return static_cast<int>(itemDataList.size());
}

// 아이템 생성 함수 (이름)
Item* ItemDataBase::createItem(const std::string& itemName) const
{
    const ItemData* data = getItemData(itemName);

    if (!data)
    {
        std::cerr << "Error: Item data not found for name: " << itemName << std::endl;
        return nullptr;
    }

    ItemType type = stringToItemType(data->typeStr);
    ItemTier tier = stringToItemTier(data->tierStr);

    switch (type)
    {
    case ItemType::WEAPON:
        // Weapon 생성자
        return new Weapon(data->name, tier, data->attackBonus, data->price, true);
    case ItemType::ARMOR:
        // Armor 생성자
        return new Armor(data->name, tier, data->defenseBonus, data->maxHealthBonus, data->price, true);
    case ItemType::CONSUMABLE:
        // Consumable 생성자
        return new Consumable(data->name, tier, data->healthRecover, data->skillCharges, data->attackBonus, data->price, false);
    default:
        std::cerr << "Error: Unknown item type for: " << itemName << std::endl;
        return nullptr;
    }
}

// 아이템 생성 함수 (인덱스로)
Item* ItemDataBase::createItem(int index) const
{
    const ItemData* data = getItemData(index);
    if (!data)
    {
        std::cerr << "Error: Item data not found for index: " << index << std::endl;
        return nullptr;
    }

    ItemType type = stringToItemType(data->typeStr);
    ItemTier tier = stringToItemTier(data->tierStr);

    switch (type)
    {
    case ItemType::WEAPON:
        // Weapon 생성자: (name, tier, attackBonus, price)
        return new Weapon(data->name, tier, data->attackBonus, data->price, true);
    case ItemType::ARMOR:
        // Armor 생성자: (name, tier, defenseBonus, maxHealthBonus, price)
        return new Armor(data->name, tier, data->defenseBonus, data->maxHealthBonus, data->price, true);
    case ItemType::CONSUMABLE:
        // Consumable 생성자: (name, tier, healthRecover, skillCharges, attackBonus, price)
        return new Consumable(data->name, tier, data->healthRecover, data->skillCharges, data->attackBonus, data->price, false);
    default:
        std::cerr << "Error: Unknown item type for index: " << index << std::endl;
        return nullptr;
    }
}

std::vector<const ItemData*> ItemDataBase::getItemDatasByType(ItemType type) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            result.push_back(&itemDataList[i]); // 데이터 주소 반환
        }
    }
    return result;
}

std::vector<const ItemData*> ItemDataBase::getItemDatasByTier(ItemTier tier) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            result.push_back(&itemDataList[i]); // 데이터 주소 반환
        }
    }
    return result;
}
void ItemDataBase::printAllItemsData() const // 함수 이름 변경: printAllItems -> printAllItemsData
{
    std::cout << "== 전체 아이템 데이터 목록 ==" << std::endl;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        const ItemData& data = itemDataList[i];
        std::cout << "[" << i << "] 이름: " << data.name
            << ", 종류: " << data.typeStr
            << ", 등급: " << data.tierStr
            << ", 공격력: " << data.attackBonus
            << ", 방어력: " << data.defenseBonus
            << ", 체력회복: " << data.healthRecover
            << ", 스킬충전: " << data.skillCharges
            << ", 최대체력: " << data.maxHealthBonus
            << ", 가격: " << data.price << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

// 상점용 아이템 '데이터' 목록을 가져옵니다.
std::vector<const ItemData*> ItemDataBase::getShopItemDatas(int maxPrice) const
{
    std::vector<const ItemData*> result;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            result.push_back(&itemDataList[i]); // 데이터 주소 반환
        }
    }
    // 가격 기준으로 정렬
    std::sort(result.begin(), result.end(),
        [](const ItemData* a, const ItemData* b)
        {
            return a->price < b->price;
        });
    return result;
}

// 랜덤 아이템 '데이터'를 가져옵니다.
const ItemData* ItemDataBase::getRandomItemData() const
{

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dropChanceDist(0, 99); // 0-99 범위

    if (dropChanceDist(gen) < 30) // 30% 확률로 아이템 드랍
    {
        std::uniform_int_distribution<> itemIndexDist(0, itemDataList.size() - 1);
        int itemIndex = itemIndexDist(gen);
        return &itemDataList[itemIndex]; // 데이터 주소 반환
    }
    else
    {
        return nullptr; // 70% 확률로 아이템을 드랍하지 않음
    }
}