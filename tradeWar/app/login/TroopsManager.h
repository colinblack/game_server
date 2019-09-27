/*
 * TroopsManager.h
 *
 *  Created on: 2018年7月16日
 *      Author: Administrator
 */

#ifndef _TROOPS_MANAGER_H_
#define _TROOPS_MANAGER_H_

#include "IManager.h"
#include "DataInc.h"

struct TroopsInfo {
	uint32_t id;
	uint32_t value;
	TroopsInfo(): id(0), value(0) {
	}

	void FromJson(const Json::Value &v) {
		id = v.get("id", 0).asUInt();
		value = v.get("v", 0).asUInt();
	}

	Json::Value ToJson() {
		Json::Value v;
		v["id"] = id;
		v["v"] = value;
		return v;
	}
};

class TroopsManager: public IManager {
public:
	enum {
		e_TROOPS_TYPE_ATTACK = 0, //
		e_TROOPS_TYPE_DEFEND = 1  //
	};
	TroopsManager();
	virtual ~TroopsManager();
	virtual bool doPacket(CNetPacket* packet);

public:
	bool load(uint32_t uid);
	bool doSend();
	bool packDefend(IBuffer *buff);
	bool packAttack(IBuffer *buff);
	bool setData(uint32_t uid, const Json::Value &data);
	bool subAttack(const vector< pair<uint32_t, uint32_t> > &data);
	bool delAttack(uint32_t id);
	bool setSkill(uint32_t id, uint32_t count);
	bool calcDefendScore();
	uint32_t getAttackCount(uint32_t type);
	uint32_t getDefendCount(uint32_t type);
	uint32_t getDefendScore();
protected:
	bool doSetAttack(CNetPacket* packet);
	bool doSetDefend(CNetPacket* packet);

	bool onSetAttackResp(byte ret);
	bool onSetDefendResp(byte ret);

	bool initAttack();
	bool initDefend();

	bool updateAttack(bool isNew);
	bool updateDefend(uint32_t id, uint32_t soldier, uint32_t type);

	bool sendAttack();
	bool sendDefend();

	bool checkDefend();

private:
	map<uint32_t, uint32_t> m_defend;  //location => id
	vector<TroopsInfo> m_attack;
	uint32_t m_defend_score;
};

#endif /* _TROOPS_MANAGER_H_ */
