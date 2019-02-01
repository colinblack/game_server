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
	unsigned heroid = req->heroid();
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

	AddUser(uid, coins, type, heroid);

	return R_SUCCESS;
}


int LogicChampionshipManager::Process(unsigned uid, ProtoChampionship::ProtoStartBattleReq* req)
{
	unsigned battleid = req->battleid();

	if(!ChampionshipManager::Instance()->IsValid(battleid))
	{
		error_log("match is invalid, uid: %u", uid);
		throw runtime_error("match_is_invalid");
	}

	auto& data = ChampionshipManager::Instance()->GetData(battleid);
	data.UpdateReadyNum(uid);
	data.UpdateLastTs();
	//保存道具
	vector<unsigned> props(req->props().begin(), req->props().end());
	data.SetProp(uid, battleid, props);

	if(data.IsAllReady())
		StartChampionship(battleid);

	return R_SUCCESS;
}


int LogicChampionshipManager::StartChampionship(unsigned battleid)
{
	auto& data = ChampionshipManager::Instance()->GetData(battleid);

	vector<BattleDemoHero> att = data.att.GetBattleDemo();
	vector<BattleDemoItem> attItem = data.att.GetBattleItem();
	auto attCfg = data.att.GetConfigItem();


	vector<BattleDemoHero> def = data.def.GetBattleDemo();
	vector<BattleDemoItem> defItem = data.def.GetBattleItem();
	auto defCfg = data.def.GetConfigItem();


	//开始战斗
	BattleDemo battle(att, def, attItem, defItem, data.att.Level(), data.def.Level());
	data.SetBattleTime(battle.Turn()*CHAMPION_TURN_MAX_TIME + 10);

	if(IsValidUid(data.att.uid))
	{
		ProtoChampionship::BattleInfoCPP* resp = new ProtoChampionship::BattleInfoCPP;
		resp->mutable_battle()->CopyFrom(battle.msg());
		resp->set_attack(e_att);
		LUI->CommonProcess(data.att.uid, attCfg, "championship", resp->mutable_commons());
		LogicManager::Instance()->sendMsg(data.att.uid, resp);
	}

	if(IsValidUid(data.def.uid))
	{
		ProtoChampionship::BattleInfoCPP* resp = new ProtoChampionship::BattleInfoCPP;
		resp->mutable_battle()->CopyFrom(battle.msg());
		resp->set_attack(e_def);
		LUI->CommonProcess(data.def.uid, attCfg, "championship", resp->mutable_commons());
		LogicManager::Instance()->sendMsg(data.def.uid, resp);
	}

	if(battle.attackerWin())
		data.SetWinner(att_win);
	else
		data.SetWinner(def_win);

//	debug_log("start championship, battleid: %u, att: %u, def: %u, winner: %u", battleid, data.att.uid, data.def.uid, data.Winner());

	return R_SUCCESS;
}

int LogicChampionshipManager::InitUserItem(unsigned uid, unsigned battleid, unsigned heroid)
{
	auto& base = BaseManager::Instance()->Get(uid);
	//添加玩家到比赛
	int ret = ChampionshipManager::Instance()->AddUser(uid, battleid, base.level);
	if(ret != R_SUCCESS)
	{
		error_log("add user error, uid=%u, ret=%u", uid, ret);
		return ret;
	}
	//设置英雄属性和技能
	HeroAttrItem attr;
	attr.id = heroid;
	LogicHeroManager::Instance()->GetHeroAttr(uid, heroid, attr);
	LogicHeroManager::Instance()->GetSkill(uid, heroid, attr.skills);

	//debug_log(".... battleid: %u, uid: %u .....", battleid, uid);
	ret = ChampionshipManager::Instance()->SetHeroAttr(uid, battleid, attr);
	if(ret != R_SUCCESS)
	{
		error_log("set hero attribute failed, uid=%u, ret=%u", uid, ret);
		return ret;
	}


	return R_SUCCESS;
}

int LogicChampionshipManager::InitNpcItem(unsigned uid, unsigned battleid, unsigned heroid)
{
	auto& robotCfg = RoBotCfgWarp().GetChampionRobotById(uid);
	//添加玩家到比赛
	int ret = ChampionshipManager::Instance()->AddUser(uid, battleid, robotCfg.level());
	if(ret != R_SUCCESS)
	{
		error_log("add user error, uid=%u, ret=%u", uid, ret);
		return ret;
	}

	NpcCfgWarp npcCfg;
	for(auto& hero : robotCfg.npc())
	{
		unsigned heroid = hero.id();
		auto& npc   = npcCfg.GetNpcById(heroid);
		auto& lattr = npc.attr().levelattr(hero.level());
		auto& cattr = npc.attr();

		unsigned battlePow = 0;
		vector<SkillItem> skills;
		skills.reserve(e_skill_max);
		for(int j = 0; j < e_skill_max; ++j)
		{
			unsigned initWeight = LogicHeroManager::initWeight[j];

			auto& info = npc.skill(j).skillinfo(hero.level()-1);
			skills.push_back(SkillItem(j+1, j, info.hurtvalue(), info.multiple(), initWeight, 0));
			battlePow += info.fight_power();
		}

		battlePow += 100 + lattr.att()/2 + lattr.hp()/10 + lattr.def();
		HeroAttrItem attr(heroid, lattr.hp(), lattr.att(), lattr.def(), cattr.critstrike(), cattr.critresist(),
				cattr.dodge(), cattr.hit(), cattr.critrate()/(double)100, lattr.first(), battlePow, skills);

	//	debug_log(".... battleid: %u, uid: %u .....", battleid, uid);
		ChampionshipManager::Instance()->SetHeroAttr(uid, battleid,  attr);
	}

	//设置道具

	return R_SUCCESS;
}

int LogicChampionshipManager::AddGame(unsigned attUid, unsigned attHero, unsigned defUid, unsigned defHero, unsigned& battleid)
{
	battleid = ChampionshipManager::Instance()->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create championship failed");
		return R_ERROR;
	}

//	debug_log("battleid: %u, attuid: %u, defuid: %u", battleid, attUid, defUid);

	int ret = 0;
	if(IsValidUid(attUid))
		ret = InitUserItem(attUid, battleid, attHero);
	else
		ret = InitNpcItem(attUid, battleid, attHero);


	if(IsValidUid(defUid))
		ret = InitUserItem(defUid, battleid, defHero);
	else
		ret = InitNpcItem(defUid, battleid, defHero);

	if(ret != R_SUCCESS)
	{
		error_log("init user error");
		return R_ERROR;
	}

	auto& data = ChampionshipManager::Instance()->GetData(battleid);
	data.UpdateLastTs();

	return R_SUCCESS;
}

void LogicChampionshipManager::OnTimer1()
{
	if(timer_cnt_++ < CHAMPIONSHIP_TIME_GAP)
		return;

	Apply();
	GameProcess();

	timer_cnt_ = 0;
}


void LogicChampionshipManager::Turn(list<unsigned>& cur, list<unsigned>& next)
{
	for(auto it = cur.begin(); it != cur.end();)
	{
		unsigned mid = *it;
		try
		{
			if(Start(mid))
			{
				Ready(mid);
				it = cur.erase(it);
				if(&cur == &turn_3_)
					Over(mid);
				else
					next.push_back(mid);
			}
			else
			{
				++it;
			}
		}
		catch(std::exception& e)
		{
			error_log("championship: u% error, %s", mid);

			for(auto& battleid : match_start_[mid])
				ChampionshipManager::Instance()->GetData(battleid).clear();

			match_start_.erase(mid);
			it = cur.erase(it);
		}

	}
}



void LogicChampionshipManager::GameProcess()
{
	Turn(turn_1_, turn_2_);
	Turn(turn_2_, turn_3_);
	Turn(turn_3_, turn_3_);
}


int LogicChampionshipManager::Apply()
{
	while(!match_user_.empty())
	{
		auto& user = match_user_.front();
		match_map_[user.type].push_back(user);
		match_user_.pop_front();
	}

	for(auto& match : match_map_)
	{
		auto& players = match.second;
		unsigned type = match.first;
		if(!players.empty())
		{
			//TODO:添加比赛
			if(players.size() < CHAMPIONSHIP_PLAYER_NUM)
			{
				vector<int> robots = RandomRobots();
				while(players.size() < CHAMPIONSHIP_PLAYER_NUM)
				{
					players.push_back(ApplyRecord(robots.back(), 0, type, 0));
					robots.pop_back();
				}
			}

			unsigned mid = CreateMatch();
			if(mid == (unsigned)-1)
			{
				error_log("creat match error");
				throw runtime_error("creat_match_error");
			}

			list<unsigned> battles;
			unsigned battleid = 0;

			try
			{
				for(auto it = players.begin(); it != players.end();)
				{
					auto att = it;
					auto def = ++it;
					//debug_log("in players , uid=%u, uid=%u", att->uid, def->uid);

					if(R_ERROR == AddGame(att->uid, att->heroid, def->uid, def->heroid, battleid))
						throw runtime_error("add_game_failed");

					it = players.erase(att, ++def);
					battles.push_back(battleid);
					rewards_[mid] += (att->coins + def->coins);
				}
			}
			catch(std::exception& e)
			{
				error_log("%s", e.what());
				players.clear();
				for(auto& battleid : battles)
					ChampionshipManager::Instance()->GetData(battleid).clear();
				rewards_.erase(mid);

				return R_ERROR;
			}


			//加到开始比赛队列
			match_start_.insert({mid, battles});

			//加到第一轮比赛队列
			Ready(mid);
			turn_1_.push_back(mid);
//			debug_log("chapionship, mid: %u, turn1", mid);
		}

	}

	return R_SUCCESS;
}

int LogicChampionshipManager::Over(unsigned mid)
{
	if(match_start_[mid].size() != 1)
	{
		error_log("championship, logic error");
		throw runtime_error("championship_logic_error");
	}
	unsigned battleid = match_start_[mid].front();
	auto& data = ChampionshipManager::Instance()->GetData(battleid);

	unsigned winner = 0;
	if(data.Winner() == att_win)
		winner = data.att.uid;
	else
		winner = data.def.uid;

	if(IsValidUid(winner) && UMI->IsOnline(winner))
	{
		DataCommon::CommonItemsCPP* msg = new DataCommon::CommonItemsCPP;
		CommonGiftConfig::CommonModifyItem cfg;
		cfg.mutable_based()->set_coin(rewards_[mid]);

		//发送奖励
		LogicUserManager::Instance()->CommonProcess(winner, cfg, "championship_rewards", msg);
		LogicManager::Instance()->sendMsg(winner, msg);
	}

	match_start_.erase(mid);
	Clear(mid);
	ChampionshipManager::Instance()->Clear(battleid);

//	debug_log("------ championship: %u is over ----------", mid);
	return R_SUCCESS;
}


int LogicChampionshipManager::Ready(unsigned mid)
{
	//TODO: 广播玩家信息
	auto& battles = match_start_[mid];
	ProtoChampionship::MatchInfoCPP matchMsg;
	vector<unsigned> players;
	players.reserve(battles.size()*2);
	for(auto& battleid : battles)
	{
		auto& data = ChampionshipManager::Instance()->GetData(battleid);
		players.push_back(data.att.uid);
		LogicChampionshipManager::Instance()->SetMessage(data.att.uid, battleid, data.att.heros[0].id, matchMsg.add_players());
		players.push_back(data.def.uid);
		LogicChampionshipManager::Instance()->SetMessage(data.def.uid, battleid, data.def.heros[0].id, matchMsg.add_players());
	}

	for(auto& uid : players)
	{
		if(IsValidUid(uid))
		{
			ProtoChampionship::MatchInfoCPP* msg = new ProtoChampionship::MatchInfoCPP;
			msg->CopyFrom(matchMsg);
			LogicManager::Instance()->sendMsg(uid, msg);
		}
	}

	//TODO: 双方都是机器人先打
	RoBotCfgWarp robotCfg;
	for(auto it = battles.begin(); it != battles.end(); ++it)
	{
		unsigned battleid = *it;
		auto& data = ChampionshipManager::Instance()->GetData(battleid);
		unsigned attUid = data.att.uid;
		unsigned defUid = data.def.uid;
		if(!IsValidUid(attUid) && !IsValidUid(defUid))
		{
			StartChampionship(battleid);
		}
	}

	return R_SUCCESS;
}


int LogicChampionshipManager::Start(unsigned mid)
{
	bool isOver = false;
	auto& battles = match_start_[mid];

	//已经结束的比赛数
	int overCount = 0;
	for(auto it = battles.begin(); it != battles.end(); ++it)
	{
		unsigned battleid = *it;
		auto& data = ChampionshipManager::Instance()->GetData(battleid);
		//TODO: 超时的比赛,暂定为30s

		if(data.Winner() == 0)
		{
			if(Time::GetGlobalTime() - data.LastTs() > 30)
			{
				if(data.CurPlayer() == data.att.uid)
					data.SetWinner(att_win);
				else
					data.SetWinner(def_win);
			}
		}

		if(data.Winner() != 0)
		{
			//比赛是否结束
			if(data.BattleTime() > 0)
			{
				if((Time::GetGlobalTime() - data.LastTs()) > data.BattleTime())
					++overCount;
			}
			else
				++overCount;
		}
	}

//	debug_log("championship: %u, over battle: %u", mid, overCount);
	//所有的比赛都结束时，本轮比赛结束
	if(overCount == battles.size())
	{
		if(overCount > 1)
		{
			for(auto it = battles.begin(); it != battles.end();)
			{
				auto first = it;
				auto second = ++it;

				unsigned battleid = *first;
				auto& data1 = ChampionshipManager::Instance()->GetData(battleid);
				unsigned attUid = 0;
				unsigned attHero = 0;
				if(data1.Winner() == att_win)
				{
					attUid = data1.att.uid;
					attHero = data1.att.heros[0].id;
				}
				else
				{
					attUid = data1.def.uid;
					attHero = data1.def.heros[0].id;
				}

				battleid = *second;
				auto& data2 = ChampionshipManager::Instance()->GetData(battleid);
				unsigned defUid = 0;
				unsigned defHero = 0;

				if(data2.Winner() == att_win)
				{
					defUid = data2.att.uid;
					defHero = data2.att.heros[0].id;
				}
				else
				{
					defUid = data2.def.uid;
					defHero = data2.def.heros[0].id;
				}
				if(R_ERROR == AddGame(attUid, attHero, defUid, defHero, battleid))
					throw runtime_error("add_game_failed");

				*first = battleid;
				ChampionshipManager::Instance()->Clear(*second);

				it = battles.erase(second);
			}

		}
		isOver = true;


	}

	return isOver;
}


vector<int> LogicChampionshipManager::RandomRobots()
{
	vector<int> indexs;
	indexs.reserve(CHAMPIONSHIP_PER_ROBOTS);
	auto& cfg = RoBotCfgWarp().Championship();
	unsigned size = cfg.item_size();

	LogicCommonUtil::GetRandoms(0, size - 1, CHAMPIONSHIP_PER_ROBOTS, indexs);

	vector<int> res;
	res.reserve(CHAMPIONSHIP_PER_ROBOTS);
	for(auto& index : indexs)
	{
		res.push_back(cfg.item(index).id());
	}

	return res;
}


#if 0

void LogicChampionshipManager::OnTimer1()
{
	try
	{
		//正在进行中的比赛
		for(auto it = match_start_.begin(); it != match_start_.end();)
		{
			if(!ChampionshipManager::Instance()->IsValid(*it))
			{
				error_log("-------------- invalid mid: %u --------------- ", *it);
				throw runtime_error("invalid_mid");
			}

			auto& item = ChampionshipManager::Instance()->GetData(*it);
//			debug_log("-------------------- march start: mid %u, status %u, turn :%u, realnum: %u ------------------ ", *it, item.status, item.turn, ChampionshipManager::Instance()->RealPlayerNum(*it));
			if(item.status == match_status_ready)
			{
				Ready(item);
				++it;
			}
			else if(item.status  == match_status_start)
			{
				Start(item);
				++it;
			}
			else if(item.status == match_status_over)
			{
				Over(item);
				//清理数据
				Clear(*it);

				debug_log("---------------- match over mid: %u ----------------------", *it);
				it = match_start_.erase(it);
			}
			else
			{
				++it;
			}
		}

		//报名的玩家加入比赛
		while(!match_user_.empty())
		{
			auto& record = match_user_.front();
			Apply(record);
			match_user_.pop_front();
		}

		if(timer_cnt_++ != CHAMPIONSHIP_TIME_GAP)
			return;
		else
			timer_cnt_ = 0;


		//没有8个玩家的比赛没五秒添加一个机器人
		for(int i = 0; i < CHAMPIONSHIP_TYPE; ++i)
		{
			if(match_await_[i] == 0)
				continue;

			unsigned mid = match_await_[i];

			if(!ChampionshipManager::Instance()->IsValid(mid))
			{
				error_log("-------------- invalid mid: %u --------------- ", mid);
				throw runtime_error("invalid_mid");
			}

			auto& item = ChampionshipManager::Instance()->GetData(mid);
			if(item.player_num != CHAMPIONSHIP_PLAYER_NUM)
			{
				debug_log("-------------- add robot mid: %u, robot: %u --------------- ", mid, robots_[mid].size());
				//每5秒加入一个机器人
				if(!robots_[mid].empty())
				{
					ChampionshipManager::Instance()->AddPlayer(mid, robots_[mid].back());
					robots_[mid].pop_back();
				}
				if(item.player_num == CHAMPIONSHIP_PLAYER_NUM)
				{
					match_start_.insert(mid);
					match_await_[item.type-1] = 0;
					for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
						left_player_index_[mid][i] = item.player[i].uid;
					item.turn = 1;
				}
			}
			else
			{
				error_log("championship is wrong");
				throw runtime_error("championship_is_wrong");
			}

		}
	}
	catch(const exception& e)
	{
		error_log("-----  %s -----------", e.what());
		return;
	}
}

unsigned LogicChampionshipManager::Apply(ApplyRecord& record)
{
	unsigned uid  = record.uid;
	unsigned type = record.type;
	unsigned heroid = record.heroid;
	int coins = record.coins;

	unsigned& mid = match_await_[type-1];


	int ret = ChampionshipManager::Instance()->AddPlayer(mid, uid, heroid);
	if(R_ERROR == ret)
	{
		if(R_SUCCESS != ChampionshipManager::Instance()->AddMatch(uid, type, mid))
		{
			error_log("join match error, uid: %u, mid: %u", uid, mid);
			throw runtime_error("join_match_error");
		}
		RandomRobots(mid);

		ChampionshipManager::Instance()->AddPlayer(mid, uid, heroid);
	}


	if(ChampionshipManager::Instance()->IsFull(mid))
	{
		auto& item = ChampionshipManager::Instance()->GetData(mid);
		match_start_.insert(mid);
		for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
			left_player_index_[mid][i] = item.player[i].uid;
		item.turn = 1;
		match_await_[type-1] = 0;
	}
	else
	{
		auto& item = ChampionshipManager::Instance()->GetData(mid);
		item.coins += coins;
		players_[uid] = mid;
	}

//	debug_log("---- join match, mid: %u, uid: %u, num: %u ------------- ", mid, uid, ChampionshipManager::Instance()->GetData(mid).player_num);

	return R_SUCCESS;
}

unsigned LogicChampionshipManager::Ready(MatchItem &item)
{
	//处理还没打的比赛
	if(item.turn_cnt-- > 0)
		return R_SUCCESS;

	unsigned mid = item.mid;

	debug_log("---------------- ready match mid: %u, left: %u, turn: %u, realnum: %u ---------------", mid, left_player_index_[mid].size(), item.turn, ChampionshipManager::Instance()->RealPlayerNum(mid));

	//如果没有真玩家直接结束比赛
	if(ChampionshipManager::Instance()->RealPlayerNum(mid) == 0)
	{
		item.status= match_status_over;
		return R_SUCCESS;
	}

	vector<unsigned> players;
	//发送玩家信息
	ProtoChampionship::MatchInfoCPP matchMsg;
	if(item.turn == 1)
	{
		for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
		{
			SetMessage(item.player[i].uid, mid, matchMsg.add_players());
		}
	}
	else
	{
		for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
		{
			unsigned status = item.player[i].status;
			auto p = matchMsg.add_players();
			p->set_uid(item.player[i].uid);
			if(status == player_status_lose)
				p->set_status(0);
			else
				p->set_status(1);
		}
	}

	//广播玩家信息
	for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
	{
		unsigned sendUid = item.player[i].uid;
		if(IsValidUid(sendUid) && ChampionshipManager::Instance()->IsInMatch(mid, sendUid) && players_[sendUid] == mid)
		{
			ProtoChampionship::MatchInfoCPP* msg = new ProtoChampionship::MatchInfoCPP;
			msg->CopyFrom(matchMsg);
			LogicManager::Instance()->sendMsg(item.player[i].uid, msg);
		}
		debug_log("------------------ send user info, uid:  %u, status: %u ----------------- ", item.player[i].uid, item.player[i].status);
	}

	//ProtoChampionship::MatchInfoCPP matchMsg;
/*
	for(auto& e : left_player_index_[mid])
	{
		debug_log("------------------ include robot, idx: %u, uid:  %u ----------------- ", e.first, e.second);
	}
*/


	for(auto it = left_player_index_[mid].begin(); it != left_player_index_[mid].end(); advance(it, 2))
	{
		//双方都是机器人的比赛先打
		unsigned index1 = it->first;
		unsigned uid1 = it->second;
		++it;
		unsigned index2 = it->first;
		unsigned uid2 = it->second;
		--it;

		unsigned& status1 = item.player[index1].status;
		unsigned& status2 = item.player[index2].status;

		//两个都是机器人后台自动打
		if(!IsValidUid(uid1) && !IsValidUid(uid2))
		{
			bool isWin = LogicBattleManager::Instance()->StartChampionship(uid1, uid2);
			if(isWin)
			{
				status1 = player_status_win;
				status2 = player_status_lose;
			//	++it;
			//	it = left_player_index_[mid].erase(it);
			}
			else
			{
				status1  = player_status_lose;
				status2  = player_status_win;
			//	it = left_player_index_[mid].erase(it);
			//	++it;
			}

/*			auto* p1 = matchMsg.add_players();
			p1->set_uid(uid1);
			p1->set_status(status1);

			auto* p2 = matchMsg.add_players();
			p2->set_uid(uid2);
			p2->set_status(status2);*/
		}

	}

/*
	for(auto& e : left_player_index_[mid])
	{
		unsigned sendUid = e.second;
		if(IsValidUid(sendUid))
		{
			ProtoChampionship::MatchInfoCPP* msg = new ProtoChampionship::MatchInfoCPP;
			msg->CopyFrom(matchMsg);
			LogicManager::Instance()->sendMsg(sendUid, msg);
		}

		debug_log("----------------   send MatchUserInfoCPP, uid: %u,  idx:  %u, turn: %u ----------", e.second, e.first, item.turn);
	}
*/

	item.status = match_status_start;
	item.turn_cnt = 0;

	return R_SUCCESS;
}

unsigned LogicChampionshipManager::Start(MatchItem &item)
{
	//处理还没打的比赛
	if(item.turn_cnt++ < PER_TURN_START_TIME)
		return R_SUCCESS;

	unsigned mid = item.mid;
	debug_log("---------------- start match mid: %u, left: %u, turn: %u ---------------", mid, left_player_index_[mid].size(), item.turn);
//	ProtoChampionship::MatchInfoCPP matchMsg;
	for(auto it = left_player_index_[mid].begin(); it != left_player_index_[mid].end();)
	{
		unsigned index1 = it->first;
		unsigned uid1 = it->second;
		++it;
		unsigned index2 = it->first;
		unsigned uid2 = it->second;
		--it;

		unsigned& status1 = item.player[index1].status;
		unsigned& status2 = item.player[index2].status;

		bool win = false;
		if(status1 == player_status_win && status2 == player_status_lose)
		{
			++it;
			it = left_player_index_[mid].erase(it);
			win = true;
		}
		else if(status1 == player_status_lose && status2 == player_status_win)
		{
			it =  left_player_index_[mid].erase(it);
			++it;
			win = false;
		}
		else if(status1 == player_status_ready && status2 == player_status_not_ready)
		{
			++it;
			it = left_player_index_[mid].erase(it);
			win = true;
		}
		else if(status1 == player_status_not_ready && status2 == player_status_ready)
		{
			it =  left_player_index_[mid].erase(it);
			++it;
			win = false;
		}
		else if(status1 == player_status_not_ready && status2 == player_status_not_ready)
		{
			++it;
			it = left_player_index_[mid].erase(it);
			win = true;
		}
		else
		{
			item.status == match_status_over;
			error_log("status error mid: %u, uid1: %u, status: %u, uid2: %u, status: %u", mid, uid1, status1, uid2, status2);
			advance(it, 2);
		}

		//没有进行战斗的玩家只发送结果
		if((status1 == player_status_not_ready && status2 == player_status_ready) ||
				(status1 == player_status_ready && status2 == player_status_not_ready))
		{

			ProtoChampionship::BattleInfoCPP* msg = new ProtoChampionship::BattleInfoCPP;
			msg->set_attack(1);
			if(status1 == player_status_not_ready)
				LogicManager::Instance()->sendMsg(uid2, msg);
			if(status2 == player_status_not_ready)
				LogicManager::Instance()->sendMsg(uid1, msg);
		}

	//	debug_log("---------------- start match mid: %u, uid1: %u, status1 = %u, uid2 = %u, status2 = %u ---------------", mid, uid1, status1, uid2, status2);
		if(win)
		{
			players_.erase(uid2);
			ChampionshipManager::Instance()->DelRealUser(mid, uid2);
			status2 = player_status_lose;
		}
		else
		{
			players_.erase(uid1);
			ChampionshipManager::Instance()->DelRealUser(mid, uid1);
			status1 = player_status_lose;
		}


/*		auto p1 = matchMsg.add_players();
		p1->set_uid(uid1);
		p1->set_status((unsigned)win);
		auto p2 = matchMsg.add_players();
		p2->set_uid(uid2);
		p2->set_status((unsigned)!win);*/
	}


	for(auto& e : left_player_index_[mid])
	{
		unsigned sendUid = e.second;
/*
		//广播消息
		if(IsValidUid(sendUid) && UMI->IsOnline(sendUid))
		{
			ProtoChampionship::MatchInfoCPP* msg = new ProtoChampionship::MatchInfoCPP;
			msg->CopyFrom(matchMsg);
			LogicManager::Instance()->sendMsg(sendUid, msg);
		}
*/
		//设置状态
		if(IsValidUid(sendUid))
			item.player[e.first].status = player_status_not_ready;
		else
			item.player[e.first].status = player_status_ready;
	}


	item.turn++;
	if(item.turn == CHAMPIONSHIP_MAX_TURN)
	{
		item.status = match_status_over;
	}
	else
	{
		item.status = match_status_ready;
		item.turn_cnt = PER_TURN_BATTLE_TIME;
	}


	return R_SUCCESS;
}


unsigned LogicChampionshipManager::Over(MatchItem & item)
{
	unsigned mid = item.mid;
	if(ChampionshipManager::Instance()->RealPlayerNum(mid) != 0)
	{
		unsigned index = left_player_index_[mid].begin()->first;
		unsigned uid  = item.player[index].uid;
		if(IsValidUid(uid))
		{
			DataCommon::CommonItemsCPP* msg = new DataCommon::CommonItemsCPP;
			CommonGiftConfig::CommonModifyItem cfg;
			cfg.mutable_based()->set_coin(item.coins);

			//发送奖励
			LogicUserManager::Instance()->CommonProcess(uid, cfg, "championship_rewards", msg);
			LogicManager::Instance()->sendMsg(uid, msg);
		}
	}

	return R_SUCCESS;
}

#endif

#if 0
int LogicChampionshipManager::StartBattle(unsigned uid, unsigned battleid, vector<unsigned>& props)
{

		auto& data = ChampionshipManager::Instance()->GetData(battleid);

		data.SetProp(uid, battleid, props);
		data.IncReadyNum();

		bool attWin = false;

		if(data.IsAllReady())
		{

			vector<unsigned> props1;
			vector<unsigned> props2;

			CommonGiftConfig::CommonModifyItem cfg1;
			CommonGiftConfig::CommonModifyItem cfg2;
			ProtoBattleDemo::ProtoBattleDemo  battleInfo;


			if(IsValidUid(uid) && IsValidUid(othUid))
			{
				attWin = LogicBattleManager::Instance()->StartChampionship(uid, othUid, hero1, hero2, props1, props2, cfg1, cfg2, battleInfo);
			}
			else
			{
				if(IsValidUid(uid) && !IsValidUid(othUid))
				{
					attWin = LogicBattleManager::Instance()->StartChampionship(uid, othUid, hero1, props1, cfg1, battleInfo);
				}
				else if(!IsValidUid(uid) && IsValidUid(othUid))
				{
					attWin = LogicBattleManager::Instance()->StartChampionship(othUid, uid, hero2, props2, cfg2, battleInfo);
				}
				else
				{
					error_log("championship battle error, uid: %u", uid);
					throw runtime_error("championship_battle_error");
				}
			}

			//player1
			if(IsValidUid(uid))
			{
				if(match.player[index1].status == player_status_ready)
				{
					ProtoChampionship::BattleInfoCPP* resp1 = new ProtoChampionship::BattleInfoCPP;
					LogicUserManager::Instance()->CommonProcess(uid, cfg1, "championship", resp1->mutable_commons());
					resp1->mutable_battle()->CopyFrom(battleInfo);
					resp1->set_attack(1);
					LogicManager::Instance()->sendMsg(uid, resp1);
				}

			}

			//player2
			if(IsValidUid(othUid))
			{
				if(match.player[index2].status == player_status_ready)
				{
					ProtoChampionship::BattleInfoCPP* resp2 = new ProtoChampionship::BattleInfoCPP;
					LogicUserManager::Instance()->CommonProcess(othUid, cfg2, "championship", resp2->mutable_commons());
					resp2->mutable_battle()->CopyFrom(battleInfo);
					resp2->set_attack(0);
					LogicManager::Instance()->sendMsg(othUid, resp2);
				}
			}
			debug_log("--- start battle uid: %u, status: %u, othUid: %u, status: %u, left: %u, win: %d ---", uid, match.player[index1].status, othUid, match.player[index2].status, left_player_index_[mid].size(), attWin);


			if(attWin)
			{
				match.player[index1].status = player_status_win;
				match.player[index2].status = player_status_lose;
				ChampionshipManager::Instance()->DelRealUser(mid, othUid);
			}
			else
			{
				match.player[index1].status = player_status_lose;
				match.player[index2].status = player_status_win;
				ChampionshipManager::Instance()->DelRealUser(mid, uid);
			}


		}


	return R_SUCCESS;
}
#endif


#if 0

PlayerItem& LogicChampionshipManager::GetData(unsigned uid, unsigned mid)
{
	int index = ChampionshipManager::Instance()->GetPlayerIndex(mid, uid);
	if(index < 0)
	{
		error_log("get data error, uid: %u, mid: %u", uid, mid);
		throw runtime_error("get_data_error");
	}

	return ChampionshipManager::Instance()->GetData(mid).player[index];
}

void LogicChampionshipManager::RandomRobots(unsigned mid)
{
	robots_[mid].clear();
	auto& cfg = RoBotCfgWarp().Championship();
	unsigned size = cfg.item_size();
	vector<int> res;
	LogicCommonUtil::GetRandoms(0, size - 1, CHAMPIONSHIP_PER_ROBOTS, res);

	for(auto& e : res)
	{
		robots_[mid].push_back(cfg.item(e).id());
	}

}

void LogicChampionshipManager::Clear(unsigned mid)
{
	try
	{
		left_player_index_.erase(mid);
		robots_.erase(mid);
		auto& item = ChampionshipManager::Instance()->GetData(mid);
		for(int i = 0; i < CHAMPIONSHIP_PLAYER_NUM; ++i)
		{
			debug_log(" ---------- erase user uid: %u -------- ", item.player[i].uid);
			players_.erase(item.player[i].uid);
		}


		ChampionshipManager::Instance()->DelItem(mid);
	}
	catch(const exception& e)
	{
		error_log("mid: %u, %s", mid, e.what());
	}

}
#endif


void LogicChampionshipManager::SetMessage(unsigned uid, unsigned battleid, unsigned heroid , ProtoChampionship::MatchUserInfoCPP* msg)
{
//	debug_log("--------------------  set message battleid: %u, uid: %u ------------------ ", battleid, uid);
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

/*void LogicChampionshipManager::LeaveMatch(unsigned uid)
{
	players_.erase(uid);
}*/



