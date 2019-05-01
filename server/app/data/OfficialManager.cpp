/*
 * OfficialManager.cpp
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */


#include "OfficialManager.h"

DepartmentRecord::DepartmentRecord(int op)
	: params_(0)
	, operate_job_(0)
	, target_job_(0)
	, ts_(Time::GetGlobalTime())
	, op_(op)
{
	memset(operate_, 0, sizeof(operate_));
	memset(target_, 0, sizeof(target_));
}

DepartmentRecord::DepartmentRecord()
	: params_(0)
	, operate_job_(0)
	, target_job_(0)
	, ts_(0)
	, op_(0)
{
	memset(operate_, 0, sizeof(operate_));
	memset(target_, 0, sizeof(target_));
}

DepartmentRecord::DepartmentRecord(const PersonnelRecord& record)
	: params_(0)
	, operate_job_(0)
	, target_job_(record.official_)
	, ts_(Time::GetGlobalTime())
	, op_(e_Usurp_op)
{
	memcpy(operate_, record.operate_, BASE_NAME_LEN);
	memcpy(target_, record.target_, BASE_NAME_LEN);
}

PersonnelRecord::PersonnelRecord()
	: department_(0)
	, official_(0)
	, ts_(0)
{
	memset(operate_, 0, sizeof(operate_));
	memset(target_, 0, sizeof(target_));
}

PersonnelRecord::PersonnelRecord(const std::string& szOperate, const std::string& szTarget,
			uint8_t depart, uint8_t job)
	: department_(depart)
	, official_(job)
	, ts_(Time::GetGlobalTime())
{
	if (szOperate.size() > BASE_NAME_LEN - 1 || szTarget.size() > BASE_NAME_LEN - 1)
	{
		throw std::runtime_error("PersonnelRecord_name_too_long");
	}

	memset(operate_, 0, sizeof(operate_));
	memset(target_, 0, sizeof(target_));
	memcpy(operate_, szOperate.c_str(), szOperate.size());
	memcpy(target_, szTarget.c_str(), szTarget.size());
}

PrivilegeRecord::PrivilegeRecord()
	: department_(0)
	, official_(0)
	, ts_(Time::GetGlobalTime())
	, type_(0)
	, params_(0)
{
	memset(operate_, 0, sizeof(operate_));
	memset(target_, 0, sizeof(target_));
}

PrivilegeRecord::PrivilegeRecord(
		unsigned op
		, const std::string& operate
		, uint8_t depart
		, uint8_t official)
	: department_(depart)
	, official_(official)
	, ts_(Time::GetGlobalTime())
	, type_(op)
	, params_(0)
{
	if (operate.size() >= BASE_NAME_LEN)
	{
		throw std::runtime_error("PrivilegeRecord_operate_too_long");
	}

	memset(operate_, 0, sizeof(operate_));
	memcpy(operate_, operate.c_str(), operate.size());
	memset(target_, 0, sizeof(target_));
}

void PrivilegeRecord::SetTarget(const std::string& target)
{
	if (target.size() >= BASE_NAME_LEN)
	{
		throw std::runtime_error("PrivilegeRecord_target_too_long");
	}

	memset(target_, 0, sizeof(target_));
	memcpy(target_, target.c_str(), target.size());
}

void PrivilegeRecord::SetParams(unsigned params)
{
	params_ = params;
}

///////////////////////////////////////////////////////////
Official::Official()
	: uid_(0)
	, job_(0)
{
}

bool Official::IsLeader() const
{
	return IS_LEADER(job_);
}

bool Official::IsDeputy() const
{
	return IS_DEPUTY(job_);
}

bool Official::IsCaptain() const
{
	return IS_CAPTAIN(job_);
}

bool Official::IsTeamer() const
{
	return job_ == e_Teamer;
}

void Official::Replace(unsigned uid)
{
	uid_ = uid;
}

void Official::Reset()
{
	uid_ = 0;
}


eOfficialType Official::Type() const
{
	if (job_ >= e_Captain) return e_Captain;
	else if (job_ >= e_Deputy) return e_Deputy;
	else if (job_ >= e_Minister) return e_Minister;
	else return e_Teamer;
}

////////////////////////////////////////////////////////////
OfficialDepartment::OfficialDepartment()
	: type_((eDepartment)0)
	, prestige_(0)
	, record_ptr_(0)
{
	memset(notice_, 0, sizeof(notice_));
	//InitJob();
}

OfficialDepartment::OfficialDepartment(eDepartment type)
	: type_(type)
	, prestige_(0)
	, record_ptr_(0)
{
	memset(notice_, 0, sizeof(notice_));
	//InitJob();
}

void OfficialDepartment::InitJob(eDepartment type)
{
	type_ = type;
	leader_.SetOfficialJob(e_Minister);

	for (int i = 0; i < OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		deputy_[i].SetOfficialJob(e_Deputy + i);
	}

	for (int i = 0; i < OFFICIAL_CAPTAIN_MEMBERS; i++)
	{
		captain_[i].SetOfficialJob(e_Captain + i);
	}

	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		member_[i].SetOfficialJob(e_Teamer);
	}
}


bool OfficialDepartment::IsCaptain(unsigned uid) const
{
	for (int i= 0; i < OFFICIAL_CAPTAIN_MEMBERS; i++)
	{
		if (captain_[i].Uid() == uid)
		{
			return true;
		}
	}

	return false;
}

bool OfficialDepartment::IsTeamer(unsigned uid) const
{
	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		if (member_[i].Uid() == uid)
		{
			return member_[i].IsTeamer();
		}
	}

	return false;
}

bool OfficialDepartment::IsLeader(unsigned uid) const
{
	return leader_.Uid() == uid;
}

Official& OfficialDepartment::GetLeader()
{
	return leader_;
}

Official& OfficialDepartment::GetCaptain(unsigned nOfficial)  //队长
{
	if (nOfficial < e_Captain)
	{
		throw std::runtime_error("not_valid_captain_params");
	}

	int index = nOfficial % e_Captain;
	if (index >= OFFICIAL_CAPTAIN_MEMBERS)
	{
		throw std::runtime_error("not_valid_captain_params");
	}

	return captain_[index];
}

Official& OfficialDepartment::GetDeputy(unsigned nOfficial)
{
	if (! IS_DEPUTY(nOfficial))
	{
		throw std::runtime_error("not_valid_deputy_params");
	}

	int index = nOfficial % e_Deputy;
	return deputy_[index];
}

bool OfficialDepartment::IsDeputy(unsigned uid) const
{
	for (int i = 0; i < OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		if (deputy_[i].Uid() == uid)
		{
			return true;
		}
	}

	return false;
}

Official& OfficialDepartment::GetTeamerByIndex(int index)
{
	if (index < 0 || index >= OFFICIAL_DEPARTMENT_MEMBERS)
	{
		throw std::runtime_error("teamer_index_params_error");
	}

	return member_[index];
}



Official& OfficialDepartment::GetOfficial(unsigned nOfficial)
{
	if (IS_LEADER(nOfficial))
	{
		return GetLeader();
	}
	else if (IS_CAPTAIN(nOfficial))
	{
		return GetCaptain(nOfficial);
	}
	else if (IS_DEPUTY(nOfficial))
	{
		return GetDeputy(nOfficial);
	}
	else
	{
		for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
		{
			if (member_[i].Job() == nOfficial)
			{
				return member_[i];
			}
		}
	}

	error_log("nOfficial: %u", nOfficial);
	throw std::runtime_error("unknown_official_params");
}

Official* OfficialDepartment::GetOfficialByUid(unsigned uid)
{
	if (leader_.Uid() == uid)
	{
		return &leader_;
	}

	for (int i = 0; i < OFFICIAL_CAPTAIN_MEMBERS; i++)
	{
		if (captain_[i].Uid() == uid)
		{
			return &captain_[i];
		}
	}

	for (int i = 0; i < OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		if (deputy_[i].Uid() == uid)
		{
			return &deputy_[i];
		}
	}

	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		if (member_[i].Uid() == uid)
		{
			return &member_[i];
		}
	}

	return NULL;
}


Official& OfficialDepartment::FireDeputy(unsigned uid)
{
	Official* ptr =  GetOfficialByUid(uid);
	if (ptr == NULL)
	{
		throw std::runtime_error("not_internal_member");
	}

	if (! ptr->IsDeputy())
	{
		throw std::runtime_error("not_deputy");
	}

	ptr->Reset();
	Official& teamer = GetEmptyTeamer();
	teamer.Replace(uid);

	return teamer;
}

Official& OfficialDepartment::GetEmptyTeamer()
{
	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		if (member_[i].IsNPC())
		{
			return member_[i];
		}
	}

	throw std::runtime_error("teamer_is_full");
}

Official& OfficialDepartment::GetEmptyDeputy()
{
	for (int i = 0; i < OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		if (deputy_[i].IsNPC())
		{
			return deputy_[i];
		}
	}

	throw std::runtime_error("deputy_is_full");
}

Official& OfficialDepartment::AppointDeputy(unsigned uid)
{
	Official* ptr =  GetOfficialByUid(uid);
	if (ptr == NULL)
	{
		throw std::runtime_error("not_internal_member");
	}

	//只能任命队长或普通成员
	if (ptr->IsTeamer() || ptr->IsCaptain())
	{
		ptr->Reset();
		Official& deputy = GetEmptyDeputy();
		deputy.Replace(uid);

		return deputy;
	}
	else if (ptr->IsDeputy())
	{
		return *ptr;
	}
	else
	{
		throw std::runtime_error("only_appoint_teamer_of_captain");
	}
}

unsigned OfficialDepartment::GetRealMembers() const
{
	unsigned nTotal = 0;
	for (int i = 0; i < OFFICIAL_CAPTAIN_MEMBERS; i++)
	{
		if (! captain_[i].IsNPC())
		{
			++ nTotal;
		}
	}

	for (int i = 0; i < OFFICIAL_DEPUTY_MEMBERS; i++)
	{
		if (! deputy_[i].IsNPC())
		{
			++ nTotal;
		}
	}

	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		if (! member_[i].IsNPC())
		{
			++ nTotal;
		}
	}

	return nTotal;
}

void OfficialDepartment::Replace(unsigned official, unsigned uid)
{
	if (IS_LEADER(official))
	{
		leader_.Replace(uid);
		prestige_ = 0;
	}
	else if (IS_CAPTAIN(official))
	{
		GetCaptain(official).Replace(uid);
	}
	else
	{
		error_log("the_official_cannot_replace. official: %u, uid:%u", official, uid);
		throw std::runtime_error("the_official_cannot_replace");
	}
}

bool OfficialDepartment::RemoveTeamer(unsigned uid)
{
	for (int i = 0; i < OFFICIAL_DEPARTMENT_MEMBERS; i++)
	{
		if (member_[i].Uid() ==  uid)
		{
			member_[i].Reset();
			return true;
		}
	}

	return false;
}


void OfficialDepartment::SetNotice(const std::string& text)
{
	if (text.size() >= OFFICIAL_NOTICE_TEXT_LIMIT)
	{
		throw std::runtime_error("notice_too_long");
	}

	memset(notice_, 0, sizeof(notice_));
	memcpy(notice_, text.c_str(), text.size());
}


void OfficialDepartment::AddPrestige(unsigned nVal)
{
	enum {
		PRESTIGE_LIMIT = 100,
	};

	if (prestige_ < PRESTIGE_LIMIT)
	{
		prestige_ += nVal;

		prestige_ = prestige_ > PRESTIGE_LIMIT ? PRESTIGE_LIMIT: prestige_;
	}
}

//部门加入申请记录
void OfficialDepartment::AddApplyJoinRecord(unsigned uid, const std::string& name)
{
	DepartmentRecord record(e_ApplyJoin_op);
	record.params_ = uid;
	memset(record.operate_, 0, sizeof(record.operate_));
	strncpy(record.operate_, name.c_str(), BASE_NAME_LEN-1);

	AddRecord(record);
}

//加入部门
void OfficialDepartment::AddJoinRecord(unsigned uid, const std::string& name)
{
	DepartmentRecord record(e_Join_op);
	record.params_ = uid;
	memset(record.operate_, 0, sizeof(record.operate_));
	strncpy(record.operate_, name.c_str(), BASE_NAME_LEN-1);

	AddRecord(record);
}

//任命负部长
void OfficialDepartment::AddAppointDeputyRecord(unsigned uid, unsigned job, const std::string& op, const std::string& adopt)
{
	DepartmentRecord record(e_Appoint_op);
	record.params_ = uid;
	memset(record.operate_, 0, sizeof(record.operate_));
	strncpy(record.operate_, op.c_str(), BASE_NAME_LEN-1);
	memset(record.target_, 0, sizeof(record.target_));
	strncpy(record.target_, adopt.c_str(), BASE_NAME_LEN-1);
	record.operate_job_ = e_Minister;
	record.target_job_ = job;

	AddRecord(record);
}

void OfficialDepartment::AddExitRecord(unsigned uid, const std::string& op)
{
	DepartmentRecord record(e_Exit_op);
	record.params_ = uid;
	memset(record.operate_, 0, sizeof(record.operate_));
	strncpy(record.operate_, op.c_str(), BASE_NAME_LEN-1);

	AddRecord(record);
}

void OfficialDepartment::AddRersonnelRecord(const PersonnelRecord& p_record)
{
	DepartmentRecord record(p_record);
	AddRecord(record);
}

void OfficialDepartment::AddKickOutMemberRecord(unsigned uid, unsigned job, const std::string& op, const std::string& adopt)
{
	DepartmentRecord record(e_Kick_op);
	record.params_ = uid;
	memset(record.operate_, 0, sizeof(record.operate_));
	strncpy(record.operate_, op.c_str(), BASE_NAME_LEN-1);
	memset(record.target_, 0, sizeof(record.target_));
	strncpy(record.target_, adopt.c_str(), BASE_NAME_LEN-1);
	record.operate_job_ = job;

	AddRecord(record);
}

void OfficialDepartment::AddRecord(const DepartmentRecord& record)
{
	if (record_ptr_  >= OFFICIAL_RECORD_CNT)
	{
		RomoveRecord(0, 10);
	}

	record_[record_ptr_++] = record;
}

void OfficialDepartment::RomoveRecord(unsigned index, unsigned nCnt)
{
	if (record_ptr_ <= (int)index)
	{
		return ;
	}

	int mv_cnt = record_ptr_ - index - nCnt;
	if (mv_cnt <= 0)
	{
		record_ptr_ = index;
		return ;
	}

	memmove(record_ + index, record_ + index + nCnt, mv_cnt * sizeof(DepartmentRecord));
	record_ptr_ -= nCnt;
}

bool OfficialDepartment::IsAlreadyApply(unsigned uid)
{
	for (int i = 0; i < record_ptr_ && i <OFFICIAL_RECORD_CNT ; i++)
	{
		if (record_[i].OP() == e_ApplyJoin_op
				&& record_[i].params_ == uid)
		{
			return true;
		}
	}

	return false;
}

void OfficialDepartment::RemoveApplyRecord(unsigned uid)
{
	int idx = -1;
	for (int i = 0; i < record_ptr_ && i <OFFICIAL_RECORD_CNT ; i++)
	{
		if (record_[i].OP() == e_ApplyJoin_op
				&& record_[i].params_ == uid)
		{
			idx = i;
			break;
		}
	}

	if (idx >= 0)
	{
		RomoveRecord(idx);
	}
}

int	  OfficialDepartment::GetRecordSize() const
{
	return record_ptr_;
}

const DepartmentRecord& OfficialDepartment::GetRecord(unsigned index) const
{
	if (index >= record_ptr_)
	{
		throw std::runtime_error("department_record_index_out");
	}

	return record_[index];
}

void	OfficialDepartment::CostPrestige(unsigned nCnt)
{
	if (prestige_ < nCnt)
	{
		throw std::runtime_error("not_enough_prestige");
	}

	prestige_ -= nCnt;
}
//////////////////////////////////////////////////////////////
OfficialToken::OfficialToken()
	: department_(eDepartment(0))
	, ts_(0)
	, city_id_(0)
{
	memset(text_, 0, sizeof(text_));
}

void OfficialToken::Refresh(unsigned department, unsigned city_id, const std::string& name, const std::string& text)
{
	if (text.size() >= OFFICIAL_TOKEN_TEXT_LIMIT)
	{
		throw std::runtime_error("text_too_long");
	}

	unsigned now = Time::GetGlobalTime();
	if (ts_ > now)
	{
		throw std::runtime_error("is_exist_token");
	}

	ts_ = now + OFFICIAL_TOKEN_VALID_TIME;
	city_id_ = city_id;
	department_ = (eDepartment)department;
	memset(text_, 0, sizeof(text_));
	memcpy(text_, text.c_str(), text.size());

	memset(operate_, 0, sizeof(operate_));
	strncpy(operate_, name.c_str(), BASE_NAME_LEN-1);
}

bool OfficialToken::IsValid() const
{
	unsigned now = Time::GetGlobalTime();
	return ts_ > now;
}

//////////////////////////////////////////////////////////////
MemoryOfficialKingdom::MemoryOfficialKingdom()
	: personnel_ptr_(0)
	, privilege_ptr_(0)
{

}

void MemoryOfficialKingdom::InitJob()
{
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		departments_[i - 1].InitJob((eDepartment)i);
	}
}

OfficialDepartment& MemoryOfficialKingdom::GetDepartment(unsigned  nDepartment)
{
	if (nDepartment < e_Commander || nDepartment >= e_department_cnt)
	{
		throw std::runtime_error("department_params_error");
	}

	return departments_[nDepartment - 1];
}

bool MemoryOfficialKingdom::IsLeader(unsigned uid)
{
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		if (departments_[i - 1].IsLeader(uid))
		{
			return true;
		}
	}

	return false;
}

Official* MemoryOfficialKingdom::GetOfficialByUid(unsigned uid)
{
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		Official* official = departments_[i - 1].GetOfficialByUid(uid);
		if (official != NULL)
		{
			return official;
		}
	}

	return NULL;
}

OfficialDepartment* MemoryOfficialKingdom::GetDepartmentByUid(unsigned uid)
{
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		Official* official = departments_[i - 1].GetOfficialByUid(uid);
		if (official != NULL)
		{
			return &departments_[i - 1];
		}
	}

	return NULL;
}

std::pair<unsigned, unsigned> MemoryOfficialKingdom::GetUserOfficial(unsigned uid)
{
	for (int i = e_Commander; i < e_department_cnt; i++)
	{
		Official* official = departments_[i - 1].GetOfficialByUid(uid);
		if (official != NULL)
		{
			return std::make_pair(i, official->Job());
		}
	}

	return std::make_pair(0, 0);
}

void MemoryOfficialKingdom::SetNotice(const std::string& text)
{
	if (text.size() >= OFFICIAL_NOTICE_TEXT_LIMIT)
	{
		throw std::runtime_error("notice_too_long");
	}

	memset(notice_, 0, sizeof(notice_));
	memcpy(notice_, text.c_str(), text.size());
}

void MemoryOfficialKingdom::AddPersonnelRecord(const PersonnelRecord& record)
{
	if (personnel_ptr_  >= OFFICIAL_RECORD_CNT)
	{
		RomovePersonnelRecord(0, 10);
	}

	personnel_record_[personnel_ptr_++] = record;
}

void MemoryOfficialKingdom::RomovePersonnelRecord(unsigned index, unsigned nCnt)
{
	if (personnel_ptr_ <= (int)index)
	{
		return ;
	}

	int mv_cnt = personnel_ptr_ - index - nCnt;
	if (mv_cnt <= 0)
	{
		personnel_ptr_ = index;
		return ;
	}

	memmove(personnel_record_ + index, personnel_record_ + index + nCnt, mv_cnt * sizeof(PersonnelRecord));
	personnel_ptr_ -= nCnt;
}

void MemoryOfficialKingdom::AddPrivilegeRecord(const PrivilegeRecord& record)
{
	if (privilege_ptr_  >= OFFICIAL_RECORD_CNT)
	{
		RomovePrivilegeRecord(0, 10);
	}

	privilege_record_[privilege_ptr_++] = record;
}

void MemoryOfficialKingdom::RomovePrivilegeRecord(unsigned index, unsigned nCnt)
{
	if (privilege_ptr_ <= (int)index)
	{
		return ;
	}

	int mv_cnt = privilege_ptr_ - index - nCnt;
	if (mv_cnt <= 0)
	{
		privilege_ptr_ = index;
		return ;
	}

	memmove(privilege_record_ + index, privilege_record_ + index + nCnt, mv_cnt * sizeof(PrivilegeRecord));
	privilege_ptr_ -= nCnt;
}

const OfficialToken& MemoryOfficialKingdom::SetToken(
		  unsigned department
		, unsigned city_id
		, const std::string& name
		, const std::string& text)
{
	token_.Refresh(department, city_id, name, text);

	return token_;
}

int	  MemoryOfficialKingdom::GetPersonnelRecordSize() const
{
	return personnel_ptr_;
}

const PersonnelRecord& MemoryOfficialKingdom::GetPersonnelRecord(unsigned index) const
{
	if (index >= personnel_ptr_)
	{
		throw std::runtime_error("personnel_record_index_out");
	}

	return personnel_record_[index];
}

int	MemoryOfficialKingdom::GetPrivilegeRecordSize() const
{
	return privilege_ptr_;
}

const PrivilegeRecord& MemoryOfficialKingdom::GetPrivilegeRecord(unsigned index) const
{
	if (index >= privilege_ptr_)
	{
		throw std::runtime_error("privilege_record_index_out");
	}

	return privilege_record_[index];
}

////////////////////////////////////////////////////////////////////////////
int OfficialManager::OnInit()
{
	for(int i=0;i<SG17_KINGDOM; ++i)
	{
		m_data->data[i].InitJob();
	}

	return 0;
}

OfficialDepartment& OfficialManager::GetDepartment(unsigned kingdom, unsigned nDepartment)
{
	return GetOfficialKingdom(kingdom).GetDepartment(nDepartment);
}

bool OfficialManager::IsLeader(unsigned kingdom, unsigned uid)
{
	return GetOfficialKingdom(kingdom).IsLeader(uid);
}

Official* OfficialManager::GetOfficialByUid(unsigned kingdom, unsigned uid)
{
	return GetOfficialKingdom(kingdom).GetOfficialByUid(uid);
}

OfficialDepartment* OfficialManager::GetDepartmentByUid(unsigned kingdom, unsigned uid)
{
	return GetOfficialKingdom(kingdom).GetDepartmentByUid(uid);
}

std::pair<unsigned, unsigned> OfficialManager::GetUserOfficial(unsigned kingdom, unsigned uid)
{
	return GetOfficialKingdom(kingdom).GetUserOfficial(uid);
}
