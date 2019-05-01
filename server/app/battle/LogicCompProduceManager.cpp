#include "LogicCompProduceManager.h"

int LogicCompProduceManager::NewUserInit(unsigned uid)
{
	DataProduceComponentManager::Instance()->New(uid);

	return 0;
}

int LogicCompProduceManager::LoginCheck(unsigned uid)
{
	//检查累积登录数据是否加载进内存
	int ret = DataProduceComponentManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataProduceComponentManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)
		{
			return NewUserInit(uid);
		}
	}

	return ret;
}

int LogicCompProduceManager::Process(unsigned uid, ProtoComponent::OpenComponentWindowReq* reqmsg, ProtoComponent::OpenComponentWindowResp* respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicCompProduceManager::OpenWindow(unsigned uid, ProtoComponent::OpenComponentWindowResp * respmsg)
{
	DBCUserBaseWrap userwrap(uid);

	respmsg->set_material(userwrap.Obj().market);

	return 0;
}

int LogicCompProduceManager::Process(unsigned uid, ProtoComponent::CashProduceReq* reqmsg, ProtoComponent::CashProduceResp* respmsg)
{
	PayCashProduce(uid, respmsg);

	return 0;
}

int LogicCompProduceManager::PayCashProduce(unsigned uid, ProtoComponent::CashProduceResp * respmsg)
{
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);

	unsigned level = produce.current_level;

	if (level >= pay_cash_level)
	{
		error_log("current level is greater-equal than limit level. uid=%u,current_level=%u,limit_level=%u", uid, level, pay_cash_level);
		throw runtime_error("current_level_not_match");
	}

	//判断是否跨天
	unsigned now = Time::GetGlobalTime();

	if (CTime::GetDayInterval(produce.paycash_ts, now))  //跨天，重置已花钻次数
	{
		produce.times = 0;
		produce.paycash_ts = now;
	}

	//判断花钻次数是否达到上限
	if (produce.times >= pay_cash_daylimit)
	{
		error_log("pay cash times not enough. uid=%u,usetimes=%u,limit_times=%u", uid, produce.times, pay_cash_daylimit);
		throw runtime_error("times_not_enough");
	}

	//扣钻
	unsigned newcash = 0;
	LogicUserManager::Instance()->CostCash(uid, need_pay_cash, "Component", newcash);

	respmsg->set_cash(newcash);

	//更新花钻后的信息
	produce.current_level = pay_cash_level;
	produce.ispaycash = 1;
	produce.times += 1;
	produce.paycash_ts = now;

	DataProduceComponentManager::Instance()->UpdateDataCompProduce(produce);
	produce.SetMessage(respmsg->mutable_produce());

	return 0;
}

int LogicCompProduceManager::Process(unsigned uid, ProtoComponent::ProduceReq* reqmsg, ProtoComponent::ProduceResp* respmsg)
{
	Produce(uid, respmsg);

	//todo 接入品质部件成就
	ComponentInterfaceExt(uid, achievement_type_character_component);

	return 0;
}

int LogicCompProduceManager::Produce(unsigned uid, ProtoComponent::ProduceResp * respmsg)
{
	//调用底层生产函数
	int ret = ProduceUnderly(uid, "Produce", respmsg->mutable_product());

	if (ret_by_full == ret)
	{
		throw runtime_error("component_package_already_full");
	}
	else if (ret_by_not_enough == ret)
	{
		throw runtime_error("material_not_enough");
	}

	//加载材料
	DBCUserBaseWrap userwrap(uid);
	respmsg->set_material(userwrap.Obj().market);

	//加载玩家的产出信息
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);
	produce.SetMessage(respmsg->mutable_produce());

	return 0;
}

int LogicCompProduceManager::Process(unsigned uid, ProtoComponent::OneKeyProduceReq* reqmsg, ProtoComponent::OneKeyProduceResp* respmsg)
{
	OneKeyProduce(uid, respmsg);

	//todo 接入品质部件成就
	ComponentInterfaceExt(uid, achievement_type_character_component);

	return 0;
}

int LogicCompProduceManager::OneKeyProduce(unsigned uid, ProtoComponent::OneKeyProduceResp * respmsg)
{
	//注意三个停止条件
	//1.格子满时
	//2.材料不足时
	//3.已到底最高等级的产出
	int ret = 0;

	while(true)
	{
		ret = ProduceUnderly(uid, "OneKeyProduce", respmsg->add_product());

		if (ret)
		{
			break;
		}
	}

	//加载材料
	DBCUserBaseWrap userwrap(uid);
	respmsg->set_material(userwrap.Obj().market);

	//加载玩家的产出信息
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);
	produce.SetMessage(respmsg->mutable_produce());

	respmsg->set_stopcode(ret);

	return 0;
}

int LogicCompProduceManager::ComponentInterfaceExt(unsigned uid, unsigned type)
{
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = type;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

int LogicCompProduceManager::ProduceUnderly(unsigned uid, string reason, ProtoComponent::ProductCPP * msg)
{
	bool isfull = IsPackageFull(uid);

	if (isfull)
	{
		return ret_by_full;
	}

	//加载玩家的产出信息
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);

	//判断是否花钻产出
	if (produce.ispaycash && (produce.current_level < pay_cash_level))
	{
		error_log("[ProduceUnderly] after pay cash, illegal thing happen. uid=%u,current_level=%hhu,need_level=%u", uid, produce.current_level, pay_cash_level);
		throw runtime_error("current_level_error");
	}

	ComponentConfigWrap componentconfigwrap;
	int nextrate = 0;
	int ret = 0;

	//扣材料，并产出部件或材料
	if (produce.ispaycash)  //如果花钻，则读花钻的配置
	{
		const ComponentConfig::Produce & produceconfig = componentconfigwrap.GetProduce(produce.current_level, true);
		nextrate = produceconfig.nextrate();

		ret = CostAndProduce(uid, reason, produceconfig, msg);
	}
	else
	{
		const ComponentConfig::Produce & produceconfig = componentconfigwrap.GetProduce(produce.current_level, false);
		nextrate = produceconfig.nextrate();

		ret = CostAndProduce(uid, reason, produceconfig, msg);
	}

	if (ret)
	{
		return ret;
	}

	//随机是否进入下一级
	if (produce.current_level <= produce_max_level - 1)
	{
		int randomval = Math::GetRandomInt(rate_max_value);

		if (randomval < nextrate)  //进入到下一级
		{
			produce.current_level += 1;
		}
		else   //回到一级
		{
			produce.current_level = 1;
		}

		msg->set_level(produce.current_level);
	}
	else   //到达最大等级，则回到第一级
	{
		produce.current_level = 1;
		produce.ispaycash = 0;   //到达最高级之后，重置花钻的状态

		msg->set_level(produce.current_level);

		return ret_by_already_most;
	}

	return 0;
}

bool LogicCompProduceManager::IsPackageFull(unsigned uid)
{
	//判断部件背包是否已满
	int have = DataComponentManager::Instance()->GetNumOfDereliction(uid);

	if (have >= package_max_limit)
	{
		error_log("[IsPackageFull] package already full.uid=%u, have=%d,limit=%u", uid, have, package_max_limit);
		return true;
	}

	return false;
}

int LogicCompProduceManager::CostAndProduce(unsigned uid, string reason, const ComponentConfig::Produce & produceconfig,
		ProtoComponent::ProductCPP * msg)
{
	//扣材料
	DBCUserBaseWrap userwrap(uid);

	int count = produceconfig.cost();

	try
	{
		userwrap.CostMarket(count, reason);
	}
	catch(runtime_error & e)
	{
		return ret_by_not_enough;
	}

	//加载玩家的产出信息
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);

	//产生当前范围内的产出
	vector<unsigned> rates;

	for(int i = 0; i < produceconfig.product_size(); ++i)
	{
		unsigned rate = produceconfig.product(i).rate();
		rates.push_back(rate);
	}

	int target = 0;
	LogicCommonUtil::TurnLuckTable(rates, rates.size(), target);

	//选定产出的物品,材料或者部件
	if (produceconfig.product(target).has_material())  //产出材料
	{
		unsigned count = produceconfig.product(target).material();
		userwrap.AddMarket(count, reason);
		msg->set_material(count);
	}
	else  //产出部件
	{
		unsigned compid = produceconfig.product(target).compid();
		LogicComponentManager::Instance()->AddSingleComponent(uid, compid, reason, msg->mutable_component());
	}

	return 0;
}

int LogicCompProduceManager::FullMessage(unsigned uid, ProtoComponent::ProduceComponentCPP *msg)
{
	DataProduceComponent& produce = DataProduceComponentManager::Instance()->Get(uid);

	produce.SetMessage(msg);

	return 0;
}
