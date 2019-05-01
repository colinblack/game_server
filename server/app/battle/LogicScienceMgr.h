/*
 * LogicScienceMgr.h
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#ifndef LOGICSCIENCEMGR_H_
#define LOGICSCIENCEMGR_H_

/**
 * 科技系统
 */

#include "ServerInc.h"


class DBCScienceWrap
{
public:
	DBCScienceWrap(unsigned uid, unsigned id);
	DBCScienceWrap(unsigned uid, ScienceType type);
	DBCScienceWrap(unsigned index);

	void Save()
	{
		container_->m_data->MarkChange(index_);
	}

	DBCScience& Obj()
	{
		return data_;
	}

	const DBCScience& Obj() const
	{
		return data_;
	}

	const ScienceConfig::ScienceItem& Cfg() const
	{
		return cfg_;
	}

	unsigned AttrValue() const;

	//注资
	void Capital();
	//解锁状态
	unsigned GetSurplusUnlockTime();
	//加速解锁的元宝数
	unsigned GetSpeedUnlockGolds();
	//完成解锁
	void FinishUnlock();

	void SetNormal();

	void Reset();
private:
	//取同类型值最大的id
	int type2index(unsigned uid, ScienceType type);

	void Init();
private:
	DataScienceMgr*	container_;
	unsigned 		index_;
	DBCScience&		data_;
	const ScienceConfig::ScienceItem& cfg_;
};


class LogicScienceMgr : public BattleSingleton, public CSingleton<LogicScienceMgr>
{
private:
	friend class CSingleton<LogicScienceMgr>;
	LogicScienceMgr();

	struct _UnlockItem
	{
		unsigned uid; //
		unsigned id;  //科技id
		int 	 surplus; //剩余时间


		_UnlockItem(const DBCScienceWrap& science)
			: uid(science.Obj().uid)
			, id(science.Obj().id)
			, surplus(science.Obj().value - Time::GetGlobalTime())
		{
			//加入值过大记录一下
			if (surplus > 30*60*24 || surplus < 0)
			{
				error_log("uid:%u, id:%u, surplus:%d", uid, id, surplus);
			}
		}
	};
private:
	void CheckIdParams(unsigned id);

	DemoOfflineProperty _Type2Prop(ScienceType type);
	unsigned			_TypeValue(ScienceType type, const DBCScienceWrap& science);
	unsigned			_TypeValue(ScienceType type, unsigned uid);

	///////////////////////////////////////////////////////////////
	void FinishHeroExpandFightAtrr(const DBCScienceWrap& science); //
	void FinishHeroBaseFightAttr(const DBCScienceWrap& science);
	void FinishBuildCapacity(const DBCScienceWrap& science);

	void SyncAttr2ResourceManager(const DBCScienceWrap& science);

	//资源类型转换成对应的科技类型
	int ResourceType2ScienceType(int type);
public:
	virtual void CallDestroy() { Destroy();}

	void OnTimer1();

	void Online(unsigned uid);
	void Offline(unsigned uid);

	//重置用户科技，使其未解锁
	void Reset(unsigned uid);


	//没有返回0
	unsigned	GetScienceId(unsigned uid, ScienceType type);
	//同步数据
	void Sync(unsigned uid, OfflineResourceItem& item);
	void Finish(const DBCScienceWrap& science);

	//判断某项科技是否开始研究
	bool IsScienceBeginResearch(unsigned uid, unsigned id);

	//某项科技是否研究完成
	bool IsScienceDoneResearch(unsigned uid, unsigned id);

	//////////////////////////////////////////////////////////////////
	//获取小兵等级 throw std::runtime_error
	int GetSoldierLevel(unsigned uid);
	//获取小兵排数 throw std::runtime_error
	int GetSoldierRows(unsigned uid);
#if 0
	//战法攻击系数  throw std::runtime_error
	int GetSkillAttackFactor(unsigned uid);
	//战法抵抗系数  throw std::runtime_error
	int GetSkillDefendFactor(unsigned uid);
	//战斗中产出的英雄经验增加系数
	int GetHeroFightExpFactor(unsigned uid);
#endif
	//上阵英雄攻防血百分比加成？固定值加成？
	int GetHeroFightFactor(unsigned uid);
	//可招募的英雄数
	int GetRecruitHeros(unsigned uid);
	//仓库加成
	int GetStorageFactor(unsigned uid);
	//功勋宝箱
	int GetExploitBoxLevel(unsigned uid);
	//每日任务
	int GetDayTaskLevel(unsigned  uid);
	//国战任务科技
	int GetCountryWarLevel(unsigned uid);

	//资源加成
	int GetYieldFactor(unsigned uid, int type);

	//是否有建筑功勋
	bool IsBuildExploit(unsigned uid);
	//////////////////////////////////////////////////////////////////
	int Process(unsigned uid, ProtoScience::ScienceCapitalReq* req, ProtoScience::ScienceCapitalResp* resp);
	int Process(unsigned uid, ProtoScience::ScienceSpeedCdReq* req, ProtoScience::ScienceSpeedCdResp* resp);

	void FullMessage(unsigned uid, User::Science* obj);

	void SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj);
	////////////////////////////////////////////////////////////////////////////////////
	void AddUnlockQueue(const DBCScienceWrap& science);

	int GetTypeValue(unsigned uid,  ScienceType type, int default_val);
private:
	//从科技解锁队列中移除用户
	void RemoveFromUnlockQueue(unsigned uid);
private:
	std::vector<_UnlockItem> lock_queue_;

	typedef void (LogicScienceMgr::*ScienceFinishImpl)(const DBCScienceWrap&);
	std::map<ScienceType, ScienceFinishImpl> m_finish_table;
};

#endif /* LOGICSCIENCEMGR_H_ */
