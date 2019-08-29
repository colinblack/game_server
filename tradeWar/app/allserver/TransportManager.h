/*
 * TransportManager.h
 *
 *  Created on: 2018年1月15日
 *      Author: Administrator
 */

#ifndef MERCHANTSHIP_MANAGER_H_
#define MERCHANTSHIP_MANAGER_H_

#include "Kernel.h"
#include "MerchantShip.pb.h"

struct RuningShip {
	uint32_t uid;
	uint32_t id;       //序号
	uint32_t endTs;    //结束时间
	uint32_t waitTs;   //等待时间
	uint32_t totalRes; //资源数
	uint32_t lostRes;  //掠夺数
	uint32_t lv;       //等级
	set<uint32_t> challenge;

	RuningShip() :
			uid(0), id(0), endTs(0), waitTs(0), totalRes(0), lostRes(0), lv(0) {
		challenge.clear();
	}

	void Parse(const MerchantShip::MerchantShipItem &data) {
		uid = data.uid();
		id = data.id();
		endTs = data.endts();
		waitTs = data.waitts();
		totalRes = data.totalres();
		lostRes = data.lostres();
		lv = data.lv();
		for (int i = 0; i < data.challenge_size(); ++i) {
			challenge.insert(data.challenge(i));
		}
	}

	void Serialize(MerchantShip::MerchantShipItem *data) {
		data->set_uid(uid);
		data->set_id(id);
		data->set_endts(endTs);
		data->set_waitts(waitTs);
		data->set_totalres(totalRes);
		data->set_lostres(lostRes);
		data->set_lv(lv);
		for (set<uint32_t>::iterator itr = challenge.begin(); itr != challenge.end(); ++itr) {
			data->add_challenge(*itr);
		}
	}
};

class CNetPacket;
class TransportManager {
public:
	virtual ~TransportManager();
	static TransportManager* getInstance() {
		static TransportManager instance;
		return &instance;
	}
	bool doPacket(CNetPacket *p);

	bool doLoad();
	bool doSave();
	void onSecondTimer();
protected:
	TransportManager();

private:
	bool doStart(CNetPacket *p);
	bool doSpeedUp(CNetPacket *p);
	bool doSearch(CNetPacket *p);
	bool doRob(CNetPacket *p);
	bool doGetTarget(CNetPacket *p);
	void onGetTarget(uint32_t uid, uint32_t target_uid, uint32_t target_id);
private:
	map<uint64_t, RuningShip> m_runing;
	map<uint32_t, set<uint64_t> > m_level;
	map<uint32_t, uint64_t> m_wait;
	map<uint32_t, vector<uint64_t> > m_npc;
};

#endif /* MERCHANTSHIP_MANAGER_H_ */
