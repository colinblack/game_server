#include "LogicHeroManager.h"

DBCHeroWrap::DBCHeroWrap(unsigned index)
	: container_(DataHeroManager::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{
}


DBCHeroWrap::DBCHeroWrap(unsigned uid, unsigned heroid)
	: container_(DataHeroManager::Instance())
	, index_(container_->GetIndex(uid, heroid))
	, data_(container_->m_data->data[index_])
{

}

bitset<32> DBCHeroWrap::combine_limit;

void DBCHeroWrap::FullMessage(ProtoHero::HeroBaseInfoCPP * hero, unsigned extra)
{

	if(DataDetachHeroManager::Instance()->IsExistItem(data_.uid, data_.id))
	{
		DataDetachHero& detach = DataDetachHeroManager::Instance()->GetData(data_.uid, data_.id);
		hero->set_detachuid(detach.detach_uid);
		hero->set_detachslot(detach.detach_slot);
	}

	if(extra == 1)
		data_.SetMessage(hero);
	GetAttr(hero_attr_);
	hero_attr_.FullMessage(hero);

}
void DBCHeroWrap::SetMessage(ProtoHero::HeroBaseInfoCPP * hero)
{
	hero->set_heroid(data_.id);
	hero_attr_.FullMessage(hero);
}

bool DBCHeroWrap::AddExp(int exp)
{
	unsigned old_lvl = data_.level;
	if(exp > 0)
	{
		data_.AddExp(exp);

		if(data_.level > old_lvl)
		{
			//英雄升级推送
			data_.base_power = (unsigned)BaseBattlePower();
			data_.battle_power = BattlePower();
			ProtoPush::PushHeroUpLevel *msg = new ProtoPush::PushHeroUpLevel;
			FullMessage(msg->mutable_hero());
			LogicManager::Instance()->sendMsg(data_.uid, msg);
			std::string open_id = UserManager::Instance()->GetOpenId(data_.uid);
			HERO_LOG("[upgrade]uid=%u,open_id=%s,old_level=%d,new_level:%d"
					, data_.uid, open_id.c_str(), old_lvl, data_.level);
		}

		Save();
		return true;
	}

	return false;
}

void DBCHeroWrap::UpdateSkillLevel(unsigned skillId)
{
	if(skillId > 3)
		return;
	data_.skill[skillId] += 1;

	unsigned level = data_.skill[skillId];
	//更新战力
	data_.skill_power =  HeroCfgWrap().GetHeroByHeroId(data_.id).skill(skillId).skillinfo(level-1).fight_power();
	data_.battle_power = BattlePower();
	Save();
}

bool DBCHeroWrap::ActDragonBall(int idx)
{
	if(idx > MAX_DRAGON_BALL_INDEX && idx < 0)
		return false;

	if(DragonBallIsAct(idx))
		return false;
	unsigned index = idx;
	data_.dragon_ball |= (1 << index);
	Save();

	return true;
}

bool DBCHeroWrap::DragonBallIsAct(int idx)
{
	if((data_.dragon_ball & (unsigned)(1 << idx)) == 0)
		return false;
	return true;
}

bool DBCHeroWrap::DragonBallAllAct()
{
	unsigned mark = 0;
	for(int i = 0; i <= MAX_DRAGON_BALL_INDEX; ++i)
	{
		mark = data_.dragon_ball & (1 << i);
		if(mark == 0)
			return false;
	}
	return true;
}

void DBCHeroWrap::UpdateStar(unsigned starid)
{
	if(starid < 1 || starid > MAX_STAR_NUM)
		return;
	data_.star |= (1 << (starid-1));

	//更新战力
	data_.star_power += StarsCfgWarp().GetStarsInfoById(data_.id).list(starid-1).fight_power();
	data_.battle_power = BattlePower();

	Save();
}

int DBCHeroWrap::GetAttr(HeroAttr& result)
{
	result.Clear();
	unsigned uid = data_.uid;
	unsigned heroid = data_.id;
	unsigned level	= data_.level;
	try
	{
		//获取百分比加成
		map<unsigned, double> addition_percent;
		//获取其他属性增加值
		map<unsigned, unsigned>	addition_value;
		//星级属性
		const Stars::HeroWithStars& stars = StarsCfgWarp().GetStarsInfoById(heroid);

		unsigned star = data_.star;
		for(int i = 0; i < stars.list_size() && i < MAX_STAR_NUM; ++i)
		{
			if(0 != (star & (i << 1)))
			{
				result.AddtionValue(addition_value, stars.list(i).attr());
				result.AddtionPercent(addition_percent, stars.list(i).attr());
			}

		}
		//龙珠属性
		const DragonBall::HeroWithDragonBall& dragon_ball = DragonBallCfgWarp().GetDragonBallInfoById(heroid);

		unsigned dragon = data_.dragon_ball;
		for(int i = 0; i < dragon_ball.list_size() && i <= MAX_DRAGON_BALL_INDEX; ++i)
		{
			if(0 != (dragon & (i << 1)))
			{
				result.AddtionValue(addition_value, dragon_ball.list(i).attr());
				result.AddtionPercent(addition_percent, dragon_ball.list(i).attr());
			}

		}

		//图鉴属性
		DataBase& user = BaseManager::Instance()->Get(uid);
		ArchiveCfgWarp archiveCfg;
		for(int i = 0; i < ARCHIVE_LENGTH; ++i)
		{
			unsigned archiveLevel = user.archive_level[i];
			if(archiveLevel > 0)
			{
				const Archive::HeroWithArchive& archive = archiveCfg.GetArchiveInfoInfoById(i+1);
				result.AddtionValue(addition_value, archive.levelattr(archiveLevel-1).attr());
				result.AddtionPercent(addition_percent, archive.levelattr(archiveLevel-1).attr());
			}
		}

		//组合属性
		vector<unsigned>& formation = LogicBattleManager::Instance()->GetFormation(data_.uid);

		if(!formation.empty() && 0 != combine_limit.count())
		{
			set<unsigned> tmp(formation.begin(), formation.end());
			auto& cfg = CombineCfgWrap().GetCombineByHeroId(tmp);
			for(int i= 0; i < cfg.list_size(); ++i)
			{
				if(!combine_limit.test(i))
					continue;
				result.AddtionValue(addition_value, cfg.list(i));
				result.AddtionPercent(addition_percent, cfg.list(i));
			}
		}

		result.SetAllAttr(addition_percent, addition_value, heroid, level);
	}
	catch(std::exception& e)
	{
		error_log("uid:%u, heroid: %d, error: %s", uid, heroid, e.what());
	}

	return R_SUCCESS;
}

void DBCHeroWrap::GetSkill(vector<char>& skills)
{
	skills.clear();
	vector<char> tmp(data_.skill, data_.skill+HERO_SKILL_LENGTH);
	skills = tmp;
}

void DBCHeroWrap::SetCombineLimit(int idx)
{
	combine_limit.set(idx, 1);
}

void DBCHeroWrap::ResetCombineLimit()
{
	combine_limit.reset();
}

double DBCHeroWrap::BaseBattlePower()
{
	HeroAttr attr;
	GetAttr(attr);
	double hp	=  static_cast<double>(attr.GetAttr(HeroProperty_hp));
	double att	=  static_cast<double>(attr.GetAttr(HeroProperty_attack));
	double def  =  static_cast<double>(attr.GetAttr(HeroProperty_defend));

	return  (100 + att/2 + hp/10 + def);
}

unsigned DBCHeroWrap::BattlePower()
{
	return (data_.base_power + data_.skill_power + data_.star_power + data_.dragon_power + data_.archive_power);
}


/*轻拳:60, 中拳:29, 重拳:10, 暴击:1*/
const unsigned LogicHeroManager::initWeight[4] = {60, 29, 10, 1};


int LogicHeroManager::FullMessage(unsigned uid, User::HerosInfo * herosmsg)
{
	vector<unsigned> vIndexs;
	DataHeroManager::Instance()->GetIndexs(uid, vIndexs);
	for(int i = 0; i < (int)vIndexs.size(); ++i)
	{
		DBCHeroWrap hero(vIndexs[i]);
		unsigned heroid = hero.Obj().id;
		try
		{
			hero.FullMessage(herosmsg->add_hero());
		}
		catch( const std::exception& e)
		{
			error_log("uid: %u,heroid: %d, %s", uid, heroid, e.what());
		}
	}

	return 0;
}

int LogicHeroManager::AddHeros(unsigned uid, unsigned heroid, string reason)
{
	bool is_exist = DataHeroManager::Instance()->IsExistItem(uid, heroid);
	if(is_exist)
	{
		error_log("hero is exist uid: %u, heroid: %u", uid, heroid);
		throw runtime_error("hero_is_exist");
	}

	//激活英雄相关图鉴属性
	DBCUserBaseWrap user(uid);
	if(!user.GetArchive(heroid))
	{
		error_log("act archive error uid: %u, heroid: %u", uid, heroid);
		throw runtime_error("act_archive_error");
	}

	DBCHeroWrap addHero(uid, heroid);

	addHero.Obj().id = heroid;
	addHero.Obj().uid = uid;
	//更新战力
	double battlePower =  ArchiveCfgWarp().GetArchiveInfoInfoById(heroid).levelattr(0).attr().fight_power();

	auto & heroCfg = HeroCfgWrap().GetHeroByHeroId(heroid);
	for(int i = 0; i < HERO_SKILL_LENGTH; ++i)
		battlePower += heroCfg.skill(i).skillinfo(0).fight_power();

	addHero.Obj().base_power = (unsigned)addHero.BaseBattlePower();
	addHero.Obj().battle_power = addHero.Obj().base_power;
	addHero.Save();

	HERO_LOG("uid=%u,id=%u,act=%s, code=%s", uid, heroid, "Add", reason.c_str());

	return 0;
}

void LogicHeroManager::GetSkill(unsigned uid, unsigned id, HeroInfo& hero)
{
	vector<char> skills;
	DBCHeroWrap heroWrap(uid, id);
	heroWrap.GetSkill(skills);
	auto& hero_cfg =  HeroCfgWrap().GetHeroByHeroId(id);
	int skillLv = 1;
	double multiple = 0.0;
	for(int i = 0; i < e_skill_max; ++i)
	{
		skillLv = skills[i];
		hero.skills[i].type 	= i;
		hero.skills[i].id 		= hero_cfg.skill(i).id();
		hero.skills[i].multiple	= hero_cfg.skill(i).skillinfo(skillLv-1).multiple();
		hero.skills[i].hurt 	= hero_cfg.skill(i).skillinfo(skillLv-1).hurtvalue();
		hero.skills[i].initWeight = LogicHeroManager::initWeight[i];
		hero.skills[i].userAddWeight = AddWeightCfgWarp().GetPlayerAddWeightBylevel(skillLv).weight(i); //玩家等级增加权重
	}
}

/*
pair<int, int> LogicHeroManager::DropDragonBall(unsigned stageId, vector<unsigned>& heroid)
{
	const Stages::AllStage& stageCfg =  StagesCfgWarp().GetStagesInfoById(stageId);
	map<unsigned, unsigned> dragon;
	for(int i = 0; i < stageCfg.dragon_size(); ++i)
	{
		dragon[stageCfg.dragon(i).heroid()] = stageCfg.dragon(i).idx();
	}

	vector<pair<int,int>> drop;
	for(int i = 0; i < heroid.size(); ++i)
	{
		if(dragon.count(heroid[i]))
		{
			drop.push_back(make_pair<int, int>(heroid[i], dragon[heroid[i]]));
		}
	}

	int maxSize = drop.size();

	if(maxSize > 0)
	{
		unsigned idx = Math::GetRandomInt(maxSize);

		//掉落的龙珠所属英雄参加了战斗
		auto it = std::find(heroid.begin(), heroid.end(), drop[idx].first);
		if(it != heroid.end())
		{
			return drop[idx];
		}
	}

	return std::make_pair(-1, -1);
}
*/


int LogicHeroManager::Process(unsigned uid, ProtoHero::BuyHeroReq* req, ProtoHero::BuyHeroResp* resp)
{
	unsigned heroid = req->heroid();
	bool is_exist = DataHeroManager::Instance()->IsExistItem(uid, heroid);
	if(is_exist)
	{
		error_log("hero is exist uid: %u, heroid: %u", uid, heroid);
		throw runtime_error("hero_is_exist");
	}

	//是否达满足解锁条件
	auto& heroCfg = HeroCfgWrap().GetHeroByHeroId(heroid);
	DataBase& user = BaseManager::Instance()->Get(uid);

    if(heroCfg.has_unlocklevel())
    {
    	if(user.level < heroCfg.unlocklevel())
    	{
    		error_log("hero unlock uid: %u userlevel: %u, unlocklevel: %u", uid, user.level, heroCfg.unlocklevel());
    		throw runtime_error("hero_unlock_error");
    	}
    }
    else if(heroCfg.has_unlockdaynum())
    {
    	if(user.login_days < heroCfg.unlockdaynum())
    	{
    		error_log("hero unlock uid: %u login_days: %u, unlockdaynum: %u", uid, user.login_days, heroCfg.unlockdaynum());
    		throw runtime_error("hero_unlock_error");
    	}
    }
    else if(heroCfg.has_unlockheronum())
    {
    	vector<unsigned> vIndexs;
    	DataHeroManager::Instance()->GetIndexs(uid, vIndexs);
    	if(vIndexs.size() < heroCfg.unlockheronum())
    	{
    		error_log("hero unlock uid: %u heronum: %u, unlockheronum: %u", uid, vIndexs.size(), heroCfg.unlockheronum());
    		throw runtime_error("hero_unlock_error");
    	}
    }

	auto& cost = heroCfg.cost();
	int coin = cost.based().coin();
	int cash = cost.based().cash();

	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_coin(coin);
	cfg.mutable_based()->set_cash(cash);

	LogicUserManager::Instance()->CommonProcess(uid, cfg, "buy_hero", resp->mutable_commons());
	AddHeros(uid, heroid, "buy_hero");
	DBCHeroWrap herowrap(uid, heroid);
	herowrap.FullMessage(resp->mutable_hero());

	//添加卡牌
	cfg.Clear();
	auto& cardCfg  = HeroCfgWrap().GetCardsByHeroId(heroid);
	int payCoin = 0;
	for(int i = 0; i < cardCfg.cardid_size(); ++i)
	{
		int cardid = cardCfg.cardid(i);
		if(LogicCardsManager::Instance()->AddCards(uid, cardid, "buy_hero", resp->mutable_cards()) != R_SUCCESS)
		{
			payCoin += CardsCfgWrap().GetCardsCfgById(cardid).coin();
		}
	}
	if(payCoin > 0)
	{
		cfg.mutable_based()->set_coin(payCoin);
		LogicUserManager::Instance()->CommonProcess(uid, cfg, "buy_heor_card_pay", resp->mutable_pay());
	}

	return 0;
}


int LogicHeroManager::Process(unsigned uid, ProtoHero::UpgradeHeroByCoinReq* req, ProtoHero::UpgradeHeroByCoinResp* resp)
{
	unsigned oneclick = req->oneclick();
	if(oneclick != 0 && oneclick != 1)
	{
		error_log("param error uid = %u, oneclick = %u", uid, oneclick);
		throw std::runtime_error("param_error");
	}
	int user_level = DBCUserBaseWrap(uid).Obj().level;

	unsigned heroid = req->heroid();
	DBCHeroWrap herowrap(uid, heroid);
	uint64_t hero_exp = herowrap.Obj().exp;
	unsigned herolevel = herowrap.Obj().level;
	if(herolevel >= user_level)
	{
		error_log("hero level upper than user. uid=%u,heroid=%u", uid, heroid);
		throw std::runtime_error("hero_level_error");
	}

	unsigned max_hero_level = HeroCfgWrap().Hero().levelexp_size();
	if(herolevel >= max_hero_level)
	{
		error_log("hero level max. uid=%u,heroid=%u", uid, heroid);
		throw std::runtime_error("hero_level_max");
	}

	//当前等级初始经验
	uint64_t curr_exp =ConfigManager::Instance()->hero_level_exp[herolevel-1];
	unsigned max_exp  = ConfigManager::Instance()->hero_level_exp[max_hero_level-1];
	unsigned curr_level = herolevel;
	unsigned next_level = curr_level+1;
	auto& nextLvelCfg = HeroCfgWrap().GetHeroByLevel(next_level);
	uint64_t next_exp = ConfigManager::Instance()->hero_level_exp[next_level-1];
	double next_coin = -nextLvelCfg.coin();
	double per_coin = (next_exp - curr_exp)/next_coin;
	int cost = (int)ceil(per_coin * (next_exp - hero_exp));

	DBCUserBaseWrap userWrap(uid);
	int coin =  userWrap.Obj().coin;
	if(cost > coin)
	{
		error_log("coin is not enough. cost =%u,coin=%u", cost, coin);
		throw std::runtime_error("coin_not_enough");
	}

	while(1)
	{
		if(curr_level >= max_hero_level || curr_level >= user_level)
			break;
		if(curr_exp > max_exp)
			break;
		if(cost > coin)
			break;
		coin -= cost;
		curr_level = next_level;
		curr_exp = next_exp;
		if(0 == oneclick)
			break;
		++next_level;
		auto& nextLvelCfg = HeroCfgWrap().GetHeroByLevel(next_level);
		next_exp = ConfigManager::Instance()->hero_level_exp[next_level-1];
		per_coin = (next_exp - curr_exp) /-nextLvelCfg.coin();
		cost = per_coin * (next_exp - curr_exp);
	}

	herowrap.AddExp(curr_exp - hero_exp);
	CommonGiftConfig::CommonModifyItem cfg;
	cost = userWrap.Obj().coin - coin;
	cfg.mutable_based()->set_coin(-cost);
	LogicUserManager::Instance()->CommonProcess(uid, cfg, "upgrade_hero", resp->mutable_commons());
	herowrap.FullMessage(resp->mutable_hero());

	return 0;
}



int LogicHeroManager::Process(unsigned uid, ProtoHero::UpGradeHeroSkillReq* req, ProtoHero::UpGradeHeroSkillResp* resp)
{
	unsigned heroid = req->heroid();
	unsigned skillId = req->skillid();
	if(skillId > 3)
	{
		error_log("skill id error uid=%u, heroid=%u, skillId=%u", uid, heroid, skillId);
		throw runtime_error("skill_id_error");
	}

	DBCHeroWrap herowrap(uid, heroid);
	unsigned skillLevel = herowrap.Obj().skill[skillId];
	if(skillLevel >= MAX_HERO_SKILL_LEVEL)
	{
		error_log("hero skill is max uid=%u, heroid=%u, skillId=%u", uid, heroid, skillId);
		throw runtime_error("hero_skill_is_max");
	}

	const Hero::HeroSkillUp& heroCfg = HeroCfgWrap().GetSkillInfoByLevel(skillLevel);
	int coin = heroCfg.cost().based().coin();

	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_coin(coin);
	CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
	for(int i = 0; i < heroCfg.cost().props_size(); ++i)
	{
		auto& props = heroCfg.cost().props(i);
		propsbase->set_id(props.id());
		propsbase->set_count(props.count());
	}

	LogicUserManager::Instance()->CommonProcess(uid, cfg, "upgrade_hero_skill", resp->mutable_commons());
	resp->set_level(skillLevel+1);
	herowrap.UpdateSkillLevel(skillId);
	resp->set_battlepower(herowrap.Obj().battle_power);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::UpGradeHeroStarReq* req, ProtoHero::UpGradeHeroStarResp* resp)
{
	unsigned heroid = req->heroid();
	//龙珠是否都激活
	DBCHeroWrap hero(uid, heroid);
	if(!hero.DragonBallAllAct())
	{
		error_log("dragon ball not act all uid=%u", uid);
		throw runtime_error("dragon_ball_not_act_all");
	}

	//依次激活
	unsigned starid = req->starid();
	if(starid < 1 || starid > MAX_STAR_NUM)
	{
		error_log("param error uid=%u, starid=%u", uid, starid);
		throw runtime_error("param_error");
	}

	unsigned star = hero.Obj().star;
	for(int i = 0; i < starid-1; ++i)
	{
		if(0 == (star & (1<<i)))
		{
			error_log("logic error uid=%u, starid=%u", uid, starid);
			throw runtime_error("logic_error");
		}
	}

	auto& starCfg = StarsCfgWarp().GetStarsInfoById(heroid).list(starid-1);

	//消耗道具和金币
	CommonGiftConfig::CommonModifyItem cfg;
	CommonGiftConfig::PropsItem * propsbase = cfg.add_props();
	cfg.mutable_based()->set_coin(starCfg.price().based().coin());
	for(int i = 0; i < starCfg.price().props_size(); ++i)
	{
		propsbase->set_count(starCfg.price().props(i).count());
		propsbase->set_id(starCfg.price().props(i).id());
	}
	//消耗
	LogicUserManager::Instance()->CommonProcess(uid,cfg,"upgrade_star",resp->mutable_commons());

	//英雄属性
	hero.UpdateStar(starid);
	hero.FullMessage(resp->mutable_hero());

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::SetHeroReq* req, ProtoHero::SetHeroResp* resp)
{
	unsigned heroid = req->heroid();
	auto& heroCfg = HeroCfgWrap().Hero();
	if(heroid > heroCfg.hero_size())
	{
		error_log("param error uid: %u, heroid: %u", uid, heroid);
		throw runtime_error("param_error");
	}
	DBCUserBaseWrap userwrap(uid);
	userwrap.SetHero(heroid);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::ActArchiveChipReq* req, ProtoHero::ActArchiveChipResp* resp)
{

	unsigned propId = req->id();
	auto& propCfg = ItemCfgWrap().GetPropsItem(propId);
	unsigned seq = propCfg.seq();
	unsigned heroId	= propCfg.heroid();

	if(seq < 1 || seq > ARCHIVE_CHIP_NUM)
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}
	unsigned act = req->act();

	DBCUserBaseWrap userwrap(uid);

	CommonGiftConfig::CommonModifyItem cfg;
	CommonGiftConfig::PropsItem * propbase = cfg.add_props();
	//激活
	if(0 == act)
	{
		if(!userwrap.ActArchiveChip(heroId, seq-1))
		{
			error_log("ack archive chip error uid: %u", uid);
			throw runtime_error("ack_archivechip_error");
		}
		propbase->set_id(propId);
		propbase->set_count(-1);
	}

	//取消激活
	if(1 == act)
	{
		if(!userwrap.UnActArchiveChip(heroId, seq-1))
		{
			error_log("unack archive chip error uid: %u", uid);
			throw runtime_error("unack_archivechip_error");
		}
		propbase->set_id(propId);
		propbase->set_count(1);
	}

	//图鉴升级
	if(userwrap.ArchiveUpLevel(heroId))
	{
		ProtoPush::PushArchiveUp *msg = new ProtoPush::PushArchiveUp;
		DBCHeroWrap herowrap(uid, heroId);
		//更新战力
		auto& archive = ArchiveCfgWarp().GetArchiveInfoInfoById(heroId);
		unsigned level = userwrap.Obj().archive_level[heroId-1];
		herowrap.Obj().archive_power = archive.levelattr(level-1).attr().fight_power();
		herowrap.Obj().battle_power = herowrap.BattlePower();
		herowrap.Save();

		herowrap.FullMessage(msg->mutable_hero());
		LogicManager::Instance()->sendMsg(uid, msg);
	}

	LogicUserManager::Instance()->CommonProcess(uid,cfg,"ack_archive_chip",resp->mutable_commons());

	return 0;
}


int LogicHeroManager::Process(unsigned uid, ProtoHero::ArchiveRewardReq* req, ProtoHero::ArchiveRewardResp* resp)
{
	unsigned id = req->id();

	DBCUserBaseWrap userWrap(uid);
	if(!userWrap.UpateArchiveRewardCount(id))
	{
		error_log("update archive reward count failed uid:%u", uid);
		throw runtime_error("get_archive_reward_error");
	}

	unsigned count = userWrap.Obj().archive_reward[id-1];
	const Archive::ArchiveRward& cfg = ArchiveCfgWarp().GetArchiveRewardByLevel(count+1);

	LogicUserManager::Instance()->CommonProcess(uid,cfg.reward(),"archive_reward",resp->mutable_commons());

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::ProtoActDragonBallReq* req, ProtoHero::ProtoActDragonBallResp* resp)
{
	unsigned idx = req->idx();
	if(idx < 1 || idx > MAX_DRAGON_BALL_INDEX)
	{
		error_log("param error uid: %u", uid);
		throw runtime_error("param_error");
	}

	//消耗龙鳞
	CommonGiftConfig::CommonModifyItem cfg;
	auto prop = cfg.add_props();
	prop->set_id(DRAGON_SCALE_ID);
	prop->set_count(-1);

	LogicUserManager::Instance()->CommonProcess(uid, cfg, "ack_dragon_ball", resp->mutable_commons());

	unsigned heroid = req->heroid();
	DBCHeroWrap hero(uid, heroid);
	if(!hero.ActDragonBall(idx-1))
	{
		error_log("ack dragon ball error uid: %u", uid);
		throw runtime_error("act_dragon_ball_error");
	}

	//更新战力
	auto& dragon_ball = DragonBallCfgWarp().GetDragonBallInfoById(heroid);
	hero.Obj().dragon_power += dragon_ball.list(idx).fight_power();
	hero.Obj().battle_power = hero.BattlePower();
	hero.FullMessage(resp->mutable_hero());
	hero.Save();

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::ProtoBuyHeroShareRewardReq* req, ProtoHero::ProtoBuyHeroShareRewardResp* resp)
{
	unsigned heroid = req->heroid();
	if(!DataHeroManager::Instance()->IsExistItem(uid, heroid))
	{
		error_log("param error uid=%u", uid);
		throw runtime_error("param_error");
	}

	DBCHeroWrap hero(uid, heroid);
	if(hero.Obj().share_reward == 1)
	{
		error_log("more than once uid=%u", uid);
		throw runtime_error("more_than_once");
	}

	auto& cfg = HeroCfgWrap().GetHeroByHeroId(heroid);
	LogicUserManager::Instance()->CommonProcess(uid, cfg.sharereward(), "shared_reward", resp->mutable_commons());
	hero.Obj().share_reward = 1;
	hero.Save();

	return 0;
}

void LogicHeroManager::UpdateBattlePower(unsigned uid)
{
	vector<unsigned> vIndexs;
	DataHeroManager::Instance()->GetIndexs(uid, vIndexs);

	for(auto& e : vIndexs)
	{
		DBCHeroWrap hero(e);
		HeroAttr attr;
		hero.GetAttr(attr);
		unsigned heroid = hero.Obj().id;
		double battlePower = hero.BaseBattlePower();
		//龙珠战力
		unsigned dragon = hero.Obj().dragon_ball;
		auto& dragon_ball = DragonBallCfgWarp().GetDragonBallInfoById(heroid);
		for(int i = 0; i < dragon_ball.list_size() && i <= MAX_DRAGON_BALL_INDEX; ++i)
		{
			if(0 != (dragon & (i << 1)))
			{
				battlePower += dragon_ball.list(i).fight_power();
			}
		}

		//图鉴战力
		DataBase& user = BaseManager::Instance()->Get(uid);
		ArchiveCfgWarp archiveCfg;
		for(int i = 0; i < ARCHIVE_LENGTH; ++i)
		{
			unsigned level = user.archive_level[i];
			if(level > 0)
			{
				auto& archive = archiveCfg.GetArchiveInfoInfoById(i+1);
				battlePower += archive.levelattr(level-1).attr().fight_power();
			}
		}

		//升星战力
		auto& stars = StarsCfgWarp().GetStarsInfoById(heroid);
		unsigned star = hero.Obj().star;
		for(int i = 0; i < stars.list_size() && i < MAX_STAR_NUM; ++i)
		{
			if(0 != (star & (i << 1)))
			{
				battlePower += stars.list(i).fight_power();
			}
		}

		//技能战力
		auto & heroCfg = HeroCfgWrap().GetHeroByHeroId(heroid);
		for(int i = 0; i < HERO_SKILL_LENGTH; ++i)
		{
			unsigned level = hero.Obj().skill[i];
			battlePower += heroCfg.skill(i).skillinfo(level-1).fight_power();
		}
		hero.Obj().battle_power = static_cast<unsigned>(battlePower);
		hero.Save();
	}
}

