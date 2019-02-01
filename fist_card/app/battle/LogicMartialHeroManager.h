/*
 * LogicMartialHeroManager.h
 *
 *  Created on: 2018年9月3日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICMARTIALHEROMANAGER_H_
#define APP_BATTLE_LOGICMARTIALHEROMANAGER_H_

#include "ServerInc.h"

class DBCMartialHeroWrap
{
public:
	DBCMartialHeroWrap(unsigned index);
	DBCMartialHeroWrap(unsigned uid, unsigned heroid);

	DataMartialHero& Obj()
	{
		return data_;
	}

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

//	void FullMessage(ProtoMartialClub::MartialHeroInfo* msg);

private:
	DataMartialHeroManager* container_;
	unsigned index_;
	DataMartialHero& data_;
};

class LogicMartialHeroManager : public  BattleSingleton, public CSingleton<LogicMartialHeroManager>
{
private:
	friend class CSingleton<LogicMartialHeroManager>;
	LogicMartialHeroManager(){};

public:
	virtual void CallDestroy() { Destroy();}

	//跨服更新武馆中的英雄信息
	int Process(ProtoMartialClub::ProtoCSMartialHeroInfo* req);

	//设置武馆中的英雄
	int AddMartialHero(unsigned uid, unsigned detachUid, unsigned grade, unsigned heroid,  unsigned slot, string reason);
	//是否满足设置条件
	bool IsValid(unsigned uid, unsigned setUid, unsigned heroId, unsigned grade,  unsigned slot);
	//更新武馆英雄信息
	void UpdateMartialHeroInfo(unsigned uid);

//	void FullMessage(unsigned uid, User::MartialHero* msg);
};


#endif /* APP_BATTLE_LOGICMARTIALHEROMANAGER_H_ */
