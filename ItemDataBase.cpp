#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>

#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"

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

Item* ItemDataBase::createItem(const std::string& itemName) const
{
    auto it = nameToIndex.find(itemName);
    if (it == nameToIndex.end())
    {
        std::cout << "아이템을 찾을 수 없습니다: " << itemName << std::endl;
        return nullptr;
    }
    return createItem(it->second);
}

Item* ItemDataBase::createItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(itemDataList.size()))
    {
        std::cout << "잘못된 아이템 인덱스 : " << index << std::endl;
        return nullptr;
    }

    const ItemData& data = itemDataList[index];
    ItemType type = stringToItemType(data.typeStr);
    ItemTier tier = stringToItemTier(data.tierStr);

    // new를 사용하여 동적 할당
    switch (type)
    {
    case ItemType::WEAPON:
        return new Weapon(data.name, tier, data.attackBonus, data.price);
    case ItemType::ARMOR:
        return new Armor(data.name, tier, data.defenseBonus, data.maxHealthBonus, data.price);
    case ItemType::CONSUMABLE:
        return new Consumable(data.name, tier, data.healthRecover, data.skillCharges, data.attackBonus, data.price);
    default:
        return nullptr;
    }
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
    if (index >= 0 && index < static_cast<int>(itemDataList.size()))
    {
        return &itemDataList[index];
    }
    return nullptr;
}

int ItemDataBase::getItemCount() const
{
    return static_cast<int>(itemDataList.size());
}

std::vector<Item*> ItemDataBase::getItemsByType(ItemType type) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            Item* item = createItem(static_cast<int>(i)); // 새로 생성
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<Item*> ItemDataBase::getItemsByTier(ItemTier tier) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            Item* item = createItem(static_cast<int>(i)); // 새로 생성
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    return result;
}

void ItemDataBase::printAllItems() const
{
    std::cout << "== 전체 아이템 목록 ==" << std::endl;
    std::vector<Item*> allItems; // 임시로 생성된 아이템을 저장할 벡터
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        Item* item = createItem(static_cast<int>(i)); // 새로 생성
        if (item)
        {
            std::cout << "[" << i << "] " << item->getItemInfo() << std::endl;
            allItems.push_back(item); // 임시 벡터에 추가하여 나중에 해제
        }
    }
    // 함수 종료 전 임시로 생성된 아이템 메모리 해제
    for (Item* item : allItems) {
        delete item;
    }
}

std::vector<Item*> ItemDataBase::getShopItems(int maxPrice) const
{
    std::vector<Item*> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            Item* item = createItem(static_cast<int>(i)); // 새로 생성
            if (item)
            {
                result.push_back(item);
            }
        }
    }
    std::sort(result.begin(), result.end(),
        [](const Item* a, const Item* b)
        {
            return a->getPrice() < b->getPrice();
        });

    return result;
}

Item* ItemDataBase::getRandomItem() const
{
    int chance = rand() % 100;

    if (chance < 30)
    {
        int itemIndex = std::rand() % itemDataList.size();
        return createItem(itemIndex);
    }
    else
    {
        return nullptr; // 30% 확률로 아이템을 드랍하지 않음
    }
}