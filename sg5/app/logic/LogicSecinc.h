#ifndef __LOGIC_SECINC_H__
#define __LOGIC_SECINC_H__

#include "LogicInc.h"

class CLogicSecinc
{
public:
	/* 2014901 Ralf change to save activity
	int AddSecinc(unsigned uid, unsigned eqid, unsigned amount);
	int ProcessSecinc(unsigned uid, const Json::Value &data);
	*/

	int GetSecinc(unsigned uid, Json::Value &data);
	int SetSecinc(unsigned uid, Json::Value &data);

	int GetSecinc(unsigned uid, unsigned sid, Json::Value &data);
	int SetOneSecinc(unsigned uid, Json::Value &data);
	int ImportSecinc(unsigned uid, Json::Value &data);
};

#endif
