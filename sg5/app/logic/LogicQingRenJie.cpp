/*
 * LogicAllianceConsume.cpp
 *
 *  Created on: 2017-3-15
 *      Author: Ralf
 */

#include "LogicQingRenJie.h"
#include "LogicCmdBase.h"

int CLogicQingRenJie::QingRenJieXianHua(unsigned uid, unsigned nsid, unsigned type, unsigned num, Json::Value &result)
{
	if (nsid < 1 || nsid > 7)
	{
		PARAM_ERROR_RETURN_MSG("nsid");
	}
	if (type != 1 && type != 2)
	{
		PARAM_ERROR_RETURN_MSG("type");
	}

	ActInfoConfig actconfig(CONFIG_QINGRENJIE_MEIGUI);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLQingRenJieMeiGui config;
	int ret = dataXML->GetQingRenJieMeiGuitem(config);
	if (ret)
	{
		return ret;
	}
	Json::Value newact;
	CLogicSecinc logicsecinc;
	ret = logicsecinc.GetSecinc(uid, NAT_QINGRENJIE_MEIGUI, newact);
	if (ret == R_ERR_NO_DATA || newact["v"].asUInt() != actconfig.Version())
	{
		newact["id"] = NAT_QINGRENJIE_MEIGUI;
		newact["v"] =  actconfig.Version();
		newact["al"] = 0;
		newact["a"] = Json::Value(Json::arrayValue);
		for (int i=0;i<XML_QINGRENJIE_LEIJI_NUM;i++)
			newact["a"].append(0);
	}
	if (!Time::IsToday(newact["t"].asUInt()))
	{
		newact["t"] = Time::GetGlobalTime();
		newact["mg"] = 0;
	}
	if (type == 1) {
		if (newact["mg"].asUInt() + num > 22)
		{
			LOGIC_ERROR_RETURN_MSG("mg limit");
		}
		newact["mg"] = newact["mg"].asUInt() + num;
		newact["al"] = newact["al"].asUInt() + num;
	}
	else {
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -7*num, 0, payData, "QingRenJieXianHua",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
		newact["al"] = newact["al"].asUInt() + num;
	}

	ret = logicsecinc.SetOneSecinc(uid, newact);
	if(ret)
		return ret;


	CDataQingRenJie *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->SongHua(uid, nsid, num, result);
	if(ret)
		return ret;

	vector<GiftEquipItem> reward;
	string code = "QingRenJieXianHua";
	BaseCmdUnit basecmdUnit(uid);

	for (int i=0;i<XML_QINGRENJIE_MEIGUI_REWARD_NUM;i++)
		reward.push_back(config.meigui[nsid-1].reward[i]);
	for (vector<GiftEquipItem>::iterator it = reward.begin(); it!=reward.end(); ++it)
		it->m_nCnt *= num;
	basecmdUnit.AddGiftEquips(reward, code, result["equipment"]);

	return 0;
}

int CLogicQingRenJie::QingRenJieLeiJi(unsigned uid, unsigned id, Json::Value &result)
{
	if (id < 1 || id > XML_QINGRENJIE_LEIJI_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}

	ActInfoConfig actconfig(CONFIG_QINGRENJIE_MEIGUI);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	DataXMLQingRenJieMeiGui config;
	int ret = dataXML->GetQingRenJieMeiGuitem(config);
	if (ret)
	{
		return ret;
	}

	Json::Value newact;
	CLogicSecinc logicsecinc;
	ret = logicsecinc.GetSecinc(uid, NAT_QINGRENJIE_MEIGUI, newact);

	if (newact["al"].asUInt() < config.leiji[id-1].require)
	{
		LOGIC_ERROR_RETURN_MSG("require not archive");
	}

	if (newact["a"][id-1].asUInt())
	{
		LOGIC_ERROR_RETURN_MSG("require has got");
	}

	newact["a"][id-1] = 1;

	ret = logicsecinc.SetOneSecinc(uid, newact);
	if(ret)
		return ret;

	vector<GiftEquipItem> reward;
	string code = "QingRenJieLeiJi";
	BaseCmdUnit basecmdUnit(uid);

	for (int i=0;i<XML_QINGRENJIE_MEIGUI_REWARD_NUM;i++)
		reward.push_back(config.leiji[id-1].reward[i]);
	basecmdUnit.AddGiftEquips(reward, code, result["equipment"]);
	return 0;
}

int CLogicQingRenJie::GetQingRenJie(Json::Value &result)
{
	CDataQingRenJie *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetInfo(result);
	if(ret)
		return ret;

	return 0;
}


