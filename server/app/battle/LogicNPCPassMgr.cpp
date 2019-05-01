/*
 * LogicNPCPassMgr.cpp
 *
 *  Created on: 2016-9-23
 *      Author: dawx62fac
 */

#include "LogicNPCPassMgr.h"

void LogicNPCPassMgr::PassSuccess(unsigned uid, unsigned id)
{
	try
	{
		NPCPassCfgWrap npcCfg;
		const PassSystemConfig::PassItem& npcCfgItem = npcCfg.Item(id);
		if (npcCfgItem.is_record_cnt())
		{
			DataNPCPassMgr::Instance()->PassSuccess(uid, id);

			//同步有记录的闯关次数
			int idx = DataNPCPassMgr::Instance()->GetIndex(uid, id);
			if (idx >= 0)
			{
				ProtoPush::PushNPCPassRecord* msg = new ProtoPush::PushNPCPassRecord;
				const DataNPCPass& npc_pass = DataNPCPassMgr::Instance()->m_data->data[idx];
				npc_pass.FullMessage(msg->mutable_item());

				LogicManager::Instance()->sendMsg(uid, msg);
			}
		}

		DBCUserBaseWrap(uid).SetNPCPassId(id);

		//接入英雄解锁接口
		LogicHeroManager::Instance()->UnlockVerify(uid, id);

		//同步数据
		OfflineResourceItem& resItem = LogicResourceManager::Instance()->Get(uid);
		LogicScienceMgr::Instance()->Sync(uid, resItem);

		//接入闯关任务接口
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_gate;
		LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);
	}
	catch (const std::exception& e)
	{
		error_log("uid:%u, id:%u. %s", uid, id, e.what());
	}
}

unsigned LogicNPCPassMgr::GetNPCPassCnt(unsigned uid, unsigned id)
{
	try
	{
		DBCUserBaseWrap user(uid);
		if (user.Obj().npc_pass < id)
		{
			return 0;
		}

		const PassSystemConfig::PassItem& npcCfgItem = NPCPassCfgWrap().Item(id);
		if (! npcCfgItem.is_record_cnt())
		{
			return 1;
		}

		int index = DataNPCPassMgr::Instance()->GetIndex(uid, id);
		return index >= 0 ? DataNPCPassMgr::Instance()->m_data->data[index].pass_cnt : 1;
	}
	catch (const std::exception& e)
	{
		(void)e;
	}

	return 0;
}

void LogicNPCPassMgr::FullMessage(unsigned uid, User::NPCPass* obj)
{
	std::vector<unsigned> vIndexs;
	DataNPCPassMgr::Instance()->GetIndexs(uid, vIndexs);

	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		const DataNPCPass& npc_pass = DataNPCPassMgr::Instance()->m_data->data[vIndexs[i]];
		npc_pass.FullMessage(obj->add_items());
	}
}

int LogicNPCPassMgr::Process(unsigned uid, ProtoPass::EnterFightReq* req)
{
	unsigned pass_id = req->id();

	NPCPassCfgWrap npcCfg;
	const PassSystemConfig::PassItem& npcCfgItem = npcCfg.Item(pass_id);
	DBCUserBaseWrap user(uid);

	if (user.Obj().level < npcCfgItem.unlock_lvl())
	{
		throw std::runtime_error("user_level_not_enough");
	}

	if (user.Obj().npc_pass + 1 < (int)pass_id)
	{
		throw std::runtime_error("need_to_unlock_pre_pass");
	}

	//消耗粮食
	user.CostUserResource(0, 0, npcCfgItem.cost_food(), 0, "npc_pass_op");

	//
	unsigned gate = pass_id;
	unsigned gid = npcCfgItem.terrain();
	std::vector<unsigned> npcs;
	for(int  i = 0;i < npcCfgItem.npcs_size(); i++)
	{
		npcs.push_back(npcCfgItem.npcs(i));
	}
	std::vector<HeroPropertyItemIndex> heros;
	for (int i = 0;i < req->hero_ids_size(); ++i)
	{
		heros.push_back(HeroPropertyItemIndex(uid, req->hero_ids(i)));
	}

	double diff;
	if(req->has_diff())
	{
		int di = req->diff();
		di = max(-10, min(10, di));
		diff = double(1) + double(di)/double(100);
	}
	else
		diff = double(1);

	int ret = WMI->CreateGateFight(uid, gate, gid, heros, npcs, diff);

	if (ret)
	{
		return ret;
	}

	//todo 闯关外部接口
	GateExternalInterface(uid);

	return 0;
}

int LogicNPCPassMgr::GateExternalInterface(unsigned uid)
{
	//todo 接入每日闯关任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_gate;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}
