#include "LogicSellComponentActivity.h"

int LogicSellComponentActivity::Process(unsigned uid, ProtoActivity::OpenSellComponentWindowReq *reqmsg, ProtoActivity::OpenSellComponentWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicSellComponentActivity::OpenWindow(unsigned uid, ProtoActivity::OpenSellComponentWindowResp * respmsg)
{
	int ret = CheckActivity();

	if (ret)
	{
		throw runtime_error("activity_not_open");
	}

	DataSellComponent& sellcomponent = DataSellComponentManager::Instance()->GetSellComponent(uid);
	unsigned now = Time::GetGlobalTime();

	int diff = CTime::GetDayInterval(sellcomponent.opents, now);

	if (diff > 0)
	{
		//跨天，重置活动数据
		ResetActivity(sellcomponent, now);
	}

	sellcomponent.SetMessage(respmsg->mutable_sellinfo());

	return 0;
}

int LogicSellComponentActivity::Process(unsigned uid, ProtoActivity::BuyComponentReq *reqmsg, ProtoActivity::BuyComponentResp * respmsg)
{
	unsigned index = reqmsg->index();

	BuyComponent(uid, index, respmsg);

	return 0;
}

int LogicSellComponentActivity::BuyComponent(unsigned uid, unsigned index, ProtoActivity::BuyComponentResp * respmsg)
{
	int ret = CheckActivity();

	if (ret)
	{
		throw runtime_error("activity_not_open");
	}

	//判断参数合法性
	if(index < 1 || index > 2)
	{
		error_log("wrong param:index. uid=%u,index=%u", uid, index);
		throw runtime_error("wrong_param");
	}

	DataSellComponent& sellcomponent = DataSellComponentManager::Instance()->GetSellComponent(uid);
	const SellComponentConfig::GoodInfo & goodcfg = SellComponentConfigWrap().GetGoodsInfoByIndex(index);

	int all_times = goodcfg.times();
	int times_now = 0;

	switch(index)
	{
		case 1: times_now = sellcomponent.num1; break;
		case 2: times_now = sellcomponent.num2; break;
		default:break;
	}

	//判断购买次数是否足够
	if (times_now >= all_times)
	{
		error_log("buy times already max. uid=%u,index=%u", uid, index);
		throw runtime_error("times_already_max");
	}

	//当有部件奖励时，判断部件格子是否已满
	for(int i = 0; i < goodcfg.goods_size(); ++i)
	{
		if (goodcfg.goods(i).has_component() && LogicCompProduceManager::Instance()->IsPackageFull(uid) )
		{
			throw runtime_error("component_package_full");
		}
	}

	//扣除钻石
	DBCUserBaseWrap userwrap(uid);
	userwrap.CostCash(goodcfg.price(), "SellComponent");

	//发放奖励
	for(int i = 0; i < goodcfg.goods_size(); ++i)
	{
		LogicUserManager::Instance()->OpReward(userwrap, goodcfg.goods(i), "SellComponent", respmsg->mutable_reward());
	}

	//活动数据修改
	switch(index)
	{
		case 1: sellcomponent.num1 += 1; break;
		case 2: sellcomponent.num2 += 1; break;
		default:break;
	}

	DataSellComponentManager::Instance()->UpdateSellComponent(sellcomponent);
	sellcomponent.SetMessage(respmsg->mutable_sellinfo());

	//钻石数量
	respmsg->set_cash(userwrap.Obj().cash);
	respmsg->set_index(index);

	return 0;
}

int LogicSellComponentActivity::ResetActivity(DataSellComponent& sellcomponent, unsigned ts)
{
	sellcomponent.opents = ts;
	sellcomponent.num1 = 0;
	sellcomponent.num2 = 0;

	DataSellComponentManager::Instance()->UpdateSellComponent(sellcomponent);

	return 0;
}

int LogicSellComponentActivity::CheckActivity()
{
	if (!IsOn())
	{
		return R_ERROR;
	}

	return 0;
}
