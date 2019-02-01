#include "DataAllianceBattle.h"

CDataAllianceBattle::CDataAllianceBattle()
{
	m_init = false;
}

int CDataAllianceBattle::Init(const string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	if (path.empty())
	{
		error_log("[init_allianceBattle_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	int allianceBattleId = 0;
	for (; allianceBattleId < AB_CITY_NUM; allianceBattleId++)
	{
		string mapfile = path;
		if (path[path.length() - 1] != '/')
			mapfile.append("/");
		mapfile.append(CTrans::ITOS(allianceBattleId)).append(".allianceBattle");
		if(!m_sh[allianceBattleId].CreateOrOpen(mapfile.c_str()
				, allianceBattleId != KINGDOM_K_CITY_NUM ? sizeof(DataAllianceBattle) : sizeof(DataAllianceBattle_K)
				, SEM_ID(sem,semgroup,semserver)))
		{
			error_log("[init_allianceBattle_data_fail][path=%s]", mapfile.c_str());
			return R_ERROR;
		}
		CAutoLock lock(&(m_sh[allianceBattleId]), true);
		if(!m_sh[allianceBattleId].HasInit())
		{
			if(allianceBattleId != KINGDOM_K_CITY_NUM)
			{
				DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[allianceBattleId].GetAddress();
				memset(pdata, 0, sizeof(*pdata));
				m_sh[allianceBattleId].SetInitDone();
			}
			else
			{
				DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[allianceBattleId].GetAddress();
				memset(pdata, 0, sizeof(*pdata));
				m_sh[allianceBattleId].SetInitDone();
			}
		}
	}
	m_init = true;
	return 0;
}

int CDataAllianceBattle::GetCityLimit(unsigned cid, DataAllianceBattleLimit &data)
{
	unsigned cnum = Cid2CityNum(cid);
	if(cnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(data,*pdata);
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(data,*pdata);
	}
	return 0;
}
int CDataAllianceBattle::SetCityLimit(unsigned cid, DataAllianceBattleLimit &data)
{
	unsigned cnum = Cid2CityNum(cid);
	if(cnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(*pdata,data);
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(*pdata,data);
	}
	return 0;
}
int CDataAllianceBattle::GetAllCityLimit(DataAllianceBattleLimit *data)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			copylimit(data[i],*pdata);
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			copylimit(data[i],*pdata);
		}
	}
	return 0;
}
int CDataAllianceBattle::SetAllCityLimit(DataAllianceBattleLimit *data)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			copylimit(*pdata,data[i]);
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			copylimit(*pdata,data[i]);
		}
	}
	return 0;
}
int CDataAllianceBattle::GetCityPrice(unsigned cid, CityPrice *price)
{
	unsigned cnum = Cid2CityNum(cid);
	if(cnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		for(unsigned i=0;i<PRICE_NUM;++i)
			price[i] = pdata->price[i];
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		for(unsigned i=0;i<PRICE_NUM;++i)
			price[i] = pdata->price[i];
	}
	return 0;
}
int CDataAllianceBattle::SetCityPrice(unsigned cid, CityPrice *price)
{
	unsigned cnum = Cid2CityNum(cid);
	if(cnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		for(unsigned i=0;i<PRICE_NUM;++i)
			pdata->price[i] = price[i];
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		for(unsigned i=0;i<PRICE_NUM;++i)
			pdata->price[i] = price[i];
	}
	return 0;
}
int CDataAllianceBattle::GetAllCityPrice(vector<vector<CityPrice> > &price)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			for(unsigned j=0;j<PRICE_NUM;++j)
				price[i][j] = pdata->price[j];
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			for(unsigned j=0;j<PRICE_NUM;++j)
				price[i][j] = pdata->price[j];
		}
	}
	return 0;
}
int CDataAllianceBattle::ClearAllCityPrice()
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			memset(pdata->price,0,sizeof(pdata->price));
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			memset(pdata->price,0,sizeof(pdata->price));
		}
	}
	return 0;
}
int CDataAllianceBattle::GetCityBattlePointLimit(unsigned cid, BattlePointLimit *defence, BattlePointLimit *attack)
{
	unsigned cnum = Cid2CityNum(cid);
	if(cnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		unsigned i=0;
		for(;i<BATTLE_NUM;++i)
			copylimit(defence[i],pdata->point[i]);
		for(;i<BATTLE_NUM*2;++i)
			copylimit(attack[i-BATTLE_NUM],pdata->point[i]);
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		unsigned i=0;
		for(;i<BATTLE_NUM_K;++i)
			copylimit(defence[i],pdata->point[i]);
		for(;i<BATTLE_NUM_K*2;++i)
			copylimit(attack[i-BATTLE_NUM_K],pdata->point[i]);
	}
	return 0;
}
int CDataAllianceBattle::GetAllBattlePointLimit(vector<vector<BattlePointLimit> > &defence, vector<vector<BattlePointLimit> > &attack)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM;++j)
				copylimit(defence[i][j],pdata->point[j]);
			for(;j<BATTLE_NUM*2;++j)
				copylimit(attack[i][j-BATTLE_NUM],pdata->point[j]);
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM_K;++j)
				copylimit(defence[i][j],pdata->point[j]);
			for(;j<BATTLE_NUM_K*2;++j)
				copylimit(attack[i][j-BATTLE_NUM_K],pdata->point[j]);
		}
	}
	return 0;
}
int CDataAllianceBattle::ClearAllBattlePoint()
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			memset(pdata->point,0,sizeof(pdata->point));
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			memset(pdata->point,0,sizeof(pdata->point));
		}
	}
	return 0;
}
int CDataAllianceBattle::SetAllBattlePointLimit(vector<vector<BattlePointLimit> > &defence, vector<vector<BattlePointLimit> > &attack)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM;++j)
				copylimit(pdata->point[j] , defence[i][j]);
			for(;j<BATTLE_NUM*2;++j)
				copylimit(pdata->point[j] , attack[i][j-BATTLE_NUM]);
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM_K;++j)
				copylimit(pdata->point[j] , defence[i][j]);
			for(;j<BATTLE_NUM_K*2;++j)
				copylimit(pdata->point[j] , attack[i][j-BATTLE_NUM_K]);
		}
	}
	return 0;
}
int CDataAllianceBattle::SetAllBattlePoint(vector<vector<BattlePoint> > &defence, vector<vector<BattlePoint> > &attack)
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM;++j)
				pdata->point[j] = defence[i][j];
			for(;j<BATTLE_NUM*2;++j)
				pdata->point[j] = attack[i][j-BATTLE_NUM];
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);
			unsigned j=0;
			for(;j<BATTLE_NUM_K;++j)
				pdata->point[j] = defence[i][j];
			for(;j<BATTLE_NUM_K*2;++j)
				pdata->point[j] = attack[i][j-BATTLE_NUM_K];

		}
	}
	return 0;
}
int CDataAllianceBattle::GetBattlePointLimit(unsigned bid, BattlePointLimit &data)
{
	unsigned cnum = Bid2CityNum(bid);
	if(cnum == -1)
		return R_ERR_PARAM;
	unsigned bnum = Bid2BattleNum(bid);
	if(bnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(data,pdata->point[bnum]);
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(data,pdata->point[bnum]);
	}
	return 0;
}
int CDataAllianceBattle::SetBattlePointLimit(unsigned bid, BattlePointLimit &data)
{
	unsigned cnum = Bid2CityNum(bid);
	if(cnum == -1)
		return R_ERR_PARAM;
	unsigned bnum = Bid2BattleNum(bid);
	if(bnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(pdata->point[bnum],data);
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		copylimit(pdata->point[bnum],data);
	}
	return 0;
}
int CDataAllianceBattle::GetBattlePoint(unsigned bid, BattlePoint &data)
{
	unsigned cnum = Bid2CityNum(bid);
	if(cnum == -1)
		return R_ERR_PARAM;
	unsigned bnum = Bid2BattleNum(bid);
	if(bnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		data = pdata->point[bnum];
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		data = pdata->point[bnum];
	}
	return 0;
}
int CDataAllianceBattle::SetBattlePoint(unsigned bid, BattlePoint &data)
{
	unsigned cnum = Bid2CityNum(bid);
	if(cnum == -1)
		return R_ERR_PARAM;
	unsigned bnum = Bid2BattleNum(bid);
	if(bnum == -1)
		return R_ERR_PARAM;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		pdata->point[bnum] = data;
	}
	else
	{
		DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[cnum].GetAddress();
		if(pdata == NULL)
		{
			return R_ERR_DB;
		}
		CAutoLock lock(&(m_sh[cnum]), true);
		pdata->point[bnum] = data;
	}
	return 0;
}
int CDataAllianceBattle::Cid2CityNum(unsigned cid)
{
	unsigned type = cid / CITY_RAG;
	unsigned num = cid % CITY_RAG;
	if(type == 0 && num < KINGDOM_1_CITY_NUM)
		return num;
	if((type == 1 || type == 2 || type ==3) && num < C_CITY_NUM)
		return M_CITY_NUM + (type - 1) * C_CITY_NUM + num;
	if((type == 4) && num < K_CITY_NUM)
			return KINGDOM_K_CITY_NUM;
	return -1;
}
int CDataAllianceBattle::Bid2BattleNum(unsigned bid)
{
	unsigned cnum = Bid2CityNum(bid);
	unsigned bnum = bid%100;
	if(cnum != KINGDOM_K_CITY_NUM)
	{
		if(bnum < BATTLE_NUM * 2)
			return bnum;
	}
	else
	{
		if(bnum < BATTLE_NUM_K * 2)
			return bnum;
	}
	return -1;
}
int CDataAllianceBattle::Bid2CityNum(unsigned bid)
{
	return Cid2CityNum(bid/100%100);
}

void CDataAllianceBattle::copylimit(BattlePoint &to,const BattlePointLimit &from)
{
	to.aid = from.aid;
	to.uid = from.uid;
	strcpy(to.name,from.name);
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.breathTs = from.breathTs;
}
void CDataAllianceBattle::copylimit(BattlePointLimit &to,const BattlePoint &from)
{
	to.aid = from.aid;
	to.uid = from.uid;
	strcpy(to.name,from.name);
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.breathTs = from.breathTs;
}
void CDataAllianceBattle::copylimit(DataAllianceBattle &to,const DataAllianceBattleLimit &from)
{
	to.aid = from.aid;
	strcpy(to.name,from.name);
	to.flag = from.flag;
	to.kingdom = from.kingdom;
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.stage = from.stage;
}
void CDataAllianceBattle::copylimit(DataAllianceBattleLimit &to,const DataAllianceBattle &from)
{
	to.aid = from.aid;
	strcpy(to.name,from.name);
	to.flag = from.flag;
	to.kingdom = from.kingdom;
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.stage = from.stage;
}
void CDataAllianceBattle::copylimit(DataAllianceBattle_K &to,const DataAllianceBattleLimit &from)
{
	to.aid = from.aid;
	strcpy(to.name,from.name);
	to.flag = from.flag;
	to.kingdom = from.kingdom;
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.stage = from.stage;
}
void CDataAllianceBattle::copylimit(DataAllianceBattleLimit &to,const DataAllianceBattle_K &from)
{
	to.aid = from.aid;
	strcpy(to.name,from.name);
	to.flag = from.flag;
	to.kingdom = from.kingdom;
	to.challenger = from.challenger;
	strcpy(to.challengername,from.challengername);
	to.stage = from.stage;
}

int CDataAllianceBattle::RepairAllianceID()
{
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			DataAllianceBattle *pdata = (DataAllianceBattle *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);

			if(pdata->aid > 4000000000)
				pdata->aid -= 2000000000;
		}
		else
		{
			DataAllianceBattle_K *pdata = (DataAllianceBattle_K *)m_sh[i].GetAddress();
			if(pdata == NULL)
			{
				return R_ERR_DB;
			}
			CAutoLock lock(&(m_sh[i]), true);

			if(pdata->aid > 4000000000)
				pdata->aid -= 2000000000;
		}
	}
	return 0;
}
