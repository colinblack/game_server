/*
 * LogicBraveNewWorld.cpp
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */


#include "LogicBraveNewWorld.h"

int CLogicBraveNewWorld::GetSelf(unsigned uid, unsigned aid, unsigned lv, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetSelf(uid, aid, lv, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetMissionInfo(unsigned uid, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetMissionInfo(uid, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetPoints(vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetPoints(p, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetOnePoint(BraveNewWorldPoint& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetOnePoint(p, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetPointsLimit(vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetPointsLimit(p, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetZones(vector<unsigned>& z, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetZones(z, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetHistory(unsigned uid, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetHistory(uid, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::GetFavourate(unsigned uid, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetFavourate(uid, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::Collect(unsigned uid, unsigned seq, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Collect(uid, seq, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::StartAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->StartAttack(uid, seq, p , cash, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::EndAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, vector<unsigned>& hp, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->EndAttack(uid, seq, p, hp, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::FastAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, bool cash1, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->FastAttack(uid, seq, p, cash, cash1, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::Move(unsigned uid, unsigned seq, BraveNewWorldPoint& p, unsigned ud, bool super, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Move(uid, seq, p, ud, super, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::Build(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Build(uid, seq, cash, p, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::Defend(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, unsigned hero, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Defend(uid, seq, cash, p, hero, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::RecoverPoint(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->RecoverPoint(uid, seq, p, cash, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::RevcoverUser(unsigned uid, unsigned seq, bool cash, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->RevcoverUser(uid, seq, cash, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::Discard(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Discard(uid, seq, p, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::JoinAlliance(unsigned uid, unsigned userid, unsigned aid, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->JoinAlliance(uid, userid, aid, result);
	if(ret)
		return ret;

	return 0;
}
int CLogicBraveNewWorld::SetFavourate(unsigned uid, unsigned seq, vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->SetFavourate(uid, seq, p, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::Buy_hts(unsigned uid, unsigned seq, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Buy_hts(uid, seq, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::Buy_bts(unsigned uid, unsigned seq, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Buy_bts(uid, seq, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::Buy_bt(unsigned uid, unsigned seq, unsigned count, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->Buy_bt(uid, seq, count, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::CollectOne(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->CollectOne(uid, seq, p, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::AttackSelf(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->AttackSelf(uid, seq, p, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::GetMission(unsigned uid, unsigned seq, unsigned type, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetMission(uid, seq, type, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::newWorldAwards(unsigned uid, unsigned index, unsigned id, unsigned seq, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->newWorldAwards(uid,index,id,seq,result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::GetTarget(unsigned uid, unsigned userid, Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

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
	ret = logicPay.ProcessOrderForBackend(uid, -20, 0, payData, "CLogicBraveNewWorld_GetTarget",user_flag,bsave);
	if(ret)
		return ret;
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	ret = pData->GetTarget(userid, result);
	if(ret)
		return ret;

	return 0;
}

int CLogicBraveNewWorld::getNewWorldBoss(Json::Value &result)
{
	CDataBraveNewWorld *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	int ret = pData->getNewWorldBoss(result["list"]);
	if(ret)
		return ret;

	return 0;
}
