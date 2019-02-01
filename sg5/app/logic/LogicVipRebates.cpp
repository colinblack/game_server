/*
 * LogicVipRebates.cpp
 *
 *  Created on: 2014年7月15日
 *      Author: Administrator
 */

#include "LogicVipRebates.h"

CDataVipRebates* CLogicVipRebates::GetCDataVipRebates(){
	GET_MEM_DATA_SEM(CDataVipRebates, CONFIG_VIP_REBATES, sem_viprebates,false)
};

int CLogicVipRebates::getVips(uint32_t viplvl, vector<VipUser> &rlt){
	CDataVipRebates *pdata = GetCDataVipRebates();
	return pdata->getVips(viplvl, rlt);
}

int CLogicVipRebates::setVip(uint32_t uid, const string &name, uint32_t fromLvl, uint32_t toLvl) {
	CDataVipRebates *pdata = GetCDataVipRebates();
	return pdata->setVip(uid, name, fromLvl, toLvl);
}

uint32_t CLogicVipRebates::getTime() {
	CDataVipRebates *pdata = GetCDataVipRebates();
	return pdata->getTime();
}

int CLogicVipRebates::clear() {
	CDataVipRebates *pdata = GetCDataVipRebates();
	pdata->clear();
	return 0;
}
