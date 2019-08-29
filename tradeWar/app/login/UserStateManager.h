/*
 * UserStateManager.h
 *
 *  Created on: 2017年11月17日
 *      Author: Administrator
 */

#ifndef USERS_TATEMANAGER_H_
#define USERS_TATEMANAGER_H_

#include "DataState.h"
#include "IManager.h"

class UserStateManager: public IManager {
public:
	UserStateManager();
	virtual ~UserStateManager();
	virtual bool doPacket(CNetPacket * packet) {
		return true;
	}
	bool load(uint32_t uid);
	void onTimer();
	DataState* getState(uint32_t id);
	bool addState(uint32_t uid, uint32_t id, const string& data);
	bool setState(uint32_t uid, uint32_t id, const string& data);
	bool setStateData(uint32_t uid, uint32_t id, const string& data);
	bool getStateData(uint32_t uid, uint32_t id, Json::Value& res);

	//client state
	bool loadClientState(uint32_t uid);
	bool setClientState(const vector<pair<byte, byte> > &data);
	bool sendClientState();
	bool saveClientState();

	//leve reward
	bool loadLevelReward(uint32_t uid);
	bool setLevelReward(uint32_t id);
	bool getLevelReward(uint32_t id);
	bool saveLevelReward();
	bool sendLevelReward();

	//online ts
	bool loadOnlineTs(uint32_t uid);
	bool setOnlineTs(uint32_t id, uint32_t ts);
	bool saveOnlineTs();
private:
	map<uint32_t, DataState> m_mapState;
	vector<byte> m_clientState;
	vector<byte> m_levelReward;
	vector<uint32_t> m_onlineTs;
};

#endif /* USERS_TATEMANAGER_H_ */
