/*
 * DataRiver.cpp
 *
 *  Created on: 2011-6-21
 *      Author: dada
 */

#include "DataRiver.h"

CDataRiver::CDataRiver() {
	m_init = false;
}

int CDataRiver::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(DataRiver),
			SEM_ID(sem,semgroup,semserver))) {
		error_log("[init_map_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if (!m_sh.HasInit()) {
		DataRiver *pTable = (DataRiver *) m_sh.GetAddress();
		memset(pTable, 0, sizeof(*pTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataRiver::AddShip(DataShip &ship, bool set)
{
	DataRiver *pTable = (DataRiver *) m_sh.GetAddress();
	if (pTable == NULL)
	{
		error_log("[map_set_user_fail][uid=%u]", ship.uid);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	for(unsigned i=0;i<pTable->count;++i)
	{
		if(pTable->Ships[i].uid == ship.uid)
		{
			if(set)
			{
				if(pTable->Ships[i].attack_num >= ship.attack_num)
					return R_ERR_LOGIC;

				pTable->Ships[i] = ship;
				return 0;
			}
			else
				return R_ERR_LOGIC;
		}
	}

	if(set)
		return R_ERR_LOGIC;

	if(pTable->count >= SHIP_USER_COUNT)
	{
		error_log("[overflow][uid=%u]", ship.uid);
		return R_ERR_DATA_LIMIT;
	}

	pTable->Ships[pTable->count] = ship;
	++pTable->count;

	return 0;
}

int CDataRiver::GetShips(vector<DataShip> &ships, vector<DataShip> &over) {
	DataRiver *pTable = (DataRiver *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[map_set_user_fail]");
		return R_ERR_DB;
	}

	unsigned now = Time::GetGlobalTime();

	CAutoLock lock(&m_sh, true);

	for(unsigned i=0;i<pTable->count;++i)
	{
		if (pTable->Ships[i].end_time <= now) {
			over.push_back(pTable->Ships[i]);

			pTable->Ships[i] = pTable->Ships[pTable->count-1];
			memset(&(pTable->Ships[pTable->count-1]),0,sizeof(DataShip));
			--pTable->count;
			continue;
		}else{
			if (pTable->Ships[i].uid)
				ships.push_back(pTable->Ships[i]);
			else{
				pTable->Ships[i] = pTable->Ships[pTable->count-1];
				memset(&(pTable->Ships[pTable->count-1]),0,sizeof(DataShip));
				--pTable->count;
				continue;
			}
		}
	}
	return 0;
}

int CDataRiver::GetOneShip(unsigned uid,DataShip &ship) {
	DataRiver *pTable = (DataRiver *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[map_set_user_fail][uid=%u]", uid);
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	for(unsigned i=0;i<pTable->count;++i)
	{
		if(pTable->Ships[i].uid == uid){
			ship = pTable->Ships[i];
			return 0;
		}
	}
	return R_ERR_NO_DATA;
}
