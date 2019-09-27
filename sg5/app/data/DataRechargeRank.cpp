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

unsigned get_rr_day(unsigned i, unsigned c)
{
	const unsigned rr_day_cash[5] = {148888,98888,28888,5888,1000};
	const unsigned rr_day_id[5] = {50124,86040,10267,44107,44106};
	for(;i<5;++i)
	{
		if(c >= rr_day_cash[i])
			return rr_day_id[i];
	}
	return 0;
}
pair<unsigned, unsigned > get_rr_all(unsigned i, unsigned c)
{
	const unsigned rr_all_cash[5] = {488888,288888,98888,28888,8888};
	const unsigned rr_all_id[5] = {50161,6610,44129,4497,44127};
	const unsigned rr_all_count[5] = {1,1,1,1,1};
	for(;i<5;++i)
	{
		if(c >= rr_all_cash[i])
			return make_pair(rr_all_id[i],rr_all_count[i]);
	}
	return make_pair(0,0);
}

int CDataRechargeRank::GetList(unsigned uid, vector<RRUser> &day, vector<RRUser> &all)
{
	const unsigned rr_day_basic_id[5] = {50151,50152,50153,50154,50155};
	const unsigned rr_all_basic_id[5] = {50156,50157,50158,50159,50160};

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

				vector<ItemAdd> equip_items;
				if (i + 1 == 1)
				{
					equip_items.push_back(ItemAdd(rr_day_basic_id[0], 1, "RechargeRank"));
					unsigned id = get_rr_day(0, pTable->day.user[p].cash);
					if (id)
						equip_items.push_back(ItemAdd(id, 1, "RechargeRank"));
				}
				else if (i + 1 <= 3)
				{
					equip_items.push_back(ItemAdd(rr_day_basic_id[1], 1, "RechargeRank"));
					unsigned id = get_rr_day(1, pTable->day.user[p].cash);
					if (id)
						equip_items.push_back(ItemAdd(id, 1, "RechargeRank"));
				}
				else if (i + 1 <= 20)
				{
					equip_items.push_back(ItemAdd(rr_day_basic_id[2], 1, "RechargeRank"));
					unsigned id = get_rr_day(2, pTable->day.user[p].cash);
					if (id)
						equip_items.push_back(ItemAdd(id, 1, "RechargeRank"));
				}
				else if (i + 1 <= 50)
				{
					equip_items.push_back(ItemAdd(rr_day_basic_id[3], 1, "RechargeRank"));
					unsigned id = get_rr_day(3, pTable->day.user[p].cash);
					if (id)
						equip_items.push_back(ItemAdd(id, 1, "RechargeRank"));
				}
				else
				{
					equip_items.push_back(ItemAdd(rr_day_basic_id[4], 1, "RechargeRank"));
					unsigned id = get_rr_day(4, pTable->day.user[p].cash);
					if (id)
						equip_items.push_back(ItemAdd(id, 1, "RechargeRank"));
				}
				if(!equip_items.empty())
				{
					AUTO_LOCK_USER(pTable->day.user[p].uid)
					if(logicEquipment.AddItems(pTable->day.user[p].uid, equip_items, temp) == 0)
					{
						Json::Value updates;
						updates["s"] = "RECHARGERANKDAY";
						updates["uid"] = pTable->day.user[p].uid;
						updates["ts"] = now1;
						updates["rank"] = i+1;
						updates["eqid"] = equip_items[0].eqid;
						if(equip_items.size()>1)
							updates["eqid1"] = equip_items[1].eqid;
						updates["cash"] = pTable->day.user[p].cash;
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

					vector<ItemAdd> equip_items;
					pair<unsigned, unsigned> reward;
					if (i + 1 == 1)
					{
						equip_items.push_back(ItemAdd(rr_all_basic_id[0], 1, "RechargeRank"));
						reward = get_rr_all(0, pTable->all.user[p].cash);
						if (reward.first)
							equip_items.push_back(ItemAdd(reward.first, reward.second, "RechargeRank"));
					}
					else if (i + 1 <= 3)
					{
						equip_items.push_back(ItemAdd(rr_all_basic_id[1], 1, "RechargeRank"));
						reward = get_rr_all(1, pTable->all.user[p].cash);
						if (reward.first)
							equip_items.push_back(ItemAdd(reward.first, reward.second, "RechargeRank"));
					}
					else if (i + 1 <= 10)
					{
						equip_items.push_back(ItemAdd(rr_all_basic_id[2], 1, "RechargeRank"));
						reward  = get_rr_all(2, pTable->all.user[p].cash);
						if (reward.first)
							equip_items.push_back(ItemAdd(reward.first, reward.second, "RechargeRank"));
					}
					else if (i + 1 <= 30)
					{
						equip_items.push_back(ItemAdd(rr_all_basic_id[3], 1, "RechargeRank"));
						reward = get_rr_all(3, pTable->all.user[p].cash);
						if (reward.first)
							equip_items.push_back(ItemAdd(reward.first, reward.second, "RechargeRank"));
					}
					else
					{
						equip_items.push_back(ItemAdd(rr_all_basic_id[4], 1, "RechargeRank"));
						reward = get_rr_all(4, pTable->all.user[p].cash);
						if (reward.first)
							equip_items.push_back(ItemAdd(reward.first, reward.second, "RechargeRank"));
					}
					if(!equip_items.empty())
					{
						AUTO_LOCK_USER(pTable->all.user[p].uid)
						if(logicEquipment.AddItems(pTable->all.user[p].uid, equip_items, temp) == 0)
						{
							Json::Value updates;
							updates["s"] = "RECHARGERANKALL";
							updates["uid"] = pTable->all.user[p].uid;
							updates["ts"] = now1+1;
							updates["rank"] = i+1;
							updates["eqid"] = equip_items[0].eqid;
							updates["num"] = reward.second;
							if(equip_items.size()>1)
								updates["eqid1"] = equip_items[1].eqid;
							updates["cash"] = pTable->all.user[p].cash;
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
