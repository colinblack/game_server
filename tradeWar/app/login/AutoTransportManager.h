/*
 * AutoTransportManager.h
 *
 *  Created on: 2018年12月12日
 *      Author: Administrator
 */

#ifndef AUTO_TRANSPORT_MANAGER_H_
#define AUTO_TRANSPORT_MANAGER_H_

#include "Kernel.h"
#include "PbMessage.h"

#define AUTO_TRANSPORT_TIME 7200
#define AUTO_TRANSPORT_MIN_LEVEL 4

struct DataAutoTransportUser {
	uint8_t lv;
	uint8_t blv;
	uint32_t uid;
	uint32_t ets;
	uint32_t res;
	uint32_t lost;

	DataAutoTransportUser() {
		lv = 0;
		blv = 0;
		uid = 0;
		ets = 0;
		res = 0;
		lost = 0;
	}

	void Parse(const ProtoAutoTransport::AutoTransportItem &msg) {
		lv = msg.lv();
		blv = msg.blv();
		uid = msg.uid();
		ets = msg.ets();
		res = msg.res();
		lost = msg.lost();
	}

	void Serialize(ProtoAutoTransport::AutoTransportItem *msg) {
		msg->set_lv(lv);
		msg->set_blv(blv);
		msg->set_uid(uid);
		msg->set_ets(ets);
		msg->set_res(res);
		msg->set_lost(lost);
	}
};

class AutoTransportManager {
public:
	static AutoTransportManager* getInstance() {
		static AutoTransportManager* _ins = NULL;
		if (_ins == NULL) {
			_ins = new AutoTransportManager();
		}
		return _ins;
	}
	virtual ~AutoTransportManager();
	bool init();
	bool save();
	bool onTimer();
	bool onStart(uint32_t uid, uint32_t ets);
	bool onFinish(uint32_t uid);
	bool onRob(uint32_t uid, uint32_t res);
	bool updateLevel(uint32_t uid);
	bool getInfo(uint32_t uid, uint32_t &ets, uint32_t &res);
	uint32_t getRes(uint32_t uid);
protected:
	AutoTransportManager();
private:
	map<uint32_t, DataAutoTransportUser> m_data;
	list<uint32_t> m_train;
	map<uint32_t, vector<uint32_t> > m_runing;
};

#endif /* AUTO_TRANSPORT_MANAGER_H_ */
