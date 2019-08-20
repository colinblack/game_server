/*
 * CMDBase.h
 *
 *  Created on: 2016-8-27
 *      Author: Administrator
 */

#ifndef CMDBASE_H_
#define CMDBASE_H_

#include "Kernel.h"
#include "DataInc.h"

class CCMDBase
{
public:
	CCMDBase();
	virtual ~CCMDBase();
	virtual int Init(unsigned uid, unsigned lasttime=0, unsigned seqid=0);
	virtual int Check(void);
	virtual int Save(void);
	virtual int SaveNewAct(void);
	virtual void GetLastTimeAndSeq(Json::Value &result);
	virtual void ResourceLog(void);
	virtual int ChangePay(int cash, int coins, const string &code);
	virtual int ParseSimpleReward(const XMLActSimpleReward *pdata, unsigned len, string &code, unsigned ats=0);
	virtual int ProvideCommonReward(const RewardConfig::RewardItemCfg & rewardcfg, const string & reason, unsigned endts);
	void ParseMaterial(Json::Value &material, unsigned index, int count);
protected:
	unsigned _uid;
	unsigned _lasttime;
	unsigned _seqid;
	unsigned _serverid;
	DataUser _user;
	bool _init;
	Json::Value _new_act;
public:
	Json::Value _equip;
	Json::Value _hero;
protected:
	unsigned _coins;
	unsigned _cash;
	unsigned _qle;
	unsigned _yl;
	unsigned _process_type;
// for resource log
	bool _need_resource_log;
	int _gcbas_chg;
	int _gcbuy_chg;
	int _r1_chg;
	int _r2_chg;
	int _r3_chg;
	int _r4_chg;
	int _r5_chg;
	int _prosper_chg;
	int _bs_chg;
	int _qle_chg;
	int _exp_chg;
	int _yl_chg;
};
#endif /* CMDBASE_H_ */
