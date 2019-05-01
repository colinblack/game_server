/*
 * OfficialManager.h
 *
 *  Created on: 2016-11-1
 *      Author: dawx62fac
 */

#ifndef OFFICIALMANAGER_H_
#define OFFICIALMANAGER_H_

#include "Kernel.h"

enum {
	//OFFICIAL_DEPARTMENT_CNT	= 5, //部门人数
	OFFICIAL_DEPUTY_MEMBERS	= 2,
	OFFICIAL_CAPTAIN_MEMBERS 	= 10,
	OFFICIAL_DEPARTMENT_MEMBERS = 50,  //部门人数
	OFFICIAL_TOKEN_TEXT_LIMIT	= 200,
	OFFICIAL_NOTICE_TEXT_LIMIT	= 300, //公告长度限制
	OFFICIAL_RECORD_CNT			= 200, //记录数
};

//部门
enum eDepartment
{
	e_Commander = 1,  	//司令部
	e_Defense 	= 2,	//国防部
	e_President = 3, 	//总统府
	e_Marshal 	= 4,	//元帅府
	e_Staff 	= 5,  	//参谋部
	e_department_cnt
};

enum eOfficialType
{
	e_Teamer	= 0, //普通队员
	e_Minister 	= 1, //部长
	e_Deputy	= 10, //副部长  起始值
	e_Captain 	= 20, //队长     起始值
};

#define IS_VALID_DEPARTMENT(x) ((x) >= e_Commander && (x) < e_department_cnt)

#define IS_LEADER(x) ((x) == e_Minister)
#define IS_DEPUTY(x) (((x) >= e_Deputy) && (((x) % e_Deputy) < OFFICIAL_DEPUTY_MEMBERS))
#define IS_CAPTAIN(x) (((x) >= e_Captain) && (((x) % e_Captain) < OFFICIAL_CAPTAIN_MEMBERS))


class Official
{
public:
	Official();

	bool IsLeader() const; //部长
	bool IsDeputy() const; //副部长
	bool IsCaptain() const; //
	bool IsTeamer() const;

	bool IsNPC() const { return uid_ == 0; }

	unsigned Uid() const { return uid_; }
	unsigned Job() const { return job_; }
	void SetOfficialJob(uint8_t job) { job_ = job; }

	void Replace(unsigned uid);
	void Reset();

	eOfficialType Type() const;
private:
	unsigned uid_;  //=0 npc; >0 玩家
	uint8_t  job_;  //1--部长;(1x)--副级 ;(1xx)--队长 ;0--成员
};

//人事变动记录
class PersonnelRecord
{
public:
	PersonnelRecord();
	PersonnelRecord(const std::string& szOperate, const std::string& szTarget,
			uint8_t depart, uint8_t job);
public:
	char 	operate_[BASE_NAME_LEN]; //操作者
	char 	target_[BASE_NAME_LEN];  //目标者
	uint8_t department_; //部门
	uint8_t official_; //官职
	unsigned ts_;		  //变动时间
};

enum privilege_op
{
	e_Issue_Token_op = 1, //发布官员令
};

//特权记录
class PrivilegeRecord
{
public:
	PrivilegeRecord();
	PrivilegeRecord(unsigned op, const std::string& operate, uint8_t depart, uint8_t official);

	void SetParams(unsigned params);
	void SetTarget(const std::string& target);
public:
	char operate_[BASE_NAME_LEN]; //操作者
	char target_[BASE_NAME_LEN];  //人名
	uint8_t department_; 			//部门
	uint8_t official_; 				//官职
	unsigned ts_;		  //变动时间
	unsigned type_;		  //操作类型
	unsigned params_;	  //扩展参数
};

enum record_op
{
	e_ApplyJoin_op 	= 1, //申请加入
	e_Join_op	   	= 2, //加入记录
	e_Appoint_op	= 3, //任命
	e_Exit_op		= 4, //退出
	e_Usurp_op		= 5, //夺取官职
	e_Kick_op		= 6, //T人
};

//部门记录
class DepartmentRecord
{
public:
	DepartmentRecord(int op);
	DepartmentRecord();
	DepartmentRecord(const PersonnelRecord& record);

	uint8_t OP() const { return op_; }
public:
	//uint16_t id_; //id
	unsigned params_;  //
	char 	 operate_[BASE_NAME_LEN]; //操作者
	char 	 target_[BASE_NAME_LEN];  //
	unsigned operate_job_;
	unsigned target_job_;
	unsigned ts_;		  //变动时间
private:
	uint8_t  op_; //
};

class OfficialDepartment
{
	//deputy
	enum {
		DEPUTY_LIMIT = 2,  //副级干部数量上限
		CAPTAIN_LIMIT	= 10, //队长数量上限
	};
public:
	OfficialDepartment();
	OfficialDepartment(eDepartment type);

	void InitJob(eDepartment type);

	eDepartment Type() const { return type_; }
	unsigned Prestige() const { return prestige_;}  //官威
	void	CostPrestige(unsigned nCnt);
	//增加官威
	void AddPrestige(unsigned nVal);

	void SetLeader(unsigned uid);

	bool IsTeamer(unsigned uid) const;
	bool IsCaptain(unsigned uid) const;
	bool IsLeader(unsigned uid) const;   //部长
	bool IsDeputy(unsigned uid) const;  //副部长

	//Official& GetMember(unsigned nOfficial);
	Official& GetLeader();
	Official& GetCaptain(unsigned nOfficial);  //队长
	Official& GetDeputy(unsigned nOfficial);  //副部长

	Official& GetTeamerByIndex(int index);

	Official& GetOfficial(unsigned nOfficial);
	Official* GetOfficialByUid(unsigned uid); //无部门返回空

	//移除成员
	bool RemoveTeamer(unsigned uid);

	//替换有职官员
	void Replace(unsigned official, unsigned uid);

	//获取非部长外的真实玩家数
	unsigned GetRealMembers() const;
	//副部长人数
	unsigned GetDeputyCnt() const;

	//解雇
	Official& FireDeputy(unsigned uid);
	//任命副部长
	Official& AppointDeputy(unsigned uid);

	//获取空闲位置
	Official& GetEmptyDeputy();
	Official& GetEmptyTeamer();

	//是否已经申请
	bool IsAlreadyApply(unsigned uid);
	void RemoveApplyRecord(unsigned uid);

	//设置公告
	void SetNotice(const std::string& text);
	std::string GetNotice() const { return std::string(notice_); }
	//部门加入申请记录
	void AddApplyJoinRecord(unsigned uid, const std::string& name);
	//加入部门
	void AddJoinRecord(unsigned uid, const std::string& name);
	//任命负部长
	void AddAppointDeputyRecord(unsigned uid, unsigned job, const std::string& op, const std::string& adopt);
	//退出记录
	void AddExitRecord(unsigned uid, const std::string& op);
	//人事变动
	void AddRersonnelRecord(const PersonnelRecord& record);
	//T人
	void AddKickOutMemberRecord(unsigned uid, unsigned job, const std::string& op, const std::string& adopt);
	//
	int	  GetRecordSize() const;
	const DepartmentRecord& GetRecord(unsigned index) const;
private:
	void AddRecord(const DepartmentRecord& record);
	void RomoveRecord(unsigned index, unsigned nCnt = 1);
private:
	eDepartment type_;								//部门类型
	unsigned 	prestige_; //官威 只有部长有 官威
	Official	leader_; //部长
	Official	deputy_[OFFICIAL_DEPUTY_MEMBERS]; // 副部长
	Official	captain_[OFFICIAL_CAPTAIN_MEMBERS]; //队长
	Official 	member_[OFFICIAL_DEPARTMENT_MEMBERS]; 	//成员
	char 		notice_[OFFICIAL_NOTICE_TEXT_LIMIT];    //公告
	DepartmentRecord record_[OFFICIAL_RECORD_CNT];
	int			record_ptr_;
};

//官员令
class OfficialToken
{
	enum {
		OFFICIAL_TOKEN_VALID_TIME = 300,  //官员令的有效时间
	};
public:
	OfficialToken();
	void Refresh(unsigned department, unsigned city_id, const std::string& name, const std::string& text);

	bool IsValid() const;

	eDepartment Department() const { return department_; }
	unsigned TS() const { return ts_; }
	unsigned CityId() const { return city_id_; }
	std::string Text() const { return std::string(text_); }
	std::string Name() const { return std::string(operate_); }
private:
	eDepartment department_; //发布官员令的部长
	unsigned	ts_;	   //到期时间
	unsigned	city_id_;   //城市id
	char		text_[OFFICIAL_TOKEN_TEXT_LIMIT]; //自定义官员令对应文字信息
	char 	 	operate_[BASE_NAME_LEN]; //操作者名字
};

class MemoryOfficialKingdom
{
public:
	MemoryOfficialKingdom();
public:
	void InitJob();

	OfficialDepartment& GetDepartment(unsigned  nDepartment);
	bool				IsLeader(unsigned uid);  //判断是不是部长

	Official*			GetOfficialByUid(unsigned uid); //无部门返回空
	OfficialDepartment* GetDepartmentByUid(unsigned uid);

	void SetNotice(const std::string& text);
	std::string GetNotice() const { return std::string(notice_); }

	//获取玩家的部门和官职
	std::pair<unsigned, unsigned> GetUserOfficial(unsigned uid);

	//人事记录
	//void AddRersonnelRecord(const PersonnelRecord& record);

	const OfficialToken& GetToken() const { return token_;}
	const OfficialToken& SetToken(unsigned department, unsigned city_id, const std::string& name, const std::string& text);

	//人事记录
	int	  GetPersonnelRecordSize() const;
	const PersonnelRecord& GetPersonnelRecord(unsigned index) const;

	//特权
	int	  GetPrivilegeRecordSize() const;
	const PrivilegeRecord& GetPrivilegeRecord(unsigned index) const;

	void AddPersonnelRecord(const PersonnelRecord& record);
	void AddPrivilegeRecord(const PrivilegeRecord& record);
private:
	void RomovePersonnelRecord(unsigned index, unsigned nCnt = 1);
	void RomovePrivilegeRecord(unsigned index, unsigned nCnt = 1);
private:
	OfficialDepartment departments_[e_department_cnt - 1]; //5个部门
	char 			   notice_[OFFICIAL_NOTICE_TEXT_LIMIT];        //公告
	//记录
	int					personnel_ptr_; //记录指针
	PersonnelRecord		personnel_record_[OFFICIAL_RECORD_CNT];	//人事记录
	int					privilege_ptr_; //记录指针
	PrivilegeRecord		privilege_record_[OFFICIAL_RECORD_CNT]; //特权记录

	OfficialToken		token_; //官员令
};

struct MemoryOfficialAllData
{
	MemoryOfficialKingdom data[SG17_KINGDOM];
};

class OfficialManager : public MemorySingleton<MemoryOfficialAllData, MEMORY_OFFICIAL>, public CSingleton<OfficialManager>
{
private:
	friend class CSingleton<OfficialManager>;
	OfficialManager(){};
	virtual ~OfficialManager(){}
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	MemoryOfficialKingdom& GetOfficialKingdom(unsigned kingdom)
	{
		if (kingdom < 1 || kingdom > SG17_KINGDOM)
		{
			throw std::runtime_error("kingdom_params_error");
		}

		return this->m_data->data[kingdom - 1];
	}

	bool IsLeader(unsigned kingdom, unsigned uid);
	OfficialDepartment& GetDepartment(unsigned kingdom, unsigned nDepartment);

	Official*			GetOfficialByUid(unsigned kingdom, unsigned uid); //无部门返回空
	OfficialDepartment* GetDepartmentByUid(unsigned kingdom, unsigned uid);
	//获取玩家的部门和官职
	std::pair<unsigned, unsigned> GetUserOfficial(unsigned kingdom, unsigned uid);
};


#endif /* OFFICIALMANAGER_H_ */
