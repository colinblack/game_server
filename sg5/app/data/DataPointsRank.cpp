/*
 * CDataPointsRank.cpp
 *
 *  Created on: 2012-10-16
 *      Author: Administrator
 */

#include "DataPointsRank.h"
#include "LogicInc.h"

/****************砸罐活动排行榜*************************/
CDataPointsRank::CDataPointsRank(){
	m_init = false;
}
CDataPointsRank::~CDataPointsRank() {
	// TODO Auto-generated destructor stub
}

int  CDataPointsRank::Init(const std::string &path, semdat sem)
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
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(PointsRank), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init__joincard_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		PointsRank *pdata = (PointsRank *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_pointsrank_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}
int sortFunc(const DataPoints& left,const DataPoints& right){
	return left.points > right.points;
}
int CDataPointsRank::UpdateRankList(const DataPoints &points)
{
	int i= 0;
	bool inFlag = false;  // 用户是否在排行榜中
	PointsRank *pdata = (PointsRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	CAutoLock lock(&m_sh, true);
	for(i = RANK_SIZE -1;i >= 0; i--)
	{
		if(pdata->pointRank[i].uid == points.uid  )
		{
			pdata->pointRank[i].points = points.points;
			// 如果用户已在排行榜，inFlag = true
			inFlag = true;
			break;
		}
	}
	if(!inFlag){
		pdata->pointRank[RANK_SIZE] = points;
	}
	else{
		memset(&(pdata->pointRank[RANK_SIZE]),0,sizeof(DataPoints));
	}

	vector<DataPoints> vecPoint;
	for(i = 0; i<=RANK_SIZE;++i){
		vecPoint.push_back(pdata->pointRank[i]);
	}

	sort(vecPoint.begin(),vecPoint.end(),sortFunc);

	for(i = 0; i<=RANK_SIZE;++i){
		pdata->pointRank[i] = vecPoint[i];
	}
	return 0;
}

int CDataPointsRank::GetRankList( DataPoints vecPoints[])
{
	PointsRank *pdata = (PointsRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	CAutoLock lock(&m_sh, true);
	memcpy(vecPoints,pdata->pointRank,sizeof(DataPoints) * RANK_SIZE);
	return 0;
}

int CDataPointsRank::SetReward(unsigned uid, byte reward)
{
	PointsRank *pdata = (PointsRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	CAutoLock lock(&m_sh, true);
	for (int i=0; i<RANK_SIZE; i++)
	{
		if (pdata->pointRank[i].uid == uid)
		{
			if(pdata->pointRank[i].reward == reward)
				return R_ERR_LOGIC;
			pdata->pointRank[i].reward = reward;
			return 0;
		}
	}
	return R_ERROR;
}

int CDataPointsRank::CleanRankList(void)
{
	PointsRank *pdata = (PointsRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_pointsrank_fail");
	}
	CAutoLock lock(&m_sh, true);
	memset(pdata, 0, sizeof(*pdata));
	return 0;
}

/*******************************************************/

/****************跨服砸罐活动排行榜*************************/
#define POINT_RANK_LOW_LIMIT 500

CDataPointsRankAllServer::CDataPointsRankAllServer() {
	m_init = false;
}
CDataPointsRankAllServer:: ~CDataPointsRankAllServer(){

}

int CDataPointsRankAllServer::Init(const string &path, semdat sem) {
	if (m_init) {
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);

	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(PointsRankALLServer),
			SEM_ID(sem,semgroup,semserver))) {
		error_log("[init_point_rank_all_server_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&(m_sh), true);
	if (!m_sh.HasInit()) {
		PointsRankALLServer *pTable = (PointsRankALLServer *) m_sh.GetAddress();
		memset(pTable, 0, sizeof(*pTable));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataPointsRankAllServer::GetRankList(unsigned uid, vector<PRUser> &day, vector<PRUser> &all)
{
	PointsRankALLServer *pTable = (PointsRankALLServer *) m_sh.GetAddress();
	if (pTable == NULL)
	{
		error_log("[GetList_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	if(pTable->version != Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER))
	{
		pTable->Clear();
		pTable->version = Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER);
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
				if(p >= POINT_RANK_ALL_SERVER_DAY)
					break;
				if(!IsValidUid(pTable->day.user[p].uid))
					break;

				unsigned eqid = 0;
				unsigned extraId = 0;
				unsigned extraCnt = 0;

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
				if (pTable->day.user[p].points >= 48888)
					p2 = 1;
				else if (pTable->day.user[p].points >= 28888)
					p2 = 2;
				else if (pTable->day.user[p].points >= 18888)
					p2 = 3;
				else if (pTable->day.user[p].points >= 5888)
					p2 = 4;
				else if (pTable->day.user[p].points >= 500)
					p2 = 5;
				pe = ((p1 && p2) ? max(p1, p2) : 0);

				if (pe == 1)
				{
					eqid = 4429;
					extraId = 623;  //威望包(1w)
					extraCnt = 10;
				}
				else if (pe == 2)
				{
					eqid = 4458;
					extraId = 623;
					extraCnt = 8;
				}
				else if (pe == 3)
				{
					eqid = 4437;
					extraId = 623;
					extraCnt = 5;
				}
				else if (pe == 4)
				{
					eqid = 4466;
					extraId = 623;
					extraCnt = 2;
				}
				else if (pe == 5)
				{
					eqid = 4405;
					extraId = 653; //威武包(5000)
					extraCnt = 1;
				}

				if(pe)
				{
					vector<ItemAdd> items;
					ItemAdd item1;
					ItemAdd item2;
					item1.eqid = eqid;
					item1.count = 1;
					item1.reason = "PointRankAllServerDay";
					item2.eqid = extraId;
					item2.count = extraCnt;
					item2.reason = "PointRankAllServerDay";
					items.push_back(item1);
					items.push_back(item2);

					AUTO_LOCK_USER(pTable->day.user[p].uid)
					if(logicEquipment.AddItems(pTable->day.user[p].uid, items, temp) == 0)
					{
						Json::Value updates;
						updates["s"] = "PointRankAllServerDay";
						updates["uid"] = pTable->day.user[p].uid;
						updates["ts"] = now1;
						updates["rank"] = i+1;
						updates["eqid"] = eqid;
						logicUpdates.AddUpdate(pTable->day.user[p].uid,updates,true);
					}
				}

				p = pTable->day.user[p].next;
			}

			if(Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS) - Time::GetGlobalTime() < 86400)
			{
				p = pTable->all.head;
				for(unsigned i=0;i<pTable->all.num;++i)
				{
					if(p >= POINT_RANK_ALL_SERVER_ALL)
						break;
					if(!IsValidUid(pTable->all.user[p].uid))
						break;

					unsigned eqid = 0;
					unsigned extraId = 0;
					unsigned extraCnt = 0;

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
					if (pTable->all.user[p].points >= 118888)
						p2 = 1;
					else if (pTable->all.user[p].points >= 68888)
						p2 = 2;
					else if (pTable->all.user[p].points >= 38888)
						p2 = 3;
					else if (pTable->all.user[p].points >= 18888)
						p2 = 4;
					else if (pTable->all.user[p].points >= 998)
						p2 = 5;
					pe = ((p1 && p2) ? max(p1, p2) : 0);

					if (pe == 1)
					{
						eqid = 44030;
						extraId = 638;  //至尊材料包
						extraCnt = 8;
					}
					else if (pe == 2)
					{
						eqid = 44039;
						extraId = 638;  //至尊材料包
						extraCnt = 5;
					}
					else if (pe == 3)
					{
						eqid = 44078;
						extraId = 638;  //至尊材料包
						extraCnt = 3;
					}
					else if (pe == 4)
					{
						eqid = 44017;
						extraId = 638;
						extraCnt = 1;
					}
					else if (pe == 5)
					{
						eqid = 44066;
						extraId = 4070;
						extraCnt = 588;
					}

					if(pe)
					{
						vector<ItemAdd> items;
						ItemAdd item1;
						ItemAdd item2;
						item1.eqid = eqid;
						item1.count = 1;
						item1.reason = "PointRankAllServerAll";
						item2.eqid = extraId;
						item2.count = extraCnt;
						item2.reason = "PointRankAllServerAll";
						items.push_back(item1);
						items.push_back(item2);

						AUTO_LOCK_USER(pTable->all.user[p].uid)
						if(logicEquipment.AddItems(pTable->all.user[p].uid, items, temp) == 0)
						{
							Json::Value updates;
							updates["s"] = "PointRankAllServerAll";
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
		if(p >= POINT_RANK_ALL_SERVER_DAY)
			break;
		if(!IsValidUid(pTable->day.user[p].uid))
			break;
		day.push_back(pTable->day.user[p]);
		p = pTable->day.user[p].next;
	}

	p = pTable->all.head;
	for(unsigned i=0;i<pTable->all.num;++i)
	{
		if(p >= POINT_RANK_ALL_SERVER_ALL)
			break;
		if(!IsValidUid(pTable->all.user[p].uid))
			break;
		all.push_back(pTable->all.user[p]);
		p = pTable->all.user[p].next;
	}

	return 0;
}

int CDataPointsRankAllServer::UpdateRankList(unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, unsigned& need)
{
	PointsRankALLServer *pTable = (PointsRankALLServer *) m_sh.GetAddress();
	if (pTable == NULL) {
		error_log("[SetUser_fail]");
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	if(pTable->version != Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER))
	{
		pTable->Clear();
		pTable->version = Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_VER);
	}

	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;

	bool bDayUpdate = true;
	bool bAllUpdate = true;
	if(tempNow >= 79200)
	{
		bDayUpdate = false;
	}
	else if(pTable->rewardFlag == 1)
	{
		pTable->rewardFlag = 0;
		pTable->day.Clear();
	}

	if (tempNow >= 79200 && Config::GetIntValue(CONFIG_HAMMERHIT_ALLSERVER_END_TS) - Time::GetGlobalTime() < 86400)
	{
		bAllUpdate = false;
	}

	unsigned needDay = 1, needAll = 1;
	/*****************************************/
	if (bDayUpdate)
	{
		if (pointsDay >= POINT_RANK_LOW_LIMIT)
		{
			if(pTable->day.num == 0)//first
			{
				pTable->day.num = 1;
				pTable->day.head = pTable->day.tail = 0;
				pTable->day.user[0].uid = uid;
				pTable->day.user[0].points = pointsDay;
				strncpy(pTable->day.user[0].name, name.c_str(), sizeof(pTable->day.user[0].name));
				pTable->day.user[0].pre = pTable->day.user[0].next = -1;
			}
			else if(pTable->day.num == POINT_RANK_ALL_SERVER_DAY && pointsDay <= pTable->day.user[pTable->day.tail].points)//full
			{
				needDay = pTable->day.user[pTable->day.tail].points - pointsDay + 1;
			}
			else if(pTable->day.num < POINT_RANK_ALL_SERVER_DAY && pointsDay <= pTable->day.user[pTable->day.tail].points)//add after tail
			{
				pTable->day.user[pTable->day.num].uid = uid;
				pTable->day.user[pTable->day.num].points = pointsDay;
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
					if(p >= POINT_RANK_ALL_SERVER_DAY)
						break;

					if(pointsDay > pTable->day.user[p].points && b > POINT_RANK_ALL_SERVER_DAY)
						b = p;
					if(uid == pTable->day.user[p].uid && s > POINT_RANK_ALL_SERVER_DAY)
						s = p;

					p = pTable->day.user[p].next;
				}

				if(b < POINT_RANK_ALL_SERVER_DAY)
				{
					if(s < POINT_RANK_ALL_SERVER_DAY)//swap
					{
						pTable->day.user[s].points = pointsDay;
					}
					else if(pTable->day.num < POINT_RANK_ALL_SERVER_DAY)//add not tail
					{
						s = pTable->day.num;
						pTable->day.user[s].uid = uid;
						pTable->day.user[s].points = pointsDay;
						strncpy(pTable->day.user[s].name, name.c_str(), sizeof(pTable->day.user[s].name));
						pTable->day.user[s].pre = -1;
						pTable->day.user[s].next = -1;
						++pTable->day.num;
					}
					else//replace
					{
						s = pTable->day.tail;
						pTable->day.user[s].uid = uid;
						pTable->day.user[s].points = pointsDay;
						strncpy(pTable->day.user[s].name, name.c_str(), sizeof(pTable->day.user[s].name));
					}

					if(s != b)
					{
						if(pTable->day.tail == s)
							pTable->day.tail = pTable->day.user[s].pre;
						if(pTable->day.head == b)
							pTable->day.head = s;

						if(pTable->day.user[s].pre < POINT_RANK_ALL_SERVER_DAY)
							pTable->day.user[pTable->day.user[s].pre].next = pTable->day.user[s].next;
						if(pTable->day.user[s].next < POINT_RANK_ALL_SERVER_DAY)
							pTable->day.user[pTable->day.user[s].next].pre = pTable->day.user[s].pre;

						pTable->day.user[s].pre = pTable->day.user[b].pre;
						pTable->day.user[s].next = b;

						if(pTable->day.user[b].pre < POINT_RANK_ALL_SERVER_DAY)
							pTable->day.user[pTable->day.user[b].pre].next = s;
						pTable->day.user[b].pre = s;
					}
				}
			}
		}
		else
		{
			needDay = POINT_RANK_LOW_LIMIT - pointsDay;
		}
	}

	/*****************************************/
	if (bAllUpdate)
	{
		if (pointsAll >= POINT_RANK_LOW_LIMIT)
		{
			if(pTable->all.num == 0)//first
			{
				pTable->all.num = 1;
				pTable->all.head = pTable->all.tail = 0;
				pTable->all.user[0].uid = uid;
				pTable->all.user[0].points = pointsAll;
				strncpy(pTable->all.user[0].name, name.c_str(), sizeof(pTable->all.user[0].name));
				pTable->all.user[0].pre = pTable->all.user[0].next = -1;
			}
			else if(pTable->all.num == POINT_RANK_ALL_SERVER_ALL && pointsAll <= pTable->all.user[pTable->all.tail].points)//full
			{
				needAll = pTable->all.user[pTable->all.tail].points - pointsAll + 1;
			}
			else if(pTable->all.num < POINT_RANK_ALL_SERVER_ALL && pointsAll <= pTable->all.user[pTable->all.tail].points)//add after tail
			{
				pTable->all.user[pTable->all.num].uid = uid;
				pTable->all.user[pTable->all.num].points = pointsAll;
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
					if(p >= POINT_RANK_ALL_SERVER_ALL)
						break;

					if(pointsAll > pTable->all.user[p].points && b > POINT_RANK_ALL_SERVER_ALL)
						b = p;
					if(uid == pTable->all.user[p].uid && s > POINT_RANK_ALL_SERVER_ALL)
						s = p;

					p = pTable->all.user[p].next;
				}

				if(b < POINT_RANK_ALL_SERVER_ALL)
				{
					if(s < POINT_RANK_ALL_SERVER_ALL)//swap
					{
						pTable->all.user[s].points = pointsAll;
					}
					else if(pTable->all.num < POINT_RANK_ALL_SERVER_ALL)//add not tail
					{
						s = pTable->all.num;
						pTable->all.user[s].uid = uid;
						pTable->all.user[s].points = pointsAll;
						strncpy(pTable->all.user[s].name, name.c_str(), sizeof(pTable->all.user[s].name));
						pTable->all.user[s].pre = -1;
						pTable->all.user[s].next = -1;
						++pTable->all.num;
					}
					else//replace
					{
						s = pTable->all.tail;
						pTable->all.user[s].uid = uid;
						pTable->all.user[s].points = pointsAll;
						strncpy(pTable->all.user[s].name, name.c_str(), sizeof(pTable->all.user[s].name));
					}

					if(s != b)
					{
						if(pTable->all.tail == s)
							pTable->all.tail = pTable->all.user[s].pre;
						if(pTable->all.head == b)
							pTable->all.head = s;

						if(pTable->all.user[s].pre < POINT_RANK_ALL_SERVER_ALL)
							pTable->all.user[pTable->all.user[s].pre].next = pTable->all.user[s].next;
						if(pTable->all.user[s].next < POINT_RANK_ALL_SERVER_ALL)
							pTable->all.user[pTable->all.user[s].next].pre = pTable->all.user[s].pre;

						pTable->all.user[s].pre = pTable->all.user[b].pre;
						pTable->all.user[s].next = b;

						if(pTable->all.user[b].pre < POINT_RANK_ALL_SERVER_ALL)
							pTable->all.user[pTable->all.user[b].pre].next = s;
						pTable->all.user[b].pre = s;
					}
				}
			}
		}
		else
		{
			needAll = POINT_RANK_LOW_LIMIT - pointsAll;
		}
	}
	/*****************************************/
	if (bDayUpdate && bAllUpdate)
		need = std::min(needDay, needAll);
	else
		need = needAll;

	return 0;
}
/*****************************************/

