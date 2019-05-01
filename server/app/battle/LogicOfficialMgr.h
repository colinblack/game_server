/*
 * LogicOfficialMgr.h
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */

#ifndef LOGICOFFICIALMGR_H_
#define LOGICOFFICIALMGR_H_

#include "ServerInc.h"

#define OFFICIAL_OPEN_LEVEL (25) //官职系统开放等级


class  LogicOfficialMgr : public BattleSingleton, public CSingleton<LogicOfficialMgr>
{
private:
	friend class CSingleton<LogicOfficialMgr>;
	LogicOfficialMgr() {};


	void CheckUserParams(const DBCUserBaseWrap& user) const;
	void CheckDepartmentParams(unsigned department) const;

	OfficialManager* DataPtr()
	{
		return OfficialManager::Instance();
	}

	//
	unsigned GetPkRival(const DBCUserBaseWrap& user, unsigned department, unsigned official);
	unsigned GetYieldsAdd(const OfficialConfig::OfficialJob& cfg, int type);
	//
	void FullMessage(Official& official, ProtoOfficial::DepartmentMember* obj);
	//
	void FullMessage(OfficialDepartment& department, ProtoOfficial::DepartmentLeader* obj);
	//部门记录
	void FullMessage(const DepartmentRecord& reocrd, ProtoOfficial::DepartmentRecord* obj);
	void FullMessage(OfficialDepartment& depart_obj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::DepartmentRecord >* obj);
	//人事记录
	void FullMessage(const PersonnelRecord& record, ProtoOfficial::PersonnelRecord* obj);
	void FullMessage(MemoryOfficialKingdom& kingdomObj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::PersonnelRecord >* obj);
	//特权
	void FullMessage(const PrivilegeRecord& record, ProtoOfficial::PrivilegeRecord* obj);
	void FullMessage(MemoryOfficialKingdom& kingdomObj, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::PrivilegeRecord >* obj);

	void FullMessage(int kingdom, const OfficialToken& token, ProtoOfficial::PublishToken* obj);

	std::string GetPlayerName(unsigned uid);

	unsigned PkNPC(unsigned department, unsigned official);

	//部门成员
	void FullMembers(OfficialDepartment& department, ::google::protobuf::RepeatedPtrField< ::ProtoOfficial::DepartmentMember >* obj);

	//将信息更新到resourcemanger里面
	void RefreshUserDepartinfo(unsigned uid, unsigned department, unsigned official);

	bool IsMeetPushToken(unsigned uid, unsigned cityId);

	//军职挑战外部接口
	int ChallengeExternalInterface(unsigned uid);

public:
	virtual void CallDestroy() { Destroy();}


	void FullMessage(const DataBase &base, User::User* obj);
	//department--部门 official--官职
	void FinishPkSuccess(unsigned uid, unsigned department, unsigned official);

	//获取加成
	unsigned GetYieldsAdd(const DBCUserBaseWrap& user, int type);

	//玩家的官职发生了变化  消息推送
	void OnChangeOfficial(unsigned uid, unsigned origin_depart, int origin_job, unsigned target_depart, int target_job);

	void OnHour();

	//挑战
	int Process(unsigned uid, ProtoOfficial::ChallengeReq* req, ProtoOfficial::ChallengeResp* resp);
	//开始挑战
	int Process(unsigned uid, ProtoOfficial::StartChallengeReq* req);
	//任命/解雇副部长
	int Process(unsigned uid, ProtoOfficial::AppointDeputyReq* req, ProtoOfficial::AppointDeputyResp* resp);
	//申请加入
	int Process(unsigned uid, ProtoOfficial::ApplyJoinReq* req, ProtoOfficial::ApplyJoinResp* resp);
	//退出申请
	int Process(unsigned uid, ProtoOfficial::ApplyExitReq* req, ProtoOfficial::ApplyExitResp* resp);
	//同意加入部门
	int Process(unsigned uid, ProtoOfficial::AgreeJoinReq* req, ProtoOfficial::AgreeJoinResp* resp);
	//公告编辑
	int Process(unsigned uid, ProtoOfficial::SetNoticeReq* req);
	//官职信息
	int Process(unsigned uid, ProtoOfficial::OfficialInfoReq* req, ProtoOfficial::OfficialInfoResp* resp);
	//俸禄
	int Process(unsigned uid, ProtoOfficial::GetSalaryReq* req, ProtoOfficial::GetSalaryResp* resp);
	//拒绝
	int Process(unsigned uid, ProtoOfficial::RefuseJoinReq* req, ProtoOfficial::RefuseJoinResp* resp);
	//部门记录
	int Process(unsigned uid, ProtoOfficial::GetDepartmentRecordReq* req, ProtoOfficial::GetDepartmentRecordResp* resp);
	//官员令
	int Process(unsigned uid, ProtoOfficial::PublishTokenReq* req);
	//人事记录
	int Process(unsigned uid, ProtoOfficial::GetPersonnelRecordReq* req, ProtoOfficial::GetPersonnelRecordResp* resp);
	//特权记录
	int Process(unsigned uid, ProtoOfficial::GetPrivilegeRecordReq* req, ProtoOfficial::GetPrivilegeRecordResp* resp);
	//T人
	int Process(unsigned uid, ProtoOfficial::KickOutMemberReq* req, ProtoOfficial::KickOutMemberResp* resp);
	//响应官员令
	int Process(unsigned uid, ProtoOfficial::RespondTokenReq* req, ProtoOfficial::RespondTokenResp* resp);
};


#endif /* LOGICOFFICIALMGR_H_ */
