#ifndef LOGIC_MARKET_MANAGER_H
#define LOGIC_MARKET_MANAGER_H

#include "ServerInc.h"

class LogicMarketManager : public BattleSingleton, public CSingleton<LogicMarketManager>
{
private:
	friend class CSingleton<LogicMarketManager>;
	LogicMarketManager(){};
	virtual ~LogicMarketManager(){}

public:
	struct MarketItem
	{
		uint8_t type;
		uint8_t character;

		MarketItem():
			type(0),
			character(0)
		{
		}
	};

	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	int FullMessage(unsigned uid, ProtoMarket::MarketCPP *msg);

private:
	//刷新时间到达之后自动刷新
	int RefreshByTime(unsigned uid);

	//集市购买资源
	int Purchase(unsigned uid, unsigned index, ProtoMarket::PurchaseMarketResp *respmsg);

	//根据类型和品质获取对应的数值
	int GetMarketValue(uint8_t type, uint8_t characer);
	//购买后的刷新
	int RefreshAfterBuy(unsigned uid);

	int RefreshMarketItem(MarketItem & marketitem);
};

#endif //LOGIC_MARKET_MANAGER_H
