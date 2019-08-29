#ifndef SHOPCONFIG_H_
#define SHOPCONFIG_H_

#include "Kernel.h"

struct ShopConfigChoujiangItem
{
	byte type;
	uint32_t cost;
	uint32_t cost10;
	uint32_t interval;
	uint16_t max;

	ShopConfigChoujiangItem():type(0),cost(0),cost10(0),interval(0),max(0)
	{
	}
};

struct ShopConfigDiamondItem
{
	byte id;
	uint32_t count;
	uint32_t extra;
	uint32_t cost;

	ShopConfigDiamondItem():id(0),count(0),extra(0),cost(0)
	{
	}
};

struct ShopConfigGold
{
	byte id;
	uint32_t count;
	uint32_t cost;
};

struct ShopGood
{
	uint32_t id;
	uint32_t cost;
	uint16_t type;
	uint16_t subType;

	ShopGood()
	{
		id = 0;
		cost = 0;
		type = 0;
		subType = 0;
	}
};

struct ShopChipItem {
	uint16_t id;
	uint16_t require;
	uint32_t equip;

	ShopChipItem() {
		id = 0;
		require = 0;
		equip = 0;
	}
};

enum ShopGoodSubType
{
	ShopGoodSubTypeRes = 1,
	ShopGoodSubTypeBag = 2
};

class CShopConfig
{
public:
	virtual ~CShopConfig();
	static CShopConfig* getInstance(){
		static CShopConfig instance;
		return &instance;
	}
	bool init();
	bool getDiamondIndex(uint32_t cash, uint32_t &id);
	uint32_t getDiamondSize();
	const ShopGood* getGoodItem(uint32_t id);
	const ShopChipItem* getChip(uint16_t id) const;
protected:
	CShopConfig();
private:
	vector<ShopConfigDiamondItem> m_diamond;
	map<uint32_t, ShopGood> m_good;
	map<uint16_t, ShopChipItem> m_chip;
};

#endif /* SHOPCONFIG_H_ */
