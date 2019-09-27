#ifndef EQUIPMENT_MANAGER_H_
#define EQUIPMENT_MANAGER_H_

#include "Award.h"
#include "Equipment.h"
#include "DataEquipment.h"
#include "ProtocolInc.h"
#include "DataInc.h"
#include "EquipmentConfig.h"
#include "IManager.h"

class EquipmentManager: public IManager {
public:
	EquipmentManager();
	~EquipmentManager();
	bool load(uint32_t uid);
	bool parse(uint32_t uid, uint32_t id, const string &data);
	bool setData(const vector<DataEquipment> &data);
	bool save(uint32_t uid);
	bool doPacket(CNetPacket *packet);
	Equipment* getNewEquip(uint32_t type, uint32_t count);
	Equipment* getEquipById(uint32_t type);
	bool sendEquipmentList();
	bool sendBagList();
	bool useGiftBag(uint32_t equipId, uint32_t count, bool bag);
	bool checkItemEnough(uint32_t equipType, uint32_t useCount);
	bool addBagItem(uint32_t type, uint32_t count, const string &reason);
	bool useBagItemByType(uint32_t equipId, uint32_t delCount, const string &reason);
	uint32_t getItemCount(uint32_t type);
	bool subGemLockCount(uint32_t type, uint32_t cnt);
	bool checkGemLockCount();
	uint32_t calcGemPower();
private:
	void release();
	bool doQueryEquipment(CNetPacket *packet);
	bool doQueryBag(CNetPacket *packet);
	bool doBuyItem(CNetPacket *packet);
	bool doEquipmentUse(CNetPacket *packet);
	bool doGemInfo(CNetPacket *packet);
	bool doGemPoint(CNetPacket *packet);
	bool doGemCombine(CNetPacket *packet);
	bool doEquipCombine(CNetPacket *packet);
	void onBuyItemResponse(byte ret);
	bool onGemPoint(uint32_t type, byte ret);
	bool onGemCombine(byte ret);
	bool onEquipCombine(byte ret, uint32_t type, Award &reward);
	bool sendOneEquip(Equipment *pEquip);
	bool sendBagAdd(Equipment *pBag);
	bool sendBagRemove(Equipment *pBag);
	bool sendCountChange(Equipment *pEquip);
private:
	map<uint32_t, Equipment*> m_bags;
	uint32_t m_maxUd;
};

#endif /* EQUIPMENT_MANAGER_H_ */
