/*
 * BattleGateManager.h
 *
 *  Created on: 2018年10月30日
 *      Author: Administrator
 */

#ifndef BATTLE_GATE_MANAGER_H_
#define BATTLE_GATE_MANAGER_H_

#include "IManager.h"
#include "DataInc.h"

class BattleGateManager: public IManager {
public:
	BattleGateManager();
	virtual ~BattleGateManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool sendInfo();
	uint32_t getCurr() const;
	uint32_t getLevelStarCnt(uint32_t level);
private:
	bool doGetInfo(CNetPacket *packet);
	bool doOver(CNetPacket *packet);
	bool doSetSpeedUp(CNetPacket *packet);
	bool onOverResp(uint32_t level, byte ret);
	bool onSpeedUpResp(byte flag);
	bool saveData(const DataBattleGate &data);
	bool onAddNewGate();
private:
	map<uint32_t, DataBattleGate> m_data;
};

#endif /* BATTLE_GATE_MANAGER_H_ */
