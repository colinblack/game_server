/*
 * LogicChampionshipManager.h
 *
 *  Created on: 2018年10月9日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_
#define APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_

#include "ServerInc.h"



class LogicChampionshipManager : public BattleSingleton, public CSingleton<LogicChampionshipManager>
{
private:
	struct ApplyRecord{
		unsigned uid;
		int coins;
		unsigned type;
		unsigned heroid;

		ApplyRecord(unsigned nUid, int nCoins, unsigned nType, unsigned nHeroid)
					: uid(nUid), coins(nCoins), type(nType), heroid(nHeroid)
		{
		}
	};

private:
	friend class CSingleton<LogicChampionshipManager>;
	LogicChampionshipManager() : timer_cnt_(0)
	{
	}

public:
	virtual void CallDestroy() { Destroy();}
	void OnTimer1();

	//参加比赛
	int Process(unsigned uid, ProtoChampionship::ProtoJoinInMatchReq* req, ProtoChampionship::ProtoJoinInMatchResp* resp);
	//开始比赛
	int Process(unsigned uid, ProtoChampionship::ProtoChampionshipReq* req, ProtoChampionship::ProtoChampionshipResp* resp);

	void SetMessage(unsigned uid, unsigned battleid, unsigned heroid, ProtoChampionship::MatchUserInfoCPP* msg);

private:
	unsigned timer_cnt_; //计时
};

#endif /* APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_ */
