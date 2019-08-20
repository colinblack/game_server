#include "LogicZhouNianQing.h"
#include "LogicCmdBase.h"

CDataZhouNianQingQianDao* CLogicZhouNianQing::GetDataZhouNianQingQianDao(void)
{
	GET_MEM_DATA_SEM(CDataZhouNianQingQianDao, CONFIG_ZHOUNIANQING_QIANDAO_DATA, sem_zhounianqing_qiandao, true)
}


int CLogicZhouNianQing::QianDao(unsigned uid, unsigned last_time)
{/*
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_QIANDAO);
	if (actconfig.IsActive()) {
		Json::Value newAct;
		CLogicSecinc logicSecinc;
		int ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_qiandao,newAct);
		if (ret && ret!=R_ERR_NO_DATA)
			return ret;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		DataXMLZhouNianQing config;
		ret = dataXML->GetZhouNianQingReward(config);
		if (ret)
		{
			return ret;
		}
		if (ret == R_ERR_NO_DATA || newAct["v"].asUInt()!=actconfig.Version())
		{
			newAct["id"] = NAT_zhounianqing_qiandao;
			newAct["v"] = actconfig.Version();
			newAct["a"] = 0;//签到值
			newAct["b"] = 0;//庆典卷数量
			newAct["c"] = Json::Value(Json::arrayValue);//签到值奖励领取
			for (int i=0;i<GetSignNum(config);i++)
				newAct["c"].append(0);
			newAct["ts"] = 0;
			newAct["n"] = 0;//拉了多少个人
			newAct["bd"] = 0;//绑定了哪个uid
		}
		if (last_time < newAct["ts"].asUInt())//老玩家绑定老玩家的情况
			last_time = newAct["ts"].asUInt();
		if (CTime::IsDiffDay(newAct["ts"].asUInt(),Time::GetGlobalTime()))
		{
			newAct["ts"] = Time::GetGlobalTime();
			newAct["d"] = Json::Value(Json::arrayValue);//兑换
			for (int i=0;i<GetShopNum(config)-1;i++)//第一个无限制兑换，所以不计是否兑换过
				newAct["d"].append(0);
		}
		else
		{
			return 0;
		}

		unsigned qiandaozhi = config.small;
		if (last_time< config.ts)//上次登录在2019年1月1日以前
			qiandaozhi = config.big;
		newAct["a"] = newAct["a"].asUInt() + qiandaozhi;
		newAct["b"] = newAct["b"].asUInt() + 100;
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
		{
			LOGIC_ERROR_RETURN_MSG("set_secinc_error");
		}

		string url = "action=AddQuanFuQianDaoZhi&version="+Convert::UIntToString(actconfig.Version())
					+"&count="+CTrans::ITOS(qiandaozhi);
		Json::Value result;
		CLogicAllServerBaseMatch logicBaseMatch;
		ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
		if(ret)
			return ret;
	}
	*/
	return 0;
}

int CLogicZhouNianQing::GetInfo(Json::Value & result)
{
	CDataZhouNianQingQianDao *pData = GetDataZhouNianQingQianDao();
	if (NULL == pData)
	{
		error_log("GetInfo fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetInfo(result);
	if(ret)
		return ret;

	return 0;
}

int CLogicZhouNianQing::GetQuanFuInfo(Json::Value & result)
{
	string url = "action=GetQuanFuQianDaoZhi";
	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;

	return 0;
}


int CLogicZhouNianQing::DuiHuan(unsigned uid, unsigned id, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_QIANDAO);
	if (!actconfig.IsActive()) {
		LOGIC_ERROR_RETURN_MSG("activity_is_over");
	}
	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLZhouNianQing config;
	int ret = dataXML->GetZhouNianQingReward(config);
	if (ret)
	{
		return ret;
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_qiandao,newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (ret == R_ERR_NO_DATA || newAct["v"].asUInt()!=actconfig.Version())
	{
		newAct["id"] = NAT_zhounianqing_qiandao;
		newAct["v"] = actconfig.Version();
		//newAct["a"] = 0;//签到值
		newAct["b"] = 0;//庆典卷数量
		//newAct["c"] = Json::Value(Json::arrayValue);//签到值奖励领取
		//for (int i=0;i<GetSignNum(config);i++)
			//newAct["c"].append(0);
		newAct["ts"] = 0;
		//newAct["n"] = 0;//拉了多少个人
		//newAct["bd"] = 0;//绑定了哪个uid
	}

	if (!id || id>GetShopNum(config))
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (newAct["b"].asUInt() < config.shop[id-1].require)
	{
		LOGIC_ERROR_RETURN_MSG("require_not_enough");
	}

	if (CTime::IsDiffDay(newAct["ts"].asUInt(),Time::GetGlobalTime()))
	{
		newAct["ts"] = Time::GetGlobalTime();
		newAct["d"] = Json::Value(Json::arrayValue);//兑换
		for (int i=0;i<GetShopNum(config)-1;i++)//第一个无限制兑换，所以不计是否兑换过
			newAct["d"].append(0);
		newAct["s"] = 0;
	}

	if (id>1 && newAct["d"][id-2].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("duihuan_has_got");
	}

	if (id>1)
	{
		newAct["d"][id-2] = 1;
	}

	newAct["b"] = newAct["b"].asUInt() - config.shop[id-1].require;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("set_secinc_error");
	}

	vector<GiftEquipItem> reward;
	string code = "zhounianqing_duihuan_"+CTrans::ITOS(id);
	for (int k=0;k<XML_ZHOUNIANQING_SHOP_REWARD_NUM;k++)
		reward.push_back(config.shop[id-1].reward[k]);
	BaseCmdUnit basecmdUnit(uid);
	basecmdUnit.AddGiftEquips(reward, code, result["equipments"],actconfig.EndTS()-Time::GetGlobalTime());

	result["newAct"] = newAct;

	return 0;
}

int CLogicZhouNianQing::GetQianDaoReward(unsigned uid, unsigned id, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_QIANDAO);
	if (!actconfig.IsActive()) {
		LOGIC_ERROR_RETURN_MSG("activity_is_over");
	}
	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLZhouNianQing config;
	int ret = dataXML->GetZhouNianQingReward(config);
	if (ret)
	{
		return ret;
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_qiandao,newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (!id || id>GetSignNum(config))
	{
		error_log("id=%u,GetSignNum(config)=%u",id,GetSignNum(config));
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (newAct["a"].asUInt() < config.sign[id-1].selfneed)
	{
		LOGIC_ERROR_RETURN_MSG("selfneed_not_enough");
	}

	if (newAct["c"][id-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("qiandaoreward_has_got");
	}

	newAct["c"][id-1] = 1;

	Json::Value qiandao;
	GetQuanFuInfo(qiandao);
	if (qiandao["total"].asUInt() < config.sign[id-1].quanfuneed)
	{
		LOGIC_ERROR_RETURN_MSG("quanfuneed_not_enough");
	}


	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("set_secinc_error");
	}

	vector<GiftEquipItem> reward;
	string code = "zhounianqing_qiandao_reward_"+CTrans::ITOS(id);
	for (int k=0;k<XML_ZHOUNIANQING_SIGN_REWARD_NUM;k++)
		reward.push_back(config.sign[id-1].reward[k]);
	BaseCmdUnit basecmdUnit(uid);
	basecmdUnit.AddGiftEquips(reward, code, result["equipments"]);

	result["newAct"] = newAct;

	return 0;
}

int CLogicZhouNianQing::zhouniantehuibangding(unsigned uid, unsigned uid2, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_QIANDAO);
	if (!actconfig.IsActive()) {
		LOGIC_ERROR_RETURN_MSG("activity_is_over");
	}

	if (uid == uid2 || !IsValidUid(uid2)) {
		error_log("uid=%u,uid2=%u",uid,uid2);
		result["uidError"] = 1;
		return 0;
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLZhouNianQing config;
	int ret = dataXML->GetZhouNianQingReward(config);
	if (ret)
	{
		return ret;
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_qiandao,newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (newAct["bd"].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("has_bangding");
	}

	if (newAct["a"].asUInt() < config.big)
	{
		LOGIC_ERROR_RETURN_MSG("not_old_player");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	ret = logicUser.GetUserLimit(uid2, dataUser);
	if (ret)
	{
		result["uidError"] = 1;
		return 0;
	}

	newAct["bd"] = uid2;

	ret = logicSecinc.SetOneSecinc(uid,newAct);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	vector<GiftEquipItem> reward;
	string code = "zhouniantehuibangding_"+CTrans::ITOS(uid)+"_"+CTrans::ITOS(uid2);
	for (int k=0;k<XML_ZHOUNIANQING_BANGDING_REWARD_NUM;k++)
		reward.push_back(config.bangding[0].reward[k]);
	BaseCmdUnit basecmdUnit(uid);
	basecmdUnit.AddGiftEquips(reward, code, result["equipments"]);


	Json::Value newAct2;

	ret = logicSecinc.GetSecinc(uid2,NAT_zhounianqing_qiandao,newAct2);
	if (ret && ret!=R_ERR_NO_DATA)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (ret == R_ERR_NO_DATA)
	{
		QianDao(uid2,dataUser.last_login_time);
		logicSecinc.GetSecinc(uid2,NAT_zhounianqing_qiandao,newAct2);
	}

	newAct2["n"] = newAct2["n"].asUInt() + 1;


	ret = logicSecinc.SetOneSecinc(uid2,newAct2);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (newAct2["n"].asUInt() <= 10)
	{
		reward.clear();
		for (int k=0;k<XML_ZHOUNIANQING_BANGDING_REWARD_NUM;k++)
			reward.push_back(config.bangding[1].reward[k]);
		BaseCmdUnit basecmdUnit(uid2);
		Json::Value equip;
		basecmdUnit.AddGiftEquips(reward, code, equip);
	}

	CLogicUpdates logicUpdates;
	Json::Value updates;
	updates["s"] = "ZHOUNIANQINGBANGDING";
	updates["uid"] = uid2;
	updates["ts"] = Time::GetGlobalTime();
	updates["uid2"] = uid;
	string userName;
	CDataUserBasic dbUser;
	dbUser.GetUserName(uid, OpenPlatform::GetType(), userName);
	updates["name"] = userName;
	updates["num"] = newAct2["n"].asUInt();
	logicUpdates.AddUpdate(uid2,updates,true);

	result["newAct"] = newAct;
	return 0;
}

int CLogicZhouNianQing::zhouniantehuigoumai(unsigned uid, unsigned id, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_GOUMAI);
	if (!actconfig.IsActive()) {
		LOGIC_ERROR_RETURN_MSG("activity_is_over");
	}
	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLZhouNianQing config;
	int ret = dataXML->GetZhouNianQingReward(config);
	if (ret)
	{
		return ret;
	}

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_goumai,newAct);
	if (ret && ret!=R_ERR_NO_DATA)
	{
		LOGIC_ERROR_RETURN_MSG("get_secinc_error");
	}

	if (ret == R_ERR_NO_DATA || CTime::IsDiffDay(newAct["ts"].asUInt(),Time::GetGlobalTime()))
	{
		newAct["id"] = NAT_zhounianqing_goumai;
		newAct["a"] = Json::Value(Json::arrayValue);
		for (int i=0;i<GetYearShopNum(config);i++)
			newAct["a"].append(0);
		newAct["ts"] = Time::GetGlobalTime();
	}

	if (!id || id>GetYearShopNum(config))
	{
		PARAM_ERROR_RETURN_MSG("id");
	}

	BaseCmdUnit basecmdUnit(uid);
	UserWrap user(uid,false);

	unsigned daily_charge = user.GetSingleDayRecharge(Time::GetGlobalTime());
	unsigned limit = 1;
	if (daily_charge >= 100)  limit++;
	if (daily_charge >= 1000) limit++;
	if (newAct["a"][id-1].asUInt() >= limit) {
		LOGIC_ERROR_RETURN_MSG("shop_limited");
	}

	string code = "zhouniantehuigoumai_"+CTrans::ITOS(id);
	if (R_SUCCESS != user.CostAsset(config.yearshop[id-1].moneyType==1?config.yearshop[id-1].require:0, config.yearshop[id-1].moneyType==2?config.yearshop[id-1].require:0, code, result["cost"]))
	{
		error_log("Cost_diamond_error");
		return R_ERROR;
	}

	newAct["a"][id-1] = newAct["a"][id-1].asUInt() + 1;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}

	vector<GiftEquipItem> reward;
	for (int i=0;i<XML_ZHOUNIANQING_YEARSHOP_REWARD_NUM;i++)
		reward.push_back(config.yearshop[id-1].reward[i]);
	basecmdUnit.AddGiftEquips(reward, code, result["equipment"],actconfig.EndTS()-Time::GetGlobalTime());

	result["newAct"] = newAct;
	user.Save();
	return 0;
}

int CLogicZhouNianQing::AddQuanFuQianDaoZhi(int version, int count)
{
	CDataZhouNianQingQianDao *pData = GetDataZhouNianQingQianDao();
	if (NULL == pData)
	{
		error_log("SetUser fail");
		return R_ERR_DATA;
	}

	pData->Add(version, count);
	return 0;
}

int CLogicZhouNianQing::online(unsigned uid, Json::Value & result)
{
	ActInfoConfig actconfig(CONFIG_ZHOUNIANQING_QIANDAO);
	if (actconfig.IsActive()) {
		Json::Value newAct;
		CLogicSecinc logicSecinc;
		int ret = logicSecinc.GetSecinc(uid,NAT_zhounianqing_qiandao,newAct);
		if (ret && ret!=R_ERR_NO_DATA)
			return ret;
		CDataXML *dataXML = CDataXML::GetCDataXML();
		DataXMLZhouNianQing config;
		ret = dataXML->GetZhouNianQingReward(config);
		if (ret)
		{
			return ret;
		}
		if (ret == R_ERR_NO_DATA || newAct["v"].asUInt()!=actconfig.Version())
		{
			newAct["id"] = NAT_zhounianqing_qiandao;
			newAct["v"] = actconfig.Version();
			//newAct["a"] = 0;//签到值
			newAct["b"] = 0;//庆典卷数量
			//newAct["c"] = Json::Value(Json::arrayValue);//签到值奖励领取
			//for (int i=0;i<GetSignNum(config);i++)
				//newAct["c"].append(0);
			newAct["ts"] = 0;
			//newAct["n"] = 0;//拉了多少个人
			//newAct["bd"] = 0;//绑定了哪个uid
		}
		if (CTime::IsDiffDay(newAct["ts"].asUInt(),Time::GetGlobalTime()))
		{
			newAct["ts"] = Time::GetGlobalTime();
			newAct["d"] = Json::Value(Json::arrayValue);//兑换
			for (int i=0;i<GetShopNum(config)-1;i++)//第一个无限制兑换，所以不计是否兑换过
				newAct["d"].append(0);
			newAct["s"]  = 0; //在线时长达标奖励领取状态（0：没领；1：领过）
		}
		else if (newAct["s"].asUInt())
		{
			return 0;
		}

		CLogicUser logicUser;
		DataUser dataUser;
		ret = logicUser.GetUserLimit(uid, dataUser);
		if (ret)
			return ret;

		if (CTime::GetDayInterval(dataUser.last_active_time, Time::GetGlobalTime()) == 0)
		{
			result["onlinets"] = dataUser.ext;
			//如果在线时长达标并且未领取
			if(dataUser.ext >= 30 && newAct["s"].asUInt() == 0)
			{
				//发奖励
				newAct["b"] = newAct["b"].asUInt() + config.juanCount;
				CActUnit ActUnit;
				ActUnit.Init(uid, CONFIG_ZHOUNIANQING_QIANDAO);
				string code = "zhounianqing_online";
				ret = ActUnit.ParseSimpleReward(config.online,MAX_ZHOUNIANQING_ONLINE_REWARD_NUM,code,actconfig.EndTS()-Time::GetGlobalTime());
				if (ret)
					return ret;
				result["equipment"] = ActUnit._equip;
				newAct["s"] = 1;  //将状态置1
			}
			else
			{
				PARAM_ERROR_RETURN_MSG("have recv or not enough time");
			}
		}
		else
		{
			PARAM_ERROR_RETURN_MSG("today not active");
		}

		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
		{
			LOGIC_ERROR_RETURN_MSG("set_secinc_error");
		}

		result["newAct"] = newAct;
	}

	return 0;
}

int CLogicZhouNianQing::GetSignNum(const DataXMLZhouNianQing & config)
{
	int non_zero = 0;
	for (int i=0;i<MAX_ZHOUNIANQING_SIGN_ITEM_NUM;i++)
		if (config.sign[i].id)
			non_zero++;
	return non_zero;
}

int CLogicZhouNianQing::GetShopNum(const DataXMLZhouNianQing & config)
{
	int non_zero = 0;
	for (int i=0;i<MAX_ZHOUNIANQING_SHOP_ITEM_NUM;i++)
		if (config.shop[i].id)
			non_zero++;
	return non_zero;
}

int CLogicZhouNianQing::GetYearShopNum(const DataXMLZhouNianQing & config)
{
	int non_zero = 0;
	for (int i=0;i<MAX_ZHOUNIANQING_SHOP_ITEM_NUM;i++)
		if (config.yearshop[i].id)
			non_zero++;
	return non_zero;
}
