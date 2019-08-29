/*
 * DataState.h
 *
 *  Created on: 2015年12月11日
 *      Author: hector
 */

#ifndef DATA_STATE_H_
#define DATA_STATE_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

enum {
	PLAYER_DATA_STATE_ACTIVITY_LOGIN				= 1,   //累计登陆,连续登陆信息
	PLAYER_DATA_STATE_SHARE_COUNT					= 2,   //分享次数
	PLAYER_DATA_STATE_ANTI_ADDICTION				= 3,   //收获加成
	PLAYER_DATA_STATE_DAILY_INTERACT				= 4,   //每日社交
	PLAYER_DATA_STATE_CLIENT_STATE					= 5,   //前台保存
	PLAYER_DATA_STATE_MERCHANT						= 6,   //商队
	PLAYER_DATA_STATE_SOLDIER_RECOVER_TRAIN			= 7,   //士兵恢复队列
	PLAYER_DATA_STATE_LEVEL_REWARD					= 8,   //等级奖励
	PLAYER_DATA_STATE_VIP							= 9,   //vip
	PLAYER_DATA_STATE_DAILY_BUY						= 10,  //每日交易
	PLAYER_DATA_STATE_SEVEN_TASK					= 11,  //开服庆典活动
	PLAYER_DATA_STATE_WORLD_SHOP					= 12,  //世界战争商店
	PLAYER_DATA_STATE_MONTH_GIFT					= 13,  //月宝箱
	PLAYER_DATA_STATE_ONLINE_TS						= 14,  //在线时长
	PLAYER_DATA_STATE_SEVEN_DAY_TASK				= 15,  //七日目标
	PLAYER_DATA_STATE_WATCH_AD						= 16,  //广告观看
	PLAYER_DATA_STATE_STAR_BOX						= 17,  //星级宝箱
	PLAYER_DATA_STATE_MAX
};

struct DataState {
	uint32_t uid;
	uint32_t id;
	string data;

	DataState(): uid(0), id(0) {
	}

	DataState(uint32_t _uid, uint32_t _id, const string &_data) {
		uid = _uid;
		id = _id;
		data = _data;
	}
};

class CDataState: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataState(int table = DB_STATE): CDataBaseDBC(table) {
	}
	virtual ~CDataState() {
	}
	virtual void doRequest(CNetPacket* packet);
	int GetState(uint32_t uid, uint32_t id, string &data);
	int GetStates(uint32_t uid, vector<DataState>& vState);
	int AddState(uint32_t uid, uint32_t id, const string &data);
	int AddState(const DataState& dataState);
	int RealAddState(CNetPacket* packet);
	int SetState(uint32_t uid, uint32_t id, const string &data);
	int SetState(const DataState& dataState);
	int RealSetState(CNetPacket* packet);
	int ReplaceState(uint32_t uid, uint32_t id, const string &data);
	int ReplaceState(const DataState& dataState);
	int RealReplaceState(CNetPacket* packet);
	int RemoveOneState(uint32_t uid, uint32_t id);
	int RealRemoveOneState(CNetPacket* packet);
	int RemoveState(uint32_t uid);
	int RealRemoveState(CNetPacket* packet);
	int setStateSync(const DataState& dataState);
	int addStateSync(const DataState& dataState);
public:
	static bool printStat();
private:
	static map<uint32_t, uint32_t> m_stat;	// 统计包的收发量
};

#endif /* DATA_STATE_H_ */
