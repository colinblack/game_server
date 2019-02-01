#include "LogicHero.h"
#include "LogicCmdUnits.h"

int CLogicHero::InitializeHero(unsigned uid)
{
	const Json::Value *pInitJson = 0;
	int ret = CLogicArchive::GetInitArchive(pInitJson);
	if (ret != 0)
		return ret;
	if (!pInitJson->isMember("hero"))
	{
		return 0;
	}
	const Json::Value &hero = (*pInitJson)["hero"];
	if (!hero.isArray())
	{
		error_log("[init hero error][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("db_init_hero_error");
	}

	Json::FastWriter writer;
	CDataHero heroDB;
	unsigned size = hero.size();
	for (unsigned i = 0; i < size; i++)
	{
		unsigned id = 0;
		if (!Json::GetUInt(hero[i], "ud", id))
		{
			error_log("[init hero error][uid=%u,index=%u]",uid,i);
			DB_ERROR_RETURN_MSG("db_init_hero_error");
		}
		ret = heroDB.AddHero(uid, id, writer.write(hero[i]));
		if (ret != 0)
		{
			error_log("[AddHero fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
			DB_ERROR_RETURN_MSG("db_add_hero_fail");
		}
	}
	return 0;
}

int CLogicHero::GetHero(unsigned uid, Json::Value &data)
{
	CDataHero heroDB;
	vector<DataHero> datas;
	int ret = heroDB.GetHero(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_hero_fail");
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
			error_log("[parse fail][uid=%u,i=%u]",uid,i);
		}
		else if(data[i].isMember("newAdd"))
			data[i].removeMember("newAdd");
	}
	return 0;
}
int CLogicHero::GetHero(unsigned uid, map<unsigned,Json::Value> &data)
{
	CDataHero heroDB;
	map<unsigned, string> datas;
	int ret = heroDB.GetHero(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_hero_fail");
	}
	if (ret == R_ERR_NO_DATA)
	{
		data.clear();
		return 0;
	}

	Json::Reader reader;
	for (map<unsigned, string>::iterator it=datas.begin();it!=datas.end();++it)
	{
		if (!reader.parse(it->second, data[it->first]))
		{
			error_log("[parse fail][uid=%u,ud=%u]",uid,it->first);
		}
		else if(data[it->first].isMember("newAdd"))
			data[it->first].removeMember("newAdd");
	}
	return 0;
}

int CLogicHero::GetHeroUsed(unsigned uid, Json::Value &data)
{
	CDataHero heroDB;
	vector<DataHero> datas;
	int ret = heroDB.GetHero(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_hero_fail");
	}
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	Json::Reader reader;
	//data.resize(datas.size());
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value json;
		if (!reader.parse(datas[i].data, json))
		{
			error_log("[parse fail][uid=%u,i=%u]",uid,i);
			continue;
		}

		if(json.isMember("newAdd"))
			json.removeMember("newAdd");

		int bud = 0;
		int def = 0;
		Json::GetInt(json,"bud",bud);
		Json::GetInt(json,"def",def);

		if(bud != 0 || def != 0 ){
			data.append(json);
		}

	}
	return 0;
}

int CLogicHero::AddHeroExp(unsigned uid, unsigned ud, int exp, int& expnow)
{
	Json::Value hero;
	int ret = Get(uid, ud, hero);
	if(ret)
		return ret;

	int oldexp = 0;
	Json::GetInt(hero, "exp", oldexp);
	oldexp += exp;
	if(oldexp < 0)
		return R_ERR_LOGIC;

	hero["exp"] = oldexp;
	ret = Chg(uid, ud, hero);
	if(ret)
		return ret;

	expnow = oldexp;
	return 0;
}

int CLogicHero::UpdateHero(unsigned uid, Json::Value &data, Json::Value &result, bool other)
{
	//TIME_COUNT_RESTART("[hero start]");

	if (!data.isArray())
	{
		error_log("[hero type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("data_hero_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataHero heroDB;
	map<unsigned, string> oldHeros;
	ret = heroDB.GetHero(uid, oldHeros);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_hero_fail");
	}
	unsigned maxid = 0;
	if(!oldHeros.empty())
		maxid = oldHeros.rbegin()->first;
	unsigned totalnew = 0;

	//TIME_COUNT_LOG("[old=%u,new=%u]",oldHeros.size(),data.size());

	map<unsigned, string>::const_iterator oldItr;
	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		string heroId;
		if (!Json::GetUInt(data[i], "ud", id) || !Json::GetString(data[i], "id", heroId))
		{
			error_log("[hero data error][uid=%u,index=%u,id=%u]",uid,i,id);
			//DATA_ERROR_RETURN_MSG("data_hero_error");
			continue;
		}

		int l = 0, oldl = 0;
		int like = 0, oldLike = 0;
		int hexp = 0, oldhexp = 0;
		int star = 0, oldstar = 0;
		unsigned exs = 0, oldexs = 0;
		unsigned ky = 0, oldky = 0;
		unsigned ch = 0, oldch = 0;
		string code;
		double oldpt = 0.0f, pt = 0.0f;
		Json::GetString(data[i], "code", code);
		Json::GetInt(data[i], "l", l);
		Json::GetInt(data[i], "like", like);
		if(data[i].isMember("pt"))
			pt = data[i]["pt"].asDouble();
		Json::GetInt(data[i], "hexp", hexp);
		Json::GetInt(data[i], "star", star);
		Json::GetUInt(data[i], "exs", exs);
		Json::GetUInt(data[i], "ky", ky);
		Json::GetUInt(data[i], "ch", ch);

		bool needJuexueLog = false;
		string act;

		unsigned newAdd = 0;
#if SERVER_HERO_ADDABLE == 1
		Json::GetUInt(data[i], "newAdd", newAdd);
		if(newAdd && id)
		{
			newAdd = 0;
			data[i].removeMember("newAdd");
		}
#endif
		if(newAdd)
		{
			act = "add";
//			if (l > 2)
//			{
//				error_log("[add hero level error][uid=%u,id=%u,l=%d]",uid,id,l);
//				DATA_ERROR_RETURN_MSG("add_hero_level_error");
//			}

			++maxid;
			data[i]["ud"] = maxid;
			id = maxid;
			++totalnew;
			result.resize(totalnew);
			result[totalnew - 1] = data[i];
			data[i].removeMember("newAdd");
		}
		else
		{
			oldItr = oldHeros.find(id);
			if (oldItr != oldHeros.end())
			{
				Json::Value oldHero;
				string oldHeroId;
				if (reader.parse(oldItr->second, oldHero) && Json::GetString(oldHero, "id", oldHeroId))
				{
					if (heroId != oldHeroId)
					{
						error_log("[hero id error][uid=%u,id=%u,heroid=%s,oldhid=%s]",uid,id,heroId.c_str(),oldHeroId.c_str());
						DATA_ERROR_RETURN_MSG("hero_type_error");
					}

					if (Json::GetInt(oldHero, "l", oldl) && l < oldl)
					{
						error_log("[hero level error][uid=%u,ud=%u,l=%d,oldl=%d]",uid,id,l,oldl);
						DATA_ERROR_RETURN_MSG("hero_level_error");
					}
					if(oldl != l)
						HERO_LEVEL_LOG("uid=%u,l=%u,ud=%u",uid,l,id);

					if (Json::GetInt(oldHero, "like", oldLike) && like != oldLike && like == 0)
					{
						string heroData = writer.write(data[i]);
						act = "like";
					}

					if(oldHero.isMember("pt"))
						oldpt = oldHero["pt"].asDouble();
					double tpt = pt - oldpt;
					if(tpt > 11.0f || tpt < -1.0f)
					{
						error_log("[hero pt error][uid=%u,id=%u,pt=%lf,oldpt=%lf]",uid,id,pt,oldpt);
						DATA_ERROR_RETURN_MSG("hero_pt_error");
					}

					if (Json::GetInt(oldHero, "hexp", oldhexp) && hexp != oldhexp)
					{
						error_log("[hero hexp error][uid=%u,id=%u,hexp=%d,oldhexp=%d]",uid,id,hexp,oldhexp);
						DATA_ERROR_RETURN_MSG("hero_hexp_error");
					}

					if(data[i].isMember("hs") && oldHero.isMember("hs"))
					{
						if(!data[i]["hs"].isArray() || data[i]["hs"].size() != 4
						|| !oldHero["hs"].isArray() || oldHero["hs"].size() != 4)
						{
							error_log("[hero hs error][uid=%u,id=%u]",uid,id);
							DATA_ERROR_RETURN_MSG("hero_hs_error");
						}
						for(unsigned j=0;j<4;++j)
						{
							if(data[i]["hs"][j].asUInt() != oldHero["hs"][j].asUInt())
							{
								error_log("[hero hs error][uid=%u,id=%u]",uid,id);
								DATA_ERROR_RETURN_MSG("hero_hs_error");
							}
						}
					}
					else
						act = "hs";

					if (Json::GetInt(oldHero, "star", oldstar) && star != oldstar)
					{
						error_log("[hero star error][uid=%u,id=%u,star=%d,oldstar=%d]",uid,id,star,oldstar);
						DATA_ERROR_RETURN_MSG("hero_star_error");
					}

					if (Json::GetUInt(oldHero, "exs", oldexs) && exs != oldexs)
					{
						error_log("[hero exs error][uid=%u,id=%u,exs=%d,oldexs=%d]",uid,id,exs,oldexs);
						DATA_ERROR_RETURN_MSG("hero_exs_error");
					}

					if (Json::GetUInt(oldHero, "ky", oldky) && ky != oldky)
					{
						error_log("[hero ky error][uid=%u,id=%u,ky=%d,oldky=%d]",uid,id,ky,oldky);
						DATA_ERROR_RETURN_MSG("hero_ky_error");
					}

					//skillcheck
					if(data[i].isMember("tskill") && oldHero.isMember("tskill")){
						ret = SkillUnit::CheakSkillVer(oldHero);
						if(!ret)
						{
							error_log("[PotianSkillTrain] cheak_skill_error failed. uid=%u", uid);
							DATA_ERROR_RETURN_MSG("cheak_skill_error");
						}
						if(data[i]["tskill"].isArray())
						{
							bool skill_falg = true;

							if(data[i]["tskill"].size() == oldHero["tskill"].size())
							{
								unsigned j = 0;
								for(unsigned j = 0;j<oldHero["tskill"].size();++j)
								{
									if(!(data[i]["tskill"][j][1u].asInt() == oldHero["tskill"][j][1u].asInt() && data[i]["tskill"][j][0u].asInt() == oldHero["tskill"][j][0u].asInt())){
											error_log("skill_check : data[sid]=%d,level=%d,old[sid]=%d,level=%d",
											data[i]["tskill"][j][0u].asInt(),
											data[i]["tskill"][j][1u].asInt(),
											oldHero["tskill"][j][0u].asInt(),
											oldHero["tskill"][j][1u].asInt()
											);
											skill_falg = false;
										}
								}
							}
							else
							{
								Json::FastWriter writer;
								string t1 = writer.write(data[i]["tskill"]);
								string t2 = writer.write(oldHero["tskill"]);
								error_log("data= %s,old= %s", t1.c_str(), t2.c_str());
								skill_falg = false;
							}
							if(!skill_falg)
							{
								error_log("[hero tskill error][uid=%u,id=%u]",uid,id);
								DATA_ERROR_RETURN_MSG(" skillcheck hero_tskill_error");
							}
						}
					}

					if (Json::GetUInt(oldHero, "ch", oldch) && ch != oldch)
					{
						error_log("[hero ch error][uid=%u,id=%u,ch=%d,oldch=%d]",uid,id,ch,oldch);
						DATA_ERROR_RETURN_MSG("hero_ch_error");
					}

					if(data[i].isMember("fm") && oldHero.isMember("fm") && data[i]["fm"].isArray() && oldHero["fm"].isArray())
					{
						if(data[i]["fm"].size() != oldHero["fm"].size())
						{
							error_log("[hero fm error][uid=%u,id=%u]",uid,id);
							DATA_ERROR_RETURN_MSG("hero_fm_error");
						}
						for(unsigned j=0;j<oldHero["fm"].size();++j)
						{
							if(data[i]["fm"][j].asUInt() != oldHero["fm"][j].asUInt())
							{
								error_log("[hero fm error][uid=%u,id=%u]",uid,id);
								DATA_ERROR_RETURN_MSG("hero_fm_error");
							}
						}
					}

					if(data[i].isMember("juexue") && oldHero.isMember("juexue"))
					{
						if(data[i]["juexue"].size() == oldHero["juexue"].size())
						{
							for(unsigned j=0;j<oldHero["juexue"].size();++j)
							{
								if(data[i]["juexue"][j]["id"] != oldHero["juexue"][j]["id"]
								|| data[i]["juexue"][j]["exp"] > oldHero["juexue"][j]["exp"])
								{
									needJuexueLog = true;
									break;
								}
							}
						}
						else
							needJuexueLog = true;
					}
					else
						act = "juexue";
					if(needJuexueLog)
					{
						error_log("[juexue_error][operated=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
				}
			}
			else
			{
#if SERVER_HERO_ADDABLE == 1
				//continue;
				error_log("[no hero id][uid=%u,id=%u,heroid=%s]",uid,id,heroId.c_str());
				DATA_ERROR_RETURN_MSG("no_hero_id");
#else
				act = "add";
//				int l = 0;
//				Json::GetInt(data[i], "l", l);
//				if (l > 2)
//				{
//					error_log("[add hero level error][uid=%u,id=%u,l=%d]",uid,id,l);
//					DATA_ERROR_RETURN_MSG("add_hero_level_error");
//				}
#endif
			}
		}

		string heroData = writer.write(data[i]);
		if (data[i].isMember("status")
				&& data[i]["status"].isIntegral()
				&& data[i]["status"].asInt() == 9)
		{
			act = "del";
			ret = heroDB.RemoveHero(uid, id);
			if (ret != 0)
			{
				error_log("[RemoveHero fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_rm_hero_fail");
			}
		}
		else
		{
			ret = heroDB.ReplaceHero(uid, id, writer.write(data[i]));
			if (ret != 0)
			{
				error_log("[ReplaceHero fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_set_hero_fail");
			}
		}
		if (!act.empty())
		{
			HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,id,heroId.c_str(),
					act.c_str(),code.c_str(),heroData.c_str());
		}

		//TIME_COUNT_LOG("[process %uth hero]", i);
	}
	return 0;
}


int CLogicHero::ImportHero(unsigned uid, const Json::Value &data)
{
	if (!data.isArray())
	{
		error_log("[hero type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("data_hero_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataHero heroDB;
	map<unsigned, string> oldHeros;
	ret = heroDB.GetHero(uid, oldHeros);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_hero_fail");
	}
	map<unsigned, string>::const_iterator oldItr;
	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		string heroId;
		if (!Json::GetUInt(data[i], "ud", id) || !Json::GetString(data[i], "id", heroId))
		{
			error_log("[hero data error][uid=%u,index=%u,id=%u]",uid,i,id);
			DATA_ERROR_RETURN_MSG("data_hero_error");
		}
		bool needLog = false;
		string code;
		if (Json::GetString(data[i], "code", code))
		{
			needLog = true;
		}
		bool bAdd = false;
		oldItr = oldHeros.find(id);
		if (oldItr != oldHeros.end())
		{
			Json::Value oldHero;
			string oldHeroId;
			if (reader.parse(oldItr->second, oldHero) && Json::GetString(oldHero, "id", oldHeroId))
			{
				int l = 0, oldl = 0;
				Json::GetInt(data[i], "l", l);
				Json::GetInt(oldHero, "l", oldl);
//				if (l < oldl)
//				{
//					error_log("[hero level error][uid=%u,id=%u,l=%d,oldl=%d]",uid,id,l,oldl);
//					DATA_ERROR_RETURN_MSG("hero_level_error");
//				}
				if (heroId != oldHeroId)
				{
					error_log("[hero id error][uid=%u,id=%u,heroid=%s,oldhid=%s]",uid,id,heroId.c_str(),oldHeroId.c_str());
					DATA_ERROR_RETURN_MSG("hero_type_error");
				}
			}

		}
		else
		{
			bAdd = true;
			needLog = true;
//			int l = 0;
//			Json::GetInt(data[i], "l", l);
//			if (l != 1)
//			{
//				error_log("[add hero level error][uid=%u,id=%u,l=%d]",uid,id,l);
//				DATA_ERROR_RETURN_MSG("add_hero_level_error");
//			}
		}

		string heroData = writer.write(data[i]);
		if (data[i].isMember("status")
				&& data[i]["status"].isIntegral()
				&& data[i]["status"].asInt() == 9)
		{
			bAdd = false;
			needLog = true;
			ret = heroDB.RemoveHero(uid, id);
			if (ret != 0)
			{
				error_log("[RemoveHero fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_rm_hero_fail");
			}
		}
		else
		{
			ret = heroDB.ReplaceHero(uid, id, writer.write(data[i]));
			if (ret != 0)
			{
				error_log("[ReplaceHero fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_set_hero_fail");
			}
		}/*
		if (needLog)
		{
			HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,code=%s,data=%s",uid,id,heroId.c_str(),
					(bAdd?"add":"del"),code.c_str(),heroData.c_str());
		}*/
	}
	return 0;
}

int CLogicHero::GetHeroAccredited(unsigned uid, unsigned world_pos,Json::Value &data)
{
	CDataHero heroDB;
	vector<DataHero> datas;
	unsigned worldpos = 0;
	CLogicUser logicUser;
	unsigned mainPos;
	int ret = heroDB.GetHero(uid, datas);
	if (!(ret == 0 || ret == R_ERR_NO_DATA))
	{
		error_log("[GetHero fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_hero_fail");
	}
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	Json::Reader reader;
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value json;
		if (!reader.parse(datas[i].data, json))
		{
			error_log("[parse fail][uid=%u,i=%u]",uid,i);
			continue;
		}

		if(json.isMember("newAdd"))
			json.removeMember("newAdd");

		int bud = 0;
		int def = 0;
		Json::GetUInt(json,"world_pos",worldpos);
		if( world_pos == worldpos ){
			data.append(json["id"]);
		}

	}
	return 0;
}

int CLogicHero::Get(unsigned uid, unsigned id, Json::Value &data)
{
	string sdata;
	CDataHero heroDB;
	Json::Reader reader;
	int ret = 0;
	ret = heroDB.GetHero(uid, id,sdata);
	if (ret != 0)
	{
		error_log("[GetHero fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_Hero_fail");
	}

	if (!reader.parse(sdata, data))
	{
		error_log("[Hero error][uid=%u,ud=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_Hero_error");
	}
	else if(data.isMember("newAdd"))
		data.removeMember("newAdd");

	return 0;
}
int CLogicHero::Del(unsigned uid, unsigned id)
{
	CDataHero heroDB;
	int ret = 0;
	ret = heroDB.RemoveHero(uid, id);
	if (ret != 0)
	{
		error_log("[DelHero fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("del_Hero_fail");
	}
	return 0;
}
int CLogicHero::Chg(unsigned uid, unsigned id, Json::Value &data)
{
	int ret = 0;
	CDataHero heroDB;
	Json::FastWriter writer;

	/**********************************
	Json::Reader reader;
	Json::Value old;
	string sdata;

	unsigned  ud = 0;
	string hid;
	if (!Json::GetString(data, "id", hid) || !Json::GetUInt(data, "ud", ud))
	{
		error_log("[Hero data error][uid=%u,ud=%u]",uid,ud);
		DATA_ERROR_RETURN_MSG("Hero_building_error");
	}

	ret = heroDB.GetHero(uid, ud,sdata);
	if (ret != 0)
	{
		error_log("[GetHero fail][uid=%u,ud=%u,ret=%d]",uid,ud,ret);
		DB_ERROR_RETURN_MSG("get_Hero_fail");
	}
	if (!reader.parse(sdata, old))
	{
		error_log("[Hero error][uid=%u,ud=%u]",uid,ud);
		DATA_ERROR_RETURN_MSG("data_Hero_error");
	}

	string oldhid;
	if(!Json::GetString(old, "id", oldhid) || oldhid != hid)
	{
		error_log("[Hero type error][uid=%u,ud=%u,id=%s,oldid=%s]",uid,ud,hid.c_str(),oldhid.c_str());
		DATA_ERROR_RETURN_MSG("Hero_type_error");
	}
	****************************************/

	ret = heroDB.SetHero(uid, id, writer.write(data));
	if (ret != 0)
	{
		error_log("[setHero fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("db_set_Hero_fail");
	}
	return 0;
}

int CLogicHero::AddOneHero(unsigned uid, string id, string code, Json::Value &result, string icon, string name)
{
	Json::Value newHeroDatas = Json::Value(Json::arrayValue);
	newHeroDatas[0u] = genHero(id,code, icon, name);
	return UpdateHero(uid, newHeroDatas, result);
}
int CLogicHero::AddHeros(unsigned uid, vector<string> &id, vector<string> &code, Json::Value &result)
{
	if(id.empty())
		return 0;

	Json::Value newHeroDatas = Json::Value(Json::arrayValue);
	for(unsigned i=0;i<id.size();++i)
		newHeroDatas[i] = genHero(id[i],code[i]);
	return UpdateHero(uid, newHeroDatas, result);
}
int CLogicHero::AddHeros(unsigned uid, vector<HeroAdd> &hero, Json::Value &result)
{
	if(hero.empty())
		return 0;

	Json::Value newHeroDatas = Json::Value(Json::arrayValue);
	for(unsigned i=0;i<hero.size();++i)
		newHeroDatas[i] = genHero(hero[i].id, hero[i].code, "", "", hero[i].star, hero[i].l);
	return UpdateHero(uid, newHeroDatas, result);
}
Json::Value CLogicHero::genHero(string &id,string &code, string icon, string name, unsigned star, unsigned l)
{
	l = min(120u, max(1u, l));
	star = min(10u, max(1u, star));

	Json::Value res;
	res["id"] = id;
	res["newAdd"] = 1;
	res["ud"] = 0;
	res["code"] = code;
	res["upts"] = Time::GetGlobalTime();
	res["l"] = l;
	res["exp"] = hero_lvl_exp[l-1];
	res["star"] = star;
	res["hs"][0u] = 0;
	res["hs"][1u] = 0;
	res["hs"][2u] = 0;
	res["hs"][3u] = 0;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(pDataXML)
	{
		XMLHero hero;
		if(pDataXML->GetHero(CDataXML::Str2Hero(id), hero) == 0)
			res["pt"] = hero.point;
	}

	if(IsGodHero(id))
	{
		if(icon.length() > 32)
			icon = icon.substr(0,32);
		if(name.length() > 32)
			name = name.substr(0,32);
		res["icon"] = icon;
		res["name"] = name;
	}

	return res;
}
bool CLogicHero::IsGodHero(string &id)
{
	if(id == "H34541"
	|| id == "H34542"
	|| id == "H37110"
	|| id == "H37111"
	|| id == "H37112"
	|| id == "H37113"
	|| id == "H35055"
	|| id == "H35056")
		return true;
	return false;
}
