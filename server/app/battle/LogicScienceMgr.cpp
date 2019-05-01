/*
 * LogicScienceMgr.cpp
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */


#include "ServerInc.h"

DBCScienceWrap::DBCScienceWrap(unsigned uid, unsigned id)
	: container_(DataScienceMgr::Instance())
	, index_(container_->GetIndex(uid, id))
	, data_(container_->m_data->data[index_])
	, cfg_(ScienceCfgWrap().Item(id))
{
	Init();
}



DBCScienceWrap::DBCScienceWrap(unsigned uid, ScienceType type)
	: container_(DataScienceMgr::Instance())
	, index_(type2index(uid, type))
	, data_(container_->m_data->data[index_])
	, cfg_(ScienceCfgWrap().Item(data_.id))
{
	Init();
}

DBCScienceWrap::DBCScienceWrap(unsigned index)
	: container_(DataScienceMgr::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
	, cfg_(ScienceCfgWrap().Item(data_.id))
{
	Init();
}

void DBCScienceWrap::Init()
{
	if (data_.RefreshStatus(cfg_))
	{
		Save();

		if (data_.Normal())
		{
			//todo 更新状态
			LogicScienceMgr::Instance()->Finish(*this);
		}
	}
}

//
int DBCScienceWrap::type2index(unsigned uid, ScienceType type)
{
	ScienceCfgWrap sciencCfgWrap;
	DataScienceMgr* pDataScience = DataScienceMgr::Instance();
	//
	std::vector<uint16_t> vIds;
	sciencCfgWrap.GetIdsByType(type, vIds);

	std::vector<unsigned> vIndexs;
	pDataScience->GetIndexs(uid, vIds, vIndexs);
	//
	unsigned id = 0;
	int index = -1;
	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		DBCScience& item = pDataScience->m_data->data[vIndexs[i]];
		item.RefreshStatus(sciencCfgWrap.Item(item.id));
		if (item.Normal() && item.id > id)
		{
			id = item.id;
			index = vIndexs[i];
		}
	}

	if (index < 0)
	{
		//!!! 异常内容不要修改
		throw std::runtime_error("get_science_type_normal_item_error");
	}

	return index;
}

void DBCScienceWrap::Reset()
{
	data_.status = -1;
	data_.value = 0;

	Save();
}

void DBCScienceWrap::Capital()
{
	data_.Capital(cfg_);
	Save();

	if (data_.IsUnlocking())
	{
		LogicScienceMgr::Instance()->AddUnlockQueue(*this);
	}
}

void DBCScienceWrap::FinishUnlock()
{
	data_.FinishUnlock(cfg_);
	Save();

	if (data_.Normal())
	{
		//todo 更新状态
		LogicScienceMgr::Instance()->Finish(*this);
	}
}

void DBCScienceWrap::SetNormal()
{
	data_.FinishUnlock(cfg_);
	Save();
}

unsigned DBCScienceWrap::AttrValue() const
{
	return cfg_.val();
}

unsigned DBCScienceWrap::GetSurplusUnlockTime()
{
	unsigned now =  Time::GetGlobalTime();
	int need_time = data_.value  - now;
	if (need_time < 0)
	{
		//error_log("status: %d, value:%d, cfg_cd:%d", data_.status, data_.value, cfg_.cd());
		//throw std::runtime_error("status_error");
		return 0;
	}

	return need_time;
}

unsigned DBCScienceWrap::GetSpeedUnlockGolds()
{
	int need_time = GetSurplusUnlockTime();
	int need_cost = (need_time + 59) / 60 * cfg_.speed_cash();
	return need_cost;
}

////////////////////////////////////////////////////////////////////////////////////////
LogicScienceMgr::LogicScienceMgr()
{
	//////////////////////////////////////////////////////
	m_finish_table[S_TYPE_1] = &LogicScienceMgr::FinishHeroExpandFightAtrr;
	m_finish_table[S_TYPE_2] = &LogicScienceMgr::FinishHeroExpandFightAtrr;
	m_finish_table[S_TYPE_3] = &LogicScienceMgr::FinishHeroExpandFightAtrr;
	m_finish_table[S_TYPE_6] = &LogicScienceMgr::FinishHeroExpandFightAtrr;
	m_finish_table[S_TYPE_7] = &LogicScienceMgr::FinishHeroExpandFightAtrr;
	m_finish_table[S_TYPE_4] = NULL; //统帅力 //上阵英雄数
	m_finish_table[S_TYPE_5] = &LogicScienceMgr::FinishHeroBaseFightAttr;
	m_finish_table[S_TYPE_8] = &LogicScienceMgr::FinishBuildCapacity; //建筑容量
	m_finish_table[S_TYPE_9] = &LogicScienceMgr::SyncAttr2ResourceManager; //功勋宝箱等级
	m_finish_table[S_TYPE_11] = &LogicScienceMgr::FinishBuildCapacity;
	m_finish_table[S_TYPE_12] = &LogicScienceMgr::FinishBuildCapacity;
	m_finish_table[S_TYPE_13] = &LogicScienceMgr::FinishBuildCapacity;
	m_finish_table[S_TYPE_14] = &LogicScienceMgr::FinishBuildCapacity;

	////////////////////////////////////////////////////////////////////////
	lock_queue_.reserve(10000);

	try
	{
		typedef std::map<unsigned, std::map<uint16_t, unsigned> > S_MAP;
		const S_MAP&  all = DataScienceMgr::Instance()->GetAllMap();
		S_MAP::const_iterator it = all.begin();
		for (; it != all.end(); ++it)
		{
			std::map<uint16_t, unsigned>::const_iterator it_user = it->second.begin();
			for (; it_user != it->second.end(); ++it_user)
			{
				DBCScienceWrap science(it_user->second);
				if (science.Obj().IsUnlocking())
				{
					this->AddUnlockQueue(science);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
	}
}

unsigned	LogicScienceMgr::GetScienceId(unsigned uid, ScienceType type)
{
	try
	{
		return DBCScienceWrap(uid, type).Obj().id;
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			return 0;
		}
		else
		{
			error_log("uid:%u, type:%d, %s", uid, type, e.what());
		}
	}

	return 0;
}

DemoOfflineProperty LogicScienceMgr::_Type2Prop(ScienceType type)
{
	switch (type)
	{
		case S_TYPE_1: return DemoOfflineProperty_hexp;
		case S_TYPE_2: return DemoOfflineProperty_s_level;
		case S_TYPE_3: return DemoOfflineProperty_soldier;
		case S_TYPE_6: return DemoOfflineProperty_tech;
		case S_TYPE_7: return DemoOfflineProperty_anti_tech;
		case S_TYPE_9: return DemoOfflineProperty_b_level;
		default: break;
	}

	error_log("type: %d", type);
	throw std::runtime_error("nonsupport_type");
}

unsigned LogicScienceMgr::_TypeValue(ScienceType type, const DBCScienceWrap& science)
{
	if (type == S_TYPE_1
			|| type == S_TYPE_6 || type == S_TYPE_7)
	{
		if (type == S_TYPE_1)
		{
			unsigned uid = science.Obj().uid;
			try
			{
				//vip的战斗经验奖励配置在科技配置中
				if (DBCUserBaseWrap(uid).VIPPower().GetFightExpAdd() > 0)
				{
					unsigned new_id_val = science.Obj().id + 900;

					if (ScienceCfgWrap().IsExistId(new_id_val))
					{
						return new_id_val;
					}
				}
			}
			catch(const std::exception& e)
			{
				error_log("uid:%u, %s", uid, e.what());
			}
		}

		return science.Obj().id;
	}
	else if (type == S_TYPE_2 || type == S_TYPE_3 || type == S_TYPE_9)
	{
		//return science.Obj().value;
		return science.AttrValue();
	}
	else
	{
		error_log("type: %d", type);
		throw std::runtime_error("nonsupport_type");
	}
}

unsigned LogicScienceMgr::_TypeValue(ScienceType type, unsigned uid)
{
	if (type == S_TYPE_1
			|| type == S_TYPE_6 || type == S_TYPE_7)
	{
		unsigned id_val = this->GetScienceId(uid, type);

		if (type == S_TYPE_1)
		{
			try
			{
				//vip的战斗经验奖励配置在科技配置中
				if (DBCUserBaseWrap(uid).VIPPower().GetFightExpAdd() > 0)
				{
					unsigned new_id_val = id_val + 900;

					if (ScienceCfgWrap().IsExistId(new_id_val))
					{
						return new_id_val;
					}
				}
			}
			catch(const std::exception& e)
			{
				error_log("uid:%u, %s", uid, e.what());
			}
		}

		return id_val;
	}
	else if (type == S_TYPE_2)
	{
		return this->GetSoldierLevel(uid);
	}
	else if (type == S_TYPE_3)
	{
		return this->GetSoldierRows(uid);
	}
	else if (type == S_TYPE_9)
	{
		return this->GetExploitBoxLevel(uid);
	}
	else
	{
		error_log("type: %d", type);
		throw std::runtime_error("nonsupport_type");
	}
}

void LogicScienceMgr::Finish(const DBCScienceWrap& science)
{
	//更新对应的属性
	ScienceType type = (ScienceType)science.Cfg().type();
	std::map<ScienceType, ScienceFinishImpl>::iterator it = m_finish_table.find(type);
	if (it != m_finish_table.end())
	{
		ScienceFinishImpl impl = it->second;
		if (impl != NULL)
		{
			(this->*impl)(science);
		}
	}

	//推送任务完成给客户端
	ProtoPush::ScienceFinish* msg = new ProtoPush::ScienceFinish;
	science.Obj().FullMessage(msg->mutable_science());
	LogicManager::Instance()->sendMsg(science.Obj().uid, msg);

	//todo 接入科技成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_tech_research;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(science.Obj().uid, achievementparam);

	//接入科技完成任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_tech_done;
	LogicMissionManager::Instance()->VerifyMissionComplete(science.Obj().uid, missionparam);
}

void LogicScienceMgr::SyncAttr2ResourceManager(const DBCScienceWrap& science)
{
	ScienceType type = (ScienceType)science.Cfg().type();
	try
	{
		DemoOfflineProperty prop = _Type2Prop(type);
		unsigned val = _TypeValue(type, science);

		LogicResourceManager::Instance()->SyncPropertyValue(science.Obj().uid, prop, val);
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}

void LogicScienceMgr::FinishHeroExpandFightAtrr(const DBCScienceWrap& science)
{
	SyncAttr2ResourceManager(science);

	LogicHeroManager::Instance()->SyncUserHerosInfo(science.Obj().uid);

	//modify 20161028 兵种升级，募兵速率有修改
	ScienceType type = (ScienceType)science.Cfg().type();
	if (type == S_TYPE_2)
	{
		LogicBuildManager::Instance()->SyncRecruitRate(science.Obj().uid);
	}
}

void LogicScienceMgr::FinishHeroBaseFightAttr(const DBCScienceWrap& science)
{
	LogicHeroManager::Instance()->SyncUserHerosInfo(science.Obj().uid);
}

void LogicScienceMgr::FinishBuildCapacity(const DBCScienceWrap& science)
{
	//推送到客户端
	ProtoPush::BuildYieldInfo* msg = new ProtoPush::BuildYieldInfo;
	if (msg)
	{
		for (int i = DataBuildingManager::FOLK_HOUSE_TYPE;
				i <= DataBuildingManager::BARRACKS_TYPE;
				++i)
		{
			LogicBuildManager::Instance()->FullMessage(science.Obj().uid, i, msg->add_yield());
		}

		LogicManager::Instance()->sendMsg(science.Obj().uid, msg);
	}
}


void LogicScienceMgr::Sync(unsigned uid, OfflineResourceItem& item)
{
	const ScienceType types[6] = {S_TYPE_1, S_TYPE_2, S_TYPE_3, S_TYPE_6, S_TYPE_7, S_TYPE_9};
	for (int i = 0; i < 6; ++i)
	{
		item.property[_Type2Prop(types[i])] = _TypeValue(types[i], uid);
	}
}

bool LogicScienceMgr::IsScienceBeginResearch(unsigned uid, unsigned id)
{
	DBCScienceWrap dbcScienceWrap(uid, id);
	return (dbcScienceWrap.Obj().IsUnlocking() || dbcScienceWrap.Obj().Normal());
}

bool LogicScienceMgr::IsScienceDoneResearch(unsigned uid, unsigned id)
{
	DBCScienceWrap dbcScienceWrap(uid, id);
	return (dbcScienceWrap.Obj().Normal());
}

/*
 *
 */
int LogicScienceMgr::GetSoldierLevel(unsigned uid)
{
	try
	{
		return DBCScienceWrap(uid, S_TYPE_2).AttrValue();
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			return 1;
		}
		else
		{
			throw e;
		}
	}

	return 1;
}

int LogicScienceMgr::GetSoldierRows(unsigned uid)
{
	try
	{
		return DBCScienceWrap(uid, S_TYPE_3).AttrValue();
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			int npc_pass = BaseManager::Instance()->Get(uid).npc_pass;
			return (npc_pass >= 1) ? 2 : 1;
		}
		else
		{
			throw e;
		}
	}

	return 0;
}

int LogicScienceMgr::GetHeroFightFactor(unsigned uid)
{
	return GetTypeValue(uid, S_TYPE_5, 0);
}

int LogicScienceMgr::GetRecruitHeros(unsigned uid)
{
	try
	{
		return DBCScienceWrap(uid, S_TYPE_4).AttrValue();
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			int npc_pass = BaseManager::Instance()->Get(uid).npc_pass;
			return (npc_pass >= 4) ? 2 : 1;
		}
		else
		{
			throw e;
		}
	}

	return 0;
}

int LogicScienceMgr::ResourceType2ScienceType(int type)
{
	switch (type)
	{
		case DataBuildingManager::FOLK_HOUSE_TYPE:  return S_TYPE_11;
		case DataBuildingManager::TIMBER_YARD_TYPE: return S_TYPE_12;
		case DataBuildingManager::FARMLAND_TYPE: 	return S_TYPE_13;
		case DataBuildingManager::MINE_FIELD_TYPE: 	return S_TYPE_14;
		case DataBuildingManager::BARRACKS_TYPE: 	return -1;
		default:
		{
			error_log("unknown_resource: %d", type);
			throw std::runtime_error("unknown_resource type");
		}
	}
}

int LogicScienceMgr::GetYieldFactor(unsigned uid, int type)
{
	try
	{
		int nScienceType = ResourceType2ScienceType(type);
		if (nScienceType > 0)
		{
			ScienceType eType = (ScienceType)(nScienceType);
			return DBCScienceWrap(uid, eType).AttrValue();
		}
		else
		{
			return 0;
		}

	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			return 0;
		}
		else
		{
			throw e;
		}
	}

	return 0;
}

int LogicScienceMgr::GetStorageFactor(unsigned uid)
{
	return GetTypeValue(uid, S_TYPE_8, 0);
}

int LogicScienceMgr::GetExploitBoxLevel(unsigned uid)
{
	return GetTypeValue(uid, S_TYPE_9, 1);
}

int LogicScienceMgr::GetDayTaskLevel(unsigned uid)
{
	return GetTypeValue(uid, S_TYPE_15, 1);
}

int LogicScienceMgr::GetCountryWarLevel(unsigned uid)
{
	return GetTypeValue(uid, S_TYPE_17, 1);
}

bool LogicScienceMgr::IsBuildExploit(unsigned uid)
{
	try
	{
		return DBCScienceWrap(uid, S_TYPE_10).Obj().Normal();
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			return false;
		}
		else
		{
			error_log("uid: %u, %s", uid, e.what());
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LogicScienceMgr::CheckIdParams(unsigned id)
{

}

void LogicScienceMgr::Online(unsigned uid)
{
	DataScienceMgr::Instance()->Online(uid);
}

void LogicScienceMgr::Offline(unsigned uid)
{
	DataScienceMgr::Instance()->Offline(uid);
}

void LogicScienceMgr::Reset(unsigned uid)
{
	RemoveFromUnlockQueue(uid);

	std::vector<unsigned> result;
	DataScienceMgr::Instance()->GetSciences(uid, result);
	for (size_t i = 0; i < result.size(); ++i)
	{
		DBCScienceWrap(result[i]).Reset();
	}
}


int LogicScienceMgr::Process(unsigned uid, ProtoScience::ScienceCapitalReq* req, ProtoScience::ScienceCapitalResp* resp)
{
	unsigned id = req->id();
	CheckIdParams(id);

	DBCScienceWrap dbcScienceWrap(uid, id);
//	if (dbcScienceWrap.Obj().Normal() || dbcScienceWrap.Obj().IsUnlocking())
//	{
//		throw std::runtime_error("status_error");
//	}

	DBCUserBaseWrap userWrap(uid);
	if(dbcScienceWrap.Obj().IsCanCapital())
	{
		//const DataBase& user = BaseManager::Instance()->Get(uid);
		const ScienceConfig::ScienceItem& scienceCfg = ScienceCfgWrap().Item(id);
		if (! dbcScienceWrap.Obj().IsCapitaling())
		{
			//TODO 关卡检查  前置任务检查
			if (userWrap.Obj().npc_pass < scienceCfg.pass())
			{
				throw std::runtime_error("unlock_pass");
			}

			if (scienceCfg.pre_lock_id() > 0)
			{
				DBCScienceWrap preScienceWrap(uid, scienceCfg.pre_lock_id());
				if (! preScienceWrap.Obj().Normal())
				{
					throw std::runtime_error("pre_scicece_item_unlock");
				}
			}
		}

		userWrap.CostUserResource(
				  scienceCfg.cost_coins()
				, scienceCfg.cost_wood()
				, scienceCfg.cost_food()
				, scienceCfg.cost_iron(), "science_capital_op");

		//todo 注资成功
		dbcScienceWrap.Capital();

		if (dbcScienceWrap.Obj().IsUnlocking())
		{
			//todo 接入科技任务接口
			LogicMissionManager::MissionParam missionparam;
			missionparam.type = mission_type_tech_research;
			LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);
		}
	}

	if (resp)
	{
		dbcScienceWrap.Obj().FullMessage(resp->mutable_item());
		resp->set_coin(userWrap.Obj().coin);
		resp->set_wood(userWrap.Obj().wood);
		resp->set_food(userWrap.Obj().food);
		resp->set_iron(userWrap.Obj().iron);
	}

	return R_SUCCESS;
}

int LogicScienceMgr::Process(unsigned uid, ProtoScience::ScienceSpeedCdReq* req, ProtoScience::ScienceSpeedCdResp* resp)
{
	unsigned id = req->id();
	CheckIdParams(id);

	DBCScienceWrap dbcScienceWrap(uid, id);
	if (! dbcScienceWrap.Obj().IsUnlocking())
	{
		throw std::runtime_error("status_error");
	}

	int need_cost = dbcScienceWrap.GetSpeedUnlockGolds();

	unsigned up_cash = 0;
	std::string reason = "science_speed_cd_op";
	LogicUserManager::Instance()->CostCash(uid, need_cost, reason, up_cash);

	//science
	dbcScienceWrap.FinishUnlock();
	if (resp)
	{
		dbcScienceWrap.Obj().FullMessage(resp->mutable_item());
		resp->set_cash(up_cash);
	}

	return R_SUCCESS;
}

void LogicScienceMgr::FullMessage(unsigned uid, User::Science* obj)
{
	std::vector<unsigned> result;
	DataScienceMgr::Instance()->GetSciences(uid, result);
	for (size_t i = 0; i < result.size(); ++i)
	{
		DBCScienceWrap science(result[i]);
		science.Obj().FullMessage(obj->add_items());
	}

	obj->set_soldiers_level(GetSoldierLevel(uid));
	obj->set_soldiers_row(GetSoldierRows(uid));
	obj->set_recruit_hero_capacity(GetRecruitHeros(uid));
	obj->set_exploit_box_level(GetExploitBoxLevel(uid));
}

void LogicScienceMgr::SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj)
{
	if (NULL == obj) return ;

	for (int i = 0; i < obj->science_size(); i++)
	{
		DBCScienceWrap(uid, obj->science(i)).SetNormal();
	}
}

void LogicScienceMgr::AddUnlockQueue(const DBCScienceWrap& science)
{
	lock_queue_.push_back(_UnlockItem(science));
}

void LogicScienceMgr::RemoveFromUnlockQueue(unsigned uid)
{
	for (std::vector<_UnlockItem>::iterator it = lock_queue_.begin();
			it != lock_queue_.end();)
	{
		if (it->uid == uid)
		{
			it = lock_queue_.erase(it);
		}
		else
		{
			++it;
		}
	}
}

int LogicScienceMgr::GetTypeValue(unsigned uid,  ScienceType type, int default_val)
{
	try
	{
		return DBCScienceWrap(uid, type).Cfg().val();
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_science_type_normal_item_error")
		{
			return default_val;
		}
		else
		{
			error_log("uid: %u,type:%d, %s", uid, type, e.what());
			throw e;
		}
	}

	return default_val;
}

void LogicScienceMgr::OnTimer1()
{
	for (std::vector<_UnlockItem>::iterator it = lock_queue_.begin();
			it != lock_queue_.end();)
	{
		try
		{
			--it->surplus;

			if (it->surplus <= 0)
			{
				DBCScienceWrap dbcScienceWrap(it->uid, it->id);
				if (dbcScienceWrap.Obj().Normal())
				{
					it = lock_queue_.erase(it);
					continue;
				}
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
		}

		++it;
	}
}





