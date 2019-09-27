#ifndef _BOAT_MANAGER_H_
#define _BOAT_MANAGER_H_

#include "Kernel.h"
#include "IManager.h"
#include "Award.h"
#include "DataBoat.h"
#include "DataBoatTrain.h"
#include "DataBoatRobLog.h"

#define MAX_DAILY_STAR 10
#define MAX_REVENGE_NUM 2

class CBoatRobResultProtocol;

struct MerchantNpc {
	uint32_t id;
	uint32_t totalRes;
	uint32_t lostRes;
	uint32_t exp;
	uint32_t power;
	byte trainId;
	string name;

	MerchantNpc(): id(0), totalRes(0), lostRes(0), exp(0), power(0), trainId(0) {
	}

	MerchantNpc& operator=(const MerchantNpc &data) {
		this->id = data.id;
		this->totalRes = data.totalRes;
		this->lostRes = data.lostRes;
		this->exp = data.exp;
		this->power = data.power;
		this->trainId = data.trainId;
		this->name = data.name;
		return *this;
	}

	void addExp(int32_t exp_) {
		if (exp_ < 0 && static_cast<uint32_t>(-1 * exp_) > exp) {
			exp = 0;
		} else {
			exp += exp_;
		}
	}
};

class BoatManager: public IManager {
public:
	enum {
		PROCESS_RET_SUCCESS = 0,
		PROCESS_RET_FAIL = 1
	};
	BoatManager();
	virtual ~BoatManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool doReset();
	bool doSave();
	bool doSend();
	bool onRob(uint32_t uid, uint32_t id, const string &name, uint32_t robRes, uint32_t &res);
	bool onRobByOther(uint32_t uid, uint32_t id, const string &name, uint32_t res, int32_t exp);
	bool onLogin();
	bool asyncAutoTrain();
	bool autoTrain(uint32_t ets, uint32_t res);
	bool addRevengeCount();
	static bool setLogStr(string &s, const map< pair<unsigned, unsigned>, unsigned> data);
private:
	//request
	bool doStart(CNetPacket *packet);
	bool doBuyCount(CNetPacket *packet);
	bool doReward(CNetPacket *packet);
	bool doGetTarget(CNetPacket *packet);
	bool doGetTargetCount(CNetPacket *packet);
	bool doRobResult(CNetPacket *packet);
	bool doRobRes(CNetPacket *packet);
	bool doGetLog(CNetPacket *packet);
	bool doSpeedUp(CNetPacket *packet);
	bool doStarReward(CNetPacket *packet);
	bool doAsrvTarget(CNetPacket *packet);
	bool doTargetInfoReq(CNetPacket *packet);
	bool doTargetInfoResp(CNetPacket *packet);
	bool doRevenge(CNetPacket *packet);
	bool doAsrvRevenge(CNetPacket *packet);
	bool doCashReset(CNetPacket *packet);
	//response
	void onStartResp(uint32_t uid, byte ret);
	void onBuyCountResp(uint32_t uid, byte ret);
	void onRewardResp(uint32_t uid, byte ret, byte id, const Award &reward);
	void onGetTargetErrResp();
	void onRobResultResp(uint32_t uid, byte ret, int32_t exp, int32_t res);
	void onRobNotice(uint32_t uid);
	void onSpeedUpResp(uint32_t uid, byte ret);
	void onStarRewardResp(uint32_t uid, byte ret, const Award &reward);
	void onRevengeResp(byte ret);
	void onCashResetResp(byte ret);
	//other
	bool onBoxReward(uint32_t lv, uint32_t id, uint32_t count, Award *result);
	bool initNpc();
	MerchantNpc* randNpc();
	int32_t calcExp(int32_t ae, int32_t be, uint32_t star, uint32_t lv);
	uint32_t caleRes(uint32_t totalRes, uint32_t lostRes, uint32_t damage);
	void delTimeOutLog(unsigned uid);
	bool robUser(uint32_t uid, CBoatRobResultProtocol &p);
	bool robNpc(uint32_t uid, CBoatRobResultProtocol &p);
	bool robTarget(uint32_t uid, CBoatRobResultProtocol &p);
	bool addLog(uint32_t att, uint32_t def, uint32_t damage, uint32_t star, int32_t res, int32_t ex, byte train_id, const string &s, const string &t, const string &sd, const string &sk);
	bool getBoatInfo(uint32_t id, IBuffer *buff, MerchantNpc &data);
	bool getNpcInfo(uint32_t id,  IBuffer *buff);
private:
	DataBoat m_boat;
	map<uint8_t, DataBoatTrain> m_train;
	map<byte, vector<DataBoatRobLog> > m_rob_log;
	map<uint32_t, MerchantNpc> m_npc;
	string m_last_npc_name;
	MerchantNpc m_target;
	uint32_t revenge_id;
};

#endif /* _BOAT_MANAGER_H_ */
