/*
 * RandomQuestManager.h
 *
 *  Created on: 2018年11月30日
 *      Author: Administrator
 */

#ifndef RANDOM_QUEST_MANAGER_H_
#define RANDOM_QUEST_MANAGER_H_

#include "IManager.h"
#include "DataRandomQuest.h"

class RandomQuestManager: public IManager {
public:
	enum {
		RandomQuestRetSuccess = 0,
		RandomQuestRetFail = 1
	};
	RandomQuestManager();
	virtual ~RandomQuestManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool onLogin();
	bool onTimer();
protected:
	bool doQuery(CNetPacket *packet);
	bool doQuest(CNetPacket *packet);
	bool doReward(CNetPacket *packet);
	bool onQuest(byte ret);
	bool onReward(byte ret);
	bool sendInfo();
	bool saveInfo(const DataRandomQuest &data, bool isNew);
	bool recover(DataRandomQuest &data);
	bool randomInfo(DataRandomQuest &data);
	bool sync();
	bool doQuestReward(const DataRandomQuest &data, uint32_t id);
	bool doQuestSoldier(const DataRandomQuest &data, const vector<pair<uint32_t, uint32_t> > &soldier);
	bool calcSoldier(const vector<uint32_t> &cfg, const set<uint32_t> &soldier, float &rate);
private:
	vector<DataRandomQuest> m_data;
};

#endif /* RANDOM_QUEST_MANAGER_H_ */

