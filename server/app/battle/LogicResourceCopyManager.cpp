#include "LogicResourceCopyManager.h"

int LogicResourceCopyManager::Process(unsigned uid, ProtoResourceCopy::OpenGateWindowReq *reqmsg, ProtoResourceCopy::OpenGateWindowResp * respmsg)
{
	OpenGateWindow(uid, respmsg);

	return 0;
}

int LogicResourceCopyManager::OpenGateWindow(unsigned uid, ProtoResourceCopy::OpenGateWindowResp * respmsg)
{
	FullMessage(uid, respmsg->mutable_rescopies());

	return 0;
}

int LogicResourceCopyManager::Process(unsigned uid, ProtoResourceCopy::BuyResourceCopyReq *reqmsg, ProtoResourceCopy::BuyResourceCopyResp * respmsg)
{
	unsigned id = reqmsg->id();

	BuyResourceCopy(uid, id, respmsg);

	return 0;
}

int LogicResourceCopyManager::BuyResourceCopy(unsigned uid, unsigned id, ProtoResourceCopy::BuyResourceCopyResp * respmsg)
{
	DataResourceCopy& rescopy = DataResourceCopyManager::Instance()->GetResourceCopy(uid, id);

	//读取配置
	const ResourceCopyConfig::ResourceCopy & resource_cfg = ResourceCopyConfigWrap().GetResourceCopyConfigById(id);
	//判断条件是否符合

	//判断vip等级
	DBCUserBaseWrap userwrap(uid);

	if (userwrap.Obj().viplevel < resource_cfg.viplevel())
	{
		error_log("vip level not match. uid=%u,need=%u,now=%u", uid, resource_cfg.viplevel(), userwrap.Obj().viplevel);
		throw runtime_error("viplevel_not_match");
	}

	//判断该关卡是否通过
	if (userwrap.Obj().npc_pass < resource_cfg.gateid())
	{
		error_log("gate not break. uid=%u,need=%u,now=%u", uid, resource_cfg.gateid(), userwrap.Obj().npc_pass);
		throw runtime_error("resource_copy_unlock");
	}

	//判断次数是否足够
	if (rescopy.buytimes >= resource_cfg.timeslimit())
	{
		error_log("times not enough. uid=%u", uid);
		throw runtime_error("times_not_enough");
	}

	unsigned index = rescopy.buytimes; //下标
	//扣钻
	int need_cash = resource_cfg.cash(index);
	userwrap.CostCash(need_cash, "Resource_Copy");

	//发放奖励
	LogicUserManager::Instance()->OpReward(userwrap, resource_cfg.reward(index), "Resource_Copy", respmsg->mutable_reward());

	//奖励发放后的后续
	rescopy.buytimes += 1;
	DataResourceCopyManager::Instance()->UpdateResourceCopy(rescopy);

	rescopy.SetMessage(respmsg->mutable_rescopy());
	respmsg->set_cash(userwrap.Obj().cash);

	return 0;
}

int LogicResourceCopyManager::FullMessage(unsigned uid, ProtoResourceCopy::ResourceCopyCPPAll* msg)
{
	vector<unsigned> indexs;
	DataResourceCopyManager::Instance()->GetResourceCopies(uid, indexs);

	for(unsigned i = 0; i < indexs.size(); ++i)
	{
		DataResourceCopy& rescopy = DataResourceCopyManager::Instance()->GetResourceCopy(indexs[i]);

		rescopy.SetMessage(msg->add_rescopy());
	}

	return 0;
}
