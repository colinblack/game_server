/*
 * FashionManager.h
 *
 *  Created on: 2019年7月30日
 *      Author: memory
 */

#ifndef FASHIONMANAGER_H_
#define FASHIONMANAGER_H_

#include "BattleBaseInc.h"

class FashionManager: public CSingleton<FashionManager> {
private:
	friend class CSingleton<FashionManager>;
	FashionManager();
	~FashionManager();

private:
	uint32_t GetIndexByIdAndNum(uint32_t id,uint32_t num);

public:
	bool Process(uint32_t uid, logins::CActiveFashionReq* req, msgs::SFashion* resp); // 激活 1418
	bool Process(uint32_t uid, logins::CPutOnFashionReq* req, logins::SPutOnFashionResp* resp); // 穿戴 2047
	bool Process(uint32_t uid, logins::CGetOffFashionReq* req, logins::SGetOffFashionResp* resp); // 脱下 2048
	bool Process(uint32_t uid, logins::CAdvanceFashionReq* req,msgs::SFashion* resp); //升级时装 2046
	bool Process(uint32_t uid, logins::CActiveFashionSuitReq* req,logins::SActiveFashionSuitResp * resp); //激活套装 3742
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props); // 计算：激活时装、升级时装  所增加的战力




public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerFashionInfo *resp); // 服务器主动推送的消息

};

#endif /* FASHIONMANAGER_H_ */
