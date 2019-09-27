/*
 * NpcManager.h
 *
 *  Created on: 2018年7月31日
 *      Author: rein
 */

#ifndef _NPC_MANAGER_H_
#define _NPC_MANAGER_H_

#include "Soldier.h"
#include "TroopsManager.h"
#include "DataGemPoint.h"

struct NpcInfo {
	vector<Soldier> soldier;
	vector<TroopsInfo> troops;
	vector<DataGemPoint> gem;
	string name;
};

class NpcManager {
public:
	static NpcManager* getInstance() {
		static NpcManager ins;
		return &ins;
	}
	virtual ~NpcManager();
	bool GetNpc(uint32_t id, IBuffer *buffer);
	bool LoadNpc(uint32_t id);
	string GetNpcName(uint32_t id);
protected:
	NpcManager();
	bool Encode(NpcInfo &data, IBuffer *buffer);
private:
	map<uint32_t, NpcInfo> m_npc;
};

#endif /* _NPC_MANAGER_H_ */
