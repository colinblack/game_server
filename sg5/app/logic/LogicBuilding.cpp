#include "LogicBuilding.h"

int CLogicBuilding::InitializeBuilding(unsigned uid)
{
	const Json::Value *pInitJson = 0;
	int ret = CLogicArchive::GetInitArchive(pInitJson);
	if (ret != 0)
		return ret;
	if (!pInitJson->isMember("baseop"))
	{
		return 0;
	}
	const Json::Value &baseop = (*pInitJson)["baseop"];
	if (!baseop.isArray())
	{
		error_log("[init building error][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("init_building_error");
	}

	Json::FastWriter writer;
	CDataBuilding bdDB;
	unsigned size = baseop.size();
	for (unsigned i = 0; i < size; i++)
	{
		unsigned id = 0;
		if (!Json::GetUInt(baseop[i], "id", id))
		{
			error_log("[init building error][uid=%u,index=%u]",uid,i);
			DB_ERROR_RETURN_MSG("init_building_error");
		}
		ret = bdDB.AddBuilding(uid, id, writer.write(baseop[i]));
		if (ret != 0)
		{
			error_log("[AddBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
			DB_ERROR_RETURN_MSG("add_building_fail");
		}
	}
	return 0;
}


int CLogicBuilding::InitializeBuilding(unsigned uid,unsigned worldpos)
{
	const Json::Value *pInitJson = 0;
	int ret = CLogicArchive::GetInitArchive(pInitJson);
	if (ret != 0)
		return ret;
	if (!pInitJson->isMember("baseop"))
	{
		return 0;
	}
	const Json::Value &baseop = (*pInitJson)["baseop"];
	if (!baseop.isArray())
	{
		error_log("[init building error][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("init_building_error");
	}

	Json::FastWriter writer;
	CDataBuilding bdDB;
	unsigned size = baseop.size();
	for (unsigned i = 0; i < size; i++)
	{
		unsigned id = 0;
		if (!Json::GetUInt(baseop[i], "id", id))
		{
			error_log("[init building error][uid=%u,index=%u]",uid,i);
			DB_ERROR_RETURN_MSG("init_building_error");
		}
		ret = bdDB.AddBuilding(uid, id, worldpos,writer.write(baseop[i]));
		if (ret != 0)
		{
			error_log("[AddBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
			DB_ERROR_RETURN_MSG("add_building_fail");
		}
	}
	return 0;
}

int CLogicBuilding::GetAllBuilding(unsigned uid, Json::Value &data)
{
	CDataBuilding bdDB;
	vector<DataBuilding> datas;
	int ret = bdDB.GetBuilding(uid, 0, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetBuilding fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	Json::Reader reader;
	data.resize(datas.size());
	for (unsigned i = 0; i < datas.size(); i++)
	{
		if (!reader.parse(datas[i].data, data[i]))
		{
			error_log("[parse fail][uid=%u,id=%d,i=%u]",uid,datas[i].id,i);
		}
		else if(data[i].isMember("newAdd"))
			data[i].removeMember("newAdd");
	}
	return 0;
}


int CLogicBuilding::GetBuilding(unsigned uid, unsigned worldpos,Json::Value &data,bool isMainBase)
{
	CDataBuilding bdDB;
	vector<DataBuilding> olddatas;
	vector<DataBuilding> newdatas;
//	int ret = bdDB.GetBuilding(uid,worldpos, newdatas);
	int ret = 0;
	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid,0, olddatas);

		if (ret != 0 && ret != R_ERR_NO_DATA)
		{
			error_log("[GetBuilding fail][uid=%u,ret=%d]",uid,ret);
			DB_ERROR_RETURN_MSG("get_building_fail");
		}
	}else{
		ret = bdDB.GetBuilding(uid,worldpos, olddatas);

		if (ret != 0 && ret != R_ERR_NO_DATA)
		{
			error_log("[GetBuilding fail][uid=%u,ret=%d]",uid,ret);
			DB_ERROR_RETURN_MSG("get_building_fail");
		}
	}
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	Json::Reader reader;
	int iCount = olddatas.size();
//	int newCount = newdatas.size();
//	int iCount = oldCount + newCount;
//	data.resize(iCount);
//
	for (unsigned i = 0; i < iCount; i++)
	{
//		if(i < newCount)
//		{
			if (!reader.parse(olddatas[i].data, data[i]))
			{
				error_log("[parse fail][uid=%u,id=%d,i=%u]",uid,olddatas[i].id,i);
			}
			else if(data[i].isMember("newAdd"))
				data[i].removeMember("newAdd");
//			continue;
//		}else{
//				if (!reader.parse(olddatas[i - newCount].data, data[i]))
//				{
//					error_log("[parse fail][uid=%u,id=%d,i=%u]",uid,olddatas[i - newCount].id,i);
//				}
//		}
//
	}

	return 0;
}
int CLogicBuilding::UpdateBuilding(unsigned uid, unsigned worldpos,
		Json::Value &data, Json::Value &result, bool isMainBase, bool isAdmin) {
	//TIME_COUNT_RESTART("[building start]");

	if (!data.isArray())
	{
		error_log("[building type error][uid=%u,type=%d]", uid, data.type());
		DATA_ERROR_RETURN_MSG("data_building_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataBuilding bdDB;
	map<unsigned, string> oldBuildings;
	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid, 0,oldBuildings);
	}else
	{
		ret = bdDB.GetBuilding(uid, worldpos,oldBuildings);
	}
	if (!(ret == 0 || ret == R_ERR_NO_DATA))
	{
		error_log("[GetBuilding fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	unsigned maxid = 0;
	if(!oldBuildings.empty())
		maxid = oldBuildings.rbegin()->first;
	unsigned totalnew = 0;

	//TIME_COUNT_LOG("[old=%u,new=%u]",oldBuildings.size(),data.size());

	unsigned now = Time::GetGlobalTime();
	map<unsigned, string>::const_iterator oldItr;
	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		int t = 0;
		if (!Json::GetUInt(data[i], "id", id) || !Json::GetInt(data[i], "t", t))
		{
			error_log("[building data error][uid=%u,index=%u,id=%u]",uid,i,id);
			//DATA_ERROR_RETURN_MSG("data_building_error");
			continue;
		}

		if(isMainBase && !isAdmin)
		{
			unsigned newAdd = 0;
#if SERVER_BUILD_ADDABLE == 1
			Json::GetUInt(data[i], "newAdd", newAdd);
			if(newAdd && id)
			{
				newAdd = 0;
				data[i].removeMember("newAdd");
			}
#endif
			if(newAdd)
			{
				int l = 0;
				Json::GetInt(data[i], "l", l);
				if(l > 2)
				{
					//error_log("[add building level error][uid=%u,id=%u,l=%d]",uid,id,l);
					//DATA_ERROR_RETURN_MSG("add_building_level_error");
					l = 2;
					data[i]["l"] = l;
				}

				++maxid;
				data[i]["id"] = maxid;
				id = maxid;
				++totalnew;
				result.resize(totalnew);
				result[totalnew - 1] = data[i];
				data[i].removeMember("newAdd");
			}
			else
			{
				oldItr = oldBuildings.find(id);
				if (oldItr != oldBuildings.end())
				{
					Json::Value oldBd;
					int oldt = 0;
					if (reader.parse(oldItr->second, oldBd) && Json::GetInt(oldBd, "t", oldt))
					{
						if (t != oldt)
						{
							error_log("[building type error][uid=%u,id=%u,t=%d,oldt=%d]",uid,id,t,oldt);
							DATA_ERROR_RETURN_MSG("building_type_error");
						}
						int l = 1, oldl = 1, cU = 0, oldcU = 0;
						unsigned upts = 0, oldupts = 0;
						Json::GetInt(data[i], "l", l);
						Json::GetInt(oldBd, "l", oldl);
						Json::GetInt(data[i], "cU", cU);
						Json::GetInt(oldBd, "cU", oldcU);
						Json::GetUInt(data[i], "upts", upts);
						Json::GetUInt(oldBd, "upts", oldupts);

						if(l < oldl)
						{
							//error_log("[building level small][uid=%u,id=%u,l=%u,oldl=%u]",uid,id,l,oldl);
							//DATA_ERROR_RETURN_MSG("building_level_small");
							l = oldl;
							data[i]["l"] = l;
						}

						if(upts > now + 60)
						{
							//error_log("[building upts large][uid=%u,id=%u,upts=%u,now=%u]",uid,id,upts,now);
							//DATA_ERROR_RETURN_MSG("building_upts_error");
							upts = now;
							data[i]["upts"] = upts;
						}

						if(upts < oldupts && oldupts < now + 60)
						{
							//error_log("[building upts small][uid=%u,id=%u,upts=%u,oldupts=%u,now=%u]",uid,id,upts,oldupts,now);
							//DATA_ERROR_RETURN_MSG("building_upts_small");
							upts = oldupts;
							data[i]["upts"] = upts;
						}

						if (oldBd.isMember("bkts"))
						{
							data[i]["bkts"] = oldBd["bkts"];
						}
						else
						{
							data[i]["bkts"] = 0;
						}

						if(oldcU)
						{
							if(cU > oldcU)
							{
								//error_log("[building cU large][uid=%u,id=%u,cU=%u,oldcU=%u,upts=%u,oldupts=%u]",uid,id,cU,oldcU,upts,oldupts);
								//DATA_ERROR_RETURN_MSG("building_cU_large");
								cU = oldcU;
								data[i]["cU"] = cU;
							}
							if(oldcU - cU > upts - oldupts + 60)
							{
								//error_log("[building cU small][uid=%u,id=%u,cU=%u,oldcU=%u,upts=%u,oldupts=%u]",uid,id,cU,oldcU,upts,oldupts);
								//DATA_ERROR_RETURN_MSG("building_cU_small");
								cU = max(0, int(oldcU) - int(upts - oldupts));
								if(cU)
								{
									data[i]["cU"] = cU;
									l = oldl;
									data[i]["l"] = l;

								}
								else
								{
									data[i].removeMember("cU");
									l = oldl + 1;
									data[i]["l"] = l;
								}
							}
							unsigned hl = data[i].isMember("hl") ? data[i]["hl"].size() : 0;
							unsigned ohl = oldBd.isMember("hl") ? oldBd["hl"].size() : 0;
							if(cU && hl != ohl)
							{
								//error_log("[building hl error][uid=%u,id=%u,hl=%u,olh=%u]",uid,id,hl,ohl);
								//DATA_ERROR_RETURN_MSG("building_hl_error");
								data[i]["hl"] = oldBd["hl"];
							}
							if((l != oldl && cU) || l - oldl > 1)
							{
								error_log("[building level large][uid=%u,id=%u,l=%u,oldl=%u,cU=%u,oldcU=%u]",uid,id,l,oldl,cU,oldcU);
								DATA_ERROR_RETURN_MSG("building_level_large");
							}
						}
						else if(t != 4)
						{
							if(oldl != l)
							{
								error_log("[building level error][uid=%u,id=%u,l=%u,oldl=%u]",uid,id,l,oldl);
								DATA_ERROR_RETURN_MSG("building_level_error");
							}
							if(cU)
							{
								error_log("[building cU error][uid=%u,id=%u,cU=%u,oldcU=%u]",uid,id,cU,oldcU);
								DATA_ERROR_RETURN_MSG("building_cU_error");
							}
						}
						/***add by ralf 20140411 for check level***/
						if(oldl != l)
							BUILDING_LEVEL_LOG("uid=%u,l=%u,id=%u",uid,l,t);
						/*****************************************/

						if(t == WATER_BUILDING_T)
							check_water(uid, oldBd, data[i]);

						if(t == 1 && oldl != l && l >= ALL_SERVER_MAP_MIN_LEVEL && OpenPlatform::IsLY_ALL_Platform())
						{
							CLogicAllServerMap logicAllServerMap;
							logicAllServerMap.Set(uid, l);
						}
					}
				}
				else
				{
#if SERVER_BUILD_ADDABLE == 1
					//continue;
					error_log("[no building id][uid=%u,id=%u,t=%d]",uid,id,t);
					DATA_ERROR_RETURN_MSG("no_building_id");
#else
					int l = 0;
					Json::GetInt(data[i], "l", l);
					if(l > 2)
					{
						//error_log("[add building level error][uid=%u,id=%u,l=%d]",uid,id,l);
						//DATA_ERROR_RETURN_MSG("add_building_level_error");
						l = 2;
						data[i]["l"] = l;
					}
#endif
				}
			}
		}

		if (data[i].isMember("status")
				&& data[i]["status"].isIntegral()
				&& data[i]["status"].asInt() == 9)
		{
			if(isMainBase)
			{
				ret = bdDB.RemoveBuilding(uid, id,0);
				if (ret != 0)
				{
					error_log("[RemoveBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
					DB_ERROR_RETURN_MSG("rm_building_fail");
				}
			}
			ret = bdDB.RemoveBuilding(uid, id,worldpos);
			if (ret != 0)
			{
				error_log("[RemoveBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("rm_building_fail");
			}
			//info_log("[RemoveBuilding] [uid=%u,id=%u worldpos=%u]",uid,id,worldpos);
		}
		else
		{
			if(isMainBase)
			{
				ret = bdDB.ReplaceBuilding(uid, id, 0, writer.write(data[i]));
			}else
			{
				ret = bdDB.ReplaceBuilding(uid, id, worldpos, writer.write(data[i]));
			}
			if (ret != 0)
			{
				error_log("[ReplaceBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("set_building_fail");
			}
			//info_log("[ReplaceBuilding] [uid=%u,id=%u worldpos=%u]",uid,id,worldpos);

		}

		//TIME_COUNT_LOG("[process %uth building]", i);
	}
	return 0;
}

int CLogicBuilding::ImportBuilding(unsigned uid, unsigned worldpos,
		const Json::Value &data, bool isMainBase) {
	if (!data.isArray())
	{
		error_log("[building type error][uid=%u,type=%d]", uid, data.type());
		DATA_ERROR_RETURN_MSG("data_building_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataBuilding bdDB;
	map<unsigned, string> oldBuildings;
	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid, 0,oldBuildings);
	}else
	{
		ret = bdDB.GetBuilding(uid, worldpos,oldBuildings);
	}
	if (!(ret == 0 || ret == R_ERR_NO_DATA))
	{
		error_log("[GetBuilding fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	map<unsigned, string>::const_iterator oldItr;
	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		int t = 0;
		if (!Json::GetUInt(data[i], "id", id) || !Json::GetInt(data[i], "t", t))
		{
			error_log("[building data error][uid=%u,index=%u,id=%u]",uid,i,id);
			DATA_ERROR_RETURN_MSG("data_building_error");
		}

		if (data[i].isMember("status")
				&& data[i]["status"].isIntegral()
				&& data[i]["status"].asInt() == 9)
		{
			if(isMainBase)
			{
				ret = bdDB.RemoveBuilding(uid, id,0);
				if (ret != 0)
				{
					error_log("[RemoveBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
					DB_ERROR_RETURN_MSG("rm_building_fail");
				}
			}
			ret = bdDB.RemoveBuilding(uid, id,worldpos);
			if (ret != 0)
			{
				error_log("[RemoveBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("rm_building_fail");
			}
			//info_log("[RemoveBuilding] [uid=%u,id=%u worldpos=%u]",uid,id,worldpos);
		}
		else
		{
			if(isMainBase)
			{
				ret = bdDB.ReplaceBuilding(uid, id, 0, writer.write(data[i]));
			}else
			{
				ret = bdDB.ReplaceBuilding(uid, id, worldpos, writer.write(data[i]));
			}
			if (ret != 0)
			{
				error_log("[ReplaceBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("set_building_fail");
			}
			//info_log("[ReplaceBuilding] [uid=%u,id=%u worldpos=%u]",uid,id,worldpos);

		}
	}
	return 0;
}
/*************************
int CLogicBuilding::GetBuilding(unsigned uid, unsigned id, Json::Value &data)
{
	string sdata;
	CDataBuilding bdDB;
	int ret = bdDB.GetBuilding(uid, id, sdata);
	if (ret != 0)
	{
		error_log("[GetBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	Json::Reader reader;
	if (!reader.parse(sdata, data))
	{
		error_log("[building error][uid=%u,id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_building_error");
	}
	return 0;
}
int CLogicBuilding::GetBuilding(unsigned uid, unsigned id, unsigned worldpos,Json::Value &data,bool isMainBase)
{
	string sdata;
	CDataBuilding bdDB;
	int ret = 0;
	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid, id, 0,sdata);
	}else
	{
		ret = bdDB.GetBuilding(uid, id, worldpos,sdata);
	}
	if (ret != 0)
	{
		error_log("[GetBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	Json::Reader reader;
	if (!reader.parse(sdata, data))
	{
		error_log("[building error][uid=%u,id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_building_error");
	}
	return 0;
}
*******************************/
int CLogicBuilding::RemoveBuilding(unsigned uid, unsigned worldpos)
{

	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataBuilding bdDB;
	ret = bdDB.RemoveBuildingOnWordPos(uid,worldpos);
	if (!(ret == 0 || ret == R_ERR_NO_DATA))
	{
		error_log("[RemoveBuilding fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	//info_log("[RemoveBuilding] [uid=%u,id=%u]");

	return 0;
}

int CLogicBuilding::Get(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase, Json::Value &data)
{
	string sdata;
	CDataBuilding bdDB;
	int ret = 0;
	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid, id, 0,sdata);
	}else
	{
		ret = bdDB.GetBuilding(uid, id, worldpos,sdata);
	}
	if (ret != 0)
	{
		error_log("[GetBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	Json::Reader reader;
	if (!reader.parse(sdata, data))
	{
		error_log("[building error][uid=%u,id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_building_error");
	}
	else if(data.isMember("newAdd"))
		data.removeMember("newAdd");

	return 0;
}
int CLogicBuilding::Del(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase)
{
	CDataBuilding bdDB;
	int ret = 0;
	if(isMainBase)
	{
		ret = bdDB.RemoveBuilding(uid, id, 0);
	}else
	{
		ret = bdDB.RemoveBuilding(uid, id, worldpos);
	}
	if (ret != 0)
	{
		error_log("[DelBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	return 0;
}
int CLogicBuilding::Chg(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase, Json::Value &data)
{
	CDataBuilding bdDB;
	Json::FastWriter writer;
	int ret = 0;

	/*****************************
	Json::Value old;
	string sdata;
	Json::Reader reader;
	unsigned id = 0, t = 0;
	if (!Json::GetUInt(data, "id", id) || !Json::GetUInt(data, "t", t))
	{
		error_log("[building data error][uid=%u,id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_building_error");
	}

	if(isMainBase)
	{
		ret = bdDB.GetBuilding(uid, id, 0,sdata);
	}else
	{
		ret = bdDB.GetBuilding(uid, id, worldpos,sdata);
	}
	if (ret != 0)
	{
		error_log("[GetBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_building_fail");
	}
	if (!reader.parse(sdata, old))
	{
		error_log("[building error][uid=%u,id=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_building_error");
	}

	unsigned oldt = 0;
	if(!Json::GetUInt(old, "t", oldt) || oldt != t)
	{
		error_log("[building type error][uid=%u,id=%u,t=%d,oldt=%d]",uid,id,t,oldt);
		DATA_ERROR_RETURN_MSG("building_type_error");
	}
	**********************************/

	if(isMainBase)
	{
		ret = bdDB.SetBuilding(uid, id, 0, writer.write(data));
	}else
	{
		ret = bdDB.SetBuilding(uid, id, worldpos, writer.write(data));
	}
	if (ret != 0)
	{
		error_log("[setBuilding fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("chg_building_fail");
	}

	return 0;
}

int CLogicBuilding::Water(unsigned uid, unsigned uidBy)
{
	Json::Reader reader;
	CDataBuilding bdDB;
	map<unsigned, string> oldBuildings;
	int ret = 0;
	ret = bdDB.GetBuilding(uid, 0,oldBuildings);
	if(ret)
		return ret;

	for(map<unsigned, string>::iterator it=oldBuildings.begin();it!=oldBuildings.end();++it)
	{
		Json::Value oldBd;
		int oldt = 0;
		unsigned id = 0;
		if (reader.parse(it->second, oldBd) && Json::GetUInt(oldBd, "id", id)
		&& Json::GetInt(oldBd, "t", oldt) && oldt == WATER_BUILDING_T
		&& oldBd.isMember("watern") && oldBd["watern"].isArray())
		{
			int l = 0;
			Json::GetInt(oldBd, "l", l);
			if(l < 5)
				l = 5;
			if(oldBd["watern"].size() >= l)
				return R_ERR_LOGIC;
			for(unsigned i=0;i<oldBd["watern"].size();++i)
			{
				if(oldBd["watern"][i].asUInt() == uidBy)
					return R_ERR_LOGIC;
			}
			oldBd["watern"].append(uidBy);
			return Chg(uid,id,0,true,oldBd);
		}
	}

	return R_ERR_DATA;
}
void CLogicBuilding::check_water(unsigned uid, Json::Value &old, Json::Value &data)
{
	if(old.isMember("watern") && old["watern"].isArray()
	&& data.isMember("watern") && data["watern"].isArray())
	{
		unsigned lharvestOld = 0;
		unsigned lharvestNew = 0;
		unsigned lowatertsOld = 0;
		unsigned lowatertsNew = 0;
		Json::GetUInt(old, "lharvest", lharvestOld);
		Json::GetUInt(old, "lowaterts", lowatertsOld);
		Json::GetUInt(data, "lharvest", lharvestNew);
		Json::GetUInt(data, "lowaterts", lowatertsNew);
		if(lharvestOld != lharvestNew)
		{
			if(!(data["watern"].size() == 1
			&& lowatertsOld != lowatertsNew
			&& data["watern"][0u].asUInt() == uid))
				data["watern"].resize(0);
		}
		else if(lowatertsOld != lowatertsNew)
		{
			old["watern"].append(uid);
			data["watern"] = old["watern"];
		}
		else
			data["watern"] = old["watern"];
	}
}
