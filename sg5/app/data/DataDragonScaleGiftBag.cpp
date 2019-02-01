/*
 * DataDragonScaleGiftBag.cpp
 *
 *  Created on: 2015-06-16
 *      Author: eddard
 */

#include "DataDragonScaleGiftBag.h"
#include "DataUserBasic.h"

#define MAGIC_NUM_B		8954

CDataDragonScaleGiftBag::CDataDragonScaleGiftBag(){
	m_init = false;
}
CDataDragonScaleGiftBag::~CDataDragonScaleGiftBag() {

}

int CDataDragonScaleGiftBag::Init(const std::string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataDragonScaleGiftBag), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_datanewlottery_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataDragonScaleGiftBag *pdata = (DataDragonScaleGiftBag *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_data_dragonScaleGiftBag_data_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataDragonScaleGiftBag::GetGiftBag(unsigned uid, Json::Value &winners, int &count, bool &succ)
{
	DataDragonScaleGiftBag *pdata = (DataDragonScaleGiftBag *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_data_dragonScaleGiftBag_data_fail");
	}
	CAutoLock lock(&m_sh, true);
	if(Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER) != pdata->version)
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
		pdata->count = 0;
	}

	if (pdata->count >= GIFT_BAG_MAX)
	{
		count = pdata->count;
		succ = false;
	}
	else
	{
		int rate = Math::GetRandomInt(10000);
		if (MAGIC_NUM_B == rate)
		{
			//抽中礼包
			pdata->count += 1;
			count = pdata->count;
			succ = true;

			DataUserBasic dataUserBasic;
			CDataUserBasic dbUserBasic;
			int ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, dataUserBasic);
			if (ret != 0)
			{
				error_log("[GetUserBasicLimit fail][ret=%d,uid=%u]", ret, uid);
				DB_ERROR_RETURN_MSG("db_get_uesr_basic_fail");
			}
			memcpy(pdata->winners[pdata->count-1].name,dataUserBasic.name.c_str(),sizeof(pdata->winners[pdata->count].name) - 1);
			pdata->winners[pdata->count-1].uid= uid;
		}
		else
		{
			count = pdata->count;
			succ = false;
		}
	}

	winners = Json::Value(Json::arrayValue);
	Json::Value winner;
	for (int i = 0; i < pdata->count; i++)
	{
		winner["uid"] = pdata->winners[i].uid;
		winner["name"] = pdata->winners[i].name;
		winners.append(winner);
	}

	return R_SUCCESS;
}

int CDataDragonScaleGiftBag::GetData(unsigned uid, Json::Value &winners, unsigned &count)
{
	DataDragonScaleGiftBag *pdata = (DataDragonScaleGiftBag *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_data_dragonScaleGiftBag_data_fail");
	}
	CAutoLock lock(&m_sh, true);

	count = pdata->count;
	winners = Json::Value(Json::arrayValue);
	Json::Value winner;
	for (int i = 0; i < pdata->count; i++)
	{
		winner["uid"] = pdata->winners[i].uid;
		winner["name"] = pdata->winners[i].name;
		winners.append(winner);
	}

	return R_SUCCESS;
}
