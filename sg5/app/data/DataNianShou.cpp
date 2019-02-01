#include "DataNianShou.h"

#define NIANSHOU_ATTACKERS_MAX (NIANSHOU_CHALLENGERS_MAX-1)
#define NIANSHOU_LAST_ATTACK_INDEX (NIANSHOU_CHALLENGERS_MAX-1)


#define STAND_TIME_LEVEL_1 1.3f
#define STAND_TIME_LEVEL_2 1.2f
#define STAND_TIME_LEVEL_3 1.1f
#define STAND_TIME_LEVEL_4 1.0f
#define STAND_TIME_LEVEL_5 0.95f
#define STAND_TIME_LEVEL_6 0.9f
#define STAND_TIME_LEVEL_7 0.85f
#define STAND_TIME_LEVEL_8 0.8f

#define STAND_TIME_ADD_1 10000000
#define STAND_TIME_ADD_2 100000
#define STAND_TIME_ADD_3 0
#define STAND_TIME_ADD_4 -10000000
#define STAND_TIME_ADD_5 -100000

#define STAND_TIME_1 350000000
#define STAND_TIME_2 480000000

#define STAND_TIME_11 5600000
#define STAND_TIME_12 3300000
#define STAND_TIME_13 4100000
#define STAND_TIME_14 5500000
#define STAND_TIME_21 14000000
#define STAND_TIME_22 12000000
#define STAND_TIME_23 9020000
#define STAND_TIME_24 12100000
#define STAND_TIME_31 19600000
#define STAND_TIME_32 15600000
#define STAND_TIME_33 14432000
#define STAND_TIME_34 18150000


CDataNianShou::CDataNianShou()
{
	m_init = false;
}
int CDataNianShou::Init(const string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	if (path.empty())
	{
		error_log("[init_nianshou_fail][path=%s,minbloods=%d ,maxbloods=%d]", path.c_str());
		return R_ERROR;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	int bossId = NIAN_SHOU_ID_MIN;
	for (; bossId <= NIAN_SHOU_ID_MAX; bossId++)
	{
		string mapfile = path;
		if (path[path.length() - 1] != '/')
			mapfile.append("/");
		mapfile.append(CTrans::ITOS(bossId)).append(".nianshou");
		int index = bossId - NIAN_SHOU_ID_MIN;
		//m_maxNianshouBlood[index] = vMaxBlood[index];
		//m_minNianshouBlood[index] = vMinBloods[index];

		if(!m_sh[index].CreateOrOpen(mapfile.c_str(), sizeof(NianShouData), SEM_ID(sem,semgroup,semserver)))
		{
			error_log("[init_nianshou_fail][path=%s]", mapfile.c_str());
			return R_ERROR;
		}
		CAutoLock lock(&(m_sh[index]), true);
		if(!m_sh[index].HasInit())
		{
			NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
			memset(pdata, 0, sizeof(NianShouData));
			m_sh[index].SetInitDone();
		}
	}
	m_init = true;
	return 0;
}

int CDataNianShou::LoadNianShou(unsigned uid, unsigned bossId, unsigned &blood, unsigned &number, int &selfRank, NianShouChallenger &self,
		vector<NianShouChallenger> &top, NianShouChallenger &last,unsigned &fullBlood)
{
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);

	unsigned fullblood;
	if (!Config::GetUIntValue(fullblood, "nianshou_blood"))
		fullblood = 100000000;
	if(!Time::IsToday(pdata->ts) || (pdata->fullBlood == pdata->blood && pdata->fullBlood!=fullblood))
	{
		/*
		if(CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime()) == 0)
		{
			switch(index)
			{
			case 1:
				pdata->fullBlood = STAND_TIME_11;
				break;
			case 2:
				pdata->fullBlood = STAND_TIME_12;
				break;
			case 3:
				pdata->fullBlood = STAND_TIME_13;
				break;
			case 4:
				pdata->fullBlood = STAND_TIME_14;
				break;
			}
		}
		else if(CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime()) == 1)
		{
			switch(index)
			{
			case 1:
				pdata->fullBlood = STAND_TIME_21;
				break;
			case 2:
				pdata->fullBlood = STAND_TIME_22;
				break;
			case 3:
				pdata->fullBlood = STAND_TIME_23;
				break;
			case 4:
				pdata->fullBlood = STAND_TIME_24;
				break;
			}
		}
		else if(CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime()) == 2)
		{
			switch(index)
			{
			case 1:
				pdata->fullBlood = STAND_TIME_31;
				break;
			case 2:
				pdata->fullBlood = STAND_TIME_32;
				break;
			case 3:
				pdata->fullBlood = STAND_TIME_33;
				break;
			case 4:
				pdata->fullBlood = STAND_TIME_34;
				break;
			}
		}
		else if(pdata->fullBlood < STAND_TIME_1)
		{
			float fullBloodLevel;

			if(pdata->blood)
				fullBloodLevel = STAND_TIME_LEVEL_8;
			else if(pdata->standts < 240)
				fullBloodLevel = STAND_TIME_LEVEL_1;
			else if(pdata->standts < 400 )
				fullBloodLevel = STAND_TIME_LEVEL_2;
			else if(pdata->standts < 600 )
				fullBloodLevel = STAND_TIME_LEVEL_3;
			else if(pdata->standts < 900 )
				fullBloodLevel = STAND_TIME_LEVEL_4;
			else if(pdata->standts < 1000)
				fullBloodLevel = STAND_TIME_LEVEL_5;
			else if (pdata->standts < 1200)
				fullBloodLevel = STAND_TIME_LEVEL_6;
			else if (pdata->standts < 1400)
				fullBloodLevel = STAND_TIME_LEVEL_7;
			else
				fullBloodLevel = STAND_TIME_LEVEL_8;

			pdata->fullBlood = pdata->fullBlood * fullBloodLevel;
			if(pdata->fullBlood > STAND_TIME_1)
				pdata->fullBlood = STAND_TIME_1;
		}
		else if(pdata->fullBlood < STAND_TIME_2)
		{
			unsigned fullBloodLevel;

			if(pdata->blood)
				fullBloodLevel = STAND_TIME_ADD_4;
			else if(pdata->standts < 600 )
				fullBloodLevel = STAND_TIME_ADD_1;
			else if(pdata->standts < 900 )
				fullBloodLevel = STAND_TIME_ADD_3;
			else
				fullBloodLevel = STAND_TIME_ADD_4;

			pdata->fullBlood = pdata->fullBlood + fullBloodLevel;
			if(pdata->fullBlood > STAND_TIME_2)
				pdata->fullBlood = STAND_TIME_2;
		}
		else
		{
			unsigned fullBloodLevel;

			if(pdata->blood)
				fullBloodLevel = STAND_TIME_ADD_5;
			else if(pdata->standts < 600 )
				fullBloodLevel = STAND_TIME_ADD_2;
			else if(pdata->standts < 900 )
				fullBloodLevel = STAND_TIME_ADD_3;
			else
				fullBloodLevel = STAND_TIME_ADD_5;

			pdata->fullBlood = pdata->fullBlood + fullBloodLevel;
		}

		if(pdata->fullBlood < m_minNianshouBlood[index])
			pdata->fullBlood = m_minNianshouBlood[index];
		else if(pdata->fullBlood > m_maxNianshouBlood[index])
			pdata->fullBlood = m_maxNianshouBlood[index];*/
		pdata->fullBlood = fullblood;
		pdata->blood = pdata->fullBlood ;
		memset(pdata->challengers, 0, sizeof(pdata->challengers));
		pdata->challNum = 0;
		pdata->showNum = 0;
		pdata->ts = Time::GetGlobalTime();
		pdata->standts = 0;
		pdata->rewarded = false;
	}

	selfRank = 0;
	fullBlood = pdata->fullBlood;

	blood = pdata->blood;
	number = pdata->showNum;
	memset(&self, 0, sizeof(NianShouChallenger));
	for (unsigned i = 0; i < pdata->challNum; i++)
	{
		if ((pdata->challengers[i]).uid == uid)
		{
			selfRank = i + 1;
			memcpy(&self, &(pdata->challengers[i]), sizeof(NianShouChallenger));
			break;
		}
	}
	unsigned size = pdata->challNum >= 10?10 : pdata->challNum;
	for (unsigned i = 0; i < size; i++)
	{
		top.push_back((pdata->challengers)[i]);
	}
	last = pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX];
	return 0;
}

int sortNianshou(const NianShouChallenger& left,const NianShouChallenger& right){
	return left.damage > right.damage;
}

int CDataNianShou::AttackNianShou(unsigned uid, unsigned bossId, unsigned damage, const string &name, const unsigned level, const unsigned kingdom,
		bool &dying, unsigned &blood, unsigned &number, int &selfRank, NianShouChallenger &self,
		vector<NianShouChallenger> &top, NianShouChallenger &last, vector<NianShouChallenger> &lucks
		, vector<NianShouChallenger> &dam, bool bAll, vector<NianShouChallenger> &all)
{
	if (!IsValidNianShouId(bossId))
		return R_ERR_NO_DATA;
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);
	dying = false;
	selfRank = 0;
	if (pdata->blood == 0 || damage == 0)
	{
		blood = pdata->blood;
		//number = pdata->challNum;
		number = pdata->showNum;
		memset(&self, 0, sizeof(NianShouChallenger));
		for (unsigned i = 0; i < pdata->challNum; i++)
		{
			if ((pdata->challengers[i]).uid == uid)
			{
				selfRank = i + 1;
				memcpy(&self, &(pdata->challengers[i]), sizeof(NianShouChallenger));
				break;
			}
		}
		unsigned size = pdata->challNum >= 10?10 : pdata->challNum;
		for (unsigned i = 0; i < size; i++)
		{
			top.push_back((pdata->challengers)[i]);
		}
		last = pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX];
		return 0;
	}
	//add by aaron 20121221
	unsigned now = Time::GetGlobalTime();
	if(pdata->fullBlood == pdata->blood)
	{

		pdata->standts = 0;
		pdata->ts = now;

	}else{
		pdata->standts = now - pdata->ts;
	}
	//add by aaron 20121220
	if (pdata->blood > damage)
	{
		pdata->blood -= damage;
	}
	else
	{
		damage = pdata->blood;
		pdata->blood = 0;
	}
	int pos = 0;
	for (; pos < (int)pdata->challNum; pos++)
	{
		if ((pdata->challengers[pos]).uid == uid)
			break;
	}
	memset(&self, 0, sizeof(NianShouChallenger));
	if (pos < (int)pdata->challNum || pdata->challNum < NIANSHOU_ATTACKERS_MAX)
	{
		unsigned newDamage = damage;
		if (pos < (int)pdata->challNum)
			 newDamage += (pdata->challengers[pos]).damage;
		int newpos = pos - 1;
		for (; newpos >= 0; newpos--)
		{
			if ((pdata->challengers[newpos]).damage >= newDamage)
				break;
		}
		newpos++;
		//前10名才按顺序排序
		if(newpos < 10)
		{
			for (int i = pos - 1; i >= newpos; i--)
			{
				pdata->challengers[i+1] = pdata->challengers[i];
			}
			(pdata->challengers[newpos]).uid = uid;
			(pdata->challengers[newpos]).damage = newDamage;
			snprintf((pdata->challengers[newpos]).name, sizeof((pdata->challengers[newpos]).name), "%s", name.c_str());
			(pdata->challengers[newpos]).kingdom = kingdom;
			(pdata->challengers[newpos]).level = level;
		}
		else
		{
			(pdata->challengers[pos]).uid = uid;
			(pdata->challengers[pos]).damage = newDamage;
			snprintf((pdata->challengers[pos]).name, sizeof((pdata->challengers[pos]).name), "%s", name.c_str());
			(pdata->challengers[pos]).kingdom = kingdom;
			(pdata->challengers[pos]).level = level;
		}

		if (pos >= (int)pdata->challNum)
		{
			pdata->challNum++;
			if(pdata-> challNum >= 10)
			{
				int r = Math::GetRandomInt(2);
				switch(r)
				{
				case 0:
					pdata->showNum += 1;
					break;
				case 1:
					pdata->showNum += 3;
					break;
				default:
					pdata->showNum += 2;
					break;
				}
			}else{
				pdata->showNum = pdata->challNum;
			}

		}
		if(newpos < 10)
		{
			memcpy(&self, &(pdata->challengers[newpos]), sizeof(NianShouChallenger));
		}
		else
		{
			memcpy(&self, &(pdata->challengers[pos]), sizeof(NianShouChallenger));
		}
		selfRank = newpos + 1;
		if (pdata->blood == 0)
		{
			pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX] = pdata->challengers[newpos];	//最后一击
		}
	}
	else
	{
		if (pdata->blood == 0)
		{
			(pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX]).uid = uid;
			(pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX]).damage = damage;
			snprintf((pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX]).name,
					sizeof((pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX]).name), "%s", name.c_str());
		}
	}
	blood = pdata->blood;

//	if(pdata->challNum > 10 && pdata->standts > 600)
//	{
//		if(pdata->showNum < 1000)
//		{
//			pdata->showNum += 1;
//		}else{
//			pdata->showNum = 1000;
//		}
//	}else{
//		pdata->showNum = pdata->challNum;
//	}
	number = pdata->showNum;
	if (pdata->blood == 0)
	{
		dying = true;
		vector<NianShouChallenger> sortend;
		int i;
		for(i = 0 ;i < NIANSHOU_LAST_ATTACK_INDEX; i++)
			sortend.push_back(pdata->challengers[i]);
		sort(sortend.begin(),sortend.end(),sortNianshou);
		for(i = 0 ;i < NIANSHOU_LAST_ATTACK_INDEX; i++)
			pdata->challengers[i] = sortend[i];
	}

	unsigned size = pdata->challNum >= 10?10 : pdata->challNum;
	for (unsigned i = 0; i < size; i++)
	{
		top.push_back((pdata->challengers)[i]);
	}
	last = pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX];
	if (pdata->blood == 0 && pdata->challNum > 10)
	{
		for (unsigned r = 20; r <= pdata->challNum; r += 10)
		{
			lucks.push_back((pdata->challengers)[r-1]);
		}
	}
	if (pdata->blood == 0)
	{
		for (unsigned j = 0; j < pdata->challNum; j++)
		{
			if((pdata->challengers)[j].damage >= pdata->fullBlood / 100)
				dam.push_back((pdata->challengers)[j]);
			if(bAll)
				all.push_back((pdata->challengers)[j]);
		}
	}
	return 0;
}

int CDataNianShou::ViewNianShou(unsigned uid, unsigned bossId, unsigned &blood,unsigned &fullBlood, unsigned &number, int &selfRank, NianShouChallenger &self,
		vector<NianShouChallenger> &top, NianShouChallenger &last)
{
	if (!IsValidNianShouId(bossId))
		return R_ERR_NO_DATA;
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);
	selfRank = 0;
	blood = pdata->blood;
	//number = pdata->challNum;
	number = pdata->showNum;
	fullBlood = pdata->fullBlood;
	memset(&self, 0, sizeof(NianShouChallenger));
	for (unsigned i = 0; i < pdata->challNum; i++)
	{
		if ((pdata->challengers[i]).uid == uid)
		{
			selfRank = i + 1;
			memcpy(&self, &(pdata->challengers[i]), sizeof(NianShouChallenger));
			break;
		}
	}
	unsigned size = pdata->challNum >= 10?10 : pdata->challNum;
	for (unsigned i = 0; i < size; i++)
	{
		top.push_back((pdata->challengers)[i]);
	}
	last = pdata->challengers[NIANSHOU_LAST_ATTACK_INDEX];
	return 0;
}
int CDataNianShou::ViewNianShou( unsigned bossId, unsigned &blood, unsigned &fullblood, unsigned &standts, unsigned ts)
{
	if (!IsValidNianShouId(bossId))
		return R_ERR_NO_DATA;
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);
	pdata->blood = blood ;
	pdata->fullBlood =fullblood;
	pdata->ts = ts;
	pdata->standts = standts;
	return 0;
}
int CDataNianShou::SetNianShou( unsigned bossId, unsigned blood, unsigned fullblood, unsigned standts, unsigned ts)
{
	if (!IsValidNianShouId(bossId))
		return R_ERR_NO_DATA;
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);
	blood = pdata->blood  ;
	fullblood = pdata->fullBlood;
	ts = pdata->ts ;
	standts = pdata->standts;
	return 0;
}

int CDataNianShou::SetRewarded(unsigned bossId)
{
	if (!IsValidNianShouId(bossId))
		return R_ERR_NO_DATA;
	int index = bossId - NIAN_SHOU_ID_MIN;
	NianShouData *pdata = (NianShouData *)m_sh[index].GetAddress();
	if(pdata == NULL)
	{
		error_log("[GetAddress fail][]");
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh[index]), true);
	debug_log("reward=%u,challNum=%u,uid=%u,damage=%u",pdata->rewarded,pdata->challNum,pdata->challengers[0].uid,pdata->challengers[0].damage);
	if (pdata->rewarded)
		return R_ERR_LOGIC;
	pdata->rewarded = true;
	return 0;
}

