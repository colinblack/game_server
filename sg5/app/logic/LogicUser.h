#ifndef LOGICUSER_H_
#define LOGICUSER_H_

#include "LogicInc.h"

#define LOCK_USER 1

#if LOCK_USER == 1
	#define AUTO_LOCK_USER(uid) CAutoLock lock_user(CLogicUser::GetLock(uid), true);
#else
	#define AUTO_LOCK_USER(uid)
#endif

#if LOCK_USER == 1
	#define AUTO_LOCK_SAVE_USER(uid,type) CAutoLock lock_user(CLogicUser::GetSaveLock(uid,type), true);
#else
	#define AUTO_LOCK_SAVE_USER(uid,type)
#endif

#if LOCK_USER == 1
	#define LOCK_LOCK_USER(uid) CLogicUser::Lock(uid);
#else
	#define LOCK_LOCK_USER(uid)
#endif

#if LOCK_USER == 1
	#define UNLOCK_LOCK_USER(uid) CLogicUser::Unlock(uid);
#else
	#define UNLOCK_LOCK_USER(uid)
#endif

enum UserStatus
{
	US_ACTIVE = 0,
	US_REMOVE = 1,
	US_BAN = 2
};

enum UserType
{
	UT_NORMAL = 0,
	UT_NOT_REAL = 1,
};

enum UserClass
{
	US_CLASS_UNKNOWN     = 0,
	US_CLASS_PAY_ONE     = 1,  //大R用户
	US_CLASS_PAY_TOW     = 2,  //中R用户
	US_CLASS_PAY_THREE   = 3,  //小R用户
	US_CLASS_LIKE_WAR    = 4,  //攻城超过5次的用户
	US_CLASS_ACTIVE      = 5,  //经常登录的用户
	US_CLASS_IN_ALLIANCE = 6,  //有联盟的用户
	US_CLASS_NOT_REAL    = 7,  //假用户
	US_CLASS_LOW_LEVEL   = 8,  //20级以下的用户
	US_CLASS_OTHER       = 9,  //其他
	US_CLASS_MAX,
};
/*
union USER_BIT_INFO
{
	unsigned v;
	struct
	{
		unsigned beAttacked:1;	//正在被攻击状态
		unsigned canOnlineAttacked:1;	//能否在线被攻击
	}s;
};

enum UserFlag
{
	UF_BE_ATTACKED,
	UF_BE_CAN_ONLINE_ATTACKED
};
*/
class CLogicUser
{
public:
	int AddUser(unsigned uid, PlatformType platform, unsigned inviteUid);	//返回uid
	int ProcessInvite(unsigned uid, unsigned inviteUid);

	int SetUser(unsigned uid, DataUser &user, unsigned flag = 0);
	int SetUserLimit(DataUser &user, unsigned flag = 0);
	int SetUserLimit(unsigned uid, DataUser &user, unsigned flag = 0);	//不含user_stat

	int GetUser(unsigned uid, DataUser &user, unsigned uidBy=0);
	int GetUserLimit(unsigned uid, DataUser &user);	//不含user_stat

	int RemoveUser(unsigned uid);

	int UpdateLogin(unsigned uid, PlatformType platform, unsigned loginTime = 0);
	//更新最近活跃时间，同时统计并更新在线时长,last_active_time 最返活跃时间，ext 在线时长
	int UpdateActiveTime(unsigned uid, unsigned last_active_time, int ext);
	int UpdateLastSaveUid(unsigned uid, unsigned last_save_uid);
	int UpdateProtectedTime(unsigned uid, unsigned protected_time = 0);
//	int UpdateBitInfo(unsigned uid, unsigned bit_info);
	int SetBitInfo(unsigned uid, unsigned bit_info);
	int SetBitInfoLastSaveUid(unsigned uid, unsigned bit_info, unsigned last_save_uid);
	int UpdateBreathTime(unsigned uid, unsigned breathTime = 0);
	//更新最近活跃时间和最近呼吸时间，同时统计并更新在线时长,last_active_time 最返活跃时间，ext 在线时长
	int UpdateActiveExtBreathTime(unsigned uid, unsigned last_active_time, int ext);
	int ChangeResource(unsigned uid, int r1, int r2, int r3, int r4);

	int GetUserFlag(unsigned uid, Json::Value &userFlag);
	int SetUserFlag(unsigned uid, const Json::Value &userFlag);

	int GetUserTech(unsigned uid, Json::Value &userTech);
	int SetUserTech(unsigned uid, const Json::Value &userTech);

	int GetUserStat(unsigned uid, Json::Value &userStat);
	int SetUserStat(unsigned uid, const Json::Value &userStat);
	// mainpos
	int TransformVipLevel(int accChargeTotal, int &vipLevel);	
	int GetUserClass(unsigned uid, int &type);
	int GetMainpos(unsigned uid, unsigned &mainpos);
	int SetMainpos(unsigned uid, const  unsigned mainpos);

	int ChangeBet(unsigned uid, int bet, bool allserver = false);
	int ChangeBetForBack(unsigned uid, int bet, string &userStat, unsigned &balance);
//	static bool GetFlag(unsigned bit_info, UserFlag flag);
//	static void SetFlag(unsigned &bit_info, UserFlag flag, bool value);

	int CheckR5(DataUser &user);//20150908 Ralf fix
	int SetR5(unsigned uid, int r5_max);

	static ILock* GetLock(unsigned uid);
	static ILock* GetSaveLock(unsigned uid, LoadType type);
	static void Lock(unsigned uid);
	static void Unlock(unsigned uid);
protected:
	static map<unsigned, ILock*> m_lockmap;
};

#endif /* LOGICUSER_H_ */
