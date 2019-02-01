/*
 * DataAllServerRank.cpp
 *
 *  Created on: 2014-7-10
 *      Author: Ralf
 */

#include "DataInc.h"
#include "LogicInc.h"

CDataAllServerRank* CDataAllServerRank::m_pData = NULL;

const int CDataAllServerRank::rank_seg[ALL_SERVER_RANK_SEG+1] = {
	ALL_SERVER_RANK_1,
	ALL_SERVER_RANK_2,
	ALL_SERVER_RANK_3,
	ALL_SERVER_RANK_4,
	ALL_SERVER_RANK_5,
	ALL_SERVER_RANK_6,
	ALL_SERVER_RANK_7,
	ALL_SERVER_RANK_8,
	ALL_SERVER_RANK_9,
	ALL_SERVER_RANK_10,
	ALL_SERVER_RANK_11};

const AllServerRankReward CDataAllServerRank::rank_reward[ALL_SERVER_RANK_SEG] = {
	ALL_SERVER_RANK_R_1,
	ALL_SERVER_RANK_R_2,
	ALL_SERVER_RANK_R_3,
	ALL_SERVER_RANK_R_4,
	ALL_SERVER_RANK_R_5,
	ALL_SERVER_RANK_R_6,
	ALL_SERVER_RANK_R_7,
	ALL_SERVER_RANK_R_8,
	ALL_SERVER_RANK_R_9,
	ALL_SERVER_RANK_R_10};

#define CDATA_ALL_SERVER_RANK_RESTART(pdata) \
m_uidmap.clear(); \
m_scoremap.clear(); \
m_count = pdata->count; \
m_day = pdata->day; \
m_dayts = pdata->dayts; \
for(unsigned dataindex=0;dataindex<pdata->count;++dataindex) \
{ \
	pdata->user[dataindex].index = dataindex; \
	m_uidmap[pdata->user[dataindex].uid] = pdata->user[dataindex]; \
	m_scoremap.insert(pair<int,unsigned>(pdata->user[dataindex].score,pdata->user[dataindex].uid)); \
} \

CDataAllServerRank::CDataAllServerRank()
{
	m_init = false;

	m_count = m_day = m_dayts = 0;
}

CDataAllServerRank::~CDataAllServerRank()
{}

CDataAllServerRank* CDataAllServerRank::GetCDataAllServerRank(bool init)
{
	if(!m_pData)
	{
		m_pData = new CDataAllServerRank;
		string dataPath = MainConfig::GetAllServerPath(CONFIG_ALL_SERVER_RANK_PATH);
		if (dataPath.empty())
		{
			return NULL;
		}
		int ret = m_pData->Init(dataPath,sem_allserver_rank,init);
		if(ret)
		{
			delete m_pData;
			return NULL;
		}
	}
	return m_pData;
}

int CDataAllServerRank::Init(const std::string &path, semdat sem, bool init)
{
	if(m_init)
		return 0;

	int semgroup = 0;
	int semserver = 0;
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataAllServerRank), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_allserverrank_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	if(!m_sh.HasInit())
	{
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	//cout<<"uid:"<<pdata->user[0].uid<<" score:"<<pdata->user[0].score<<endl;
	if(init)
	{
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
	}
	//cout<<"uid:"<<pdata->user[0].uid<<" score:"<<pdata->user[0].score<<endl;

	m_init = true;

	return 0;
}

int CDataAllServerRank::GetUser(unsigned uid, AllServerRankUser &user, unsigned &count, unsigned &day, unsigned &dayts, unsigned &nextuid)
{
	day = m_day;
	dayts = m_dayts;

	if(m_count == 0)
	{
		nextuid = 0;
		AllServerRankUser temp;
		temp.score = ALL_SERVER_RANK_START;
		temp.shigh = ALL_SERVER_RANK_START;
		temp.slow = ALL_SERVER_RANK_START;
		temp.uid = uid;
		user = temp;
		m_uidmap[temp.uid] = temp;
		m_scoremap.insert(pair<int,unsigned>(temp.score,temp.uid));
		m_count = 1;

		DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}

		CAutoLock lock(&(m_sh), true);

		if(pdata->count == 0)
		{
			pdata->user[0] = temp;
			pdata->count = 1;
		}
		else
		{
			error_log("count mismatch!");

			CDATA_ALL_SERVER_RANK_RESTART(pdata)
			//exit(1);
			return R_ERR_DB;
		}
	}
	else if(m_count == 1)
	{
		if(m_uidmap.count(uid))
		{
			user = m_uidmap[uid];
			nextuid = 0;
		}
		else
		{
			nextuid = m_uidmap.begin()->second.uid;
			AllServerRankUser temp;
			temp.score = ALL_SERVER_RANK_START;
			temp.shigh = ALL_SERVER_RANK_START;
			temp.slow = ALL_SERVER_RANK_START;
			temp.uid = uid;
			user = temp;
		}
	}
	else
	{
		if(m_uidmap.count(uid))
		{
			user = m_uidmap[uid];
		}
		else
		{
			AllServerRankUser temp;
			temp.score = ALL_SERVER_RANK_START;
			temp.shigh = ALL_SERVER_RANK_START;
			temp.slow = ALL_SERVER_RANK_START;
			temp.uid = uid;
			user = temp;
		}

		AllServerRankScoreMap::iterator lowb, upb, it;
		int distance = 0, low = user.score - ALL_SERVER_RANK_RANGE, up = user.score + ALL_SERVER_RANK_RANGE;
		while(!distance)
		{
			lowb = m_scoremap.lower_bound(low);
			if(lowb == m_scoremap.end())
				--lowb;
			upb = m_scoremap.upper_bound(up);
			if(upb == m_scoremap.end())
				--upb;
			distance = std::distance(lowb, upb);
			if(distance > 0)
			{
				nextuid = uid;
				while(nextuid == uid)
				{
					it = lowb;
					int r = Math::GetRandomInt(distance + 1);
					for(int i=0;i<r;++i)
						++it;
					if(it != m_scoremap.end())
						nextuid = it->second;
				}
			}
			else if(!distance)
			{
				low -= ALL_SERVER_RANK_RANGE;
				up += ALL_SERVER_RANK_RANGE;
			}
			/*
			else
			{
				error_log("range mismatch!");

				DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
				if(pdata == NULL)
				{
					return R_ERR_DB;
				}

				CAutoLock lock(&(m_sh), true);

				CDATA_ALL_SERVER_RANK_RESTART(pdata)
				//exit(1);
				return R_ERR_DB;
			}
			*/
		}
	}

	count = m_count;
	return 0;
}

int CDataAllServerRank::StartFight(unsigned attacker, unsigned defender)
{
	DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	if(m_count != pdata->count)
	{
		error_log("defender mismatch!");
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
		//exit(1);
		return R_ERR_DB;
	}

	m_day = pdata->day;
	m_dayts = pdata->dayts;
	m_count = pdata->count;

	if(!m_uidmap.count(defender)
	|| m_uidmap[defender].index >= ALL_SERVER_RANK_USER
	|| pdata->user[m_uidmap[defender].index].uid != defender)
	{
		error_log("defender mismatch!");
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
		//exit(1);
		return R_ERR_DB;
	}

	if(!m_uidmap.count(attacker))
	{
		if(pdata->count >= ALL_SERVER_RANK_USER)
		{
			error_log("full!");
			return R_ERR_DB;
		}

		AllServerRankUser temp;
		temp.score = ALL_SERVER_RANK_START - ALL_SERVER_RANK_LOSE;
		temp.tscore = -ALL_SERVER_RANK_LOSE;
		temp.shigh = ALL_SERVER_RANK_START;
		temp.slow = ALL_SERVER_RANK_START - ALL_SERVER_RANK_LOSE;
		temp.tfight = 1;
		temp.flag = AllServerRankFlag_attacking;
		temp.uid = attacker;
		temp.index = pdata->count;
		temp.history[0] = AllServerRankHistory(defender,AllServerRankResult_Lose,"Internet");
		pdata->user[pdata->count] = temp;
		m_uidmap[temp.uid] = temp;
		m_scoremap.insert(pair<int,unsigned>(temp.score,temp.uid));
		++pdata->count;
		m_count = pdata->count;
	}
	else
	{
		if(m_uidmap[attacker].index >= ALL_SERVER_RANK_USER
		|| pdata->user[m_uidmap[attacker].index].uid != attacker)
		{
			error_log("attacker mismatch!");
			CDATA_ALL_SERVER_RANK_RESTART(pdata)
			//exit(1);
			return R_ERR_DB;
		}
		else
		{
			int attackerscore = pdata->user[m_uidmap[attacker].index].score;

			if(pdata->user[m_uidmap[attacker].index].flag == AllServerRankFlag_attacking)
				pdata->user[m_uidmap[attacker].index].tcwin = 0;
			else
				pdata->user[m_uidmap[attacker].index].flag = AllServerRankFlag_attacking;
			++pdata->user[m_uidmap[attacker].index].tfight;
			pdata->user[m_uidmap[attacker].index].tscore -= ALL_SERVER_RANK_LOSE;
			pdata->user[m_uidmap[attacker].index].score -= ALL_SERVER_RANK_LOSE;
			if(pdata->user[m_uidmap[attacker].index].score < pdata->user[m_uidmap[attacker].index].slow)
				pdata->user[m_uidmap[attacker].index].slow = pdata->user[m_uidmap[attacker].index].score;

			for(int i=ALL_SERVER_RANK_HISTORY-1;i>0;--i)
				pdata->user[m_uidmap[attacker].index].history[i] = pdata->user[m_uidmap[attacker].index].history[i-1];
			pdata->user[m_uidmap[attacker].index].history[0] = AllServerRankHistory(defender,AllServerRankResult_Lose,"Internet");

			m_uidmap[attacker] = pdata->user[m_uidmap[attacker].index];

			pair<AllServerRankScoreMap::iterator,AllServerRankScoreMap::iterator> it;
			AllServerRankScoreMap::iterator iter;
			it = m_scoremap.equal_range(attackerscore);
			for(iter=it.first;iter!=it.second;++iter)
			{
				if(iter->second == attacker)
				{
					m_scoremap.erase(iter);
					break;
				}
			}
			m_scoremap.insert(pair<int,unsigned>(pdata->user[m_uidmap[attacker].index].score,attacker));
		}
	}

	return 0;
}

int CDataAllServerRank::SetResult(unsigned attacker, unsigned defender, bool win, unsigned lvl, string &attackername, string &defendername, int &scoreres)
{
	DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	if(m_count != pdata->count)
	{
		error_log("defender mismatch!");
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
		//exit(1);
		return R_ERR_DB;
	}

	m_day = pdata->day;
	m_dayts = pdata->dayts;
	m_count = pdata->count;

	if(!m_uidmap.count(defender)
	|| m_uidmap[defender].index >= ALL_SERVER_RANK_USER
	|| pdata->user[m_uidmap[defender].index].uid != defender)
	{
		error_log("defender mismatch!");
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
		//exit(1);
		return R_ERR_DB;
	}

	if(!m_uidmap.count(attacker)
	|| m_uidmap[attacker].index >= ALL_SERVER_RANK_USER
	|| pdata->user[m_uidmap[attacker].index].uid != attacker)
	{
		error_log("attacker mismatch!");
		CDATA_ALL_SERVER_RANK_RESTART(pdata)
		//exit(1);
		return R_ERR_DB;
	}

	pdata->user[m_uidmap[attacker].index].lvl = lvl;
	memcpy(pdata->user[m_uidmap[attacker].index].name,attackername.c_str(),sizeof(pdata->user[m_uidmap[attacker].index].name)-1);
	if(win)
	{
		int attackerscore = pdata->user[m_uidmap[attacker].index].score;
		int defenderscore = pdata->user[m_uidmap[defender].index].score;

		if(pdata->user[m_uidmap[attacker].index].flag == AllServerRankFlag_attacking)
			pdata->user[m_uidmap[attacker].index].flag = AllServerRankFlag_none;
		else
			return R_ERR_LOGIC;
		++pdata->user[m_uidmap[attacker].index].swin;
		pdata->user[m_uidmap[attacker].index].tscore += ALL_SERVER_RANK_WIN + ALL_SERVER_RANK_LOSE + pdata->user[m_uidmap[attacker].index].tcwin*ALL_SERVER_RANK_CW;
		pdata->user[m_uidmap[attacker].index].score += ALL_SERVER_RANK_WIN + ALL_SERVER_RANK_LOSE + pdata->user[m_uidmap[attacker].index].tcwin*ALL_SERVER_RANK_CW;
		++pdata->user[m_uidmap[attacker].index].tcwin;
		if(pdata->user[m_uidmap[attacker].index].score > pdata->user[m_uidmap[attacker].index].shigh)
			pdata->user[m_uidmap[attacker].index].shigh = pdata->user[m_uidmap[attacker].index].score;

		++pdata->user[m_uidmap[defender].index].tbeat;
		++pdata->user[m_uidmap[defender].index].sbeat;
		if(pdata->user[m_uidmap[defender].index].tbeat <= ALL_SERVER_RANK_BT)
		{
			pdata->user[m_uidmap[defender].index].tscore -= ALL_SERVER_RANK_BEAT;
			pdata->user[m_uidmap[defender].index].score -= ALL_SERVER_RANK_BEAT;
			if(pdata->user[m_uidmap[defender].index].score < pdata->user[m_uidmap[defender].index].slow)
				pdata->user[m_uidmap[defender].index].slow = pdata->user[m_uidmap[defender].index].score;
		}

		int hi = pdata->user[m_uidmap[defender].index].flag == AllServerRankFlag_attacking ? 1 : 0;
		for(int i=ALL_SERVER_RANK_HISTORY-1;i>hi;--i)
			pdata->user[m_uidmap[defender].index].history[i] = pdata->user[m_uidmap[defender].index].history[i-1];
		pdata->user[m_uidmap[defender].index].history[hi] = AllServerRankHistory(attacker,AllServerRankResult_Beat,attackername);
		pdata->user[m_uidmap[attacker].index].history[0] = AllServerRankHistory(defender,AllServerRankResult_Win,defendername);

		m_uidmap[attacker] = pdata->user[m_uidmap[attacker].index];
		m_uidmap[defender] = pdata->user[m_uidmap[defender].index];

		pair<AllServerRankScoreMap::iterator,AllServerRankScoreMap::iterator> it;
		AllServerRankScoreMap::iterator iter;
		it = m_scoremap.equal_range(attackerscore);
		for(iter=it.first;iter!=it.second;++iter)
		{
			if(iter->second == attacker)
			{
				m_scoremap.erase(iter);
				break;
			}
		}
		m_scoremap.insert(pair<int,unsigned>(pdata->user[m_uidmap[attacker].index].score,attacker));
		if(pdata->user[m_uidmap[defender].index].tbeat <= ALL_SERVER_RANK_BT)
		{
			it = m_scoremap.equal_range(defenderscore);
			for(iter=it.first;iter!=it.second;++iter)
			{
				if(iter->second == defender)
				{
					m_scoremap.erase(iter);
					break;
				}
			}
			m_scoremap.insert(pair<int,unsigned>(pdata->user[m_uidmap[defender].index].score,defender));
		}
	}
	else
	{
		if(pdata->user[m_uidmap[attacker].index].flag == AllServerRankFlag_attacking)
			pdata->user[m_uidmap[attacker].index].flag = AllServerRankFlag_none;
		else
			return R_ERR_LOGIC;
		pdata->user[m_uidmap[attacker].index].tcwin = 0;
		++pdata->user[m_uidmap[attacker].index].slose;

		++pdata->user[m_uidmap[defender].index].sdefend;

		int i = ALL_SERVER_RANK_HISTORY - 1;
		for(;i>0;--i)
			pdata->user[m_uidmap[defender].index].history[i] = pdata->user[m_uidmap[defender].index].history[i-1];
		pdata->user[m_uidmap[attacker].index].history[0] = AllServerRankHistory(defender,AllServerRankResult_Lose,defendername);
		pdata->user[m_uidmap[defender].index].history[0] = AllServerRankHistory(attacker,AllServerRankResult_Defend,attackername);

		m_uidmap[attacker] = pdata->user[m_uidmap[attacker].index];
		m_uidmap[defender] = pdata->user[m_uidmap[defender].index];
	}

	scoreres = m_uidmap[attacker].score;

	return 0;
}

int CDataAllServerRank::Reward()
{
	bool flag = false;
	if(m_day + 1 >= ALL_SERVER_RANK_SEASON)
		flag = true;

	CLogicUpdates logicUpdates;
	CLogicEquipment logicEquipment;
	CDataUser dataUser;
	Json::Reader reader;
	Json::FastWriter writer;
	unsigned rank = ALL_SERVER_RANK_SEG, r = 1;
	for(AllServerRankScoreMap::reverse_iterator rit=m_scoremap.rbegin();rit!=m_scoremap.rend();++rit)
	{
		while(rank)
		{
			if(rit->first < rank_seg[rank] && rit->first >= rank_seg[rank-1])
				break;
			--rank;
		}
		if(!rank)
			break;

		if(m_uidmap.count(rit->second) && m_uidmap[rit->second].tfight >= 5)
		{
			Json::Value temp,updates;
			if(logicEquipment.AddOneItem(rit->second, rank_reward[rank-1].id,
					flag?rank_reward[rank-1].c2:rank_reward[rank-1].c1,
					flag?"AllServerRankSeason":"AllServerRankDay",temp) == 0)
			{
				updates["s"] = flag?"AllServerRankSeason":"AllServerRankDay";
				updates["rank"] = r;
				updates["point"] = rit->first;
				updates["eqid"] = rank_reward[rank-1].id;
				updates["count"] = flag?rank_reward[rank-1].c2:rank_reward[rank-1].c1;
				updates["seg"] = rank;
				updates["ts"] = Time::GetGlobalTime();
				logicUpdates.AddUpdates(rit->second,updates,true);
			}
			else
				error_log("add rank error uid=%u, point=%u",rit->second,rit->first);
		}

		if(flag && rank == ALL_SERVER_RANK_SEG && r <= ALL_SERVER_RANK_SEG_RANK)
		{
			DataUser user;
			Json::Value tech;
			if(dataUser.GetUser(rit->second, user) == 0)
			{
				if(!user.user_tech.empty() && reader.parse(user.user_tech, tech))
				{
					tech["rank"]["r"] = r;
					tech["rank"]["ts"] = Time::GetGlobalTime() + ALL_SERVER_RANK_SEASON*86400;
					user.user_tech = writer.write(tech);
					if(dataUser.SetUser(rit->second,user) != 0)
						error_log("set tech error uid=%u",rit->second);
				}
				else
					error_log("get tech error uid=%u",rit->second);
			}
			else
				error_log("get user error uid=%u",rit->second);
		}

		++r;
	}

	return 0;
}

int CDataAllServerRank::Rank(string path)
{
	Json::Value data;
	data.resize(ALL_SERVER_RANK_SEG);
	for(unsigned i=0;i<ALL_SERVER_RANK_SEG;++i)
	{
		data[i].resize(ALL_SERVER_RANK_SEG_RANK);

		if(m_scoremap.empty())
			continue;

		AllServerRankScoreMap::iterator it;
		it = m_scoremap.upper_bound(rank_seg[i+1]);
		if(it == m_scoremap.end())
			--it;
		unsigned j=0;
		for(unsigned j=0;j<ALL_SERVER_RANK_SEG_RANK;++j)
		{
			if(m_uidmap.count(it->second))
			{
				if(m_uidmap[it->second].score <= rank_seg[i])
					break;
				data[i][j]["uid"] = m_uidmap[it->second].uid;
				data[i][j]["lvl"] = m_uidmap[it->second].lvl;
				data[i][j]["tfight"] = m_uidmap[it->second].tfight;
				data[i][j]["tcwin"] = m_uidmap[it->second].tcwin;
				data[i][j]["tbeat"] = m_uidmap[it->second].tbeat;
				data[i][j]["swin"] = m_uidmap[it->second].swin;
				data[i][j]["slose"] = m_uidmap[it->second].slose;
				data[i][j]["sbeat"] = m_uidmap[it->second].sbeat;
				data[i][j]["sdefend"] = m_uidmap[it->second].sdefend;
				data[i][j]["shigh"] = m_uidmap[it->second].shigh;
				data[i][j]["slow"] = m_uidmap[it->second].slow;
				data[i][j]["index"] = m_uidmap[it->second].index;
				data[i][j]["tscore"] = m_uidmap[it->second].tscore;
				data[i][j]["score"] = m_uidmap[it->second].score;
				data[i][j]["name"] = m_uidmap[it->second].name;

				if(it == m_scoremap.begin())
					break;
				--it;
			}
		}
	}
	int ret = File::Write(path, Json::ToString(data));
	if(ret)
		cout<<"write AllServerRank fail"<<endl;
	return 0;
}

int CDataAllServerRank::Day()
{
	DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	++pdata->day;
	pdata->dayts = Time::GetGlobalTime();
	if(pdata->day >= ALL_SERVER_RANK_SEASON)
	{
		pdata->day = 0;
		int i = 0, j = pdata->count-1;
		for(;i<=j;++i)
		{
			if(pdata->user[i].swin + pdata->user[i].slose == 0)
			{
				for(;i<=j;--j)
				{
					--pdata->count;
					if(pdata->user[j].swin + pdata->user[j].slose == 0)
					{
						memset(&(pdata->user[j]),0,sizeof(AllServerRankUser));
					}
					else
					{
						pdata->user[i] = pdata->user[j];
						memset(&(pdata->user[j]),0,sizeof(AllServerRankUser));
						break;
					}
				}
				if(i > j)
					break;
			}
			pdata->user[i].tfight = 0;
			pdata->user[i].tcwin = 0;
			pdata->user[i].flag = AllServerRankFlag_none;
			pdata->user[i].tbeat = 0;
			pdata->user[i].tscore = 0;
			pdata->user[i].swin = 0;
			pdata->user[i].slose = 0;
			pdata->user[i].sbeat = 0;
			pdata->user[i].sdefend = 0;
			pdata->user[i].shigh = ALL_SERVER_RANK_START;
			pdata->user[i].slow = ALL_SERVER_RANK_START;
			pdata->user[i].score = ALL_SERVER_RANK_START;
		}
	}
	else
	{
		for(unsigned i=0;i<pdata->count;++i)
		{
			pdata->user[i].tfight = 0;
			pdata->user[i].tcwin = 0;
			pdata->user[i].flag = AllServerRankFlag_none;
			pdata->user[i].tbeat = 0;
			pdata->user[i].tscore = 0;
		}
	}

	//CDATA_ALL_SERVER_RANK_RESTART(pdata)

	return 0;
}

int CDataAllServerRank::Watch()
{
	DataAllServerRank *pdata = (DataAllServerRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	cout<<"count:"<<pdata->count<<" day:"<<pdata->day<<" dayts:"<<pdata->dayts<<endl;
	for(unsigned i=0;i<pdata->count;++i)
	{
		if(pdata->user[i].uid)
			cout<<"uid:"<<pdata->user[i].uid
			<<" score:"<<pdata->user[i].score
			<<" shigh:"<<pdata->user[i].shigh
			<<" slow:"<<pdata->user[i].slow
			<<" tscore:"<<pdata->user[i].tscore
			<<" tfight:"<<pdata->user[i].tfight
			<<" tcwin:"<<pdata->user[i].tcwin
			<<" tbeat:"<<pdata->user[i].tbeat
			<<" swin:"<<pdata->user[i].swin
			<<" slose:"<<pdata->user[i].slose
			<<" sbeat:"<<pdata->user[i].sbeat
			<<" sdefend:"<<pdata->user[i].sdefend
			<<endl;
		else
			break;
	}

	return 0;
}
