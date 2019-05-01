#ifndef LOGIC_COMP_PRODUCE_MANAGER_H
#define LOGIC_COMP_PRODUCE_MANAGER_H

#include "ServerInc.h"

class LogicCompProduceManager : public BattleSingleton, public CSingleton<LogicCompProduceManager>
{
private:
	friend class CSingleton<LogicCompProduceManager>;
	LogicCompProduceManager(){};
	virtual ~LogicCompProduceManager(){}

	enum
	{
		ret_by_full = 1, //背包格子满
		ret_by_not_enough, //材料不足
		ret_by_already_most, //到达最高等级
		pay_cash_level	= 4,  //花钻到达的产出等级
		produce_max_level = 5, //产出的最大等级
		package_max_limit = 28, //部件背包格子数
		pay_cash_daylimit = 30, //花钻每天次数上限
		need_pay_cash	= 50, //消耗的钻石数
		rate_max_value = 100,  //概率最大值
	};

public:
	virtual void CallDestroy() {Destroy();}

	int NewUserInit(unsigned uid);

	int LoginCheck(unsigned uid);

	//打开窗口
	int Process(unsigned uid, ProtoComponent::OpenComponentWindowReq* reqmsg, ProtoComponent::OpenComponentWindowResp* respmsg);

	//花钻产出
	int Process(unsigned uid, ProtoComponent::CashProduceReq* reqmsg, ProtoComponent::CashProduceResp* respmsg);

	//普通产出
	int Process(unsigned uid, ProtoComponent::ProduceReq* reqmsg, ProtoComponent::ProduceResp* respmsg);

	//一键产出
	int Process(unsigned uid, ProtoComponent::OneKeyProduceReq* reqmsg, ProtoComponent::OneKeyProduceResp* respmsg);

	//背包是否已满
	bool IsPackageFull(unsigned uid);

	int FullMessage(unsigned uid, ProtoComponent::ProduceComponentCPP *msg);

private:
	//部件外部接口
	int ComponentInterfaceExt(unsigned uid, unsigned type);

	int OpenWindow(unsigned uid, ProtoComponent::OpenComponentWindowResp * respmsg);

	//花钻产出-实际并未产出物品，只是修改产出等级
	int PayCashProduce(unsigned uid, ProtoComponent::CashProduceResp * respmsg);

	//普通产出
	int Produce(unsigned uid, ProtoComponent::ProduceResp * respmsg);

	//一键产出
	int OneKeyProduce(unsigned uid, ProtoComponent::OneKeyProduceResp * respmsg);

	//产出的底层实现
	int ProduceUnderly(unsigned uid, string reason, ProtoComponent::ProductCPP * msg);

	//扣材料及生产产品
	int CostAndProduce(unsigned uid, string reason, const ComponentConfig::Produce & produceconfig, ProtoComponent::ProductCPP * msg);
};

#endif //LOGIC_COMP_PRODUCE_MANAGER_H
