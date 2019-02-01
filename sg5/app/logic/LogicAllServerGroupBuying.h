#ifndef LOGIC_ALLSERVER_GROUPBUY_H_
#define LOGIC_ALLSERVER_GROUPBUY_H_


#include "LogicInc.h"
#include "LogicBase.h"

#include "DataAllServerGroupBuying.h"

//跨区团购
class CLogicAllServerGroupBuying : public LogicBase<CDataAllServerGroupBuying>
{
public:
	enum
	{
		max_items_nums = 3, //团购项个数
	};

	//加载排行榜数据
	int Load(unsigned uid, Json::Value& result);

	//加入团购
	int Join(unsigned uid, unsigned id, Json::Value & result);

private:
	CDataAllServerGroupBuying* DataWrap();

	int CheckActivity();

	//判断活动是否开启
	bool IsActivityOpen();

	//给参团的用户发送返回钻石的邮件
	int SendBackEmail(unsigned id, unsigned interuid, unsigned number, unsigned cash);

	int GetConfigVersion();
};

#endif /* LOGIC_ALLSERVER_GROUPBUY_H_ */
