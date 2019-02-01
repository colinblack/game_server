/*
 * GameAllManager.cpp
 *
 *  Created on: 2018年11月28日
 *      Author: colin
 */

#include "GameAllManager.h"
#include "LogicBattleManager.h"

int GamePve::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{
	if(InitUserItem(uid, battleid) != R_SUCCESS)
	{
		error_log("init user item failed, uid=%u", uid);
		return R_ERROR;
	}

	if(InitNpcItem(uid, battleid, req.id()) != R_SUCCESS)
	{
		error_log("init npc item failed, uid=%u", uid);
		return R_ERROR;
	}

	ProtoBattle::ProtoPveBattleResp* resp = dynamic_cast<ProtoBattle::ProtoPveBattleResp*>(message);
	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_pve, resp->mutable_common());


	return R_SUCCESS;
}


int GamePve::InitNpcItem(unsigned uid, unsigned battleid, unsigned id)
{
	unsigned stageid = id;
	int stageidx = ConfigManager::Instance()->stage_index[stageid]+1;

	auto& stageCfg = StagesCfgWarp().GetStagesInfoById(stageid);

	DataBase& base = BaseManager::Instance()->Get(uid);

	//添加npc到比赛
	vector<unsigned> npchero;
	for(int i = 0; i < stageCfg.npcid_size(); ++i)
	{
		npchero.push_back(stageCfg.npcid(i));
	}

	//获取阵型
	vector<unsigned>& formation = LogicBattleManager::Instance()->GetFormation(uid);
	//获取npc等级
	unsigned npclv = 1;
	if(stageidx == base.pass + 1)
		npclv = stageCfg.level();
	else
	{
		for(auto& heroid : formation)
		{
			DataHero& hero = DataHeroManager::Instance()->GetData(uid, heroid);
			npclv = max(npclv, hero.level);
		}
	}


	int ret = DataGameManager::Instance()->AddUser(stageid, battleid, npclv);
	if(ret != R_SUCCESS)
	{
		error_log("add npc error, uid=%u, ret=%u", uid, ret);
		return ret;
	}

	//设置英雄属性
	for(auto& heroid : npchero)
	{
		auto& ncpcfg = NpcCfgWarp().GetNpcById(heroid);
		auto& lattr = ncpcfg.attr().levelattr(npclv - 1);
		auto& cattr = ncpcfg.attr();

		unsigned battlePow = 100 + lattr.att()/2 + lattr.hp()/10 + lattr.def();
		HeroAttrItem attr(heroid, lattr.hp(), lattr.att(), lattr.def(), cattr.critstrike(), cattr.critresist(),
							cattr.dodge(), cattr.hit(), cattr.critrate()/(double)100, lattr.first(), battlePow, 0);
		DataGameManager::Instance()->SetHeroAttr(stageid, battleid, heroid, attr);
	}

	//随机从卡池里抽牌组成战斗卡包
	vector<CardItem> cardbag;
	cardbag.reserve(stageCfg.cards_size());
	for(int i = 0; i < stageCfg.cards_size(); ++i)
	{
		cardbag.push_back(CardItem(0, stageCfg.cards(i).id(), stageCfg.cards(i).star(), e_card_common));
	}

	CreatNpcCardBag(battleid, stageid, npchero, cardbag);

	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, stageid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, stageid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, stageid);

	//随机从战斗卡包中抽牌组成手牌
	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}


int GamePve::PveAccount(unsigned uid, bool attackerWin, unsigned stageId, vector<unsigned>& heroId, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoPveBattleResult* msg)
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

		//掉落卡牌
		for(auto& card : stageCfg.dropcards())
			LogicCardsManager::Instance()->AddCards(uid, card.id(), "pve_drop_cards", msg->mutable_dropcards());
		//更新关卡
		DBCUserBaseWrap user(uid);
		user.UpdateStages(CMI->stage_index[stageId]+1);
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

/*
	for(auto& value : heros)
	{
		value.Obj().SetMessage(msg->add_hero());
	}

*/
	//玩家消耗体力
	if(stageCfg.rewards().based().has_power())
		cfg.mutable_based()->set_power(stageCfg.rewards().based().power());

	LogicUserManager::Instance()->CommonProcess(uid,cfg,"pve_battle",msg->mutable_commons());

	return 0;
}


void GamePve::GameEnd(unsigned battleid)
{
	//结算
	auto& data = DataGameManager::Instance()->GetData(battleid);

	unsigned uid = data.att.uid;
	unsigned stageid = GamePve::Instance()->StageId(uid);
	vector<unsigned> formation = LogicBattleManager::Instance()->GetFormation(uid);
	CommonGiftConfig::CommonModifyItem cfg;

	ProtoBattle::ProtoPveBattleResult* msg = new ProtoBattle::ProtoPveBattleResult;
	try
	{
		PveAccount(uid, data.AttackerWin(), stageid, formation, cfg, msg);
	}
	catch(const exception& e)
	{
		delete msg;
		error_log("pve account error, battleid: %u", battleid);
		throw runtime_error("pva_account_error");
	}

	LogicManager::Instance()->sendMsg(uid, msg);
	DBCHeroWrap::ResetCombineLimit();
	DataGameManager::Instance()->Clear(battleid);
}


int GameGrade::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{
	if(InitUserItem(uid, battleid) != R_SUCCESS)
	{
		error_log("init user item failed, uid=%u", uid);
		return R_ERROR;
	}

	if(real_user_.count(battleid) > 0)
	{
		InitOthItem(uid, battleid, true);
	}
	else if(robot_.count(battleid) >0)
	{
		InitOthItem(uid, battleid, false);
	}
	else
	{
		error_log("enemy hero empty, uid:%u", uid);
		return R_ERROR;
	}

	ProtoBattle::ProtoGradeBattleResp* resp = dynamic_cast<ProtoBattle::ProtoGradeBattleResp*>(message);
	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_grade, resp->mutable_common());

	return R_SUCCESS;
}

int GameGrade::InitOthItem(unsigned uid, unsigned battleid, bool isUser)
{
	unsigned level = 0;
	unsigned id = 0;

	vector<HeroAttrItem> attrItem;
	attrItem.reserve(MAX_FORMATION_HERO);
	if(isUser)
	{
		auto& item = LogicResourceManager::Instance()->Get(real_user_.count(uid));
		for(int i = 0; i < MAX_FORMATION_HERO; ++i)
		{
			auto& info = item.heros[i];
			if(info.id == 0)
				continue;

			auto& attr = info.attr;
			HeroAttrItem temp(info.id, attr.hp, attr.att, attr.def, attr.crit, attr.acrit, attr.dodge,
							attr.adodge, attr.critt, attr.speed, attr.battlePower, 0);
			attrItem.push_back(temp);
		}
		level = item.level;
		id  = item.uid;
	}
	else
	{
		auto& item = LogicUserGradeManager::Instance()->Get(uid);
		unsigned grade = item.grade;
		auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(grade).item(robot_[uid]);
		NpcCfgWarp ncpWarp;
		for(int i = 0; i < cfg.npc_size(); ++i)
		{
			unsigned id = cfg.npc(i).id();
			unsigned level = cfg.npc(i).level();
			auto& npcCfg = ncpWarp.GetNpcById(id);
			auto& lv = npcCfg.attr().levelattr(level - 1);
			auto& c	 = npcCfg.attr();
			double battlePow = 100 + lv.att() / 2 + lv.hp() / 10 + lv.def();
			HeroAttrItem temp(id, lv.hp(), lv.att(), lv.def(), c.critstrike(), c.critresist(), c.dodge(),
					c.hit(), c.critrate(), lv.first(), battlePow, 0);
			attrItem.push_back(temp);
		}
		level = cfg.level();
		id = cfg.id();
	}

	if(DGI->AddUser(id, battleid, level) != R_SUCCESS)
	{
		error_log("add user error, uid=%u", uid);
		return R_ERROR;
	}

	for(auto& e : attrItem)
	{
		if(DataGameManager::Instance()->SetHeroAttr(uid, battleid, e.id, e) != R_SUCCESS)
		{
			error_log("set hero attribute failed, uid=%u, ret=%u", uid);
			return R_ERROR;
		}
	}

	//创建手牌
	if(isUser)
	{
		//随机从卡池里抽牌组成战斗卡包
		CreateUserCardBag(battleid, uid);
		//获取手牌
		vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
		vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
		vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);
		CreateHandCard(handcards, cardbags, tempcards);
	}
	else
	{
		UserGradeItem& item = LogicUserGradeManager::Instance()->Get(uid);
		auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(item.grade);
		vector<CardItem> cardbag;
		cardbag.reserve(cfg.cards_size());
		for(int i = 0; i < cfg.cards_size(); ++i)
		{
			cardbag.push_back(CardItem(0, cfg.cards(i).id(), cfg.cards(i).star(), e_card_common));
		}

		vector<unsigned> heros;
		heros.reserve(MAX_FORMATION_HERO);
		for(auto& e : attrItem)
			heros.push_back(e.id);

		CreatNpcCardBag(battleid, item.grade, heros, cardbag);

		//获取手牌
		vector<CardItem>& handcards = DGI->GetHandCards(battleid, item.grade);
		vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, item.grade);
		vector<CardItem> tempcards  = DGI->GetTempCards(battleid, item.grade);

		//随机从战斗卡包中抽牌组成手牌
		CreateHandCard(handcards, cardbags, tempcards);

	}

	return R_SUCCESS;
}

unsigned GameGrade::MatchUser(unsigned uid, unsigned grade, int& index)
{
	unsigned ret = 0;
	auto& cfg = RoBotCfgWarp().GetGradeRobotByGrade(grade);

	if(UserGradeManager::Instance()->GetMap().size() < GRADE_BATTLE_USER)
	{
		ret = UserGradeManager::Instance()->GetUserRandom(uid, grade, cfg.item_size());
		if(!IsValidUid(ret))
		{
			index = ret;
			ret = 0;
		}
	}
	else
	{
		ret = LogicUserGradeManager::Instance()->Match(uid, grade);
	}

	return ret;
}


void GameGrade::GameEnd(unsigned battleid)
{
	auto& data = DGI->GetData(battleid);
	auto& gradeItem = LogicUserGradeManager::Instance()->Get(data.att.uid);
	if(data.AttackerWin())
	{
		gradeItem.IncWin();
		int index = LogicUserGradeManager::Instance()->GetWinIdex(gradeItem.Win());
		if(-1 != index && !gradeItem.Streaking(index))
		{
			ProtoPush::PushWinstreak* msg = new ProtoPush::PushWinstreak;
			msg->set_count(gradeItem.Win());
			//推送连胜消息
			LogicManager::Instance()->sendMsg(data.att.uid, msg);
			gradeItem.Streaking(index, true);
		}
	}
	else
	{
		gradeItem.ClearWin();
	}

	ProtoBattle::ProtoGradeBattleResult* resp = new ProtoBattle::ProtoGradeBattleResult;
	gradeItem.SetMessage(resp);

	LogicManager::Instance()->sendMsg(data.att.uid, resp);
	DataGameManager::Instance()->Clear(battleid);
}

int GameRandom::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{
	if(InitUserItem(uid, battleid) != R_SUCCESS)
	{
		error_log("init user item failed, uid=%u", uid);
		return R_ERROR;
	}

	if(random_.count(uid) == 0)
	{
		error_log("enemy empty, uid:%u", uid);
		return R_ERROR;
	}

	unsigned othuid = random_[uid];
	if(!IsValidUid(othuid))
	{
		error_log("othuid is invalid, uid=%u, othuid=%u", uid, othuid);
	}


	InitOthItem(othuid, battleid);

	ProtoBattle::ProtoRandomUserResp* resp = dynamic_cast<ProtoBattle::ProtoRandomUserResp*>(message);

	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_random, resp->mutable_common());

	return R_SUCCESS;
}

void GameRandom::GameEnd(unsigned battleid)
{
	auto& data =DGI->GetData(battleid);

	CommonGiftConfig::CommonModifyItem cfg;
	unsigned uid 	= data.att.uid;
	unsigned othuid = random_[uid];
	if(data.AttackerWin())
		RandomUserReward(othuid, othuid, cfg);

	revenge_[othuid] = uid;
	random_.erase(uid);
	revenge_.erase(uid);

	ProtoBattle::ProtoRandomUserResult* resp = new ProtoBattle::ProtoRandomUserResult;
	LogicUserManager::Instance()->CommonProcess(uid,cfg,"random_battle",resp->mutable_commons());

	LogicManager::Instance()->sendMsg(uid, resp);
	DataGameManager::Instance()->Clear(battleid);
}


unsigned GameRandom::RefreshUser(unsigned uid)
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

unsigned GameRandom::SelectUser(unsigned uid, set<unsigned>& users)
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


int GameRandom::RandomUserReward(unsigned uid, unsigned othuid, CommonGiftConfig::CommonModifyItem& cfg)
{
	vector<unsigned>& formation = LogicBattleManager::Instance()->GetFormation(uid);

	if(formation.empty())
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


	if(othuid == 0)
		return 0;

	//加载对方数据
	OffUserSaveControl  offuserCtl(othuid);
	DBCUserBaseWrap enemyWrap(uid);

	DataBase& enemy = enemyWrap.Obj();
	if(enemy.honor >= PER_HONOR)
		enemyWrap.CostHonor(-PER_HONOR, "random_user");


	set<unsigned> tmp(formation.begin(), formation.end());
	vector<unsigned> other;
	vector<unsigned> vIndexs;
	DataHeroManager::Instance()->GetIndexs(othuid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DataHero& hero = DataHeroManager::Instance()->GetDataByIndex(vIndexs[i]);
		unsigned heroId = hero.id;
		vector<unsigned> chips = CMI->archive_chip[heroId];
		for(int i = 0; i < chips.size(); ++i)
		{
			unsigned ud = DataItemManager::Instance()->GetPropsUd(othuid, chips[i]);
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
		unsigned ud = DataItemManager::Instance()->GetPropsUd(othuid, propId);
		if(-1 == ud)
		{
			error_log("props not exist. uid=%u,propsid=%u", uid, propId);
			throw runtime_error("props_not_exist");
		}
		//掉落对手图鉴
		LogicPropsManager::Instance()->CostProps(othuid, ud, propId, 1, "random_user_battle");
	}

	//玩家获得图鉴
	auto prop = cfg.add_props();
	prop->set_count(1);
	prop->set_id(propId);

	return R_SUCCESS;
}

int GameFriend::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{
	if(InitUserItem(uid, battleid) != R_SUCCESS)
	{
		error_log("init user item failed, uid=%u", uid);
		return R_ERROR;
	}

	if(friend_.count(uid) == 0)
	{
		error_log("friend empty, uid:%u", uid);
		return R_ERROR;
	}

	unsigned othuid = friend_[uid];
	if(!IsValidUid(othuid))
	{
		error_log("othuid is invalid, uid=%u, othuid=%u", uid, othuid);
	}

	InitOthItem(othuid, battleid);

	ProtoBattle::ProtoFriendBattleResp* resp = dynamic_cast<ProtoBattle::ProtoFriendBattleResp*>(message);
	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_friend, resp->mutable_common());

	return R_SUCCESS;
}

void GameFriend::GameEnd(unsigned battleid)
{
	CommonGiftConfig::CommonModifyItem cfg;
	auto& data = DGI->GetData(battleid);
	unsigned uid = data.att.uid;
	vector<unsigned>& fromation = LogicBattleManager::Instance()->GetFormation(uid);

	ProtoBattle::ProtoFriendBattleResult* resp = new ProtoBattle::ProtoFriendBattleResult;
	FriendBattleReward(uid, data.AttackerWin(), fromation, cfg, resp);
	LogicUserManager::Instance()->CommonProcess(uid, cfg, "friend_battle", resp->mutable_commons());

	DBCFriendWrap friendWrap(uid, data.def.uid);
	friendWrap.UpdateBattle(data.AttackerWin() ? e_friendbattle_win : e_friendbattle_lose);

	LogicManager::Instance()->sendMsg(uid, resp);
	DataGameManager::Instance()->Clear(battleid);
}


void GameFriend::FriendBattleReward(unsigned uid, bool attckerWin, vector<unsigned>& heros, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoFriendBattleResult* msg)
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
	for(auto& id : heros)
	{
		DBCHeroWrap data(uid, id);
		//加经验
		if(data.Obj().exp + heroExp < heroMaxExp)
			data.AddExp(heroExp);
	}

	//消耗体力
	cfg.mutable_based()->set_power(power);
}

int GameMartialClub::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{

	if(info_.count(uid) == 0)
	{
		error_log("martial battle info empty, uid=%u, battleid=%u", uid, battleid);
		return R_ERROR;
	}
	if(info_[uid].othAttr.empty())
	{
		error_log("other no hero, uid=%u, battleid=%u", uid, battleid);
		return R_ERROR;
	}

	if(InitUserItem(uid, info_[uid].mymGrde, battleid) != R_SUCCESS)
	{
		error_log("init user item failed, uid=%u", uid);
		return R_ERROR;
	}

	InitOthItem(info_[uid].othuid, battleid, info_[uid].othAttr);

	ProtoBattle::ProtoMartialClubBattleResp* resp = dynamic_cast<ProtoBattle::ProtoMartialClubBattleResp*>(message);
	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_martial, resp->mutable_common());

	return LMI->sendMsg(uid, resp) ? R_SUCCESS : R_ERROR;
}

void GameMartialClub::GameEnd(unsigned battleid)
{
	auto& data = DGI->GetData(battleid);
	CommonGiftConfig::CommonModifyItem cfg;
	unsigned uid = data.att.uid;
	auto& info = info_[uid];

	if(data.AttackerWin())
	{
		cfg.mutable_based()->set_coin(info.othCoins / 2);
		info.othProtectTs = Time::GetGlobalTime() + MARTIAL_BATTLE_PROTECT_TS;

		for(auto& e : info.othProps)
		{
			auto prop = cfg.add_props();
			prop->set_count(e.second/2);
			prop->set_id(e.first);

			e.second /= 2;

		}
		info.othCoins /= 2;
		info.othProtectTs = Time::GetGlobalTime() + MARTIAL_BATTLE_PROTECT_TS;
		ProtoBattle::ProtoMartialClubBattleResult* resp = new ProtoBattle::ProtoMartialClubBattleResult;
		LogicUserManager::Instance()->CommonProcess(uid, cfg, "martial_battle", resp->mutable_commons());
		LogicManager::Instance()->sendMsg(uid, resp);


		DBCUserBaseWrap user(uid);
		user.IncDailyBattleCount();
		//战报
		BattleReport(battleid);
	}

}

int GameMartialClub::InitUserItem(unsigned uid, unsigned grade, unsigned battleid)
{
	auto& club = DataMartialClubManager::Instance()->GetData(uid, grade);
	vector<unsigned> vIndexs;
	DataMartialHeroManager::Instance()->GetIndexs(uid, vIndexs);

	for(auto& index : vIndexs)
	{
		auto& hero = DataMartialHeroManager::Instance()->GetDataByIndex(index);
		if(hero.id / 10 == grade)
		{
			HeroAttrItem temp(hero.id, hero.hp, hero.att, hero.def, hero.crit, hero.acrit, hero.dodge,
								hero.adodge, hero.critt, hero.speed, hero.battlePower, 0);

			if(DGI->SetHeroAttr(uid, battleid, temp.id, temp) != R_SUCCESS)
			{
				error_log("set hero attribute failed, uid=%u, ret=%u", uid);
				return R_ERROR;
			}
		}
	}

	//随机充卡池中抽取卡牌组成战斗卡包
	CreateUserCardBag(battleid, uid);
	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}

int GameMartialClub::InitOthItem(unsigned uid, unsigned battleid, vector<HeroAttrItem>& info)
{
	for(auto& hero : info)
	{
		HeroAttrItem temp(hero.id, hero.hp, hero.att, hero.def, hero.crit, hero.acrit, hero.dodge,
									hero.adodge, hero.critt, hero.speed, hero.battlePower, 0);

		if(DGI->SetHeroAttr(uid, battleid, temp.id, temp) != R_SUCCESS)
		{
			error_log("set hero attribute failed, uid=%u, ret=%u", uid);
			return R_ERROR;
		}
	}

	//随机充卡池中抽取卡牌组成战斗卡包
	CreateUserCardBag(battleid, uid);
	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}

void GameMartialClub::BattleReport(unsigned battleid)
{
	auto& data = DGI->GetData(battleid);
	auto& info = info_[battleid];
	auto& user = BaseManager::Instance()->Get(data.att.uid);
	//战报
	MartialClubItem postItem;
	postItem.type 	= e_post_martialBattle;
	postItem.ts 	= Time::GetGlobalTime();
	postItem.grade  = info.mymGrde;
	postItem.level  = user.level;
	postItem.uuid   = data.att.uid;
	postItem.win   	= data.AttackerWin() ? 1 : 0;
	memcpy(postItem.fig, user.fig, sizeof(postItem.fig));
	memcpy(postItem.name, user.name, sizeof(postItem.name));
	LogicPostManager::Instance()->AddPost(data.def.uid, postItem);
	if(UserManager::Instance()->IsOnline(data.def.uid))
	{
		ProtoNotify::PushMartialBattlePost* msg = new ProtoNotify::PushMartialBattlePost;
		postItem.SetMessage(msg->mutable_post());
		LMI->sendMsg(data.def.uid, msg);
	}
}

map<unsigned, unsigned> GameMartialClub::GetMartialClubProp(vector<unsigned>&& in)
{
	map<unsigned, unsigned> out;
	auto& propIndex = LogicMartialClubManager::Instance()->GetPropsIndex();
	for(auto& e : propIndex)
		out.insert({e.first, in[e.second]});

	return out;
}


int GameMartialClub::SynOthMartialInfo(unsigned battleid)
{
	auto& data = DGI->GetData(battleid);
	auto& info = info_[data.att.uid];

	ProtoBattle::ProtoCSSynOthMartialInfo* msg = new ProtoBattle::ProtoCSSynOthMartialInfo;
	msg->set_othuid(info.othuid);
	msg->set_othmgrade(info.othmGrade);
	msg->set_othcoins(info.othCoins);
	msg->set_othprotectts(info.othProtectTs);

	for(auto& e : info.othProps)
	{
		auto prop = msg->add_othprops();
		prop->set_id(e.first);
		prop->set_count(e.second);
	}

	return ProtoManager::BattleConnectNoReplyByUID(data.def.uid, msg);
}

int GameChampionship::GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message)
{
	ProtoBattle::ProtoPveBattleResp* resp = dynamic_cast<ProtoBattle::ProtoPveBattleResp*>(message);
	resp->set_battleid(battleid);
	SendCard(uid, battleid, e_battletype_championship, resp->mutable_common());

	return R_SUCCESS;
}

void GameChampionship::GameEnd(unsigned battleid)
{
	auto& data = DGI->GetData(battleid);
	if(data.AttackerWin())
		data.SetWinner(att_win);
	else
		data.SetWinner(def_win);
}

int GameChampionship::InitUserItem(unsigned uid, unsigned battleid, unsigned heroid)
{
	auto& base = BaseManager::Instance()->Get(uid);
	//添加玩家到比赛
	int ret = DataGameManager::Instance()->AddUser(uid, battleid, base.level);
	if(ret != R_SUCCESS)
	{
		error_log("add user error, uid=%u, ret=%u", uid, ret);
		return ret;
	}
	//设置英雄属性
	HeroAttrItem attr;
	attr.id = heroid;
	LogicHeroManager::Instance()->GetHeroAttr(uid, heroid, attr);
	attr.n_hp = attr.hp;
	ret = DataGameManager::Instance()->SetHeroAttr(uid, battleid, heroid, attr);
	if(ret != R_SUCCESS)
	{
		error_log("set hero attribute failed, uid=%u, ret=%u", uid, ret);
		return ret;
	}

	//随机从卡池里抽牌组成战斗卡包
	CreateUserCardBag(battleid, uid);

	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}


int GameChampionship::InitNpcItem(unsigned uid, unsigned battleid, unsigned heroid)
{
	auto& robotCfg = RoBotCfgWarp().GetChampionRobotById(uid);
	NpcCfgWarp npcCfg;
	vector<unsigned> npchero(1, heroid);
	for(auto& hero : robotCfg.npc())
	{
		unsigned heroid = hero.id();
		auto& lattr = npcCfg.GetNpcById(heroid).attr().levelattr(hero.level());
		auto& cattr = npcCfg.GetNpcById(heroid).attr();

		unsigned battlePow = 100 + lattr.att()/2 + lattr.hp()/10 + lattr.def();
		HeroAttrItem attr(heroid, lattr.hp(), lattr.att(), lattr.def(), cattr.critstrike(), cattr.critresist(),
				cattr.dodge(), cattr.hit(), cattr.critrate()/(double)100, lattr.first(), battlePow, 0);

		DataGameManager::Instance()->SetHeroAttr(uid, battleid, heroid, attr);
	}
	//随机从卡池里抽牌组成战斗卡包
	vector<CardItem> cardbag;
	cardbag.reserve(robotCfg.cards_size());
	for(int i = 0; i < robotCfg.cards_size(); ++i)
	{
		cardbag.push_back(CardItem(0, robotCfg.cards(i).id(), robotCfg.cards(i).star(), e_card_common));
	}

	CreatNpcCardBag(battleid, uid, npchero, cardbag);

	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	//随机从战斗卡包中抽牌组成手牌
	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}

int GameChampionship::Apply()
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
					DGI->GetData(battleid).Clear(battleid);
				rewards_.erase(mid);

				return R_ERROR;
			}

			//加到开始比赛队列
			match_start_.insert({mid, battles});

			//加到第一轮比赛
			Ready(mid);

			//加到第一轮比赛队列
			turn_1_.push_back(mid);
		}

	}

	return R_SUCCESS;
}

int GameChampionship::Ready(unsigned mid)
{
	//TODO: 广播玩家信息
	auto& battles = match_start_[mid];
	ProtoChampionship::MatchInfoCPP matchMsg;
	vector<unsigned> players;
	players.reserve(battles.size()*2);
	for(auto& battleid : battles)
	{
		auto& data = DGI->GetData(battleid);
		players.push_back(data.att.uid);
		LogicChampionshipManager::Instance()->SetMessage(data.att.uid, battleid, data.att.attr[0].id, matchMsg.add_players());
		players.push_back(data.def.uid);
		LogicChampionshipManager::Instance()->SetMessage(data.def.uid, battleid, data.def.attr[0].id, matchMsg.add_players());
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
		auto& data = DGI->GetData(*it);
		unsigned attUid = data.att.uid;
		unsigned defUid = data.def.uid;
		if(!IsValidUid(attUid) && !IsValidUid(defUid))
		{
			//根据概率随机决定胜利方
			auto& robot1 = robotCfg.GetChampionRobotById(attUid);
			auto& robot2 = robotCfg.GetChampionRobotById(defUid);
			int index = ::abs(robot1.level() - robot2.level()) % 10 - 1;
			if (robotCfg.Championship().prob_size() > index)
			{
				int random =  Math::GetRandomInt(100);
				int prob   =  robotCfg.Championship().prob(index);
				if(robot1.level() < robot2.level())
				{
					if(random < prob)
						data.SetWinner(att_win);
					else
						data.SetWinner(def_win);
				}
				else
				{
					if(random < prob)
						data.SetWinner(def_win);
					else
						data.SetWinner(att_win);
				}
			}
			else
			{
				if(robot1.level() < robot2.level())
					data.SetWinner(att_win);
				else
					data.SetWinner(def_win);
			}
		}
	}

	return R_SUCCESS;
}

bool GameChampionship::Start(unsigned mid)
{
	bool isOver = false;
	auto& battles = match_start_[mid];

	//已经结束的比赛数
	int overCount = 0;
	for(auto it = battles.begin(); it != battles.end(); ++it)
	{
		unsigned battleid = *it;
		auto& data = DGI->GetData(battleid);
		//TODO: 超时的比赛,暂定为60s
		if(data.Winner() == 0)
		{
			if(Time::GetGlobalTime() - data.LastOutCardTs() > 60)
			{
				if(data.CurrentPlayer() == e_att)
					data.SetWinner(att_win);
				else
					data.SetWinner(def_win);
			}
		}

		if(data.Winner() != 0)
			++overCount;
	}

	//所有的比赛都结束时，本轮比赛结束
	if(overCount == battles.size())
	{
		if(overCount > 1)
		{
			for(auto it = battles.begin(); it != battles.end();)
			{
				auto first = it;
				auto second = ++it;

				auto& data1 = DGI->GetData(*first);
				unsigned attUid = 0;
				unsigned attHero = 0;
				if(data1.AttackerWin())
				{
					attUid = data1.att.uid;
					attHero = data1.att.attr[0].id;
				}
				else
				{
					attUid = data1.def.uid;
					attHero = data1.def.attr[0].id;
				}

				auto& data2 = DGI->GetData(*second);
				unsigned defUid = 0;
				unsigned defHero = 0;

				if(data2.AttackerWin())
				{
					defUid = data2.att.uid;
					defHero = data2.att.attr[0].id;
				}
				else
				{
					defUid = data2.def.uid;
					defHero = data2.def.attr[0].id;
				}
				unsigned battleid = 0;
				if(R_ERROR == AddGame(attUid, attHero, defUid, defHero, battleid))
					throw runtime_error("add_game_failed");

				*first = battleid;
				DGI->Clear(*second);

				it = battles.erase(second);
			}

		}
		isOver = true;
	}

	return isOver;
}


int GameChampionship::Over(unsigned mid)
{
	if(match_start_[mid].size() != 1)
	{
		error_log("championship, logic error");
		throw runtime_error("championship_logic_error");
	}
	unsigned battleid = match_start_[mid].front();
	auto& data = DGI->GetData(battleid);

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
	DGI->Clear(battleid);

	return R_SUCCESS;
}

int GameChampionship::AddGame(unsigned attUid, unsigned attHero, unsigned defUid, unsigned defHero, unsigned& battleid)
{
	battleid = DataGameManager::Instance()->CreateGame();
	if(battleid == (unsigned)-1)
	{
		error_log("create championship failed");
		return R_ERROR;
	}

	int ret = 0;
	if(IsValidUid(attUid))
		ret = InitUserItem(attUid, battleid, attHero);
	else
		ret = InitNpcItem(attUid, battleid, attHero);

	if(ret != R_SUCCESS)
	{
		error_log("init user error");
		return R_ERROR;
	}


	if(IsValidUid(defUid))
		ret = InitUserItem(defUid, battleid, defHero);
	else
		ret = InitNpcItem(defUid, battleid, defHero);

	if(ret != R_SUCCESS)
	{
		error_log("init user error");
		return R_ERROR;
	}

	return R_SUCCESS;
}


void GameChampionship::GameProcess()
{
	Turn(turn_1_, turn_2_);
	Turn(turn_2_, turn_3_);
	Turn(turn_3_, turn_3_);
}

vector<int> GameChampionship::RandomRobots()
{
	vector<int> res;
	res.reserve(CHAMPIONSHIP_PER_ROBOTS);
	auto& cfg = RoBotCfgWarp().Championship();
	unsigned size = cfg.item_size();
	LogicCommonUtil::GetRandoms(0, size - 1, CHAMPIONSHIP_PER_ROBOTS, res);

	return res;
}


void GameChampionship::Turn(list<unsigned>& cur, list<unsigned>& next)
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
				DGI->GetData(battleid).Clear(battleid);

			match_start_.erase(mid);
			it = cur.erase(it);
		}

	}
}

