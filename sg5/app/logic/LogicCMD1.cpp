/*
 * LogicCMD1.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */



#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>


int CLogicCMD::CountryDayLogin(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数是否合法
	if (order > COUNTRY_DAY_LOGIN_KINDS || !order)
	{
		PARAM_ERROR_RETURN_MSG("order_illegal");
	}

	//从配置读取 活动时间， 判断该活动是否开启了,
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned begin_ts_activity = 0;
	unsigned end_ts_activity = 0;
	int ret = 0;
	ret = dataXML->GetCountryDayLoginOpenTime(begin_ts_activity, end_ts_activity);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetXML_activity_time_fail");
	}
	unsigned now_ts = Time::GetGlobalTime();
	if (now_ts < begin_ts_activity || now_ts > end_ts_activity)
	{
		DATA_ERROR_RETURN_MSG("activity_no_open");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//对newAct进行初始化
	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_GUOQING_LOGIN, newAct);  //newAct: {"a":ts,"b":0,"c":0, "l":[0,0,0,0,0,0,0], "id":83}
	if (R_ERR_NO_DATA == ret)
	{
		newAct["id"] = NAT_GUOQING_LOGIN;
		newAct["a"]=  0;
		newAct["b"] = 0;
		newAct["c"] = 0;
		for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_LOGIN_OPEN_DAYS; ++ix)
		{
			newAct["l"][ix] = 0;
		}
	} else if (R_SUCCESS != ret)
	{
		DATA_ERROR_RETURN_MSG("get_newact_guoqing_login");
	}

	//判断 玩家是否已经领取过了
	if ((order == 1) && Time::IsToday(newAct["a"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("one_day_only_one");
	}
	if ((order == 2) && newAct["b"].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("five_day_only_one");
	}
	if  ((order == 3) && newAct["c"].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("seven_day_only_one");
	}

	//根据order 来判断 该玩家登录时间 是否满足了要求
	unsigned total_login_days = 0;
	for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_LOGIN_OPEN_DAYS; ++ix)
	{
		total_login_days += newAct["l"][ix].asUInt();
	}
	if ((order == 2) && (total_login_days < 5))
	{
		LOGIC_ERROR_RETURN_MSG("login_days_not_enough");
	}
	if ((order == 3) && (total_login_days < 7))
	{
		LOGIC_ERROR_RETURN_MSG("login_days_not_enough");
	}

	//给玩家发奖励 (奖励里没有英雄), 将物品返回给前端
	XMLCountryDayLoginItem login_item;
	ret = dataXML->GetCountryDayLoginItem(order - 1, login_item);
	if (ret)
	{
		error_log("GetCountryDayLoginItem failed, uid=%u, order=%u", uid, order);
		return ret;
	}

	string szReason;
	if (order == 1)
	{
		szReason = "country_day_login_daily";
	} else if (order == 2)
	{
		szReason = "country_day_login_five";
	} else
	{
		szReason = "country_day_login_seven";
	}
	vector<ItemAdd> items;
	items.clear();
	for(int ix = 0; ix != MAX_COUNTRY_DAY_LOGIN_EQUIP_CNT; ++ix)
	{
		if (login_item.equip_items_[ix].eqid_)
		{
			items.push_back(ItemAdd(login_item.equip_items_[ix].eqid_, login_item.equip_items_[ix].cnt_, szReason));
		}
	}
	CLogicEquipment logicEquip;
	if ((ret = logicEquip.AddItems(uid, items, result["equipment"], true)) != 0)
	{
		error_log("GetCountryDayLoginItem AddItems failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	//标记玩家已经领取过了, 将newAct返回给前端
	if (order == 1)
	{
		newAct["a"]=  now_ts;
	} else if (order == 2)
	{
		newAct["b"] = 1;
	} else
	{
		newAct["c"] = 1;
	}
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		error_log("GetCountryDayLoginItem SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::CountryDayShop(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数是否合法
	if (order > MAX_COUNTRY_DAY_SHOP_ITEMS || !order)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	//活动是否开启了
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned begin_ts_activity = 0;
	unsigned end_ts_activity = 0;
	int ret = 0;
	ret = dataXML->GetCountryDayShopOpenTime(begin_ts_activity, end_ts_activity);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetXML_activity_time_fail");
	}
	unsigned now_ts = Time::GetGlobalTime();
	if (now_ts < begin_ts_activity || now_ts > end_ts_activity)
	{
		DATA_ERROR_RETURN_MSG("activity_no_open");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//对newAct进行初始化   newAct {"a":[[2,ts], [c,ts], [c,ts]], "id":1}  打算一个存放7个
	unsigned index_db_nat = 0;
	if (order <= MAX_COUNTRY_DAY_SHOP_DB_CNT)
	{
		index_db_nat = NAT_GUOQING_SHOP_ONE;
	} else if (order > MAX_COUNTRY_DAY_SHOP_DB_CNT && order <= 2*MAX_COUNTRY_DAY_SHOP_DB_CNT)
	{
		index_db_nat = NAT_GUOQING_SHOP_TWO;
	} else
	{
		PARAM_ERROR_RETURN_MSG("order is illegal");
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, index_db_nat, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		newAct["id"] = index_db_nat;
		for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_SHOP_DB_CNT; ++ix)  //7代表数据表里最大存放的个数
		{
			newAct["a"][ix][0u] = 0;
			newAct["a"][ix][1u] = 0;
		}
	} else if (R_SUCCESS != ret)
	{
		DATA_ERROR_RETURN_MSG("guoqing_shop_get_secinc");
	}

	//对玩家的数据进行更新， 当 变成另一天后
	unsigned index_mapping_order = (order - 1) % MAX_COUNTRY_DAY_SHOP_DB_CNT;
	if ((!Time::IsToday(newAct["a"][index_mapping_order][1u].asUInt()))  &&
		(!newAct["a"][index_mapping_order][0u].asUInt()))
	{
		newAct["a"][index_mapping_order][0u] = 0;
	}

	//每种物品每日购买的次数是否够了
	XMLCountryDayShopItem shop_item;
	ret = dataXML->GetCountryDayShopItem(order - 1, shop_item);
	if (ret)
	{
		error_log("GetCountryDayShopItem failed, uid=%u, order=%u", uid, order);
		return ret;
	}

	if (newAct["a"][index_mapping_order][0u].asUInt() >= shop_item.limit_)
	{
		LOGIC_ERROR_RETURN_MSG("can_get_no_more");
	}
	//购买时间是否仍在在 冷却里
	if (newAct["a"][index_mapping_order][1u].asUInt() > now_ts)
	{
		LOGIC_ERROR_RETURN_MSG("is_still_freeze");
	}

	//扣钱
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);

	unsigned need_cash = shop_item.cash_;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "country_day_shop_"+ CTrans::UTOS(shop_item.id_);
	ret = logicPay.ProcessOrderForBackend(uid, -need_cash, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;



	//然后添加物品， 将物品返回给前端
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, shop_item.eqid_, shop_item.eq_cnt_, "country_day_shop_" + CTrans::UTOS(shop_item.id_), result["equip"], true);
	if (ret)
	{
		error_log("CountryDayShop_AddOneItem failed, uid=%u, id=%u, ret=%d", uid, shop_item.id_, ret);
		return ret;
	}

	//更改newAct里的玩家的 购买次数 和 购买时间。 将newAct返回给前端
	if (Time::IsToday(now_ts + shop_item.ts_))
	{
		newAct["a"][index_mapping_order][0u] = newAct["a"][index_mapping_order][0u].asUInt() + 1;
		newAct["a"][index_mapping_order][1u] = now_ts + shop_item.ts_;
	} else
	{
		newAct["a"][index_mapping_order][0u] = 0;
		newAct["a"][index_mapping_order][1u] = (unsigned)CTime::GetDayBeginTime(now_ts + shop_item.ts_);
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		error_log("CountryDayShop SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = newAct;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::CountryDayBag(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//参数是否合法
	if (order > MAX_COUNTRY_DAY_BAG_ITEMS || !order)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	//活动是否开启了
	unsigned begin_ts_activity = Config::GetIntValue(CONFIG_COUNTRY_BAG_BEGIN_TS);
	unsigned end_ts_activity = Config::GetIntValue(CONFIG_COUNTRY_BAG_END_TS);
	unsigned now_ts = Time::GetGlobalTime();
	if (now_ts < begin_ts_activity || now_ts > end_ts_activity)
	{
		LOGIC_ERROR_RETURN_MSG("activity_no_open");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//当日充值cash是否够了
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	XMLCountryDayBagItem bag_item;
	ret = dataXML->GetCountryDayBagItem(order-1, bag_item);
	if (ret)
	{
		error_log("GetCountryDayBagItem failed, uid=%u, order=%u", uid, order);
		return ret;
	}
	if (chargeTotal < bag_item.daily_pay_)
	{
		LOGIC_ERROR_RETURN_MSG("charge is less");
	}

	//对newAct进行初始化
	Json::Value newAct;
	CLogicSecinc logicSecinc;  //{"a":[ts,ts,ts], "id":1}
	ret = logicSecinc.GetSecinc(uid, NAT_GUOQING_FUDAI, newAct);
	if (R_ERR_NO_DATA == ret)
	{
		newAct["id"] = NAT_GUOQING_FUDAI;
		for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_BAG_ITEMS; ++ix)
		{
			newAct["a"][ix] = 0;
		}
	} else if (R_SUCCESS != ret)
	{
		DATA_ERROR_RETURN_MSG("country_day_bag_get_secinc");
	}

	//今天是否领取过了， 一天只能领取一次
	if (Time::IsToday(newAct["a"][order-1].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("one_day_only_one");
	}

	//然后给玩家 发物品 ， 把添加的物品返回给前端
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, bag_item.eqid_, bag_item.eq_cnt_, "country_day_bag_" + CTrans::UTOS(bag_item.id_), result["equip"], true);
	if (ret)
	{
		error_log("CountryDayBag_AddOneItem failed, uid=%u, id=%u, ret=%d", uid, bag_item.id_, ret);
		return ret;
	}

	//然后更改 newAct,  并且将newAct返回给前端    newAct {"a":[ts,ts,ts], "id":1}
	newAct["a"][order-1] = now_ts;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		error_log("GetCountryDayBagItem SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = newAct;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::ResetCountryDayShop(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启了
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned begin_ts_activity = 0;
	unsigned end_ts_activity = 0;
	int ret = 0;
	ret = dataXML->GetCountryDayShopOpenTime(begin_ts_activity, end_ts_activity);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetXML_activity_time_fail");
	}
	unsigned now_ts = Time::GetGlobalTime();
	if (now_ts < begin_ts_activity || now_ts > end_ts_activity)
	{
		DATA_ERROR_RETURN_MSG("activity_no_open");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newActOne;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_GUOQING_SHOP_ONE, newActOne);
	if (R_ERR_NO_DATA == ret)
	{
		newActOne["id"] = NAT_GUOQING_SHOP_ONE;
		for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_SHOP_DB_CNT; ++ix)  //7代表数据表里最大存放的个数
		{
			newActOne["a"][ix][0u] = 0;
			newActOne["a"][ix][1u] = 0;
		}
	} else if (R_SUCCESS != ret)
	{
		DATA_ERROR_RETURN_MSG("guoqing_shop_get_secinc");
	}

	for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_SHOP_DB_CNT; ++ix)
	{
		if (!Time::IsToday(newActOne["a"][ix][1u].asUInt()))
		{
			newActOne["a"][ix][0u] = 0;
			newActOne["a"][ix][1u] = now_ts;
		}
	}

	ret = logicSecinc.SetOneSecinc(uid, newActOne);
	if (ret)
	{
		error_log("ResetCountryDayShop SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][0u] = newActOne;


	//NAT_GUOQING_SHOP_TWO
	Json::Value newActTwo;
	ret = logicSecinc.GetSecinc(uid, NAT_GUOQING_SHOP_TWO, newActTwo);
	if (R_ERR_NO_DATA == ret)
	{
		newActTwo["id"] = NAT_GUOQING_SHOP_TWO;
		for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_SHOP_DB_CNT; ++ix)  //7代表数据表里最大存放的个数
		{
			newActTwo["a"][ix][0u] = 0;
			newActTwo["a"][ix][1u] = 0;
		}
	} else if (R_SUCCESS != ret)
	{
		DATA_ERROR_RETURN_MSG("guoqing_shop_get_secinc");
	}

	for(unsigned ix = 0; ix != MAX_COUNTRY_DAY_SHOP_DB_CNT; ++ix)
	{
		if (!Time::IsToday(newActTwo["a"][ix][1u].asUInt()))
		{
			newActTwo["a"][ix][0u] = 0;
			newActTwo["a"][ix][1u] = now_ts;
		}
	}

	ret = logicSecinc.SetOneSecinc(uid, newActTwo);
	if (ret)
	{
		error_log("ResetCountryDayShop SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;
	result["newAct"][1u] = newActTwo;

	return R_SUCCESS;
}


int CLogicCMD::HeartbeatBigSaleReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//1.活动是否开启
	unsigned now = Time::GetGlobalTime();
	unsigned start_time = Config::GetIntValue(CONFIG_TEMAI_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_TEMAI_END_TS);
	if(now < start_time || now > end_time)
	{
		error_log("temai_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//2.没有数据
	bool can_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_TEMAI, SecincData);  //{"a":[3,0,0,0],"id":22,"ts":1476354025,"v":20161009}   ts是活动重置的时间
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;

	} else if (ret)
	{
		return ret;
	}

	if (!can_reset)  //当有数据的时候
	{
		//3.版本
		if(SecincData["v"].asInt() != Config::GetIntValue(CONFIG_TEMAI_VER))
		{
			can_reset = true;
		}

		//4.每日进行重置
		if (!Time::IsToday(SecincData["ts"].asUInt()))
		{
			can_reset = true;
		}
	}

	if (!can_reset)
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}
	SecincData["id"] = NAT_TEMAI;
	for(unsigned ix = 0; ix != HEART_BEAT_BIG_SALE_ITEM_NUM; ++ix)
	{
		SecincData["a"][ix] = 0;
	}
	SecincData["ts"] = now;
	SecincData["v"] = Config::GetIntValue(CONFIG_TEMAI_VER);
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("ResetHeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::HeartbeatBigSale(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//1.参数是否合法
	if (order > HEART_BEAT_BIG_SALE_ITEM_NUM || !order || !count)
	{
		error_log("param error: order or count out of range");
		return R_ERR_PARAM;
	}

	//2.活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_TEMAI_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_TEMAI_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("temai_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//3.没有数据
	bool can_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_TEMAI, SecincData);   //{"a":[3,0,0,0],"id":22,"ts":1476354025,"v":20161009}
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (ret)
	{
		return ret;
	}

	if (!can_reset)  //当有数据的时候
	{
		//4.版本
		if(SecincData["v"].asInt() != Config::GetIntValue(CONFIG_TEMAI_VER))
		{
			can_reset = true;
		}

		//5. 每日重置
		if (!Time::IsToday(SecincData["ts"].asUInt()))
		{
			can_reset = true;
		}
	}

	if (can_reset)
	{
		SecincData["id"] = NAT_TEMAI;
		for(unsigned ix = 0; ix != HEART_BEAT_BIG_SALE_ITEM_NUM; ++ix)
		{
			SecincData["a"][ix] = 0;
		}
		SecincData["ts"] = now;
		SecincData["v"] = Config::GetIntValue(CONFIG_TEMAI_VER);
	}

	//6.每日购买次数限制
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	XMLHeartbeatBigSaleItem xmlsale;
	unsigned sid = Config::GetZoneByUID(uid);
	ret = dataXML->GetHeartbeatBigSaleItem(sid, order-1, xmlsale);
	if (ret || !xmlsale.id_)
	{
		DB_ERROR_RETURN_MSG("GetHeartbeatBigSaleItemfail");
	}

	unsigned max_count = xmlsale.limit_;
	if ((SecincData["a"][order-1].asUInt() + count) > max_count)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//7.扣钱
	Json::FastWriter writer;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "xdtm_"+ CTrans::UTOS(xmlsale.id_);
	unsigned real_cash_need = count * xmlsale.cash_;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, -real_cash_need, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//8.发道具
	CLogicEquipment logicEquipment;
	unsigned real_count = count * xmlsale.reward_.cnt_;
	ret = logicEquipment.AddOneItem(uid, xmlsale.reward_.eqid_, real_count, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("HeartbeatBigSale  AddOneItem failed, uid=%u, id=%u, ret=%d", uid, xmlsale.id_, ret);
		return ret;
	}

	//9.更改newAct
	SecincData["a"][order-1] = SecincData["a"][order-1].asUInt() + count;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("HeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FiveBigSaleShop(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_WUXING_SHOP_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_WUXING_SHOP_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("wuxing_shop_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (order > MAX_FIVE_SPECIAL_SHOP_ITEMS || !order || !count)
	{
		error_log("param error: order or count out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_WUXING_TEMAI_SHOP, SecincData);  //没有数据也报错    {"id":88,"c":[0,0,0,0,0,0,0]}
	if (ret)
	{
		error_log("FiveBigSaleShop_GetSecinc_error, uid=%u, ret=%d", uid, ret);
		return ret;
	}

	//检测count
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	XMLFiveSpecialShopItem  xmlspecial;
	ret = dataXML->GetFiveSpecialShopItem(order-1, xmlspecial);
	if (ret || !xmlspecial.id_)
	{
		error_log("FiveBigSaleShop_GetFiveSpecialShopItem_error, uid=%u, id=%u, ret=%d", uid, xmlspecial.id_, ret);
		return ret;
	}
	if ((SecincData["c"][order-1].asUInt() + count) > xmlspecial.limit_)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//7.扣钱
	Json::FastWriter writer;
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "wuxing_special_shop_"+ CTrans::UTOS(xmlspecial.id_);
	unsigned real_cash_need = count * xmlspecial.price_;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, -real_cash_need, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//8.发道具
	CLogicEquipment logicEquipment;
	unsigned real_count = count * xmlspecial.eq_cnt_;
	ret = logicEquipment.AddOneItem(uid, xmlspecial.eqid_, real_count, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("FiveBigSaleShop_AddOneItem_failed, uid=%u, eqid=%u, add=%u, ret=%d", uid, xmlspecial.eqid_, real_count, ret);
		return ret;
	}

	//9.更改newAct
	SecincData["c"][order-1] = SecincData["c"][order-1].asUInt() + count;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("FiveBigSaleShop_SetOneSecinc_failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FiveCouponShop(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_WUXING_SHOP_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_WUXING_SHOP_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("wuxing_shop_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (order > MAX_FIVE_DISCOUNT_SHOP_ITEMS || !order || !count)
	{
		error_log("param error: order or count out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincDataCouponShop;
	ret = Secinc.GetSecinc(uid, NAT_WUXING_COUPON_SHOP, SecincDataCouponShop); //没有数据也直接报错    {"id":88,"c":[0,0,0,0,0,0,0]}
	if (ret)
	{
		return ret;
	}
	Json::Value SecincDataCoupon;
	ret = Secinc.GetSecinc(uid, NAT_WUXING_COUPON, SecincDataCoupon);
	if (ret)
	{
		return ret;
	}

	//检测count和卷
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	XMLFiveDiscountShopItem  xmldiscountitem;
	ret = dataXML->GetFiveDiscountShopItem(order-1, xmldiscountitem);
	if (ret || !xmldiscountitem.id_)
	{
		DB_ERROR_RETURN_MSG("GetFiveDiscountShopItem fail");
	}

	unsigned max_count = xmldiscountitem.limit_;
	if ((SecincDataCouponShop["c"][order-1].asUInt() + count) > max_count)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//计算当日充值cash
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	map<unsigned, unsigned> charge_map;
	charge_map.clear();
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= start_time && ts <= end_time)
		{
			unsigned day_index = ceil((ts - start_time + 1)/86400);
			charge_map[day_index] += user_flag["chgs"][i][1u].asUInt();
		}
	}


	unsigned quan_pay = 0, quan_count = 0, quan_limit = 0;
	ret = dataXML->GetFiveShopQuan(quan_pay, quan_count, quan_limit);
	if (ret)
	{
		return ret;
	}
	unsigned total_quan = 0;
	for(map<unsigned, unsigned>::iterator iter = charge_map.begin(); iter != charge_map.end(); ++iter)
	{
		unsigned quan_one_day = floor((iter->second)/quan_pay) * quan_count;
		if (quan_one_day > quan_limit)
			quan_one_day = quan_limit;
		total_quan += quan_one_day;
	}
	unsigned remain_quan = total_quan - SecincDataCoupon["used"].asUInt();
	unsigned need_quan = xmldiscountitem.quan_ * count;
	if (remain_quan < need_quan)
	{
		LOGIC_ERROR_RETURN_MSG("remain quan is not enough");
	}

	//7.扣钱
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "wuxing_discount_shop_"+ CTrans::UTOS(xmldiscountitem.id_);
	unsigned real_cash_need = count * xmldiscountitem.price_;
	ret = logicPay.ProcessOrderForBackend(uid, -real_cash_need, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发道具
	CLogicEquipment logicEquipment;
	unsigned real_count = count * xmldiscountitem.eq_cnt_;
	ret = logicEquipment.AddOneItem(uid, xmldiscountitem.eqid_, real_count, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("HeartbeatBigSale  AddOneItem failed, uid=%u, id=%u, ret=%d", uid, xmldiscountitem.id_, ret);
		return ret;
	}

	//更改newAct
	SecincDataCouponShop["c"][order-1] = SecincDataCouponShop["c"][order-1].asUInt() + count;
	ret = Secinc.SetOneSecinc(uid, SecincDataCouponShop);
	if (ret)
	{
		error_log("HeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][0u] = SecincDataCouponShop;

	SecincDataCoupon["used"] = SecincDataCoupon["used"].asUInt() + need_quan;
	ret = Secinc.SetOneSecinc(uid, SecincDataCoupon);
	if (ret)
	{
		error_log("HeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][1u] = SecincDataCoupon;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FiveShopReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_WUXING_SHOP_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_WUXING_SHOP_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("wuxing_shop_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//没有数据时重置
	bool can_reset = false;
	bool reset_used_count = false;
	CLogicSecinc Secinc;
	Json::Value SecincDataCoupon;
	ret = Secinc.GetSecinc(uid, NAT_WUXING_COUPON, SecincDataCoupon);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
		reset_used_count = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (!can_reset)  //有数据时
	{
		//版本重置
		if(SecincDataCoupon["v"].asInt() != Config::GetIntValue(CONFIG_WUXING_SHOP_VER))
		{
			can_reset = true;
			reset_used_count = true;
		}

		//每日进行重置
		if (!Time::IsToday(SecincDataCoupon["ts"].asUInt()))
		{
			can_reset = true;     //3个表都要重置，但是used不能重置
		}
	}

	if (!can_reset)
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}

	//{"id":90,"used":99,"ts":1476354025,"v":20161009}
	SecincDataCoupon["id"] = NAT_WUXING_COUPON;
	if (reset_used_count)
	{
		SecincDataCoupon["used"] = 0;
	}
	SecincDataCoupon["ts"] = now;
	SecincDataCoupon["v"] = Config::GetIntValue(CONFIG_WUXING_SHOP_VER);
	ret = Secinc.SetOneSecinc(uid, SecincDataCoupon);
	if (ret)
	{
		error_log("ResetHeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][2u] = SecincDataCoupon;

	//{"id":88,"c":[0,0,0,0,0,0,0]}
	Json::Value SecincDataTemaiShop;
	SecincDataTemaiShop["id"] = NAT_WUXING_TEMAI_SHOP;
	for(unsigned ix = 0; ix != MAX_FIVE_SPECIAL_SHOP_ITEMS; ++ix)
	{
		SecincDataTemaiShop["c"][ix] = 0;
	}
	ret = Secinc.SetOneSecinc(uid, SecincDataTemaiShop);
	if (ret)
	{
		error_log("ResetHeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][0u] = SecincDataTemaiShop;

	//{"id":89,"c":[0,0,0,0,0,0,0]}
	Json::Value SecincDataCouponShop;
	SecincDataCouponShop["id"] = NAT_WUXING_COUPON_SHOP;
	for(unsigned ix = 0; ix != MAX_FIVE_DISCOUNT_SHOP_ITEMS; ++ix)
	{
		SecincDataCouponShop["c"][ix] = 0;
	}
	ret = Secinc.SetOneSecinc(uid, SecincDataCouponShop);
	if (ret)
	{
		error_log("ResetHeartbeatBigSale SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][1u] = SecincDataCouponShop;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::JinQiuShiYue(unsigned uid, unsigned index, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_JINQIUSHIYUE_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_JINQIUSHIYUE_END_TS))
		return R_ERR_LOGIC;

	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned need;
	pair<unsigned, unsigned> item;
	ret = pDataXML->GetJinqiushiyue(index, type, need, item);
	if(ret)
		return ret;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_JINQIUSHIYUE_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_JINQIUSHIYUE_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}
	if(chargeTotal < need)
		return R_ERR_LOGIC;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_JINQIUSHIYUE, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX; i++)
			array.append(0);
		newAct["id"] = NAT_JINQIUSHIYUE;
		newAct["a"] = array;
		newAct["ts"] = Time::GetGlobalTime();
	}
	else if(ret)
		return ret;
	if(!Time::IsToday(newAct["ts"].asUInt()))
	{
		for(unsigned i = 0; i < CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX; i++)
			newAct["a"][i] = 0;
		newAct["ts"] = Time::GetGlobalTime();
	}
	if(newAct["a"][index].asUInt() != 0)
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, item.first, item.second,"JinQiuShiYue",result["equip"], true);
	if(ret)
		return ret;

	newAct["a"][index] = 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return 0;
}
int CLogicCMD::ChongZhiHuiKui(unsigned uid, unsigned index, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_CHARGE_BINGSHU_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_CHARGE_BINGSHU_END_TS))
		return R_ERR_LOGIC;

	unsigned version = Config::GetIntValue(CONFIG_CHARGE_BINGSHU_VERSION);
	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned need;
	pair<unsigned, unsigned> item;
	ret = pDataXML->GetChongzhihuikui(index, type, need, item);
	if(ret)
		return ret;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}

	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	unsigned nowts = Time::GetGlobalTime();

	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();

		if(ts >= Config::GetIntValue(CONFIG_CHARGE_BINGSHU_BEGIN_TS) && ts <= nowts)
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}

	if(chargeTotal < need)
	{
		error_log("charge not enough. uid=%u,index=%u,charge=%u", uid, index, chargeTotal);
		LOGIC_ERROR_RETURN_MSG("charge_not_enough");
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_CHONGZHIHUIKUI, newAct);

	if (ret == R_ERR_NO_DATA)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX; i++)
			array.append(0);
		newAct["id"] = NAT_CHONGZHIHUIKUI;
		newAct["a"] = array;
		newAct["v"] = version;
		newAct["ts"] = Time::GetGlobalTime();

		logicSecinc.SetOneSecinc(uid, newAct);
	}
	else if(ret)
		return ret;

	//新增的字段，考虑旧的数据可能不存在该字段
	if (!newAct.isMember("v"))
	{
		newAct["v"] = 0;
	}

	//根据版本号进行重置
	if (newAct["v"].asUInt() != version)
	{
		//重置活动
		for(unsigned i = 0; i < CHONGZHIHUIKUI_JINQIUSHIYUE_INDEX; i++)
		{
			newAct["a"][i] = 0;
		}

		newAct["v"] = version;

		//先进行保存
		logicSecinc.SetOneSecinc(uid, newAct);
	}

	if(newAct["a"][index].asUInt() != 0)
	{
		error_log("reward already been gotten. uid=%u,index=%u", uid, index);
		LOGIC_ERROR_RETURN_MSG("rewardl_already_gotten");
	}

	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, item.first, item.second,"ChongZhiHuiKui",result["equip"], true);
	if(ret)
		return ret;

	newAct["a"][index] = 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return 0;
}

int CLogicCMD::ZhiZunBaoXiang(unsigned uid, unsigned type, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_END_TS))
		return R_ERR_LOGIC;

	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ZHIZUNBAOXIANG, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ZHIZUNBAOXIANG;
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["ver"] = Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_VERSION);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_VERSION) != newAct["ver"].asInt())
	{
		newAct["a"] = 0;
		newAct["b"] = 0;
		newAct["ver"] = Config::GetIntValue(CONFIG_ZHIZUNBAOXIANG_VERSION);
	}

	if(type)
	{
		unsigned t = newAct["b"].asUInt();
		if(t >= 6)
			return R_ERR_LOGIC;

		pair<unsigned, unsigned> item;
		ret = pDataXML->GetZhiZunBaoXiangB(t, item);
		if(ret)
			return ret;

		if(chargeTotal < item.first)
			return R_ERR_LOGIC;

		CLogicEquipment logicEquipment;
		ret = logicEquipment.AddOneItem(uid, item.second, 1, "ZhiZunBaoXiang",result["equip"], true);
		if(ret)
			return ret;

		newAct["b"] = t + 1;
	}
	else
	{
		unsigned t = newAct["a"].asUInt();
		if(t >= 20)
			return R_ERR_LOGIC;

		if(chargeTotal < (t+1)*500)
			return R_ERR_LOGIC;

		pair<unsigned, unsigned> item;
		ret = pDataXML->GetZhiZunBaoXiangK(item);
		if(ret)
			return ret;

		CLogicEquipment logicEquipment;
		ret = logicEquipment.AddOneItem(uid, item.first, item.second,"ZhiZunBaoXiang",result["equip"], true);
		if(ret)
			return ret;

		newAct["a"] = t + 1;
	}

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return 0;
}


int CLogicCMD::JueXingTeHui(unsigned uid, unsigned order, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_JUEXINGTEHUI_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_JUEXINGTEHUI_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JueXingTeHui_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (!order || !count)
	{
		error_log("param error: order or count out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_JUEXINGTEHUI, SecincData);
	if (ret)
		return ret;
	if(!SecincData.isMember("v") ||
		SecincData["v"].asInt() != Config::GetIntValue(CONFIG_JUEXINGTEHUI_VER))
	{
		LOGIC_ERROR_RETURN_MSG("cheat");
	}
	if (!Time::IsToday(SecincData["a"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("please close activity");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	//检查order是否合法
	unsigned xml_item_cnt = 0;
	ret = dataXML->GetJueXingTeHuiItemsCnt(xml_item_cnt);
	if (ret || !xml_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetJueXingTeHuiItemsCnt fail");
	}
	if (order > xml_item_cnt)
	{
		LOGIC_ERROR_RETURN_MSG("order is illegal");
	}

	XMLJueXingTeHuiItem  xml_juexingtehui_item;
	ret = dataXML->GetJueXingTeHuiItem(order-1, xml_juexingtehui_item);
	if (ret || !xml_juexingtehui_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetFiveDiscountShopItem fail");
	}

	//检查限购次数
	unsigned max_count = xml_juexingtehui_item.limit_;
	if ((SecincData["b"][order-1].asUInt() + count) > max_count)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//检查武将
	unsigned need_wujiang_cnt = 0;
	unsigned need_wujiang_jie = 0;
	need_wujiang_cnt = xml_juexingtehui_item.wj_cnt_;
	need_wujiang_jie = xml_juexingtehui_item.wj_jie_;
	map<unsigned, unsigned> all_hero;
	all_hero.clear();
	CLogicHero logicHero;
	Json::Value heroData;
	heroData.clear();
	ret = logicHero.GetHero(uid, heroData);
	for (int j=0; j<heroData.size(); ++j)
	{
		Json::Value & hero = heroData[j];
		if(hero.isMember("hs") && hero["hs"].isArray())  //"hs":[39,720,30,0]
		{
			unsigned level = 0, jie = 0;
			level =  hero["hs"][0u].asUInt();
			jie = floor(level/10) + 1;
			if (all_hero.count(jie))
			{
				all_hero[jie] = all_hero[jie] + 1;
			} else
			{
				all_hero[jie] = 1;
			}
		}
	}

	if (need_wujiang_jie && need_wujiang_cnt)
	{
		unsigned have_match_cnt = 0;
		for(map<unsigned, unsigned>::iterator iter = all_hero.begin(); iter != all_hero.end(); ++iter)
		{
			if (iter->first >= need_wujiang_jie)
			{
				have_match_cnt += (iter->second);
			}
		}
		if (have_match_cnt < need_wujiang_cnt)
		{
			error_log("wujiang jie fail, uid=%u, need=%u, have=%u", uid, need_wujiang_cnt, have_match_cnt);
			LOGIC_ERROR_RETURN_MSG("wujiang jie fail");
		}
	}

	//7.扣钱
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "juexingtehui_"+ CTrans::UTOS(xml_juexingtehui_item.id_);
	unsigned real_cash_need = count * xml_juexingtehui_item.price_;
	ret = logicPay.ProcessOrderForBackend(uid, -real_cash_need, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发道具
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, xml_juexingtehui_item.eqid_, count, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("juexingtehui AddOneItem failed, uid=%u, id=%u, ret=%d", uid, xml_juexingtehui_item.id_, ret);
		return ret;
	}

	//更改newAct
	SecincData["b"][order-1] = SecincData["b"][order-1].asUInt() + count;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("juexingtehui SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JueXingTeHuiReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_JUEXINGTEHUI_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_JUEXINGTEHUI_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JueXingTeHui_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//没有数据时重置
	bool can_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_JUEXINGTEHUI, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (!can_reset)  //有数据时
	{
		//版本重置
		if(!SecincData.isMember("v") ||
			SecincData["v"].asInt() != Config::GetIntValue(CONFIG_JUEXINGTEHUI_VER))
		{
			can_reset = true;
		}

		//每日进行重置
		if (!Time::IsToday(SecincData["a"].asUInt()))
		{
			can_reset = true;
		}
	}

	if (!can_reset)
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned xml_item_cnt = 0;
	ret = dataXML->GetJueXingTeHuiItemsCnt(xml_item_cnt);
	if (ret || !xml_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetJueXingTeHuiItemsCnt fail");
	}

	//{"a":1477656782,"b":[0,0,0,0,0,0,0,0,0,0,0,0],"id":52,"v":20161009}
	SecincData["a"] = now;
	if (SecincData.isMember("b") && SecincData["b"].isArray())
	{
		SecincData["b"].clear();
	}
	for(unsigned inx = 0; inx != xml_item_cnt; ++inx)
	{
		SecincData["b"][inx] = 0;
	}
	SecincData["id"] = NAT_JUEXINGTEHUI;
	SecincData["v"] = Config::GetIntValue(CONFIG_JUEXINGTEHUI_VER);
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("JueXingTeHuiReset SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FuDai(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_FUDAIHUODONG_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_FUDAIHUODONG_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("FuDai_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (!order || order > FUDAI_BAG_KINDS)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	bool reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_FUDAI, SecincData);
	if (ret == R_ERR_NO_DATA) //没有数据
	{
		reset = true;
	} else if (ret)
		return ret;

	if (!reset) //有数据
	{
		if (!SecincData.isMember("v") || !SecincData.isMember("id") || !SecincData.isMember("usetime")||
			!SecincData["usetime"].isArray() || SecincData["usetime"].size() != FUDAI_BAG_KINDS)
		{
			DATA_ERROR_RETURN_MSG("fudai_SecincData");
		}
	}
	if (SecincData["v"].asUInt() != Config::GetIntValue(CONFIG_FUDAIHUODONG_VER))
		reset = true;
	if (reset)
	{
		SecincData["id"] = NAT_FUDAI;
		SecincData["v"] = Config::GetIntValue(CONFIG_FUDAIHUODONG_VER);
		for(unsigned inx = 0; inx != FUDAI_BAG_KINDS; ++inx)
		{
			SecincData["usetime"][inx] = 0;
		}
	}

	//看是否已经领取过了
	if (SecincData["usetime"][order-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("have get already");
	}

	//检查当天充值的钱是否够了
	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(Time::IsToday(ts))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}
	if (chargeTotal < FUDAI_COST[order-1])
	{
		LOGIC_ERROR_RETURN_MSG("accharge is not enough");
	}

	//发道具
	CLogicEquipment logicEquipment;
	unsigned add_eqid = FUDAI_EQIP[order-1];
	unsigned add_cnt = 1;
	string log_reason = "fudaihuodong_"+ CTrans::UTOS(add_eqid) + ":" + CTrans::UTOS(add_cnt);
	ret = logicEquipment.AddOneItem(uid, add_eqid, add_cnt, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("FuDai AddOneItem failed, uid=%u, id=%u, ret=%d", uid, add_eqid, ret);
		return ret;
	}

	//更改newAct
	SecincData["usetime"][order-1] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("FuDai SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}



int CLogicCMD::FreeExchange(unsigned uid, unsigned order, unsigned ud_left, unsigned ud_right, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	bool use_qihun = false;
	if (!ud_left && !ud_right)
	{
		PARAM_ERROR_RETURN_MSG("param error: must be one ud above zero");
	} else if (!ud_left || !ud_right)
	{
		use_qihun = true;
	}

	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_LIMIT_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_LIMIT_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("FreeExchange_activity_time_error");
		return R_ERR_AUTH;
	}

	//检查order是否合法
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned xml_item_cnt = 0;
	int ret = 0;
	ret = dataXML->GetFreeExchangeItemsCnt(xml_item_cnt);
	if (ret || !xml_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetFreeExchangeItemsCnt fail");
	}
	if (!order || order > xml_item_cnt)
	{
		LOGIC_ERROR_RETURN_MSG("order is illegal");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_FREEEXCHANGE, SecincData);
	if (ret)
		return ret;

	if (!SecincData.isMember("id") || !SecincData.isMember("ts") || !SecincData.isMember("v") ||
		!SecincData.isMember("uestimes") || !SecincData["uestimes"].isArray() || SecincData["uestimes"].size() != xml_item_cnt)
	{
		DATA_ERROR_RETURN_MSG("FreeExchange_SecincData");
	}

	if(SecincData["v"].asInt() != Config::GetIntValue(CONFIG_LIMIT_VER))
	{
		LOGIC_ERROR_RETURN_MSG("cheat");
	}
	if (!Time::IsToday(SecincData["ts"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("please close activity");
	}

	XMLFreeExchangeItem  xml_freeexchange_item;
	ret = dataXML->GetFreeExchangeItem(order-1, xml_freeexchange_item);
	if (ret || !xml_freeexchange_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetFreeExchangeItem fail");
	}

	//检查限购次数
	unsigned max_count = xml_freeexchange_item.limit_;
	if (SecincData["uestimes"][order-1].asUInt() >= max_count)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//扣道具
	CLogicEquipment equipment;
	string log_reason = "freeexchange_"+ CTrans::UTOS(xml_freeexchange_item.id_);
	if (ud_left && (xml_freeexchange_item.eqid1_ > 1))
	{
		int ret = equipment.UseEquipment(uid, xml_freeexchange_item.eqid1_, ud_left, xml_freeexchange_item.need1_, log_reason);
		if (ret)
		{
			LOGIC_ERROR_RETURN_MSG("eqid1 is not enough");
		}

	}
	if (ud_right && (xml_freeexchange_item.eqid2_ > 1))
	{
		int ret = equipment.UseEquipment(uid, xml_freeexchange_item.eqid2_, ud_right, xml_freeexchange_item.need2_, log_reason);
		if (ret)
		{
			LOGIC_ERROR_RETURN_MSG("eqid2 is not enough");
		}

	}
	if (use_qihun) //扣除器魂
	{
		Json::Value tech;
		Json::Reader reader;
		Json::FastWriter writer;
		reader.parse(dataUser.user_tech, tech);
		if (!tech.isMember("godE") || !tech["godE"].isMember("qlE") || tech["godE"]["qlE"][0u].asUInt() < xml_freeexchange_item.need1_)
		{
			LOGIC_ERROR_RETURN_MSG("qihun is not enough");
		}
		tech["godE"]["qlE"][0u] = tech["godE"]["qlE"][0u].asUInt() - xml_freeexchange_item.need1_;
		dataUser.user_tech = writer.write(tech);
		result["qh"] = tech["godE"]["qlE"][0u].asUInt();
	}

	//发道具
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, xml_freeexchange_item.reward_.eqid_, xml_freeexchange_item.reward_.cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		error_log("freeexchange AddOneItem failed, uid=%u, id=%u, ret=%d", uid, xml_freeexchange_item.id_, ret);
		return ret;
	}

	//更改newAct
	SecincData["uestimes"][order-1] = SecincData["uestimes"][order-1].asUInt() + 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("freeexchange SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(use_qihun)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::FreeExchangeReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_LIMIT_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_LIMIT_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("FreeExchange_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//没有数据时重置
	bool can_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_FREEEXCHANGE, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (!can_reset)  //有数据时
	{
		//版本重置
		if(!SecincData.isMember("v") ||
			SecincData["v"].asInt() != Config::GetIntValue(CONFIG_LIMIT_VER))
		{
			can_reset = true;
		}

		//每日进行重置
		if (!Time::IsToday(SecincData["ts"].asUInt()))
		{
			can_reset = true;
		}
	}

	if (!can_reset)
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned xml_item_cnt = 0;
	ret = dataXML->GetJueXingTeHuiItemsCnt(xml_item_cnt);
	if (ret || !xml_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetJueXingTeHuiItemsCnt fail");
	}

	//{"ts":1477656782,"uestimes":[0,0,0,0,0,0,0,0,0,0,0,0],"id":52,"v":20161009}
	SecincData["ts"] = now;
	if (SecincData.isMember("uestimes") && SecincData["uestimes"].isArray())
	{
		SecincData["uestimes"].clear();
	}
	for(unsigned inx = 0; inx != xml_item_cnt; ++inx)
	{
		SecincData["uestimes"][inx] = 0;
	}
	SecincData["id"] = NAT_FREEEXCHANGE;
	SecincData["v"] = Config::GetIntValue(CONFIG_LIMIT_VER);
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("FreeExchangeReset SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::JiFenDuiHuan(unsigned uid, unsigned id, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(id == 0 || id > CONFIG_ACTIVITY_GALLERY_ITEM)
		return R_ERR_PARAM;
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS))
		return R_ERR_LOGIC;

	Json::Reader reader;
	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	map<string, string> config;
	ret = pDataXML->GetActivityConfig("jifenduihuan", config);
	if(ret)
		return ret;
	string sid = CTrans::ITOS(id);
	if(!config.count(sid))
		return R_ERR_PARAM;
	Json::Value reward;
	if(!reader.parse(config[sid], reward) || !reward.isMember("price") || !reward.isMember("times") || !reward.isMember("reward")
	|| !reward["reward"].isMember("equip") || !reward["reward"]["equip"].isMember("id") || !reward["reward"]["equip"].isMember("c"))
		return R_ERR_DATA;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_JIFEN_DUIHUAN, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CONFIG_ACTIVITY_GALLERY_ITEM; i++)
			array.append(0);
		newAct["id"] = NAT_JIFEN_DUIHUAN;
		newAct["a"] = array;
		newAct["b"] = 0;
		newAct["c"] = Time::GetGlobalTime();
		newAct["v"] = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_VER) != newAct["v"].asInt())
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < CONFIG_ACTIVITY_GALLERY_ITEM; i++)
			array.append(0);
		newAct["a"] = array;
		newAct["b"] = 0;
		newAct["c"] = Time::GetGlobalTime();
		newAct["v"] = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_VER);
	}
	if(!Time::IsToday(newAct["c"].asUInt()))
	{
		for(unsigned i = 0; i < CONFIG_ACTIVITY_GALLERY_ITEM; i++)
			newAct["a"][i] = 0;
		newAct["c"] = Time::GetGlobalTime();
	}

	if(newAct["a"][id-1].asUInt() >= reward["times"].asUInt()
	|| chargeTotal < newAct["b"].asUInt() + reward["price"].asUInt())
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	if(reward.isMember("ats") && reward["ats"].asUInt())
		ret = logicEquipment.AddOneItem(uid, reward["reward"]["equip"]["id"].asUInt(), reward["reward"]["equip"]["c"].asUInt(),"jifenduihuan",result["equip"], true, 0, 0, Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS)-Time::GetGlobalTime());
	else
		ret = logicEquipment.AddOneItem(uid, reward["reward"]["equip"]["id"].asUInt(), reward["reward"]["equip"]["c"].asUInt(),"jifenduihuan",result["equip"], true);
	if(ret)
		return ret;

	newAct["a"][id-1] = newAct["a"][id-1].asUInt() + 1;
	newAct["b"] = newAct["b"].asUInt() + reward["price"].asUInt();
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return 0;
}


int CLogicCMD::DoubleEleven(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_DOUBLEELEVEN_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_DOUBLEELEVEN_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("DoubleEleven_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (!big_order || !small_order || small_order > DOUBLE_ELEVEN_SMALL_ITEMS_CNT)
	{
		error_log("param error: big_order or small_order out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_DOUBLEELEVEN, SecincData);
	if (ret)
		return ret;
	if(!SecincData.isMember("v") ||
		SecincData["v"].asInt() != Config::GetIntValue(CONFIG_DOUBLEELEVEN_VER))
	{
		LOGIC_ERROR_RETURN_MSG("cheat");
	}
	if (!Time::IsToday(SecincData["ts"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("please close activity");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	//检查big_order是否合法
	unsigned xml_big_item_cnt = 0;
	ret = dataXML->GetDoubleElevenBigItemsCnt(xml_big_item_cnt);
	if (ret || !xml_big_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetDoubleElevenBigItemsCnt fail");
	}
	if (big_order > xml_big_item_cnt)
	{
		LOGIC_ERROR_RETURN_MSG("big_order is illegal");
	}

	XMLDoubleElevenBigItem  xml_doubleeleven_big_item;
	ret = dataXML->GetDoubleElevenBigItem(big_order-1, xml_doubleeleven_big_item);
	if (ret || !xml_doubleeleven_big_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetDoubleElevenBigItem fail");
	}

	//检查限购次数
	unsigned max_count = xml_doubleeleven_big_item.limitbuy_;
	if ((SecincData["usetimes"][big_order-1].asUInt()) >= max_count)
	{
		LOGIC_ERROR_RETURN_MSG("have buy maximum");
	}

	//看充值的钻石是否够了
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}

	unsigned accharge_limit = xml_doubleeleven_big_item.recharge_;
	if (chargeTotal < accharge_limit) //充值的钱数 是否和 big_table的权限是否一致
	{
		LOGIC_ERROR_RETURN_MSG("accharge cash less");
	}

	//7.扣钱
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	string log_reason = "doubleeleven_"+ CTrans::UTOS(xml_doubleeleven_big_item.id_) + "_" + CTrans::UTOS(xml_doubleeleven_big_item.small_items_[small_order-1].id_);
	unsigned real_cash_need = xml_doubleeleven_big_item.small_items_[small_order-1].cash_;
	ret = logicPay.ProcessOrderForBackend(uid, -real_cash_need, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		Json::FastWriter writer;
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发奖励的道具
	CLogicEquipment logicEquipment;
	vector<ItemAdd> items;
	ItemAdd award_equip;
	award_equip.eqid = xml_doubleeleven_big_item.rewardid_;
	award_equip.count = xml_doubleeleven_big_item.rewardcnt_;
	award_equip.reason = log_reason;
	items.push_back(award_equip);

	//发买的道具
	ItemAdd buy_equip;
	buy_equip.eqid = xml_doubleeleven_big_item.small_items_[small_order-1].eqid_;
	buy_equip.count = xml_doubleeleven_big_item.small_items_[small_order-1].cnt_;
	buy_equip.reason = log_reason;
	items.push_back(buy_equip);

	if(items.size())
	{
		ret = logicEquipment.AddItems(uid, items, result["equip"], true);
		if(ret)
		{
			error_log("doubleeleven AddOneItem failed, uid=%u, big_id=%u, small_id=%u, ret=%d", uid, xml_doubleeleven_big_item.id_, xml_doubleeleven_big_item.small_items_[small_order-1].id_, ret);
			return ret;
		}
	}

	//更改newAct
	SecincData["usetimes"][big_order-1] = SecincData["usetimes"][big_order-1].asUInt() + 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("doubleeleven SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::DoubleElevenReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_DOUBLEELEVEN_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_DOUBLEELEVEN_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("DoubleEleven_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//没有数据时重置
	bool can_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_DOUBLEELEVEN, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (!can_reset)  //有数据时
	{
		//版本重置
		if(!SecincData.isMember("v") ||
			SecincData["v"].asInt() != Config::GetIntValue(CONFIG_DOUBLEELEVEN_VER))
		{
			can_reset = true;
		}

		//每日进行重置
		if (!Time::IsToday(SecincData["ts"].asUInt()))
		{
			can_reset = true;
		}
	}

	if (!can_reset)
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	unsigned xml_big_item_cnt = 0;
	ret = dataXML->GetDoubleElevenBigItemsCnt(xml_big_item_cnt);
	if (ret || !xml_big_item_cnt)
	{
		DB_ERROR_RETURN_MSG("GetDoubleElevenBigItemsCnt fail");
	}

	//{"usetimes":[0,0,0,0,0],"ts":1478069860,"v":0, "id":44}
	SecincData["ts"] = now;
	if (SecincData.isMember("usetimes") && SecincData["usetimes"].isArray())
	{
		SecincData["usetimes"].clear();
	}
	for(unsigned inx = 0; inx != xml_big_item_cnt; ++inx)
	{
		SecincData["usetimes"][inx] = 0;
	}
	SecincData["id"] = NAT_DOUBLEELEVEN;
	SecincData["v"] = Config::GetIntValue(CONFIG_DOUBLEELEVEN_VER);
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("DoubleElevenReset SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaDailyGetLantian(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_2, SecincData);
	if (ret)
		return ret;

	//{"b":[1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],"d":20161107,"e":1478485823,"id":2}
	if(!SecincData.isMember("b") ||
	   !SecincData.isMember("e") ||
	   !SecincData.isMember("id")||
	   !SecincData.isMember("d") || SecincData["d"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_VER))
	{
		LOGIC_ERROR_RETURN_MSG("cheat");
	}

	if (!Time::IsToday(SecincData["e"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("please close activity");
	}

	//是否已经领取过了
	if (SecincData["b"][0u].asInt() >= 1)
	{
		LOGIC_ERROR_RETURN_MSG("one day only once");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLJuBaoXiaDailyFreeItem  xml_free_item;
	ret = dataXML->GetJuBaoXiaDailyFreeItem(xml_free_item);
	if (ret || !xml_free_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetJubBaoXiaDailyFreeItem fail");
	}

	//发道具
	string log_reason = "jubaoxiadailyfree";
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, xml_free_item.id_, xml_free_item.cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	//更改newAct
	SecincData["b"][0u] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("jubaoxia SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaExchange(unsigned uid, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLJuBaoXiaExchangeItem  xml_exchange_item;
	ret = dataXML->GetJuBaoXiaExchangeItem(xml_exchange_item);
	if (ret || !xml_exchange_item.need_id_)
	{
		DB_ERROR_RETURN_MSG("GetJubBaoXiaExchangeItem fail");
	}

	//扣道具
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, xml_exchange_item.need_id_, ud, xml_exchange_item.need_cnt_, "jubaoxiaexchange");
	if(ret)
	{
		error_log("jubaoxia uid=%u | id=%u", uid , xml_exchange_item.need_id_);
		return R_ERR_DATA;
	}

	//扣钱
	CLogicPay logicPay;
	DataPay payData;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	bool bsave = false;
	ret = logicPay.ProcessOrderForBackend(uid, -xml_exchange_item.need_cash_, 0, payData, "jubaoxiaexchange", user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		Json::FastWriter writer;
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发道具
	string log_reason = "jubaoxiaexchange";
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, xml_exchange_item.get_id_, xml_exchange_item.get_cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaGetKey(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (order < 3 || order > JUBAOXIA_GET_KEY_CHANNEL_KINDS)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_2, SecincData);
	if (ret)
		return ret;

	//{"b":[1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],"d":20161107,"e":1478485823,"id":2}
	if(!SecincData.isMember("b") ||
	   !SecincData.isMember("e") ||
	   !SecincData.isMember("id")||
	   !SecincData.isMember("d") || SecincData["d"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_VER))
	{
		LOGIC_ERROR_RETURN_MSG("cheat");
	}

	if (SecincData["b"][order-2].asInt() >= 1)
	{
		LOGIC_ERROR_RETURN_MSG("only once");
	}

	if (!Time::IsToday(SecincData["e"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("please close activity");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLJuBaoXiaKeyItem  xml_key_item;
	ret = dataXML->GetJuBaoXiaKeyItem(order-3, xml_key_item);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetJubBaoXiaKeyItem fail");
	}

	//充值钻石是否够了
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(Time::IsToday(ts))
		{
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
		}
	}
	if (chargeTotal < xml_key_item.need_charge_)
	{
		LOGIC_ERROR_RETURN_MSG("accharge cash less");
	}

	//发道具
	string log_reason = "jubaoxiakey_"+ CTrans::UTOS(order);
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, xml_key_item.get_id_, xml_key_item.get_cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	//更改newAct
	SecincData["b"][order-2] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("jubaoxia SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaGetTreasure(unsigned uid, unsigned order, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	//参数检测
	if (!order  || order > JUBAOXIA_TREASURE_CNT)
	{
		error_log("param error: order out of range");
		return R_ERR_PARAM;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;


	//首先获取已开宝箱的信息
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_1, SecincData);
	if (ret)
		return ret;

	if (SecincData["a"][order-1].asInt() != -1)
	{
		LOGIC_ERROR_RETURN_MSG("the bag have open");
	}

	//如果只剩最后一个, 特殊处理
	unsigned left_close_treasure = 0;
	for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
	{
		if (SecincData["a"][inx].asInt() == -1)
		{
			++left_close_treasure;
		}
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	map<unsigned, unsigned> rate_all;
	rate_all.clear();
	if (left_close_treasure == 1)
	{
		unsigned temp_circle = SecincData["c"].asUInt() + 1;
		if (temp_circle > 4)
		{
			temp_circle = 4;
		}
		ret = dataXML->GetJuBaoXiaPreciousRate(temp_circle, rate_all);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaPreciousRate fail");
		}
	} else if (left_close_treasure > 1)
	{
		ret = dataXML->GetJuBaoXiaCommonRate(rate_all);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaCommonRate fail");
		}

	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	map<unsigned, unsigned> new_rate;
	new_rate.clear();
	unsigned total_sum_rate = 0;
	if (left_close_treasure == 1)
	{
		for(map<unsigned, unsigned>::iterator iter = rate_all.begin(); iter != rate_all.end(); ++iter)
		{
			total_sum_rate += iter->second;
			if (total_sum_rate && (!new_rate.count(total_sum_rate)))
			{
				new_rate[total_sum_rate] = iter->first;
			}
		}

	} else if (left_close_treasure > 1)
	{
		for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
		{
			if (SecincData["a"][inx].asInt() != -1)
			{
				rate_all.erase(SecincData["a"][inx].asInt());
			}
		}
		for(map<unsigned, unsigned>::iterator iter = rate_all.begin(); iter != rate_all.end(); ++iter)
		{
			total_sum_rate += iter->second;
			if (total_sum_rate && (!new_rate.count(total_sum_rate)))
			{
				new_rate[total_sum_rate] = iter->first;
			}
		}
	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	int rand = Math::GetRandomInt(total_sum_rate);
	int find_index = 0;
	for(map<unsigned, unsigned>::iterator iter = new_rate.begin(); iter != new_rate.end(); ++iter)
	{
		if (rand <= iter->first)
		{
			find_index = iter->second;
			break;
		}
	}

	//扣除和氏璧
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, 50064, ud, 1, "jubaoxiaopenbox");
	if(ret)
	{
		error_log("jubaoxiaopenbox uid=%u", uid);
		return R_ERR_DATA;
	}

	//然后获取相应的item
	if (left_close_treasure == 1)
	{
		XMLJuBaoXiaTreasurePreciousItem precious_item;
		ret = dataXML->GetJuBaoXiaPreciousItem(find_index, precious_item);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaPreciousItem fail");
		}

		//发物品  (注意东西有hero)
		string log_reason =  "jubaoxia_precious_"+ CTrans::UTOS(find_index);
		if (precious_item.is_hero_)
		{
			CLogicHero logicHero;
			ret = logicHero.AddOneHero(uid, "H" + CTrans::UTOS(precious_item.id_), log_reason, result["hero"]);
			if (ret)
			{
				return ret;
			}
		} else
		{
			CLogicEquipment logicEquip;
			ret = logicEquip.AddOneItem(uid, precious_item.id_, precious_item.amount_, log_reason, result["equip"], true);
			if (ret)
			{
				return ret;
			}
		}

		//要重置secinc, 然后增加轮数
		for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
		{
			SecincData["a"][inx] = -1;
		}
		SecincData["c"] = SecincData["c"].asUInt() + 1;
	} else if (left_close_treasure > 1)
	{
		XMLJuBaoXiaTreasureCommonItem common_item;
		ret = dataXML->GetJuBaoXiaCommonItem(find_index, common_item);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaCommonItem fail");
		}

		//然后发东西
		CLogicEquipment logicEquip;
		string log_reason =  "jubaoxia_common_"+ CTrans::UTOS(find_index);
		ret = logicEquip.AddOneItem(uid, common_item.id_, common_item.amount_, log_reason, result["equip"], true);
		if (ret)
		{
			return ret;
		}
		SecincData["a"][order-1] = find_index;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("jubaoxia SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;


	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaOneKey(unsigned uid, unsigned order, unsigned ud, Json::Value &SecincData, Json::Value &equip, Json::Value &hero,  CDataXML *dataXML)
{
//如果只剩最后一个, 特殊处理
	unsigned left_close_treasure = 0;
	for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
	{
		if (SecincData["a"][inx].asInt() == -1)
		{
			++left_close_treasure;
		}
	}
	int ret = 0;
	map<unsigned, unsigned> rate_all;
	rate_all.clear();
	if (left_close_treasure == 1)
	{
		unsigned temp_circle = SecincData["c"].asUInt() + 1;
		if (temp_circle > 4)
		{
			temp_circle = 4;
		}
		ret = dataXML->GetJuBaoXiaPreciousRate(temp_circle, rate_all);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaPreciousRate fail");
		}
	} else if (left_close_treasure > 1)
	{
		ret = dataXML->GetJuBaoXiaCommonRate(rate_all);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaCommonRate fail");
		}

	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	map<unsigned, unsigned> new_rate;
	new_rate.clear();
	unsigned total_sum_rate = 0;
	if (left_close_treasure == 1)
	{
		for(map<unsigned, unsigned>::iterator iter = rate_all.begin(); iter != rate_all.end(); ++iter)
		{
			total_sum_rate += iter->second;
			if (total_sum_rate && (!new_rate.count(total_sum_rate)))
			{
				new_rate[total_sum_rate] = iter->first;
			}
		}

	} else if (left_close_treasure > 1)
	{
		for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
		{
			if (SecincData["a"][inx].asInt() != -1)
			{
				rate_all.erase(SecincData["a"][inx].asInt());
			}
		}
		for(map<unsigned, unsigned>::iterator iter = rate_all.begin(); iter != rate_all.end(); ++iter)
		{
			total_sum_rate += iter->second;
			if (total_sum_rate && (!new_rate.count(total_sum_rate)))
			{
				new_rate[total_sum_rate] = iter->first;
			}
		}
	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	int rand = Math::GetRandomInt(total_sum_rate);
	int find_index = 0;
	for(map<unsigned, unsigned>::iterator iter = new_rate.begin(); iter != new_rate.end(); ++iter)
	{
		if (rand <= iter->first)
		{
			find_index = iter->second;
			break;
		}
	}

	//扣除和氏璧
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, 50064, ud, 1, "jubaoxiaopenbox");
	if(ret)
	{
		error_log("jubaoxiaopenbox uid=%u", uid);
		return R_ERR_DATA;
	}

	//然后获取相应的item
	if (left_close_treasure == 1)
	{
		XMLJuBaoXiaTreasurePreciousItem precious_item;
		ret = dataXML->GetJuBaoXiaPreciousItem(find_index, precious_item);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaPreciousItem fail");
		}

		//发物品  (注意东西有hero)
		string log_reason =  "jubaoxia_precious_"+ CTrans::UTOS(find_index);
		if (precious_item.is_hero_)
		{
			CLogicHero logicHero;
			ret = logicHero.AddOneHero(uid, "H" + CTrans::UTOS(precious_item.id_), log_reason, hero);
			if (ret)
			{
				return ret;
			}
		} else
		{
			CLogicEquipment logicEquip;
			ret = logicEquip.AddOneItem(uid, precious_item.id_, precious_item.amount_, log_reason, equip, true);
			if (ret)
			{
				return ret;
			}
		}

		//要重置secinc, 然后增加轮数
		for(unsigned inx = 0; inx != SecincData["a"].size(); ++inx)
		{
			SecincData["a"][inx] = -1;
		}
		SecincData["c"] = SecincData["c"].asUInt() + 1;
	} else if (left_close_treasure > 1)
	{
		XMLJuBaoXiaTreasureCommonItem common_item;
		ret = dataXML->GetJuBaoXiaCommonItem(find_index, common_item);
		if (ret)
		{
			DB_ERROR_RETURN_MSG("GetJubBaoXiaCommonItem fail");
		}

		//然后发东西
		CLogicEquipment logicEquip;
		string log_reason =  "jubaoxia_common_"+ CTrans::UTOS(find_index);
		ret = logicEquip.AddOneItem(uid, common_item.id_, common_item.amount_, log_reason, equip, true);
		if (ret)
		{
			return ret;
		}
		SecincData["a"][order-1] = find_index;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("close_treasure_is_wrong");
	}

	return R_SUCCESS;
}


int CLogicCMD::JuBaoXiaGetTreasureOneKey(unsigned uid, Json::Value orders, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//首先获取已开宝箱的信息
	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_1, SecincData);
	if (ret)
		return ret;
	for(int i = 0; i < orders.size(); ++i)
	{
		if(SecincData["a"][orders[i].asUInt()-1].asInt() != -1)
		{
			LOGIC_ERROR_RETURN_MSG("the bag have open");
		}
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}

	result["equip"].resize(orders.size());
	for(int i = 0; i < orders.size(); ++i)
	{
		ret = JuBaoXiaOneKey(uid, orders[i].asUInt(), ud, SecincData, result["equip"][i], result["hero"], dataXML);
		if(ret)
			return ret;
	}

	result["newAct"] = SecincData;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("jubaoxia SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::JuBaoXiaReset(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("JubBaoXia_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//没有数据时重置
	bool treasure_reset = false;
	bool key_reset = false;
	CLogicSecinc Secinc;
	Json::Value SecincTreasureData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_1, SecincTreasureData);
	if (ret == R_ERR_NO_DATA)
	{
		treasure_reset = true;
		key_reset = true;
	} else if (ret)
	{
		error_log("GetSecinc_1_error,uid = %u", uid);
		return ret;
	}

	Json::Value SecincKeyData;
	ret = Secinc.GetSecinc(uid, NAT_MOONCAKE_2, SecincKeyData);
	if (ret == R_ERR_NO_DATA)
	{
		treasure_reset = true;
		key_reset = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if ((!treasure_reset) && (!key_reset)) //都有数据时
	{
		//版本重置
		if(!SecincKeyData.isMember("d") ||
			SecincKeyData["d"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_VER))
		{
			treasure_reset = true;
			key_reset = true;
		}

		//每日重置
		if (!Time::IsToday(SecincKeyData["e"].asUInt()))
		{
			key_reset = true;
		}
	}

	if ((!treasure_reset) && (!key_reset))
	{
		LOGIC_ERROR_RETURN_MSG("reset_cond_wrong");
	}

	//{"a":[20,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],"c":1,"id":1}
	if (treasure_reset)
	{
		for(unsigned inx = 0; inx != JUBAOXIA_TREASURE_CNT; ++inx)
		{
			SecincTreasureData["a"][inx] = -1;
		}
		SecincTreasureData["c"] = 0;
		SecincTreasureData["id"] = NAT_MOONCAKE_1;
		ret = Secinc.SetOneSecinc(uid, SecincTreasureData);
		if (ret)
		{
			error_log("JubBaoXiaReset SetOneSecinc1 failed. uid=%u, ret=%d", uid, ret);
			return ret;
		}
	}

	//{"b":[1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],"d":20161107,"e":1478485823,"id":2}
	if (key_reset)
	{
		for(unsigned inx = 0; inx != (JUBAOXIA_KEY_CNT + 1); ++inx)  //还有一个因为可以一直兑换，所以就没在数组里存放
		{
			SecincKeyData["b"][inx] = -1;
		}
		SecincKeyData["d"] = Config::GetIntValue(CONFIG_ACTIVITY_MOONCAKE_VER);
		SecincKeyData["e"] = now;
		SecincKeyData["id"] = NAT_MOONCAKE_2;
		if (SecincKeyData.isMember("c"))
		{
			SecincKeyData.removeMember("c");
		}
		ret = Secinc.SetOneSecinc(uid, SecincKeyData);
		if (ret)
		{
			error_log("JubBaoXiaReset SetOneSecinc2 failed. uid=%u, ret=%d", uid, ret);
			return ret;
		}
	}

	result["newAct"][0u] = SecincTreasureData;
	result["newAct"][1u] = SecincKeyData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if (ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::HeavenStep(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_BINGSHU_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_BINGSHU_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("HeavenStep_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	bool can_reset = false;
	ret = Secinc.GetSecinc(uid, NAT_LINSHI_BINGSHU, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (!ret)
	{
		//版本号
		if (SecincData["v"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_SNAP_BINGSHU_VER))
		{
			can_reset = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (can_reset)
	{
		SecincData["id"] = NAT_LINSHI_BINGSHU;
		SecincData["v"] = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_BINGSHU_VER);
		for(unsigned inx = 0; inx != HEAVENSTEP_JIE_NUM; ++inx)
		{
			SecincData["a"][inx] = 0;
		}
	}

	//对数据格式 严格检查
	if(!SecincData.isMember("id") ||
	   !SecincData.isMember("v")  ||
	   !SecincData.isMember("a")  || !SecincData["a"].isArray())
	{
		DATA_ERROR_RETURN_MSG("SecincData");
	}

	//校验size
	if(SecincData["a"].size() != HEAVENSTEP_JIE_NUM)
	for(int index = SecincData["a"].size(); index < HEAVENSTEP_JIE_NUM; index ++)
	{
		SecincData["a"][index] = 0;
	}

	//获取玩家兵书的 当前阶
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_tech;
	reader.parse(dataUser.user_tech,user_tech);
	unsigned curr_jie = 0;
	if(user_tech.isMember("heaven"))
	{
		if (!user_tech["heaven"]["lv"].asUInt())
		{
			user_tech["heaven"]["lv"] = 1;
		}
		curr_jie = floor((user_tech["heaven"]["lv"].asUInt() - 1) / 10) + 1;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("jie must above one");
	}

	//是否已经领取过了
	if (SecincData["a"][curr_jie-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("only can get once");
	}

	//发道具
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLHeavenStepRewardItem  reward;
	ret = dataXML->GetHeavenStepItem(curr_jie, reward);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetHeavenStepItem fail");
	}
	if (reward.jie_id_ != curr_jie)
	{
		DB_ERROR_RETURN_MSG("jie is not match");
	}

	vector<ItemAdd> items;
	for (int i = 0; i < HEAVENSTEP_REWARD_KINDS; ++i)
	{
		ItemAdd item;
		item.eqid = reward.eqid_[i];
		item.count = reward.cnt_[i];
		item.ats =  Config::GetIntValue(CONFIG_ACTIVITY_SNAP_BINGSHU_E_TS) - Time::GetGlobalTime();
		item.reason = "heavenstep_"+ CTrans::UTOS(curr_jie);
		items.push_back(item);
	}
	CLogicEquipment logicEquip;
	ret = logicEquip.AddItems(uid, items, result["equipment"], true);
	if (ret)
	{
        error_log("heaven step add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	//更改newAct
	SecincData["a"][curr_jie-1] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("heaven step SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::DaoistStep(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_DUNJIA_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_DUNJIA_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("DaoistStep_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	bool can_reset = false;
	ret = Secinc.GetSecinc(uid, NAT_LINSHI_DUNJIA, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (!ret)
	{
		//版本号
		if (SecincData["v"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_SNAP_DUNJIA_VER))
		{
			can_reset = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (can_reset)
	{
		SecincData["id"] = NAT_LINSHI_DUNJIA;
		SecincData["v"] = Config::GetIntValue(CONFIG_ACTIVITY_SNAP_DUNJIA_VER);
		for(unsigned inx = 0; inx != DAOISTSTEP_JIE_NUM; ++inx)
		{
			SecincData["a"][inx] = 0;
		}
	}

	//对数据格式 严格检查
	if(!SecincData.isMember("id") ||
	   !SecincData.isMember("v")  ||
	   !SecincData.isMember("a")  || !SecincData["a"].isArray())
	{
		DATA_ERROR_RETURN_MSG("SecincData");
	}

	//校验size
	if(SecincData["a"].size() != DAOISTSTEP_JIE_NUM)
	for(int index = SecincData["a"].size(); index < DAOISTSTEP_JIE_NUM; index ++)
	{
		SecincData["a"][index] = 0;
	}

	//获取玩家遁甲的 当前阶
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_tech;
	reader.parse(dataUser.user_tech,user_tech);
	unsigned curr_jie = 0;
	if(user_tech.isMember("daoist"))
	{
		if (!user_tech["daoist"]["lv"].asUInt())
		{
			user_tech["daoist"]["lv"] = 1;
		}
		curr_jie = floor((user_tech["daoist"]["lv"].asUInt() - 1) / 10) + 1;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("jie must above one");
	}

	//是否已经领取过了
	if (SecincData["a"][curr_jie-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("only can get once");
	}

	//发道具
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLDaoistStepRewardItem  reward;
	ret = dataXML->GetDaoistStepItem(curr_jie, reward);
	if (ret)
	{
		DB_ERROR_RETURN_MSG("GetDaoistStepItem fail");
	}
	if (reward.jie_id_ != curr_jie)
	{
		DB_ERROR_RETURN_MSG("jie is not match");
	}

	vector<ItemAdd> items;
	for (int i = 0; i < DAOISTSTEP_REWARD_KINDS; ++i)
	{
		ItemAdd item;
		item.eqid = reward.eqid_[i];
		item.count = reward.cnt_[i];
		item.ats =  Config::GetIntValue(CONFIG_ACTIVITY_SNAP_DUNJIA_E_TS) - Time::GetGlobalTime();
		item.reason = "daoiststep_"+ CTrans::UTOS(curr_jie);
		items.push_back(item);
	}
	CLogicEquipment logicEquip;
	ret = logicEquip.AddItems(uid, items, result["equipment"], true);
	if (ret)
	{
        error_log("daoist step add items failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	//更改newAct
	SecincData["a"][curr_jie-1] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("daoist step SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::ZhenBaoGeHero(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("zhenbaoge_activity_time_error");
		return R_ERR_AUTH;
	}

	//魂石活动
	string type_zhenbaoge = Config::GetValue(CONFIG_ACTIVITY_ZHENBAOGE_TYPE);
	if (type_zhenbaoge != "stone")
	{
		error_log("zhenbaoge_type_error, %s", type_zhenbaoge.c_str());
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//版本号, no data, 每天进行重置
	CLogicSecinc Secinc;
	Json::Value SecincData;
	bool can_reset = false;
	ret = Secinc.GetSecinc(uid, NAT_ZHENBAOGE, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (!ret)
	{
		//对数据格式 严格检查
		if(!SecincData.isMember("a") ||
		   !SecincData.isMember("b")  ||
		   !SecincData.isMember("id")  ||
		   !SecincData.isMember("c1")  || !SecincData["c1"].isArray() || SecincData["c1"].size() != ZHENBAOGEHERO_SMALL_NUM ||
		   !SecincData.isMember("c2")  || !SecincData["c2"].isArray() || SecincData["c2"].size() != ZHENBAOGEHERO_SMALL_NUM)
		{
			DATA_ERROR_RETURN_MSG("SecincData");
		}

		//版本号
		if (SecincData["a"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_VER))
		{
			can_reset = true;
		}

		//每日重置
		if (!Time::IsToday(SecincData["b"].asUInt()))
		{
			can_reset = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (can_reset)
	{
		SecincData["id"] = NAT_ZHENBAOGE;
		SecincData["a"] = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_VER);
		SecincData["b"] = now;
		for(unsigned inx = 0; inx != ZHENBAOGEHERO_SMALL_NUM; ++inx)
		{
			SecincData["c1"][inx] = 0;
			SecincData["c2"][inx] = 0;
		}
	}

	//读取newAct，比较配置， 看是否买到了上限
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLZhenBaoGeHeroItem  xml_item;
	ret = dataXML->GetZhenBaoGeHeroItem(big_order-1, small_order-1, xml_item);
	if (ret || !xml_item.eqid_)
	{
		DB_ERROR_RETURN_MSG("GetZhenBaoGeHeroItem fail");
	}

	if (((big_order == 1) && (SecincData["c1"][small_order-1].asInt() >= xml_item.limit_times_)) ||
		((big_order == 2) && (SecincData["c2"][small_order-1].asInt() >= xml_item.limit_times_)))
	{
		LOGIC_ERROR_RETURN_MSG("can not buy more");
	}

	//扣钱，添加物品，更改newAct
	CLogicPay logicPay;
	DataPay payData;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	bool bsave = false;
	string log_reason = "zhenbaogehero_"+ CTrans::UTOS(big_order) + "_" + CTrans::UTOS(small_order);
	ret = logicPay.ProcessOrderForBackend(uid, -xml_item.cash_, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		Json::FastWriter writer;
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发道具
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, xml_item.eqid_, xml_item.eq_cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	if (big_order == 1)
	{
		SecincData["c1"][small_order-1] = SecincData["c1"][small_order-1].asInt() + 1;
	} else if (big_order == 2)
	{
		SecincData["c2"][small_order-1] = SecincData["c2"][small_order-1].asInt() + 1;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("big order is illegal");
	}

	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("ZhenBaoGeHero SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::ZhenBaoGeBuilding(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("zhenbaoge_activity_time_error");
		return R_ERR_AUTH;
	}

	//魂石活动
	string type_zhenbaoge = Config::GetValue(CONFIG_ACTIVITY_ZHENBAOGE_TYPE);
	if (type_zhenbaoge != "building")
	{
		error_log("zhenbaoge_type_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//版本号, no data, 每天进行重置
	CLogicSecinc Secinc;
	Json::Value SecincData;
	bool can_reset = false;
	ret = Secinc.GetSecinc(uid, NAT_ZHENBAOGE, SecincData);
	if (ret == R_ERR_NO_DATA)
	{
		can_reset = true;
	} else if (!ret)
	{
		//对数据格式 严格检查
		if(!SecincData.isMember("a") ||
		   !SecincData.isMember("b")  ||
		   !SecincData.isMember("id")  ||
		   !SecincData.isMember("c1")  || !SecincData["c1"].isArray() || SecincData["c1"].size() != ZHENBAOGEBUILDING_SMALL_NUM ||
		   !SecincData.isMember("c2")  || !SecincData["c2"].isArray() || SecincData["c2"].size() != ZHENBAOGEBUILDING_SMALL_NUM)
		{
			DATA_ERROR_RETURN_MSG("SecincData");
		}

		//版本号
		if (SecincData["a"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_VER))
		{
			can_reset = true;
		}

		//每日重置
		if (!Time::IsToday(SecincData["b"].asUInt()))
		{
			can_reset = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (can_reset)
	{
		SecincData["id"] = NAT_ZHENBAOGE;
		SecincData["a"] = Config::GetIntValue(CONFIG_ACTIVITY_ZHENBAOGE_VER);
		SecincData["b"] = now;
		for(unsigned inx = 0; inx != ZHENBAOGEBUILDING_SMALL_NUM; ++inx)
		{
			SecincData["c1"][inx] = 0;
			SecincData["c2"][inx] = 0;
		}
	}

	//读取newAct，比较配置， 看是否买到了上限
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLZhenBaoGeBuildingItem  xml_item;
	ret = dataXML->GetZhenBaoGeBuildingItem(big_order-1, small_order-1, xml_item);
	if (ret || !xml_item.eqid_)
	{
		DB_ERROR_RETURN_MSG("GetZhenBaoGeBuildingItem fail");
	}

	if (((big_order == 1) && (SecincData["c1"][small_order-1].asInt() >= xml_item.limit_times_)) ||
		((big_order == 2) && (SecincData["c2"][small_order-1].asInt() >= xml_item.limit_times_)))
	{
		LOGIC_ERROR_RETURN_MSG("can not buy more");
	}

	//扣钱，添加物品，更改newAct
	CLogicPay logicPay;
	DataPay payData;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	bool bsave = false;
	string log_reason = "zhenbaogebuilding_"+ CTrans::UTOS(big_order) + "_" + CTrans::UTOS(small_order);
	ret = logicPay.ProcessOrderForBackend(uid, -xml_item.cash_, 0, payData, log_reason, user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		Json::FastWriter writer;
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//发道具
	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, xml_item.eqid_, xml_item.eq_cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	if (big_order == 1)
	{
		SecincData["c1"][small_order-1] = SecincData["c1"][small_order-1].asInt() + 1;
	} else if (big_order == 2)
	{
		SecincData["c2"][small_order-1] = SecincData["c2"][small_order-1].asInt() + 1;
	} else
	{
		LOGIC_ERROR_RETURN_MSG("big order is illegal");
	}

	ret = Secinc.SetOneSecinc(uid, SecincData);
	if (ret)
	{
		error_log("ZhenBaoGeBuilding SetOneSecinc failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"] = SecincData;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::HeroStoneStep(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("HeroStoneStep_activity_time_error");
		return R_ERR_AUTH;
	}

	//是否是魂石活动
	string type_zhenbaoge = Config::GetValue(CONFIG_ACTIVITY_GEM_STONE_TYPE);
	if (type_zhenbaoge != "soulstone")
	{
		error_log("HeroStoneStep_type_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//重置: version, no data
	CLogicUserData logicUserData;
	DataUserData data;
	ret = logicUserData.GetUserData(uid, data);
	if (ret)
		return ret;

	bool can_reset = false;
	Json::Value gift;
	Json::FromString(gift, data.gift);
	if(!gift.isMember("stoneVer") ||
	   !gift.isMember("stonen")  || !gift["stonen"].isArray() || gift["stonen"].size() != HEROSTONESTEP_ITEM_CNT)
	{
		can_reset = true;
	} else if (gift["stoneVer"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_VER))
	{
		can_reset = true;
	}

	if (can_reset)
	{
		for(unsigned inx = 0; inx != HEROSTONESTEP_ITEM_CNT; ++inx)
		{
			gift["stonen"][inx] = 0;
		}
		gift["stoneVer"] = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_VER);
	}

	//是否已经领取到了上限
	Json::Value & stonen = gift["stonen"];
	Json::Value & stoneVer = gift["stoneVer"];
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLHeroStoneStepItem  xml_item;
	ret = dataXML->GetHeroStoneStepItem(order-1, xml_item);
	if (ret || !xml_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetHeroStoneStepItem fail");
	}
	if (stonen[order - 1].asUInt() >= xml_item.maxcount_)
	{
		LOGIC_ERROR_RETURN_MSG("can not buy more");
	}

	//魂石数目必须大于已经领取的次数
	//#define IS_SOULSTONE_EQID(eqid)  (eqid >= 4401 && eqid <= 4490)
	//物攻命中魂石6-10级：4496-4500
	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	unsigned have_matched_stone = 0;
	for(int i=0; i<equip_data.size(); ++i)
	{
		unsigned temp_eqid = equip_data[i]["id"].asUInt();
		if ((temp_eqid >= 4401 && temp_eqid <= 4490) ||
			(temp_eqid >= 4496 && temp_eqid <= 4500))
		{
			if ((xml_item.lv_ == 4) &&
				((temp_eqid % 10) >= 1) &&
				((temp_eqid % 10) <= 4))
			{
				++have_matched_stone;
			} else if ((xml_item.lv_ > 4) &&
					  ((temp_eqid % 10) == xml_item.lv_))
			{
				++have_matched_stone;
			}
		}
	}

	if (have_matched_stone <= stonen[order - 1].asUInt())
	{
        error_log("HeroStoneStep matched stone failed. uid=%u, have_stone=%d, have_buy=%d", uid, have_matched_stone, stonen[order - 1].asUInt());
		return R_ERR_LOGIC;
	}

	//发临时魂石
	unsigned ats = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_E_TS) - Time::GetGlobalTime();
	string log_reason = "herostonestep_"+ CTrans::UTOS(order);
	ret = logicEquip.AddOneItem(uid, xml_item.reward_.eqid_, xml_item.reward_.eq_cnt_, log_reason, result["equip"], true, 0, 0, ats);
	if (ret)
	{
        error_log("HeroStoneStep add item failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	//更改gift
	stonen[order - 1] = stonen[order - 1].asUInt() + 1;
	result["stonen"] = stonen;
	result["stoneVer"] = stoneVer;
	ret = logicUserData.SetGift(uid, gift);
	if (ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::BuildingStoneStep(unsigned uid, unsigned order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//活动是否开启
	unsigned start_time = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_B_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_E_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("BuildingStoneStep_activity_time_error");
		return R_ERR_AUTH;
	}

	//是否是宝石活动
	string type_zhenbaoge = Config::GetValue(CONFIG_ACTIVITY_GEM_STONE_TYPE);
	if (type_zhenbaoge != "buildstone")
	{
		error_log("BuildingStoneStep_type_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//重置: version, no data
	CLogicUserData logicUserData;
	DataUserData data;
	ret = logicUserData.GetUserData(uid, data);
	if (ret)
		return ret;

	bool can_reset = false;
	Json::Value gift;
	Json::FromString(gift, data.gift);
	if(!gift.isMember("stoneVer") ||
	   !gift.isMember("stonen")  || !gift["stonen"].isArray() || gift["stonen"].size() != BUILDINGSTONESTEP_ITEM_CNT)
	{
		can_reset = true;
	} else if (gift["stoneVer"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_VER))
	{
		can_reset = true;
	}

	if (can_reset)
	{
		for(unsigned inx = 0; inx != BUILDINGSTONESTEP_ITEM_CNT; ++inx)
		{
			gift["stonen"][inx] = 0;
		}
		gift["stoneVer"] = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_VER);
	}

	//是否已经领取到了上限
	Json::Value & stonen = gift["stonen"];
	Json::Value & stoneVer = gift["stoneVer"];
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		DB_ERROR_RETURN_MSG("GetInitXML_fail");
	}
	XMLBuildingStoneStepItem  xml_item;
	ret = dataXML->GetBuildingStoneStepItem(order-1, xml_item);
	if (ret || !xml_item.id_)
	{
		DB_ERROR_RETURN_MSG("GetBuildingStoneStepItem fail");
	}
	if (stonen[order - 1].asUInt() >= xml_item.maxcount_)
	{
		LOGIC_ERROR_RETURN_MSG("can not buy more");
	}

	//宝石数目必须大于已经领取的次数
	//#define IS_BUILDSTONE_EQID(eqid)  (eqid >= 4301 && eqid <= 4360)
	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	unsigned have_matched_stone = 0;
	for(int i=0; i<equip_data.size(); ++i)
	{
		unsigned temp_eqid = equip_data[i]["id"].asUInt();
		if ((temp_eqid >= 4301 && temp_eqid <= 4360))
		{
			if ((xml_item.lv_ == 4) &&
				((temp_eqid % 10) >= 1) &&
				((temp_eqid % 10) <= 4))
			{
				++have_matched_stone;
			} else if ((xml_item.lv_ > 4) &&
					  ((temp_eqid % 10) == xml_item.lv_))
			{
				++have_matched_stone;
			}
		}
	}

	if (have_matched_stone <= stonen[order - 1].asUInt())
	{
        error_log("BuildingStoneStep matched stone failed. uid=%u, have_stone=%d, have_buy=%d", uid, have_matched_stone, stonen[order - 1].asUInt());
		return R_ERR_LOGIC;
	}

	//发临时宝石
	unsigned ats = Config::GetIntValue(CONFIG_ACTIVITY_GEM_STONE_E_TS) - Time::GetGlobalTime();
	string log_reason = "buildingstonestep_"+ CTrans::UTOS(order);
	ret = logicEquip.AddOneItem(uid, xml_item.reward_.eqid_, xml_item.reward_.eq_cnt_, log_reason, result["equip"], true, 0, 0, ats);
	if (ret)
	{
        error_log("BuildingStoneStep add item failed. uid=%d, ret=%d", uid, ret);
		return ret;
	}

	//更改gift
	stonen[order - 1] = stonen[order - 1].asUInt() + 1;
	result["stonen"] = stonen;
	result["stoneVer"] = stoneVer;
	ret = logicUserData.SetGift(uid, gift);
	if (ret)
		return ret;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::JinQiuNovember(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_JINQIUNOVEMBER_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_JINQIUNOVEMBER_END_TS))
		return R_ERR_LOGIC;

	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned need;
	pair<unsigned, unsigned> item;
	ret = pDataXML->GetJinQiuNovember(index, need, item);
	if(ret)
		return ret;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_JINQIUNOVEMBER_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_JINQIUNOVEMBER_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}
	if(chargeTotal < need)
		return R_ERR_LOGIC;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_JINQIUNOVEMBER, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < JINQIUNOVEMBER_INDEX; i++)
			array.append(0);
		newAct["id"] = NAT_JINQIUNOVEMBER;
		newAct["a"] = array;
		newAct["v"] = Config::GetIntValue(CONFIG_JINQIUNOVEMBER_VER);
	}
	else if(ret)
		return ret;

	if (newAct["v"].asInt() != Config::GetIntValue(CONFIG_JINQIUNOVEMBER_VER))
	{
		newAct["id"] = NAT_JINQIUNOVEMBER;
		for(unsigned i = 0; i < JINQIUNOVEMBER_INDEX; i++)
			newAct["a"][i] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_JINQIUNOVEMBER_VER);
	}

	if(newAct["a"][index].asUInt() != 0)
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	string log_reason = "jinqiunovember_"+ CTrans::UTOS(index);
	ret = logicEquipment.AddOneItem(uid, item.first, item.second, log_reason,result["equip"], true);
	if(ret)
		return ret;

	newAct["a"][index] = 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::AcchargeBackShenwen(unsigned uid, unsigned index, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_END_TS))
		return R_ERR_LOGIC;

	int ret = 0;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	unsigned need;
	pair<unsigned, unsigned> item;
	ret = pDataXML->GetAcchargeBackShenwen(index, need, item);
	if(ret)
		return ret;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag, user_flag);
	if (!user_flag.isMember("chgs") || !user_flag["chgs"].isArray())
	{
		error_log("chgs error");
		DATA_ERROR_RETURN_MSG("chgs error");
	}
	unsigned size = user_flag["chgs"].size();
	unsigned chargeTotal = 0;
	for (unsigned i = 0; i < size; ++i)
	{
		unsigned ts  = user_flag["chgs"][i][0u].asUInt();
		if(ts >= Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_BEGIN_TS)
		&& ts <= Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_END_TS))
			chargeTotal += user_flag["chgs"][i][1u].asUInt();
	}
	if(chargeTotal < need)
		return R_ERR_LOGIC;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ACCHARGEBACKSHENWEN, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		Json::Value array(Json::arrayValue);
		for(unsigned i = 0; i < ACCHARGEBACKSHENWEN_INDEX; i++)
			array.append(0);
		newAct["id"] = NAT_ACCHARGEBACKSHENWEN;
		newAct["a"] = array;
		newAct["v"] = Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_VER);
	}
	else if(ret)
		return ret;

	if (newAct["v"].asInt() != Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_VER))
	{
		newAct["id"] = NAT_ACCHARGEBACKSHENWEN;
		for(unsigned i = 0; i < ACCHARGEBACKSHENWEN_INDEX; i++)
			newAct["a"][i] = 0;
		newAct["v"] = Config::GetIntValue(CONFIG_ACCHARGEBACKSHENWEN_VER);
	}

	if(newAct["a"][index].asUInt() != 0)
		return R_ERR_LOGIC;

	CLogicEquipment logicEquipment;
	string log_reason = "acchargebackshenwen_"+ CTrans::UTOS(index);
	ret = logicEquipment.AddOneItem(uid, item.first, item.second, log_reason,result["equip"], true);
	if(ret)
		return ret;

	newAct["a"][index] = 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;
	result["newAct"] = newAct;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::HeroGrowStep(unsigned uid, unsigned hero_ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUser(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	Json::Value hero;
	CLogicHero logicHero;
	ret = logicHero.Get(uid, hero_ud, hero);
	if(ret)
		return ret;

	int hero_grade = 0;
	Json::GetInt(hero, "grade", hero_grade);

	//英雄level是否满足条件
	int cond_hero_level = 0, hero_level = 0;
	ret = CDataXML::GetHeroStepNeedHeroLevel(hero_grade + 1, cond_hero_level);
	if(ret)
		return ret;
	Json::GetInt(hero, "l", hero_level);
	if (hero_level < cond_hero_level)
	{
		LOGIC_ERROR_RETURN_MSG("hero level is small");
	}

	/* 去掉训练馆等级的检测
	//训练馆等级是否满足条件
	Json::Value jsonBd;
	CLogicBuilding logicBd;
	ret = logicBd.Get(uid, 19, 0, true, jsonBd); //19是训练馆的id
	if (ret != 0)
	{
		error_log("get_train_build failed. uid=%u", uid);
		return R_ERROR;
	}

	int cond_building_level = 0, building_level = 0;
	ret = CDataXML::GetHeroStepNeedBuildingLevel(hero_grade + 1, cond_building_level);
	if(ret)
		return ret;
	Json::GetInt(jsonBd, "l", building_level);
	if (building_level < cond_building_level)
	{
		LOGIC_ERROR_RETURN_MSG("building level is small");
	}
	*/

	//4阶的时候，pt是否满足条件
	if (hero_grade == 4)
	{
		XMLHero xmlhero;
		string hid = hero["id"].asString();
		ret = dataXML->GetHero(CDataXML::Str2Hero(hid), xmlhero);
		if(ret)
			return ret;
		float maxpt = CDataXML::GetMaxGradePoint(hero_grade, (float)xmlhero.point);
		if (hero["pt"].asDouble() + double(0.09) < maxpt)
		{
			error_log("%f-%f", hero["pt"].asDouble(), maxpt);
			LOGIC_ERROR_RETURN_MSG("hero pt is small");
		}
	}

	//扣除战魂
	int bs_sub = 0;
	ret = CDataXML::GetHeroStepNeedBSCost(hero_grade + 1, bs_sub);
	if(ret)
		return ret;
	if (dataUser.battle_spirits < bs_sub)
	{
		LOGIC_ERROR_RETURN_MSG("battle_spirits is less");
	}

	dataUser.battle_spirits -= bs_sub;
	result["bs"] = dataUser.battle_spirits;

	//扣除金币
	int coins_sub = 0;
	ret = CDataXML::GetHeroStepNeedGoldCost(hero_grade + 1, coins_sub);
	if(ret)
		return ret;

	CLogicPay logicPay;
	DataPay payData;
	Json::Value user_flag;
	Json::Reader reader;
	reader.parse(dataUser.user_flag, user_flag);
	bool bsave = false;
	ret = logicPay.ProcessOrderForBackend(uid, 0, -coins_sub, payData, "herostep", user_flag, bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		Json::FastWriter writer;
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//更新hero表的数据
	hero["grade"] = hero_grade + 1;
	hero["pt"] = hero["pt"].asDouble() * 1.03;

	if (Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_PEIYANG_BEGIN_TS) &&
		Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PEIYANG_END_TS))
	{
		hero["pot"]["g"] = hero["grade"];
		hero["pot"]["p"] = hero["pt"];
	}
	result["grade"] = hero["grade"];
	result["pot"] = hero["pot"];
	result["pt"] = hero["pt"];


	ret = logicHero.Chg(uid, hero_ud, hero);
	if(ret)
		return ret;

	if(bsave)
		ret = logicUser.SetUser(uid, dataUser);
	else
		ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}



int CLogicCMD::GrowDevelopGet(unsigned uid, unsigned big_order, unsigned small_order, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	unsigned start_time = Config::GetIntValue(CONFIG_PEIYANG_BEGIN_TS);
	unsigned end_time = Config::GetIntValue(CONFIG_PEIYANG_END_TS);
	unsigned now = Time::GetGlobalTime();
	if(now < start_time || now > end_time)
	{
		error_log("GrowDevelop_activity_time_error");
		return R_ERR_AUTH;
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = 0;
	ret = logicUser.GetUserLimit(uid, dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u", uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if (ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser, lasttime, seqid);
	if (ret)
	{
		return ret;
	}
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	//更新Secinc data
	bool reset_secinc = false;
	CLogicSecinc Secinc;
	Json::Value SecincDataOne;
	ret = Secinc.GetSecinc(uid, NAT_PEIYANG_1, SecincDataOne);
	if (ret == R_ERR_NO_DATA)
	{
		reset_secinc = true;
	} else if (!ret)
	{
		if ((!SecincDataOne.isMember("ver")) || SecincDataOne["ver"].asInt() != Config::GetIntValue(CONFIG_PEIYANG_VER))
		{
			reset_secinc = true;
		}
	} else
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	Json::Value SecincDataTwo;
	ret = Secinc.GetSecinc(uid, NAT_PEIYANG_2, SecincDataTwo);
	if (ret == R_ERR_NO_DATA)
	{
		reset_secinc = true;
	} else if (ret)
	{
		error_log("GetSecinc_error,uid = %u", uid);
		return ret;
	}

	if (reset_secinc)
	{
		SecincDataOne["id"] = NAT_PEIYANG_1;
		SecincDataOne["ver"] = Config::GetIntValue(CONFIG_PEIYANG_VER);
		Json::Value array_rd(Json::arrayValue);
		for(unsigned i = 0; i < HEROGROWDEVELOP_BIG_CNT; i++)
			array_rd.append(0);
		SecincDataOne["rd"] = array_rd;
		Json::Value array(Json::arrayValue);
		for (int i = 0; i < HEROGROWDEVELOP_BIG_CNT; i++)
		{
			Json::Value subArray(Json::arrayValue);
			for (int j = 0; j < HEROGROWDEVELOP_SMALL_CNT; j++)
				subArray.append(0);
			array.append(subArray);
		}
		SecincDataOne["gd"] = array;

		SecincDataTwo["id"] = NAT_PEIYANG_2;
		SecincDataTwo["mh"] = array;
	}

	//判断是否领取过 或者 是否有能力领取
	if ((SecincDataOne["gd"][big_order-1][small_order-1].asUInt() == 1) ||
		 SecincDataOne["rd"][big_order-1].asUInt() < small_order )
	{
		LOGIC_ERROR_RETURN_MSG("have_got_or_no_cond_get");
	}

	//发放物品
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	XMLGrowDevelopRewardItem xml_item;
	ret = dataXML->GetGrowDevelopRewardItem(big_order-1, small_order-1, xml_item);
	if(ret)
		return ret;

	CLogicEquipment logicEquip;
	string log_reason = "growdevelop_"+ CTrans::UTOS(big_order) + "_" + CTrans::UTOS(small_order);
	ret = logicEquip.AddOneItem(uid, xml_item.eqid_, xml_item.eq_cnt_, log_reason, result["equip"], true);
	if (ret)
	{
		return ret;
	}

	//更新secinic
	SecincDataOne["gd"][big_order-1][small_order-1] = 1;
	ret = Secinc.SetOneSecinc(uid, SecincDataOne);
	if (ret)
	{
		error_log("hero GrowDevelop SecincDataOne failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	ret = Secinc.SetOneSecinc(uid, SecincDataTwo);
	if (ret)
	{
		error_log("hero GrowDevelop SecincDataTwo failed. uid=%u, ret=%d", uid, ret);
		return ret;
	}
	result["newAct"][0u] = SecincDataOne;
	result["newAct"][1u] = SecincDataTwo;

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}
