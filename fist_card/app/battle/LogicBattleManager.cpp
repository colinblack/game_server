/*
 * LogicBattleManager.cpp
 *
 *  Created on: 2018年7月12日
 *      Author: colin
 */

#include "LogicBattleManager.h"

int LogicBattleManager::OnInit()
{
	games_[e_battletype_pve] = GamePve::Instance();
	games_[e_battletype_grade] = GameGrade::Instance();
	games_[e_battletype_championship] = GameChampionship::Instance();

	return 0;
}

void LogicBattleManager::OnTimer1()
{
	while(!robot_.empty())
	{
		const auto& item = robot_.front();
		unsigned battleid = item.id;
		unsigned type = item.type;
		try
		{
			if(games_[type]->RobotOutCard(battleid) == R_ERROR)
				throw runtime_error("robot_out_card_error");
		}
		catch(const std::exception& e)
		{
			error_log("onrobot battleid: %u, type: %u, %s", battleid, type, e.what());
		}

		robot_.pop_front();
	}

}


void LogicBattleManager::CallDestroy()
{
	for(auto it = games_.begin(); it != games_.end(); ++it)
	{
		it->second->CallDestroy();
	}

	Destroy();
}


//设置阵型
int LogicBattleManager::Process(unsigned uid, ProtoBattle::SetFormationReq* req, ProtoBattle::SetFormationResp* resp)
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

int LogicBattleManager::Process(unsigned uid, ProtoBattleBase::ProtoBattleReq* req, ProtoBattleBase::ProtoBattleResp* resp)
{
	unsigned battleid = req->battleid();

	//battleid是否存在
	if(!DataGameManager::Instance()->IsValid(battleid))
	{
		error_log("battle invalid, uid=%u, battleid=%u", uid, battleid);
		throw runtime_error("battle_invalid");
	}

	unsigned cardid = req->cardid();
	unsigned ud = req->ud();

	//临时卡
	if(ud != 0 && !DataCardsManager::Instance()->IsExistItem(uid, ud))
	{
		error_log("card not exist, uid=%u, ud=%u", uid, ud);
		throw runtime_error("card_not_exist");
	}

	//检查前端发过来的参数
	auto& gameData = DataGameManager::Instance()->GetData(battleid);

	GameTeam* attacker = gameData.CurAtt();
	GameTeam* defender = gameData.CurDef();

	if(attacker->uid != uid || attacker->attr[attacker->index].id != req->heroid())
	{
		error_log("param error, uid=%u, ud=%u, index: %u, hero1: %u, hero2: %u, reqid:%u, attacking: %u", uid, ud, attacker->index, attacker->attr[0].id, attacker->attr[1].id, req->heroid(), gameData.attacking);
		throw runtime_error("param_error");
	}

	auto& cfg = CardsCfgWrap().GetCardsCfgById(cardid);

	//点数是否足够
	if(attacker->left_point < cfg.point() &&  cfg.point() != 0)
	{
		error_log("point no enough, uid=%u, battleid=%u", uid, battleid);
		throw runtime_error("point_no_enough");
	}

	auto& data = DataCardsManager::Instance()->GetData(uid, ud);
	unsigned star = data.star;

	//处理效果
	attacker->record.Star((char)star);
	for(int i = 0; i < cfg.action(star).list_size(); ++i)
	{
		auto& actionCfg = cfg.action(star).list(i);
		attacker->record.Index((char)i);
		if(LAI->Process(battleid, cardid, actionCfg, resp->mutable_battle()) == R_ERROR)
		{
			error_log("out card failed, uid=%u", uid);
			throw runtime_error("out_card_failed");
		}
		//清除出牌玩家本次效果数据;
		gameData.Clear(e_att);

	}
	//处理防守方复活buff
	LAI->Revive(battleid, *defender, resp->mutable_battle());

	//TODO:处理流血buff
	if(LAI->Blood(battleid, *attacker, *defender, resp->mutable_battle()) == R_ERROR)
	{
		error_log("out card failed, uid=%u", uid);
		throw runtime_error("out_card_failed");
	}

	//TODO:处理反击
	if(LAI->ShotBack(battleid, *attacker, *defender, resp->mutable_battle()) == R_ERROR)
	{
		error_log("out card failed, uid=%u", uid);
		throw runtime_error("out_card_failed");
	}

	//TODO:处理进攻方复活buff
	LAI->Revive(battleid, *attacker, resp->mutable_battle());

	//TODO: 判断游戏是否结束, 结束就进行结算结算
	if(DataGameManager::Instance()->Impl(battleid))
	{
		unsigned winUid = gameData.AttackerWin() ? gameData.att.uid : gameData.def.uid;
		resp->set_winuid(winUid);
		games_[req->type()]->GameEnd(battleid);
	}

	//TODO:处理死亡次数buff
	LAI->DealBuff(battleid, *attacker, e_action_last_4);
	LAI->DealBuff(battleid, *defender, e_action_last_4);

	//出的牌
	resp->set_cardid(cardid);
	//消耗点数
	resp->set_point(attacker->CostPoint(cfg.point()));

	auto& handcards = DGI->GetHandCards(battleid, attacker->uid);
	//将卡牌加到废弃牌库x
	for(auto it = handcards.begin(); it != handcards.end(); ++it)
	{
		//如果是临时卡直接丢弃掉
		if(it->ud == ud && it->ud != 0)
		{
			DGI->AddCardTemp(battleid, uid, *it);
			swap(*it, handcards.back());
			handcards.pop_back();
			break;
		}
	}

	//更新出牌时戳
	gameData.UpdataOutCardTs(Time::GetGlobalTime());

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoTurnEndReq* req, ProtoBattle::ProtoTurnEndResp* resp)
{
	unsigned battleid = req->battleid();
	auto& gameData = DataGameManager::Instance()->GetData(battleid);
	auto& attacker = *gameData.CurAtt();

	//判断当前出牌玩家
	if(attacker.uid != uid)
	{
		error_log("current user error, uid=%u", uid);
		throw runtime_error("current_user_error");
	}

	//重置回合数据
	attacker.Reset();

	//获取手牌
	vector<CardItem>& handcards = DataGameManager::Instance()->GetHandCards(battleid, attacker.uid);
	vector<CardItem>& tempcards = DataGameManager::Instance()->GetTempCards(battleid, uid);
	vector<CardItem>& cardbags = DataGameManager::Instance()->GetCardBag(battleid, uid);

	//发牌
	GameBase::CreateHandCard(handcards, cardbags, tempcards);

	//发送发牌给前端
	for(auto& card : cardbags)
	{
		card.SetMessage(resp->mutable_cards()->add_bag());
	}

	for(auto& card : handcards)
	{
		card.SetMessage(resp->mutable_cards()->add_hand());
	}

	resp->set_nextuser(gameData.ChangeAttacking());
	resp->set_point(attacker.left_point);
	//设置电脑出牌
	LogicBattleManager::Instance()->AddRobot(battleid, req->type());

	//TODO: 处理按回合buff
	LAI->DealBuff(battleid, attacker, e_action_last_1);

	return R_SUCCESS;
}

//pve
int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoPveBattleReq* req, ProtoBattle::ProtoPveBattleResp* resp)
{
	DBCUserBaseWrap userwrap(uid);
	unsigned stage = req->common().id();


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

	//创建比萨
	unsigned battleid = DataGameManager::Instance()->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_pve];
	//开始比赛
	int ret = gameBase->GameStart(uid, battleid, req->common(), resp);
	if(ret != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_game_failed");
	}

	//保存关卡索引
	auto gamePve = dynamic_cast<GamePve*>(gameBase);
	gamePve->SaveStageId(uid, stage);

	return 0;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoGradeBattleReq* req, ProtoBattle::ProtoGradeBattleResp* resp)
{
	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_grade];
	if(gameBase->GameStart(uid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_grade_battle_failed");
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoMatchReq* req,  ProtoBattle::ProtoMatchResp* resp)
{
	UserGradeItem& item = LogicUserGradeManager::Instance()->Get(uid);
	auto gameGrade = dynamic_cast<GameGrade*>(games_[e_battletype_grade]);
	int index = 0;
	unsigned user = gameGrade->MatchUser(uid, item.grade, index);

	auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(item.grade);
	if(user == 0)
	{
		resp->set_name(cfg.item(index).name());
		resp->set_grade(item.grade);
		auto& npc = cfg.item(index).npc();
		for(int i = 0; i < npc.size(); ++i)
		{
			resp->add_heroid(npc.Get(i).id());
		}
		gameGrade->SetRobot(uid, index);
	}
	else
	{
		//加载玩家数据
		OffUserSaveControl  offuserCtl(user);
		OfflineResourceItem& defItem = LogicResourceManager::Instance()->Get(user);
		defItem.SetMessage(item.grade, resp);
		gameGrade->SetUser(uid, user);
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRefreshReq* req, ProtoBattle::ProtoRefreshResp* resp)
{
	auto gameRandom	= dynamic_cast<GameRandom*>(games_[e_battletype_random]);

	//刷新随机玩家
	unsigned othUid = gameRandom->RefreshUser(uid);
	if(0 != othUid)
	{
		OfflineResourceItem& defItem = LogicResourceManager::Instance()->Get(othUid);
		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			if(0 == defItem.heros[i].id)
				continue;
			auto attr = resp->mutable_hero()->Add();
			defItem.SetMessage(i, attr);
		}
		defItem.SetMessage(resp);

		gameRandom->SetRandom(uid, othUid);
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
		gameRandom->SetRandom(uid, idx);
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRandomUserReq* req, ProtoBattle::ProtoRandomUserResp* resp)
{
	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_random];
	if(gameBase->GameStart(uid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_grade_battle_failed");
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoRevengeReq* req, ProtoBattle::ProtoRevengeResp* resp)
{
	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_revenge];
	auto gameRevenge = dynamic_cast<GameRandom*>(gameBase);
	gameRevenge->SetRandom(uid, gameRevenge->Revenge(uid));

	if(gameBase->GameStart(uid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_grade_revenge_battle_failed");
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoFriendBattleReq* req, ProtoBattle::ProtoFriendBattleResp* resp)
{
	unsigned othuid = req->otherid();
	//对方uid是否有效
	if(!IsValidUid(othuid))
	{
		error_log("othuid is invalid. uid=%u,othuid=%u", uid, othuid);
		throw runtime_error("param_uid_invalid");
	}
	//好友每天只能挑战一次
	if(!DataConcernManager::Instance()->IsExistItem(uid, othuid))
	{
		error_log("freind not exist, uid: %u, othuid: %u", uid, othuid);
		throw runtime_error("freind_not_exist");
	}

	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_friend];
	auto gameFriend = dynamic_cast<GameFriend*>(gameBase);
	gameFriend->SetFriend(uid, othuid);
	if(gameBase->GameStart(uid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_friend_battle_failed");
	}

	DBCFriendWrap data(uid, othuid);
	if(!data.UpdateBattleTs())
		throw runtime_error("battle_ts_error");

	return R_SUCCESS;
}

int LogicBattleManager::Process(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq* req)
{
	unsigned othuid = req->othuid();
	unsigned mymGrade = req->mymartialgrade();
	unsigned othmGrade = req->othmartialgrade();

	if(!IsValidMartialGrade(mymGrade) ||
			!IsValidMartialGrade(othmGrade))
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

	//发送跨服踢馆数据
	if(CMI->IsNeedConnectByUID(othuid))
	{
		ProtoBattle::ProtoCSMartialClubBattleReq* msg = new ProtoBattle::ProtoCSMartialClubBattleReq;
		msg->set_othuid(othuid);

		return ProtoManager::BattleConnectNoReplyByUID(othuid, msg);
	}

	//加载玩家数据
	OffUserSaveControl offuserCtl(othuid);
	DBCMartialClubWrap othClub(othuid, othmGrade);
	if(othClub.Obj().protect_ts > Time::GetGlobalTime())
	{
		error_log("protect time  %u", uid);
		throw runtime_error("protect_time");
	}

	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", uid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_martial];

	vector<unsigned> vIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(othuid, vIndexs);

	vector<HeroAttrItem> temp;
	for(auto& index : vIndexs)
	{
		auto& hero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(hero.id / 10 == othmGrade)
		{
			temp.push_back(HeroAttrItem(hero.id, hero.hp, hero.att, hero.def, hero.crit, hero.acrit, hero.dodge,
					hero.adodge, hero.critt, hero.speed, hero.battlePower, 0));
		}
	}

	auto gameClub = dynamic_cast<GameMartialClub*>(gameBase);
	auto& clubData = DataMartialClubManager::Instance()->GetData(othuid, othmGrade);
	unsigned othCoins = clubData.coin;
	unsigned othProtectTs = clubData.protect_ts;
	map<unsigned, unsigned> props = gameClub->GetMartialClubProp(vector<unsigned>(clubData.props, clubData.props+MAX_BATTLE_PROPS));

	MartialBattleInfo info(mymGrade, othuid, othmGrade, othCoins, othProtectTs, temp, props);
	gameClub->SetMartialBattleInfo(uid, info);

	ProtoBattle::ProtoMartialClubBattleResp* resp = new ProtoBattle::ProtoMartialClubBattleResp;
	if(gameBase->GameStart(uid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_friend_battle_failed");
	}

	return R_SUCCESS;
}


int LogicBattleManager::Process(ProtoBattle::ProtoCSMartialClubBattleReq* req)
{
	unsigned myuid 	= req->othuid();
	unsigned mymGrade = req->mymgrade();
	unsigned othuid = req->myuid();

	OffUserSaveControl offuserCtl(myuid);
	auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
	ProtoBattle::ProtoCSMartialClubBattleResp* resp = new ProtoBattle::ProtoCSMartialClubBattleResp;

	auto& club = DataMartialClubManager::Instance()->GetData(myuid, mymGrade);
	club.SetMessage(propIndex, resp);
	vector<unsigned> vIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(myuid, vIndexs);
	for(auto& index : vIndexs)
	{
		auto& martialHero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(martialHero.id / 10 == mymGrade)
		{
			DBCHeroWrap hero(myuid, martialHero.id);
			hero.SetMessage(resp->add_hero());
		}
	}

	resp->set_myuid(othuid);
	resp->set_mymgrade(mymGrade);

	return ProtoManager::BattleConnectNoReplyByUID(othuid, resp);
}

int LogicBattleManager::Process(ProtoBattle::ProtoCSMartialClubBattleResp* req)
{
	unsigned myuid 		= req->othuid();
	unsigned othuid 	= req->myuid();
	unsigned mymGrade 	= req->mymgrade();
	unsigned othmGrade 	= req->othmgrade();
	unsigned othProtectTs = req->othprotectts() ;
	unsigned othCoins	  = req->othcoins();

	if(othProtectTs > Time::GetGlobalTime())
	{
		error_log("in protect time, uid=%u", othuid);
		throw runtime_error("in_protect_time");
	}

	unsigned battleid = DGI->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create game failed, uid=%u", myuid);
		throw runtime_error("create_game_failed");
	}

	auto gameBase = games_[e_battletype_martial];

	vector<HeroAttrItem> temp;
	for(int i = 0; i < req->hero_size(); ++i)
	{
		auto& hero = req->hero(i);
		temp.push_back(HeroAttrItem(hero.heroid(), hero.hp(), hero.att(), hero.def(), hero.critstrike(), hero.critresist(), hero.dodge(),
						hero.hit(), hero.critrate(), hero.first(), hero.battlepower(), 0));
	}

	map<unsigned, unsigned> props;
	for_each(req->othprops().begin(), req->othprops().end(),
				[&](ProtoMartialClub::MartialClubProp item){props.insert({item.id(), item.count()});});
	MartialBattleInfo info(mymGrade, othuid, othmGrade, othCoins, othProtectTs, temp, props);

	ProtoBattle::ProtoMartialClubBattleResp* resp = new ProtoBattle::ProtoMartialClubBattleResp;
	if(gameBase->GameStart(myuid, battleid, req->common(), resp) != R_SUCCESS)
	{
		DataGameManager::Instance()->Clear(battleid);
		throw runtime_error("start_friend_battle_failed");
	}

	return R_SUCCESS;
}

int LogicBattleManager::Process(ProtoBattle::ProtoCSSynOthMartialInfo* req)
{
	unsigned myuid = req->othuid();
	unsigned mymGrade = req->othmgrade();
	unsigned coins = req->othcoins();
	unsigned protectTs = req->othprotectts();

	DBCMartialClubWrap club(myuid, mymGrade);
	club.Obj().coin = coins;
	club.Obj().protect_ts = protectTs;

	auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
	for(auto& prop : req->othprops())
	{
		int index = propIndex[prop.id()];
		club.Obj().props[index] = prop.count();
	}

	club.Save();

	return R_SUCCESS;
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
