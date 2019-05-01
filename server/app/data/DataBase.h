

#ifndef DATABASE_H_
#define DATABASE_H_
#include "Kernel.h"


enum {
	COINTS_TYPE = 1,
	WOOD_TYPE = 2,
	FOOD_TYPE = 3,
	IRON_TYPE = 4,
	RESOURCE_TYPE = 5,
};

enum {
		INTEGRA_TIME_CNT_INIT = 5,//整点/后勤奖励次数
		PK_FIELD_CNT_INIT	  = 5, //竞技场次数
};

struct DataBase{
	uint32_t uid;
	uint8_t register_platform;//注册平台
	uint32_t register_time;//注册时间
	uint32_t invite_uid;//邀请者id
	uint8_t last_login_platform;//上次登录平台
	uint32_t last_login_time;//上次登录时间
	uint32_t login_times;//连续登录次数
	uint32_t login_days;//累计登录天数
	uint32_t last_active_time;//上次活跃时间
	uint32_t last_off_time;//上次下线时间
	uint32_t forbid_ts;//封号到期时间
	char forbid_reason[BASE_FORBID_REASON_LEN];//封号原因
	uint16_t invite_count;//邀请次数
	uint16_t today_invite_count;//今日邀请次数
	uint16_t tutorial_stage;//新手教程步骤
	char name[BASE_NAME_LEN];//名字
	char fig[BASE_FIG_LEN];//头像url
	uint8_t kingdom;//国家
	uint64_t exp;//经验
	uint8_t level;//等级
	uint32_t acccharge;//累计充值
	uint8_t viplevel;//vip等级
	uint32_t cash;//元宝
	uint32_t coin;//铜币--钞票--民居
	uint32_t wood;//木材--钢材--伐木厂
	uint32_t food;//粮食--石油--田
	uint32_t iron;//镔铁--黄金---矿场
	uint32_t ticket;//点券
	uint32_t silk;//(丝绸)废弃，作为回血ts
	uint16_t order;//募兵令
	uint16_t bag;//背包格子
	uint32_t preward;//内政功勋
	uint8_t loyal;//民忠
	uint8_t sacrifice;//免费祭祀次数
	uint32_t market;//(集市次数)废弃，作为龙鳞
	uint32_t bmarketcd;//黑市cd
	uint8_t banquet;//宴会次数
	uint16_t eshopintimacy;//装备商店亲密度
	uint32_t eshopcd;//装备商店cd
	uint8_t refresh;//免费洗练次数
	uint8_t arefresh;//免费至尊洗练次数
	uint8_t harmmer;//金色锤子次数
	uint8_t shadow; //(影子次数)废弃,作为充点小钱和杀敌活跃的标志位
	uint32_t up_res_time; //更新资源时间戳
	uint32_t rests;//领取国战资源的时戳
	uint8_t mp1;//国战个人任务状态 012  0--不可领取 1--可领取 2--已经领取
	uint8_t mp2;//国战个人任务状态 012
	uint8_t mk1;//国战国家任务状态 01   0--可领取   1--已经领取
	uint8_t mk2;//国战国家任务状态 01
	uint8_t rewardb;//国战功勋箱子数
	uint8_t mp3;//国战个人任务状态 01
	uint16_t npc_pass; //副本关卡
	uint16_t flamen_coins_cnt; //花费元宝祭祀金币次数
	uint16_t flamem_wood_cnt; //花费元宝祭祀木材
	uint16_t flamem_food_cnt; //花费元宝祭祀食物
	uint16_t flamem_iron_cnt; //花费元宝祭祀镔铁
	uint8_t first_recharge;  	//首充 1--可领取 2--已经领取
	uint8_t	auto_build_flag; 	//建筑自动升级特权标志
	uint8_t	integral_time_cnt; 	//整点奖励次数
	uint8_t vip_reward; //vip奖励领取进度
	uint8_t use_ship; //运船次数
	uint8_t rob_ship; //截船次数
	uint8_t ladder; //竞技场次数
	uint8_t mission_time; //政务次数
	uint32_t mission_id; //政务id
	uint32_t ladder_ts; //领取竞技场奖励时间
	uint32_t job_reward_ts; //领取军职奖励时间
	uint32_t mine_normal_ts; //普通矿开启时间
	uint32_t mine_reward_ts; //国家矿领取奖励时间
	uint32_t mine_exp;		  //开矿经验
	uint32_t token_op_ts;	  //响应官员令的时间戳
	uint16_t pass_reward;     //闯关送钻,位标记
	uint32_t daily_refresh_ts;  //每日任务的刷新时间
	uint8_t  daily_reward_times;  //每日任务领取奖励次数
	uint8_t  daily_free_times;  //每日任务已使用免费刷新次数
	uint32_t harbor_reward_ts;  //上次领取偷袭珍珠港奖励的时间

	DataBase(){
		uid = 0;
		register_platform = 0;
		register_time = 0;
		invite_uid = 0;
		last_login_platform = 0;
		last_login_time = 0;
		login_times = 0;
		login_days = 0;
		last_active_time = 0;
		last_off_time = 0;
		forbid_ts = 0;
		invite_count = 0;
		today_invite_count = 0;
		tutorial_stage = 0;
		kingdom = 0;
		exp = 0;
		level = 0;
		acccharge = 0;
		viplevel = 0;
		cash = 0;
		coin = 0;
		wood = 0;
		food = 0;
		iron = 0;
		ticket = 0;
		silk = 0;
		order = 0;
		bag = 0;
		preward = 0;
		loyal = 0;
		sacrifice = 0;
		market = 0;
		bmarketcd = 0;
		banquet = 0;
		eshopintimacy = 0;
		eshopcd = 0;
		refresh = 0;
		arefresh = 0;
		harmmer = 0;
		shadow = 0;
		up_res_time = 0;
		rests = 0;
		mp1 = 0;
		mp2 = 0;
		mp3 = 0;
		mk1 = 0;
		mk2 = 0;
		rewardb = 0;
		npc_pass = 0;
		flamen_coins_cnt = 0;
		flamem_wood_cnt = 0;
		flamem_food_cnt = 0;
		flamem_iron_cnt = 0;
		first_recharge = 0;
		auto_build_flag = 0;
		integral_time_cnt = 0;
		vip_reward = 0;
		use_ship = 0;
		rob_ship = 0;
		ladder = 0;
		mission_time = 0;
		mission_id = 0;
		ladder_ts = 0;
		job_reward_ts = 0;
		mine_normal_ts = 0;
		mine_reward_ts = 0;
		mine_exp = 0;
		token_op_ts = 0;
		pass_reward = 0;
		daily_refresh_ts = 0;
		daily_reward_times = 0;
		daily_free_times = 0;
		harbor_reward_ts = 0;

		memset(forbid_reason, 0, sizeof(forbid_reason));
		memset(name, 0, sizeof(name));
		memset(fig, 0, sizeof(fig));
	}

	void SetMessage(User::Base* msg)
	{
		msg->set_register_platform(register_platform);
		msg->set_register_time(register_time);
		msg->set_invite_uid(invite_uid);
		msg->set_last_login_platform(last_login_platform);
		msg->set_last_login_time(last_login_time);
		msg->set_login_times(login_times);
		msg->set_login_days(login_days);
		msg->set_last_active_time(last_active_time);
		msg->set_last_off_time(last_off_time);
		msg->set_forbid_ts(forbid_ts);
		msg->set_forbid_reason(string(forbid_reason));
		msg->set_invite_count(invite_count);
		msg->set_today_invite_count(today_invite_count);
		msg->set_tutorial_stage(tutorial_stage);
		msg->set_name(string(name));
		msg->set_fig(string(fig));
		msg->set_kingdom(kingdom);
		msg->set_exp(exp);
		msg->set_level(level);
		msg->set_acccharge(acccharge);
		msg->set_viplevel(viplevel);
		msg->set_cash(cash);
		msg->set_coin(coin);
		msg->set_wood(wood);
		msg->set_food(food);
		msg->set_iron(iron);
		msg->set_ticket(ticket);
		msg->set_silk(silk);
		msg->set_order(order);
		msg->set_bag(bag);
		msg->set_preward(preward);
		msg->set_loyal(loyal);
		msg->set_sacrifice(sacrifice);
		msg->set_market(market);
		msg->set_bmarketcd(bmarketcd);
		msg->set_banquet(banquet);
		msg->set_eshopintimacy(eshopintimacy);
		msg->set_eshopcd(eshopcd);
		msg->set_refresh(refresh);
		msg->set_arefresh(arefresh);
		msg->set_harmmer(harmmer);
		msg->set_shadow(shadow);
		msg->set_up_res_time(up_res_time);
		msg->set_rests(rests);
		msg->set_mp1(mp1);
		msg->set_mp2(mp2);
		msg->set_mp3(mp3);
		msg->set_mk1(mk1);
		msg->set_mk2(mk2);
		msg->set_rewardb(rewardb);
		msg->set_npc_pass(npc_pass);
		msg->set_flamem_food_cnt(flamem_food_cnt);
		msg->set_flamem_wood_cnt(flamem_wood_cnt);
		msg->set_flamen_coins_cnt(flamen_coins_cnt);
		msg->set_flamem_iron_cnt(flamem_iron_cnt);
		msg->set_first_recharge(first_recharge);
		msg->set_auto_build_flag(auto_build_flag);
		msg->set_integral_time_cnt(integral_time_cnt);
		msg->set_mission_time(mission_time);
		msg->set_mission_id(mission_id);
		msg->set_vip_reward(vip_reward);
		msg->set_ladder(ladder);
		msg->set_ladder_ts(ladder_ts);
		msg->set_job_reward_ts(job_reward_ts);
		msg->set_token_ts(token_op_ts);
		msg->set_daily_refresh_ts(daily_refresh_ts);
		msg->set_daily_reward_times(daily_reward_times);
		msg->set_daily_free_times(daily_free_times);
	}

	void FullBuildSyncMessage(ProtoBuilding::BuildUserSyncInfo* obj) const
	{
		obj->set_total_exploit(preward);
		obj->set_user_coins(coin);
		obj->set_user_woods(wood);
		obj->set_user_exp(exp);
		obj->set_user_level(level);
	}

	void FullResourceMessage(ProtoBuilding::BuildResourceSyncResq* obj) const
	{
		obj->set_coin(coin);
		obj->set_wood(wood);
		obj->set_food(food);
		obj->set_iron(iron);
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

	void		AddExp(int exp);
	void 	 	AddFlamenBuyCnt(int type, int cnt);
	uint16_t 	GetFlamenBuyCnt(int type);
	//
	uint32_t 	GetResource(int type);
	void 		AddResource(int type, int val);

	void RefreshIntegralTime();

	//重置国家任务状态
	void ResetCountryTaskStatus();
};

class CDataBase :public DBCBase<DataBase, DB_BASE>
{
public:
	virtual int Get(DataBase &data);
	virtual int Add(DataBase &data);
	virtual int Set(DataBase &data);
	virtual int Del(DataBase &data);
};


struct DataUser
{
	uint32_t uid;
	string name;
	uint32_t level;
	uint64_t exp;
	uint8_t viplevel;

	DataUser():
		uid(0),
		name(""),
		level(0),
		exp(0),
		viplevel(0)
	{

	}
};

#endif /* DATABASE_H_ */
