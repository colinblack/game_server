/*
 * DataVipRebates.cpp
 *
 *  Created on: 2014年7月15日
 *      Author: Administrator
 */

#include "DataVipRebates.h"

CDataVipRebates::CDataVipRebates()
{
	m_init = false;
}

int CDataVipRebates::Init(const string &path, semdat sem){
	if(m_init)
	{
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(VipRebatesData), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_vip_rebates_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		VipRebatesData *pdata = (VipRebatesData *)m_sh.GetAddress();
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}


int CDataVipRebates::getVips(uint32_t viplvl, vector<VipUser> &rlt){
	VipRebatesData *pdata = (VipRebatesData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);

	for(size_t i = 0; i < VIP_LEVEL_COUNT; ++i) {
		if(pdata->vips[i].viplvl == viplvl) {
			rlt = pdata->vips[i].getVipUsers();
			return 0;
		}
	}
	return R_ERR_PARAM;
}


// [fromLvl,toLvl] 闭区间
int CDataVipRebates::setVip(uint32_t uid, const string &name, uint32_t fromLvl, uint32_t toLvl){
	bool flag = toLvl >= fromLvl;
		flag &= toLvl >= 6;

	if(!flag) {
		return R_ERR_PARAM;
	}

	// vip从6级开始
	if(fromLvl < 6) {
		fromLvl = 6;
	}


	VipRebatesData *pdata = (VipRebatesData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	pdata->updateTime = time(NULL);
	for(uint32_t level = fromLvl; level <= toLvl; ++level) {
		bool isAppend = false;
		for(size_t i = 0; i < VIP_LEVEL_COUNT; ++i) {
			VipUser user;
			user.uid = uid;
			sprintf(user.name, "%s", name.c_str());
			if(pdata->vips[i].viplvl == level) {
				pdata->vips[i].append(user);
				isAppend = true;
				break;
			}

			if(pdata->vips[i].viplvl == 0) {
				pdata->vips[i].viplvl = level;
				pdata->vips[i].append(user);
				isAppend = true;
				break;
			}
		}

		if(!isAppend) {
			return R_ERR_PARAM;
		}
	}
	return 0;
}


uint32_t CDataVipRebates::getTime(){
	VipRebatesData *pdata = (VipRebatesData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	return pdata->updateTime;
}

int CDataVipRebates::clear(){
	VipRebatesData *pdata = (VipRebatesData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);
	memset(pdata, 0, sizeof(VipRebatesData));
	for(size_t i = 0; i < VIP_LEVEL_COUNT; ++i) {
		pdata->vips[i].viplvl = VIP_LEVEL_COUNT + i + 1;	// 从6级开始
	}
	return 0;
}
