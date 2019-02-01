

#ifndef DATABASE_H_
#define DATABASE_H_
#include "Kernel.h"


struct DataBase{
	uint32_t uid;
	uint32_t register_platform;//注册平台
	uint32_t register_time;//注册时间
	uint32_t last_login_platform;//(上次登录平台)废弃， 作为累计在线秒数
	uint32_t last_login_time;//上次登录时间
	uint32_t login_times;//连续登录次数
	uint32_t login_days;//累计登录天数
	uint32_t last_active_time;//上次活跃时间
	uint32_t last_off_time;//上次下线时间
	uint32_t forbid_ts;//封号到期时间
	char forbid_reason[BASE_FORBID_REASON_LEN];//封号原因
	uint32_t tutorial_stage;//新手教程步骤
	char name[BASE_NAME_LEN];//名字
	char fig[BASE_FIG_LEN];//头像url
	uint64_t exp;//经验
	uint32_t level;//等级
	uint32_t acccharge;//累计充值
	uint32_t viplevel;//vip等级
	uint32_t cash;//二级货币
	uint32_t coin;//代币
	uint32_t first_recharge;  	//首充领取标志。按位表示第一次，第二次首充状态
	uint32_t alliance_id;//加入的联盟
	uint16_t archive_chip[ARCHIVE_CHIP_LENGTH];   //图鉴碎片
	char archive_level[ARCHIVE_LENGTH]; //图鉴等级
	char archive_reward[ARCHIVE_LENGTH]; //图鉴奖励已领次数
	uint32_t power; //体力
	uint32_t recover_time;//体力恢复时间
	uint32_t pass;	//通过的关卡编号
	char limit_times_props[LIMIT_TIMES_PROPS_LEN]; //每日限次道具使用记录
	uint32_t use_props_ts; //每日限次道具使用时戳
	uint32_t heroId;	//保存开场动画英雄
	uint64_t honor;	//荣誉值
	uint32_t daily_power; //每天收到好友的体力值
	uint32_t daily_power_ts; //每日收到好友体力时戳
	uint32_t onhook_coin_ts; //挂机金币时戳
	uint32_t onhook_exp_ts;	//挂机经验时戳
	uint32_t daily_battle_ts;	//记录上次踢馆时间
	uint32_t daily_battle_count;  //每日踢馆次数
	uint32_t invite_friend_count;	//邀请好友数量
	uint64_t invite_reward_mark;  //邀请玩家奖励领取标志
	uint32_t invite_add_reward_mark; //累积邀请玩家奖励标志
	uint32_t free_draw_reward_ts;	//免费抽奖时戳

	DataBase(){
		uid = 0;
		register_platform = 0;
		register_time = 0;
		last_login_platform = 0;
		last_login_time = 0;
		login_times = 0;
		login_days = 0;
		last_active_time = 0;
		last_off_time = 0;
		forbid_ts = 0;
		tutorial_stage = 0;
		exp = 0;
		level = 1;
		acccharge = 0;
		viplevel = 0;
		cash = 0;
		coin = 0;
		first_recharge = 0;
		alliance_id = 0;
		power = 0;
		recover_time = 0;
		pass = 0;
		use_props_ts  = 0;
		heroId = 0;
		honor  = 100;
		daily_power = 0;
		daily_power_ts = 0;
		onhook_coin_ts = 0;
		onhook_exp_ts = 0;
		daily_battle_ts = 0; //记录上次踢馆时间
		daily_battle_count = 0;  //每日踢馆次数
		invite_friend_count = 0;
		invite_reward_mark = 0;
		invite_add_reward_mark = 0;
		free_draw_reward_ts = 0;
		memset(forbid_reason, 0, sizeof(forbid_reason));
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
		memset(archive_chip, 0, sizeof(archive_chip));
		memset(archive_level, 0, sizeof(archive_level));
		memset(limit_times_props, 0, sizeof(limit_times_props));
		memset(archive_reward, 0, sizeof(archive_reward));

	}

	void SetMessage(User::Base* msg)
	{
		msg->set_uid(uid);
		msg->set_registerplatform(register_platform);
		msg->set_registertime(register_time);
		msg->set_lastloginplatform(last_login_platform);
		msg->set_lastlogintime(last_login_time);
		msg->set_logintimes(login_times);
		msg->set_logindays(login_days);
		msg->set_lastactivetime(last_active_time);
		msg->set_lastofftime(last_off_time);
		msg->set_forbidts(forbid_ts);
		msg->set_forbidreason(string(forbid_reason));
		msg->set_tutorialstage(tutorial_stage);
		msg->set_name(string(name));
		msg->set_fig(string(fig));
		msg->set_exp(exp);
		msg->set_level(level);
		msg->set_acccharge(acccharge);
		msg->set_viplevel(viplevel);
		msg->set_cash(cash);
		msg->set_coin(coin);
		msg->set_firstrecharge(first_recharge);
		msg->set_allianceid(alliance_id);
		msg->set_archivechip(archive_chip, ARCHIVE_CHIP_LENGTH*2);
		msg->set_archivelevel(archive_level, ARCHIVE_LENGTH);
		msg->set_archivereward(archive_reward, ARCHIVE_LENGTH);
		msg->set_power(power);
		msg->set_recovertime(recover_time);
		msg->set_pass(pass);
		msg->set_limittimesprops(limit_times_props, LIMIT_TIMES_PROPS_LEN);
		msg->set_usepropsts(use_props_ts);
		msg->set_heroid(heroId);
		msg->set_honor(honor);
		msg->set_dailypower(daily_power);
		msg->set_dailypowerts(daily_power_ts);
		msg->set_onhookcoints(onhook_coin_ts);
		msg->set_onhookexpts(onhook_exp_ts);
		msg->set_dailybattlets(daily_battle_ts);
		msg->set_dailybattlecount(daily_battle_count);
		msg->set_invitefriendcount(invite_friend_count);
		msg->set_inviterewardmark(invite_reward_mark);
		msg->set_inviteaddrewardmark(invite_add_reward_mark);
		msg->set_freedrawrewardsts(free_draw_reward_ts);
	}

	bool IsOnline()
	{
		return last_off_time < last_login_time;
	}

	bool CanOff()
	{
		return IsOnline() && last_active_time + 12 * 3600 < Time::GetGlobalTime();
	}

	bool CanClear()
	{
		return !IsOnline() && last_off_time + 300 < Time::GetGlobalTime();
	}

	void AddExp(int exp_);
};

class CDataBase :public DBCBase<DataBase, DB_BASE>
{
public:
	virtual int Get(DataBase &data);
	virtual int Add(DataBase &data);
	virtual int Set(DataBase &data);
	virtual int Del(DataBase &data);
};

#endif /* DATABASE_H_ */
