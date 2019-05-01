#include "LogicHeroManager.h"

DBCHeroWrap::DBCHeroWrap(unsigned uid, unsigned heroid)
	: container_(DataHeroManager::Instance())
	, index_(container_->GetHeroIndex(uid, heroid))
	, data_(container_->m_data->data[index_])
{

}

DBCHeroWrap::DBCHeroWrap(unsigned index)
	: container_(DataHeroManager::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{
}

int DBCHeroWrap::GetFightAttr(HeroFightAttr& result, bool isPushSoldiers)
{
	result.Clear();
	unsigned uid = data_.uid;
	unsigned heroid = data_.heroid;

	int s_lvl = LogicScienceMgr::Instance()->GetSoldierLevel(uid);

	//装备本身属性
	HeroFightAttr equip_attr;
	LogicEquipmentManager::Instance()->GetFightAttr(uid, heroid, equip_attr);

	//套装属性
	HeroFightAttr suit_attr;
	LogicEquipmentManager::Instance()->GetEquipSuitAttr(uid, heroid, suit_attr);

	//部件基本属性，不包含百分比属性类型
	HeroFightAttr component_base_attr;
	LogicComponentManager::Instance()->GetBaseAttr(uid, heroid, component_base_attr);

	//读取血量，攻击，防御的配置  统 勇
	HeroFightAttr cfg_attr;
	HeroCfgWrap().GetHeroFightAttr(heroid, data_.level, s_lvl, cfg_attr);

	//兵器系统  //攻击，防御，血量
	HeroFightAttr weapons_attr;
	LogicWeaponsMgr::Instance()->GetHeroFightAttr(uid, weapons_attr);

	result = equip_attr + cfg_attr + weapons_attr + suit_attr + component_base_attr;

	//英雄等级设置
	result.SetAttr(DemoHeroProperty_level, data_.level);

	//百分比加成
	map<unsigned, double> addition_percent;

	//科技加成
	int factor = LogicScienceMgr::Instance()->GetHeroFightFactor(uid);
	if (factor > 0)
	{
		//攻防血加成
		addition_percent[property_type_attack_percent] = factor;
		addition_percent[property_type_defend_percent] = factor;
		addition_percent[property_type_hp_percent] = factor;
	}

	//部件的百分比属性加成
	LogicComponentManager::Instance()->GetPercentAttr(uid, heroid, addition_percent);

	//战机加成
	if(heroid == VIP_HERO_ID_9)
	{
		//攻防血加成
		addition_percent[property_type_attack_percent] += VIP_HERO_EFFECT_9;
		addition_percent[property_type_defend_percent] += VIP_HERO_EFFECT_9;
		addition_percent[property_type_hp_percent] += VIP_HERO_EFFECT_9;
	}

	result.AdditionFightBase(addition_percent);

	try
	{
		//同步到英雄属性管理器
		HeroPropertyWrap(uid, heroid).UpdateProperty(result, isPushSoldiers);
	}
	catch(const std::exception& e)
	{
		(void)e;
	}

	return R_SUCCESS;
}

bool DBCHeroWrap::FinalData(const OfflineResourceItemHexp& hexp, bool isPushSoldiers)
{
	bool bChange = false;
	if (hexp.hexp > 0)
	{
		AddExp(hexp.hexp, isPushSoldiers);
	}

	if (hexp.kill > 0) { data_.killnum += hexp.kill; bChange = true;}
	if (hexp.occupy > 0) { data_.attacknum += hexp.occupy; bChange = true;}
	if (hexp.win > 0) { data_.ovonum += hexp.win; bChange = true;}

	if (bChange)
	{
		Save();
	}

	return bChange;
}
void DBCHeroWrap::AddOccupy()
{
	++data_.attacknum;
	Save();
}

bool DBCHeroWrap::AddExp(int exp, bool isPushSoldiers)
{
	if (exp <= 0) return false;

	int old_level = data_.level;

	DBCUserBaseWrap user(data_.uid);
	data_.AddExp(exp, user.Obj().level);
	if (old_level != data_.level)
	{
		//refresh hero data;
		HeroFightAttr attr;
		GetFightAttr(attr, isPushSoldiers);

		//todo 接入英雄升级任务接口
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_hero_upgrade;

		LogicMissionManager::Instance()->VerifyMissionComplete(data_.uid, missionparam);
	}

	Save();

	return true;
}

void DBCHeroWrap::FullMessage(ProtoHero::HeroBaseInfoCPP * hero, bool isPushSoldiers)
{
	HeroFightAttr fightAttr;
	this->GetFightAttr(fightAttr, isPushSoldiers);

	fightAttr.FullMessage(hero);
}


///////////////////////////////////////////////////////////////////////////////////
HeroPropertyWrap::HeroPropertyWrap(unsigned uid, unsigned heroId)
	: data_(LogicHeroManager::Instance()->GetHeroPropertyItem(uid, heroId))
	, attr_(LogicResourceManager::Instance()->Get(uid))
	, soldier_rows_(attr_.GetSoldiresRows())

{
	//有僚机 加一排士兵
	if (data_.extraid > 0)
	{
		soldier_rows_ += 1;
	}
}

void HeroPropertyWrap::UpdateProperty(HeroFightAttr& result, bool isPushSoldiers)
{
	int soldiers = data_.GetTotalTroops(soldier_rows_);

	data_.UpdateProperty(result);

	WMI->CalcPower(data_.index);
	result.SetAttr(DemoHeroProperty_power, data_.property[DemoHeroProperty_power]);

	//int new_soldiers = data_.GetTotalTroops(soldier_rows_);
	if (soldiers > 0 && /*soldiers != new_soldiers &&*/ isPushSoldiers)
	{
		ProtoHero::SyncSoldiersResp* soldier_ptr = new ProtoHero::SyncSoldiersResp;
		if (soldier_ptr)
		{
			this->FullMessage(soldier_ptr->add_heros());
			LogicManager::Instance()->sendMsg(attr_.uid, soldier_ptr);
		}
	}
}

void HeroPropertyWrap::GetHeroFightAttr(HeroFightAttr& fight_attr) const
{
	data_.GetHeroFightAttr(fight_attr);
}

bool HeroPropertyWrap::IsFullTroops()
{
	return data_.IsFullTroops(soldier_rows_);
}

unsigned HeroPropertyWrap::CalcRealRecruitSoldires(unsigned nAddSoldires)
{
	return data_.CalcRealRecruitSoldires(soldier_rows_, nAddSoldires);
}

void	HeroPropertyWrap::RecruitSoldires(unsigned nAddSoldires)
{
	data_.RecruitSoldires(soldier_rows_, nAddSoldires);
}

void	HeroPropertyWrap::FullSoldires()
{
	data_.FullSoldires(soldier_rows_);
}

void HeroPropertyWrap::FullMessage(ProtoHero::HeroSoldiersCPP * obj)
{
	data_.FullMessage(soldier_rows_, obj);
}


unsigned 	HeroPropertyWrap::GetActualTroops()
{
	return data_.GetActualTroops(soldier_rows_);
}

unsigned 	HeroPropertyWrap::GetTotalTroops()
{
	return data_.GetTotalTroops(soldier_rows_);
}

unsigned	HeroPropertyWrap::GetFreeTroops()
{
	return data_.GetFreeTroops(soldier_rows_);
}

unsigned	HeroPropertyWrap::GetHeroLevel() const
{
	return data_.property[DemoHeroProperty_level];
}


///////////////////////////////////////////////////////////////////////////////////
LogicHeroManager::LogicHeroManager()
	: up_recruit_time_(Time::GetGlobalTime())
{
}

int LogicHeroManager::GetAllFightAttr(unsigned uid, unsigned heroid, HeroFightAttr& result)
{
	try
	{
		return DBCHeroWrap(uid, heroid).GetFightAttr(result);
	}
	catch (const std::exception& e)
	{
		error_log("uid:%d, heroid: %d, %s", uid, heroid, e.what());
	}

	return R_ERROR;
}

void LogicHeroManager::OnTimer1()
{
	unsigned now = Time::GetGlobalTime();
	if (now >= up_recruit_time_ + UP_RECRUIT_INTERVAL)
	{
		int nCnt = 1;
		if (up_recruit_time_ == 0)
		{
			nCnt = 1;
			up_recruit_time_ = now;
		}
		else
		{
			nCnt = (now - up_recruit_time_) / UP_RECRUIT_INTERVAL;
			up_recruit_time_ += nCnt * UP_RECRUIT_INTERVAL;
		}
		
    	vector<unsigned> uids;
		UMI->GetOnlineUsers(uids);

	    for(vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
		{
			try
			{
				RecruitSoldiers(*it, nCnt);
			}
			catch(const std::exception& e)
			{
				(void)e;
			}
		}

	}
}

HeroPropertyItem& LogicHeroManager::GetHeroPropertyItem(unsigned uid, unsigned heroId)
{
	int index = HeroPropertyManager::Instance()
				->GetIndex(HeroPropertyItemIndex(uid, heroId));
	if (-1 == index)
	{
		//error_log("uid: %u, heroId: %u", uid, heroId);
		throw std::runtime_error("get_hero_property_data_error");
	}

	return HeroPropertyManager::Instance()->m_data->item[index];
}


bool LogicHeroManager::IsHeroFullHP(unsigned uid, unsigned heroid)
{
	return HeroPropertyWrap(uid, heroid).IsFullTroops();
}

unsigned LogicHeroManager::GetUserRush(unsigned uid)
{
	//遍历所有英雄,获取累积单挑
	vector<unsigned> indexs;
	DataHeroManager::Instance()->GetHeros(uid, indexs);
	unsigned count = 0;

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataHero & hero = DataHeroManager::Instance()->GetHeroByIndex(indexs[i]);
		count += hero.ovonum;
	}

	return count;
}

unsigned LogicHeroManager::GetUserKill(unsigned uid)
{
	//遍历所有英雄,获取累积单挑
	vector<unsigned> indexs;
	DataHeroManager::Instance()->GetHeros(uid, indexs);
	unsigned count = 0;

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataHero & hero = DataHeroManager::Instance()->GetHeroByIndex(indexs[i]);
		count += hero.killnum;
	}

	return count;
}

unsigned LogicHeroManager::GetUserOccupy(unsigned uid)
{
	//遍历所有英雄,获取累积单挑
	vector<unsigned> indexs;
	DataHeroManager::Instance()->GetHeros(uid, indexs);
	unsigned count = 0;

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataHero & hero = DataHeroManager::Instance()->GetHeroByIndex(indexs[i]);
		count += hero.attacknum;
	}

	return count;
}

void LogicHeroManager::SyncUserHerosInfo(unsigned uid)
{
	std::vector<unsigned> vHeroIndexs;
	DataHeroManager::Instance()->GetRecruitHero(uid, vHeroIndexs);

	ProtoPush::HerosInfo* heros = new ProtoPush::HerosInfo;
	try
	{
		for (size_t i = 0; i < vHeroIndexs.size(); ++i)
		{
			DBCHeroWrap heroWrap(vHeroIndexs[i]);
			HeroFightAttr heroproperty;
			heroWrap.GetFightAttr(heroproperty);

			ProtoHero::HeroBaseInfoCPP* hero = heros->add_heros();
			heroproperty.FullMessage(hero);
			heroWrap.Obj().SetMessage(hero);
		}
		//send
		LogicManager::Instance()->sendMsg(uid, heros);
	}
	catch(const std::exception& e)
	{
		error_log("uid:%d, %s", uid, e.what());
		delete heros;
	}
}

void LogicHeroManager::RecruitSoldiersByStartTime(unsigned uid,  unsigned start_time)
{
	if (up_recruit_time_ > start_time && start_time > 0)
	{
		int nCnt = (up_recruit_time_ - start_time) / UP_RECRUIT_INTERVAL;
		RecruitSoldiers(uid, nCnt);
	}
}

float LogicHeroManager::RecruitSoldiresCostFactor(int level)
{
#if 0
	const float val[4] = {0.2, 0.26, 0.32, 0.4};
	if (level < 1 || level > 4)
	{
		error_log("soldier_level:%d", level);
		throw std::runtime_error("soldiers_level_error");
	}

	return val[level - 1];
#endif
	return HeroCfgWrap().GetRecruitCostFactor(level);
}

void LogicHeroManager::RecruitSoldiers(unsigned uid, unsigned nCnt)
{
	std::vector<DataHero> vHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vHeros);
	for (size_t i = 0; i < vHeros.size(); ++i)
	{
		try
		{
			CheckHeroIdParams(uid, vHeros[i].heroid);
		}
		catch (const std::exception& ) {
			continue;
		}

		//战斗状态
		if (WorldManager::Instance()
					->IsHeroFighting(HeroPropertyItemIndex(uid, vHeros[i].heroid)))
		{
			continue;
		}

		try
		{
			HeroPropertyWrap hero(uid, vHeros[i].heroid);
			//满员
			if(hero.IsFullTroops())
			{
				//接入回血任务接口
				LogicMissionManager::MissionParam missionparam;
				missionparam.type = mission_type_herohp_recover;
				LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

				continue;
			}

			//TODO 回血扣资源
			unsigned nAddSoldires =  hero.Attr().GetRecruitRate() * nCnt;
			int nRealSolires = hero.CalcRealRecruitSoldires(nAddSoldires);

			/*
			debug_log("uid: %u, hero: %u, real: %d, total: %u, soldires: %u, nAddSoldires: %d, cnt:%d"
					, uid, vHeros[i].heroid, hero.GetActualTroops(), hero.GetTotalTroops()
					, nRealSolires
					, nAddSoldires, nCnt);
					*/

			int cost_food = nRealSolires * RecruitSoldiresCostFactor(hero.Attr().GetSoldierLevel());
			try
			{
				DBCUserBaseWrap userWrap(uid);
				userWrap.RestoreResource();
				if (userWrap.Obj().food >= cost_food)
				{
					userWrap.CostUserResource(0, 0, cost_food, 0, "recruit_solldire_op");
					hero.RecruitSoldires(nRealSolires);
				}
				//debug_log("uid: %u, hero: %u, real_soldires: %d", uid, vHeros[i].heroid, hero.GetActualTroops());
			}
			catch(const std::exception& ){}

		}
		catch(const std::exception& e)
		{
			error_log("uid: %u,heroid:%d", uid, vHeros[i].heroid);
		}
	}
}

void LogicHeroManager::FinalData(unsigned uid, BattleReward& r)
{
	bool ischange = false;

	for(map<unsigned,OfflineResourceItemHexp>::iterator it=r.hexp.begin();it!=r.hexp.end();++it)
	{
		try
		{
			DBCHeroWrap hero(uid, it->first);
			bool istemp = hero.FinalData(it->second);

			if (!ischange)
			{
				ischange = istemp;
			}

			HeroFightAttr heroproperty;
			hero.GetFightAttr(heroproperty);

			ProtoHero::HeroBaseInfoCPP* heroMsg = new ProtoHero::HeroBaseInfoCPP();
			heroproperty.FullMessage(heroMsg);
			hero.Obj().SetMessage(heroMsg);

			LogicManager::Instance()->sendMsg(uid, heroMsg);
		}
		catch(const std::exception& e)
		{
			(void)e;
		}
	}

	//todo 接入单挑、杀敌、占领城市等成就
	if (ischange)
	{
		HeroFightExternal(uid);
	}
}

bool LogicHeroManager::FinalData(unsigned uid, OfflineResourceItemHexp hexp[SG17_HERO_NUM])
{
	bool bChange = false;
	bool ischange = false;

	for (int i = 0; i < SG17_HERO_NUM; i++)
	{
		if (hexp[i].id > 0)
		{
			try
			{
				bChange = DBCHeroWrap(uid, hexp[i].id).FinalData(hexp[i], false);

				if (!ischange)
				{
					ischange = bChange;
				}
			}
			catch(const std::exception& e)
			{
				(void)e;
			}
		}
	}

	//todo 接入单挑、杀敌、占领城市等成就
	if (ischange)
	{
		HeroFightExternal(uid);
	}

	return bChange;
}

int LogicHeroManager::HeroFightExternal(unsigned uid)
{
	//突进
	LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_rush;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	//杀敌
	achievementparam.type = achievement_type_kill;
	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	//占领
	achievementparam.type = achievement_type_occupycity;
	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

int LogicHeroManager::LoginHeroCheck(unsigned uid)
{
	//判断英雄数据是否加载进内存
	int ret = DataHeroManager::Instance()->CheckBuff(uid);

	if (ret)
	{
		//没有数据。重新加载一遍
		int ret = DataHeroManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)   //表中没有数据，重新初始化
		{
			NewUserInit(uid);
		}
		else if (ret)
		{
			return ret;
		}
	}

	//检查用户所有已上阵的英雄是否在heroproperty中
	vector<DataHero> vcthero;
	DataHeroManager::Instance()->GetRecruitHero(uid, vcthero);

	for(int i = 0; i < vcthero.size(); ++i)
	{
		HeroPropertyItemIndex heroitem(uid, vcthero[i].heroid);

		bool isHave = HeroPropertyManager::Instance()->HasHero(heroitem);

		if (!isHave)
		{
			AddHeroProperty(uid, vcthero[i].heroid);
		}
	}

	//登录时同步一下属性
	std::vector<unsigned> vHIndex;
	DataHeroManager::Instance()->GetRecruitHero(uid, vHIndex);
	for (size_t i = 0; i < vHIndex.size(); ++i)
	{
		try
		{
			DBCHeroWrap heroWrap(vHIndex[i]);
			HeroFightAttr attr;
			heroWrap.GetFightAttr(attr, false);
		}
		catch(const std::exception& e)
		{

		}

	}

	//阅兵次数结算
	CalcuteParadeTimes(uid);

	return 0;
}

int LogicHeroManager::NewUserInit(unsigned uid)
{
	ProtoHero::HeroBaseInfoCPP * herobase = new ProtoHero::HeroBaseInfoCPP;

	//先获得第一个英雄的heroid
	unsigned heroid = TavernConfigWrap().GetFirstHeroId();

	UnlockHero(uid, heroid, "NewUser", herobase);   //自动解锁第一个英雄
	RecruitHero(uid, heroid, true, herobase);   //自动招募第二个英雄

	delete herobase;

	return 0;
}

bool LogicHeroManager::UnlockVerify(unsigned uid, unsigned gateid)
{
	ProtoHero::UnlockHeroPushReq * unlockheromsg = new ProtoHero::UnlockHeroPushReq;

	bool isSuccess = UnlockVerify(uid, gateid, unlockheromsg->mutable_hero());

	if (!isSuccess)
	{
		delete unlockheromsg;
		return false;
	}

	try
	{
		//add oulong 20160927 添加带兵信息
		HeroPropertyWrap hero(uid,  unlockheromsg->hero().heroid());
		hero.FullMessage(unlockheromsg->mutable_soidiers());
	}
	catch(exception & e)  //不对异常做处理
	{
		;
	}

	LogicManager::Instance()->sendMsg(uid, unlockheromsg);

	return true;
}

bool LogicHeroManager::UnlockVerify(unsigned uid, unsigned gateid, ProtoHero::HeroBaseInfoCPP * heromsg)
{
	//判断该关卡是否在酒馆的解锁条件之中
	const TavernConfig::HeroRecruit &  allhero = TavernConfigWrap().Tavern();
	bool isCanUnlok = false;   //是否可解锁

	unsigned heroid = 0;

	TavernConfigWrap tavernConfig;

	heroid = tavernConfig.GetHeroIdByGate(gateid);

	if ((unsigned)-1 == heroid)  //闯关id不在配置文件中，说明此关和英雄解锁无关
	{
		return false;
	}

	unsigned needtimes = tavernConfig.GetNeedTimesById(gateid);

	if ((unsigned)-1 == needtimes)  //闯关id不在配置文件中，说明此关和英雄解锁无关
	{
		return false;
	}

	//接下来判断闯关数目
	int gatetimes = LogicNPCPassMgr::Instance()->GetNPCPassCnt(uid, gateid);

	if (gatetimes < needtimes)
	{
		return false;
	}

	//满足条件，自动调用英雄解锁
	int ret = UnlockHero(uid, heroid, "BreakGate", heromsg);

	if (ret)
	{
		return false;
	}

	int secondgateid = tavernConfig.GetSecondGateId();

	if (secondgateid == gateid)  //闯过该关卡，自动招募英雄
	{
		try
		{
			RecruitHero(uid, heroid, true, heromsg);
		}
		catch(exception & e)   //对异常不做处理
		{
			;
		}
	}

	return true;
}

int LogicHeroManager::UnlockHero(unsigned uid, unsigned heroid, string reason, ProtoHero::HeroBaseInfoCPP * heromsg)
{
	//对参数进行判断
	if (heroid < 1 || heroid == -1)
	{
		return R_ERROR;
	}

	//判断英雄是否存在配置文件里
	bool isHaveCfg = HeroCfgWrap().isHeroExistCfg(heroid);

	if (!isHaveCfg)
	{
		error_log("[UnlockHero] hero not exist in config. uid=%u,heroid=%u", uid, heroid);
		return R_ERROR;
	}

	//先判断英雄中是否已经拥有该英雄
	bool isExist = DataHeroManager::Instance()->isHeroExists(uid, heroid);

	if (isExist)
	{
		return R_ERROR;
	}

	//将英雄信息写入表中
	DataHero addhero;
	addhero.level = 1;
	addhero.exp = 0;
	addhero.uid = uid;
	addhero.heroid = heroid;

	int ret = DataHeroManager::Instance()->AddBuff(addhero);

	if (ret)
	{
		error_log("[UnlockHero] add hero error. uid=%u,heroid=%u,ret=%d", uid, heroid, ret);
		return ret;
	}

	addhero.SetMessage(heromsg);

	HERO_LOG("uid=%u,heroid=%u,act=%s,code=%s",uid, heroid, "Unlock", reason.c_str());

	//todo 接入解锁英雄成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_unlockhero;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::RecruitHeroReq *reqmsg, ProtoHero::RecruitHeroResp * respmsg)
{
	unsigned heroid = reqmsg->heroid();
	RecruitHero(uid, heroid, false, respmsg->mutable_hero());
	DBCUserBaseWrap userwrap(uid);
	respmsg->set_coin(userwrap.Obj().coin);

	//add oulong 20160926 添加带兵信息
	HeroPropertyWrap hero(uid,  heroid);
	hero.FullMessage(respmsg->mutable_soidiers());

	//todo 接入任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_recruit;
	missionparam.subparam.push_back(heroid);

	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

int LogicHeroManager::RecruitHero(unsigned uid, unsigned heroid, bool isfree, ProtoHero::HeroBaseInfoCPP * heromsg)
{
	//判断当前英雄是否已解锁
	bool isExist = DataHeroManager::Instance()->isHeroExists(uid, heroid);

	if (!isExist)
	{
		error_log("[RecruitHeroReq] hero is in lock. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("hero_in_lock");
	}

	//获取英雄信息
	unsigned index = 0;

	DataHero & hero = DataHeroManager::Instance()->GetHero(uid, heroid, index);

	if (hero.status)
	{
		throw std::runtime_error("hero_already_recruit");
	}

	//判断可招募英雄是否达到上限
	int MAX_HERO_NUM = LogicScienceMgr::Instance()->GetRecruitHeros(uid);

	int curnum = DataHeroManager::Instance()->GetUsingHeroNums(uid);

	if (curnum >= MAX_HERO_NUM)
	{
		error_log("[RecruitHeroReq] recruit hero num is max. cur=%d, max=%d", curnum, MAX_HERO_NUM);
		throw std::runtime_error("hero_recruit_max");
	}

	if (!isfree)   //非免费招募
	{
		//扣去资源
		int price = 0;
		int ret = DataHeroManager::Instance()->GetHeroPrice(uid, heroid, price);

		if (ret)
		{
			throw std::runtime_error("get_hero_price_error");
		}

		Json::Value result;
		LogicUserManager::Instance()->CostUserResource(uid, price, 0, 0, 0, "Recruit_Hero", result);
	}

	hero.status = 1;
	DataHeroManager::Instance()->UpdateHero(index);

	AddHeroProperty(uid, heroid);

	//计算并获取英雄信息
	SetHeroMessage(uid, heroid, heromsg);

	HeroPropertyWrap heroWrap(uid,  heroid);
	heroWrap.FullSoldires();

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::FireHeroReq *reqmsg, ProtoHero::FireHeroResp * respmsg)
{
	unsigned heroid = reqmsg->heroid();

	//判断当前英雄是否已解锁
	bool isExist = DataHeroManager::Instance()->isHeroExists(uid, heroid);

	if (!isExist)
	{
		error_log("[FireHeroReq] hero is in lock. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("hero_in_lock");
	}

	VerifyHeroRecruit(uid, heroid);
	HeroPropertyItemIndex heroindex(uid, heroid);

	//移动中不能解雇英雄
	if(WMI->IsHeroMoving(heroindex))
	{
		throw std::runtime_error("hero_moving");
	}

	//有部件，不能解雇英雄
	vector<unsigned> indexs;
	DataComponentManager::Instance()->GetHeroComponents(uid, heroid, indexs);

	if (indexs.size() > 0)
	{
		throw std::runtime_error("hero_have_component");
	}

	WMI->RemoveHeroFromCity(heroindex, false);
	HeroPropertyManager::Instance()->Del(heroindex);

	//获取英雄信息
	unsigned index = 0;
	DataHero & hero = DataHeroManager::Instance()->GetHero(uid, heroid, index);
	hero.status = 0;
	DataHeroManager::Instance()->UpdateHero(index);

	//将英雄的装备放回仓库
	LogicEquipmentManager::Instance()->UnDressAllEquipment(uid, heroid, respmsg->mutable_equipwrap());

	//计算并获取英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::DressEquipReq *reqmsg, ProtoHero::DressEquipResp * respmsg)
{
	unsigned equd = reqmsg->equd();
	unsigned oldequd = reqmsg->oldequd();
	unsigned heroid = reqmsg->heroid();

	VerifyHeroRecruit(uid, heroid);

	int ret = LogicEquipmentManager::Instance()->DressEquipment(uid, equd, oldequd, heroid, respmsg->mutable_equipwrap());

	if (ret)
	{
		throw std::runtime_error("dress_equip_error");
	}

	if (oldequd > 0)   //旧装备
	{
		AfterUnDress(uid, oldequd, heroid);
	}

	//新装备的穿装备处理
	if (equd > 0 )
	{
		AfterDress(uid, equd, heroid);
	}

	//计算并获取英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	//todo 接入装备相关的任务
	CheckDressMission(uid);

	return 0;
}

int LogicHeroManager::AfterDress(unsigned uid, unsigned equd, unsigned heroid)
{
	//暂时只处理僚机的后续
	bool iswing = LogicEquipmentManager::Instance()->IsWingMan(uid, equd);

	if (!iswing)
	{
		return 0;
	}

	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);

	//穿上僚机之后，应将heroid中的副将设置成僚机的eqid
	HeroPropertyItemIndex heroindex(uid, heroid);

	//获取Heroproperty中的索引
	int index = HeroPropertyManager::Instance()->GetIndex(heroindex);
	HeroPropertyManager::Instance()->m_data->item[index].extraid = equip.eqid;

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::UnDressEquipReq *reqmsg, ProtoHero::UnDressEquipResp * respmsg)
{
	unsigned equd = reqmsg->equd();
	unsigned heroid = reqmsg->heroid();

	VerifyHeroRecruit(uid, heroid);

	int ret = LogicEquipmentManager::Instance()->UnDressEquipment(uid, equd, heroid, respmsg->mutable_equip());

	if (ret)
	{
		throw std::runtime_error("undress_equip_error");
	}

	if (equd > 0)   //旧装备
	{
		AfterUnDress(uid, equd, heroid);
	}

	//计算并获取英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	return 0;
}

int LogicHeroManager::AfterUnDress(unsigned uid, unsigned equd, unsigned heroid)
{
	//暂时只处理僚机的后续
	bool iswing = LogicEquipmentManager::Instance()->IsWingMan(uid, equd);

	if (!iswing)
	{
		return 0;
	}

	//脱掉僚机之后，应将heroid中的副将取消
	HeroPropertyItemIndex heroindex(uid, heroid);

	//获取Heroproperty中的索引
	int index = HeroPropertyManager::Instance()->GetIndex(heroindex);
	HeroPropertyManager::Instance()->m_data->item[index].extraid = 0;

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::OneKeyDressReq *reqmsg, ProtoHero::OneKeyDressResp * respmsg)
{
	unsigned heroid = reqmsg->heroid();

	VerifyHeroRecruit(uid, heroid);

	int ret = LogicEquipmentManager::Instance()->OneKeyDressEquipment(uid, heroid, respmsg->mutable_equipwrap());

	if (ret)
	{
		throw std::runtime_error("onekey_dress_equip_error");
	}

	//计算并获取英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	//todo 接入装备相关的任务
	CheckDressMission(uid);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::SwitchDressReq *reqmsg, ProtoHero::SwitchDressResp * respmsg)
{
	unsigned heroid = reqmsg->heroids(0);
	unsigned othheroid = reqmsg->heroids(1);

	VerifyHeroRecruit(uid, heroid);
	VerifyHeroRecruit(uid, othheroid);

	int ret = LogicEquipmentManager::Instance()->SwitchDress(uid, heroid, othheroid, respmsg->mutable_equipwrap());

	if (ret)
	{
		throw std::runtime_error("onekey_dress_equip_error");
	}

	//重新计算英雄属性
	SetHeroMessage(uid, heroid, respmsg->add_heroes());
	SetHeroMessage(uid, othheroid, respmsg->add_heroes());

	return 0;
}

void LogicHeroManager::CheckHeroIdParams(unsigned uid, unsigned heroId)
{
	HeroPropertyItemIndex index(uid, heroId);
	if(! HMI->HasHero(index))
	{
		//LMI->SetErrMsg("no_hero");
		throw std::runtime_error("no_hero");
	}
}

//使用募兵令
int LogicHeroManager::Process(unsigned uid, ProtoHero::UseRecruitPropReq* req, ProtoHero::UseRecruitPropResp* resp)
{
	unsigned heroId = req->hero_id();
	CheckHeroIdParams(uid, heroId);

	if (WorldManager::Instance()
				->IsHeroFighting(HeroPropertyItemIndex(uid, heroId)))
	{
		throw std::runtime_error("hero_is_fighting");
	}


	HeroPropertyWrap hero(uid, heroId);
	DBCUserBaseWrap userWrap(uid);
	//
	int nFreeTroops = hero.GetFreeTroops();
	while(nFreeTroops > 0)
	{
		int soldire_level = hero.Attr().GetSoldierLevel();
		int rate = hero.Attr().GetRecruitRate();
		int orders = userWrap.Obj().order == 0 ? userWrap.Obj().cash : userWrap.Obj().order;

		//Fix: 募兵令过多，导致换算溢出
		int nPropSoldires = 0;
		if (orders > 15000)
		{
			nPropSoldires = nFreeTroops;
		}
		else
		{
			nPropSoldires = orders * rate * (RECRUIT_PROP_TIME / UP_RECRUIT_INTERVAL); //一个募兵令五分钟
		}

		int nFoodSoldires = nFreeTroops;
		if (userWrap.Obj().food < RecruitSoldiresCostFactor(soldire_level) * nFoodSoldires)
		{
			nFoodSoldires = float(userWrap.Obj().food) / RecruitSoldiresCostFactor(soldire_level);
		}
		//需要募兵和募兵令和粮食三者的最小值
		nFreeTroops = std::min(std::min(nFreeTroops, nPropSoldires), nFoodSoldires);
		if (nFreeTroops <= 0) break;

		//向上取整
		//需要多少个5s
		int interval = (nFreeTroops + rate - 1) / rate;
		int nTotalCostTime = interval * UP_RECRUIT_INTERVAL;
		//5分钟一个 向上取整
		int nPropCnt = (nTotalCostTime + RECRUIT_PROP_TIME - 1) / RECRUIT_PROP_TIME;

		int nUsePop = userWrap.RealUseRecruitProp(nPropCnt);
		int cost_cash = 0;
		//募兵令用完了消费钻石  @add 20161026 oulong 一个募兵令一钻
		if (nUsePop == 0)
		{
			nUsePop = nPropCnt;
			cost_cash = nPropCnt;
		}

		if (userWrap.Obj().cash < cost_cash)
		{
			break;
		}

		if (cost_cash > 0)
		{
			userWrap.CostCash(cost_cash, "use_recruit_prop_op");
		}


		int nRealPropSolires = nUsePop * rate * RECRUIT_PROP_TIME / UP_RECRUIT_INTERVAL;
		int nRealSoldires = hero.CalcRealRecruitSoldires(nRealPropSolires);

		int cost_food = nRealSoldires * RecruitSoldiresCostFactor(soldire_level);

		userWrap.UseRecruitProp(nUsePop);
		userWrap.CostUserResource(0, 0, cost_food, 0, "use_recruit_solldire_prop_op");
		hero.RecruitSoldires(nRealSoldires);

		//todo 接入募兵令消耗成就
	    LogicAchievementManager::AchievementParam achievementparam;
		achievementparam.type = achievement_type_hprecover;
		achievementparam.subparam.push_back(nUsePop);  //传入募兵令消耗数量

		LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

		break;
	}

	//resp
	if (resp)
	{
		resp->set_order(userWrap.Obj().order);
		resp->set_food(userWrap.Obj().food);
		resp->set_cash(userWrap.Obj().cash);
		hero.FullMessage(resp->mutable_hero());
	}

	//接入回血任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_herohp_recover;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return R_SUCCESS;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::SyncSoldiersReq* req, ProtoHero::SyncSoldiersResp* resp)
{
	if (resp)
	{
		for (int i = 0; i < req->hero_ids_size(); ++i)
		{
			unsigned heroId = req->hero_ids(i);
			//FullMessage(uid, heroId, resp->add_heros());
			HeroPropertyWrap(uid, heroId).FullMessage(resp->add_heros());
		}
	}

	return R_SUCCESS;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::OpenSmeltWindowReq* reqmsg, ProtoHero::OpenSmeltWindowResp* respmsg)
{
	int times = LogicEquipmentManager::Instance()->GetRefreshTimes(uid);
	respmsg->set_freetimes(times);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::EquipSmeltReq* reqmsg, ProtoHero::EquipSmeltResp* respmsg)
{
	unsigned equd = reqmsg->equd();
	int type = reqmsg->type();

	//获取装备信息
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, equd);

	if (equip.heroid)   //正在战斗的英雄，不能进行洗练的操作
	{
		//验证英雄
		VerifyHeroRecruit(uid, equip.heroid);
	}

	//洗练
	LogicEquipmentManager::Instance()->SmeltEquipment(uid, equd, type, respmsg);

	if (equip.heroid)
	{
		SetHeroMessage(uid, equip.heroid, respmsg->mutable_hero());
	}

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::EquipSmeltPropReq* req, ProtoHero::EquipSmeltPropResp* resp)
{
	DBCUserBaseWrap user(uid);
	unsigned prop_id = 80006;
	unsigned prop_ud = req->prop_ud();

	unsigned rest_cnt = 0;
	std::string reason = "extreme_smelt_prop_op";
	LogicEquipmentManager::Instance()->UseEquipment(uid, prop_id, prop_ud, 1, reason, rest_cnt);

	//
	unsigned equip_ud = req->equip_ud();

	DBCEquipmentWrap equipment(uid, equip_ud);
	equipment.Smelt(smelt_type_of_super);

	if (equipment.IsDressed())
	{
		DBCHeroWrap(uid, equipment.Obj().heroid).FullMessage(resp->mutable_hero(), true);
	}

	equipment.Obj().SetMessage(resp->mutable_equip());
	resp->set_prop_ud(prop_ud);
	resp->set_prop_cnt(rest_cnt);

	return R_SUCCESS;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::UseHeroexpPropsReq* reqmsg, ProtoHero::UseHeroexpPropsResp* respmsg)
{
	unsigned heroid = reqmsg->heroid();
	unsigned eqid = reqmsg->eqid();
	unsigned equd = reqmsg->equd();
	unsigned count = reqmsg->count();

	AddHeroExpByProps(uid, heroid, equd, eqid, count, respmsg);

	return 0;
}

int LogicHeroManager::AddHeroExpByProps(unsigned uid, unsigned heroid, unsigned equd, unsigned eqid, unsigned count,
		ProtoHero::UseHeroexpPropsResp *msg)
{
	//对英雄进行校验
	try
	{
		VerifyHeroRecruit(uid, heroid);  //如果校验不通过，会抛出异常

		//计算达到当前最大等级所需的道具个数
		int maxherolevel = DBCUserBaseWrap(uid).Obj().level;
		uint64_t max_exp = HeroCfgWrap().GetHeroMaxExpByLevel(maxherolevel);

		DBCHeroWrap herowrap(uid, heroid);

		if (herowrap.Obj().exp > max_exp)
		{
			error_log("[AddHeroExpByProps] hero exp bigger than maxexp. uid=%u,heroid=%u", uid, heroid);
			throw std::runtime_error("hero_exp_error");
		}

		uint64_t diff_exp = max_exp - herowrap.Obj().exp;
		int addexp = EquipCfgWrap().GetEquipExpByEqid(eqid);	//单个道具增加的经验
		unsigned costcount = (unsigned) ceil( diff_exp/static_cast<double>(addexp) );

		if (costcount > count)
		{
			costcount = count;
		}

		//消耗道具
		unsigned restcount = 0;
		LogicEquipmentManager::Instance()->UseEquipment(uid, eqid, equd, costcount, "AddHeroExp", restcount);

		msg->set_equd(equd);
		msg->set_count(restcount);

		herowrap.AddExp(addexp);

		//推送英雄信息
		SetHeroMessage(uid, heroid, msg->mutable_hero());
	}
	catch (std::runtime_error & e)
	{
		throw e;
	}

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::ComposeSuitReq* reqmsg, ProtoHero::ComposeSuitResp * respmsg)
{
	unsigned equd = reqmsg->equd();
	vector<unsigned>  material;

	for(int i = 0; i < reqmsg->materialud_size(); ++i)
	{
		material.push_back(reqmsg->materialud(i));
	}

	ComposeEquipSuit(uid, equd, material, respmsg);

	return 0;
}

int LogicHeroManager::ComposeEquipSuit(unsigned uid, unsigned equd, vector<unsigned> & material, ProtoHero::ComposeSuitResp * respmsg)
{
	unsigned suit_equd = LogicEquipmentManager::Instance()->ComposeEquipSuit(uid, equd, material, respmsg->mutable_equips());

	//获取装备信息
	DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentNoIndex(uid, suit_equd);

	if (equip.heroid)
	{
		//获得英雄信息
		DataHero & hero = DataHeroManager::Instance()->GetHero(uid, equip.heroid);
		hero.SetMessage(respmsg->mutable_hero());

		//todo  重新计算英雄属性
		CalcuteHeroProperty(uid, equip.heroid, respmsg->mutable_hero());
	}

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::OpenParadeWindowReq* reqmsg, ProtoHero::OpenParadeWindowResp* respmsg)
{
	OpenParadeWindow(uid, respmsg);

	return 0;
}

int LogicHeroManager::OpenParadeWindow(unsigned uid, ProtoHero::OpenParadeWindowResp * respmsg)
{
	//进行阅兵次数计算
	CalcuteParadeTimes(uid);

	//加载阅兵次数
	DataBase & database = BaseManager::Instance()->Get(uid);

	respmsg->set_banquet(database.banquet);

	//加载回血次数
	OfflineResourceItem & offline = LogicResourceManager::Instance()->Get(uid);
	respmsg->set_silk(offline.silk);

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::ParadeReq* reqmsg, ProtoHero::ParadeResp* respmsg)
{
	Parade(uid, respmsg);

	//todo 阅兵外部接口
	ParadeExternalInterface(uid);

	return 0;
}

int LogicHeroManager::Parade(unsigned uid, ProtoHero::ParadeResp * respmsg)
{
	//判断是否有上阵英雄
	//检查用户所有已上阵的英雄是否在heroproperty中
	vector<DataHero> vcthero;
	DataHeroManager::Instance()->GetRecruitHero(uid, vcthero);

	//加载阅兵次数
	DBCUserBaseWrap userwrap(uid);

	//判断阅兵次数是否足够
	if (userwrap.Obj().banquet < 1)
	{
		error_log("[Parade] times is not enough. uid=%u", uid);
		throw runtime_error("times_not_enough");
	}

	//加载回血次数
	OfflineResourceItem & offline = LogicResourceManager::Instance()->Get(uid);

	if (0 == vcthero.size())
	{
		respmsg->set_banquet(userwrap.Obj().banquet);
		respmsg->set_silk(offline.silk);
		return 0;
	}

	userwrap.Obj().banquet -= 1;
	userwrap.Save();

	//加载可招募的上限
	int MAX_HERO_NUM = LogicScienceMgr::Instance()->GetRecruitHeros(uid);

	offline.silk += MAX_HERO_NUM;

	set<HeroPropertyItemIndex> heros;
	HMI->GetHeros(uid, heros);
	for(set<HeroPropertyItemIndex>::iterator it=heros.begin();it!=heros.end();++it)
	{
		if(!WMI->IsHeroFighting(*it) && WMI->TryRecoverHero(*it))
			respmsg->add_id(it->id);
	}

	if (offline.silk > recover_times_max)  //回血次数达到上限
	{
		offline.silk = recover_times_max;
	}

	respmsg->set_banquet(userwrap.Obj().banquet);
	respmsg->set_silk(offline.silk);

	return 0;
}

int LogicHeroManager::ParadeExternalInterface(unsigned uid)
{
	//todo 接入每日阅兵任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_parade;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	//接入阅兵成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_parade;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	return 0;
}

//装载部件
int LogicHeroManager::Process(unsigned uid, ProtoHero::LoadCompoReq* reqmsg, ProtoHero::LoadCompoResp* respmsg)
{
	unsigned compud = reqmsg->compud();
	unsigned heroid = reqmsg->heroid();
	unsigned pos = reqmsg->pos();

	unsigned oldcompud = reqmsg->oldcompud();

	LoadComponent(uid, compud, oldcompud, heroid, pos, respmsg);

	return 0;
}

int LogicHeroManager::LoadComponent(unsigned uid, unsigned compud, unsigned oldcompud, unsigned heroid, unsigned pos, ProtoHero::LoadCompoResp *respmsg)
{
	//验证英雄
	VerifyHeroRecruit(uid, heroid);

	int ret = LogicComponentManager::Instance()->LoadComponent(uid, compud, oldcompud, heroid, pos, respmsg->mutable_compoall());

	if (ret)
	{
		throw std::runtime_error("load_component_error");
	}

	//重新计算英雄属性并发送英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::UnLoadCompoReq* reqmsg, ProtoHero::UnLoadCompoResp* respmsg)
{
	unsigned compud = reqmsg->compud();
	unsigned heroid = reqmsg->heroid();

	UnloadComponent(uid, compud, heroid, respmsg);

	return 0;
}

int LogicHeroManager::UnloadComponent(unsigned uid, unsigned compud, unsigned heroid, ProtoHero::UnLoadCompoResp *respmsg)
{
	//验证英雄
	VerifyHeroRecruit(uid, heroid);

	int ret = LogicComponentManager::Instance()->UnloadComponent(uid, compud, heroid, respmsg->mutable_compo());

	if (ret)
	{
		throw std::runtime_error("unload_component_error");
	}

	//重新计算英雄属性并发送英雄信息
	SetHeroMessage(uid, heroid, respmsg->mutable_hero());

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::StrengthenCompoReq* reqmsg, ProtoHero::StrengthenCompoResp* respmsg)
{
	unsigned compud = reqmsg->compud();
	vector<unsigned> othcompud;

	for(int i = 0; i < reqmsg->othcompud_size(); ++i)
	{
		othcompud.push_back(reqmsg->othcompud(i));
	}

	StrengthenComponent(uid, compud, othcompud, respmsg);

	return 0;
}

int LogicHeroManager::StrengthenComponent(unsigned uid, unsigned compud, vector<unsigned> & othcompud, ProtoHero::StrengthenCompoResp *respmsg)
{
	//强化部件
	//在开始强化前，记录起始资源量
	DBCUserBaseWrap userwrap(uid);
	unsigned oldcoin = userwrap.Obj().coin;
	unsigned oldwood = userwrap.Obj().wood;

	//判断装备是否属于某一个英雄
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	if (component.heroid)
	{
		//验证英雄
		VerifyHeroRecruit(uid, component.heroid);
	}

	for(int i = 0; i < othcompud.size(); ++i)
	{
		LogicComponentManager::Instance()->StrengthenComponent(uid, compud, othcompud[i], respmsg->mutable_compo());
		respmsg->add_delcompos(othcompud[i]);
	}

	unsigned diff_coin = oldcoin - userwrap.Obj().coin;
	unsigned diff_wood = oldwood - userwrap.Obj().wood;

	respmsg->mutable_coin()->set_value(diff_coin);
	respmsg->mutable_coin()->set_total_value(userwrap.Obj().coin);

	respmsg->mutable_wood()->set_value(diff_wood);
	respmsg->mutable_wood()->set_total_value(userwrap.Obj().wood);

	//判断部件是否属于某一个英雄，如果是，则要重新计算英雄属性

	if(component.heroid)
	{
		//重新计算英雄属性并发送英雄信息
		SetHeroMessage(uid, component.heroid, respmsg->mutable_hero());
	}

	return 0;
}

int LogicHeroManager::Process(unsigned uid, ProtoHero::OneKeyStrengthenCompoReq* reqmsg, ProtoHero::OneKeyStrengthenCompoResp* respmsg)
{
	unsigned compud = reqmsg->compud();

	OneKeyStrengthenComponent(uid, compud, respmsg);

	return 0;
}

int LogicHeroManager::OneKeyStrengthenComponent(unsigned uid, unsigned compud, ProtoHero::OneKeyStrengthenCompoResp *respmsg)
{
	//一键强化部件
	DataComponent& component = DataComponentManager::Instance()->GetComponent(uid, compud);

	if (component.heroid)
	{
		//验证英雄
		VerifyHeroRecruit(uid, component.heroid);
	}

	//在开始强化前，记录起始资源量
	DBCUserBaseWrap userwrap(uid);
	unsigned oldcoin = userwrap.Obj().coin;
	unsigned oldwood = userwrap.Obj().wood;

	vector<unsigned> delcompo;
	LogicComponentManager::Instance()->OneKeyStrengthenComponent(uid, compud, respmsg->mutable_compo(), delcompo);

	//记录删除的部件ud
	for(int i = 0; i < delcompo.size(); ++i)
	{
		respmsg->add_delcompos(delcompo[i]);
	}

	//记录消耗的资源
	unsigned diff_coin = oldcoin - userwrap.Obj().coin;
	unsigned diff_wood = oldwood - userwrap.Obj().wood;

	respmsg->mutable_coin()->set_value(diff_coin);
	respmsg->mutable_coin()->set_total_value(userwrap.Obj().coin);

	respmsg->mutable_wood()->set_value(diff_wood);
	respmsg->mutable_wood()->set_total_value(userwrap.Obj().wood);

	//判断部件是否属于某一个英雄，如果是，则要重新计算英雄属性
	if(component.heroid)
	{
		//重新计算英雄属性并发送英雄信息
		SetHeroMessage(uid, component.heroid, respmsg->mutable_hero());
	}

	return 0;
}

int LogicHeroManager::SetHeroMessage(unsigned uid, unsigned heroid, ProtoHero::HeroBaseInfoCPP * heromsg)
{
	//获得英雄信息
	DataHero & hero = DataHeroManager::Instance()->GetHero(uid, heroid);
	hero.SetMessage(heromsg);

	//todo 调用英雄属性计算接口
	CalcuteHeroProperty(uid, heroid, heromsg);

	return 0;
}

int LogicHeroManager::CalcuteHeroProperty(unsigned uid, unsigned heroid, ProtoHero::HeroBaseInfoCPP * hero)
{
	//计算英雄属性
	HeroFightAttr heroproperty;

	GetAllFightAttr(uid, heroid, heroproperty);

	int attack = heroproperty.GetAttr(DemoHeroProperty_attack);   //攻击
	int hp = heroproperty.GetAttr(DemoHeroProperty_hp);    //血量
	int defend = heroproperty.GetAttr(DemoHeroProperty_defend);   //防御
	int rule = heroproperty.GetAttr(DemoHeroProperty_int);   //统
	int courage = heroproperty.GetAttr(DemoHeroProperty_str);   //勇
	int power = heroproperty.GetAttr(DemoHeroProperty_power);

	hero->set_attack(attack);
	hero->set_hp(hp);
	hero->set_defend(defend);
	hero->set_rule(rule);
	hero->set_courage(courage);
	hero->set_power(power);

	return 0;
}

int LogicHeroManager::AddHeroProperty(unsigned uid, unsigned heroid)
{
	DataBase & base = BaseManager::Instance()->Get(uid);

	HeroPropertyItemIndex heroindex(uid, heroid);
	int ret = HeroPropertyManager::Instance()->Add(heroindex);
	if (ret)
	{
		error_log("[AddHeroProperty] add hero error. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("add_hero_error");
	}

	unsigned index = HeroPropertyManager::Instance()->GetIndex(heroindex);
	HeroPropertyItem & heroitem = HeroPropertyManager::Instance()->m_data->item[index];
	heroitem.city = BattleFieldManager::Instance()->getCapital(base.kingdom);

	unsigned extra_eqid = LogicEquipmentManager::Instance()->GetWingmanByHeroid(uid, heroid);
	heroitem.extraid = extra_eqid;  //副将id填上

	WMI->NewAddHero(heroindex, heroitem.city, base.kingdom);
	//debug_log("add hero uid=%u,id=%u,cid=%u", uid, heroid, heroitem.city);
	return 0;
}

int LogicHeroManager::VerifyHeroRecruit(unsigned uid, unsigned heroid)
{
	unsigned index = 0;

	DataHero & hero = DataHeroManager::Instance()->GetHero(uid, heroid, index);

	if (!hero.status)
	{
		error_log("[VerifyHeroRecruit] heroid is not recruit. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("hero_not_recruit");
	}

	//判断英雄是否在战斗记录的内存中
	HeroPropertyItemIndex heroindex(uid, heroid);

	if(!HMI->HasHero(heroindex))
	{
		error_log("[VerifyHeroRecruit] no_hero. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("no_hero");
	}

	//判断英雄是否在战斗中
	bool isFight = WorldManager::Instance()->IsHeroFighting(heroindex);

	if (isFight)
	{
		error_log("[VerifyHeroRecruit] heroid is fighting. uid=%u, heroid=%u", uid, heroid);
		throw std::runtime_error("hero_is_fighting");
	}

	return 0;
}

int LogicHeroManager::CalcuteParadeTimes(unsigned uid)
{
	DBCUserBaseWrap userwrap(uid);

	unsigned now = Time::GetGlobalTime();

	if (now < userwrap.Obj().silk)   //当前时间小于上次阅兵次数增加的时间，发生于更改服务器时间时
	{
		return 0;
	}

	unsigned diff = now - userwrap.Obj().silk;
	unsigned times = diff/parade_time_interval;

	if (0 == times)
	{
		return 0;
	}

	userwrap.Obj().silk = now;
	userwrap.Obj().banquet += times;

	if (userwrap.Obj().banquet > parade_times_max)   //阅兵次数达到上限，则取上限值
	{
		userwrap.Obj().banquet = parade_times_max;
	}

	userwrap.Save();

	return 0;
}

int LogicHeroManager::FullMessage(unsigned uid, User::Hero * heromsg)
{
	DataHeroManager::Instance()->FullMessage(uid, heromsg);

	int size = heromsg->hero_size();

	for(int i = 0; i < size; ++i)
	{
		int heroid = heromsg->hero(i).heroid();

		HeroPropertyItemIndex heroindex;
		heroindex.id = heroid;
		heroindex.uid = uid;

		 int index = HeroPropertyManager::Instance()->GetIndex(heroindex);

		 if (-1 == index)
		 {
			 continue;
		 }

		 try
		 {
			 //CalcuteHeroProperty(uid, heroid, heromsg->mutable_hero(i));
			 DBCHeroWrap(uid, heroid).FullMessage(heromsg->mutable_hero(i), false);
			 //add oulong 英雄的士兵数
			//this->FullMessage(uid, heroid, heromsg->add_soldiers());
			 HeroPropertyWrap(uid, heroid).FullMessage(heromsg->add_soldiers());
		 }
		 catch( const std::exception& e)
		 {
			 error_log("uid: %u, %s", uid, e.what());
		 }

	}

	return 0;
}

int LogicHeroManager::CheckDressMission(unsigned uid)
{
	//todo 接入穿戴装备任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_herodress;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//穿戴指定品质装备任务
	missionparam.type = mission_type_character_dress;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//接入指定数量装备的任务
	missionparam.type = mission_type_num_dress;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}


int LogicHeroManager::AdminFireHero(unsigned uid, bool isAdmin)
{
	if (!isAdmin)  //非管理标志，不得执行此操作
	{
		return 0;
	}

	vector<unsigned> vcthero;
	DataHeroManager::Instance()->GetRecruitHero(uid, vcthero);

	for(int i = 0; i < vcthero.size(); ++i)
	{
		//解雇英雄
		unsigned index = vcthero[i];
		DataHero & hero = DataHeroManager::Instance()->GetHeroByIndex(index);

		HeroPropertyItemIndex heroindex(uid, hero.heroid);
		WMI->RemoveHeroFromCity(heroindex, false);
		HeroPropertyManager::Instance()->Del(heroindex);

		//获取英雄信息
		hero.status = 0;
		DataHeroManager::Instance()->UpdateHero(index);

		//将英雄的装备放回仓库
		ProtoHero::EquipmentWrapCPP msg;
		LogicEquipmentManager::Instance()->UnDressAllEquipment(uid, hero.heroid, &msg);
	}

	return 0;
}

int LogicHeroManager::AdminRecuruitHero(unsigned uid, const BotConfig::BotHero * herocfgmsg, bool isAdmin)
{
	if (!isAdmin)  //非管理标志，不得执行此操作
	{
		return 0;
	}

	//判断英雄id是否存在
	unsigned heroid = herocfgmsg->heroid();
	unsigned level = herocfgmsg->level();

	bool isExist = DataHeroManager::Instance()->isHeroExists(uid, heroid);
	ProtoHero::HeroBaseInfoCPP  msg;

	if (!isExist)  //英雄不存在，即未解锁
	{
		//解锁英雄
		UnlockHero(uid, heroid, "ADMIN", &msg);
	}

	//更新英雄等级
	unsigned index = 0;
	DataHero & hero = DataHeroManager::Instance()->GetHero(uid, heroid, index);
	hero.level = level;

	DataHeroManager::Instance()->UpdateHero(index);

	//招募英雄
	RecruitHero(uid, heroid, true, &msg);

	//给英雄穿上装备
	for(int i = 0; i < herocfgmsg->equip_size(); ++i)
	{
		const BotConfig::BotEquipment & equipcfg = herocfgmsg->equip(i);

		DataEquipment equip;
		equip.uid = uid;
		equip.num = 1;

		equip.eqid = equipcfg.eqid();
		equip.heroid = heroid;
		equip.star = equipcfg.star();
		equip.born1 = equipcfg.born1();
		equip.born2 = equipcfg.born2();
		equip.subt1 = equipcfg.subt1();
		equip.sublv1 = equipcfg.sublv1();
		equip.subt2 = equipcfg.subt2();
		equip.sublv2 = equipcfg.sublv2();
		equip.subt3 = equipcfg.subt3();
		equip.sublv3 = equipcfg.sublv3();
		equip.subt4 = equipcfg.subt4();
		equip.sublv4 = equipcfg.sublv4();

		DataCommon::EquipmentCPP  equipmsg;

		LogicEquipmentManager::Instance()->AddEqupmentUnderlying(equip, "ADMIN", &equipmsg);
	}

	return 0;
}
