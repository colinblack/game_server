/*
 * ChargeHistoryManager.h
 *
 *  Created on: 2019年1月3日
 *      Author: Administrator
 */

#ifndef CHARGE_HISTORY_MANAGER_H_
#define CHARGE_HISTORY_MANAGER_H_

#include "IManager.h"
#include "DataInc.h"
#define DATA_CHARGE_HISTORY_LEN 15

class ChargeHistoryManager: public IManager {
public:
	ChargeHistoryManager();
	virtual ~ChargeHistoryManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool save(const DataChargeHistory &data, bool isNew);
	bool onLogin();
	bool doCharge(uint32_t money);
	uint32_t getTotalCharge(uint32_t bts, uint32_t ets);
	uint32_t getDailyCharge();
	uint32_t getChargeDays(uint32_t bts, uint32_t ets);
	bool push();
protected:
	bool checkSize();
private:
	map<uint32_t, DataChargeHistory> m_data;
};

#endif /* CHARGE_HISTORY_MANAGER_H_ */
