#ifndef LOGICZHOUNIANQING_H_
#define LOGICZHOUNIANQING_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicZhouNianQing
{
public:
	CLogicZhouNianQing(){};
	~CLogicZhouNianQing(){}

	static CDataZhouNianQingQianDao* GetDataZhouNianQingQianDao(void);

	int QianDao(unsigned uid, unsigned last_time);

	int DuiHuan(unsigned uid, unsigned id, Json::Value & result);

	int GetQianDaoReward(unsigned uid, unsigned id, Json::Value & result);

	int zhouniantehuigoumai(unsigned uid, unsigned id, Json::Value & result);

	int GetInfo(Json::Value & result);

	int GetQuanFuInfo(Json::Value & result);

	int zhouniantehuibangding(unsigned uid, unsigned uid2, Json::Value & result);

	int AddQuanFuQianDaoZhi(int version, int count);

	int online(unsigned uid, Json::Value & result);

private:
	int GetSignNum(const DataXMLZhouNianQing & config);
	int GetShopNum(const DataXMLZhouNianQing & config);
	int GetYearShopNum(const DataXMLZhouNianQing & config);
};



#endif /* LOGICZHOUNIANQING_H_*/
