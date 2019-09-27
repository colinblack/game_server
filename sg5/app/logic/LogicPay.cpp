
#include "LogicPay.h"
#include "LogicCmdUnits.h"

int CLogicPay::InitailizePay(unsigned uid)
{
	DataPay pay;
	pay.uid = uid;
	pay.cash = NEW_USER_CASH;
	pay.coins = NEW_USER_COINS;
	CDataPay dbPay;
	int ret = dbPay.AddPay(pay);
	if(ret != 0)
	{
		fatal_log("[AddPay fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}
	return 0;
}

int CLogicPay::AddUser(unsigned uid, unsigned cash)
{
	DataPay pay;
	pay.uid = uid;
	pay.cash = cash;
	pay.coins = 0;
	CDataPay dbPay;
	int ret = dbPay.AddPay(pay);
	if(ret != 0)
	{
		fatal_log("[AddPay fail][ret=%d,uid=%u,cash=%u]", ret, uid, cash);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}
	return 0;
}

int CLogicPay::GetPay(unsigned uid, DataPay &pay)
{
	CDataPay dbPay;
	int ret = dbPay.GetPay(uid, pay);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA || !IsAllianceId(uid))
		{
			error_log("[GetPay fail][ret=%d,uid=%u]", ret, uid);
		}
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_pay_data");
		}
		DB_ERROR_RETURN_MSG("db_get_pay_fail");
	}
	return 0;
}

//int CLogicPay::GetCash(unsigned uid, unsigned &cash)
//{
//	DataPay pay;
//	int ret = GetPay(uid, pay);
//	if (ret != 0)
//		return ret;
//	cash = pay.cash;
//	return 0;
//}

//用于购买隐藏武将碎片的积分
int CLogicPay::ChangePayHeroCoins(unsigned uid,int coins2,const string &type, Json::Value &user_flag)
{
	if(!user_flag.isMember("heroCoins"))
	{
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "ChangePayNewCoins_limit_error");
	}

	int hero_coins_old = user_flag["heroCoins"][1u].asInt();

	int hero_coins = hero_coins_old + coins2;
	if(hero_coins < 0)
	{
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "ChangePayNewCoins_limit_error");
	}

	user_flag["heroCoins"][1u] = hero_coins;

	COINS_LOG("[change hero_coins pay log][uid=%u,oherocoins=%d,herocoins=%d,type=%s]",
			uid,hero_coins_old,coins2,type.c_str());

	return 0;
}

int CLogicPay::AddHeroCoins(unsigned uid,int cash,const string &type, Json::Value &user_flag)
{
	unsigned now = Time::GetGlobalTime();
	int cash_total=0;
	int ocash_total = 0;
	int old_herocoins = 0;

	if(!user_flag.isMember("heroCoins"))
	{
		ocash_total =0;
		old_herocoins = 0;
		user_flag["heroCoins"][0u]= now;
		user_flag["heroCoins"][1u]= 0;          //herocoins
		user_flag["heroCoins"][2u]= cash;
	}
	else
	{
		unsigned last_ts = user_flag["heroCoins"][0u].asInt();
		old_herocoins = user_flag["heroCoins"][1u].asInt();
		if(CTime::GetDayInterval(last_ts,now) == 0)
		{
			ocash_total = user_flag["heroCoins"][2u].asInt();
			cash_total = user_flag["heroCoins"][2u].asInt() + cash;
			user_flag["heroCoins"][2u] = cash_total;
			user_flag["heroCoins"][0u] = now;
		}
		else
		{
			ocash_total =0;
			user_flag["heroCoins"][2u] = cash;
			user_flag["heroCoins"][0u] = now;
		}
	}

	unsigned cu = OpenPlatform::GetType() == PT_4399 ? HERO_COIN_CASH_4399 : HERO_COIN_CASH;
	unsigned cn = OpenPlatform::GetType() == PT_4399 ? HERO_COIN_NUM_4399 : HERO_COIN_NUM;
	unsigned oldcount = ocash_total / cu;
	unsigned newcount = user_flag["heroCoins"][2u].asInt()  / cu;
	unsigned count = (newcount - oldcount) * cn;
	user_flag["heroCoins"][0u] = now;
	user_flag["heroCoins"][1u] = count + user_flag["heroCoins"][1u].asInt();

	COINS_LOG("[change hero_coins pay log][uid=%u,oherocoins=%d,herocoins=%d,type=%s]",
			uid,old_herocoins,count,type.c_str());

	return 0;
}

int CLogicPay::ChangePay(unsigned uid, int cash, int coins, DataPay &pay, const string &type, Json::Value &user_flag, bool &bsave, unsigned flag, bool iskuafufenghuo)
{
	int ret = GetPay(uid, pay);
	if (ret != 0)
		return ret;
	unsigned org_cash = pay.cash;
	unsigned org_coins = pay.coins;
	if ((cash < 0 && (unsigned)(-cash) > pay.cash)
	|| (coins < 0 && (unsigned)(-coins) > pay.coins))
	{
		if(flag & PAY_FLAG_COST_ALL)
		{
			if(cash < 0 && (unsigned)(-cash) > pay.cash)
				cash = -pay.cash;
			if(coins < 0 && (unsigned)(-coins) > pay.coins)
				coins = -pay.coins;
		}
		else
		{
			error_log("[pay overspend][uid=%u,cash=%d,coins=%d,cashbal=%u,coinsbal=%u]",
					uid, cash, coins, pay.cash, pay.coins);
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "pay_limit_error");
		}
	}
	pay.cash += cash;
	pay.coins += coins;
	CDataPay dbPay;
	ret = dbPay.SetPay(uid, pay);
	if (ret != 0)
	{
		error_log("[SetPay fail][ret=%d,uid=%u,cash=%d,coins=%d,cashbal=%u,coinsbal=%u]",
				ret, uid, cash, coins, pay.cash, pay.coins);
		DB_ERROR_RETURN_MSG("set_pay_fail");
	}

	//处理充值回调
	if((flag & PAY_FLAG_CHARGE) && !(flag & PAY_FLAG_ADMIN) && !(flag & PAY_FLAG_NO_REPLY) && OpenPlatform::GetPlatform())
		OpenPlatform::GetPlatform()->ReplyCharge();

	bool saveUserPay = false;
	bool saveHero = false;
	//消费活动
	if((cash < 0 || coins < 0) && !(flag & PAY_FLAG_ADMIN))
	{
		//消费积分
		saveUserPay = true;
		addUserConsumeByDay(user_flag, coins, cash);
		if(cash < 0)
		{
			//百日庆典消费钻石
			SetHundredDaysActivities( uid, cash, user_flag);
			SetConsumeRank( uid, cash, user_flag, iskuafufenghuo);
		}
	}

	//处理充值
	if( cash > 0 && (flag & PAY_FLAG_CHARGE) && !(flag & PAY_FLAG_ADMIN))
	{
		if (!user_flag.isMember("dchg")
		|| CTime::GetDayInterval(user_flag["dchg"][0u].asUInt(), Time::GetGlobalTime()) != 0)
		{
			user_flag["dchg"][0u] = Time::GetGlobalTime();
			user_flag["dchg"][1u] = 0;
		}
		user_flag["dchg"][1u] = user_flag["dchg"][1u].asInt() + cash;
		// 累计充值
		addPaymentByDay(user_flag, cash);
		uint32_t now = Time::GetGlobalTime();
		/** 每日首次充值, add by vincent 2014-07-14*/
		if(CTime::IsDiffDay(user_flag["dfchg"][0u].asUInt(), now))
		{
			user_flag["dfchg"][0u] = (uint32_t)now;
			user_flag["dfchg"][1u] = cash;
		}
		else
		{
			user_flag["dfchg"][0u] = (uint32_t)now;
			user_flag["dfchg"][1u] = user_flag["dfchg"][1u].asUInt() + cash;
		}

		//武将碎片
		AddHeroCoins(uid,cash,type,user_flag);
		saveHero = true;

		//改为跨服架构---ralf 20140101
		//联盟为单位充值活动
		AllianceMember recharge;
		CLogicRechargeAlliance Rechargealliance;

		recharge.uid = uid;
		recharge.cash = cash;

		ret = Rechargealliance.UpdateRechargeAllianceData(recharge);
		if(0 != ret)
		{
			error_log("[update recharge alliance fail][uid=%d,ret=%d,cash=%d]", uid, ret, cash);
		}

		//充值排行榜
		SetRechargeRank(uid, cash, user_flag);
	}

	bsave =  saveUserPay || saveHero;

	COINS_LOG("[change pay log][uid=%u,ocash=%u,ocoins=%u,ncash=%u,nconis=%u,cash=%d,coins=%d,type=%s]",
			uid,org_cash,org_coins,pay.cash,pay.coins,cash,coins,type.c_str());
	return 0;
}

int CLogicPay::FixConsumeRank(unsigned uid)
{
	CLogicUser logicUser;
	DataUser user;
	Json::Value user_flag;
	Json::Reader reader;
	int ret = logicUser.GetUser(uid,user);
	if (ret)
		return ret;
	reader.parse(user.user_flag, user_flag);
	addUserConsumeByDay(user_flag, 0, 0);
		//百日庆典消费钻石
	SetHundredDaysActivities( uid, 0, user_flag);
	SetConsumeRank( uid, 0, user_flag);
	return 0;
}

int CLogicPay::ProcessOrderForBackend(unsigned uid, int cash, int coins, DataPay &pay, const string &type, Json::Value &user_flag, bool &bsave, unsigned flag, bool iskuafufenghuo)
{
	int ret = ChangePay(uid, cash, coins, pay, type, user_flag, bsave, flag, iskuafufenghuo);
	if(ret)
	{
		return ret;
	}
	if(cash < 0) {
		ORDERS_LOG("uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,type.c_str(),cash,1,1);
	}

	if(coins < 0) {
		ORDERS_LOG("uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,type.c_str(),coins,1,0);
	}
	return ret;
}


int CLogicPay::ChangePay(unsigned uid, int cash, int coins, const string &type, unsigned flag)
{
	DataPay pay;
	Json::Value user_flag;
	bool save = false;
	return ChangePay(uid, cash, coins, pay, type, user_flag, save, flag | PAY_FLAG_ADMIN);
}

int CLogicPay::ChangePay(unsigned uid, int cash, int coins, const string &type, DataPay &pay, unsigned flag)
{
	Json::Value user_flag;
	bool save = false;
	return ChangePay(uid, cash, coins, pay, type, user_flag, save, flag | PAY_FLAG_ADMIN);
}

int CLogicPay::AddPayHistory(DataPayHistory &payHistory)
{
	payHistory.time = Time::GetGlobalTime();
	uint64_t tempid = 0;
	CLogicIdCtrl logicIdCtrl;
	int ret = logicIdCtrl.GetNextId(KEY_PAY_ID_CTRL, tempid);
	if(ret != 0)
	{
		error_log("[GetNextId fail][ret=%d,uid=%u,channel=%d]",
				ret, payHistory.uid, payHistory.channel);
		DB_ERROR_RETURN_MSG("get_pay_id_fail");
	}
	payHistory.pay_id = tempid;
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.AddPayHistory(payHistory);
	if(ret != 0)
	{
		error_log("[AddPayHistory fail][ret=%d,uid=%u,payid=%llu,channel=%d]",
				ret, payHistory.uid, payHistory.pay_id, payHistory.channel);
		DB_ERROR_RETURN_MSG("add_pay_history_fail");
	}
	return 0;
}

int CLogicPay::GetPayHistory(unsigned uid, uint64_t payId, DataPayHistory &payHistory)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, payId, payHistory);
	if(ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetPayHistory fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
		DB_ERROR_RETURN_MSG("get_pay_history_fail");
	}
	return ret;
}

int CLogicPay::GetPayHistory(unsigned uid, PayChannelType channel, const string &channelPayId, DataPayHistory &payHistory)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, channel, channelPayId, payHistory);
	if(ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetPayHistory fail][ret=%d,uid=%u,channel=%d,channel_pay_id=%s]",
				ret, uid, channel, channelPayId.c_str());
		DB_ERROR_RETURN_MSG("get_pay_history_fail");
	}
	return ret;
}

int CLogicPay::GetPayHistory(unsigned uid, unsigned startTs, unsigned endTs, unsigned &totalPay)
{
	CDataPayHistory dbPayHistory;
	vector<DataPayHistory> vecPay;
	int ret = dbPayHistory.GetPayHistory(uid, startTs, endTs, vecPay);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetPayHistory fail][ret=%d,uid=%u,startts=%u,endts=%u]",
				ret, uid, startTs, endTs);
		DB_ERROR_RETURN_MSG("get_pay_history_fail");
	}

    vector<DataPayHistory>::iterator itr = vecPay.begin();
    for (; itr != vecPay.end(); itr++)
    {
    	if(itr->status == PST_OK)
    		totalPay += itr->count;
    }

	return ret;
}

int CLogicPay::SetPayHistoryStatus(unsigned uid, uint64_t payId, PayStatusType status)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.SetPayHistoryStatus(uid, payId, status);
	if(ret != 0)
	{
		error_log("[SetPayHistoryStatus fail][ret=%d,uid=%u,payId=%llu,status=%d]",
				ret, uid, payId, status);
		DB_ERROR_RETURN_MSG("set_pay_history_fail");
	}
	return ret;
}

int CLogicPay::SetPayHistoryStatus(unsigned uid, PayChannelType channel, const string &channelPayId, PayStatusType status)
{
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.SetPayHistoryStatus(uid, channel, channelPayId, status);
	if(ret != 0)
	{
		error_log("[SetPayHistoryStatus fail][ret=%d,uid=%u,channel=%d,channelPayId=%s,,status=%d]",
				ret, uid, channel, channelPayId.c_str(), status);
		DB_ERROR_RETURN_MSG("set_pay_history_fail");
	}
	return ret;
}

int CLogicPay::AddAlliancePay(unsigned aid, const string &type, int coins)
{
	CDataAlliancePay dbAlliancePay;
	DataAlliancePay alliancePay;
	alliancePay.alliance_id = aid;
	if (coins < 0)
	{
		fatal_log("[AddAlliancePay fail][coins=%d,aid=%u]", coins, aid);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}
	alliancePay.coins = coins;
	int ret = dbAlliancePay.AddPay(alliancePay);
	if(ret != 0)
	{
		fatal_log("[AddAlliancePay fail][ret=%d,aid=%u]", ret, aid);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}

	COINS_LOG("[change pay log][uid=%u,ocash=0,ocoins=0,ncash=0,nconis=%u,cash=0,coins=%u,type=%s,count=1]",
				aid,alliancePay.coins,coins,type.c_str());

	return 0;
}
int CLogicPay::GetAlliancePay(unsigned aid, DataAlliancePay &pay)
{
	CDataAlliancePay dbAlliancePay;
	int ret = dbAlliancePay.GetPay(aid, pay);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA || !IsAllianceId(aid))
		{
			error_log("[GetAlliancePay fail][ret=%d,uid=%u]", ret, aid);
		}
		if(ret == R_ERR_NO_DATA)
		{
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_pay_data");
		}
		DB_ERROR_RETURN_MSG("db_get_pay_fail");
	}
	return 0;
}

int CLogicPay::ChangeAlliancePay(unsigned aid, int coins, const string &type, int count)
{
	DataAlliancePay alliancePay;
	int ret = GetAlliancePay(aid, alliancePay);
	if (ret != 0)
			return ret;
	unsigned org_coins = alliancePay.coins;
	if ((coins < 0 && (unsigned)(-coins) > alliancePay.coins))
	{
		error_log("[pay overspend][aid=%u,coins=%d,coinsbal=%u]", aid, coins, alliancePay.coins);
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "pay_limit_error");
	}

	alliancePay.coins += coins;
	CDataAlliancePay dbAlliancePay;
	ret = dbAlliancePay.SetPay(aid, alliancePay);
	if (ret != 0)
	{
		error_log("[ChangeAlliancePay fail][ret=%d,aid=%u,coins=%d,coinsbal=%u]",
				ret, aid, coins, alliancePay.coins);
		DB_ERROR_RETURN_MSG("set_pay_fail");
	}

	COINS_LOG("[change pay log][uid=%u,ocash=0,ocoins=%u,ncash=0,nconis=%u,cash=0,coins=%d,type=%s,count=%d]",
			aid,org_coins,alliancePay.coins,coins,type.c_str(),count);
	return 0;
}

/** 玩家支付完后需要做的处理 */
int CLogicPay::DoPay(unsigned uid, DataUser &user, const unsigned cash)
{
	CDataUser userDb;
	int t = cash;
	userDb.AddAccCharge(uid, t);
	// 指定的平台才需要发邮件
	if(OpenPlatform::IsQQPlatform())
	{
#ifdef SG_16_VER
		if(user.accCharge < 30000 && user.accCharge + cash >= 30000
		&& (Time::GetGlobalTime()-user.register_time) < (86400*30))
		{
			DataEmail email;
			CLogicEmail logicEmail;
			vector<uint64_t> toUidList;
			toUidList.push_back(uid);
			email.attach_flag = 0;
			email.attachments = "";
			email.uid = ADMIN_UID;
			email.post_ts = Time::GetGlobalTime();
			email.title = "至尊会员";
			email.text = "尊敬的玩家您好，恭喜您成为我们的高级VIP用户。请联系QQ：3139311550 领取VIP礼包并有专业人士进行游戏指导。";
			logicEmail.AddEmail(email,toUidList);
		}
#else
		if(user.accCharge < 50000 && user.accCharge + cash >= 50000
		&& (Time::GetGlobalTime()-user.register_time) < (86400*21))
		{
			DataEmail email;
			CLogicEmail logicEmail;
			vector<uint64_t> toUidList;
			toUidList.push_back(uid);
			email.attach_flag = 0;
			email.attachments = "";
			email.uid = ADMIN_UID;
			email.post_ts = Time::GetGlobalTime();
			email.title = "至尊会员";
			email.text = "尊敬的玩家您好，恭喜您成为我们的高级VIP用户。请联系QQ：2624248020领取VIP礼包并有专业人士进行游戏指导。";
			logicEmail.AddEmail(email,toUidList);
		}
#endif
	}
	user.accCharge += cash;
	return 0;
}

int CLogicPay::addPaymentByDay(Json::Value &userFlag, int accCharge){
	uint32_t now = Time::GetGlobalTime();
	if(!userFlag.isMember("chgs") || !userFlag["chgs"].isArray() || userFlag["chgs"].size() == 0) {
		//补丁
		if(userFlag.isMember("hqchg")) {
			accCharge += userFlag["hqchg"][1u].asInt();
			userFlag.removeMember("hqchg");
		}
		userFlag["chgs"][0u][0u] = now;
		userFlag["chgs"][0u][1u] = accCharge;
		return 0;
	}

	size_t size = userFlag["chgs"].size();
	vector<pair<uint32_t, int> > vec_chg;
	for(size_t i = 0; i < size; ++i){
		pair<uint32_t, int> pair;
		pair.first  = userFlag["chgs"][i][0u].asUInt();
		pair.second = userFlag["chgs"][i][1u].asInt();
		vec_chg.push_back(pair);
	}

	if(!CTime::IsDiffDay(vec_chg.back().first, now)) {
		vec_chg.back().second += accCharge;
	} else {
		pair<uint32_t, int> pair;
		pair.first = now;
		pair.second = accCharge;
		vec_chg.push_back(pair);
	}

	while(vec_chg.size() > 15) {
		vec_chg.erase(vec_chg.begin());
	}
	userFlag["chgs"].clear();
	for(size_t i = 0; i < vec_chg.size(); ++i) {
		uint32_t chgTime = vec_chg[i].first;
		int chrg = vec_chg[i].second;
		userFlag["chgs"][i][0u] = chgTime;
		userFlag["chgs"][i][1u] = chrg;
	}
	return 0;
}

int CLogicPay::SetUserPayRank(unsigned uid, int cash, Json::Value &user_flag, bool &bsave)
{
	unsigned now = Time::GetGlobalTime();
	if(now >= Config::GetIntValue(CONFIG_PAYRANK_BEGIN_TS)
	&& now <= Config::GetIntValue(CONFIG_PAYRANK_END_TS)
	&& cash < 0)
	{
		bsave = true;

		int ret = 0;
		int lastpay_ts = 0;
		int payTotal = 0;
		if(!user_flag.isMember("pointpay"))
		{
			user_flag["pointpay"][0u]= -cash;
			user_flag["pointpay"][1u]= now;
			payTotal = -cash;
		}
		else
		{
			lastpay_ts = user_flag["pointpay"][1u].asInt();
			if(    lastpay_ts >= Config::GetIntValue(CONFIG_PAYRANK_BEGIN_TS)
				&& lastpay_ts <= Config::GetIntValue(CONFIG_PAYRANK_END_TS))
			{
				payTotal = user_flag["pointpay"][0u].asUInt() - cash;
				user_flag["pointpay"][0u] = payTotal;
				user_flag["pointpay"][1u]= now;
			}
			else
			{
				user_flag["pointpay"][0u] = payTotal = - cash;
				user_flag["pointpay"][1u] = now;
			}

			string activity_type;
			Config::GetValue(activity_type, CONFIG_PAYRANK_TYPE);
			if(activity_type == "cutprice" && CTime::GetDayInterval(lastpay_ts, now) != 0)   //五一活动需要每天清积分
			{
				user_flag["pointpay"][0u] = payTotal = - cash;
				user_flag["pointpay"][1u] = now;
			}
		}
		/*
		CLogicUserBasic logicUserBasic;
		DataUserBasic userBasic;
		ret = logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),userBasic);
		if (0 != ret)
		{
			error_log("[get usr basic fail][uid=%u,ret=%d]", uid, ret);
		}
		CLogicPayRank logicPayRank;
		PayItem payItem;
		payItem.uid = uid;
		payItem.payTotal = payTotal;
		memcpy(payItem.name,userBasic.name.c_str(),sizeof(payItem.name) - 1);
		ret = logicPayRank.UpdatePayRank(uid,payItem);
		if (0 != ret)
		{
			error_log("[UpdatePayRank fail][uid=%u,ret=%d,points=%d]", uid, ret,payItem.payTotal);
		}
		*/
	}
	return 0;
}
int CLogicPay::SetUserPayTotal(unsigned uid, int cash, Json::Value &user_flag, bool &bsave)
{
	unsigned now = Time::GetGlobalTime();
	if(now >= Config::GetIntValue(CONFIG_PAY_TOTAL_BEGIN_TS)
	&& now <= Config::GetIntValue(CONFIG_PAY_TOTAL_END_TS)
	&& cash < 0)
	{
		bsave = true;

		int ret = 0;
		int lastpay_ts = 0;
		int payTotal = 0;
		if(!user_flag.isMember("payTotal"))
		{
			user_flag["payTotal"][0u]= -cash;
			user_flag["payTotal"][1u]= now;
		}
		else
		{
			lastpay_ts = user_flag["payTotal"][1u].asInt();
			if(    lastpay_ts >= Config::GetIntValue(CONFIG_PAY_TOTAL_BEGIN_TS)
				&& lastpay_ts <= Config::GetIntValue(CONFIG_PAY_TOTAL_END_TS))
			{
				payTotal = user_flag["payTotal"][0u].asUInt() - cash;
				user_flag["payTotal"][0u] = payTotal;
				user_flag["payTotal"][1u]= now;
			}
			else
			{
				user_flag["payTotal"][0u] = payTotal = - cash;
				user_flag["payTotal"][1u] = now;
			}
		}
	}
	return 0;
}
//百日庆典活动
int CLogicPay::SetHundredDaysActivities(unsigned uid, int cash, Json::Value &user_flag)
{
	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	if((unsigned)now >= Config::GetIntValue(CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_PAY_OF_HUNDRED_DAYS_END_TS)
	&& tempNow < 79200					//每天的0点至22点
	&& cash < 0)
	{
		if(user_flag.isMember("hundredDaysPay"))
		{
			user_flag.removeMember("hundredDaysPay");
		}
		unsigned payTotal = 0;
		unsigned size = user_flag["user_pay"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["user_pay"][i][0u].asUInt();
			if(!CTime::IsDiffDay(ts, now))
			{
				payTotal = user_flag["user_pay"][i][1u].asUInt();
				break;
			}
		}

		DataHDaysAcvitityPay points;
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		CLogicHundredDaysActivityRank hdaysactivittyRank;
		logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);
		points.uid = uid;
		points.pay = payTotal;
		memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);
		int ret = hdaysactivittyRank.UpdateHundredDaysActivityRank(uid,points);
		if(ret != 0)
		{
			error_log("UpdateHundredDaysActivityRank error uid=%u,ret=%d,points=%d",uid,ret,points.pay);
		}
	}
	return 0;
}

int CLogicPay::SetConsumeRank(unsigned uid, int cash, Json::Value &user_flag, bool iskuafufenghuo)
{
	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	if((unsigned)now >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS)
	&& tempNow < 79200					//每天的0点至22点
	&& cash <= 0)
	{
		int ret = 0;
		unsigned lastpay_ts = 0;
		unsigned dayTotal = 0;
		unsigned allTotal = 0;
		unsigned need = 0;
		if(user_flag.isMember("consumeRank"))
		{
			user_flag.removeMember("consumeRank");
		}

		if(!user_flag.isMember("pay_need")
		|| user_flag["pay_need"][1u].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_VER))
		{
			user_flag["pay_need"][0u] = need;
			user_flag["pay_need"][1u] = Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_VER);
		}

		unsigned size = user_flag["user_pay"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["user_pay"][i][0u].asUInt();
			if(!CTime::IsDiffDay(ts, now))
			{
				need = user_flag["pay_need"][0u].asUInt();
				dayTotal = user_flag["user_pay"][i][1u].asUInt();
			}
			else
			{
				user_flag["pay_need"][0u] = need;
			}
			if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
			&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
			{
				allTotal += user_flag["user_pay"][i][1u].asUInt();
			}
		}

		if (iskuafufenghuo)
		{
			user_flag["pay_need"][0u] = 0;
		}
		else {
			if(-cash >= need)
			{
				CLogicUserBasic logicUserBasic;
				DataUserBasic dataUserBasic;
				logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);

				CLogicConsumeRank logicConsumeRank;
				logicConsumeRank.SetUser(uid, dayTotal, allTotal, dataUserBasic.name, need);
				user_flag["pay_need"][0u] = need;
			}
			else
			{
				need += cash;
				user_flag["pay_need"][0u] = need;
			}
		}
	}
	if((unsigned)now >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS)
	&& cash < 0)
	{
		int ret = 0;
		int allTotal = 0;
		unsigned size = user_flag["user_pay"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["user_pay"][i][0u].asUInt();
			if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
			&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_CONSUME_RANK_E_TS))
			{
				allTotal += user_flag["user_pay"][i][1u].asUInt();
			}
		}
		int oat = allTotal + cash;
		unsigned check[8] = {998,5888,28888,48888,88888,118888,288888,588888};
		unsigned gift[8] = {31111,31112,31113,31114,31115,31116,31117,31118};
		for(int i=0;i<8;++i)
		{
			if(oat < check[i] && allTotal >= check[i])
			{
				Json::Value temp;
				CLogicEquipment().AddOneItem(uid, gift[i], 1, "SetConsumeRank", temp);
				Json::Value updates;
				updates["s"] = "SetConsumeRank";
				updates["uid"] = uid;
				updates["ts"] = (unsigned)now;
				updates["cash"] = check[i];
				updates["eqid"] = gift[i];
				CLogicUpdates().AddUpdate(uid,updates,true);
			}
		}
	}
	return 0;
}

int CLogicPay::SetRechargeRank(unsigned uid, int cash, Json::Value &user_flag)
{
	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	if((unsigned)now >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS)
	&& tempNow < 79200					//每天的0点至22点
	&& cash > 0)
	{
		int ret = 0;
		unsigned dayTotal = 0;
		unsigned allTotal = 0;
		unsigned need = 0;

		if(!user_flag.isMember("recharge_need")
		|| user_flag["recharge_need"][1u].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER))
		{
			user_flag["recharge_need"][0u] = need;
			user_flag["recharge_need"][1u] = Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER);
			user_flag["recharge_need"][2u] = (unsigned)now;
		}

		if(CTime::IsDiffDay(user_flag["recharge_need"][2u].asUInt(), now))
		{
			user_flag["recharge_need"][0u] = 0;
			user_flag["recharge_need"][2u] = (unsigned)now;
		}
		else
		{
			need = user_flag["recharge_need"][0u].asUInt();
		}

		unsigned size = user_flag["chgs"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["chgs"][i][0u].asUInt();
			if(!CTime::IsDiffDay(ts, now))
			{
				dayTotal = user_flag["chgs"][i][1u].asUInt();
			}

			if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
			&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
			{
				allTotal += user_flag["chgs"][i][1u].asUInt();
			}
		}

		if(cash >= need)
		{
			CLogicUserBasic logicUserBasic;
			DataUserBasic dataUserBasic;
			logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);

			CLogicRechargeRank logicRechargeRank;
			logicRechargeRank.SetUser(uid, dayTotal, allTotal, dataUserBasic.name, need);
			user_flag["recharge_need"][0u] = need;
		}
		else
		{
			need -= cash;
			user_flag["recharge_need"][0u] = need;
		}
	}
	if((unsigned)now >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
	&& (unsigned)now <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS)
	&& cash > 0)
	{
		int ret = 0;
		unsigned allTotal = 0;
		unsigned size = user_flag["chgs"].size();
		for(int i = 0; i < size; ++i)
		{
			unsigned ts  = user_flag["chgs"][i][0u].asUInt();
			if(ts >= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
			&& ts <= Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS))
			{
				allTotal += user_flag["chgs"][i][1u].asUInt();
			}
		}
		int oat = allTotal - cash;
		unsigned check[8] = {988,5888,28888,48888,88888,118888,288888,588888};
		unsigned gift[8] = {31119,31120,31121,31122,31123,31124,31125,31126};
		for(int i=0;i<8;++i)
		{
			if(oat < check[i] && allTotal >= check[i])
			{
				Json::Value temp;
				CLogicEquipment().AddOneItem(uid, gift[i], 1, "SetRechargeRank", temp);
				Json::Value updates;
				updates["s"] = "SetRechargeRank";
				updates["uid"] = uid;
				updates["ts"] = (unsigned)now;
				updates["cash"] = check[i];
				updates["eqid"] = gift[i];
				CLogicUpdates().AddUpdate(uid,updates,true);
			}
		}
	}
	return 0;
}

int CLogicPay::Try(unsigned int uid, int cash, int coins)
{
	DataPay pay;
	int ret = GetPay(uid, pay);
	if (ret != 0)
		return ret;

	if ((cash < 0 && (unsigned)(-cash) > pay.cash) || (coins < 0 && (unsigned)(-coins) > pay.coins))
		return R_ERR_LOGIC;

	return 0;
}

int CLogicPay::addUserConsumeByDay(Json::Value &userFlag, int coins, int cash)
{
	if(coins > 0)
		coins = 0;
	if(cash > 0)
		cash = 0;

	if(userFlag.isMember("pointpay"))
	{
		userFlag.removeMember("pointpay");
	}
	if(userFlag.isMember("payTotal"))
	{
		userFlag.removeMember("payTotal");
	}
	unsigned now = Time::GetGlobalTime();
	if(!userFlag.isMember("user_pay") || !userFlag["user_pay"].isArray() || userFlag["user_pay"].size() == 0)
	{
		userFlag["user_pay"][0u][0u] = now;
		userFlag["user_pay"][0u][1u] = -cash;
		userFlag["user_pay"][0u][2u] = -coins;
		return 0;
	}

	unsigned size = userFlag["user_pay"].size();
	vector<User_Pay> vec_chg;
	for(int i = 0; i < size; ++i)
	{
		User_Pay pair;
		pair.ts  = userFlag["user_pay"][i][0u].asUInt();
		pair.cash = userFlag["user_pay"][i][1u].asInt();
		pair.coins = userFlag["user_pay"][i][2u].asInt();
		vec_chg.push_back(pair);
	}

	if(!CTime::IsDiffDay(vec_chg.back().ts, now))
	{
		vec_chg.back().cash -= cash;
		vec_chg.back().coins -= coins;
	}
	else
	{
		User_Pay pair;
		pair.ts = now;
		pair.cash = -cash;
		pair.coins = -coins;
		vec_chg.push_back(pair);
	}

	while(vec_chg.size() > 7)
	{
		vec_chg.erase(vec_chg.begin());
	}

	userFlag["user_pay"].clear();
	for(int i = 0; i < vec_chg.size(); ++i)
	{
		userFlag["user_pay"][i][0u] = vec_chg[i].ts;
		userFlag["user_pay"][i][1u] = vec_chg[i].cash;
		userFlag["user_pay"][i][2u] = vec_chg[i].coins;
	}

	return 0;
}
