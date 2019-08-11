/*
 * GemManager.h
 *
 *  Created on: 2019年8月6日
 *      Author: memory
 */

#ifndef GEMMANAGER_H_
#define GEMMANAGER_H_

#include "BattleBaseInc.h"

class GemManager: public CSingleton<GemManager> {
private:
	friend class CSingleton<GemManager>;
	GemManager();
	~GemManager();

public:
	bool Process(uint32_t uid, logins::CEmbedGemReq* req, logins::SEmbedGemResp* resp); //1037 宝石 镶嵌/替换/一键替换
	bool Process(uint32_t uid, logins::CRemoveGemReq* req, logins::SRemoveGemResp* resp); //1056 宝石 卸下
	bool Process(uint32_t uid, logins::CctivateGemTargetReq* req); //1057 激活宝石目标
	bool Process(uint32_t uid, logins::CUpgradeGemReq* req, logins::SUpgradeGemResp* resp); //1120 宝石 升级/一键升级
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props); // 计算： 所变化的战力
	bool useGemItem(UserCache& cache, DataEquip equip, uint32_t cost, const string &code);

private:
	string updateExtend(string &str, map<int32_t,int64_t> ,uint32_t uid,uint32_t rid);
	string DeleteExtend(string &str, int32_t gemSlot,uint32_t uid,uint32_t rid);
	string upgrateExtend(string &str, vector<int32_t> gemSlot,uint32_t uid,uint32_t rid);

	bool String2Vector(vector<uint32_t>gemUidSlot,string str);

public:
	 bool FormatMsg(const DataForge &data, dbs::TPlayerEquip &msg);

	uint32_t getPos(string &str);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerFashionInfo *resp); // 服务器主动推送的消息


};

#endif /* GEMMANAGER_H_ */
