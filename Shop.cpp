#include "Shop.h"
#include <limits> // INT_MAX 사용을 위해

Shop::Shop(std::string name) : shopName(name), itemDB() {
    // 필요한 경우 상점별 초기 아이템 세팅 로직 추가 가능
}

Shop::~Shop() {
    // itemDB는 멤버 변수이므로 자동으로 소멸자가 호출됩니다.
}

std::string Shop::getName() const {
    return shopName;
}

void Shop::displayShopItems(int maxPrice) const {
    std::cout << "-------- " << shopName << " 아이템 목록 --------" << std::endl;
    // ItemDataBase에서 ItemData 목록을 가져옵니다. (여기서는 Item*를 new 하지 않습니다)
    std::vector<const ItemData*> shopItemDatas = itemDB.getShopItemDatas(maxPrice);

    if (shopItemDatas.empty()) {
        std::cout << "현재 상점에 아이템이 없습니다." << std::endl;
    }
    else {
        for (size_t i = 0; i < shopItemDatas.size(); ++i) {
            const ItemData* data = shopItemDatas[i];
            // display는 ItemData를 기반으로 직접 출력
            std::cout << "[" << i << "] " << data->name
                << " (가격: " << data->price << " G)";
            // 아이템 타입에 따른 추가 정보 출력 (getItemInfo 대체)
            if (stringToItemType(data->typeStr) == ItemType::WEAPON) {
                std::cout << " (공격력: " << data->attackBonus << ")";
            }
            else if (stringToItemType(data->typeStr) == ItemType::ARMOR) {
                std::cout << " (방어력: " << data->defenseBonus << ", 체력: " << data->maxHealthBonus << ")";
            }
            else if (stringToItemType(data->typeStr) == ItemType::CONSUMABLE) {
                if (data->healthRecover > 0) std::cout << " (체력 회복: " << data->healthRecover << ")";
                if (data->skillCharges > 0) std::cout << " (스킬 충전: " << data->skillCharges << ")";
                if (data->attackBonus > 0) std::cout << " (공격력 증가: " << data->attackBonus << ")";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "---------------------------------" << std::endl;
}

// 아이템 구매 시 실제 Item 객체를 생성하여 반환
Item* Shop::getSelectedItemForPurchase(int index, int maxPrice) const {
    std::vector<const ItemData*> shopItemDatas = itemDB.getShopItemDatas(maxPrice);

    if (index >= 0 && index < shopItemDatas.size()) {
        const ItemData* data = shopItemDatas[index]; // 선택된 ItemData

        // 선택된 ItemData를 기반으로 Shop이 직접 Item 객체를 new
        ItemType type = stringToItemType(data->typeStr);
        ItemTier tier = stringToItemTier(data->tierStr);

        switch (type)
        {
        case ItemType::WEAPON:
            return new Weapon(data->name, tier, data->attackBonus, data->price);
        case ItemType::ARMOR:
            return new Armor(data->name, tier, data->defenseBonus, data->maxHealthBonus, data->price);
        case ItemType::CONSUMABLE:
            return new Consumable(data->name, tier, data->healthRecover, data->skillCharges, data->attackBonus, data->price);
        default:
            std::cout << "알 수 없는 아이템 타입입니다: " << data->typeStr << std::endl;
            return nullptr;
        }
    }
    else {
        return nullptr; // 유효하지 않은 인덱스
    }
}