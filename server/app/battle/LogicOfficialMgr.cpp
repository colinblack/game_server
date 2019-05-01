/*
 * LogicOfficialMgr.cpp
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */


#include "LogicOfficialMgr.h"

void LogicOfficialMgr::CheckUserParams(const DBCUserBaseWrap& user) const
{
	if (user.Obj().level < OFFICIAL_OPEN_LEVEL)
	{
		throw std::runtime_error("user_level_not_enough");
	}
}

void LogicOfficialMgr::CheckDepartmentParams(unsigned department) const
{
	if (department < e_Commander || department >= e_department_cnt)
	{
		throw std::runtime_error("department_params_error");
	}
}

void LogicOfficialMgr::RefreshUserDepartinfo(unsigned uid, unsigned department, unsigned official)
{
	if (uid > 0)
	{
		//更新官职对手数据
		int index = ResourceManager::Instance()->GetIndex(uid);
		if (index >= 0)
		{
			ResourceManager::Instance()->m_data->item[index].aid = department;
			ResourceManager::Instance()->m_data->item[index].job = official;
		}
	}
}

unsigned LogicOfficialMgr::PkNPC(unsigned department, unsigned official)
{
	/*
	e_Commander = 1,  	//司令部
	e_Defense 	= 2,	//国防部
	e_President = 3, 	//总统府
	e_Marshal 	= 4,	//元帅府
	e_Staff 	= 5,  	//参谋部
	*/
	const unsigned npc[e_department_cnt - 1] = {
			9000114,
			9000115,
			9000117,
			9000116,
			9000113
	};

	if (IS_LEADER(official))
	{
		if (IS_VALID_DEPARTMENT(department))
		{
			return npc[department - 1];
		}
		else
		{
			error_log("department: %u", department);
			throw std::runtime_error("department_params_error");
		}
	}
	else
	{
		return 9000112;
	}
}

void LogicOfficialMgr::FullMessage(const DataBase &base, User::User* obj)
{
	MemoryOfficialKingdom& kingdomObj = DataPtr()->GetOfficialKingdom(base.kingdom);
	//官职数据
	unsigned uid = base.uid;
	OfficialDepartment* depart_ptr = kingdomObj.GetDepartmentByUid(uid);
	if (depart_ptr != NULL)
	{
		obj->mutable_base()->set_department(depart_ptr->Type());
		Official* official_ptr = depart_ptr->GetOfficialByUid(uid);
		int job = official_ptr != NULL ? official_ptr->Job() : 0;
		obj->mutable_base()->set_official(job);

		if (depart_ptr->IsLeader(uid))
		{
			obj->mutable_base()->set_prestige(depart_ptr->Prestige());
		}

		//
		LogicOfficialMgr::Instance()->RefreshUserDepartinfo(uid, depart_ptr->Type(), job);
	}
	else
	{
		obj->mutable_base()->set_department(0);
		obj->mutable_base()->set_official(0);
	}

	for (int i = 1; i <= SG17_KINGDOM; i++)
	{
		const OfficialToken& token = DataPtr()->GetOfficialKingdom(i).GetToken();
		if (token.IsValid())
		{
			FullMessage(i, token, obj->mutable_token()->Add());
		}
	}
}

void LogicOfficialMgr::FullMessage(const DepartmentRecord& record, ProtoOfficial::DepartmentRecord* obj)
{
	obj->set_params(record.params_);
	obj->set_operate(record.operate_);
	obj->set_target(record.target_);
	obj->set_operate_job(record.operate_job_);
	obj->set_target_job(record.target_job_);
	obj->set_ts(record.ts_);
	obj->set_op(record.OP());
}

void LogicOfficialMgr::FullMessage(OfficialDepartment& depart_obj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::DepartmentRecord >* obj)
{
	for (int i = depart_obj.GetRecordSize() - 1; i >= 0; i--)
	{
		const DepartmentRecord& reocrd = depart_obj.GetRecord(i);
		FullMessage(reocrd, obj->Add());
	}
}

void LogicOfficialMgr::FullMessage(const PersonnelRecord& record, ProtoOfficial::PersonnelRecord* obj)
{
	obj->set_operate(record.operate_);
	obj->set_target(record.target_);
	obj->set_department((::ProtoOfficial::eDepartment)record.department_);
	obj->set_official(record.official_);
	obj->set_ts(record.ts_);
}

void LogicOfficialMgr::FullMessage(MemoryOfficialKingdom& kingdomObj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::PersonnelRecord >* obj)
{
	for (int i = kingdomObj.GetPersonnelRecordSize() - 1; i >= 0; i--)
	{
		const PersonnelRecord& record = kingdomObj.GetPersonnelRecord(i);
		FullMessage(record, obj->Add());
	}
}
void LogicOfficialMgr::FullMessage(const PrivilegeRecord& record, ProtoOfficial::PrivilegeRecord* obj)
{
	obj->set_operate(record.operate_);
	obj->set_target(record.target_);
	obj->set_department((::ProtoOfficial::eDepartment)record.department_);
	obj->set_official(record.official_);
	obj->set_ts(record.ts_);
	obj->set_type(record.type_);
	obj->set_params(record.params_);
}

void LogicOfficialMgr::FullMessage(MemoryOfficialKingdom& kingdomObj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::PrivilegeRecord >* obj)
{
	for (int i = kingdomObj.GetPrivilegeRecordSize() - 1; i >= 0; i--)
	{
		const PrivilegeRecord& record = kingdomObj.GetPrivilegeRecord(i);
		FullMessage(record, obj->Add());
	}
}

void LogicOfficialMgr::FullMembers(OfficialDepartment& depart_obj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::DepartmentMember >* obj)
{
	Official&  leader = depart_obj.GetLeader();
	FullMessage(leader, obj->Add());
	//副部长
	for (int i = e_Deputy; i < e_Deputy + OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		Official& deputy = depart_obj.GetDeputy(i);
		if (! deputy.IsNPC())
		{
			FullMessage(deputy, obj->Add());
		}
	}

	//队长
	for (int i = e_Captain; i < e_Captain + OFFICIAL_CAPTAIN_MEMBERS; i++)
	{
		Official& captain = depart_obj.GetCaptain(i);
		FullMessage(captain, obj->Add());
	}

	//
	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		Official& teamer = depart_obj.GetTeamerByIndex(i);
		if (! teamer.IsNPC())
		{
			FullMessage(teamer, obj->Add());
		}
	}
}

void LogicOfficialMgr::FullMessage(int kingdom, const OfficialToken& token, ProtoOfficial::PublishToken* obj)
{
	obj->set_department((::ProtoOfficial::eDepartment)token.Department());
	obj->set_city_id(token.CityId());
	obj->set_ts(token.TS());
	obj->set_text(token.Text());
	obj->set_name(token.Name());
	obj->set_kingdom(kingdom);
}

unsigned LogicOfficialMgr::GetYieldsAdd(const OfficialConfig::OfficialJob& cfg, int type)
{
	switch (type)
	{
	case DataBuildingManager::FOLK_HOUSE_TYPE: return cfg.coin_yield_add();
	case DataBuildingManager::TIMBER_YARD_TYPE: return cfg.wood_yield_add();
	case DataBuildingManager::FARMLAND_TYPE:	return cfg.food_yield_add();
	case DataBuildingManager::MINE_FIELD_TYPE:  return cfg.iron_yield_add();
	default: return 0;
	}
}

unsigned LogicOfficialMgr::GetYieldsAdd(const DBCUserBaseWrap& user, int type)
{
	if (user.Obj().level < OFFICIAL_OPEN_LEVEL)
	{
		return 0;
	}

	int kingdom = user.Obj().kingdom;
	unsigned uid = user.Obj().uid;
	std::pair<unsigned, unsigned> officialInfo = DataPtr()->GetUserOfficial(kingdom, uid);

	try
	{
		const OfficialConfig::OfficialJob& jobCfg
						= OfficialCfgWrap().GetJobCfg(officialInfo.first, officialInfo.second);
		return GetYieldsAdd(jobCfg, type);
	}
	catch (const std::exception& e)
	{
		error_log("uid: %u, %s", uid, e.what());
	}

	return 0;
}

void LogicOfficialMgr::OnHour()
{
	const unsigned table[e_department_cnt -1] = {5,10,15,10,5};
	for (int kingdom = 1; kingdom <= 3; kingdom++)
	{
		MemoryOfficialKingdom& kingdom_obj =  DataPtr()->GetOfficialKingdom(kingdom);
		for (int i = e_Commander; i < e_department_cnt; i++)
		{
			OfficialDepartment& depart_obj = kingdom_obj.GetDepartment(i);

			depart_obj.AddPrestige(table[i - 1]);
		}
	}
}

std::string LogicOfficialMgr::GetPlayerName(unsigned uid)
{
	do
	{
		if (uid <= 0) break;
		int index = ResourceManager::Instance()->GetIndex(uid);
		if (index < 0) break;

		OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[index];

		return std::string(item.name);

	} while(0);

	return "";
}

void LogicOfficialMgr::FinishPkSuccess(unsigned uid, unsigned department, unsigned official)
{
	try
	{
		DBCUserBaseWrap user(uid);
		int kingdom = user.Obj().kingdom;

		MemoryOfficialKingdom& kingdom_data = DataPtr()->GetOfficialKingdom(kingdom);
		OfficialDepartment& depObj = kingdom_data.GetDepartment(department);

		unsigned originDepart = 0;
		unsigned originJob = 0;
		//部长之间不能进行挑战
		OfficialDepartment* OriginDpObj = kingdom_data.GetDepartmentByUid(uid);
		if (OriginDpObj)
		{
			originDepart = OriginDpObj->Type();
		}

		Official* self_official = kingdom_data.GetOfficialByUid(uid);
		if (self_official != NULL)
		{
			if(self_official->IsLeader())
			{
				error_log("leader_pk_other. uid: %u", uid);
				return ;
			}

			originJob = self_official->Job();

			self_official->Reset();
		}

		unsigned defend_uid = depObj.GetOfficial(official).Uid();

		depObj.Replace(official, uid);

		RefreshUserDepartinfo(defend_uid, 0, 0);

		//uid
		std::string attack_name = this->GetPlayerName(uid);
		std::string defend_name = this->GetPlayerName(defend_uid);
		if(IS_LEADER(official))
		{
			kingdom_data.AddPersonnelRecord(
					PersonnelRecord(attack_name, defend_name, department, official));
		}
		else
		{
			depObj.AddRersonnelRecord(
					PersonnelRecord(attack_name, defend_name, department, official));
		}

		OnChangeOfficial(uid, originDepart, originJob, department, official);
	}
	catch(const std::exception& e)
	{
		error_log("uid: %u, department: %u, official: %u; %s", uid, department, official, e.what());
	}
}

void LogicOfficialMgr::OnChangeOfficial(unsigned uid, unsigned originDepart, int originJob, unsigned targetDepart, int targetJob)
{
	ProtoOfficial::PushJobChangeMsg* msg = new ProtoOfficial::PushJobChangeMsg;
	msg->set_origin_depart((::ProtoOfficial::eDepartment)originDepart);
	msg->set_origin_job(originJob);
	msg->set_target_depart((::ProtoOfficial::eDepartment)targetDepart);
	msg->set_target_job(targetJob);

	LogicManager::Instance()->sendMsg(uid, msg);

	RefreshUserDepartinfo(uid, targetDepart, targetJob);

	//更新产量
	LogicBuildManager::Instance()->SyncYield(uid);

	//todo 接入部门成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_joindepartment;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);

	//todo 接入官职成就
	achievementparam.type = achievement_type_official;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(uid, achievementparam);
}

void LogicOfficialMgr::FullMessage(Official& official, ProtoOfficial::DepartmentMember* obj)
{
	unsigned uid = official.Uid();
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
			obj->set_name(std::string(item.name));
			obj->set_official(official.Job());
			obj->set_head(std::string(item.fig));
			return ;

		} while(0);
	} catch(const std::exception& e)
	{
		error_log("uid: %u, %s", uid, e.what());
	}

	obj->set_uid(0);
	obj->set_lvl(0);
	obj->set_name("");
	obj->set_official(official.Job());
	obj->set_head("");
}

void LogicOfficialMgr::FullMessage(OfficialDepartment& department, ProtoOfficial::DepartmentLeader* obj)
{
	Official& leader = department.GetLeader();
	obj->set_type((::ProtoOfficial::eDepartment)department.Type());
	obj->set_prestige(department.Prestige());

	FullMessage(leader, obj->mutable_leader());
}


unsigned LogicOfficialMgr::GetPkRival(const DBCUserBaseWrap& user, unsigned department, unsigned official)
{
	unsigned kingdom  = user.Obj().kingdom;
	unsigned uid = user.Obj().uid;

	OfficialDepartment& depObj = DataPtr()->GetDepartment(kingdom, department);
	//Official* official_ptr = NULL;
	if (IS_LEADER(official))
	{
		//official_ptr = &depObj.GetLeader();
	}
	else if (IS_CAPTAIN(official))
	{
		if (! depObj.IsTeamer(uid) && !depObj.IsCaptain(uid))
		{
			throw std::runtime_error("not_internal_member");
		}
	}
	else
	{
		throw std::runtime_error("the_member_cannot_challenge");
	}

	Official& offiObj = depObj.GetOfficial(official);
	if (offiObj.Uid() == uid)
	{
		throw std::runtime_error("cannot_challenge_self");
	}

	if (DataPtr()->IsLeader(user.Obj().kingdom, uid))
	{
		throw std::runtime_error("leader_cannot_challenge");
	}

	return offiObj.Uid();
}

//挑战
int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::ChallengeReq* req, ProtoOfficial::ChallengeResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned department = req->department();
	unsigned official = req->official();

	unsigned rival_uid = GetPkRival(user, department, official);
	//
	if (rival_uid == 0)
	{
		resp->add_hero_ids(PkNPC(department, official));
	}
	else
	{
		std::set<HeroPropertyItemIndex> heros;
		HeroPropertyManager::Instance()->GetHeros(rival_uid, heros);
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

	resp->set_department(req->department());
	resp->set_official(official);

	return R_SUCCESS;
}

//开始挑战
int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::StartChallengeReq* req)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned department = req->department();
	unsigned official = req->official();

	unsigned rival_uid = GetPkRival(user, department, official);

	std::vector<HeroPropertyItemIndex> heros;
	for (int i = 0;i < req->hero_ids_size(); ++i)
	{
		heros.push_back(HeroPropertyItemIndex(uid, req->hero_ids(i)));
	}

	vector<HeroPropertyItemIndex> enemy;

	if (rival_uid > 0)
	{
		HeroPropertyManager::Instance()->GetHeros(rival_uid, enemy);
	}

	if(enemy.empty())
	{
		enemy.push_back(HeroPropertyItemIndex(e_gate_npc, PkNPC(department, official)));
		//enemy.insert(HeroPropertyItemIndex(e_gate_npc, LADDER_NPC_ID));
	}

	//todo 战斗
	//需要传递参数 department, official
	unsigned params = department*1000 + e_gt_official_min + official;

	int ret = WMI->CreateLadderFight(uid, params, heros, enemy);

	if (ret)
	{
		return ret;
	}

	//todo 军职挑战外部接口
	ChallengeExternalInterface(uid);

	return 0;
}

int LogicOfficialMgr::ChallengeExternalInterface(unsigned uid)
{
	//todo 接入每日军职挑战任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_official;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::AppointDeputyReq* req, ProtoOfficial::AppointDeputyResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned appoint_uid = req->uid();

	if (appoint_uid == uid)
	{
		throw std::runtime_error("not_appoint_self");
	}

	unsigned department = req->department();
	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);

	if (! depart_obj.IsLeader(uid))
	{
		throw std::runtime_error("not_jurisdiction");
	}

	Official* appoint_ptr = depart_obj.GetOfficialByUid(appoint_uid);
	if (NULL == appoint_ptr)
	{
		throw std::runtime_error("not_appoint_external_member");
	}

	unsigned origin_job = appoint_ptr->Job();
	unsigned target_job = 0;

	if (appoint_ptr->IsDeputy())
	{
		target_job = depart_obj.FireDeputy(appoint_uid).Job();
	}
	else
	{
		target_job = depart_obj.AppointDeputy(appoint_uid).Job();

		std::string op_name = GetPlayerName(uid);
		std::string adopt_name = GetPlayerName(appoint_uid);
		depart_obj.AddAppointDeputyRecord(appoint_uid, target_job, op_name, adopt_name);
	}

	//
	resp->set_department(req->department());
	resp->set_uid(appoint_uid);
	resp->set_origin(origin_job);
	resp->set_target(target_job);

	FullMembers(depart_obj, resp->mutable_members());
	FullMessage(depart_obj, resp->mutable_records());

	OnChangeOfficial(appoint_uid, department, origin_job, department, target_job);

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::ApplyJoinReq* req, ProtoOfficial::ApplyJoinResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();

	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);
	Official& leader = depart_obj.GetLeader();
	if (depart_obj.GetRealMembers() >= OFFICIAL_DEPARTMENT_MEMBERS)
	{
		throw std::runtime_error("department_members_is_full");
	}

	resp->set_department(req->department());

	//部门领导为npc直接加入部门
	if (leader.IsNPC())
	{
		//
		Official& new_teamer = depart_obj.GetEmptyTeamer();
		new_teamer.Replace(uid);

		depart_obj.AddJoinRecord(uid, std::string(user.Obj().name));

		FullMembers(depart_obj, resp->mutable_members());
		FullMessage(depart_obj, resp->mutable_records());

		OnChangeOfficial(uid, 0, 0, department, 0);
	}
	else
	{
		//查找是否申请
		if (! depart_obj.IsAlreadyApply(uid))
		{
			depart_obj.AddApplyJoinRecord(uid, std::string(user.Obj().name));
		}
	}

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::ApplyExitReq* req, ProtoOfficial::ApplyExitResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();
	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);

	Official* self_ptr = depart_obj.GetOfficialByUid(uid);
	if (NULL == self_ptr)
	{
		throw std::runtime_error("not_appoint_external_member");
	}

	self_ptr->Reset();

	resp->set_department((::ProtoOfficial::eDepartment)0);
	resp->set_official(0);
	resp->set_prestige(0);
	FullMembers(depart_obj, resp->mutable_members());

	RefreshUserDepartinfo(uid, 0, 0);

	depart_obj.AddExitRecord(uid, std::string(user.Obj().name));

	//更新产量
	LogicBuildManager::Instance()->SyncYield(uid);

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::AgreeJoinReq* req, ProtoOfficial::AgreeJoinResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned handle_uid = req->uid();
	unsigned department = req->department();

	MemoryOfficialKingdom& kindomObj = DataPtr()->GetOfficialKingdom(kingdom);
	OfficialDepartment& depart_obj = kindomObj.GetDepartment(department);
	Official* self_ptr = depart_obj.GetOfficialByUid(uid);
	if (NULL == self_ptr || (! (self_ptr->IsLeader() || self_ptr->IsDeputy())))
	{
		throw std::runtime_error("not_handle_power");
	}

	if (depart_obj.GetRealMembers() >= OFFICIAL_DEPARTMENT_MEMBERS)
	{
		throw std::runtime_error("department_members_is_full");
	}

	depart_obj.RemoveApplyRecord(handle_uid);


	Official* handlr_ptr = kindomObj.GetOfficialByUid(handle_uid);
	if (handlr_ptr != NULL)
	{
		throw std::runtime_error("already_in_the_department");
	}

	Official& new_teamer = depart_obj.GetEmptyTeamer();
	new_teamer.Replace(handle_uid);

	depart_obj.AddJoinRecord(handle_uid, GetPlayerName(handle_uid));

	///////////////////////////////////////////////////////
	resp->set_department(req->department());
	//
	FullMembers(depart_obj, resp->mutable_members());
	FullMessage(depart_obj, resp->mutable_records());

	OnChangeOfficial(handle_uid, 0, 0, department, new_teamer.Job());

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::SetNoticeReq* req)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();

	MemoryOfficialKingdom& kingdom_obj =  DataPtr()->GetOfficialKingdom(kingdom);
	if (department == 0)
	{
		if (kingdom_obj.GetDepartment(e_President).GetLeader().Uid() != uid)
		{
			throw std::runtime_error("not_predident");
		}

		//
		kingdom_obj.SetNotice(req->text());
	}
	else
	{
		OfficialDepartment& depart_obj = kingdom_obj.GetDepartment(department);
		if (depart_obj.GetLeader().Uid() != uid)
		{
			throw std::runtime_error("not_leader");
		}
		depart_obj.SetNotice(req->text());
	}

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::OfficialInfoReq* req, ProtoOfficial::OfficialInfoResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();

	MemoryOfficialKingdom& kingdom_obj =  DataPtr()->GetOfficialKingdom(kingdom);
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		OfficialDepartment& depart_obj = kingdom_obj.GetDepartment(i);

		FullMessage(depart_obj, resp->add_leaders());
	}

	resp->set_country_notice(kingdom_obj.GetNotice());

	if (department > 0)
	{
		OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);
		FullMembers(depart_obj, resp->mutable_members());

		resp->set_depart_notice(depart_obj.GetNotice());
	}
	else
	{
		int nCnt = 0;
		for (int  i = 0; nCnt < 50; i++)
		{
			const  OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[i];
			if (item.uid == 0) break;
			if (item.aid != 0) continue;
			if (item.kingdom != kingdom) continue;
			if (item.property[DemoOfflineProperty_u_level] < OFFICIAL_OPEN_LEVEL) continue;


			ProtoOfficial::DepartmentMember* obj = resp->add_members();
			//
			obj->set_uid(item.uid);
			obj->set_lvl(item.property[DemoOfflineProperty_u_level]);
			obj->set_name(item.name);
			obj->set_official(0);
			obj->set_head(item.fig);

			nCnt++;
		}

		resp->set_depart_notice("");
	}

	resp->set_department(req->department());

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::GetSalaryReq* req, ProtoOfficial::GetSalaryResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	if (Time::IsToday(user.Obj().job_reward_ts))
	{
		throw std::runtime_error("already_get_salary");
	}

	unsigned kingdom  = user.Obj().kingdom;
	std::pair<unsigned, unsigned> officialInfo = DataPtr()->GetUserOfficial(kingdom, uid);
	unsigned nSalary = OfficialCfgWrap().GetJobCfg(officialInfo.first, officialInfo.second).pay();

	user.SetJobSalary();

	std::map<unsigned, unsigned> srcMap;
	srcMap[COINTS_TYPE] = nSalary;
	user.AddResource(srcMap, "official_get_salary_op");

	resp->set_salary(nSalary);
	resp->set_coins(user.Obj().coin);
	resp->set_job_reward_ts(user.Obj().job_reward_ts);

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::RefuseJoinReq* req, ProtoOfficial::RefuseJoinResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);
	//
	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();

	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);
	depart_obj.RemoveApplyRecord(req->uid());

	resp->set_department(req->department());
	FullMessage(depart_obj, resp->mutable_records());

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::GetDepartmentRecordReq* req, ProtoOfficial::GetDepartmentRecordResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();

	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);
	FullMessage(depart_obj, resp->mutable_records());

	return 0;
}

bool LogicOfficialMgr::IsMeetPushToken(unsigned uid, unsigned cityId)
{
	std::set<HeroPropertyItemIndex> heros;
	HeroPropertyManager::Instance()->GetHeros(uid, heros);
	for (std::set<HeroPropertyItemIndex>::const_iterator it = heros.begin();
			it != heros.end();
			++it)
	{
		const HeroPropertyItem& item = GET_HMI(*it);
		if (item.city == cityId)
		{
			return true;
		}
	}

	return false;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::PublishTokenReq* req)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;
	unsigned department = req->department();
	unsigned cityId = req->city_id();

	MemoryOfficialKingdom& kingdomObj = DataPtr()->GetOfficialKingdom(kingdom);
	OfficialDepartment& departObj = kingdomObj.GetDepartment(department);

	if (! departObj.IsLeader(uid))
	{
		throw std::runtime_error("not_publish_token_power");
	}

	if (departObj.Prestige() < 30)
	{
		throw std::runtime_error("prestige_not_enough");
	}
	//todo 官威  //城市 GET_BMI_CITY(cid).kingdom
	if (! IsMeetPushToken(uid, cityId))
	{
		throw std::runtime_error("not_alliance_in_the_city");
	}

	const OfficialToken& token = kingdomObj.SetToken(
			department, cityId, std::string(user.Obj().name),  req->text());

	departObj.CostPrestige(30);

	//todo resp
	ProtoOfficial::PushPublishToken* msg = new ProtoOfficial::PushPublishToken;
	FullMessage(kingdom, token, msg->mutable_token());

	PrivilegeRecord record(e_Issue_Token_op
			, std::string(user.Obj().name), department, e_Minister);
	record.SetParams(cityId);
	kingdomObj.AddPrivilegeRecord(record);

	LogicManager::Instance()->broadcastMsg(msg);

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::GetPersonnelRecordReq* req, ProtoOfficial::GetPersonnelRecordResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;

	MemoryOfficialKingdom& kingdomObj = DataPtr()->GetOfficialKingdom(kingdom);

	FullMessage(kingdomObj, resp->mutable_records());

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::GetPrivilegeRecordReq* req, ProtoOfficial::GetPrivilegeRecordResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned kingdom  = user.Obj().kingdom;

	MemoryOfficialKingdom& kingdomObj = DataPtr()->GetOfficialKingdom(kingdom);

	FullMessage(kingdomObj, resp->mutable_records());

	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::KickOutMemberReq* req, ProtoOfficial::KickOutMemberResp* resp)
{
	DBCUserBaseWrap user(uid);
	CheckUserParams(user);

	unsigned department = req->department();
	unsigned kick_uid = req->uid();

	unsigned kingdom = user.Obj().kingdom;
	OfficialDepartment& depart_obj = DataPtr()->GetDepartment(kingdom, department);

	Official* user_official = depart_obj.GetOfficialByUid(uid);
	if (NULL == user_official
			|| ((! user_official->IsLeader()) && (!user_official->IsDeputy())))
	{
		throw std::runtime_error("not_permission");
	}

	/////////////////////////////////////////////////////////////
	if (depart_obj.RemoveTeamer(kick_uid))
	{
		//
		depart_obj.AddKickOutMemberRecord(uid, user_official->Job(),
				std::string(user.Obj().name), GetPlayerName(kick_uid));
		OnChangeOfficial(kick_uid, department, 0, 0, 0);
		//
		Json::Value notifyval;
		notifyval["department"] = department;
		notifyval["name"] = user.Obj().name;
		Json::FastWriter writer;
		string content  = writer.write(notifyval);
		NotifyItem notifyitem(kick_uid, e_Notify_DepartKick);
		snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

		LogicNotifyManager::Instance()->AddNotify(notifyitem);
	}

	resp->set_department(req->department());
	//
	FullMembers(depart_obj, resp->mutable_members());
	FullMessage(depart_obj, resp->mutable_records());


	return 0;
}

int LogicOfficialMgr::Process(unsigned uid, ProtoOfficial::RespondTokenReq* req, ProtoOfficial::RespondTokenResp* resp)
{
	DBCUserBaseWrap user(uid);

	unsigned kingdom  = user.Obj().kingdom;
	MemoryOfficialKingdom& kingdomObj = DataPtr()->GetOfficialKingdom(kingdom);
	const OfficialToken& token = kingdomObj.GetToken();
	if (! token.IsValid())
	{
		throw std::runtime_error("token_not_valid");
	}

	if (user.Obj().token_op_ts >= token.TS())
	{
		throw std::runtime_error("already_respond_the_token");
	}

	for (int i = 0; i < req->hero_ids_size(); ++i)
	{
		int heroid = req->hero_ids(i);

		HeroPropertyItemIndex heroIdx =  HeroPropertyItemIndex(uid, heroid);
		const HeroPropertyItem& item = GET_HMI(heroIdx);
		if (item.city == token.CityId())
		{
			continue;
		}

		int flyRet = WMI->Fly(heroIdx, token.CityId());
		if (flyRet == 0)
		{
			resp->add_hero_ids(heroid);
		}
	}
	//

	if (resp->hero_ids_size() > 0)
	{
		user.SetTokenOpTs(token.TS());
	}

	resp->set_token_ts(user.Obj().token_op_ts);

	return 0;
}
