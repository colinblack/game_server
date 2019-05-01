/*
 * LogicBuildingManager.cpp
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */


#include "LogicBuildManager.h"


void DBCBuildingDataWrap::Init()
{
	int ret = data_.RefreshStatus();
	if (ret > 0)
	{
		Save();
	}

	if (ret == 2)
	{
		FinishUpgrade();
	}
	else if (ret == 1)
	{
		SyncYield();

		//接入升级外部接口
		UpgradeExternalInterface();
	}
}

unsigned DBCBuildingDataWrap::_Index(unsigned index)
{
	return index;
}

DBCBuildingDataWrap::DBCBuildingDataWrap(unsigned uid, unsigned buildid)
		: container_(DataBuildingManager::Instance())
		, index_(container_->GetIndex(uid, buildid))
		, data_(container_->m_data->data[index_])
		, type_(container_->BuildId2Type(data_.id))
{
	Init();
}

DBCBuildingDataWrap::DBCBuildingDataWrap(unsigned index)
	: container_(DataBuildingManager::Instance())
	, index_(_Index(index))
	, data_(container_->m_data->data[index_])
	, type_(container_->BuildId2Type(data_.id))
{
	Init();
}

DBCBuildingDataWrap::~DBCBuildingDataWrap()
{
	//Save();
}

void DBCBuildingDataWrap::Unlock()
{
	if (data_.Unlock())
	{
		Save();

#if 0
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_upgrade_building;
		LogicMissionManager::Instance()->VerifyMissionComplete(data_.uid, missionparam);

		SyncYield();
#endif
	}
}

void DBCBuildingDataWrap::FreeSpeed()
{
	int oldlevel = data_.level;
	data_.FreeSpeed();

	Save();
	int newlevel = data_.level;

	if (newlevel > oldlevel)  //升级处理
	{
		FinishUpgrade();
	}
}

void DBCBuildingDataWrap::OnceFinishUpgrade()
{
	if (data_.Upgrading())
	{
		data_.OnceFinishUpgrade();
		FinishUpgrade();
	}

	Save();
}

void DBCBuildingDataWrap::SyncYield()
{
	try
	{
		if (type_ == DataBuildingManager::BARRACKS_TYPE)
		{
			unsigned yield = LogicBuildManager::Instance()->RecruitRate(data_.uid);
			LogicResourceManager::Instance()->SyncRecruitRate(data_.uid, yield);
		}
	}
	catch(const std::exception& e)
	{
		(void)e;
	}

	//推送到客户端
	ProtoPush::BuildYieldInfo* msg = new ProtoPush::BuildYieldInfo;
	if (msg)
	{
		LogicBuildManager::Instance()->FullMessage(data_.uid, type_, msg->add_yield());
		LogicManager::Instance()->sendMsg(data_.uid, msg);
	}

	//产量任务
	ProductExternalInterface();
}

void DBCBuildingDataWrap::FinishUpgrade()
{
	BuildCfgWrap buildCfg;
	const Building::LvLs& lvlsCfg = buildCfg.LvLs(data_.id, data_.level);
	//升级完成
	DBCUserBaseWrap user(data_.uid);
	user.AddExp(lvlsCfg.out_exp());

	if (LogicScienceMgr::Instance()->IsBuildExploit(data_.uid))
	{
		user.AddBuildExploit(lvlsCfg.out_exploit());
	}

	SyncYield();

	//接入建筑升级外部接口
	UpgradeExternalInterface();
}

int DBCBuildingDataWrap::ProductExternalInterface()
{
	//todo 接入产量任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_productivity;
	LogicMissionManager::Instance()->VerifyMissionComplete(data_.uid, missionparam);

	//todo 接入每日产量任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_productivity;
	dailymissionparam.subparam.push_back(type_);  //传递建筑类型

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(data_.uid, dailymissionparam);

	//接入产量成就
	LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_productivity;
	achievementparam.subparam.push_back(type_);  //传递建筑类型
	LogicAchievementManager::Instance()->VerifyAchievementComplete(data_.uid, achievementparam);

	return 0;
}

int DBCBuildingDataWrap::UpgradeExternalInterface()
{
	//todo 接入任务接口
	//建筑升级任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_upgrade_building;
	LogicMissionManager::Instance()->VerifyMissionComplete(data_.uid, missionparam);

	//接入政务事件接口
	LogicUserManager::Instance()->VerifyGovernAffairTimes(data_.uid, data_.id);

	return 0;
}

int DBCBuildingDataWrap::Upgrade(unsigned startTime)
{
	int ret = DBCUserBaseWrap(data_.uid).BuildUpgrade(data_.id, data_.level + 1);
	if (ret != R_SUCCESS)
	{
		return ret;
	}

	data_.Upgrade(startTime);
	Save();

	return R_SUCCESS;
}

void DBCBuildingDataWrap::FullMessage(::ProtoBuilding::BuildInfo* obj)
{
	data_.FullMessage(obj);
}


////////////////////////////////////////////////////////////////////////////////////
DBCBuildingQueueDataWrap::DBCBuildingQueueDataWrap(unsigned uid)
	: container_(DataBuildQueue::Instance())
	, index_(container_->UserId2Index(uid))
	, data_(container_->m_data->data[index_])
{
	bool bChange = false;
	do
	{
		//检查建造队列是否完成
		for (int i = 0; i < DBCBuidingQueueData::capacity; ++i)
		{
			if (data_.QueueIsBusy(i))
			{
				DBCBuildingDataWrap dbcBuilds(uid, data_.QueueBuild(i));
				if (! dbcBuilds.Obj().Upgrading())
				{
					data_.QueueOverWork(i, dbcBuilds.Obj().OverHandleTime());
					bChange = true;
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////
		//处理自动升级
		if (! data_.IsAutoUpgrade()) break;

		int nCnt = data_.FreeQueueCnt();
		if (nCnt <= 0) break;

		std::vector<unsigned> vBuildsIndex;
		//获取的是数据偏移位置
		this->GetAutoUpgradeBuilds(uid, nCnt, data_.type, vBuildsIndex);
		if (vBuildsIndex.empty()) break;

		int flag = true;
		for (size_t i = 0; i < vBuildsIndex.size(); ++i)
		{
			int wk_index = data_.GetEmpty();
			if (wk_index >= 0)
			{
				DBCBuildingDataWrap buildingWrap(vBuildsIndex[i]);
				if (R_SUCCESS == buildingWrap.Upgrade(data_.QueueOverTime(wk_index)))
				{
					data_.QueueUpgrade(wk_index, buildingWrap.Obj().id);
					bChange = true;

					data_.DecAutoUpgrade();
				}
				else
				{
					flag = false; break;
				}
			}
			else
			{
				flag = false; break;
			}
		}

		if (! flag) break;

	}while(1);

	if (bChange)
	{
		Save();
	}
}

int DBCBuildingQueueDataWrap::Upgrade(unsigned index, unsigned build_id)
{
	data_.QueueUpgrade(index, build_id);
	Save();
	return R_SUCCESS;
}

void DBCBuildingQueueDataWrap::Unlock(unsigned cnt)
{
	data_.Unlock(cnt);
	Save();
}

void DBCBuildingQueueDataWrap::SetAutoUpgrade(uint8_t build_type, int16_t cnt)
{
	data_.SetAutoUpgrade(build_type, cnt);
	Save();
}


void DBCBuildingQueueDataWrap::AbolishAutoUpgrade()
{
	data_.AbolishAutoUpgrade();
	Save();
}

void DBCBuildingQueueDataWrap::GetAutoUpgradeBuilds(unsigned uid, int cnt, int type, std::vector<unsigned>& vBuilds)
{
	vBuilds.clear();

	if (cnt <= 0) return;

	//@type = 0为全部
	std::vector<unsigned> allBuildsIndex;
	//DataBuildingManager::Instance()->GetBuildIds(uid, type, allBuilds);
	DataBuildingManager::Instance()->IndexsBuildsByType(uid, type, allBuildsIndex);
	while(cnt > 0)
	{
		const DataBase&  baseUser = BaseManager::Instance()->Get(uid);
		//建筑等级必须比玩家等级小
		int level = baseUser.level;
		int index = -1;
		for (size_t i = 0; i < allBuildsIndex.size(); i++)
		{
			DBCBuildingDataWrap dbcBuild(allBuildsIndex[i]);
			if (dbcBuild.Obj().Normal() && (int)dbcBuild.Obj().level < level)
			{
				index = i;
				level = (int)dbcBuild.Obj().level;
			}
		}

		if (index >= 0)
		{
			int buildIndex = allBuildsIndex[index];
			allBuildsIndex.erase(allBuildsIndex.begin() + index);

			vBuilds.push_back(buildIndex);
		}
		else
		{
			break;
		}

		--cnt;
	}
}

void DBCBuildingQueueDataWrap::FullMessage(ProtoBuilding::BuildQueue* obj)
{
	data_.FullMessage(obj);
}

///////////////////////////////////////////////////////////////////////////////////
LogicBuildManager::LogicBuildManager()
{
};

const DataBase& LogicBuildManager::UserData(unsigned uid) const
{
	int index = BaseManager::Instance()->GetIndex(uid);
	if (index < 0)
	{
		error_log("uid: %u, index=%u", uid, index);
		throw std::runtime_error("get_user_info_from_buff_error");
	}

	return  BaseManager::Instance()->m_data->data[index];
}

int LogicBuildManager::BuildId2Type(unsigned id) const
{
	int type = id / 100;
	if (type < DataBuildingManager::FOLK_HOUSE_TYPE  || type > DataBuildingManager::BARRACKS_TYPE)
	{
		error_log("build_id: %d", id);
		throw std::runtime_error("build_id_cfg_error");
	}

	return type;
}

void LogicBuildManager::CheckParamsBuildId(unsigned id) const
{
	int type = id / 100;
	int child_id = id % 100;

	if (type < 1 || type > 5)
	{
		throw std::runtime_error("build_id_params_error");
	}

	if (child_id < 1 || child_id > 16)
	{
		throw std::runtime_error("build_id_params_error");
	}
}

void LogicBuildManager::FullMessageInLogin(unsigned uid, User::Building* obj)
{
	if (obj)
	{
		DBCBuildingQueueDataWrap buildQueueWrap(uid);
		buildQueueWrap.FullMessage(obj->mutable_queue());

		std::vector<unsigned> vBuilds;
		DataBuildingManager::Instance()->GetBuildIds(uid, 0, vBuilds);
		for (size_t i = 0; i < vBuilds.size(); i++)
		{
			//DBCBuildingData& build = this->Get(uid, vBuilds[i]);
			DBCBuildingDataWrap buildWrap(uid, vBuilds[i]);
			buildWrap.FullMessage(obj->add_builds());
		}


		for (int i = DataBuildingManager::FOLK_HOUSE_TYPE;
				i <= DataBuildingManager::BARRACKS_TYPE;
				++i)
		{
			this->FullMessage(uid, i, obj->add_yield());
		}
	}
}

void LogicBuildManager::FullMessage(unsigned uid, int type, ProtoBuilding::BuildYield* obj)
{
	unsigned yield = 0;
	unsigned capatity = 0;
	if (type == DataBuildingManager::BARRACKS_TYPE)
	{
		//换算成每每分钟的产量
		yield = LogicBuildManager::Instance()->RecruitRate(uid) * 12;
	}
	else
	{
		yield = LogicBuildManager::Instance()->Yields(uid, type);
		capatity = LogicBuildManager::Instance()->GetCapacity(uid, type);
	}

	//推送到客户端
	obj->set_type(type);
	obj->set_yield(yield);
	obj->set_capacity(capatity);
}

unsigned LogicBuildManager::RecruitRate(unsigned uid)
{
	enum {
		RECRUIT_RATE_INIT = 111,
	};
	//兵营的产量单位为分钟
	unsigned nYields = this->Yields(uid,  DataBuildingManager::BARRACKS_TYPE);

	//兵种等级
	unsigned s_lvl = LogicScienceMgr::Instance()->GetSoldierLevel(uid);
	float rate_factor = HeroCfgWrap().GetRecruitRateFactor(s_lvl);

	return (nYields / 60 / 12 + RECRUIT_RATE_INIT)*rate_factor;
}

unsigned LogicBuildManager::GetCapacity(unsigned uid, int type)
{
	unsigned capacity = this->Capacity(uid, type);
	try
	{
		int nFactor = LogicScienceMgr::Instance()->GetStorageFactor(uid);
		if (nFactor > 0)
		{
			capacity += capacity * nFactor / 100;
		}

		return capacity;
	}
	catch (const std::exception& e)
	{
		error_log("uid: %d, type:%d, %s",uid, type, e.what());
	}

	return capacity;
}

void LogicBuildManager::SyncRecruitRate(unsigned uid)
{
	unsigned yield = RecruitRate(uid);
	LogicResourceManager::Instance()->SyncRecruitRate(uid, yield);

	int type = DataBuildingManager::BARRACKS_TYPE;
	//推送到客户端
	ProtoPush::BuildYieldInfo* msg = new ProtoPush::BuildYieldInfo;
	if (msg)
	{
		LogicBuildManager::Instance()->FullMessage(uid, type, msg->add_yield());
		LogicManager::Instance()->sendMsg(uid, msg);
	}
}

void LogicBuildManager::SyncYield(unsigned uid)
{
	//推送到客户端
	ProtoPush::BuildYieldInfo* msg = new ProtoPush::BuildYieldInfo;
	for (int  type = DataBuildingManager::FOLK_HOUSE_TYPE
			; type <= DataBuildingManager::BARRACKS_TYPE
			; ++type)
	{
		try
		{
			if (type == DataBuildingManager::BARRACKS_TYPE)
			{
				unsigned yield = LogicBuildManager::Instance()->RecruitRate(uid);
				LogicResourceManager::Instance()->SyncRecruitRate(uid, yield);
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
		}


		if (msg)
		{
			LogicBuildManager::Instance()->FullMessage(uid, type, msg->add_yield());
		}
	}

	LogicManager::Instance()->sendMsg(uid, msg);
}

void LogicBuildManager::SyncYield(unsigned uid, int type)
{
	try
	{
		if (type == DataBuildingManager::BARRACKS_TYPE)
		{
			unsigned yield = LogicBuildManager::Instance()->RecruitRate(uid);
			LogicResourceManager::Instance()->SyncRecruitRate(uid, yield);
		}
	}
	catch(const std::exception& e)
	{
		(void)e;
	}

	//推送到客户端
	ProtoPush::BuildYieldInfo* msg = new ProtoPush::BuildYieldInfo;
	if (msg)
	{
		LogicBuildManager::Instance()->FullMessage(uid, type, msg->add_yield());
		LogicManager::Instance()->sendMsg(uid, msg);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildSyncReq* msg,  ProtoBuilding::BuildSyncResp* resp)
{
	unsigned type = msg->type();
	if (type > 5)
	{
		throw std::runtime_error("build_type_params_error");
	}

	if (resp)
	{
		resp->set_type(type);

		DBCBuildingQueueDataWrap buildQueueWrap(uid);
		buildQueueWrap.FullMessage(resp->mutable_queue());

		//用户信息
		const DataBase& userData = UserData(uid);
		userData.FullBuildSyncMessage(resp->mutable_user());

		std::vector<unsigned> vBuilds;
		//DataBuildingManager::Instance()->GetBuildIds(uid, type, vBuilds);
		DataBuildingManager::Instance()->GetBuildIds(uid, 0, vBuilds);
		for (size_t i = 0; i < vBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildWrap(uid, vBuilds[i]);
			buildWrap.FullMessage(resp->add_builds());
		}
	}


	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildUnlockReq* msg, ProtoBuilding::BuildUnlockResp* reply)
{
	int type = -1;
	std::vector<unsigned> vUnlocks;
	for (int i = 0;  i < msg->ids_size(); i++)
	{
		unsigned id = msg->ids(i);
		CheckParamsBuildId(id);

		if (type < 0)
		{
			type = BuildId2Type(id);
		}
		else
		{
			if (type != BuildId2Type(id))
			{
				throw std::runtime_error("unlock_builds_need_same_type");
			}
		}

		BuildCfgWrap buildCfg;
		const DataBase& user = UserData(uid);
		const Building::Item& buildItemCfg = buildCfg.Item(id);

		if (user.level < buildItemCfg.unlock_lvl())
		{
			//todo error;
			throw std::runtime_error("user_level_not_enough");
		}

		vUnlocks.push_back(id);
	}

	if (type < 0)
	{
		return R_ERROR;
	}

	for (size_t i = 0; i < vUnlocks.size(); i++)
	{
		DBCBuildingDataWrap buildDataWrap(uid, vUnlocks[i]);
		buildDataWrap.Unlock();
	}

	//
	if (msg->has_lock_queue())
	{
		DBCBuildingQueueDataWrap buildingQueueWrap(uid);
		buildingQueueWrap.Unlock(1);
	}

	//
	if (reply)
	{
		DBCBuildingQueueDataWrap buildingQueueWrap(uid);
		buildingQueueWrap.FullMessage(reply->mutable_build_queue());

		//建筑信息
		std::vector<unsigned> vBuilds;
		DataBuildingManager::Instance()->GetBuildIds(uid, type, vBuilds);
		for (size_t i = 0; i < vBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildWrap(uid, vBuilds[i]);
			buildWrap.FullMessage(reply->add_builds());
		}
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildUpgradeReq* msg, ProtoBuilding::BuildUpgradeResp* reply)
{
	unsigned buildid = (unsigned)(msg->id());
	CheckParamsBuildId(buildid);
	//队列
	DBCBuildingQueueDataWrap buildingQueueWrap(uid);
	int build_q_index = buildingQueueWrap.Obj().GetEmpty();
	if (build_q_index < 0)
	{
		throw std::runtime_error("build_queue_busy");
	}

	DBCBuildingDataWrap buildWrap(uid, buildid);
	if (! buildWrap.Obj().Normal())
	{
		throw std::runtime_error("cur_status_not_upgrade");
	}

	//
	int ret = buildWrap.Upgrade(Time::GetGlobalTime());
	if (ret != R_SUCCESS)
	{
		return ret;
	}

	buildingQueueWrap.Upgrade(build_q_index, buildid);

	//消息回复
	if (reply)
	{
		reply->set_id(buildid);

		//建筑队列
		DBCBuildingQueueDataWrap up_buildingQueueWrap(uid);
		up_buildingQueueWrap.FullMessage(reply->mutable_build_queue());
		//用户信息
		const DataBase& userData = UserData(uid);
		userData.FullBuildSyncMessage(reply->mutable_user());

		//建筑信息
		std::vector<unsigned> vBuilds;
		int build_type = DataBuildingManager::Instance()->BuildId2Type(buildid);
		DataBuildingManager::Instance()->GetBuildIds(uid, build_type, vBuilds);
		for (size_t i = 0; i < vBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildWrap(uid, vBuilds[i]);
			buildWrap.FullMessage(reply->add_builds());
		}
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildFreeSpeedReq* msg, ProtoBuilding::BuildSyncResp* resp)
{
	unsigned buildid = (unsigned)(msg->id());
	CheckParamsBuildId(buildid);

	DBCBuildingDataWrap buildingWrap(uid, buildid);
	buildingWrap.FreeSpeed();

	if (resp)
	{
		DBCBuildingQueueDataWrap buildQueueWrap(uid);
		buildQueueWrap.FullMessage(resp->mutable_queue());

		//用户信息
		const DataBase& userData = UserData(uid);
		userData.FullBuildSyncMessage(resp->mutable_user());

		std::vector<unsigned> vBuilds;
		DataBuildingManager::Instance()->GetBuildIds(uid, BuildId2Type(buildid), vBuilds);
		for (size_t i = 0; i < vBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildWrap(uid, vBuilds[i]);
			buildWrap.FullMessage(resp->add_builds());
		}
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildOverOnceReq* msg, ProtoBuilding::BuildOverOnceResp* resp)
{
	DBCUserBaseWrap user(uid);

	const unsigned cost_cash = 20; //没有锤子消耗钻石
	std::vector<unsigned> vBuilds;
	DBCBuildingQueueDataWrap buildingQueueWrap(uid);
	buildingQueueWrap.Obj().GetUpgradeBuilds(vBuilds);

	do
	{
		if (vBuilds.empty()) break;
		std::string reason = "build_once_upgrade_op";

		if (user.Obj().harmmer > 0)
		{
			user.CostHarmmer(1, reason);
		}
		else if(user.Obj().cash >= cost_cash)
		{
			user.CostCash(cost_cash, reason);
		}
		else
		{
			break;
		}

		for (size_t i = 0; i < vBuilds.size(); ++i)
		{
			DBCBuildingDataWrap buildingWrap(uid, vBuilds[i]);
			buildingWrap.OnceFinishUpgrade();
		}

		//todo 接入使用黄金锤子任务接口
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_hammer;
		LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	} while(0);

	if (resp)
	{
		DBCBuildingQueueDataWrap buildingQueueWrap(uid);
		buildingQueueWrap.FullMessage(resp->mutable_build_queue());

		//建筑信息
		std::vector<unsigned> vUpBuilds;
		DataBuildingManager::Instance()->GetBuildIds(uid, 0, vUpBuilds);
		for (size_t i = 0; i < vUpBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildingWrap(uid, vUpBuilds[i]);
			buildingWrap.FullMessage(resp->add_builds());
		}

		resp->set_hammer_cnt(user.Obj().harmmer);
		resp->set_cash(user.Obj().cash);
		resp->set_total_exploit(user.Obj().preward);
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildAutoUpgradeReq* msg, ProtoBuilding::BuildAutoUpgradeResp* resp)
{
	DBCUserBaseWrap user(uid);
	if (user.Obj().level >= 35 && ! user.IsAutoBuildPower())
	{
		throw std::runtime_error("user_condition_dissatisfy");
	}


	DBCBuildingQueueDataWrap buildingQueueWrap(uid);

	if (! buildingQueueWrap.Obj().IsAutoUpgrade())
	{
		unsigned cnt = buildingQueueWrap.Obj().UnlockQueueCnt() * 5
										+ user.VIPPower().GetAutoBuildCnt() ;
		buildingQueueWrap.SetAutoUpgrade((uint8_t)msg->type(), cnt);
	}
	else
	{
		buildingQueueWrap.AbolishAutoUpgrade();
	}

	//todo 接入使用自动建造任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_autoupgrade;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	if (resp)
	{
		DBCBuildingQueueDataWrap buildingQueueWrap(uid);
		buildingQueueWrap.FullMessage(resp->mutable_build_queue());

		//用户信息
		user.Obj().FullBuildSyncMessage(resp->mutable_user());

		//建筑信息
		std::vector<unsigned> vUpBuilds;
		DataBuildingManager::Instance()->GetBuildIds(uid, (uint8_t)msg->type(), vUpBuilds);
		for (size_t i = 0; i < vUpBuilds.size(); i++)
		{
			DBCBuildingDataWrap buildingWrap(uid, vUpBuilds[i]);
			buildingWrap.FullMessage(resp->add_builds());
		}
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildExploitReq* msg, ProtoBuilding::BuildExploitResp* resp)
{
	DBCUserBaseWrap user(uid);

	unsigned build_exploit = user.Obj().preward;
	if (build_exploit <= 0)
	{
		throw std::runtime_error("not_can_get_build_exploit");
	}

	const OfflineResourceItem& attr = LogicResourceManager::Instance()->AddExploit(uid, build_exploit);
	user.ClearBuildExploit();
	//todo
	if (resp)
	{
		resp->set_user_exploit(attr.reward);
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildResourceSyncReq* msg, ProtoBuilding::BuildResourceSyncResq* resp)
{
	DBCUserBaseWrap userWrap(uid);
	userWrap.RestoreResource();

	if (resp)
	{
		userWrap.Obj().FullResourceMessage(resp);
	}

	return R_SUCCESS;
}

int LogicBuildManager::Process(unsigned uid, ProtoBuilding::BuildUnlockQueueReq* msg, ProtoBuilding::BuildUnlockQueueResp* resp)
{
	DBCBuildingQueueDataWrap buildingQueueWrap(uid);
	int nCnt = buildingQueueWrap.Obj().UnlockQueueCnt();
	int unlockLevel_array[4] = {1, 1, 9, 17};

	DBCUserBaseWrap user(uid);
	unsigned need_lock_cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		if (user.Obj().level >= unlockLevel_array[i])
		{
			++need_lock_cnt;
		}
		else
		{
			break;
		}
	}


	if (nCnt < (int)need_lock_cnt)
	{
		buildingQueueWrap.Unlock(need_lock_cnt - nCnt);
	}


	if (resp)
	{
		DBCBuildingQueueDataWrap buildingQueueWrap(uid);
		buildingQueueWrap.FullMessage(resp->mutable_build_queue());

		std::vector<unsigned> vBuilds;
		buildingQueueWrap.Obj().GetUpgradeBuilds(vBuilds);

		for (size_t i = 0; i < vBuilds.size(); ++i)
		{
			DBCBuildingDataWrap buildingWrap(uid, vBuilds[i]);
			buildingWrap.FullMessage(resp->add_builds());
		}
	}

	return R_SUCCESS;
}

unsigned LogicBuildManager::ProductValue(unsigned uid, int type, unsigned start, unsigned end)
{
	if (start >= end) return 0;

	unsigned baseVal = YieldsBase(uid, type);
	unsigned addition = YieldsAddition(uid, type, baseVal);
	int index = LogicTimeLimitPropMgr::Instance()->GetBuildsIndex(uid, type);
	if (index >= 0)
	{
		DBCTimeLimitPropWrap prop(index);

		unsigned nTotalVal = baseVal + addition;
		//有加成总共的
		unsigned nTotalAdd = nTotalVal + baseVal * prop.AttrValue() / 100;

		if (prop.LostTime() > start)
		{
			unsigned normalPeroid = prop.OpTime() > start ? prop.OpTime() - start : 0;
			normalPeroid += prop.LostTime() < end ? end - prop.LostTime() : 0;

			unsigned addPeroid = std::min(prop.LostTime(), end) - std::max(prop.OpTime(), start);
			return nTotalVal / 60 * normalPeroid + nTotalAdd / 10 * addPeroid;
		}
		else
		{
			unsigned interval_minit = (end - start) / 60;

			return nTotalVal / 60 * interval_minit;
		}
	}
	else
	{
		unsigned nTotalVal = baseVal + addition;
		unsigned interval_minit = (end - start) / 60;
		return nTotalVal / 60 * interval_minit;
	}
}

unsigned LogicBuildManager::Yields(unsigned uid, int type)
{
	unsigned baseValue = YieldsBase(uid, type);
	unsigned addition = YieldsAddition(uid, type, baseValue);
	//限时道具加成
	unsigned time_prop_factor = LogicTimeLimitPropMgr::Instance()->GetBuildAddFactor(uid, type);
	unsigned time_prop_add = baseValue * time_prop_factor / 100;


	return baseValue + addition + time_prop_add;
}

unsigned LogicBuildManager::YieldAchievement(unsigned uid, int type)
{
	unsigned baseValue = YieldsBase(uid, type);
	unsigned addition = YieldsAddition(uid, type, baseValue);

	return baseValue + addition;
}

unsigned LogicBuildManager::YieldsBase(unsigned uid, int type)
{
	std::vector<unsigned> vBuildsIndex;
	DataBuildingManager::Instance()->IndexsBuildsByType(uid, type, vBuildsIndex);

	BuildCfgWrap buildCfg;
	unsigned val = 0;
	for (size_t i = 0; i < vBuildsIndex.size(); ++i)
	{
		DBCBuildingDataWrap buildingWrap(vBuildsIndex[i]);
		//builds.level
		if (buildCfg.Item(buildingWrap.Obj().id).type() == 0)
		{
			val += buildCfg.LvLs(buildingWrap.Obj().id, buildingWrap.Obj().level).value();
		}
	}

	return val;
}

unsigned LogicBuildManager::YieldsAddition(unsigned uid, int type, unsigned baseValue)
{
	DBCUserBaseWrap user(uid);
	//限时道具加成
	//unsigned time_prop_factor = LogicTimeLimitPropMgr::Instance()->GetBuildAddFactor(uid, type);
	//unsigned time_prop_add = baseValue * time_prop_factor / 100;
	//VIP加成
	UVIPPower vipPower = user.VIPPower();
	unsigned add_vip = baseValue * vipPower.ResourceYieldAdd() / 100;
	if (type ==  DataBuildingManager::MINE_FIELD_TYPE)
	{
		add_vip += baseValue * vipPower.IronAdd() / 100;
	}

	//科技加成
	int nScienceFactor =  LogicScienceMgr::Instance()->GetYieldFactor(uid, type);
	unsigned add_science = (baseValue +  add_vip) * nScienceFactor / 100;
	//官职加成
	unsigned official_add = LogicOfficialMgr::Instance()->GetYieldsAdd(user, type);

	return add_vip + add_science + official_add;
}

unsigned LogicBuildManager::Capacity(unsigned uid, int type)
{
	enum {
		CAPACITY_INIT = 10000,
	};

	unsigned nCapacityVal = CAPACITY_INIT;
	try
	{
		std::vector<unsigned> vBuildsIndex;
		DataBuildingManager::Instance()->IndexsBuildsByType(uid, type, vBuildsIndex);

		BuildCfgWrap buildCfg;
		for (size_t i = 0; i < vBuildsIndex.size(); ++i)
		{
			DBCBuildingDataWrap buildingWrap(vBuildsIndex[i]);
			//builds.level
			if (buildingWrap.Obj().IsUnLocked() && buildCfg.Item(buildingWrap.Obj().id).type() == 1)
			{
				nCapacityVal += buildCfg.LvLs(buildingWrap.Obj().id, buildingWrap.Obj().level).value();
				break;
			}
		}
	}
	catch(const std::exception& e)
	{
		(void)e;
	}

	nCapacityVal += nCapacityVal * DBCUserBaseWrap(uid).VIPPower().StorageCapacityAdd() / 100;

	return nCapacityVal;
}

int LogicBuildManager::GetBuildingByType(unsigned uid, int type, vector<DBCBuildingData> &vctBuilds)
{
	//根据类型，获取所有的建筑id
	std::vector<unsigned> vBuildsIndex;
	DataBuildingManager::Instance()->IndexsBuildsByType(uid, type, vBuildsIndex);

	for(int i = 0; i < (int)vBuildsIndex.size(); ++i)
	{
		DBCBuildingDataWrap buildingWrap(vBuildsIndex[i]);
		vctBuilds.push_back(buildingWrap.Obj());
	}

	return R_SUCCESS;
}
