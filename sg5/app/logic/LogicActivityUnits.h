/*
 * LogicActivityUnits.h
 *
 *  Created on: 2016-8-24
 *      Author: Administrator
 */

#ifndef LOGICACTIVITYUNITS_H_
#define LOGICACTIVITYUNITS_H_

#include "LogicInc.h"
#include "CMDBase.h"

class CActUnit : public CCMDBase
{
public:
	CActUnit();
	virtual ~CActUnit();
	virtual int Init(unsigned uid, const string &act_time_name="", unsigned lasttime=0, unsigned seqid=0);
	virtual int Process(const Json::Value &data, unsigned type) {return 0;};
	virtual int GetNewAct(void) {return 0;};
	virtual int GetResult(Json::Value &result) { return 0;};
	virtual unsigned GetTotalCharge(void);
	virtual unsigned GetDailyCharge(void);
	virtual unsigned GetTotalConsume(void);
	virtual unsigned GetDailyConsume(void);
	virtual bool CheckActTime(void);
	virtual bool CheckVersion(void);
protected:
	ActInfoConfig _act_time;  //活动时间
	string _act_time_name;
};


class CActTouZiDaFanLi: public CActUnit {
public:
	enum {
		ACT_TOUZI_DAFALI_PROCESS_TOUZI = 0,
		ACT_TOUZI_DAFALI_PROCESS_LINGQU = 1,
		ACT_TOUZI_DAFALI_PROCESS_DUIHUAN = 2,
		ACT_TOUZI_DAFALI_PROCESS_YIJIANLINGQU = 3
	};
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	virtual int SaveNewAct(void);
	int GetChongZhiPoint();
	int touzi(unsigned id, unsigned money);
	int lingqu(unsigned id);
	int yijianlingqu();
	int duihuan(unsigned id);
private:
	int GetNowPoint();
	int CheckLingQu(const string & s,const DataXMLTouZiDaFanLi & config, unsigned id);
	void GetNewActIndex(unsigned id, Json::Value *& wh);
private:
	Json::Value _new_act_2;
	Json::Value _new_act_3;
};
class CActGuYu: public CActUnit {
public:
	enum {
		ACT_GUYU_PROCESS_ONLINE = 1,
		ACT_GUYU_PROCESS_JIFEN = 2,
		ACT_GUYU_PROCESS_MEIRI = 3,
		ACT_GUYU_PROCESS_JINJIE_DIAMOND = 4, //消耗钻石
		ACT_GUYU_PROCESS_JINJIE_HUANYU = 5  //幻羽
	};
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	virtual int SaveNewAct(void);
	int online();
	int jifen(unsigned id);
	int meiri(unsigned id);
	int diamond();
	int huanyu();
	int sumHuanyu(int num);
private:
	Json::Value _new_act_2;
	Json::Value _new_act_3; 
};

//星石积分
class CActXingshiPoints : public CActUnit
{
	public:
		virtual int Process(const Json::Value &data, unsigned type);
		virtual int GetNewAct(void);
		virtual int GetResult(Json::Value &result);
	private:
		int GetStoneGrade();
};

class CActchildrenDaysActivity: public CActUnit {
public:
	enum {
		ACT_CHILDRENDAT_PROCESS_GET = 0,
		ACT_CHILDRENDAT_PROCESS_LINGQU = 1,  //领取
		ACT_CHILDRENDAT_PROCESS_DUIHUAN = 2, //兑换
	};
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	virtual unsigned GetTotalCharge(void);
	int initconfig();
	int lingqu(unsigned id);
	int duihuan(unsigned id);
private:
	DataXMLchildrenDaysActivity _config;
	Json::Value jsoncount;
};

class CActWuYiQingDian: public CActUnit {
public:
	enum {
		ACT_WUYIQINGDIAN_PROCESS_MEIRI = 1,
		ACT_WUYIQINGDIAN_PROCESS_JIFEN = 2,
	};
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	int jifen(unsigned id);
	int meiri(unsigned id);
	int initconfig();
	int get_pass_day();
	unsigned get_meiri_item_num(unsigned idx);
private:
	DataXMLWuYiQingDian _config;
};

class CActyongguansanjun: public CActUnit {
public:
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	int initconfig();
	bool CheckVersion(void);
private:
	DataXMLyongguansanjun_goumai _config;
	unsigned _non_zero;
};

class CActQunXing: public CActUnit {
public:
	enum {
		ACT_QUNXING_DAILY = 0,
		ACT_QUNXING_TOTAL = 1,
		ACT_QUNXING_JINDU = 2,
	};
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	int Daily(unsigned id);
	int Total(unsigned id);
	int Jindu(unsigned id);
	int SetPoint(unsigned point);
	int AddJinDu();
	int GetInfo(Json::Value &result);
};

class CActQiTianJinJie: public CActUnit {
public:
	virtual int Process(const Json::Value &data, unsigned type);
	virtual int GetNewAct(void);
	virtual int GetResult(Json::Value &result);
	int meiri(unsigned id);
	int initconfig();
	int get_pass_day();
	unsigned get_meiri_item_num(unsigned idx);
private:
	int _idx_zone;
	DataXMLQiTianJinJie _config;
};

#endif /* LOGICACTIVITYUNITS_H_ */
