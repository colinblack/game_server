/*
 * LogicAllServerLordsList.h
 *
 *  Created on: 2016-7-6
 *      Author: dawx62fac
 */

#ifndef LOGICALLSERVERLORDSLIST_H_
#define LOGICALLSERVERLORDSLIST_H_


#include "LogicInc.h"
#include "LogicBase.h"

#include "DataAllServerLordsList.h"

/**
 * 尊主榜
 */

class CLogicAllServerLordsList : public LogicBase<CDataAllServerLordsList>
{

public:
	//同步排行榜数据
	int Sync(int type, const Json::Value& jsonList);
	//确立尊主
	//int Establish(int type);
	//关闭膜拜
	int CloseWorship();
	int Worship(unsigned uid, int id, int type, Json::Value& result);

	int GetRankList(unsigned uid, int type, Json::Value& result);
	int GetAllLords(unsigned uid, Json::Value& result);
private:
	CDataAllServerLordsList* DataWrap();

};



#endif /* LOGICALLSERVERLORDSLIST_H_ */
