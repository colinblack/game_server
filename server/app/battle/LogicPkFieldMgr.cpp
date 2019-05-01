/*
 * LogicPkFieldMgr.cpp
 *
 *  Created on: 2016-10-20
 *      Author: dawx62fac
 */

#include "LogicPkFieldMgr.h"

void LogicPkFieldMgr::CheckUser(const DBCUserBaseWrap& user)
{
	if (user.Obj().level < 40)
	{
		throw std::runtime_error("user_lvl_not_enough");
	}
}

void LogicPkFieldMgr::FullMessage(unsigned uid, int rank, ::ProtoPkField::PkUserItem* obj)
{
	try
	{
		do
		{
			if (uid <= 0) break;
			int index = ResourceManager::Instance()->GetIndex(uid);
			if (index < 0) break;

			OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[index];

			obj->set_uid(uid);
			obj->set_lvl(item.property[DemoOfflineProperty_u_level]);
			obj->set_name(item.name);
			obj->set_rank(rank);
			obj->set_head(item.fig);

			return ;

		} while(0);
	} catch(const std::exception& e)
	{
		error_log("uid: %u, rank:%d, %s", uid, rank, e.what());
	}

	obj->set_uid(0);
	obj->set_lvl(0);
	obj->set_name("");
	obj->set_head("");
	obj->set_rank(rank);
}

bool LogicPkFieldMgr::RefreshRival(int kingdom, int rank, ::google::protobuf::RepeatedPtrField< ::ProtoPkField::PkUserItem >* obj)
{
	int start = 0;
	int end = 0;
	if (rank >= 0 && rank <= LADDER_ENEMY)
	{
		LadderItem& myself_item = LadderManager::Instance()->GetLadderItem(kingdom, rank);
		int nIdx = 0;
		for (int i = 0;  i <=  LADDER_ENEMY; i++)
		{
			if (i == rank)
			{
				continue;
			}

			LadderItem& enemyItem = LadderManager::Instance()->GetLadderItem(kingdom, i);
			myself_item.enemy[nIdx] = i;

			if (obj)
			{
				FullMessage(enemyItem.uid, i + 1, obj->Add());
			}

			++nIdx;
		}
	}
	else if (rank > LADDER_ENEMY)
	{
		LadderItem& ladderItem = LadderManager::Instance()->GetLadderItem(kingdom, rank);

		//start = rank > 100 ? rank - 100 : 0;
		start = rank > 10 ? rank - 10 : 0;
		end = rank > 1 ? rank - 1 : 0;

		std::vector<int> vRanks;
		LogicCommonUtil::GetRandoms(start, end, LADDER_ENEMY, vRanks);

		ladderItem.ClearEnemy();
		for (size_t i = 0; i < vRanks.size(); ++i)
		{
			LadderItem& enemyItem = LadderManager::Instance()->GetLadderItem(kingdom, vRanks[i]);
			ladderItem.enemy[i] = vRanks[i];

			if (obj)
			{
				FullMessage(enemyItem.uid, vRanks[i] + 1, obj->Add());
			}
		}
	}
	else
	{
		if (obj)
		{
			std::vector<int> vRanks;
			//LogicCommonUtil::GetRandoms(LADDER_ITEM - 100, LADDER_ITEM - 1, LADDER_ENEMY, vRanks);
			LogicCommonUtil::GetRandoms(LADDER_ITEM - 10, LADDER_ITEM - 1, LADDER_ENEMY, vRanks);
			for (size_t i = 0; i < vRanks.size(); i++)
			{
				LadderItem& enemyItem = LadderManager::Instance()->GetLadderItem(kingdom, vRanks[i]);
				unsigned enemy_uid = enemyItem.uid;
				FullMessage(enemy_uid, vRanks[i] + 1, obj->Add());
			}
		}
	}

	return true;
}

bool LogicPkFieldMgr::RefreshRival(const DBCUserBaseWrap& user, ::google::protobuf::RepeatedPtrField< ::ProtoPkField::PkUserItem >* obj )
{
	int kingdom = user.Obj().kingdom;
	unsigned uid = user.Obj().uid;
	int rank = LadderManager::Instance()->GetRank(kingdom, uid);
	return RefreshRival(kingdom, rank, obj);
}

int LogicPkFieldMgr::Process(unsigned uid, ProtoPkField::PkFieldReq* req, ProtoPkField::PkFieldResp* resp)
{
	//
	DBCUserBaseWrap user(uid);
	int kingdom = user.Obj().kingdom;

	CheckUser(user);

	//前几名
	for (int i = 0; i < 3; ++i)
	{
		LadderItem& ladderItem = LadderManager::Instance()->GetLadderItem(kingdom, i);
		FullMessage(ladderItem.uid, i + 1, resp->add_winners());
	}

	int rank = LadderManager::Instance()->GetRank(kingdom, uid);
	if (rank >= 0)
	{
		LadderItem& ladderItem = LadderManager::Instance()->GetLadderItem(kingdom, rank);
		if (ladderItem.IsInitValue())
		{
			RefreshRival(kingdom, rank);
		}

		for (int i = 0; i < LADDER_ENEMY; ++i)
		{
			int enemy_rank = ladderItem.enemy[i];
			if (enemy_rank >= 0)
			{
				LadderItem& enemy = LadderManager::Instance()->GetLadderItem(kingdom, enemy_rank);
				FullMessage(enemy.uid, enemy_rank + 1, resp->add_defier());
			}
		}
	}
	else
	{
		std::vector<int> vRanks;
		//LogicCommonUtil::GetRandoms(LADDER_ITEM - 100, LADDER_ITEM - 1, LADDER_ENEMY, vRanks);
		LogicCommonUtil::GetRandoms(LADDER_ITEM - 10, LADDER_ITEM - 1, LADDER_ENEMY, vRanks);
		for (size_t i = 0; i < vRanks.size(); i++)
		{
			LadderItem& ladderItem = LadderManager::Instance()->GetLadderItem(kingdom, vRanks[i]);
			unsigned enemy_uid = ladderItem.uid;
			FullMessage(enemy_uid, vRanks[i] + 1, resp->add_defier());
		}
	}

	//todo 奖励倒计时
	if (resp)
	{
		resp->set_reward_rank(LadderManager::Instance()->GetReward(kingdom, uid) + 1);
		resp->set_rank(rank + 1);
		resp->set_challenge(user.Obj().ladder);
	}

	return 0;
}

void LogicPkFieldMgr::FinishPkSuccess(unsigned uid, unsigned rank)
{
	try
	{
		//官职战斗
		//unsigned params = department*1000 + 5000 + official;;
		if (rank >= e_gt_official_min && rank <= e_gt_official_max)
		{
			rank -= e_gt_official_min;
			unsigned department = rank / 1000;
			unsigned official = rank % 1000;

			LogicOfficialMgr::Instance()->FinishPkSuccess(uid, department, official);
		}
		else if(rank >= e_gt_city_min && rank <= e_gt_city_max)
			WMI->CityMasterWin(uid, rank - e_gt_city_min);
		else
		{
			DBCUserBaseWrap user(uid);
			int kingdom = user.Obj().kingdom;
			int self_rank = LadderManager::Instance()->GetRank(kingdom, uid);

			LadderItem& rivalItem = LadderManager::Instance()->GetLadderItem(kingdom, rank - 1);
			unsigned rival_uid = rivalItem.uid;
			if (rival_uid > 0)
			{
				if (self_rank >= 0)
				{
					LadderItem& item = LadderManager::Instance()->GetLadderItem(kingdom, self_rank);
					item.uid = rival_uid;
					RefreshRival(kingdom, self_rank);
				}
			}
			else
			{
				if (self_rank >= 0)
				{
					LadderItem& item = LadderManager::Instance()->GetLadderItem(kingdom, self_rank);
					item.uid = 0;
					item.ResetEnemy();
				}
			}

			rivalItem.uid = uid;
			RefreshRival(kingdom, rank - 1);

			//修改映射表
			LadderManager::Instance()->SetRankMap(kingdom, rival_uid, self_rank);
			LadderManager::Instance()->SetRankMap(kingdom, uid, rank - 1);
		}
	}
	catch(const std::exception& e)
	{
		error_log("uid: %u, %s", uid, e.what());
	}
}

int LogicPkFieldMgr::Process(unsigned uid, ProtoPkField::StartPkReq* req)
{
	DBCUserBaseWrap user(uid);
	CheckUser(user);

	//rank 的起始值为 1
	int rank = req->rank();
	if (rank < 1 || rank > LADDER_ITEM)
	{
		throw std::runtime_error("rank_params_error");
	}

	std::vector<HeroPropertyItemIndex> heros;
	for (int i = 0;i < req->hero_ids_size(); ++i)
	{
		heros.push_back(HeroPropertyItemIndex(uid, req->hero_ids(i)));
	}

	//竞技场次数不够，花费10钻石
	if (user.Obj().ladder > 0)
	{
		user.UserPkCnt(1);
	}
	else
	{
		user.CostCash(10, "enter_pk_field_op");
	}

	vector<HeroPropertyItemIndex> enemy;
	int kingdom = user.Obj().kingdom;
	LadderItem& item = LadderManager::Instance()->GetLadderItem(kingdom, rank - 1);
	if (item.uid > 0)
		HeroPropertyManager::Instance()->GetHeros(item.uid, enemy);
	if(enemy.empty())
		enemy.push_back(HeroPropertyItemIndex(e_gate_npc,LADDER_NPC_ID));

	 int ret = WMI->CreateLadderFight(uid, rank, heros, enemy);

	 if (ret)
	 {
		 return ret;
	 }

	 //todo 竞技场挑战外部接口
	 PKFieldExternalInterface(uid);

	 return 0;
}

int LogicPkFieldMgr::PKFieldExternalInterface(unsigned uid)
{
	//todo 接入每日竞技场任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_pkfield;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}

int LogicPkFieldMgr::Process(unsigned uid, ProtoPkField::EnterPkFieldReq* req, ProtoPkField::EnterPkFieldResp* resp)
{
	//rank 的起始值为 1
	int rank = req->rank();
	if (rank < 1 || rank > LADDER_ITEM)
	{
		throw std::runtime_error("rank_params_error");
	}

	DBCUserBaseWrap user(uid);
	int kingdom = user.Obj().kingdom;
	CheckUser(user);

	int myself_rank = LadderManager::Instance()->GetRank(kingdom, uid);
	if (myself_rank >= 0 && myself_rank + 1 < rank)
	{
		throw std::runtime_error("can_not_pk_lower_rank_user");
	}

	LadderItem& item = LadderManager::Instance()->GetLadderItem(kingdom, rank - 1);
	if (item.uid > 0)
	{
		//
		std::set<HeroPropertyItemIndex> heros;
		HeroPropertyManager::Instance()->GetHeros(item.uid, heros);
		for (std::set<HeroPropertyItemIndex>::const_iterator it = heros.begin();
				it != heros.end();
				++it)
		{
			try
			{

				HeroPropertyWrap hero(it->uid, it->id);
				int troops = hero.GetTotalTroops();
				int level = hero.GetHeroLevel();

				resp->add_hero_ids(it->id);
				resp->add_hero_lvl(level);
				resp->add_hero_troops(troops);
			}
			catch (const std::exception& e) {
				(void)e;
			}
		}
	}
	else
	{
		resp->add_hero_ids(LADDER_NPC_ID);
	}

	return R_SUCCESS;
}

int LogicPkFieldMgr::Process(unsigned uid, ProtoPkField::RefreshRivalReq* req, ProtoPkField::RefreshRivalResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUser(user);
	user.CostCash(10, "refresh_pk_field_rival");

	resp->set_cash(user.Obj().cash);
	RefreshRival(uid, resp->mutable_rival());

	return 0;
}

void LogicPkFieldMgr::OnHour()
{
	LadderManager::Instance()->OnHour();

	const std::map<unsigned, unsigned>& users = LadderManager::Instance()->GetRewardMap();
	//奖励列表不为空则发放奖励(1.进程重启；2每日19点会初始化奖励列表)；进程重启可能会延迟一个小时发放
	if (users.size() > 0)
	{
		unsigned now = Time::GetGlobalTime();
		for (std::map<unsigned, unsigned>::const_iterator it = users.begin();
				it  != users.end();
				++it)
		{
			unsigned uid = it->first;
			unsigned nRank = it->second + 1;

			if (uid > 0 && nRank > 0)
			{
				enum {
					RESOURCE_LIMIT = 1000000,
				};
				ProtoPkField::PkRewardResp* msg  = new ProtoPkField::PkRewardResp;
				try
				{
					DBCUserBaseWrap user(uid);
					const CommonGiftConfig::BaseReward& rewardCfg = PkFieldCfgWrap().GetReward(nRank);

					user.SetPkRewardTime(now);
					//当单项资源超过100w时，不奖励
					CommonGiftConfig::BaseReward real_reward;
					real_reward.CopyFrom(rewardCfg);
					if (user.Obj().coin >= RESOURCE_LIMIT)
					{
						real_reward.clear_coin();
					}

					if (user.Obj().iron >= RESOURCE_LIMIT)
					{
						real_reward.clear_iron();
					}

					if (user.Obj().coin < RESOURCE_LIMIT || user.Obj().iron < RESOURCE_LIMIT)
					{
						user.Reward(real_reward, msg->mutable_base(), "pk_field_reward");
					}
					/////////////////////////////////////////////////////////////////////

					msg->set_ladder_ts(now);
					LogicManager::Instance()->sendMsg(uid, msg);

					AddNotifyMsg(uid, nRank, rewardCfg);
				}
				catch(const std::exception& e)
				{
					error_log("uid: %u, %s", uid, e.what());
					if (msg)
					{
						delete msg;
						msg = NULL;
					}
				}
			}
		}
		//发完奖励，清理奖励表
		LadderManager::Instance()->OnDay();
	}

	return ;
}

void LogicPkFieldMgr::AddNotifyMsg(unsigned uid, unsigned rank, const CommonGiftConfig::BaseReward& reward)
{
	//！！！这里直接把奖励类型写死了
	Json::Value notifyval;
	notifyval["rank"] = rank;
	notifyval["coin"] = reward.coin();
	notifyval["iron"] = reward.iron();

	Json::FastWriter writer;
	string content  = writer.write(notifyval);

	NotifyItem notifyitem(uid, e_Notify_Arena);

	snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

	LogicNotifyManager::Instance()->AddNotify(notifyitem);
}

int LogicPkFieldMgr::Process(unsigned uid, ProtoPkField::PkRewardReq* req, ProtoPkField::PkRewardResp* resp)
{
	throw std::runtime_error("limit_interface");
#if 0
	DBCUserBaseWrap user(uid);
	CheckUser(user);
	unsigned now = Time::GetGlobalTime();

	int hour = LogicCommonUtil::GetHourByTime(now);
	if (hour < LADDER_REWARD_T)
	{
		throw std::runtime_error("not_get_reward_time");
	}

	if (Time::IsToday(user.Obj().ladder_ts))
	{
		throw std::runtime_error("already_get_pk_reward");
	}

	int kingdom = user.Obj().kingdom;
	int nRank = LadderManager::Instance()->GetReward(kingdom, uid);
	if (nRank < 0)
	{
		throw std::runtime_error("out_reward_rank");
	}

	const CommonGiftConfig::BaseReward& rewardCfg = PkFieldCfgWrap().GetReward(nRank + 1);

	user.SetPkRewardTime(now);
	user.Reward(rewardCfg, resp->mutable_base(), "pk_field_reward");

	resp->set_ladder_ts(user.Obj().ladder_ts);
#endif
	return 0;
}
