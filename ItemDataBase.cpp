#include "ItemDataBase.h"
#include <iostream>
#include <algorithm>

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

std::unique_ptr<Item> ItemDataBase::createItem(const std::string& itemName) const
{
    const ItemData* data = getItemData(itemName);
    if (!data)
    {
        std::cout << "아이템을 찾을 수 없습니다: " << itemName << std::endl;
        return nullptr;
    }

    return createItem(nameToIndex.at(itemName));
}

std::unique_ptr<Item> ItemDataBase::createItem(int index) const
{
    if (index < 0 || index >= static_cast<int>(itemDataList.size()))
    {
        std::cout << "잘못된 아이템 인덱스 : " << index << std::endl;
        return nullptr;
    }

    const ItemData& data = itemDataList[index];
    ItemType type = stringToItemType(data.typeStr);
    ItemTier tier = stringToItemTier(data.tierStr);

    // 아이템 타입에 따른 적절한 객체 생성 (클래스명 변경)
    switch (type)
    {
    case ItemType::WEAPON:
        return std::make_unique<Weapon>(data.name, tier, data.attackBonus, data.price);
    case ItemType::ARMOR:
        return std::make_unique<Armor>(data.name, tier, data.defenseBonus, data.maxHealthBonus, data.price);
    case ItemType::CONSUMABLE: // EDIBLE -> CONSUMABLE 변경
        return std::make_unique<Consumable>(data.name, tier, data.healthRecover, data.skillCharges, data.attackBonus, data.price);
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

std::vector<std::unique_ptr<Item>> ItemDataBase::getItemsByType(ItemType type) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemType(itemDataList[i].typeStr) == type)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }

    return result;
}

std::vector<std::unique_ptr<Item>> ItemDataBase::getItemsByTier(ItemTier tier) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (stringToItemTier(itemDataList[i].tierStr) == tier)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }
    return result;
}

void ItemDataBase::printAllItems() const // 함수명 수정
{
    std::cout << "== 전체 아이템 목록 ==" << std::endl;
    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        auto item = createItem(static_cast<int>(i));
        if (item)
        {
            std::cout << "[" << i << "] " << item->getItemInfo() << std::endl; // getIteminfo -> getItemInfo
        }
    }
}

std::vector<std::unique_ptr<Item>> ItemDataBase::getShopItems(int maxPrice) const
{
    std::vector<std::unique_ptr<Item>> result;

    for (size_t i = 0; i < itemDataList.size(); ++i)
    {
        if (itemDataList[i].price <= maxPrice)
        {
            auto item = createItem(static_cast<int>(i));
            if (item)
            {
                result.push_back(std::move(item));
            }
        }
    }
    std::sort(result.begin(), result.end(),
        [](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b)
        {
            return a->getPrice() < b->getPrice();
        });

    return result;
}