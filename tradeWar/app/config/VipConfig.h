#ifndef VIP_CONFIG_H_
#define VIP_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct VipConftRight {
	uint32_t harvest;
	uint32_t boatres;
	uint32_t offline;
	uint32_t lootadd;
	uint32_t boattimes;
	uint32_t capacity;

	VipConftRight() {
		harvest = 0;
		boatres = 0;
		offline = 0;
		lootadd = 0;
		boattimes = 0;
		capacity = 0;
	}
};

struct VipConfigItem {
	uint32_t id;
	uint32_t ts;
	byte box;
	VipConftRight right;
	Award award;
	Award first;

	VipConfigItem() {
		id = 0;
		ts = 0;
		box = 0;
	}
};

struct MonthGiftConfigItem {
	byte id;
	byte box;
	Award reward;

	MonthGiftConfigItem() {
		id = 0;
		box = 0;
	}
};

class VipConfig {
public:
	~VipConfig();
	static VipConfig * getInstance() {
		static VipConfig instance;
		return &instance;
	}
public:
	bool init(const string & path);
	bool initRight(const Json::Value &value, VipConftRight *pRight);
	const VipConfigItem* getItem(uint32_t level);
	uint32_t getTs(uint32_t level);
	uint32_t getHarvest(uint32_t level);
	uint32_t getBoatRes(uint32_t level);
	uint32_t getOffline(uint32_t level);
	uint32_t getLootAdd(uint32_t level);
	uint32_t getBoatTimes(uint32_t level);
	uint32_t getCapacity(uint32_t level);
	uint32_t getSize() const {
		return m_items.size();
	}
	const MonthGiftConfigItem* getGift(uint32_t id) const;
	uint32_t getGiftSize() const;
protected:
	VipConfig();
private:
	map<uint32_t, VipConfigItem> m_items;
	map<byte, MonthGiftConfigItem> m_gift;
};

#endif /* VIP_CONFIG_H_ */
