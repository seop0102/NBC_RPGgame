#include "Shop.h"
#include <limits> // INT_MAX ����� ����

Shop::Shop(std::string name) : shopName(name), itemDB() {
    // �ʿ��� ��� ������ �ʱ� ������ ���� ���� �߰� ����
}

Shop::~Shop() {
    // itemDB�� ��� �����̹Ƿ� �ڵ����� �Ҹ��ڰ� ȣ��˴ϴ�.
}

std::string Shop::getName() const {
    return shopName;
}

void Shop::displayShopItems(int maxPrice) const {
    std::cout << "-------- " << shopName << " ������ ��� --------" << std::endl;
    // ItemDataBase���� ItemData ����� �����ɴϴ�. (���⼭�� Item*�� new ���� �ʽ��ϴ�)
    std::vector<const ItemData*> shopItemDatas = itemDB.getShopItemDatas(maxPrice);

    if (shopItemDatas.empty()) {
        std::cout << "���� ������ �������� �����ϴ�." << std::endl;
    }
    else {
        for (size_t i = 0; i < shopItemDatas.size(); ++i) {
            const ItemData* data = shopItemDatas[i];
            // display�� ItemData�� ������� ���� ���
            std::cout << "[" << i << "] " << data->name
                << " (����: " << data->price << " G)";
            // ������ Ÿ�Կ� ���� �߰� ���� ��� (getItemInfo ��ü)
            if (stringToItemType(data->typeStr) == ItemType::WEAPON) {
                std::cout << " (���ݷ�: " << data->attackBonus << ")";
            }
            else if (stringToItemType(data->typeStr) == ItemType::ARMOR) {
                std::cout << " (����: " << data->defenseBonus << ", ü��: " << data->maxHealthBonus << ")";
            }
            else if (stringToItemType(data->typeStr) == ItemType::CONSUMABLE) {
                if (data->healthRecover > 0) std::cout << " (ü�� ȸ��: " << data->healthRecover << ")";
                if (data->skillCharges > 0) std::cout << " (��ų ����: " << data->skillCharges << ")";
                if (data->attackBonus > 0) std::cout << " (���ݷ� ����: " << data->attackBonus << ")";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "---------------------------------" << std::endl;
}

// ������ ���� �� ���� Item ��ü�� �����Ͽ� ��ȯ
Item* Shop::getSelectedItemForPurchase(int index, int maxPrice) const {
    std::vector<const ItemData*> shopItemDatas = itemDB.getShopItemDatas(maxPrice);

    if (index >= 0 && index < shopItemDatas.size()) {
        const ItemData* data = shopItemDatas[index]; // ���õ� ItemData

        // ���õ� ItemData�� ������� Shop�� ���� Item ��ü�� new
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
            std::cout << "�� �� ���� ������ Ÿ���Դϴ�: " << data->typeStr << std::endl;
            return nullptr;
        }
    }
    else {
        return nullptr; // ��ȿ���� ���� �ε���
    }
}