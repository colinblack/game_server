#ifndef __LOGIC_ADMIN_H__
#define __LOGIC_ADMIN_H__

#include "LogicInc.h"

enum ADMIN_LEVEL
{
	ADMIN_LEVEL_0 = 0,		//只能查看
	ADMIN_LEVEL_1 = 1,		//只能禁言
	ADMIN_LEVEL_9 = 9,		//能改金币
	ADMIN_LEVEL_ALL = 10	//最高权限，能改金币，能导档
};

struct AdminSession
{
	string   skey;
	unsigned activeTime;
};

struct AdminInfo
{
	string pwd;
	int level;
};

class CLogicAdmin
{
public:
	static CDataGM* GetDataGM(void);
	int GetLevel(const string &name);
	int CheckLevel(const string &name, ADMIN_LEVEL needLevel);
	int Login(const string &name, const string &passwd, string &skey);
	int LoginCheck(string const &name,string const &skey);
	int AutoLogin(const string &name, string &skey);
	int ModifyPassword(const string &name, const string &password, const string &newpwd);
	int CheckSession(const string &name, const string &skey);
	int ChangePay(unsigned uid, int cash, int coins, DataPay &pay,int channel);
	int QueryUserInfo(unsigned uid, PlatformType pt, DataUserBasic &userBasic, DataUser &user);
	int QueryUserBasicInfo(const string &openid, PlatformType pt, DataUserBasic &userBasic);
	int QueryUser(unsigned uid, DataUser &user);
	int ChangeGcbase(unsigned uid, int gcbase, unsigned &balance);
	int ChangeStars(unsigned uid, int stars, unsigned &balance);
	int ChangeSoul(unsigned uid, int soul, unsigned &balance);
	int ChangeqlE(unsigned uid, int qle, unsigned &balance);
	int ChangePoint1(unsigned uid, int experience, unsigned &balance);   //经验值
	int ChangeR1(unsigned uid, int r1, unsigned &balance);
	int ChangeR2(unsigned uid, int r2, unsigned &balance);
	int ChangeR3(unsigned uid, int r3, unsigned &balance);
	int ChangeR4(unsigned uid, int r4, unsigned &balance);
	int ChangeR5(unsigned uid, int r5, unsigned &balance);
	int AddR(unsigned uid, const string &reason, int r1 = 0, int r2 = 0, int r3 = 0, int r4 = 0);
	int ChangeTutorialStage(unsigned uid, int tutorial_stage);
	int ChangeWfStatus(unsigned uid, const string &wf_status);
	int ChangeProsper(unsigned uid, int prosper, unsigned &balance);
	int ChangeBlockTs(unsigned uid, unsigned block_time, const string &close_reason);
	int ChangeRefreshTs(unsigned uid, unsigned refresh_time);
	int ChangeProtectTs(unsigned uid, unsigned pro_time);
	int ChangeBattleSpirits(unsigned uid, int battleSpirits, unsigned &balance);
	int ExportArchive(unsigned uid, Json::Value &result);
	int ImportArchive(unsigned uid, Json::Value &data, bool keepvip = false, uint64_t exp = 0, unsigned level = 0, unsigned lastlogin = 0);

	int AddAttack(unsigned uid1,unsigned uid2, unsigned res);
	int UpdatesAttack(uint64_t attack_id,unsigned uid1, unsigned uid2, unsigned res);

	int BroadCastByTool(string message, int repeats = 0, int interval = 0, string serverid="");
	int BroadCast(string message, int repeats = 0, int interval = 0, string serverid="");
	int AddForbidUser(unsigned uid,unsigned forbidts, string serverid="", string splatform="2");

	int SetFlag(const string &openid, unsigned flag);
	int CheckGM(const string &openid, unsigned &flag);

	int ChangePlatform(const string &name, const string &value);
	int ChangeActivityTime(const string &name, unsigned value);
	int GetPlatform(const string &name, string &value);
	int GetActivityTime(const string &name, unsigned &value);
	int ChangeBlockTs(const string &openid,unsigned block_time, const string &close_reason);
	int GetBlockTs(const string &openid, Json::Value &data);
	int GetInviteList(unsigned uid,Json::Value &data);
	bool CheckIp(string const &host);
	int UpdateBuildingLevel(unsigned uid, int buildingId, int buildingLev);
	static void Log(const string &admin, const string &op, const string &reason,
			unsigned uid, const string &value, const string &detail = "");
	static void R_Log(const string &admin,const string &op,const string &reason,
		unsigned uid,const string &value,const string &detail= "");
	static void AddHeroOrEquip_Log(const string &admin,const string &op, string &reason,
		unsigned uid, unsigned id, unsigned count);
	static void AddCheckLog(const string &admin, const string &ip, const string &op, string &reason, unsigned uid, unsigned id, int count);
	int AddAccCharge(unsigned uid, int accCharge);
	int Changewuhujiang(unsigned uid, unsigned zhang, unsigned jie);

	int AddJueXueBao(unsigned uid,unsigned juexue,unsigned exp,Json::Value &result);
	int AddLonglin(unsigned uid,unsigned longlin,unsigned &balance);

	int ChangeHeroCoin(unsigned uid, int coin, const string &reaseon, unsigned &blance);
	int ChangeRechargeAlliance(unsigned uid, int cash);

	int Th_ExportUserTech(unsigned uid, Json::Value &result);
	int Th_ImportUserTech(unsigned uid, Json::Value &data);
	int Th_ExportUserStat(unsigned uid, Json::Value &result);
	int Th_ImportUserStat(unsigned uid, Json::Value &data);
	int Th_ExportHero(unsigned uid, unsigned hero_ud, Json::Value &result);
	int Th_ImportHero(unsigned uid, Json::Value &data);
	int Th_ExportEquip(unsigned uid, unsigned equip_ud, Json::Value &result);
	int Th_ImportEquip(unsigned uid, Json::Value &data);
	int Th_ExportNewAct(unsigned uid, unsigned sid, Json::Value &result);
	int Th_ImportNewAct(unsigned uid, Json::Value &data);

	int KickOffline(unsigned uid);

private:
	static map<string, AdminInfo> adminList;
	static map<string, AdminSession> adminSession;
	static int UpdateAdminList();
};

#endif
