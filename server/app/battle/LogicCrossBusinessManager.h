#ifndef LOGIC_CROSS_BUSINESS_MANAGER_H
#define LOGIC_CROSS_BUSINESS_MANAGER_H

#include "ServerInc.h"

class LogicCrossBusinessManager : public BattleSingleton, public CSingleton<LogicCrossBusinessManager>
{
private:
	friend class CSingleton<LogicCrossBusinessManager>;
	LogicCrossBusinessManager(){};
	virtual ~LogicCrossBusinessManager(){}

public:
	enum
	{
		max_slot_items = 6, //最大格子数
	};

	virtual void CallDestroy() {Destroy();}

	//打开窗口
	int Process(unsigned uid, ProtoCrossBusiness::BusinessOpenWindowReq *reqmsg, ProtoCrossBusiness::BusinessOpenWindowResp * respmsg);

	//刷新
	int Process(unsigned uid, ProtoCrossBusiness::BusinessRefreshReq *reqmsg, ProtoCrossBusiness::BusinessRefreshResp * respmsg);

	//购买
	int Process(unsigned uid, ProtoCrossBusiness::BusinessPurchaseReq *reqmsg, ProtoCrossBusiness::BusinessPurchaseResp * respmsg);
private:
	//打开窗口
	int OpenWindow(unsigned uid, ProtoCrossBusiness::BusinessOpenWindowResp * respmsg);

	//刷新商店
	int RefreshShop(unsigned uid, bool iscash, ProtoCrossBusiness::BusinessRefreshResp * respmsg);

	//购买
	int Purchase(unsigned uid, unsigned pos, ProtoCrossBusiness::BusinessPurchaseResp * respmsg);

	//底层刷新
	int Refresh(unsigned uid, bool iscash);

	//设置指定格子的值
	int SetSlotValue(DataCrossBusiness & business, int pos, unsigned value);

	//获取指定格子的值
	unsigned GetSlotValue(DataCrossBusiness & business, int pos);
};

#endif //LOGIC_CROSS_BUSINESS_MANAGER_H
