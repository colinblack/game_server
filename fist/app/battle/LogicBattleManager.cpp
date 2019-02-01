/*
 * LogicBattleManager.cpp
 *
 *  Created on: 2018年7月12日
 *      Author: colin
 */

#include "LogicBattleManager.h"


void LogicBattleManager::GetFormation(unsigned uid, vector<unsigned>& heros)
{
	heros.clear();
	heros = formation_[uid];
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::SetFormationReq* req, ProtoBattle::SetFormationResp* resps)
{
	if(req->heroid_size() > MAX_FORMATION_HERO)
	{
		error_log("hero number is wrong uid=%u", uid);
		throw runtime_error("hero_number_is_wrong");
	}

	vector<unsigned> heros;
	for(auto& value: req->heroid())
	{

		heros.push_back(value);
	}
	//保存阵型
	formation_[uid].clear();
	formation_[uid] = heros;
	set<unsigned> heroid(heros.begin(), heros.end());
	if(CombineCfgWrap().IsFormat(heroid))
	{
		auto& cfg = CombineCfgWrap().GetCombineByHeroId(heroid);
		for(int i= 0; i < cfg.list_size(); ++i)
		{
			auto& attr = cfg.list(i);
			unsigned cnt = 0;
			if(attr.limit().has_star())
			{
				unsigned star = attr.limit().star();
				for(auto& value : heroid)
				{
					DBCHeroWrap hero(uid, value);
					if(0 != (hero.Obj().star & (1<<star)))
						++cnt;
				}
				if(cnt == heroid.size())
					DBCHeroWrap::SetCombineLimit(i);
			}
		}

	}

	return 0;
}

//pve
int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoPveBattleReq* req, ProtoBattle::ProtoPveBattleResp* resp)
{
	DBCUserBaseWrap userwrap(uid);
	unsigned stage = req->common().stageid();


	unsigned stageIdx =  ConfigManager::Instance()->stage_index[stage]+1;
	//关卡是否解锁
	if(stageIdx > (userwrap.GetStages()+1))
	{
		error_log("stage is unlock uid=%u, stageIdx: %u, pass: %u, stage: %u", uid, stageIdx, userwrap.GetStages(), stage);
		throw runtime_error("stage_is_unlock");
	}

	if(stage > NPC_MAX_STAGE)
	{
		error_log("stage bigger than max =%u, stage=%u", uid, stage);
		throw runtime_error("param_error");
	}

	try
	{
		CommonGiftConfig::CommonModifyItem cfg;
		ProtoBattleDemo::ProtoBattleDemo msg;
		bool attackerWin = StartBattle(uid, e_battletype_pve, req->mutable_common(), cfg, msg);
		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);

		//结算
		PveAccount(uid, attackerWin, stage, formation_[uid], cfg, resp);
		//更新关卡
		if(attackerWin)
			userwrap.UpdateStages(stageIdx);

		formation_[uid].clear();
		DBCHeroWrap::ResetCombineLimit();
	}
	catch(const std::exception &e)
	{
		error_log("pve: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoMatchReq* req,  ProtoBattle::ProtoMatchResp* resp)
{
	//随机匹配玩家
	UserGradeItem& item = LogicUserGradeManager::Instance()->Get(uid);


	//真玩家+假玩家
	unsigned defUid = 0;
	unsigned idx = 0;
	auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(item.grade);

	if(UserGradeManager::Instance()->GetMap().size() < GRADE_BATTLE_USER)
	{
		defUid = UserGradeManager::Instance()->GetUserRandom(uid, item.grade, cfg.item_size());
		if(!IsValidUid(defUid))
		{
			idx = defUid;
			defUid = 0;
		}
	}
	else
	{
		defUid = LogicUserGradeManager::Instance()->Match(uid, item.grade);
	}


	//没有匹配到使用真玩家
	if(defUid == 0)
	{
		resp->set_name(cfg.item(idx).name());
		resp->set_grade(item.grade);
		auto& npc = cfg.item(idx).npc();
		for(int i = 0; i < npc.size(); ++i)
		{
			resp->add_heroid(npc.Get(i).id());
		}
		grade_robot_[uid] = idx;

	}
	else
	{
		//加载玩家数据
		OffUserSaveControl  offuserCtl(defUid);
		OfflineResourceItem& defItem = LogicResourceManager::Instance()->Get(defUid);

		enemy_[uid] = defItem;
		resp->set_fig(string(defItem.fig));
		resp->set_name(string(defItem.name));
		resp->set_grade(item.grade);

		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			if(0 == defItem.heros[i].id)
				continue;
			resp->add_heroid(defItem.heros[i].id);
		}
	}

	return 0;
}


//排位赛
int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoGradeBattleReq* req, ProtoBattle::ProtoGradeBattleResp* resp)
{
	try
	{
		CommonGiftConfig::CommonModifyItem cfg;
		ProtoBattleDemo::ProtoBattleDemo msg;

		bool attackerWin = false;
		if(enemy_.count(uid) != 0)
		{
			attackerWin = StartBattle(uid, e_battletype_grade, req->mutable_common(), cfg, msg);
			enemy_.erase(uid);
		}
		else
		{
			attackerWin = StartRobotBattle(uid, e_battletype_grade_robot, req->mutable_common(), cfg, msg);
			grade_robot_.erase(uid);
		}

		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);
		LogicUserManager::Instance()->CommonProcess(uid,cfg,"grade_battle",resp->mutable_commons());

		//更新段位信息
		UserGradeItem& gradeItem = LogicUserGradeManager::Instance()->Get(uid);
		if(attackerWin)
		{
			LogicUserGradeManager::Instance()->UpdateScore(uid, GRADE_PER_SCORE);
			gradeItem.win++;
			int idx = LogicUserGradeManager::Instance()->GetWinIdex(gradeItem.win);
			if(-1 != idx && !gradeItem.win_record[idx])
			{
				ProtoPush::PushWinstreak* msg = new ProtoPush::PushWinstreak;
				msg->set_count(gradeItem.win);
				//推送连胜消息
				LogicManager::Instance()->sendMsg(uid, msg);
				gradeItem.win_record[idx] = true;
			}
		}
		else
		{
			gradeItem.win = 0;
		}
		resp->set_grade(gradeItem.grade);
		resp->set_score(gradeItem.score);
		resp->set_dailyscore(gradeItem.daily_score);
		formation_[uid].clear();
	}
	catch(const exception &e)
	{
		error_log("grade: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}


	return 0;
}


int LogicBattleManager::Process(unsigned uid, ProtoBattle::UpgradeRewardReq* req, ProtoBattle::UpgradeRewardResp* resp)
{
	unsigned grade = req->grade();
	if(grade < 1 || grade > USER_GRADE_INDEX)
	{
		error_log("param error : %u", uid);
		throw runtime_error("param_error");
	}

	auto& gradeCfg = GradeCfgWarp().Grade();
	auto& reward = gradeCfg.upgrade(grade-1);

	LogicUserManager::Instance()->CommonProcess(uid,reward.reward(),"upgrade_reward",resp->mutable_rewards());

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::DailyRewardReq* req, ProtoBattle::DailRewardResp* resp)
{

	UserGradeItem& gradeItem = LogicUserGradeManager::Instance()->Get(uid);
	if(Time::IsToday(gradeItem.daily_reward_ts))
	{
		error_log("logic error : %u", uid);
		throw runtime_error("logic_error");
	}
	unsigned grade = gradeItem.grade;
	auto& gradeCfg = GradeCfgWarp().Grade();
	auto rewardCfg = gradeCfg.daily(grade-1).reward();

	unsigned factor = GradeCfgWarp().Grade().factor(grade-1).value();
	rewardCfg.mutable_based()->set_coin(factor * rewardCfg.based().coin());


	gradeItem.daily_reward_ts = Time::GetGlobalTime();
	LogicUserManager::Instance()->CommonProcess(uid, rewardCfg,"daily_reward",resp->mutable_rewards());

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::WinStreakRewardReq* req, ProtoBattle::WinStreakRewardResp* resp)
{
	unsigned count = req->count();
	int idx =  LogicUserGradeManager::Instance()->GetWinIdex(count);
	if(-1 == idx)
	{
		error_log("param error : %u", uid);
		throw runtime_error("param_error");
	}

	UserGradeItem& gradeItem = LogicUserGradeManager::Instance()->Get(uid);
	unsigned grade = gradeItem.grade;
	unsigned factor =  GradeCfgWarp().Grade().factor(grade-1).value();


	auto rewardCfg = GradeCfgWarp().Grade().win(idx).reward();
	rewardCfg.mutable_based()->set_coin(rewardCfg.based().coin() * factor);

	LogicUserManager::Instance()->CommonProcess(uid,rewardCfg,"winstreak_reward",resp->mutable_rewards());
	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::UpgradeShareRewardReq* req, ProtoBattle::UpgradeShareRewardResp* resp)
{
	unsigned grade = req->grade();
	if(grade < 1 || grade > USER_GRADE_INDEX)
	{
		error_log("param error : %u", uid);
		throw runtime_error("param_error");
	}

	auto& gradeCfg = GradeCfgWarp().Grade();
	auto reward = gradeCfg.upgrade(grade-1).reward();
	const unsigned multiple = 2;
	unsigned cash = reward.based().cash() * multiple;
	auto *p = reward.mutable_based();
	p->set_cash(cash);

	LogicUserManager::Instance()->CommonProcess(uid,reward,"upgrade_share_reward",resp->mutable_rewards());

	return 0;
}


int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRefreshReq* req, ProtoBattle::ProtoRefreshResp* resp)
{
	//刷新随机玩家
	unsigned enemyUid = RefreshUser(uid);

	if(0 != enemyUid)
	{
		OfflineResourceItem& defItem = LogicResourceManager::Instance()->Get(enemyUid);
		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			if(0 == defItem.heros[i].id)
				continue;
			auto p = resp->mutable_hero();
			auto attr = p->Add();
			attr->set_heroid(defItem.heros[i].id);
			attr->set_att(defItem.heros[i].attr.att);
			attr->set_hp(defItem.heros[i].attr.hp);
			attr->set_def(defItem.heros[i].attr.def);
		}
		resp->set_name(defItem.name);
		resp->set_fig(defItem.fig);
		random_[uid] = defItem;
	}
	else
	{
		//随机获取npc
		unsigned size = RandomCfgWarp().UserSize();
		int idx = Math::GetRandomInt(size);
		const Random::UserInfo& cfg = RandomCfgWarp().User(idx);
		DataBase& base = BaseManager::Instance()->Get(uid);
		unsigned npcLevel = base.level;

		NpcCfgWarp npcCfg;
		for(int i = 0; i < cfg.npcid_size(); ++i)
		{
			const NpcConfig::NpcInfo&  npc = npcCfg.GetNpcById(cfg.npcid(i));
			auto p = resp->mutable_hero();
			auto attr = p->Add();
			attr->set_heroid(npc.id());
			attr->set_att(npc.attr().levelattr(npcLevel-1).att());
			attr->set_hp(npc.attr().levelattr(npcLevel-1).hp());
			attr->set_def(npc.attr().levelattr(npcLevel-1).def());
		}
		resp->set_name(cfg.name());
		npc_[uid] = idx;
	}

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoPost* msg)
{
	const string& info = msg->info();

	RandomUserItem postItem;

	postItem.uid = uid;
	postItem.type = e_Post_randomUser;
	postItem.ts = Time::GetGlobalTime();
	memcpy(postItem.content, info.c_str(), sizeof(postItem.content));

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRandomUserReq* req, ProtoBattle::ProtoRandomUserResp* resp)
{
	try
	{
		CommonGiftConfig::CommonModifyItem cfg;
		ProtoBattleDemo::ProtoBattleDemo msg;
		bool attackerWin = StartBattle(uid, e_battletype_random, req->mutable_common(), cfg, msg);

		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);
		unsigned enemyUid = (random_.count(uid) == 0 ? 0 : random_[uid].uid);
		if(attackerWin)
			RandomUserReward(uid, enemyUid, cfg);

		revenge_[enemyUid] = uid;
		random_.erase(uid);
		npc_.erase(uid);
		formation_[uid].clear();

		LogicUserManager::Instance()->CommonProcess(uid,cfg,"random_battle",resp->mutable_commons());

	}
	catch(const exception& e)
	{
		error_log("random battle: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRevengeReq* req, ProtoBattle::ProtoRevengeResp* resp)
{
	try
	{
		CommonGiftConfig::CommonModifyItem cfg;
		ProtoBattleDemo::ProtoBattleDemo msg;
		bool attackerWin = StartBattle(uid, e_battletype_random, req->mutable_common(), cfg, msg);
		unsigned enemyUid = req->enemyid();
		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);
		if(attackerWin)
			RandomUserReward(uid, enemyUid, cfg);
		revenge_.erase(uid);
		formation_[uid].clear();
		LogicUserManager::Instance()->CommonProcess(uid,cfg,"revenge_battle",resp->mutable_commons());
	}
	catch(const exception& e)
	{
		error_log("revenge battle: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}

	return 0;
}


int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoFriendBattleReq* req, ProtoBattle::ProtoFriendBattleResp* resp)
{
	try
	{
		unsigned otherId = req->otherid();
		//对方uid是否有效
		if(!IsValidUid(otherId))
		{
			error_log("othuid is invalid. uid=%u,othuid=%u", uid, otherId);
			throw runtime_error("param_uid_invalid");
		}

		//好友每天只能挑战一次
		DBCFriendWrap data(uid, otherId);
		if(DataConcernManager::Instance()->IsExistItem(uid, otherId))
		{
			if(!data.UpdateBattleTs())
				throw runtime_error("battleTs_error");
		}

		friend_[uid] = LogicResourceManager::Instance()->Get(otherId);
		CommonGiftConfig::CommonModifyItem cfg;
		ProtoBattleDemo::ProtoBattleDemo msg;
		bool attackerWin = StartBattle(uid, e_battletype_friend, req->mutable_common(), cfg, msg);
		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);
		FriendBattleReward(uid, attackerWin,formation_[uid], cfg, resp);
		LogicUserManager::Instance()->CommonProcess(uid,cfg,"friend_battle",resp->mutable_commons());
		data.UpdateBattle(attackerWin ? e_friendbattle_win : e_friendbattle_lose);
		formation_[uid].clear();
		friend_.erase(uid);
	}
	catch(const exception& e)
	{
		error_log("friend battle: %s", e.what());
		throw std::runtime_error(e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq* req)
{
	unsigned othUid = req->othuid();
	unsigned martialGrade = req->mymartialgrade();
	unsigned othMartialGrade = req->othmartialgrade();

	if(!IsValidMartialGrade(martialGrade) ||
			!IsValidMartialGrade(othMartialGrade))
	{
		error_log("param error %u", uid);
		throw runtime_error("param_error");
	}

	DBCUserBaseWrap user(uid);
	if(!Time::IsToday(user.Obj().daily_battle_ts))
	{
		user.Obj().daily_battle_count = 0;
		user.Obj().daily_battle_ts = Time::GetGlobalTime();
		user.Save();
	}


	if(user.Obj().daily_battle_count == MARTIAL_BATTLE_DAILY_MAX_COUNT)
	{
		error_log("daily battle count max %u", uid);
		throw runtime_error("daily_battle_count_max");
	}

	if(CMI->IsNeedConnectByUID(othUid))
	{
		vector<unsigned> vIndex;
		vector<unsigned> heros;

		DataMartialHeroManager::Instance()->GetIndexs(uid, vIndex);
		for(auto& e: vIndex)
		{
			DBCMartialHeroWrap hero(e);
			if(hero.Obj().id / 10 == martialGrade)
			{
				heros.push_back(hero.Obj().heroid);
			}
		}

		if(heros.empty())
		{
			error_log("no hero: %u", uid);
			throw runtime_error("no_hero");
		}

		ProtoBattle::ProtoCSMartialClubBattleReq* msg = new ProtoBattle::ProtoCSMartialClubBattleReq;
		msg->set_myuid(uid);
		msg->set_level(user.Obj().level);
		msg->set_othuid(othUid);
		msg->set_othmartialgrade(othMartialGrade);
		msg->set_mymartialgrade(martialGrade);
		msg->set_myname(user.Obj().name);
		msg->set_myfig(user.Obj().fig);

		msg->mutable_common()->CopyFrom(req->common());
		try
		{
			for(auto &e : heros)
			{
				DBCHeroWrap hero(uid, e);
				hero.FullMessage(msg->add_hero());
			}
		}
		catch(const exception& e)
		{
			delete msg;
			error_log("martial battle error uid: %u, %s", uid, e.what());
			throw runtime_error("martial_battle_error");
		}

		return ProtoManager::BattleConnectNoReplyByUID(othUid, msg);
	}

	//加载玩家数据
	OffUserSaveControl offuserCtl(othUid);
	DBCMartialClubWrap othClub(othUid, othMartialGrade);
	if(othClub.Obj().protect_ts > Time::GetGlobalTime())
	{
		error_log("protect time  %u", uid);
		throw runtime_error("protect_time");
	}

	ProtoBattle::ProtoMartialClubBattleResp *resp = new ProtoBattle::ProtoMartialClubBattleResp;
	CommonGiftConfig::CommonModifyItem cfg;
	ProtoBattleDemo::ProtoBattleDemo msg;
	try
	{
		bool attackerWin = StartMartialBattle(uid, req, e_battletype_martial, cfg, msg);
		auto battle = resp->mutable_info();
		battle->CopyFrom(msg);
		if(attackerWin)
		{
			cfg.mutable_based()->set_coin(othClub.Obj().coin/2);
			auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
			for(auto e : propIndex)
			{
				cfg.add_props()->set_count(othClub.Obj().props[e.second]/2);
				cfg.add_props()->set_id(e.first);
				othClub.Obj().props[e.second] /= 2;
			}
			othClub.Obj().coin /= 2;
			othClub.Obj().protect_ts = Time::GetGlobalTime() + MARTIAL_BATTLE_PROTECT_TS;
			othClub.Save();

		}
		LogicUserManager::Instance()->CommonProcess(uid,cfg,"martial_battle",resp->mutable_commons());
		user.Obj().daily_battle_count += 1;
		user.Save();

		//战报
		MartialClubItem postItem;
		postItem.type 	= e_post_martialBattle;
		postItem.ts 	= Time::GetGlobalTime();
		postItem.grade  = martialGrade;
		postItem.level  = user.Obj().level;
		postItem.uuid   = uid;
		postItem.win   	= attackerWin ? 1 : 0;
		memcpy(postItem.fig, user.Obj().fig, sizeof(postItem.fig));
		memcpy(postItem.name, user.Obj().name, sizeof(postItem.name));
		LogicPostManager::Instance()->AddPost(othUid, postItem);
		if(UserManager::Instance()->IsOnline(othUid))
		{
			ProtoNotify::PushMartialBattlePost* msg = new ProtoNotify::PushMartialBattlePost;
			postItem.SetMessage(msg->mutable_post());
			LMI->sendMsg(othUid, msg);
		}
	}
	catch(const exception& e)
	{
		delete resp;
		error_log("martial battle error uid: %u, %s", uid, e.what());
		throw runtime_error("martial_battle_error");
	}

	return LMI->sendMsg(uid, resp) ? R_SUCCESS : R_ERROR;
}

int LogicBattleManager::Process(ProtoBattle::ProtoCSMartialClubBattleReq* req)
{
	unsigned myUid = req->myuid();
	unsigned myMartialGrade = req->mymartialgrade();
	unsigned othUid = req->othuid();
	unsigned othMartialGrade = req->othmartialgrade();

	//加载玩家数据
	OffUserSaveControl offuserCtl(othUid);
	DBCMartialClubWrap club(othUid, othMartialGrade);
	if(club.Obj().protect_ts > Time::GetGlobalTime())
	{
		error_log("protect time  %u", myUid);
		throw runtime_error("protect_time");
	}

	ProtoBattle::ProtoCSBattleResultReq* battleReq = new ProtoBattle::ProtoCSBattleResultReq;
	battleReq->set_myuid(myUid);
	CommonGiftConfig::CommonModifyItem cfg;
	ProtoBattleDemo::ProtoBattleDemo msg;
	try
	{
		bool attackerWin = StartMartialCSBattle(req, e_battletype_martial, cfg, msg);
		auto battle = battleReq->mutable_info();
		battle->CopyFrom(msg);
		if(attackerWin)
		{

			cfg.mutable_based()->set_coin(club.Obj().coin/2);
			auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
			for(auto e : propIndex)
			{
				cfg.add_props()->set_count(club.Obj().props[e.second]/2);
				cfg.add_props()->set_id(e.first);
				club.Obj().props[e.second] /= 2;
			}
			club.Obj().protect_ts = Time::GetGlobalTime() + MARTIAL_BATTLE_PROTECT_TS;
			club.Save();
		}

		//发送战报
		MartialClubItem postItem;
		postItem.type 	= e_post_martialBattle;
		postItem.ts 	= Time::GetGlobalTime();
		postItem.grade  = myMartialGrade;
		postItem.level  = req->level();
		postItem.uuid	= myUid;
		postItem.win    = attackerWin ? 1 : 0;
		memcpy(postItem.fig, req->myfig().c_str(), sizeof(postItem.fig));
		memcpy(postItem.name, req->myname().c_str(), sizeof(postItem.name));

		LogicPostManager::Instance()->AddPost(othUid, postItem);
		if(UserManager::Instance()->IsOnline(othUid))
		{
			ProtoNotify::PushInvitePost* msg = new ProtoNotify::PushInvitePost;
			postItem.SetMessage(msg->mutable_post());
			return LMI->sendMsg(othUid, msg) ? 0 : R_ERROR;
		}

		auto baseItem = battleReq->mutable_commons()->mutable_userbase()->add_baseitem();
		baseItem->set_type(type_coin);
		baseItem->set_change(cfg.based().coin());

		for(int i = 0; i < cfg.props_size(); ++i)
		{
			auto propItem = battleReq->mutable_commons()->mutable_props()->add_propsitem()->mutable_props();
			propItem->set_propsid(cfg.props(i).id());
			propItem->set_itemcnt(cfg.props(i).count());
		}
	}
	catch(const exception& e)
	{
		delete battleReq;
		error_log("csmartial_battle_error: uid: %u, %s",othUid,  e.what());
		throw runtime_error("csmartial_battle_error");
	}

	return ProtoManager::BattleConnectNoReplyByUID(myUid, battleReq);
}

int LogicBattleManager::Process(ProtoBattle::ProtoCSBattleResultReq* req)
{
	//消耗道具和抢夺的金币和道具
	CommonGiftConfig::CommonModifyItem cfg;
	auto& userBase = req->commons().userbase();
	for(int i = 0; i < userBase.baseitem_size(); ++i)
	{
		if(userBase.baseitem(i).type() == type_coin)
			cfg.mutable_based()->set_coin(userBase.baseitem(i).change());
		if(userBase.baseitem(i).type() == type_cash)
			cfg.mutable_based()->set_cash(userBase.baseitem(i).change());
	}

	auto& props = req->commons().props();
	for(int i = 0; i < props.propsitem_size(); ++i)
	{
		auto p = cfg.add_props();
		p->set_id(props.propsitem(i).props().propsid());
		p->set_count(props.propsitem(i).props().itemcnt());
	}

	ProtoBattle::ProtoCSMartialClubBattleResp* resp = new ProtoBattle::ProtoCSMartialClubBattleResp;
	try
	{
		LogicUserManager::Instance()->CommonProcess(req->myuid(), cfg, "martial_battle",resp->mutable_commons());
		resp->mutable_info()->CopyFrom(req->info());
		DBCUserBaseWrap user(req->myuid());
		user.Obj().daily_battle_count += 1;
		user.Save();

	}
	catch(const exception& e)
	{
		delete resp;
		error_log("martial battle error uid :%u, %s", req->myuid(), e.what());
		throw runtime_error("martial_battle_error");
	}

	return LMI->sendMsg(req->myuid(), resp) ? 0 : R_ERROR;
}



bool LogicBattleManager::StartBattle(unsigned uid, BattleType type, ProtoBattle::BattleCommon* req, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg)
{
	//消耗体力
	string log;
	if(type == e_battletype_pve)
		log = "pve";
	if(type == e_battletype_grade)
		log = "grade";
	if(type == e_battletype_random)
		log = "random";
	if(type == e_battletype_revenge)
		log	= "revenge";
	if(type == e_battletype_friend)
		log = "friend";

	bool win = false;
	DBCUserBaseWrap userwrap(uid);
	if(type != e_battletype_grade)
	{
		//恢复体力
		userwrap.RecoverPower(Time::GetGlobalTime(), userwrap.Obj().recover_time);

		if(userwrap.Obj().power < PVE_POWER_MIN)
		{
			error_log("power is not enough uid=%u, stage=%u", uid);
			throw runtime_error("power_not_enough");
		}
	}

	vector<BattleDemoHero> attacker;
	vector<BattleDemoItem> vecAttItem;
	UserBattleInit(uid, req, attacker, vecAttItem, cfg);

	//对方英雄
	vector<BattleDemoHero> defender;
	if(type == e_battletype_pve)
	{
		unsigned stage 	= req->stageid();
		unsigned stageIdx =  ConfigManager::Instance()->stage_index[stage]+1;
		//获取关卡信息
		const Stages::AllStage& stageCfg = StagesCfgWarp().GetStagesInfoById(stage);
		unsigned npcLevel = 1;

		if(stageIdx == (userwrap.GetStages() + 1))
			npcLevel = stageCfg.level();
		else
		{
			for(int i = 0; i < formation_[uid].size(); ++i)
			{
				DBCHeroWrap heroWrap(uid, formation_[uid][i]);
				npcLevel = max(npcLevel, heroWrap.Obj().level);
			}
		}

		for(int i = 0; i < stageCfg.npcid_size(); ++i)
		{
			SetBattleNpc(stageCfg.npcid(i), npcLevel, defender);
		}

		vector<BattleDemoItem> vecDefItem;
		//获取npc道具
		for(int i = 0; i < stageCfg.propsid_size() && i < e_item_max; ++i)
		{
			unsigned propId = stageCfg.propsid(i);
			auto& prop = ItemCfgWrap().GetPropsItem(propId);
			vecDefItem.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));
		}

		//开始战斗
		BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, userwrap.GetLevel(), npcLevel);
		msg = Battle.msg();
		win = Battle.attackerWin();

	}
	if(type == e_battletype_grade || type == e_battletype_revenge || type == e_battletype_friend
			|| (type == e_battletype_random && random_.count(uid) != 0) )
	{
		vector<BattleDemoHeroSkill> vecDefSkill;
		OfflineResourceItem* defItem = nullptr;
		if(type == e_battletype_grade)
		{
			if(enemy_.count(uid) == 0)
			{
				error_log("logic error uid: %u", uid);
				throw runtime_error("logic_error");
			}
			defItem	=  &enemy_[uid];
		}

		if(type == e_battletype_random)
		{
			if(random_.count(uid) == 0)
			{
				error_log("logic error uid: %u", uid);
				throw runtime_error("logic_error");
			}
			defItem = &random_[uid];
		}

		if(type == e_battletype_revenge)
		{
			if(revenge_.count(uid) == 0)
			{
				error_log("logic error uid: %u", uid);
				throw runtime_error("logic_error");
			}
			defItem= &(LogicResourceManager::Instance()->Get(uid));
		}

		if(type == e_battletype_friend)
		{
			if(friend_.count(uid) == 0)
			{
				error_log("logic error uid: %u", uid);
				throw runtime_error("logic_error");
			}
			defItem= &friend_[uid];
		}

		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			if(0 == defItem->heros[i].id)
				continue;
			for(int j = 0; j < e_skill_max; ++j)
			{
				unsigned initWeight = LogicHeroManager::initWeight[j];
				SkillInfo& skill = defItem->heros[i].skills[j];
				vecDefSkill.push_back(BattleDemoHeroSkill(skill.id, skill.type, skill.mul, skill.hurt, initWeight, skill.p_a));
			}

			AttrInfo& attr = defItem->heros[i].attr;
			defender.push_back(BattleDemoHero(defItem->heros[i].id, attr.hp,  attr.att, attr.def, attr.crit, attr.acrit, attr.dodge,
											attr.adodge, attr.critt, attr.speed, attr.battlePower, vecDefSkill));
			vecDefSkill.clear();
		}

		if(defender.empty())
		{
			error_log("logic error uid=%u", uid);
			throw runtime_error("logic_error");
		}

		//敌方道具
		vector<BattleDemoItem>  vecDefItem;
		for(int i = 0; i < MAX_BATTLE_PROPS; ++i)
		{
			unsigned propId = defItem->props[i];
			if(0 == propId)
				continue;
			auto& propCfg = ItemCfgWrap().GetPropsItem(propId);
			vecDefItem.push_back(BattleDemoItem(propCfg.id(), propCfg.type(), propCfg.factor(), propCfg.value(), propCfg.turn()));
		}
		//开始战斗
		BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, userwrap.GetLevel(), defItem->level);
		msg = Battle.msg();
		win = Battle.attackerWin();
	}
	if(type == e_battletype_random && random_.count(uid) == 0)
	{
		unsigned npcLevel = userwrap.Obj().level;
		const Random::UserInfo& randomcfg = RandomCfgWarp().User(npc_[uid]);
		for(int i = 0; i < randomcfg.npcid_size(); ++i)
		{
			SetBattleNpc(randomcfg.npcid(i), npcLevel, defender);
		}
		vector<BattleDemoItem> vecDefItem;
		//获取npc道具
		for(int i = 0; i < randomcfg.propsid_size() && i < e_item_max; ++i)
		{
			unsigned propId = randomcfg.propsid(i);
			auto& prop = ItemCfgWrap().GetPropsItem(propId);
			vecDefItem.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));
		}

		//开始战斗
		BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, userwrap.GetLevel(), npcLevel);
		msg = Battle.msg();
		win = Battle.attackerWin();
	}
	auto& item = LogicUserGradeManager::Instance()->Get(uid);
	item.battle_cnt++;


	return win;
}

bool LogicBattleManager::StartRobotBattle(unsigned uid, BattleType type, ProtoBattle::BattleCommon* req, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg)
{
	string log;
	if(type == e_battletype_grade_robot)
		log = "grade_robot";
	bool win = false;
	DBCUserBaseWrap userwrap(uid);
	if(type != e_battletype_grade_robot)
	{
		//恢复体力
		userwrap.RecoverPower(Time::GetGlobalTime(), userwrap.Obj().recover_time);

		if(userwrap.Obj().power < PVE_POWER_MIN)
		{
			error_log("power is not enough uid=%u, stage=%u", uid);
			throw runtime_error("power_not_enough");
		}
	}

	vector<BattleDemoHero> attacker;
	vector<BattleDemoItem> vecAttItem;
	UserBattleInit(uid, req, attacker, vecAttItem, cfg);

	//对方英雄
	vector<BattleDemoHero> defender;
	if(type == e_battletype_grade_robot)
	{
		if(grade_robot_.count(uid) == 0)
			throw runtime_error("no_match_robot");

		int idx = grade_robot_[uid];
		UserGradeItem& item = LogicUserGradeManager::Instance()->Get(uid);
		unsigned grade = item.grade;

		auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(grade).item(idx);
		for(int i = 0; i < cfg.npc_size(); ++i)
		{
			unsigned id = cfg.npc(i).id();
			unsigned level = cfg.npc(i).level();
			SetBattleNpc(id, level, defender);
		}

		//npc道具
		vector<BattleDemoItem> vecDefItem;
		for(int i = 0; i < cfg.props_size(); ++i)
		{
			unsigned propId = cfg.props(i);
			auto& prop = ItemCfgWrap().GetPropsItem(propId);
			vecDefItem.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));
		}

		//开始战斗
		BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, userwrap.GetLevel(), cfg.level());
		msg = Battle.msg();
		win = Battle.attackerWin();
	}

	auto& item = LogicUserGradeManager::Instance()->Get(uid);
	item.battle_cnt++;

	return win;
}

void LogicBattleManager::UserBattleInit(unsigned uid, ProtoBattle::BattleCommon* req, vector<BattleDemoHero>& team, vector<BattleDemoItem>& item, CommonGiftConfig::CommonModifyItem& cfg)
{
	auto& formation = formation_[uid];
	//是否设置阵型
	if(formation.empty())
	{
		error_log("no formation uid=%u", uid);
		throw runtime_error("no_formation");
	}

	//玩家英雄
	for(int i = 0; i < formation.size() && i < 2; ++i)
	{
		if(!DataHeroManager::Instance()->IsExistItem(uid, formation[i]))
		{
			error_log("hero is invalid uid=%u, heroid: %u", uid, formation[i]);
			throw runtime_error("hero_is_invalid");
		}

		SetBatttleHero(uid,  formation[i], team);
	}


	for(int i = 0; i < req->propid_size(); ++i)
	{
		//玩家道具
		CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
		unsigned props_id = req->propid(i);
		auto& prop = ItemCfgWrap().GetPropsItem(props_id);
		propsbase->set_id(props_id);
		propsbase->set_count(-1);
		item.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));
	}
	//更新玩家英雄信息
	for(int i = 0; i < team.size() && i < MAX_FORMATION_HERO; ++i)
	{
		HeroInfo hero;
		FullHeroAttr(i, team[i], hero);
		LogicResourceManager::Instance()->Update(uid, i, hero);
	}

}

int LogicBattleManager::PveAccount(unsigned uid, bool attackerWin, unsigned stageId, vector<unsigned>& heroId, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoPveBattleResp* msg)
{
	if(stageId > NPC_MAX_STAGE)
	{
		error_log("stage bigger than max =%u, stage=%u", uid, stageId);
		throw runtime_error("param_error");
	}
	//经验奖励
	const Stages::AllStage& stageCfg =  StagesCfgWarp().GetStagesInfoById(stageId);

	//玩家经验,金币,随机道具奖励
	int exp = stageCfg.rewards().based().exp();
	int coin = stageCfg.rewards().based().coin();
	if(!attackerWin)
		exp /= 2;
	if(attackerWin)
	{

		unsigned propMaxNum = stageCfg.rewards().props_size();


		if(stageId > 1)
		{
			unsigned randIndex = Math::GetRandomInt(propMaxNum);
			auto& randProp = stageCfg.rewards().props(randIndex);
			cfg.mutable_based()->set_coin(coin);
			CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
			propsbase->set_id(randProp.id());
			propsbase->set_count(randProp.count());
		}
		else
		{
			for(int i = 0; i < propMaxNum; ++i)
			{
				CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
				propsbase->set_id(stageCfg.rewards().props(i).id());
				propsbase->set_count(stageCfg.rewards().props(i).count());
			}

		}

	}
	cfg.mutable_based()->set_exp(exp);

	//英雄经验, 龙族奖励
	unsigned heroExp = stageCfg.heroexp();
	if(!attackerWin)
		heroExp /= 2;

	vector<DBCHeroWrap> heros;
	unsigned heroMaxLevel =  DBCUserBaseWrap(uid).Obj().level;
	unsigned heroMaxExp   = HeroCfgWrap().GetHeroByLevel(heroMaxLevel).exp();
	for(auto& id : heroId)
	{
		heros.push_back(DBCHeroWrap(uid, id));
		//加经验
		auto& hero = heros.back();
		if(hero.Obj().exp + heroExp < heroMaxExp)
			hero.AddExp(heroExp);
	}

	//奖励龙魂
	if(attackerWin)
	{
		CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
		propsbase->set_id(DRAGON_SCALE_ID);
		propsbase->set_count(1);
	}

	for(auto& value : heros)
	{
		value.Obj().SetMessage(msg->add_hero());
	}

	//玩家消耗体力
	if(stageCfg.rewards().based().has_power())
		cfg.mutable_based()->set_power(stageCfg.rewards().based().power());

	LogicUserManager::Instance()->CommonProcess(uid,cfg,"pve_battle",msg->mutable_commons());

	return 0;
}


int LogicBattleManager::SetBatttleHero(unsigned uid, unsigned heroId, vector<BattleDemoHero>& hero)
{
	HeroInfo heroAttr;
	heroAttr.id = heroId;
	LogicHeroManager::Instance()->GetHeroAttr(uid, heroId, heroAttr.attr);
	LogicHeroManager::Instance()->GetSkill(uid, heroId, heroAttr.skills);

	AttrInfo attr = heroAttr.attr;
	SkillInfo* skill =  heroAttr.skills;
	vector<BattleDemoHeroSkill> vecSkill;
	for(int i = 0; i < e_skill_max; ++i)
	{
		SkillInfo &s = skill[i];
		vecSkill.push_back(BattleDemoHeroSkill(s.id, s.type, s.mul, s.hurt, s.p_c, s.p_a));

	}

	hero.push_back(BattleDemoHero(heroId, attr.hp, attr.att, attr.def, attr.crit, attr.acrit, attr.dodge, attr.adodge, attr.critt, attr.speed, attr.battlePower, vecSkill));


	return 0;
}

int LogicBattleManager::SetBattleNpc(unsigned npcId, unsigned npclv, vector<BattleDemoHero>& npc)
{
	//获取关卡信息
	vector<BattleDemoHeroSkill> skill;
	double hp, att , def, crit_t = 0.0, battlePower;
	int speed, crit, a_crit, dodge, a_dodge = 0;
	auto& npcCfg = NpcCfgWarp().GetNpcById(npcId);
	for(int j = 0; j < e_skill_max; ++j)
	{
		unsigned initWeight = LogicHeroManager::initWeight[j];
		auto& skill_info = npcCfg.skill(j).skillinfo(npclv-1);
		battlePower += skill_info.fight_power();
		skill.push_back(BattleDemoHeroSkill(j+1, j, skill_info.multiple(), skill_info.hurtvalue(),initWeight, 0));
	}
	auto& level_attr = npcCfg.attr().levelattr(npclv - 1);
	hp = static_cast<double>(level_attr.hp());
	att = static_cast<double>(level_attr.att());
	def = static_cast<double>(level_attr.def());
	speed  = level_attr.first();
	auto& const_attr = npcCfg.attr();
	crit    = const_attr.critstrike();
	a_crit  = const_attr.critresist();
	dodge   = const_attr.dodge();
	a_dodge = const_attr.hit();
	crit_t  = const_attr.critrate()/(double)100;
	battlePower += 100 + att/2 + hp/10 + def;

	npc.push_back(BattleDemoHero(npcId, hp, att,def, crit, a_crit, dodge, a_dodge,crit_t, speed, battlePower, skill));

	return 0;
}


void LogicBattleManager::FullHeroAttr(int idx, BattleDemoHero& hero, HeroInfo& res)
{
	if(idx >= MAX_FORMATION_HERO)
	{
		throw runtime_error("param_error");
	}

	memset(&res, 0, sizeof(res));
	res.id 					= hero.id();
	res.attr.hp 			= hero.hp();
	res.attr.att 			= hero.att();
	res.attr.def 			= hero.def();
	res.attr.speed 			= hero.speed();
	res.attr.adodge 		= hero.a_dodge();
	res.attr.dodge			= hero.dodge();
	res.attr.crit			= hero.crit();
	res.attr.acrit			= hero.a_crit();
	res.attr.critt			= hero.crit_t();
	res.attr.battlePower	= hero.battlePower();

	vector<BattleDemoHeroSkill> heroSkill;
	hero.skills(heroSkill);
	for(int j = 0; j < heroSkill.size(); ++j)
	{
		res.skills[j].id 			= heroSkill[j].id();
		res.skills[j].type 			= heroSkill[j].type();
		res.skills[j].hurt 			= heroSkill[j].c();
		res.skills[j].mul	 		= heroSkill[j].s();
		res.skills[j].p_c 			= heroSkill[j].p_c();
		res.skills[j].p_a			= heroSkill[j].p_a();
	}
}


unsigned LogicBattleManager::RefreshUser(unsigned uid)
{
	//更新刷新次数
	UserGradeItem& gradeItem = LogicUserGradeManager::Instance()->Get(uid);
	gradeItem.refresh_cnt++;

	auto& userMap = ResourceManager::Instance()->GetMap();
	//1.过滤出在线的人数
	set<unsigned> onelineSet;
	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		if(UMI->IsOnline(it.first) && it.first != uid)
		{
			onelineSet.insert(it.first);
		}
	});
	//获取对方uid
	unsigned enemyUid = SelectUser(uid, onelineSet);
	if(0 != enemyUid)
		return enemyUid;

	//2. 过滤出昨天登录过的人

	set<unsigned> yesterdaySet;

	std::for_each(userMap.begin(), userMap.end(), [&](map<unsigned, unsigned>::const_reference it){
		DBCUserBaseWrap userWrap(it.first);
		if(it.first != uid && Time::IsToday(userWrap.Obj().last_login_time + 86400))
			yesterdaySet.insert(it.first);
	});

	enemyUid = SelectUser(uid, yesterdaySet);
	if(0 != enemyUid)
		return enemyUid;

	return 0;
}

unsigned LogicBattleManager::SelectUser(unsigned uid, set<unsigned>& users)
{
	set<unsigned> userSet;
	//搜索等级范围
	DBCUserBaseWrap userWrap(uid);
	int level = userWrap.Obj().level;
	const int range = 5;
	int min = level - range;
	int max = level + range;

	if(min <= 0)
		min = 1;
	if(max > USER_MAX_LEVEL)
		max = USER_MAX_LEVEL;

	auto& gradeItem = LogicUserGradeManager::Instance()->Get(uid);
	unsigned score = gradeItem.score;
	unsigned grade = gradeItem.grade;

	unsigned cnt = gradeItem.refresh_cnt;

	std::for_each(users.begin(), users.end(), [&](unsigned enemyId){
		auto& rItem = LogicResourceManager::Instance()->Get(enemyId);
		auto& gItem = LogicUserGradeManager::Instance()->Get(enemyId);
		if(cnt < 4)
		{
			if(gItem.score < score && (rItem.level >= (unsigned)min && rItem.level <= (unsigned)max))
				userSet.insert(enemyId);
		}
		else if(cnt < 11)
		{
			if(gItem.score > score && (rItem.level >= (unsigned)min && rItem.level <= (unsigned)max))
				userSet.insert(enemyId);
		}
		else
		{
			if(gItem.grade < grade && (rItem.level >= (unsigned)min && rItem.level <= (unsigned)max))
				userSet.insert(enemyId);
		}

	});

	if(userSet.empty())
		return 0;

	auto iter = userSet.begin();
	int offest = Math::GetRandomInt(userSet.size());
	advance(iter, offest);

	return *iter;
}


int LogicBattleManager::RandomUserReward(unsigned uid, unsigned enemyUid, CommonGiftConfig::CommonModifyItem& cfg)
{
	if(formation_[uid].empty())
	{
		error_log("no formation: %u", uid);
		throw runtime_error("no_formation");
	}


	DBCUserBaseWrap userWrap(uid);
	const CommonGiftConfig::CommonModifyItem& reward = RandomCfgWarp().GetRewardByLevel(userWrap.Obj().level);
	//荣誉值
	if(userWrap.Obj().level < MAX_HONOR)
		userWrap.AddHonor(PER_HONOR, "random_user");

	//奖励金币
	cfg.mutable_based()->set_coin(reward.based().coin());

	//消耗体力
	cfg.mutable_based()->set_power(reward.based().power());

	//钻石奖励
	cfg.mutable_based()->set_cash(reward.based().cash());

	if(enemyUid == 0)
		return 0;

	//加载对方数据
	OffUserSaveControl  offuserCtl(enemyUid);
	DBCUserBaseWrap enemyWrap(uid);

	DataBase& enemy = enemyWrap.Obj();
	if(enemy.honor >= PER_HONOR)
		enemyWrap.CostHonor(-PER_HONOR, "random_user");


	set<unsigned> tmp(formation_[uid].begin(), formation_[uid].end());
	vector<unsigned> formation;
	vector<unsigned> other;

	vector<unsigned> vIndexs;
	DataHeroManager::Instance()->GetIndexs(enemyUid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DataHero& hero = DataHeroManager::Instance()->GetDataByIndex(vIndexs[i]);
		unsigned heroId = hero.id;
		vector<unsigned> chips = CMI->archive_chip[heroId];
		for(int i = 0; i < chips.size(); ++i)
		{
			unsigned ud = DataItemManager::Instance()->GetPropsUd(enemyUid, chips[i]);
			if(-1 == ud)
				continue;
			if(tmp.count(heroId) != 0)
				formation.push_back(chips[i]);
			else
				other.push_back(chips[i]);
		}
	}
	unsigned propId = 0;
	//先从对方上阵英雄中掉落图鉴, 如果没有从其他碎片中掉落, 如果没有则不掉落
	if(!formation.empty())
	{
		unsigned idx = Math::GetRandomInt(formation.size());
		propId  = formation[idx];
	}
	else if(!other.empty())
	{
		unsigned idx = Math::GetRandomInt(other.size());
		propId = formation[idx];
	}

	if(propId != 0)
	{
		unsigned ud = DataItemManager::Instance()->GetPropsUd(enemyUid, propId);
		if(-1 == ud)
		{
			error_log("props not exist. uid=%u,propsid=%u", uid, propId);
			throw runtime_error("props_not_exist");
		}
		//掉落对手图鉴
		LogicPropsManager::Instance()->CostProps(enemyUid, ud, propId, 1, "random_user_battle");
	}

	//玩家获得图鉴
	auto prop = cfg.add_props();
	prop->set_count(1);
	prop->set_id(propId);

	return 0;
}


void LogicBattleManager::FriendBattleReward(unsigned uid, bool attckerWin, vector<unsigned>& heroId, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoFriendBattleResp* msg)
{
	unsigned level = BaseManager::Instance()->Get(uid).level;
	auto& rewardCfg = FriendCfgWarp().GetRewardByLevel(level);
	int exp = rewardCfg.reward().based().exp();
	int coin = rewardCfg.reward().based().coin();
	int power = rewardCfg.reward().based().power();
	int heroExp = rewardCfg.heroexp();

	if(!attckerWin)
	{
		exp /= 2;
		coin /= 2;
		heroExp /= 2;
	}

	cfg.mutable_based()->set_exp(exp);
	cfg.mutable_based()->set_coin(coin);
	for(int i = 0; i < rewardCfg.reward().props_size(); ++i)
	{
		auto p = cfg.add_props();
		p->set_id(rewardCfg.reward().props(i).id());
		p->set_count(rewardCfg.reward().props(i).count());
	}

	//英雄经验
	unsigned heroMaxLevel =  DBCUserBaseWrap(uid).Obj().level;
	unsigned heroMaxExp   = HeroCfgWrap().GetHeroByLevel(heroMaxLevel).exp();
	for(auto& id : heroId)
	{
		DBCHeroWrap data(uid, id);
		//加经验
		if(data.Obj().exp + heroExp < heroMaxExp)
			data.AddExp(heroExp);
	}

	//消耗体力
	cfg.mutable_based()->set_power(power);
}

bool  LogicBattleManager::StartMartialBattle(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq *req, BattleType type, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg)
{
	string log;
	if(type == e_battletype_martial)
		log = "martial";

	unsigned enemyUid = req->othuid();
	unsigned martialGrade = req->mymartialgrade();
	unsigned othMartialGrade = req->othmartialgrade();
	auto common = req->mutable_common();

	//我方英雄
	vector<BattleDemoHero> attacker;
	SetMartialBattleItem(uid, martialGrade, attacker);

	DataBase& user = BaseManager::Instance()->Get(uid);

	//玩家道具
	vector<BattleDemoItem> vecAttItem;
	CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
	DataMartialClub& myClub = DataMartialClubManager::Instance()->GetData(uid, martialGrade);
	for(int i = 0; i <  common->propid_size() && i < MAX_BATTLE_PROPS ; ++i)
	{
		unsigned props_id = common->propid(i);
		auto& prop = ItemCfgWrap().GetPropsItem(props_id);
		propsbase->set_id(props_id);
		propsbase->set_count(-1);
		vecAttItem.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));

		//记录使用道具
		myClub.use_props[i] = props_id;
	}

	vector<BattleDemoHero> defender;
	SetMartialBattleItem(enemyUid, othMartialGrade, defender);

	DataMartialClub& othclub = DataMartialClubManager::Instance()->GetData(enemyUid, othMartialGrade);
	vector<BattleDemoItem>  vecDefItem;
	for(int i = 0; i < MAX_BATTLE_PROPS; ++i)
	{
		unsigned propId = othclub.use_props[i];
		if(0 == propId)
			continue;
		auto& propCfg = ItemCfgWrap().GetPropsItem(propId);
		vecDefItem.push_back(BattleDemoItem(propCfg.id(), propCfg.type(), propCfg.factor(), propCfg.value(), propCfg.turn()));
	}

	DataBase& enemy = BaseManager::Instance()->Get(enemyUid);


	BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, user.level, enemy.level);
	msg = Battle.msg();

	return Battle.attackerWin();
}



//跨服踢馆
bool LogicBattleManager::StartMartialCSBattle(ProtoBattle::ProtoCSMartialClubBattleReq* req, BattleType type, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg)
{
	string log;
	if(type == e_battletype_martial)
		log = "martial";
	//我方英雄
	vector<BattleDemoHero> attacker;
	for(int i = 0; i < req->hero_size(); ++i)
	{
		//获取技能
		auto& hero_cfg =  HeroCfgWrap().GetHeroByHeroId(req->hero(i).heroid());
		int skillLv = 1;
		vector<BattleDemoHeroSkill> vecSkill;
		for(int j = 0; j < req->hero(i).skill_size(); ++j)
		{
			skillLv = req->hero(i).skill(j);
			unsigned type 	= j;
			unsigned id 		= hero_cfg.skill(j).id();
			double multiple	= hero_cfg.skill(j).skillinfo(skillLv-1).multiple();
			unsigned hurt 	= hero_cfg.skill(j).skillinfo(skillLv-1).hurtvalue();
			unsigned initWeight = LogicHeroManager::initWeight[j];
			unsigned userAddWeight = AddWeightCfgWarp().GetPlayerAddWeightBylevel(skillLv).weight(j); //玩家等级增加权重
			vecSkill.push_back(BattleDemoHeroSkill(id, type, multiple, hurt, initWeight, userAddWeight));
		}

		auto hero = req->hero(i);
		attacker.push_back(BattleDemoHero(hero.heroid(), hero.hp(), hero.att(), hero.def(), hero.critstrike(),
						hero.critresist(), hero.dodge(), hero.hit(), hero.critrate(), hero.first(), hero.battlepower(), vecSkill));
	}

	//我方道具
	vector<BattleDemoItem> vecAttItem;
	CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
	auto common = req->mutable_common();
	for(int i = 0; i <  common->propid_size() ; ++i)
	{
		unsigned props_id = common->propid(i);
		auto& prop = ItemCfgWrap().GetPropsItem(props_id);
		propsbase->set_id(props_id);
		propsbase->set_count(-1);
		vecAttItem.push_back(BattleDemoItem(prop.id(), prop.type(), prop.factor(), prop.value(), prop.turn()));
	}


	//对方英雄
	//加载离线数据
	OffUserSaveControl offuserCtl(req->othuid());

	vector<BattleDemoHero> defender;
	SetMartialBattleItem(req->othuid(), req->othmartialgrade(), defender);

	DataMartialClub& club = DataMartialClubManager::Instance()->GetData(req->othuid(), req->othmartialgrade());
	vector<BattleDemoItem>  vecDefItem;
	for(int i = 0; i < MAX_BATTLE_PROPS; ++i)
	{
		unsigned propId = club.use_props[i];
		if(0 == propId)
			continue;
		auto& propCfg = ItemCfgWrap().GetPropsItem(propId);
		vecDefItem.push_back(BattleDemoItem(propCfg.id(), propCfg.type(), propCfg.factor(), propCfg.value(), propCfg.turn()));
	}

	DataBase& enemy = BaseManager::Instance()->Get(req->othuid());
	BattleDemo Battle(attacker, defender, vecAttItem, vecDefItem, req->level(), enemy.level);
	msg = Battle.msg();

	return Battle.attackerWin();

}

void LogicBattleManager::SetMartialBattleItem(unsigned uid, unsigned martialGrade, vector<BattleDemoHero>& battleDemo)
{
	//对方英雄
	vector<unsigned> vIndex;
	vector<unsigned> enemyHeros;

	DataMartialHeroManager::Instance()->GetIndexs(uid, vIndex);
	for(auto& e: vIndex)
	{
		DBCMartialHeroWrap hero(e);
		if(hero.Obj().id / 10 == martialGrade)
		{
			HeroInfo heroAttr;
			auto& hero_cfg =  HeroCfgWrap().GetHeroByHeroId(hero.Obj().heroid);
			double multiple = 0.0;
			for(int i = 0; i < e_skill_max; ++i)
			{
				int skillLv = hero.Obj().skill[i];
				heroAttr.skills[i].type 	= i;
				heroAttr.skills[i].id 		= hero_cfg.skill(i).id();
				heroAttr.skills[i].mul		= hero_cfg.skill(i).skillinfo(skillLv-1).multiple();
				heroAttr.skills[i].hurt 	= hero_cfg.skill(i).skillinfo(skillLv-1).hurtvalue();
				heroAttr.skills[i].p_c		= LogicHeroManager::initWeight[i];
				heroAttr.skills[i].p_a 		= AddWeightCfgWarp().GetPlayerAddWeightBylevel(skillLv).weight(i); //玩家等级增加权重
			}

			SkillInfo* skill =  heroAttr.skills;
			vector<BattleDemoHeroSkill> vecSkill;
			for(int i = 0; i < e_skill_max; ++i)
			{
				SkillInfo &s = skill[i];
				vecSkill.push_back(BattleDemoHeroSkill(s.id, s.type, s.mul, s.hurt, s.p_c, s.p_a));
			}

			auto& obj = hero.Obj();
			battleDemo.push_back(BattleDemoHero(obj.heroid, obj.hp, obj.att, obj.def, obj.crit, obj.acrit, obj.dodge, obj.adodge, obj.critt, obj.speed, obj.battlePower, vecSkill));
		}
	}

}


int LogicBattleManager::FullMessage(unsigned uid, User::FriendInfo*msg)
{
	vector<unsigned> vIndexs;
	DataConcernManager::Instance()->GetIndexs(uid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DataConcern& data = DataConcernManager::Instance()->GetDataByIndex(vIndexs[i]);
		try
		{
			data.SetMessage(msg->add_info());
		}
		catch(const std::exception &e)
		{
			error_log("uid: %u, %s", uid, e.what());
		}

	}

	return 0;
}
