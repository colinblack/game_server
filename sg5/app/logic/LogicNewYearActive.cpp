/*
 * LogicNewYearActive.cpp
 *
 *  Created on: 2018年1月26日
 *      Author: Administrator
 */

#include "LogicNewYearActive.h"
#include "LogicUnitWrap.h"

CLogicNewYearActive::CLogicNewYearActive()
{
}

CLogicNewYearActive::~CLogicNewYearActive()
{
}

int CLogicNewYearActive::Visit(unsigned uid, unsigned userid, Json::Value &result)
{
	if (uid == userid)
	{
		error_log("uid error,uid=%u,userid=%u", uid, userid);
		return R_ERR_PARAM;
	}
	int serveridb;
	Config::GetDomain(serveridb);
	set<int> dbs;
	MainConfig::GetIncludeDomains(serveridb, dbs);
	unsigned attack_server = Config::GetZoneByUID(userid);
	if (!dbs.count(attack_server))
	{
		error_log("not_in_same_server uid=%u,userid=%u", uid, userid);
		LOGIC_ERROR_RETURN_MSG("not_in_same_server");
	}

	ActInfoConfig actconfig(CONFIG_NEWYEAR_ACTIVE);
	if (!actconfig.IsActive())
	{
		return R_ERR_LOGIC;
	}
	int ret = 0;
	Json::Value newAct;
	ret = getNewAct(uid, newAct);
	if (ret)
	{
		return ret;
	}

	ActivityConfigWrap actWrap;
	const ConfigActivity::HongBao &config = actWrap.GetHongBao();

	unsigned useCount = 0;
	Json::GetUInt(newAct, "c", useCount);
	if (useCount > config.count())
	{
		error_log("count error, uid=%u, use=%u, max=%u", uid, useCount, config.count());
		return R_ERR_LOGIC;
	}

	CDataNewYearActive *pdata = GetData();
	if (pdata == NULL)
	{
		error_log("get data error!");
		return R_ERR_DATA;
	}
	Json::Value otherNewAct;
	ret = getNewAct(userid, otherNewAct);
	if (ret)
	{
		return ret;
	}
	unsigned type = 0;
	Json::GetUInt(otherNewAct, "t", type);
	unsigned eqid = 0, eqcount = 0;
	ret = getEquipReward(type, eqid, eqcount);
	if (ret)
	{
		error_log("getEquipReward error, ret=%d,uid=%u", ret, uid);
		return ret;
	}
	bool can = true;
	ret = pdata->AddInfo(uid, userid, type, eqid, eqcount, can);
	if (ret)
	{
		error_log("get data error! uid=%u, userid=%u", uid, userid);
		return ret;
	}

	if (!can)
	{
		result["newAct"] = newAct;
		result["can"] = 0;
		return 0;
	}

	newAct["c"] = useCount + 1;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}
	result["newAct"] = newAct;
	result["can"] = 1;

	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, eqid, eqcount, "newyearactive_"+CTrans::ITOS(type), result["equipment"], true);
	if (ret)
	{
		return ret;
	}
	string code = "newyearactive_baifang_" + CTrans::ITOS(userid);
	ORDERS_LOG("uid=%u&code=%s&price=1&amount=1&type=3", uid, code.c_str());
	return 0;
}

int CLogicNewYearActive::GetInfo(unsigned uid, unsigned userid, Json::Value &result)
{
	int ret = 0;
	CDataNewYearActive *pdata = GetData();
	if (pdata == NULL)
	{
		error_log("get data error!");
		return R_ERR_DATA;
	}
	ret = pdata->GetRank(result["rank"]);
	if (ret)
	{
		error_log("get rank error,uid=%u,ret=%d", uid, ret);
		return ret;
	}
	ret = pdata->GetLastHistory(result["last"]);
	if (ret)
	{
		error_log("get last items error,uid=%u,ret=%d", uid, ret);
		return ret;
	}
	bool can = true;
	ret = pdata->GetUserHistory(uid, userid, can, result["history"]);
	if (ret)
	{
		error_log("get history error,uid=%u,ret=%d", uid, ret);
		return ret;
	}
	result["can"] = can ? 1 : 0;
	ret = getNewAct(uid, result["newAct"]);
	if (ret)
	{
		return ret;
	}
	result["totalCharge"] = 0;
	if (uid == userid)
	{
		ActInfoConfig actconfig(CONFIG_NEWYEAR_ACTIVE);
		UserWrap userWrap(uid, false);
		result["totalCharge"] = userWrap.GetRechargePoint(actconfig.StartTS(), actconfig.EndTS());
	}
	return 0;
}

int CLogicNewYearActive::Refresh(unsigned uid, Json::Value &result)
{
	int ret = 0;
	Json::Value newAct;
	ret = getNewAct(uid, newAct);
	if (ret)
	{
		return ret;
	}
	ActivityConfigWrap actWrap;
	const ConfigActivity::HongBao &config = actWrap.GetHongBao();
	unsigned refresh_count = 0;
	Json::GetUInt(newAct, "r", refresh_count);

	bool buy = false;
	unsigned price = 0;
	if (refresh_count >= config.refresh_free())
	{
		ActInfoConfig actconfig(CONFIG_NEWYEAR_ACTIVE);
		UserWrap userWrap(uid, false);
		unsigned point = userWrap.GetRechargePoint(actconfig.StartTS(), actconfig.EndTS());
		unsigned use_point = 0;
		Json::GetUInt(newAct, "u", use_point);
		if (use_point + config.refresh_cost() > point)
		{
			error_log("point error udi=%u point=%u,use=%u,need=%u", point, uid, use_point, config.refresh_cost());
			return R_ERR_LOGIC;
		}
		newAct["u"] = use_point + config.refresh_cost();
		price = config.refresh_cost();
		buy = true;
	}

	newAct["t"] = randomType(buy);
	newAct["r"] = refresh_count + 1;

	CLogicSecinc logicSecinc;
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
	{
		return ret;
	}
	result["newAct"] = newAct;
	string code = "newyearactiverefresh_" + CTrans::ITOS(refresh_count + 1);
	ORDERS_LOG("uid=%u&code=%s&price=%u&amount=1&type=3", uid, code.c_str(), price);
	return 0;
}

int CLogicNewYearActive::getNewAct(unsigned uid, Json::Value & newAct)
{
	int ret = 0;
	CLogicSecinc logicSecinc;
	unsigned sid = NAT_NEWYEAR_ACTIVE;
	ret = logicSecinc.GetSecinc(uid, sid, newAct);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		return ret;
	}

	unsigned ts = 0;
	Json::GetUInt(newAct, "ts", ts);
	if (CTime::IsDiffDay(ts, Time::GetGlobalTime()))
	{
		newAct["id"] = sid;
		newAct["ts"] = Time::GetGlobalTime();
		newAct["t"] = 0;
		newAct["c"] = 0;
		newAct["r"] = 0;
	}
	if (ret == R_ERR_NO_DATA)
	{
		newAct["u"] = 0;
	}
	unsigned old_version = 0;
	Json::GetUInt(newAct, "v", old_version);
	ActInfoConfig actconfig(CONFIG_NEWYEAR_ACTIVE);
	if (old_version != actconfig.Version())
	{
		newAct["v"] = actconfig.Version();
		newAct["u"] = 0;
	}
	return 0;
}

int CLogicNewYearActive::randomType(bool buy)
{
	ActivityConfigWrap actWrap;
	const ConfigActivity::HongBao &config = actWrap.GetHongBao();
	vector<int> rates;
	int rate = 0;
	for (size_t i = 0; i < config.item_size(); ++i)
	{
		if (buy)
		{
			rate += config.item(i).rate_buy();
		}
		else
		{
			rate += config.item(i).rate_free();
		}
		rates.push_back(rate);
	}
	if (rates.empty())
	{
		return 0;
	}
	int max_rate = *(rates.rbegin());
	int r = Math::GetRandomInt(max_rate ? max_rate : 1);
	for (size_t i = 0; i < rates.size(); ++i)
	{
		if (r <= rates[i])
		{
			return i;
		}
	}
	return 0;
}

int CLogicNewYearActive::getEquipReward(unsigned type, unsigned &equid, unsigned &count)
{
	ActivityConfigWrap actWrap;
	const ConfigActivity::HongBao &config = actWrap.GetHongBao();
	if (type < config.item_size() && config.item(type).reward().equips_size() > 0)
	{
		unsigned giftbagId = config.item(type).reward().equips(0).eqid();
		unsigned eqcount = config.item(type).reward().equips(0).c();

		CDataXML *pDataXML = CDataXML::GetCDataXML();
		if(!pDataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}
		Json::Value data;
		data.clear();
		int ret = pDataXML->GetGiftBag(0, giftbagId, eqcount, data);
		if(ret)
		{
			error_log("GetGiftBag error,giftbagId=%u", giftbagId);
			return R_ERR_DATA;
		}
		for(size_t i = 0; i < data.size(); ++i)
		{
			Json::Value::Members members(data[i].getMemberNames());
			for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
			{
				string type = *it;
				if(type.find("equip") != string::npos)
				{
					equid = data[i][type]["id"].asUInt();
					count = data[i][type]["c"].asUInt();
					break;
				}
			}
		}
		return R_SUCCESS;
	}
	return R_ERR_DATA;
}
