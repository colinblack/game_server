/*
 * TitleManager.h
 *
 *  Created on: 2019年7月16日
 *      Author: memory
 */

#ifndef TITLEMANAGER_H_
#define TITLEMANAGER_H_

#include "BattleBaseInc.h"

class TitleManager: public CSingleton<TitleManager> {
private:
	friend class CSingleton<TitleManager> ;
	TitleManager();
	~TitleManager();

public:
	bool ActiveTitle(uint32_t uid, uint32_t rid, uint32_t id);// 激活称号，写入数据库
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props); // 计算获得称号后所增加的战力

	uint32_t GetShowId();
public:
	// 处理客户端称号穿戴情况消息
	bool Process(uint32_t uid, logins::STitleReq *req);
public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SIntIntMap *resp); // 服务器主动推送的消息
};

#endif /* TITLEMANAGER_H_ */

