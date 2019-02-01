/*
 * LogicChampionshipManager.cpp
 *
 *  Created on: 2018年10月9日
 *      Author: colin
 */

#include "LogicChampionshipManager.h"


int LogicChampionshipManager::Process(unsigned uid, ProtoChampionship::ProtoJoinInMatchReq* req, ProtoChampionship::ProtoJoinInMatchResp* resp)
{
	unsigned type = req->id();
	unsigned heroid	= req->heroid();
	if(type == 0 || type > CHAMPIONSHIP_TYPE)
	{
		error_log("param error, uid : %u", uid);
		throw runtime_error("param_error");
	}

	unsigned free = req->free();

	//比赛type不是1不能免费
	if(type > 1 && free == 0)
	{
		error_log("param error, uid: %u", uid);
		throw runtime_error("param_error");
	}

	//判断玩家段位是否满足要求
	auto& cfg = UserCfgWrap().GetChampionshipById(type);
	int coins = 0;
	if(free == 1)
	{
		unsigned grade = LogicUserGradeManager::Instance()->Get(uid).grade;
		if(grade < cfg.grade_limit())
		{
			error_log("grade is low, uid: %u", uid);
			throw runtime_error("grade_is_low");
		}
		coins = -cfg.cost().based().coin();
		LogicUserManager::Instance()->CommonProcess(uid, cfg.cost(), "championship_cost", resp->mutable_commons());
	}

	GameChampionship::Instance()->AddUser(uid, coins, type, heroid);

	return R_SUCCESS;
}


int LogicChampionshipManager::Process(unsigned uid, ProtoChampionship::ProtoChampionshipReq* req, ProtoChampionship::ProtoChampionshipResp* resp)
{
	unsigned battleid = req->battleid();
	if(!DGI->IsValid(battleid))
	{
		error_log("championship, battleid invalid, uid=%u, battleid=%u", uid, battleid);
		throw runtime_error("battleid_invalid");
	}

	auto gameBase = LogicBattleManager::Instance()->GetGames(e_battletype_championship);
	if(gameBase == nullptr)
	{
		error_log("get game failed, uid=%u", uid);
		throw runtime_error("get_game_failed");
	}

	auto gameChampionship = dynamic_cast<GameChampionship*>(gameBase);

	return gameBase->GameStart(uid, battleid, req->common(), resp);
}

void LogicChampionshipManager::OnTimer1()
{
	if(timer_cnt_++ < CHAMPIONSHIP_TIME_GAP)
		return;

	auto champoin = dynamic_cast<GameChampionship*>(LogicBattleManager::Instance()->GetGames(e_battletype_championship));
	champoin->Apply();
	champoin->GameProcess();

	timer_cnt_ = 0;
}

void LogicChampionshipManager::SetMessage(unsigned uid, unsigned battleid, unsigned heroid , ProtoChampionship::MatchUserInfoCPP* msg)
{
//	debug_log("--------------------  set message mid: %u, uid: %u ------------------ ", mid, uid);
	msg->set_uid(uid);
	msg->set_battleid(battleid);
	if(IsValidUid(uid))
	{
		auto& user = BaseManager::Instance()->Get(uid);
		msg->set_fig(user.fig);
		msg->set_name(user.name);

		auto& item = LogicUserGradeManager::Instance()->Get(uid);
		msg->set_grade(item.grade);
		msg->set_heroid(heroid);
	}
	else
	{
		auto& cfg = RoBotCfgWarp().GetChampionRobotById(uid);
		msg->set_name(cfg.name());
		msg->set_grade(cfg.grade());
		msg->set_heroid(cfg.npc(0).id());
	}
}



