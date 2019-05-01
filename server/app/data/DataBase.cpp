
#include "DataBase.h"
#include "DataInc.h"



void DataBase::AddExp(int exp_)
{
	if (exp_ < 0)
	{
		error_log("params error. uid=%u,exp=%d", uid, exp_);
		return ;
	}

	if (exp_ == 0) return ;

	exp += exp_;

	const UserCfg::User& userCfg = UserCfgWrap().User();
	//更新用户level数据
	int levelSize = userCfg.user_exp_size();
	if (exp >=  userCfg.user_exp(levelSize - 1))
	{
		exp =  userCfg.user_exp(levelSize - 1);
		level = levelSize;
	}
	else
	{
		for (int i = level; i < levelSize; i++)
		{
			if (exp < (uint64_t)userCfg.user_exp(i))
			{
				level = i;
				break;
			}
		}
	}
}

uint16_t DataBase::GetFlamenBuyCnt(int type)
{
	if (type < 1 || type >= RESOURCE_TYPE)
	{
		error_log("type: %d", type);
		throw std::runtime_error("GetFlamenBuyCnt_params_error");
	}
	const uint16_t array_cnt[RESOURCE_TYPE - 1] ={flamen_coins_cnt
			, flamem_wood_cnt
			, flamem_food_cnt
			, flamem_iron_cnt};
	return array_cnt[type - 1];
}

void DataBase::AddFlamenBuyCnt(int type, int cnt)
{
	if (type < 1 || type >= RESOURCE_TYPE)
	{
		error_log("type: %d", type);
		throw std::runtime_error("AddFlamenBuyCnt_params_error");
	}
	uint16_t* array_cnt[RESOURCE_TYPE - 1] ={&flamen_coins_cnt
			, &flamem_wood_cnt
			, &flamem_food_cnt
			, &flamem_iron_cnt};
	*(array_cnt[type - 1]) += cnt;
}

uint32_t DataBase::GetResource(int type)
{
	if (type < 1 || type >= RESOURCE_TYPE)
	{
		error_log("type: %d", type);
		throw std::runtime_error("GetResource_params_error");
	}

	uint32_t* array_res[RESOURCE_TYPE - 1] = {&coin, &wood, &food, &iron};
	return *(array_res[type - 1]);
}

void DataBase::AddResource(int type, int val)
{
	if (type < 1 || type >= RESOURCE_TYPE)
	{
		error_log("type: %d", type);
		throw std::runtime_error("AddResource_params_error");
	}

	uint32_t* array_res[RESOURCE_TYPE - 1] = {&coin, &wood, &food, &iron};

	*(array_res[type - 1]) = *(array_res[type - 1]) + val;
}

void DataBase::RefreshIntegralTime()
{
	integral_time_cnt = INTEGRA_TIME_CNT_INIT;
}

void DataBase::ResetCountryTaskStatus()
{
	mp1 = 0;
	mp2 = 0;
	mp3 = 0;
	mk1 = 0;
	mk2 = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
int CDataBase::Get(DataBase &data)
{
	DBCREQ_DECLARE(DBC::GetRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(register_platform);
	DBCREQ_NEED(register_time);
	DBCREQ_NEED(invite_uid);
	DBCREQ_NEED(last_login_platform);
	DBCREQ_NEED(last_login_time);
	DBCREQ_NEED(login_times);
	DBCREQ_NEED(login_days);
	DBCREQ_NEED(last_active_time);
	DBCREQ_NEED(last_off_time);
	DBCREQ_NEED(forbid_ts);
	DBCREQ_NEED(forbid_reason);
	DBCREQ_NEED(invite_count);
	DBCREQ_NEED(today_invite_count);
	DBCREQ_NEED(tutorial_stage);
	DBCREQ_NEED(name);
	DBCREQ_NEED(fig);
	DBCREQ_NEED(kingdom);
	DBCREQ_NEED(exp);
	DBCREQ_NEED(level);
	DBCREQ_NEED(acccharge);
	DBCREQ_NEED(viplevel);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(coin);
	DBCREQ_NEED(wood);
	DBCREQ_NEED(food);
	DBCREQ_NEED(iron);
	DBCREQ_NEED(ticket);
	DBCREQ_NEED(silk);
	DBCREQ_NEED(order);
	DBCREQ_NEED(bag);
	DBCREQ_NEED(preward);
	DBCREQ_NEED(loyal);
	DBCREQ_NEED(sacrifice);
	DBCREQ_NEED(market);
	DBCREQ_NEED(bmarketcd);
	DBCREQ_NEED(banquet);
	DBCREQ_NEED(eshopintimacy);
	DBCREQ_NEED(eshopcd);
	DBCREQ_NEED(refresh);
	DBCREQ_NEED(arefresh);
	DBCREQ_NEED(harmmer);
	DBCREQ_NEED(shadow);
	DBCREQ_NEED(up_res_time);
	DBCREQ_NEED(rests);
	DBCREQ_NEED(mp1);
	DBCREQ_NEED(mp2);
	DBCREQ_NEED(mk1);
	DBCREQ_NEED(mk2);
	DBCREQ_NEED(rewardb);
	DBCREQ_NEED(mp3);
	DBCREQ_NEED(npc_pass);
	DBCREQ_NEED(flamen_coins_cnt);
	DBCREQ_NEED(flamem_wood_cnt);
	DBCREQ_NEED(flamem_food_cnt);
	DBCREQ_NEED(flamem_iron_cnt);
	DBCREQ_NEED(first_recharge);
	DBCREQ_NEED(auto_build_flag);
	DBCREQ_NEED(integral_time_cnt);
	DBCREQ_NEED(vip_reward);
	DBCREQ_NEED(use_ship);
	DBCREQ_NEED(rob_ship);
	DBCREQ_NEED(ladder);
	DBCREQ_NEED(mission_time);
	DBCREQ_NEED(mission_id);
	DBCREQ_NEED(ladder_ts);
	DBCREQ_NEED(job_reward_ts);
	DBCREQ_NEED(mine_normal_ts);
	DBCREQ_NEED(mine_reward_ts);
	DBCREQ_NEED(mine_exp);
	DBCREQ_NEED(token_op_ts);
	DBCREQ_NEED(pass_reward);
	DBCREQ_NEED(daily_refresh_ts);
	DBCREQ_NEED(daily_reward_times);
	DBCREQ_NEED(daily_free_times);
	DBCREQ_NEED(harbor_reward_ts);
	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(data, uid);
	DBCREQ_GET_INT(data, register_platform);
	DBCREQ_GET_INT(data, register_time);
	DBCREQ_GET_INT(data, invite_uid);
	DBCREQ_GET_INT(data, last_login_platform);
	DBCREQ_GET_INT(data, last_login_time);
	DBCREQ_GET_INT(data, login_times);
	DBCREQ_GET_INT(data, login_days);
	DBCREQ_GET_INT(data, last_active_time);
	DBCREQ_GET_INT(data, last_off_time);
	DBCREQ_GET_INT(data, forbid_ts);
	DBCREQ_GET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_GET_INT(data, invite_count);
	DBCREQ_GET_INT(data, today_invite_count);
	DBCREQ_GET_INT(data, tutorial_stage);
	DBCREQ_GET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_GET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_GET_INT(data, kingdom);
	DBCREQ_GET_INT(data, exp);
	DBCREQ_GET_INT(data, level);
	DBCREQ_GET_INT(data, acccharge);
	DBCREQ_GET_INT(data, viplevel);
	DBCREQ_GET_INT(data, cash);
	DBCREQ_GET_INT(data, coin);
	DBCREQ_GET_INT(data, wood);
	DBCREQ_GET_INT(data, food);
	DBCREQ_GET_INT(data, iron);
	DBCREQ_GET_INT(data, ticket);
	DBCREQ_GET_INT(data, silk);
	DBCREQ_GET_INT(data, order);
	DBCREQ_GET_INT(data, bag);
	DBCREQ_GET_INT(data, preward);
	DBCREQ_GET_INT(data, loyal);
	DBCREQ_GET_INT(data, sacrifice);
	DBCREQ_GET_INT(data, market);
	DBCREQ_GET_INT(data, bmarketcd);
	DBCREQ_GET_INT(data, banquet);
	DBCREQ_GET_INT(data, eshopintimacy);
	DBCREQ_GET_INT(data, eshopcd);
	DBCREQ_GET_INT(data, refresh);
	DBCREQ_GET_INT(data, arefresh);
	DBCREQ_GET_INT(data, harmmer);
	DBCREQ_GET_INT(data, shadow);
	DBCREQ_GET_INT(data, up_res_time);
	DBCREQ_GET_INT(data, rests);
	DBCREQ_GET_INT(data, mp1);
	DBCREQ_GET_INT(data, mp2);
	DBCREQ_GET_INT(data, mk1);
	DBCREQ_GET_INT(data, mk2);
	DBCREQ_GET_INT(data, rewardb);
	DBCREQ_GET_INT(data, mp3);
	DBCREQ_GET_INT(data, npc_pass);
	DBCREQ_GET_INT(data, flamen_coins_cnt);
	DBCREQ_GET_INT(data, flamem_wood_cnt);
	DBCREQ_GET_INT(data, flamem_food_cnt);
	DBCREQ_GET_INT(data, flamem_iron_cnt);
	DBCREQ_GET_INT(data, first_recharge);
	DBCREQ_GET_INT(data, auto_build_flag);
	DBCREQ_GET_INT(data, integral_time_cnt);
	DBCREQ_GET_INT(data, vip_reward);
	DBCREQ_GET_INT(data, use_ship);
	DBCREQ_GET_INT(data, rob_ship);
	DBCREQ_GET_INT(data, ladder);
	DBCREQ_GET_INT(data, mission_time);
	DBCREQ_GET_INT(data, mission_id);
	DBCREQ_GET_INT(data, ladder_ts);
	DBCREQ_GET_INT(data, job_reward_ts);
	DBCREQ_GET_INT(data, mine_normal_ts);
	DBCREQ_GET_INT(data, mine_reward_ts);
	DBCREQ_GET_INT(data, mine_exp);
	DBCREQ_GET_INT(data, token_op_ts);
	DBCREQ_GET_INT(data, pass_reward);
	DBCREQ_GET_INT(data, daily_refresh_ts);
	DBCREQ_GET_INT(data, daily_reward_times);
	DBCREQ_GET_INT(data, daily_free_times);
	DBCREQ_GET_INT(data, harbor_reward_ts);

	return 0;
}

int CDataBase::Add(DataBase &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, invite_uid);
	DBCREQ_SET_INT(data, last_login_platform);
	DBCREQ_SET_INT(data, last_login_time);
	DBCREQ_SET_INT(data, login_times);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, last_active_time);
	DBCREQ_SET_INT(data, last_off_time);
	DBCREQ_SET_INT(data, forbid_ts);
	DBCREQ_SET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_SET_INT(data, invite_count);
	DBCREQ_SET_INT(data, today_invite_count);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, kingdom);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, acccharge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, coin);
	DBCREQ_SET_INT(data, wood);
	DBCREQ_SET_INT(data, food);
	DBCREQ_SET_INT(data, iron);
	DBCREQ_SET_INT(data, ticket);
	DBCREQ_SET_INT(data, silk);
	DBCREQ_SET_INT(data, order);
	DBCREQ_SET_INT(data, bag);
	DBCREQ_SET_INT(data, preward);
	DBCREQ_SET_INT(data, loyal);
	DBCREQ_SET_INT(data, sacrifice);
	DBCREQ_SET_INT(data, market);
	DBCREQ_SET_INT(data, bmarketcd);
	DBCREQ_SET_INT(data, banquet);
	DBCREQ_SET_INT(data, eshopintimacy);
	DBCREQ_SET_INT(data, eshopcd);
	DBCREQ_SET_INT(data, refresh);
	DBCREQ_SET_INT(data, arefresh);
	DBCREQ_SET_INT(data, harmmer);
	DBCREQ_SET_INT(data, shadow);
	DBCREQ_SET_INT(data, up_res_time);
	DBCREQ_SET_INT(data, rests);
	DBCREQ_SET_INT(data, mp1);
	DBCREQ_SET_INT(data, mp2);
	DBCREQ_SET_INT(data, mk1);
	DBCREQ_SET_INT(data, mk2);
	DBCREQ_SET_INT(data, rewardb);
	DBCREQ_SET_INT(data, mp3);
	DBCREQ_SET_INT(data, npc_pass);
	DBCREQ_SET_INT(data, flamen_coins_cnt);
	DBCREQ_SET_INT(data, flamem_wood_cnt);
	DBCREQ_SET_INT(data, flamem_food_cnt);
	DBCREQ_SET_INT(data, flamem_iron_cnt);
	DBCREQ_SET_INT(data, first_recharge);
	DBCREQ_SET_INT(data, auto_build_flag);
	DBCREQ_SET_INT(data, integral_time_cnt);
	DBCREQ_SET_INT(data, vip_reward);
	DBCREQ_SET_INT(data, use_ship);
	DBCREQ_SET_INT(data, rob_ship);
	DBCREQ_SET_INT(data, ladder);
	DBCREQ_SET_INT(data, mission_time);
	DBCREQ_SET_INT(data, mission_id);
	DBCREQ_SET_INT(data, ladder_ts);
	DBCREQ_SET_INT(data, job_reward_ts);
	DBCREQ_SET_INT(data, mine_normal_ts);
	DBCREQ_SET_INT(data, mine_reward_ts);
	DBCREQ_SET_INT(data, mine_exp);
	DBCREQ_SET_INT(data, token_op_ts);
	DBCREQ_SET_INT(data, pass_reward);
	DBCREQ_SET_INT(data, daily_refresh_ts);
	DBCREQ_SET_INT(data, daily_reward_times);
	DBCREQ_SET_INT(data, daily_free_times);
	DBCREQ_SET_INT(data, harbor_reward_ts);

	DBCREQ_EXEC;
	return 0;
}

int CDataBase::Set(DataBase &data)
{
	DBCREQ_DECLARE(DBC::UpdateRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_SET_INT(data, register_platform);
	DBCREQ_SET_INT(data, register_time);
	DBCREQ_SET_INT(data, invite_uid);
	DBCREQ_SET_INT(data, last_login_platform);
	DBCREQ_SET_INT(data, last_login_time);
	DBCREQ_SET_INT(data, login_times);
	DBCREQ_SET_INT(data, login_days);
	DBCREQ_SET_INT(data, last_active_time);
	DBCREQ_SET_INT(data, last_off_time);
	DBCREQ_SET_INT(data, forbid_ts);
	DBCREQ_SET_CHAR(data, forbid_reason, BASE_FORBID_REASON_LEN);
	DBCREQ_SET_INT(data, invite_count);
	DBCREQ_SET_INT(data, today_invite_count);
	DBCREQ_SET_INT(data, tutorial_stage);
	DBCREQ_SET_CHAR(data, name, BASE_NAME_LEN);
	DBCREQ_SET_CHAR(data, fig, BASE_FIG_LEN);
	DBCREQ_SET_INT(data, kingdom);
	DBCREQ_SET_INT(data, exp);
	DBCREQ_SET_INT(data, level);
	DBCREQ_SET_INT(data, acccharge);
	DBCREQ_SET_INT(data, viplevel);
	DBCREQ_SET_INT(data, cash);
	DBCREQ_SET_INT(data, coin);
	DBCREQ_SET_INT(data, wood);
	DBCREQ_SET_INT(data, food);
	DBCREQ_SET_INT(data, iron);
	DBCREQ_SET_INT(data, ticket);
	DBCREQ_SET_INT(data, silk);
	DBCREQ_SET_INT(data, order);
	DBCREQ_SET_INT(data, bag);
	DBCREQ_SET_INT(data, preward);
	DBCREQ_SET_INT(data, loyal);
	DBCREQ_SET_INT(data, sacrifice);
	DBCREQ_SET_INT(data, market);
	DBCREQ_SET_INT(data, bmarketcd);
	DBCREQ_SET_INT(data, banquet);
	DBCREQ_SET_INT(data, eshopintimacy);
	DBCREQ_SET_INT(data, eshopcd);
	DBCREQ_SET_INT(data, refresh);
	DBCREQ_SET_INT(data, arefresh);
	DBCREQ_SET_INT(data, harmmer);
	DBCREQ_SET_INT(data, shadow);
	DBCREQ_SET_INT(data, up_res_time);
	DBCREQ_SET_INT(data, rests);
	DBCREQ_SET_INT(data, mp1);
	DBCREQ_SET_INT(data, mp2);
	DBCREQ_SET_INT(data, mk1);
	DBCREQ_SET_INT(data, mk2);
	DBCREQ_SET_INT(data, rewardb);
	DBCREQ_SET_INT(data, mp3);
	DBCREQ_SET_INT(data, npc_pass);
	DBCREQ_SET_INT(data, flamen_coins_cnt);
	DBCREQ_SET_INT(data, flamem_wood_cnt);
	DBCREQ_SET_INT(data, flamem_food_cnt);
	DBCREQ_SET_INT(data, flamem_iron_cnt);
	DBCREQ_SET_INT(data, first_recharge);
	DBCREQ_SET_INT(data, auto_build_flag);
	DBCREQ_SET_INT(data, integral_time_cnt);
	DBCREQ_SET_INT(data, vip_reward);
	DBCREQ_SET_INT(data, use_ship);
	DBCREQ_SET_INT(data, rob_ship);
	DBCREQ_SET_INT(data, ladder);
	DBCREQ_SET_INT(data, mission_time);
	DBCREQ_SET_INT(data, mission_id);
	DBCREQ_SET_INT(data, ladder_ts);
	DBCREQ_SET_INT(data, job_reward_ts);
	DBCREQ_SET_INT(data, mine_normal_ts);
	DBCREQ_SET_INT(data, mine_reward_ts);
	DBCREQ_SET_INT(data, mine_exp);
	DBCREQ_SET_INT(data, token_op_ts);
	DBCREQ_SET_INT(data, pass_reward);
	DBCREQ_SET_INT(data, daily_refresh_ts);
	DBCREQ_SET_INT(data, daily_reward_times);
	DBCREQ_SET_INT(data, daily_free_times);
	DBCREQ_SET_INT(data, harbor_reward_ts);

	DBCREQ_EXEC;
	return 0;
}

int CDataBase::Del(DataBase &data)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, data.uid);
	DBCREQ_SET_KEY(data.uid);
	DBCREQ_EXEC;
	return 0;
}


