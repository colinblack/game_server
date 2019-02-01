#include "LogicAllianceBattle.h"

CDataAllianceBattle* CLogicAllianceBattle::GetCDataAllianceBattle()
{
	GET_MEM_DATA_SEM(CDataAllianceBattle, CONFIG_ALLIANCE_BATTLE_DIR, sem_alliance_battle,false);
}

int CLogicAllianceBattle::GetAllCityLimit(Json::Value &result)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[GetAllCityLimit][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetAllCityLimit_fail");
	}

	CLogicAlliance logicAlliance;
	result.resize(AB_CITY_NUM);
	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		result[i]["aid"] = data[i].aid;
		result[i]["name"] = data[i].name;
		result[i]["flag"] = data[i].flag;
		result[i]["kingdom"] = data[i].kingdom;
		result[i]["challenger"] = data[i].challenger;
		result[i]["challengername"] = data[i].challengername;
		result[i]["stage"] = data[i].stage;

		/*
		DataAlliance alliance;
		if(logicAlliance.GetAllianceLimit(data[i].aid, alliance) == 0)
			result[i]["kingdom"] = alliance.kingdom;
		else
			result[i]["kingdom"] = 0;
		*/
	}
	return 0;
}

int CLogicAllianceBattle::GetCityPrice(unsigned cid, Json::Value &result)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[GetCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetCityPrice_fail");
	}

	if(city.stage != AllianceBattle_Price)
		return 0;

	CityPrice data[PRICE_NUM];
	ret = dataAllianceBattle->GetCityPrice(cid,data);
	if (ret != 0)
	{
		error_log("[GetCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetCityPrice_fail");
	}

	result.resize(PRICE_NUM);
	for(unsigned i=0;i<PRICE_NUM;++i)
	{
		result[i]["aid"] = data[i].aid;
		result[i]["name"] = data[i].name;
		result[i]["price"] = data[i].price;
	}
	return 0;
}

int CLogicAllianceBattle::GetAllCityPrice(Json::Value &result)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	vector<vector<CityPrice> > price;
	price.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
		price[k].resize(PRICE_NUM);
	int ret = dataAllianceBattle->GetAllCityPrice(price);
	if (ret != 0)
	{
		error_log("[GetCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetCityPrice_fail");
	}

	result.resize(AB_CITY_NUM);
	for(unsigned j=0;j<AB_CITY_NUM;++j)
	{
		result[j].resize(PRICE_NUM);
		for(unsigned i=0;i<PRICE_NUM;++i)
		{
			result[j][i]["aid"] = price[j][i].aid;
			result[j][i]["name"] = price[j][i].name;
			result[j][i]["price"] = price[j][i].price;
		}
	}
	return 0;
}

int CLogicAllianceBattle::PayCityPrice(unsigned cid, unsigned aid, string &name)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[PayCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("PayCityPrice_fail");
	}

	if(city.stage != AllianceBattle_Price)
		return 0;

	CityPrice data[PRICE_NUM];
	ret = dataAllianceBattle->GetCityPrice(cid,data);
	if (ret != 0)
	{
		error_log("[PayCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("PayCityPrice_fail");
	}

	int price = data[0].price;
	if(cid >= CITY_RAG && cid%CITY_RAG == 0)
		price += PRICE_K;
	else
		price += PRICE_NK;

	unsigned i=0;
	for(;i<PRICE_NUM;++i)
	{
		if(data[i].aid == aid)
			break;
	}
	unsigned j;
	if(i == PRICE_NUM)
		j = PRICE_NUM - 1;
	else
		j = i;
	for(;j>0;--j)
		data[j] = data[j-1];
	data[0].aid = aid;
	data[0].price = price;
	strcpy(data[0].name, name.c_str());

	ret = dataAllianceBattle->SetCityPrice(cid,data);
	if (ret != 0)
	{
		error_log("[PayCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("PayCityPrice_fail");
	}

	return 0;
}

int CLogicAllianceBattle::StartDefence()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartDefence_fail");
	}

	vector<vector<CityPrice> > price;
	price.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
		price[k].resize(PRICE_NUM);
	ret = dataAllianceBattle->GetAllCityPrice(price);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartDefence_fail");
	}

	vector<vector<BattlePointLimit> > defencelimit,attacklimit;
	defencelimit.resize(AB_CITY_NUM);
	attacklimit.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
	{
		if(k != KINGDOM_K_CITY_NUM)
		{
			defencelimit[k].resize(BATTLE_NUM);
			attacklimit[k].resize(BATTLE_NUM);
		}
		else
		{
			defencelimit[k].resize(BATTLE_NUM_K);
			attacklimit[k].resize(BATTLE_NUM_K);
		}
	}
	ret = dataAllianceBattle->GetAllBattlePointLimit(defencelimit,attacklimit);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}

	for(unsigned i=0;i<AB_CITY_NUM;++i)
	{
		if(data[i].stage != AllianceBattle_Price)
			continue;

		for(unsigned j=0;j<PRICE_NUM;++j)
		{
			if(price[i][j].price && IsAllianceId(price[i][j].aid))
			{
				CLogicAlliance logicAlliance;
				ret = logicAlliance.ChangeResource(price[i][j].aid, 0, 0, 0, 0, 0, -price[i][j].price, "AllBat");
				if(ret == 0)
				{
					if(i == KINGDOM_K_CITY_NUM)
					{
						DataAlliance alliance;
						if(logicAlliance.GetAllianceLimit(price[i][j].aid, alliance) == 0)
							data[i].challenger = alliance.kingdom;
						else
							data[i].challenger = 0;
					}
					else
						data[i].challenger = price[i][j].aid;
					strcpy(data[i].challengername,price[i][j].name);
					data[i].stage = AllianceBattle_Defence;
					if(i != KINGDOM_K_CITY_NUM)
					{
						for(unsigned k = 0;k<BATTLE_NUM;++k)
						{
							defencelimit[i][k].aid = data[i].aid;
							attacklimit[i][k].aid = data[i].challenger;
						}
					}
					else
					{
						for(unsigned k = 0;k<BATTLE_NUM_K;++k)
						{
							defencelimit[i][k].aid = data[i].aid;
							attacklimit[i][k].aid = data[i].challenger;
						}
					}

					CLogicAlliance logicAlliance;
					Json::Value updates;
					updates["s"] = "chibi";
					updates["cb_gold"] = price[i][j].price;
					updates["ts"] = Time::GetGlobalTime();
					logicAlliance.AllianceUpdate(data[i].challenger,updates);
					logicAlliance.AllianceUpdate(data[i].aid,updates);

					break;
				}
			}
		}
		if(data[i].challenger == 0)
			data[i].stage = AllianceBattle_max;
	}

	dataAllianceBattle->ClearAllCityPrice();
	ret = dataAllianceBattle->SetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartDefence_fail");
	}
	ret = dataAllianceBattle->SetAllBattlePointLimit(defencelimit, attacklimit);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}
	return 0;
}

int CLogicAllianceBattle::GetAllBattlePointLimit(unsigned cid, Json::Value &result)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[GetAllBattlePointLimit][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("PayCityPrice_fail");
	}

	if(city.stage != AllianceBattle_Defence && city.stage != AllianceBattle_Attack)
		return 0;

	BattlePointLimit defence[BATTLE_NUM_K],attack[BATTLE_NUM_K];
	ret = dataAllianceBattle->GetCityBattlePointLimit(cid,defence,attack);
	if (ret != 0)
	{
		error_log("[GetAllBattlePointLimit][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetAllBattlePointLimit_fail");
	}

	unsigned len;
	if(cid != CITY_K_ID)
		len = BATTLE_NUM;
	else
		len = BATTLE_NUM_K;
	result.resize(len*2);
	unsigned i=0;
	for(;i<len;++i)
	{
		result[i]["aid"] = defence[i].aid;
		result[i]["uid"] = defence[i].uid;
		result[i]["name"] = defence[i].name;
		result[i]["challenger"] = defence[i].challenger;
		result[i]["challengername"] = defence[i].challengername;
		result[i]["breathTs"] = defence[i].breathTs;
	}
	for(;i<len*2;++i)
	{
		result[i]["aid"] = attack[i-len].aid;
		result[i]["uid"] = attack[i-len].uid;
		result[i]["name"] = attack[i-len].name;
		result[i]["challenger"] = attack[i-len].challenger;
		result[i]["challengername"] = attack[i-len].challengername;
		result[i]["breathTs"] = attack[i-len].breathTs;
	}
	return 0;
}

int CLogicAllianceBattle::SetDefence(unsigned bid, unsigned uid, const string &name)
{
	if (!IsValidAllianceBattleId(bid))
		return -1;

	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	unsigned cid = bid/100%100;
	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[SetDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetDefence_fail");
	}

	if(city.stage != AllianceBattle_Defence)
		return 0;

	BattlePointLimit data;
	ret = dataAllianceBattle->GetBattlePointLimit(bid,data);
	if (ret != 0)
	{
		error_log("[SetDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetDefence_fail");
	}

	data.uid = uid;
	strcpy(data.name, name.c_str());
	ret = dataAllianceBattle->SetBattlePointLimit(bid,data);
	if (ret != 0)
	{
		error_log("[SetDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("SetDefence_fail");
	}

	return 0;
}

int CLogicAllianceBattle::StartAttack()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartAttack][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}

	vector<vector<BattlePointLimit> > defencelimit,attacklimit;
	defencelimit.resize(AB_CITY_NUM);
	attacklimit.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
	{
		if(k != KINGDOM_K_CITY_NUM)
		{
			defencelimit[k].resize(BATTLE_NUM);
			attacklimit[k].resize(BATTLE_NUM);
		}
		else
		{
			defencelimit[k].resize(BATTLE_NUM_K);
			attacklimit[k].resize(BATTLE_NUM_K);
		}
	}
	ret = dataAllianceBattle->GetAllBattlePointLimit(defencelimit,attacklimit);
	if (ret != 0)
	{
		error_log("[StartAttack][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}

	unsigned i,j;
	vector<vector<BattlePoint> > defence,attack;
	defence.resize(AB_CITY_NUM);
	attack.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
	{
		if(k != KINGDOM_K_CITY_NUM)
		{
			defence[k].resize(BATTLE_NUM);
			attack[k].resize(BATTLE_NUM);
		}
		else
		{
			defence[k].resize(BATTLE_NUM_K);
			attack[k].resize(BATTLE_NUM_K);
		}
	}
	for(i=0;i<AB_CITY_NUM;++i)
	{
		if(i != KINGDOM_K_CITY_NUM)
		{
			for(j=0;j<BATTLE_NUM;++j)
				CDataAllianceBattle::copylimit(defence[i][j],defencelimit[i][j]);
			for(j=0;j<BATTLE_NUM;++j)
				CDataAllianceBattle::copylimit(attack[i][j],attacklimit[i][j]);
		}
		else
		{
			for(j=0;j<BATTLE_NUM_K;++j)
				CDataAllianceBattle::copylimit(defence[i][j],defencelimit[i][j]);
			for(j=0;j<BATTLE_NUM_K;++j)
				CDataAllianceBattle::copylimit(attack[i][j],attacklimit[i][j]);
		}
	}

	for(i=0;i<AB_CITY_NUM;++i)
	{
		unsigned len;
		if(i != KINGDOM_K_CITY_NUM)
			len = BATTLE_NUM;
		else
			len = BATTLE_NUM_K;
		if(data[i].stage != AllianceBattle_Defence)
		{
			for(unsigned k=0;k<len;++k)
			{
				memset(&defence[i][k],0,sizeof(BattlePointLimit));
				memset(&attack[i][k],0,sizeof(BattlePointLimit));
			}
			continue;
		}

		data[i].stage = AllianceBattle_Attack;

		for(j=0;j<len;++j)
		{
			int npcid;
			if(j==0)
				npcid = ALLIANCE_NPC_BIG;
			else
				npcid = ALLIANCE_NPC;

			defence[i][j].challenger = 0;
			memset(defence[i][j].challengername, 0, sizeof(defence[i][j].challengername));
			defence[i][j].breathTs = 0;
			if(IsValidUid(defence[i][j].uid))
			{
				memset(defence[i][j].archive, 0, sizeof(defence[i][j].archive));
				ret = SetArchive(BattleNum2Bid(i,j,true), defence[i][j].uid,defence[i][j].archive);
				if(ret)
				{
					defence[i][j].uid = npcid;
					memset(defence[i][j].name, 0, sizeof(defence[i][j].name));
					SetNPC(BattleNum2Bid(i,j,true), npcid,defence[i][j].archive);
				}
			}
			else
			{
				defence[i][j].uid = npcid;
				memset(defence[i][j].name, 0, sizeof(defence[i][j].name));
				SetNPC(BattleNum2Bid(i,j,true), npcid,defence[i][j].archive);
			}

			attack[i][j].challenger = 0;
			memset(attack[i][j].challengername, 0, sizeof(attack[i][j].challengername));
			attack[i][j].breathTs = 0;
			if(IsValidUid(attack[i][j].uid))
			{
				memset(attack[i][j].archive, 0, sizeof(attack[i][j].archive));
				ret = SetArchive(BattleNum2Bid(i,j,false),attack[i][j].uid,attack[i][j].archive);
				if(ret)
				{
					attack[i][j].uid = npcid;
					memset(attack[i][j].name, 0, sizeof(attack[i][j].name));
					SetNPC(BattleNum2Bid(i,j,true), npcid,attack[i][j].archive);
				}
			}
			else
			{
				attack[i][j].uid = npcid;
				memset(attack[i][j].name, 0, sizeof(attack[i][j].name));
				SetNPC(BattleNum2Bid(i,j,true), npcid,attack[i][j].archive);
			}
		}
	}

	ret = dataAllianceBattle->SetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartAttack][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}
	ret = dataAllianceBattle->SetAllBattlePoint(defence, attack);
	if (ret != 0)
	{
		error_log("[StartAttack][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}

	return 0;
}

int CLogicAllianceBattle::Load(unsigned bid, DataUser &userBy, LoadType loadType, Json::Value &result)
{
	unsigned uidBy = userBy.uid;
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	unsigned cid = bid/100%100;
	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[Load][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Load_fail");
	}
	if(city.stage != AllianceBattle_Attack)
		return 0;

	unsigned aid = cid == CITY_K_ID ? userBy.kingdom : userBy.alliance_id;

	BattlePointLimit defence[BATTLE_NUM_K],attack[BATTLE_NUM_K];
	ret = dataAllianceBattle->GetCityBattlePointLimit(cid,defence,attack);
	if (ret != 0)
	{
		error_log("[Load][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Load_fail");
	}
	if(defence[0].aid == city.challenger || attack[0].aid == city.aid)
	{
		error_log("[Load][ret=%d]",ret);
		string banMsg = "ban_attack_7";
		LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
	}

	unsigned len;
	if(cid != CITY_K_ID)
		len = BATTLE_NUM;
	else
		len = BATTLE_NUM_K;

	if(bid%100 == 0)
	{
		unsigned i = 1;
		for(;i<len;++i)
		{
			if(defence[i].aid != city.challenger)
			{
				error_log("[Load][ret=%d]",ret);
				string banMsg = "ban_attack_7";
				LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
			}
		}
	}
	if(bid%100 == len)
	{
		unsigned i = 1;
		for(;i<len;++i)
		{
			if(attack[i].aid != city.aid)
			{
				error_log("[Load][ret=%d]",ret);
				string banMsg = "ban_attack_7";
				LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
			}
		}
	}

	BattlePoint data;
	ret = dataAllianceBattle->GetBattlePoint(bid,data);
	if (ret != 0)
	{
		error_log("[Load][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Load_fail");
	}
	if(data.aid == aid)
	{
		error_log("[Load][ret=%d]",ret);
		string banMsg = "ban_attack_7";
		LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
	}
	if(IsBeingAttacked(data.breathTs))
	{
		error_log("[Load][ret=%d]",ret);
		string banMsg = "ban_attack_7";
		LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
	}

	Json::Reader reader;
	if(!reader.parse(data.archive, result))
	{
		error_log("[Load][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Load_fail");
	}

	DataUserBasic userByBasic;
	CLogicUserBasic logicUserBasic;
	logicUserBasic.GetUserBasicLimit(uidBy,(PlatformType)0,userByBasic);

	data.challenger = uidBy;
	data.breathTs = Time::GetGlobalTime();
	strcpy(data.challengername, userByBasic.name.c_str());

	result["userid"] = bid;

	BattlePointLimit temp;
	CDataAllianceBattle::copylimit(temp,data);
	ret = dataAllianceBattle->SetBattlePointLimit(bid,temp);
	if (ret != 0)
	{
		error_log("[Load][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Load_fail");
	}

	return 0;
}

int CLogicAllianceBattle::Save(unsigned bid, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype)
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	unsigned cid = bid/100%100;
	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}
	if(city.stage != AllianceBattle_Attack)
		return 0;

	BattlePointLimit defence[BATTLE_NUM_K],attack[BATTLE_NUM_K];
	ret = dataAllianceBattle->GetCityBattlePointLimit(cid,defence,attack);
	if (ret != 0)
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}
	if(defence[0].aid == city.challenger || attack[0].aid == city.aid)
	{
		error_log("[Save][ret=%d]",ret);
		return 0;
	}

	BattlePoint point;
	ret = dataAllianceBattle->GetBattlePoint(bid,point);
	if (ret != 0)
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}
	if(point.challenger != userBy.uid)
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}

	if (Json::IsObject(data, "attackinfo"))
	{
		CLogicArchive logicArchive;
		ret = logicArchive.ProcessAttackInfo(userBy.uid, data["attackinfo"], result["attackinfo"], bid, loadtype);
		if (ret != 0)
			return ret;
	}

	Json::Reader reader;
	Json::Value pointjson;
	if(!reader.parse(point.archive, pointjson))
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}

	int damage = 0;
	Json::GetInt(data, "damage", damage);
	if (damage > 99)
	{
		/*********20140417 ralf check damage pve**************
		if (Json::IsArray(data, "baseop") && Json::IsArray(pointjson, "baseop")) {
			for (unsigned i = 0; i < data["baseop"].size(); ++i)
			{
				unsigned id = 0;
				if (!Json::GetUInt(data["baseop"][i], "id", id))
					continue;

				for (unsigned j = 0; j < pointjson["baseop"].size(); ++j)
				{
					unsigned thisid = 0;
					if (!Json::GetUInt(pointjson["baseop"][j], "id", thisid))
						continue;

					if(thisid == id)
					{
						//Json::FastWriter writer;
						//debug_log("%s->%s",writer.write(pointjson["baseop"][j]).c_str(),writer.write(data["baseop"][i]).c_str());
						pointjson["baseop"][j] = data["baseop"][i];
						break;
					}
				}
			}
		}
		for (unsigned k = 0; k < pointjson["baseop"].size(); ++k)
		{
			unsigned type = 0;
			if (!Json::GetUInt(pointjson["baseop"][k], "t", type))
				continue;
			if(type == 4 || type == 14 ||type == 15 ||type == 16 ||type == 50)
				continue;
			unsigned hp = 0;
			if (!Json::GetUInt(pointjson["baseop"][k], "hp", hp))
				continue;
			if(hp > 10)
			{
				error_log("[alliance battle damage][uid=%u,bid=%u]",userBy.uid,bid);
				LOGIC_ERROR_RETURN_MSG("????");
			}
		}
		**************************************************/

		DataUserBasic userByBasic;
		CLogicUserBasic logicUserBasic;
		logicUserBasic.GetUserBasicLimit(userBy.uid,(PlatformType)0,userByBasic);

		point.aid = cid == CITY_K_ID ? (point.aid == city.aid ? city.challenger : city.aid) : userBy.alliance_id;
		point.uid = userBy.uid;
		strcpy(point.name,userByBasic.name.c_str());
		point.challenger = 0;
		memset(point.challengername, 0, sizeof(point.challengername));
		point.breathTs = 0;
		SetArchive(bid, userBy.uid,point.archive);
	}
	else
	{
		if (Json::IsArray(data, "baseop") && Json::IsArray(pointjson, "baseop")) {
			for (unsigned i = 0; i < data["baseop"].size(); ++i)
			{
				unsigned id = 0;
				if (!Json::GetUInt(data["baseop"][i], "id", id))
					continue;

				for (unsigned j = 0; j < pointjson["baseop"].size(); ++j)
				{
					unsigned thisid = 0;
					if (!Json::GetUInt(pointjson["baseop"][j], "id", thisid))
						continue;

					if(thisid == id)
					{
						//Json::FastWriter writer;
						//debug_log("%s->%s",writer.write(pointjson["baseop"][j]).c_str(),writer.write(data["baseop"][i]).c_str());
						pointjson["baseop"][j] = data["baseop"][i];
						break;
					}
				}
			}
		}
		if (Json::IsArray(data, "hero") && Json::IsArray(pointjson, "hero")) {
			for (unsigned i = 0; i < data["hero"].size(); ++i)
			{
				unsigned id = 0;
				if (!Json::GetUInt(data["hero"][i], "ud", id))
					continue;

				for (unsigned j = 0; j < pointjson["hero"].size(); ++j)
				{
					unsigned thisid = 0;
					if (!Json::GetUInt(pointjson["hero"][j], "ud", thisid))
						continue;

					if(thisid == id)
					{
						//Json::FastWriter writer;
						//debug_log("%s->%s",writer.write(pointjson["hero"][j]).c_str(),writer.write(data["hero"][i]).c_str());
						pointjson["hero"][j] = data["hero"][i];
						break;
					}
				}
			}
		}
		/***************************/
		int attackend = 0;
		if (Json::GetInt(data, "attackend", attackend) && attackend == 1)
		{
			point.challenger = 0;
			memset(point.challengername, 0, sizeof(point.challengername));
			point.breathTs = 0;
		}
		else
			point.breathTs = Time::GetGlobalTime();

		Json::FastWriter writer;
		strcpy(point.archive,writer.write(pointjson).c_str());
	}

	ret = dataAllianceBattle->SetBattlePoint(bid,point);
	if (ret != 0)
	{
		error_log("[Save][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("Save_fail");
	}

	return 0;
}

int CLogicAllianceBattle::StartOccupy()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartOccupy_fail");
	}

	vector<vector<BattlePointLimit> > defencelimit,attacklimit;
	defencelimit.resize(AB_CITY_NUM);
	attacklimit.resize(AB_CITY_NUM);
	for(unsigned k=0;k<AB_CITY_NUM;++k)
	{
		if(k != KINGDOM_K_CITY_NUM)
		{
			defencelimit[k].resize(BATTLE_NUM);
			attacklimit[k].resize(BATTLE_NUM);
		}
		else
		{
			defencelimit[k].resize(BATTLE_NUM_K);
			attacklimit[k].resize(BATTLE_NUM_K);
		}
	}
	ret = dataAllianceBattle->GetAllBattlePointLimit(defencelimit,attacklimit);
	if (ret != 0)
	{
		error_log("[StartAttack][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartAttack_fail");
	}

	unsigned i,j;

	for(i=0;i<AB_CITY_NUM;++i)
	{
		if(data[i].stage != AllianceBattle_Attack)
			continue;

		data[i].stage = AllianceBattle_Occupy;
		int defencewin = 0, attackwin = 0;
		unsigned len;
		if(i != KINGDOM_K_CITY_NUM)
			len = BATTLE_NUM;
		else
			len = BATTLE_NUM_K;
		for(j=1;j<len;++j)
		{
			if(attacklimit[i][j].aid == data[i].aid)
				++defencewin;
			if(defencelimit[i][j].aid == data[i].challenger)
				++attackwin;
		}

		bool win = false;
		if(defencelimit[i][0].aid == data[i].challenger
			&& attacklimit[i][0].aid != data[i].aid)
			win = true;
		else if(defencelimit[i][0].aid != data[i].challenger
			&& attacklimit[i][0].aid != data[i].aid
			&& defencewin < attackwin)
			win = true;
		if(win)
		{
			data[i].aid = data[i].challenger;
			data[i].flag = 0;
			data[i].kingdom = 0;
			strcpy(data[i].name,data[i].challengername);
		}
		data[i].challenger = 0;
		memset(data[i].challengername, 0, sizeof(data[i].challengername));
	}

	ret = dataAllianceBattle->SetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartOccupy_fail");
	}
	ret = dataAllianceBattle->ClearAllBattlePoint();
	if (ret != 0)
	{
		error_log("[StartOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartOccupy_fail");
	}

	return 0;
}

int CLogicAllianceBattle::ChooseOccupy(unsigned cid, unsigned aid, unsigned flag, unsigned kingdom)
{
	if(cid == CITY_K_ID)
		return 0;

	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit city;
	int ret = dataAllianceBattle->GetCityLimit(cid,city);
	if (ret != 0)
	{
		error_log("[ChooseOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("ChooseOccupy_fail");
	}

	if(city.aid != aid)
	{
		error_log("[ChooseOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("ChooseOccupy_fail");
	}

	if(city.stage != AllianceBattle_Occupy && city.stage != AllianceBattle_max)
		return 0;

	city.challenger = Time::GetGlobalTime();
	city.flag = flag;
	city.kingdom = kingdom;
	ret = dataAllianceBattle->SetCityLimit(cid, city);
	if (ret != 0)
	{
		error_log("[ChooseOccupy][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("ChooseOccupy_fail");
	}

	return 0;
}

int CLogicAllianceBattle::RewardAndRestart()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[RewardAndRestart][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("RewardAndRestart_fail");
	}

	int i=0;
	map<unsigned,map<unsigned,unsigned> > occupy;
	map<unsigned,map<unsigned,unsigned> >::iterator it;
	map<unsigned,unsigned>::reverse_iterator rit;
	for(i=0;i<KINGDOM_1_CITY_NUM;++i)
	{
		if(!occupy[data[i].aid].count(data[i].challenger))
			occupy[data[i].aid][data[i].challenger] = i;
		else
		{
			data[i].aid = 0;
			data[i].flag = 0;
			data[i].kingdom = 0;
			memset(data[i].name,0,sizeof(data[i].name));
		}
	}
	for(it=occupy.begin();it!=occupy.end();++it)
	{
		for(rit=it->second.rbegin();rit!=it->second.rend();++rit)
		{
			if(rit != it->second.rbegin())
			{
				data[rit->second].aid = 0;
				data[rit->second].flag = 0;
				data[rit->second].kingdom = 0;
				memset(data[rit->second].name,0,sizeof(data[rit->second].name));
			}
		}
	}

	occupy.clear();
	for(i=KINGDOM_1_CITY_NUM;i<KINGDOM_2_CITY_NUM;++i)
	{
		if(!occupy[data[i].aid].count(data[i].challenger))
			occupy[data[i].aid][data[i].challenger] = i;
		else
		{
			data[i].aid = 0;
			data[i].flag = 0;
			data[i].kingdom = 0;
			memset(data[i].name,0,sizeof(data[i].name));
		}
	}
	for(it=occupy.begin();it!=occupy.end();++it)
	{
		for(rit=it->second.rbegin();rit!=it->second.rend();++rit)
		{
			if(rit != it->second.rbegin())
			{
				data[rit->second].aid = 0;
				data[rit->second].flag = 0;
				data[rit->second].kingdom = 0;
				memset(data[rit->second].name,0,sizeof(data[rit->second].name));
			}
		}
	}

	occupy.clear();
	for(i=KINGDOM_2_CITY_NUM;i<KINGDOM_3_CITY_NUM;++i)
	{
		if(!occupy[data[i].aid].count(data[i].challenger))
			occupy[data[i].aid][data[i].challenger] = i;
		else
		{
			data[i].aid = 0;
			data[i].flag = 0;
			data[i].kingdom = 0;
			memset(data[i].name,0,sizeof(data[i].name));
		}
	}
	for(it=occupy.begin();it!=occupy.end();++it)
	{
		for(rit=it->second.rbegin();rit!=it->second.rend();++rit)
		{
			if(rit != it->second.rbegin())
			{
				data[rit->second].aid = 0;
				data[rit->second].flag = 0;
				data[rit->second].kingdom = 0;
				memset(data[rit->second].name,0,sizeof(data[rit->second].name));
			}
		}
	}

	occupy.clear();
	for(i=KINGDOM_3_CITY_NUM;i<KINGDOM_K_CITY_NUM;++i)
	{
		if(!occupy[data[i].aid].count(data[i].challenger))
			occupy[data[i].aid][data[i].challenger] = i;
		else
		{
			data[i].aid = 0;
			data[i].flag = 0;
			data[i].kingdom = 0;
			memset(data[i].name,0,sizeof(data[i].name));
		}
	}
	for(it=occupy.begin();it!=occupy.end();++it)
	{
		for(rit=it->second.rbegin();rit!=it->second.rend();++rit)
		{
			if(rit != it->second.rbegin())
			{
				data[rit->second].aid = 0;
				data[rit->second].flag = 0;
				data[rit->second].kingdom = 0;
				memset(data[rit->second].name,0,sizeof(data[rit->second].name));
			}
		}
	}

	for(i=0;i<AB_CITY_NUM;++i)
	{
		data[i].stage = AllianceBattle_Price;
		data[i].challenger = 0;
		if(i == KINGDOM_K_CITY_NUM)
		{
			data[i].kingdom = data[i].aid;
		}
		else if(IsAllianceId(data[i].aid))
		{
			CLogicAlliance logicAlliance;
			if(i < KINGDOM_1_CITY_NUM )
				ret = logicAlliance.ChangeResource(data[i].aid, 0, 0, 0, 0, HUFU_M_C, 0, "AllBat");
			else if(i == KINGDOM_1_CITY_NUM || i == KINGDOM_2_CITY_NUM || i == KINGDOM_3_CITY_NUM)
				ret = logicAlliance.ChangeResource(data[i].aid, 0, 0, 0, 0, HUFU_K_C, 0, "AllBat");
			else if(i < KINGDOM_K_CITY_NUM)
				ret = logicAlliance.ChangeResource(data[i].aid, 0, 0, 0, 0, HUFU_NK_C, 0, "AllBat");
			if(ret != 0)
				error_log("[RewardAndRestart][ret=%d]",ret);

			DataAlliance alliance;
			if(logicAlliance.GetAllianceLimit(data[i].aid, alliance) == 0)
				data[i].kingdom = alliance.kingdom;
			else
				data[i].kingdom = 0;
		}
		else
		{
			if(i < KINGDOM_1_CITY_NUM )
				data[i].kingdom = 0;
			else if(i < KINGDOM_2_CITY_NUM)
				data[i].kingdom = 1;
			else if(i < KINGDOM_3_CITY_NUM)
				data[i].kingdom = 2;
			else if(i < KINGDOM_K_CITY_NUM)
				data[i].kingdom = 3;
			else
				data[i].kingdom = 0;
		}
	}

	ret = dataAllianceBattle->SetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[StartDefence][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("StartDefence_fail");
	}
	return 0;
}
int CLogicAllianceBattle::SetNPC(unsigned bid, unsigned npcid, char archiveStr[1048128])
{
	Json::Value archive;
	CLogicNpc::GetNpcArchive(npcid,archive);
	archive["userid"] = bid;
	Json::FastWriter writer;
	strcpy(archiveStr,writer.write(archive).c_str());
	return 0;
}
int CLogicAllianceBattle::SetArchive(unsigned bid, unsigned uid, char archiveStr[1048128])
{
	DataUser userBy;
	CLogicUser logicUser;
	int ret = logicUser.GetUser(uid,userBy);
	DataUserBasic userBasic;
	CLogicUserBasic logicUserBasic;
	ret = logicUserBasic.GetUserBasicLimitSmart(uid, (PlatformType)0, userBasic);
	if (ret != 0)
		return ret;
	Json::Value archive;
	archive["userid"] = bid;
	archive["name"] = userBasic.name;
	archive["pic"] = userBasic.figure_url;
	archive["viptype"] = userBasic.vip_type;
	archive["viplevel"] = userBasic.vip_level;
	archive["pt"] = userBasic.platform;
	archive["invite_count"] = userBy.invite_count;
	archive["today_invite_count"] = userBy.today_invite_count;
	archive["level"] = userBy.level;
	archive["exp"] = Convert::UInt64ToString(userBy.point);
	archive["tutorialstage"] = userBy.tutorial_stage;
	archive["resources"].resize(5);
	archive["resources"][(unsigned)0]["c"] = userBy.r1;
	archive["resources"][(unsigned)0]["m"] = userBy.r1_max;
	archive["resources"][(unsigned)1]["c"] = userBy.r2;
	archive["resources"][(unsigned)1]["m"] = userBy.r2_max;
	archive["resources"][(unsigned)2]["c"] = userBy.r3;
	archive["resources"][(unsigned)2]["m"] = userBy.r3_max;
	archive["resources"][(unsigned)3]["c"] = userBy.r4;
	archive["resources"][(unsigned)3]["m"] = userBy.r4_max;
	archive["resources"][(unsigned)4]["c"] = 0;
	archive["resources"][(unsigned)4]["m"] = 0;
	archive["currencys"][(unsigned)0] = userBy.gcbase;
	archive["currencys"][(unsigned)1] = userBy.gcbuy;
	archive["currencys"][(unsigned)2] = userBy.prosper;
	archive["lasttime"] = userBy.last_save_time;
	archive["newgcbase"] = userBy.newgcbase;
	archive["protected_time"] = userBy.protected_time;
	Json::Reader reader;
	userBy.user_tech.empty() || reader.parse(userBy.user_tech, archive["tech"]);
	userBy.barrackQ.empty() || reader.parse(userBy.barrackQ, archive["barrackQ"]);
	userBy.soldier.empty() || reader.parse(userBy.soldier, archive["soldier"]);
	userBy.soldierlevel.empty() || reader.parse(userBy.soldierlevel, archive["soldierlevel"]);
	userBy.buildQ.empty() || reader.parse(userBy.buildQ, archive["buildQ"]);
	userBy.skillQ.empty() || reader.parse(userBy.skillQ, archive["skillQ"]);
	userBy.trainQ.empty() || reader.parse(userBy.trainQ, archive["trainQ"]);
	CLogicBuilding logicBuiding;
	ret = logicBuiding.GetBuilding(userBy.uid,0, archive["baseop"],true);
	if (ret != 0)
		return ret;
	CLogicHero logicHero;
	ret = logicHero.GetHero(userBy.uid, archive["hero"]);
	if (ret != 0)
		return ret;
	CLogicEquipment logicEquip;
	ret = logicEquip.GetEquipmentUsed(userBy.uid, archive["equipment"]);
	if (ret != 0)
		return ret;

	Json::FastWriter writer;
	strcpy(archiveStr,writer.write(archive).c_str());
	return 0;
}

int CLogicAllianceBattle::BattleNum2Bid(unsigned cnum, unsigned bnum, bool defence)
{
	unsigned len;
	if(cnum != KINGDOM_K_CITY_NUM)
		len = BATTLE_NUM;
	else
		len = BATTLE_NUM_K;
	unsigned cid, bid;
	cnum = cnum % AB_CITY_NUM;
	bnum = bnum % len;

	if(cnum < KINGDOM_1_CITY_NUM)
		cid = cnum;
	else if(cnum >= KINGDOM_1_CITY_NUM && cnum < KINGDOM_2_CITY_NUM)
		cid = cnum - KINGDOM_1_CITY_NUM + CITY_RAG;
	else if(cnum >= KINGDOM_2_CITY_NUM && cnum < KINGDOM_3_CITY_NUM)
		cid = cnum - KINGDOM_2_CITY_NUM + CITY_RAG*2;
	else if(cnum >= KINGDOM_3_CITY_NUM && cnum < KINGDOM_K_CITY_NUM)
		cid = cnum - KINGDOM_3_CITY_NUM + CITY_RAG*3;
	else
		cid = cnum - KINGDOM_K_CITY_NUM + CITY_RAG*4;

	if(defence)
		bid = bnum;
	else
		bid = bnum + len;

	return ALLIANCE_BATTLE_ID_MIN + cid*100 + bid;
}

int CLogicAllianceBattle::SetHufu(unsigned aid, Json::Value &hufu)
{
	int sum = 0;
	map<unsigned, Json::Value> updates;
	CLogicUpdates logicUpdates;
	for(int i=0;i<hufu.size();++i)
	{
		updates[hufu[i]["uid"].asUInt()]["s"] = "setalliancehufu";
		updates[hufu[i]["uid"].asUInt()]["c"] = hufu[i]["c"].asUInt();
		updates[hufu[i]["uid"].asUInt()]["ts"] = Time::GetGlobalTime();
		sum += hufu[i]["c"].asUInt();
	}
	CLogicAlliance logicAlliance;
	CLogicEquipment logicEquipment;
	Json::Value temp;
	int ret = logicAlliance.ChangeResource(aid, 0, 0, 0, 0, -sum, 0, "AllBat");
	if(ret != 0)
		return ret;
	for(map<unsigned, Json::Value>::iterator iter=updates.begin();iter!=updates.end();++iter)
	{
		AUTO_LOCK_USER(iter->first)
		if(logicEquipment.AddOneItem(iter->first, HUFU_ID, (iter->second)["c"].asUInt(),"AllBat",temp) == 0)
			logicUpdates.AddUpdates(iter->first,iter->second);
		else
			error_log("add hufu error uid=%u, count=%u",iter->first,iter->second["c"].asUInt());
	}
	return 0;
}

int CLogicAllianceBattle::GetHufu(unsigned uid, Json::Value &result)
{
	int ret;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	Json::Value stats;
	Json::Reader reader;
	reader.parse(dataUser.user_stat,stats);
	if(stats.isMember("frhf") && stats["frhf"].asInt() == 1)
		return R_ERR_LOGIC;


	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit city;
	ret = dataAllianceBattle->GetCityLimit(CITY_K_ID,city);
	if (ret != 0)
	{
		error_log("[GetCityPrice][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("GetCityPrice_fail");
	}

	unsigned count = HUFU_K;
	if(dataUser.kingdom != city.kingdom)
		count = HUFU_NK;

	/*
	//合区长安活动奖励领取
	if((Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS)))
	{
		int reward_flag =0;

		int kingdom_id = 0;
		if(city.kingdom == 1)
		{
			kingdom_id = KINGDOM_1_ID;
		}
		else if(city.kingdom == 2)
		{
			kingdom_id = KINGDOM_2_ID;
		}
		else if(city.kingdom == 3)
		{
			kingdom_id = KINGDOM_3_ID;
		}

		DataAllianceBattleLimit kingdom_city;
		ret = dataAllianceBattle->GetCityLimit(kingdom_id,kingdom_city);
		if (ret != 0)
		{
			error_log("[GetCityPrice][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("GetCityPrice_fail");
		}

		CLogicPay logicPay;
		CLogicAlliance alliance;
		DataAlliance alliance_leader;
		alliance.GetAllianceLimit(kingdom_city.aid,alliance_leader);
		if(uid == alliance_leader.leader_uid)					//盟主奖励
		{
			reward_flag = 1;
			count += HUFU_A_1;
			logicPay.ChangePay(uid, 0, 300, "activity_hequ_changan_leader");
			result["reward_coins"] = 300;
		}

		if(0 == reward_flag)									//盟成员奖励
		{
			vector<DataAllianceMember> members;
			members.clear();
			alliance.GetMembers(kingdom_city.aid, members);
			for(vector<DataAllianceMember>::iterator itr=members.begin(); itr!=members.end(); itr++)
			{
				if(uid == (*itr).uid)
				{
					reward_flag = 1;
					count += HUFU_A_2;
					logicPay.ChangePay(uid, 0, 150, "activity_hequ_changan");
					result["reward_coins"] = 150;
					break;
				}
			}
		}

		if(0 == reward_flag)									//所属国奖励
		{
			if(dataUser.kingdom == city.kingdom)
			{
				reward_flag = 1;
				count += HUFU_A_3;
				logicPay.ChangePay(uid, 0, 50, "activity_hequ_changan");
				result["reward_coins"] = 50;
			}
		}
	}
	*/

	result["hufu_c"] = count;
	/*
	CLogicEquipment logicEquipment;
	ret = logicEquipment.AddOneItem(uid, HUFU_ID, count,"GetHufu",result["equipment"]);
	if(ret)
	{
		error_log("add hufu error uid=%u, count=%u",uid,count);
		return ret;
	}
	*/
	dataUser.prosper += count;

	stats["frhf"] = 1;
	dataUser.user_stat = Json::ToString(stats);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
	{
		error_log(" set  user info failed,uid = %u",uid);
		return ret;
	}

	return 0;
}

int CLogicAllianceBattle::HequChanganActivity(unsigned uid, Json::Value &result)
{
	//合区长安活动
	if((Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS)))
	{
		int ret;

		CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
		if (!dataAllianceBattle)
		{
			DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
		}

		DataAllianceBattleLimit city;
		ret = dataAllianceBattle->GetCityLimit(CITY_K_ID,city);
		if (ret != 0)
		{
			error_log("[GetCityPrice][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("GetCityPrice_fail");
		}

		int kingdom_id = 0;
		if(city.kingdom == 1)
		{
			kingdom_id = KINGDOM_1_ID;
		}
		else if(city.kingdom == 2)
		{
			kingdom_id = KINGDOM_2_ID;
		}
		else if(city.kingdom == 3)
		{
			kingdom_id = KINGDOM_3_ID;
		}

		DataAllianceBattleLimit kingdom_city;
		ret = dataAllianceBattle->GetCityLimit(kingdom_id,kingdom_city);
		if (ret != 0)
		{
			error_log("[GetCityPrice][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("GetCityPrice_fail");
		}

		CLogicAlliance alliance;
		DataAlliance alliance_data;
		alliance.GetAllianceLimit(kingdom_city.aid,alliance_data);
		if (ret != 0)
		{
			error_log("[GetAllianceLimit Fail][ret=%d]",ret);
			DB_ERROR_RETURN_MSG("GetAllianceLimit_Fail");
		}
		result["a_id"] = kingdom_city.aid;
		result["name"] = alliance_data.name;
		result["kingdom"] = alliance_data.kingdom;
	}
	return 0;

}

int CLogicAllianceBattle::ProcessKingdom()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	DataAllianceBattleLimit data[AB_CITY_NUM];
	int ret = dataAllianceBattle->GetAllCityLimit(data);
	if (ret != 0)
	{
		error_log("[ProcessKingdom][ret=%d]",ret);
		DB_ERROR_RETURN_MSG("ProcessKingdom_fail");
	}

	CLogicAlliance logicAlliance;
	CLogicKingdom logicKingdom;
	CLogicUserBasic logicUserBasic;
	unsigned a[3];
	a[0] = KINGDOM_1_CITY_NUM;
	a[1] = KINGDOM_2_CITY_NUM;
	a[2] = KINGDOM_3_CITY_NUM;
	for(unsigned i=0;i<3;++i)
	{
		unsigned kingdom = data[a[i]].kingdom;
		unsigned aid = 0;
		string aname;
		unsigned kinguid = 0;
		string kingname;

		DataAlliance alliance;
		if(logicAlliance.GetAllianceLimit(data[a[i]].aid, alliance) == 0)
		{
			aid = data[a[i]].aid;
			aname = data[a[i]].name;
			kinguid = alliance.leader_uid;
			kingdom = alliance.kingdom;

			DataUserBasic userBasic;
			if(logicUserBasic.GetUserBasicLimitWithoutPlatform(kinguid,userBasic) == 0)
				kingname = userBasic.name;
		}

		int ret = logicKingdom.CheckJob(kingdom,Job_King,kinguid);
		//debug_log("kingdom=%u,uid=%u,name=%s,aid=%u,aname=%s,ret=%u",kingdom,kinguid,kingname.c_str(),aid,aname.c_str(),ret);
		if(ret == R_ERR_LOGIC)
		{
			logicKingdom.ChangeKing(kingdom,kinguid,kingname,aid,aname);
			info_log("[ProcessKingdom][kingdom=%u,uid=%u]",kingdom,kinguid);
		}
	}
	return 0;
}

int CLogicAllianceBattle::RepairAllianceID()
{
	CDataAllianceBattle* dataAllianceBattle = GetCDataAllianceBattle();
	if (!dataAllianceBattle)
	{
		DB_ERROR_RETURN_MSG("init_allianceBattle_fail");
	}

	return dataAllianceBattle->RepairAllianceID();
}
