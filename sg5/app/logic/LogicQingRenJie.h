#ifndef LOGICQINGRENJIE_H_
#define LOGICQINGRENJIE_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicQingRenJie : public LogicBase<CDataQingRenJie>
{
public:
	CLogicQingRenJie(){}
	~CLogicQingRenJie(){}

	int QingRenJieXianHua(unsigned uid, unsigned nsid, unsigned type, unsigned num, Json::Value &result);
	int QingRenJieLeiJi(unsigned uid, unsigned id, Json::Value &result);
	int GetQingRenJie(Json::Value &result);
};



#endif /* LOGICQINGRENJIE_H_ */
