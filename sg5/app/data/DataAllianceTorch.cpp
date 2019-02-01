/*
 * DataAllianceTorch.cpp
 *
 *  Created on: 2016-05-18
 *      Author: zkw
 */

#include "DataAllianceTorch.h"
#include <fstream>
#include <iostream>


CDataAllianceTorch::CDataAllianceTorch(string path)
	: DataBase(path)
{
	m_msg = new AllianceTorch::AllianceTorch();
}

int CDataAllianceTorch::Init()
{
	int ret = Parse();
	if(ret)
		return ret;

	m_data.Parse(*(AllianceTorch::AllianceTorch *)m_msg);

	((AllianceTorch::AllianceTorch *)m_msg)->Clear();

	return 0;
}

int CDataAllianceTorch::Save()
{
	m_data.Serialize((AllianceTorch::AllianceTorch *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//debug_log("%s",m_msg->DebugString().c_str());

	((AllianceTorch::AllianceTorch *)m_msg)->Clear();

	return 0;
}

int CDataAllianceTorch::GetAllianceTorchCurrStatus(unsigned aid_new, map<unsigned int, DataCurrTorchStatus> &datas)
{
	return m_data.GetAllianceTorchCurrStatus(aid_new, datas);
}

int CDataAllianceTorch::BurnAllianceTorch(unsigned aid_new, unsigned uid_new, unsigned time_new, unsigned tid_new, map<unsigned int, DataCurrTorchStatus> &datas)
{
	if(!IsAllianceId(aid_new))
		return R_ERR_PARAM;

	return m_data.BurnAllianceTorch(aid_new, uid_new, time_new, tid_new, datas);
}

int CDataAllianceTorch::GetAllianceTorchBuyLog(unsigned aid_new, map<unsigned int, DataLogBuyRecord> &datas)
{
	if(!IsAllianceId(aid_new))
		return R_ERR_PARAM;

	return m_data.GetAllianceTorchBuyLog(aid_new, datas);
}


