/*
 * DefendManager.h
 *
 *  Created on: 2017年11月14日
 *      Author: Administrator
 */

#ifndef DEFEND_MANAGER_H_
#define DEFEND_MANAGER_H_

#include "Kernel.h"
#include "DataDefend.h"
#include "IManager.h"

class DefendManager: public IManager
{
public:
	DefendManager();
	virtual ~DefendManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool sendInfo();
	uint32_t getCurr() const;
private:
	bool doGetInfo(CNetPacket *packet);
	bool doDefendOver(CNetPacket *packet);
	bool onDefendOverResp(uint32_t level, byte ret);
	bool saveData(const DataDefend &data);
	bool onAddNewGate();
private:
	map<uint32_t, DataDefend> m_defends;
};

#endif /* DEFEND_MANAGER_H_ */
