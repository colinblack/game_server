/*
 * LogicAllianceTorch.cpp
 *
 *  Created on: 2016-05-18
 *      Author: zkw
 */

#include "LogicAllianceTorch.h"
#include <math.h>

const int ALLIANCE_TORCH_ADD_POINT[3] = {1200, 400, 2000};
const int ALLIANCE_TORCH_CASH[3] = {300, 100, 500};


int CLogicAllianceTorch::checkLastSaveUID(DataUser &user)
{
	if (IsBeingAttacked(user.last_breath_time))
	{
		//error_log("[being_attacked][uid=%u,last_breath_time=%u]",user.uid,user.last_breath_time);
		LOGIC_ERROR_RETURN_MSG("u_being_attacked");
	}
	if(user.last_save_uid != user.uid)
	{
		error_log("[last_save_uid_mismatch][operator=%u,user_last_save_uid=%u]",user.uid, user.last_save_uid);
		LOGIC_ERROR_RETURN_MSG("last_save_uid_mismatch");
	}
	return R_SUCCESS;
}


int CLogicAllianceTorch::checkLastSaveTime(DataUser &user,unsigned lasttime,unsigned seqid)
{
	if (lasttime != user.last_save_time || seqid != user.lastseq + 1)
	{
		error_log("[lasttime_mismatch][operator=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
			user.uid, lasttime, user.last_save_time, seqid, user.lastseq);
		LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
	}
	user.last_save_time = Time::GetGlobalTime();
	user.lastseq = seqid;
	return R_SUCCESS;
}


int CLogicAllianceTorch::GetAllianceTorchCurrStatus(unsigned aid, Json::Value &result)
{
	CDataAllianceTorch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	map<unsigned int, DataCurrTorchStatus> datas;
	datas.clear();
	int ret = pData->GetAllianceTorchCurrStatus(aid, datas);
	if(ret)
		return ret;
	if (!datas.size())   //当alliance map里没有该联盟的记录时
	{
		DataCurrTorchStatus temp;
		for(unsigned ix = 0; ix < 3; ++ix)
		{
			datas[ix] = temp;
			datas[ix].ResetTorch(ix);
		}
	}

	CLogicUserBasic logicUserBasic;
	string name;
	for (map<unsigned int, DataCurrTorchStatus>::iterator iter = datas.begin(); iter != datas.end(); ++iter)
	{
		result["torch"][iter->first]["tid"] = (iter->second).tid;
		result["torch"][iter->first]["status"] = (iter->second).status;
		result["torch"][iter->first]["ts"] = (iter->second).ts;
		result["torch"][iter->first]["uid"] = (iter->second).uid;
		name = "";
		if ((iter->second).uid)
		{
			ret = logicUserBasic.GetName((iter->second).uid, name);
			if (ret)
				return ret;
		}
		result["torch"][iter->first]["name"] = name;
	}

	return 0;
}


int CLogicAllianceTorch::BurnAllianceTorch(unsigned aid, unsigned uid, unsigned torch_type, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	//逻辑判断，是否已经点燃
	CDataAllianceTorch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}
	map<unsigned int, DataCurrTorchStatus> datas;
	datas.clear();
	int ret = pData->GetAllianceTorchCurrStatus(aid, datas);
	if(ret)
		return ret;
	if (datas.count(torch_type) && datas[torch_type].GetTorchStatus(torch_type))
	{
		error_log("alliance torch has been burned, [aid=%u],[uid=%u],[torch_type=%u]", aid, uid, torch_type);
		return R_ERR_LOGIC;
	}

	AUTO_LOCK_USER(uid)
	CLogicUser logicUser;
	DataUser dataUser;
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log("get_user_info_failed,uid = %u",uid);
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

	//扣钱
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	reader.parse(dataUser.user_flag,user_flag);
	CLogicPay logicPay;
	DataPay payData;
	bool bsave = false;
	ret = logicPay.ProcessOrderForBackend(uid, -ALLIANCE_TORCH_CASH[torch_type], 0, payData, "alliance_torch_buy",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins2"] = payData.cash;

	//添加火炬
	unsigned ts = Time::GetGlobalTime();
	datas.clear();
	ret = pData->BurnAllianceTorch(aid, uid, ts, torch_type, datas);
	if(ret)
		return ret;
	if (!datas.size())
	{
		error_log("alliance must have one torch, [aid=%u],[uid=%u],[torch_type=%u]", aid, uid, torch_type);
		return R_ERR_LOGIC;
	}

	CLogicUserBasic logicUserBasic;
	string name;
	for (map<unsigned int, DataCurrTorchStatus>::iterator iter = datas.begin(); iter != datas.end(); ++iter)
	{
		result["torch"][iter->first]["tid"] = (iter->second).tid;
		result["torch"][iter->first]["status"] = (iter->second).status;
		result["torch"][iter->first]["uid"] = (iter->second).uid;
		result["torch"][iter->first]["ts"] = (iter->second).ts;
		name = "";
		if ((iter->second).uid)
		{
			ret = logicUserBasic.GetName((iter->second).uid, name);
			if (ret)
				return ret;
		}
		result["torch"][iter->first]["name"] = name;
	}

	//添加联盟贡献
	CLogicAlliance logicAlliance;
	unsigned point = ALLIANCE_TORCH_ADD_POINT[torch_type];
	ret  = logicAlliance.AddPoint(aid, uid, point);
	if (ret)
	{
		return ret;
	}

	DataAllianceMember allianceMemberDB;
	ret = logicAlliance.GetMember(aid, uid, allianceMemberDB);
	if(ret == 0)
	{
		result["alliance_point"] = (unsigned)allianceMemberDB.curr_point;
	}

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}


int CLogicAllianceTorch::GetAllianceTorchBuyLog(unsigned aid, Json::Value &result)
{
	CDataAllianceTorch *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	map<unsigned int, DataLogBuyRecord> datas;
	datas.clear();
	int ret = pData->GetAllianceTorchBuyLog(aid, datas);
	if(ret)
		return ret;
	if (!datas.size())
	{
		return R_SUCCESS;
	}

	CLogicUserBasic logicUserBasic;
	string name;
	unsigned temp_index = 0;
	for (map<unsigned int, DataLogBuyRecord>::iterator iter = datas.begin(); iter != datas.end(); ++iter)
	{
		result["log"][temp_index]["time"] = (iter->second).time;
		result["log"][temp_index]["tid"] = (iter->second).tid;
		result["log"][temp_index]["uid"] = (iter->second).uid;
		name = "";
		if ((iter->second).uid)
		{
			ret = logicUserBasic.GetName((iter->second).uid, name);
			if (ret)
				return ret;
		}
		result["log"][temp_index]["name"] = name;
		++temp_index;
	}
	return R_SUCCESS;
}
