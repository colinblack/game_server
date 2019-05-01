#include "LogicFogGateManager.h"

int LogicFogGateManager::LoginCheck(unsigned uid)
{
	//检查部件数据是否加载进内存
	int ret = DataFogGateManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataFogGateManager::Instance()->LoadBuff(uid);
	}

	return ret;
}

int LogicFogGateManager::Process(unsigned uid, ProtoFogGate::StartFogGateReq* req)
{
	unsigned gateid = req->gateid();
	vector<unsigned> heros;

	for(int i = 0; i < req->heros_size(); ++i)
	{
		heros.push_back(req->heros(i));
	}

	//调用开始接口
	int ret = StartFogGate(uid, gateid, heros);
	return ret;
}

int LogicFogGateManager::StartFogGate(unsigned uid, unsigned gateid, vector<unsigned> & heros)
{
	//校验是否迷雾战
	bool isfog = IsFogGate(gateid);

	if (!isfog)
	{
		error_log("[StartFogGate] gate not fog gate. uid=%u,gateid=%u", uid, gateid);
		return 0;
	}

	//根据gateid，获取迷雾关卡内容
	//先判断关卡id是否存在于配置文件中

	const FogGateConfig::FogGate & fogcfg = FogGateConfigWrap().GetFogGate(gateid);

	//先判断是否存在该关卡数据，如果不存在，说明未挑战过
	bool isExist = DataFogGateManager::Instance()->IsFogGateExists(uid, gateid);

	if (!isExist)
	{
		//新建
		DataFogGate addgate;
		addgate.uid = uid;
		addgate.gateid = gateid;
		addgate.leftnpc = fogcfg.npcs_size();

		int ret = DataFogGateManager::Instance()->AddBuff(addgate);

		if (ret)
		{
			error_log("[StartFogGate] add new gate data error. uid=%u,gateid=%u,ret=%d", uid, gateid, ret);
			return ret;
		}
	}

	//判断是否已全部挑战
	DataFogGate& foggate = DataFogGateManager::Instance()->GetFogGate(uid, gateid);

	if (foggate.leftnpc < 1)
	{
		error_log("[StartFogGate] gate already over. uid=%u,gateid=%u", uid, gateid);
		throw runtime_error("gate_already_over");
	}

	//地形
	unsigned gid = fogcfg.terrain();

	//我方参战英雄
	vector<HeroPropertyItemIndex> heroPropertys;
	for (int i = 0;i < heros.size(); ++i)
	{
		heroPropertys.push_back(HeroPropertyItemIndex(uid, heros[i]));
	}

	//敌方npc,从剩下的npc开始，而不是将配置的npc全部填入
	vector<unsigned> npcs;

	int start_index = fogcfg.npcs_size() - foggate.leftnpc;  //起始索引

	for(int  i = 0;i < foggate.leftnpc; i++)
	{
		npcs.push_back(fogcfg.npcs(i+start_index));
	}

	double diff = 1;

	return WMI->CreateGateFight(uid, gateid, gid, heroPropertys, npcs, diff);
}

int LogicFogGateManager::EndFogGate(unsigned uid, unsigned gateid, unsigned leftnpc)
{
	//校验是否迷雾战
	bool isfog = IsFogGate(gateid);

	if (!isfog)
	{
		return 0;
	}

	try
	{
		DataFogGate& foggate = DataFogGateManager::Instance()->GetFogGate(uid, gateid);

		foggate.leftnpc = leftnpc;

		DataFogGateManager::Instance()->UpdateFogGate(foggate);

		//todo 推送剩余npc数量给前端
		ProtoFogGate::PushFogGateReq * pushfoggate = new ProtoFogGate::PushFogGateReq;
		pushfoggate->set_gateid(gateid);
		pushfoggate->set_leftnpc(leftnpc);

		LogicManager::Instance()->sendMsg(uid, pushfoggate);

		//todo 接入迷雾战任务
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_foggate_success;

		LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

		//todo 接入迷雾战成就
	    LogicAchievementManager::AchievementParam achievementparam;
		achievementparam.type = achievement_type_foggate;

		LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);
	}
	catch(runtime_error & e)
	{
		error_log("[EndFogGate] exception. uid=%u,reason=%s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}

bool LogicFogGateManager::IsHaveFogGateSuccess(unsigned uid)
{
	vector<unsigned> fogindexs;

	DataFogGateManager::Instance()->GetFogGates(uid, fogindexs);

	for(int i = 0; i < fogindexs.size(); ++i)
	{
		DataFogGate& foggate = DataFogGateManager::Instance()->GetFogGate(fogindexs[i]);

		//判断是否通过
		if (0 == foggate.leftnpc)
		{
			return true;
		}
	}

	return false;
}

unsigned LogicFogGateManager::GetFogGateSuccessNum(unsigned uid)
{
	unsigned num = 0;

	vector<unsigned> fogindexs;

	DataFogGateManager::Instance()->GetFogGates(uid, fogindexs);

	for(int i = 0; i < fogindexs.size(); ++i)
	{
		DataFogGate& foggate = DataFogGateManager::Instance()->GetFogGate(fogindexs[i]);

		//判断是否通过
		if (0 == foggate.leftnpc)
		{
			++num;
		}
	}

	return num;
}

bool LogicFogGateManager::IsFogGate(unsigned gateid)
{
	if (gateid >= e_gt_fog_min && gateid <= e_gt_fog_max)  //迷雾战的关卡范围
	{
		return true;
	}

	return false;
}

int LogicFogGateManager::FullMessage(unsigned uid, ProtoFogGate::FogGateCPPAll* msg)
{
	vector<unsigned> component_indexs;

	DataFogGateManager::Instance()->GetFogGates(uid, component_indexs);

	for(int i = 0; i < component_indexs.size(); ++i)
	{
		DataFogGate& foggate = DataFogGateManager::Instance()->GetFogGate(component_indexs[i]);
		foggate.SetMessage(msg->add_foggates());
	}

	return 0;
}

