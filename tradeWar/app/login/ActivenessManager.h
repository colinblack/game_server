#ifndef ACTIVENESSMANAGER_H_
#define ACTIVENESSMANAGER_H_

#include "Kernel.h"
#include "DataActiveness.h"
#include "Award.h"

class Player;
typedef enum
{
	ACTIVENESS_ATTACK = 1,
	ACTIVENESS_BOAT = 2,
	ACTIVENESS_GATE = 3,
	ACTIVENESS_HARVEST = 4,
	ACTIVENESS_ZHEN = 5,
	ACTIVENESS_BUILD = 6,
	ACTIVENESS_UPSOLDIER = 7,
	ACTIVENESS_ZhengWu = 8,
	ACTIVENESS_MAX
} ActivenessTaskType;

struct ActivenessMsg
{
	uint32_t id;
	uint32_t count;
	byte finish;
	ActivenessMsg() :
			id(0), count(0), finish(0)
	{
	}
	void fromJson(const Json::Value &value)
	{
		if (value.isNull() || !value.isObject())
		{
			return;
		}
		id = value.get("id", 0).asUInt();
		count = value.get("v", 0).asUInt();
		finish = value.get("r", 0).asUInt();
	}
	void toJson(Json::Value &value)
	{
		value = Json::Value(Json::objectValue);
		value["id"] = id;
		value["v"] = count;
		value["r"] = static_cast<uint32_t>(finish);
	}
	bool operator==(uint32_t index)
	{
		return id == index;
	}
};

class ActivenessManager
{
public:
	enum
	{
		ACTIVENESS_FLAG_DOING = 0,
		ACTIVENESS_FLAG_FINISH = 1
	};
	ActivenessManager();
	~ActivenessManager();
	void setPlayer(Player* player)
	{
		m_player = player;
	}
	bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool onLogin();
	bool onAttack();
	bool onBoat();
	bool onGate();
	bool onHarvest();
	bool onZhen();
	bool onBuild();
	bool onUpSoldier();
	bool onZhengWu();
	uint32_t getScore() {
		return m_score;
	}
	bool setScore(uint16_t score) {
		m_score = score;
		m_sync = true;
		saveData(false);
		return true;
	}
private:
	bool doProgress(uint32_t id, uint32_t count = 1);
	bool setValue(uint32_t id, uint32_t value);
	bool getValue(uint32_t id, uint32_t &value);
	bool doView(CNetPacket *packet);
	bool doBuy(CNetPacket *packet);
	bool doFinish(CNetPacket *packet);
	bool onFinishResp(byte ret, uint32_t id = 0);
	bool doReward(CNetPacket *packet);
	bool onRewardResp(byte ret, uint32_t id = 0);
	bool checkData();
	bool resetData();
	bool saveData(bool isAdd = false);
	bool sendData();
	bool sendScore();
private:
	Player* m_player;
	vector<ActivenessMsg> m_msg;
	uint16_t m_score;
	uint32_t m_resetTs;
	uint32_t m_reward;
	bool m_sync;
};

#endif
