/*
 * DataRechargeRank.cpp
 *
 *  RReated on: 2015-7-28
 *      Author: Ralf
 */

#include "DataRechargeRank.h"
#include "LogicInc.h"

#define RECHARGE_LOW_LIMIT 500

CDataRechargeRank::CDataRechargeRank() {
	m_init = false;
}
CDataRechargeRank:: ~CDataRechargeRank(){

}

int CDataRechargeRank::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	int zoneId = 0;
	for (; zoneId < RR_ZONE_NUM; zoneId++)
	{
		string mapfile = path;
		if (path[path.length() - 1] != '/')
			mapfile.append("/");
		mapfile.append(CTrans::ITOS(zoneId)).append(".rechargeRank");
		if (!m_sh[zoneId].CreateOrOpen(mapfile.c_str(), sizeof(DataRechargeRank),
				SEM_ID(sem,semgroup,semserver))) {
			error_log("[init_recharge_rank_data_fail][path=%s]", mapfile.c_str());
			return R_ERROR;
		}
		CAutoLock lock(&(m_sh[zoneId]), true);
		if (!m_sh[zoneId].HasInit()) {
			DataRechargeRank *pTable = (DataRechargeRank *) m_sh[zoneId].GetAddress();
			memset(pTable, 0, sizeof(*pTable));
			m_sh[zoneId].SetInitDone();
		}
	}

	m_init = true;
	return 0;
}

int CDataRechargeRank::GetList(unsigned uid, vector<RRUser> &day, vector<RRUser> &all)
{
	unsigned zoneId = 0;
	int ret = getZoneId(uid, zoneId);
	if (ret)
	{
		return ret;
	}

	DataRechargeRank *pTable = (DataRechargeRank *) m_sh[zoneId].GetAddress();
	if (pTable == NULL)
	{
		error_log("[GetList_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh[zoneId]), true);

	if(pTable->version != Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER))
	{
		pTable->Clear();
		pTable->version = Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER);
	}

	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	if(tempNow >= 79200)
	{
		if(pTable->rewardFlag == 0)
		{
			pTable->rewardFlag = 1;

			CLogicEquipment logicEquipment;
			Json::Value temp;
			CLogicUpdates logicUpdates;
			unsigned now1 = Time::GetGlobalTime();
			unsigned p = pTable->day.head;
			for(unsigned i=0;i<pTable->day.num;++i)
			{
				if(p >= RR_DAY)
					break;
				if(!IsValidUid(pTable->day.user[p].uid))
					break;

				int p1 = 0, p2 = 0, pe = 0;
				if (i + 1 == 1)
					p1 = 1;
				else if (i + 1 <= 3)
					p1 = 2;
				else if (i + 1 <= 20)
					p1 = 3;
				else if (i + 1 <= 100)
					p1 = 4;
				else
					p1 = 5;
				if (pTable->day.user[p].cash >= 148888)
					p2 = 1;
				else if (pTable->day.user[p].cash >= 88888)
					p2 = 2;
				else if (pTable->day.user[p].cash >= 28888)
					p2 = 3;
				else if (pTable->day.user[p].cash >= 5888)
					p2 = 4;
				else if (pTable->day.user[p].cash >= 1000)
					p2 = 5;
				pe = ((p1 && p2) ? max(p1, p2) : 0);

				unsigned eqid = 0;
				if(pe == 1)
					eqid = 942;
				else if(pe == 2)
					eqid = 943;
				else if(pe == 3)
					eqid = 944;
				else if(pe == 4)
					eqid = 945;
				else if(pe == 5)
					eqid = 946;

				if(pe)
				{
					AUTO_LOCK_USER(pTable->day.user[p].uid)
					if(logicEquipment.AddOneItem(pTable->day.user[p].uid, eqid, 1, "RechargeRank", temp) == 0)
					{
						Json::Value updates;
						updates["s"] = "RECHARGERANKDAY";
						updates["uid"] = pTable->day.user[p].uid;
						updates["ts"] = now1;
						updates["rank"] = i+1;
						updates["eqid"] = eqid;
						logicUpdates.AddUpdate(pTable->day.user[p].uid,updates,true);
					}
				}

				p = pTable->day.user[p].next;
			}

			if(Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_E_TS) - Time::GetGlobalTime() < 86400)
			{
				p = pTable->all.head;
				for(unsigned i=0;i<pTable->all.num;++i)
				{
					if(p >= RR_ALL)
						break;
					if(!IsValidUid(pTable->all.user[p].uid))
						break;

					int p1 = 0, p2 = 0, pe = 0;
					if (i + 1 == 1)
						p1 = 1;
					else if (i + 1 <= 3)
						p1 = 2;
					else if (i + 1 <= 10)
						p1 = 3;
					else if (i + 1 <= 50)
						p1 = 4;
					else
						p1 = 5;
					if (pTable->all.user[p].cash >= 488888)
						p2 = 1;
					else if (pTable->all.user[p].cash >= 288888)
						p2 = 2;
					else if (pTable->all.user[p].cash >= 98888)
						p2 = 3;
					else if (pTable->all.user[p].cash >= 28888)
						p2 = 4;
					else if (pTable->all.user[p].cash >= 8888)
						p2 = 5;
					pe = ((p1 && p2) ? max(p1, p2) : 0);

					unsigned eqid = 0;
					if(pe == 1)
						eqid = 947;
					else if(pe == 2)
						eqid = 948;
					else if(pe == 3)
						eqid = 949;
					else if(pe == 4)
						eqid = 950;
					else if(pe == 5)
						eqid = 951;

					if(pe)
					{
						AUTO_LOCK_USER(pTable->all.user[p].uid)
						if(logicEquipment.AddOneItem(pTable->all.user[p].uid, eqid, 1, "RechargeRank", temp) == 0)
						{
							Json::Value updates;
							updates["s"] = "RECHARGERANKALL";
							updates["uid"] = pTable->all.user[p].uid;
							updates["ts"] = now1+1;
							updates["rank"] = i+1;
							updates["eqid"] = eqid;
							logicUpdates.AddUpdate(pTable->all.user[p].uid,updates,true);
						}
					}

					p = pTable->all.user[p].next;
				}
			}
		}
	}
	else if(pTable->rewardFlag == 1)
	{
		pTable->rewardFlag = 0;
		pTable->day.Clear();
	}

	unsigned p = pTable->day.head;
	for(unsigned i=0;i<pTable->day.num;++i)
	{
		if(p >= RR_DAY)
			break;
		if(!IsValidUid(pTable->day.user[p].uid))
			break;
		day.push_back(pTable->day.user[p]);
		p = pTable->day.user[p].next;
	}

	p = pTable->all.head;
	for(unsigned i=0;i<pTable->all.num;++i)
	{
		if(p >= RR_ALL)
			break;
		if(!IsValidUid(pTable->all.user[p].uid))
			break;
		all.push_back(pTable->all.user[p]);
		p = pTable->all.user[p].next;
	}

	return 0;
}

int CDataRechargeRank::SetUser(unsigned uid, unsigned cashDay, unsigned cashAll, string& name, unsigned& need)
{
	unsigned zoneId = 0;
	int ret = getZoneId(uid, zoneId);
	if (ret)
	{
		return ret;
	}

	DataRechargeRank *pTable = (DataRechargeRank *) m_sh[zoneId].GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh[zoneId]), true);

	if(pTable->version != Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER))
	{
		pTable->Clear();
		pTable->version = Config::GetIntValue(CONFIG_ACTIVITY_RECHARGE_RANK_VER);
	}

	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;
	if(tempNow >= 79200)
		return 0;
	else if(pTable->rewardFlag == 1)
	{
		pTable->rewardFlag = 0;
		pTable->day.Clear();
	}

	unsigned needDay = 1, needAll = 1;
	/*****************************************/
	if (cashDay >= RECHARGE_LOW_LIMIT)
	{
		if(pTable->day.num == 0)//first
		{
			pTable->day.num = 1;
			pTable->day.head = pTable->day.tail = 0;
			pTable->day.user[0].uid = uid;
			pTable->day.user[0].cash = cashDay;
			strncpy(pTable->day.user[0].name, name.c_str(), sizeof(pTable->day.user[0].name));
			pTable->day.user[0].pre = pTable->day.user[0].next = -1;
		}
		else if(pTable->day.num == RR_DAY && cashDay <= pTable->day.user[pTable->day.tail].cash)//full
		{
			needDay = pTable->day.user[pTable->day.tail].cash - cashDay + 1;
		}
		else if(pTable->day.num < RR_DAY && cashDay <= pTable->day.user[pTable->day.tail].cash)//add after tail
		{
			pTable->day.user[pTable->day.num].uid = uid;
			pTable->day.user[pTable->day.num].cash = cashDay;
			strncpy(pTable->day.user[pTable->day.num].name, name.c_str(), sizeof(pTable->day.user[pTable->day.num].name));
			pTable->day.user[pTable->day.num].pre = pTable->day.tail;
			pTable->day.user[pTable->day.num].next = -1;
			pTable->day.user[pTable->day.tail].next = pTable->day.num;
			pTable->day.tail = pTable->day.num;
			++pTable->day.num;
		}
		else//replace or swap or add not tail
		{
			unsigned p = pTable->day.head, b = -1, s = -1;
			for(unsigned i=0;i<pTable->day.num;++i)
			{
				if(p >= RR_DAY)
					break;

				if(cashDay > pTable->day.user[p].cash && b > RR_DAY)
					b = p;
				if(uid == pTable->day.user[p].uid && s > RR_DAY)
					s = p;

				p = pTable->day.user[p].next;
			}

			if(b < RR_DAY)
			{
				if(s < RR_DAY)//swap
				{
					pTable->day.user[s].cash = cashDay;
				}
				else if(pTable->day.num < RR_DAY)//add not tail
				{
					s = pTable->day.num;
					pTable->day.user[s].uid = uid;
					pTable->day.user[s].cash = cashDay;
					strncpy(pTable->day.user[s].name, name.c_str(), sizeof(pTable->day.user[s].name));
					pTable->day.user[s].pre = -1;
					pTable->day.user[s].next = -1;
					++pTable->day.num;
				}
				else//replace
				{
					s = pTable->day.tail;
					pTable->day.user[s].uid = uid;
					pTable->day.user[s].cash = cashDay;
					strncpy(pTable->day.user[s].name, name.c_str(), sizeof(pTable->day.user[s].name));
				}

				if(s != b)
				{
					if(pTable->day.tail == s)
						pTable->day.tail = pTable->day.user[s].pre;
					if(pTable->day.head == b)
						pTable->day.head = s;

					if(pTable->day.user[s].pre < RR_DAY)
						pTable->day.user[pTable->day.user[s].pre].next = pTable->day.user[s].next;
					if(pTable->day.user[s].next < RR_DAY)
						pTable->day.user[pTable->day.user[s].next].pre = pTable->day.user[s].pre;

					pTable->day.user[s].pre = pTable->day.user[b].pre;
					pTable->day.user[s].next = b;

					if(pTable->day.user[b].pre < RR_DAY)
						pTable->day.user[pTable->day.user[b].pre].next = s;
					pTable->day.user[b].pre = s;
				}
			}
		}
	}
	else
	{
		needDay = RECHARGE_LOW_LIMIT - cashDay;
	}

	/*****************************************/
	if (cashAll >= RECHARGE_LOW_LIMIT)
	{
		if(pTable->all.num == 0)//first
		{
			pTable->all.num = 1;
			pTable->all.head = pTable->all.tail = 0;
			pTable->all.user[0].uid = uid;
			pTable->all.user[0].cash = cashAll;
			strncpy(pTable->all.user[0].name, name.c_str(), sizeof(pTable->all.user[0].name));
			pTable->all.user[0].pre = pTable->all.user[0].next = -1;
		}
		else if(pTable->all.num == RR_ALL && cashAll <= pTable->all.user[pTable->all.tail].cash)//full
		{
			needAll = pTable->all.user[pTable->all.tail].cash - cashAll + 1;
		}
		else if(pTable->all.num < RR_ALL && cashAll <= pTable->all.user[pTable->all.tail].cash)//add after tail
		{
			pTable->all.user[pTable->all.num].uid = uid;
			pTable->all.user[pTable->all.num].cash = cashAll;
			strncpy(pTable->all.user[pTable->all.num].name, name.c_str(), sizeof(pTable->all.user[pTable->all.num].name));
			pTable->all.user[pTable->all.num].pre = pTable->all.tail;
			pTable->all.user[pTable->all.num].next = -1;
			pTable->all.user[pTable->all.tail].next = pTable->all.num;
			pTable->all.tail = pTable->all.num;
			++pTable->all.num;
		}
		else//replace or swap or add not tail
		{
			unsigned p = pTable->all.head, b = -1, s = -1;
			for(unsigned i=0;i<pTable->all.num;++i)
			{
				if(p >= RR_ALL)
					break;

				if(cashAll > pTable->all.user[p].cash && b > RR_ALL)
					b = p;
				if(uid == pTable->all.user[p].uid && s > RR_ALL)
					s = p;

				p = pTable->all.user[p].next;
			}

			if(b < RR_ALL)
			{
				if(s < RR_ALL)//swap
				{
					pTable->all.user[s].cash = cashAll;
				}
				else if(pTable->all.num < RR_ALL)//add not tail
				{
					s = pTable->all.num;
					pTable->all.user[s].uid = uid;
					pTable->all.user[s].cash = cashAll;
					strncpy(pTable->all.user[s].name, name.c_str(), sizeof(pTable->all.user[s].name));
					pTable->all.user[s].pre = -1;
					pTable->all.user[s].next = -1;
					++pTable->all.num;
				}
				else//replace
				{
					s = pTable->all.tail;
					pTable->all.user[s].uid = uid;
					pTable->all.user[s].cash = cashAll;
					strncpy(pTable->all.user[s].name, name.c_str(), sizeof(pTable->all.user[s].name));
				}

				if(s != b)
				{
					if(pTable->all.tail == s)
						pTable->all.tail = pTable->all.user[s].pre;
					if(pTable->all.head == b)
						pTable->all.head = s;

					if(pTable->all.user[s].pre < RR_ALL)
						pTable->all.user[pTable->all.user[s].pre].next = pTable->all.user[s].next;
					if(pTable->all.user[s].next < RR_ALL)
						pTable->all.user[pTable->all.user[s].next].pre = pTable->all.user[s].pre;

					pTable->all.user[s].pre = pTable->all.user[b].pre;
					pTable->all.user[s].next = b;

					if(pTable->all.user[b].pre < RR_ALL)
						pTable->all.user[pTable->all.user[b].pre].next = s;
					pTable->all.user[b].pre = s;
				}
			}
		}
	}
	else
	{
		needAll = RECHARGE_LOW_LIMIT - cashAll;
	}

	/*****************************************/
	need = std::min(needDay, needAll);

	return 0;
}

int CDataRechargeRank::getZoneId(unsigned uid, unsigned &zoneId)
{
	if (!IsValidUid(uid))
	{
		error_log("get wrong uid in recharge rank");
		return R_ERR_PARAM;
	}
	unsigned serverId = Config::GetZoneByUID(uid);
	if (1 <= serverId && serverId <= 595)
	{
		zoneId = 0;
	}
	else
	{
		zoneId = 1;
	}

	return 0;
}
