/*
 * DataAllianceConsume.cpp
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */


#include "DataAllianceConsume.h"
#include "ConfigManager.h"
#include "LogicEquipment.h"
#include "LogicSecinc.h"
#include "LogicPay.h"

CDataAllianceConsume::CDataAllianceConsume(string path)
	: DataBase(path)
{
	m_msg = new AllianceConsume::AllianceConsume();
}

int CDataAllianceConsume::Init()
{
	int ret = Parse();
	if(ret && ret != R_ERR_NO_DATA)
		return ret;

	if(ret != R_ERR_NO_DATA)
	{
		m_data.Parse(*(AllianceConsume::AllianceConsume *)m_msg);

		if(m_data.ver != Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER))
		{
			m_data.ver = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
			m_data.alliance.clear();
		}
	}

	((AllianceConsume::AllianceConsume *)m_msg)->Clear();

	return 0;
}
int CDataAllianceConsume::Save()
{
	m_data.Serialize((AllianceConsume::AllianceConsume *)m_msg);

	int ret = Serialize();

	((AllianceConsume::AllianceConsume *)m_msg)->Clear();

	return ret;
}

int CDataAllianceConsume::AllianceShopInfo(unsigned aid, Json::Value &result)
{
	if(aid == 0)
		return R_ERR_PARAM;

	m_data.GetJson(aid, result);
	return 0;
}
int CDataAllianceConsume::AllianceShopBuy(unsigned uid, unsigned aid, unsigned index, unsigned count, Json::Value &result)
{
	if(aid == 0)
		return R_ERR_PARAM;

	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_END_TS))
		return R_ERR_PARAM;

	if(index >= ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.a_size())
		return R_ERR_PARAM;
	const AllianceConsumeConfig::AllianceConsumeConfigItem& config = ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.a(index);

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	CLogicEquipment loigcEquipment;
	AUTO_LOCK_USER(uid)

	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	reader.parse(dataUser.user_flag,user_flag);

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ALLIANCE_CONSUME, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ALLIANCE_CONSUME;
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER) != newAct["v"].asInt())
	{
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}

	ret = logicPay.ProcessOrderForBackend(uid, -(config.price()*count), 0, payData, "AllianceShopBuy",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = loigcEquipment.AddOneItem(uid, config.eqid(), count*config.count(), "AllianceShopBuy", result["equip"], true);
	if(ret)
		return ret;

	m_data.Add(aid, uid, config.price()*count);
	m_data.GetJson(aid, result);

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;
	result["newAct"] = newAct;
	return 0;
}
int CDataAllianceConsume::AllianceShopLimit(unsigned uid, unsigned aid, unsigned type, unsigned index, unsigned count, Json::Value &result)
{
	if(aid == 0)
		return R_ERR_PARAM;

	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_END_TS))
		return R_ERR_PARAM;

	bool f = false;
	switch(type)
	{
	case 1:
		f = m_data.Check(aid, 5, 100) && index < ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.b_size();
		break;
	case 2:
		f = m_data.Check(aid, 10, 100) && index < ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.c_size();
		break;
	case 3:
		f = m_data.Check(aid, 15, 100) && index < ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.d_size();
		break;
	default:
		break;
	}
	if(!f)
		return R_ERR_LOGIC;

	const AllianceConsumeConfig::AllianceConsumeConfigItemLimit& config =
			type == 1 ? ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.b(index)
					: (type == 2 ? ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.c(index)
					: ConfigManager::Instance()->m_AllianceConsumeConfig.m_config.d(index));

	int ret;
	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	CLogicEquipment loigcEquipment;
	AUTO_LOCK_USER(uid)

	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	reader.parse(dataUser.user_flag,user_flag);

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ALLIANCE_CONSUME, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ALLIANCE_CONSUME;
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER) != newAct["v"].asInt())
	{
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}
	Json::Value& t = type == 1 ? newAct["b"] : (type == 2 ? newAct["c"] : newAct["d"]);
	if(t[index].asUInt() + count > config.limit())
		return R_ERR_LOGIC;
	t[index] = t[index].asUInt() + count;

	ret = logicPay.ProcessOrderForBackend(uid, -(config.price()*count), 0, payData, "AllianceShopLimit",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = loigcEquipment.AddOneItem(uid, config.eqid(), count*config.count(), "AllianceShopLimit", result["equip"], true);
	if(ret)
		return ret;

	m_data.Add(aid, uid, config.price()*count);
	m_data.GetJson(aid, result);

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;
	result["newAct"] = newAct;
	return 0;
}
int CDataAllianceConsume::AllianceShopGift(unsigned uid, unsigned aid, unsigned index, Json::Value &result)
{
	if(aid == 0)
		return R_ERR_PARAM;

	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_BEGIN_TS)
	|| Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_END_TS))
		return R_ERR_PARAM;

	bool f = false;
	unsigned eqid = 0;
	switch(index)
	{
	case 0:
		f = m_data.Check(aid, 5, 300);
		eqid = 58001;
		break;
	case 1:
		f = m_data.Check(aid, 10, 300);
		eqid = 58002;
		break;
	case 2:
		f = m_data.Check(aid, 15, 300);
		eqid = 58003;
		break;
	case 3:
		f = m_data.Check(aid, 30, 300);
		eqid = 58004;
		break;
	case 4:
		f = m_data.Check(aid, 45, 300);
		eqid = 58005;
		break;
	default:
		break;
	}
	if(!f)
		return R_ERR_LOGIC;

	int ret;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	CLogicEquipment loigcEquipment;
	AUTO_LOCK_USER(uid)

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	ret = logicSecinc.GetSecinc(uid, NAT_ALLIANCE_CONSUME, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = NAT_ALLIANCE_CONSUME;
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}
	else if(ret)
		return ret;
	if(Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER) != newAct["v"].asInt())
	{
		newAct["a"].resize(0);
		for(unsigned i=0;i<5;++i)
			newAct["a"].append(0);
		newAct["b"].resize(0);
		newAct["c"].resize(0);
		newAct["d"].resize(0);
		for(unsigned i=0;i<4;++i)
		{
			newAct["b"].append(0);
			newAct["c"].append(0);
			newAct["d"].append(0);
		}
		newAct["v"] = Config::GetIntValue(CONFIG_ALLIANCE_CONSUME_VER);
	}
	if(newAct["a"][index].asUInt())
		return R_ERR_LOGIC;
	newAct["a"][index] = 1;

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if(ret)
		return ret;

	ret = loigcEquipment.AddOneItem(uid, eqid, 1, "AllianceShopGift", result["equip"], true);
	if(ret)
		return ret;

	result["newAct"] = newAct;
	return 0;
}
