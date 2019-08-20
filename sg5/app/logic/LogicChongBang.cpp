#include "LogicChongBang.h"
#include "LogicCmdBase.h"

CLogicChongBang::CLogicChongBang(const std::string& path, unsigned version)
	: m_nReset(0),
	  m_nStop(0),
	  m_path(path),
	  m_Version(version)
{
	if (File::IsExist(m_path))
	{
		std::string content;
		int ret = File::Read(m_path, content);
		if (ret < 0)
		{
			throw std::runtime_error("CLogicChongBang_read_file_error");
		}

		Json::Value jsonData;
		if (content.size() > 0)
		{
			if(! Json::FromString(jsonData, content))
			{
				throw std::runtime_error("CLogicChongBang_file_content_error");
			}

			//m_nTime = jsonData["upTime"].asInt();

			unsigned now = Time::GetGlobalTime();
			m_nReset = jsonData["reset"].asInt();
			//隔月，重置文件
			if (m_Version !=  jsonData["version"].asInt())
			{
				//m_nReset = 1;
				m_nStop = 0;
			}
			else
			{
				m_nStop = jsonData["stop"].asInt();

				if (m_nStop == 0 && jsonData.isMember("data") && jsonData["data"].isArray())
				{
					for (size_t i = 0; i < jsonData["data"].size(); i++)
					{
						unsigned uid = jsonData["data"][i]["uid"].asInt();
						if (0 == uid)
						{
							continue;
						}

						//
						m_mapData[uid] = jsonData["data"][i];
					}
				}
			}
		}

		if (m_nStop == 0)
		{
			ret = File::Clear(m_path);
			if (ret != 0)
			{
				throw std::runtime_error("CLogicChongBang_clear_file_error");
			}
		}
	}
	else
	{
		std::cout << "File: " << path << "isn't exist" << std::endl;
	}
}

CDataChongBangWangZhe* CLogicChongBang::GetDataChongBangWangZhe(void)
{
	GET_MEM_DATA_SEM(CDataChongBangWangZhe, CONFIG_CHONGBANG_WANGZHE_DATA, sem_chongbangwangzhe, false)
}


int CLogicChongBang::GetXianShiReward(unsigned uid, string key, unsigned id, Json::Value & result)
{
	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLXianShiMuBiao config;
	int ret = dataXML->GetXianShiMuBiaoReward(config);
	if (ret)
	{
		return ret;
	}
	for (unsigned i=0;i<MAX_XIANSHI_MUBIAO_HUODONG_NUM;i++)
		if (string(config.huodong[i].name) == key)
		{
			ActInfoConfig actconfig(key);
			if (!actconfig.IsActive())
			{
				LOGIC_ERROR_RETURN_MSG("activity_is_over");
			}
			unsigned sid = FindSid(key);
			CLogicSecinc logicSecinc;
			Json::Value newAct;
			ret = logicSecinc.GetSecinc(uid,sid,newAct);
			if (ret)
				return ret;
			for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
				if (config.huodong[i].equip[j].id == id)
				{
					unsigned total_used = newAct["a"][id-1][0u].asUInt();
					unsigned now_reward = newAct["a"][id-1][1u].asUInt();
					unsigned require =  config.huodong[i].equip[j].item[now_reward].require;
					if (!require)
					{
						LOGIC_ERROR_RETURN_MSG("all_have_got");
					}
					if (total_used < require)
					{
						error_log("uid=%u,key=%s,id=%u,total_used=%u,require=%u",uid,key.c_str(),id,total_used,require);
						LOGIC_ERROR_RETURN_MSG("used_not_enough");
					}
					newAct["a"][id-1][1u] = now_reward + 1;
					ret = logicSecinc.SetOneSecinc(uid,newAct);
					if (ret)
						return ret;
					vector<GiftEquipItem> reward;
					string code = string(config.huodong[i].name)+"_xianshi_"+CTrans::ITOS(id);
					for (int k=0;k<XML_XIANSHI_MUBIAO_REWARD_NUM;k++)
						reward.push_back(config.huodong[i].equip[j].item[now_reward].reward[k]);
					BaseCmdUnit basecmdUnit(uid);
					basecmdUnit.AddGiftEquips(reward, code, result["equipments"], actconfig.EndTS() - Time::GetGlobalTime());
				}

		}
	return 0;
}

int CLogicChongBang::AddUseEquipCnt(unsigned uid, unsigned eqid, unsigned count, string code, bool ishuode)
{
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	DataXMLXianShiMuBiao config;
	int ret = dataXML->GetXianShiMuBiaoReward(config);
	if (ret)
	{
		return ret;
	}
	for (unsigned i=0;i<MAX_XIANSHI_MUBIAO_HUODONG_NUM;i++)
		if (strlen(config.huodong[i].name))
		{
			string activity(config.huodong[i].name);
			ActInfoConfig actconfig(activity);
			try
			{
				if (!actconfig.IsActive())
					continue;
			}
			catch(runtime_error & e)
			{
				continue;
			}
			unsigned sid = FindSid(activity);
			CLogicSecinc logicSecinc;
			Json::Value newAct;
			ret = logicSecinc.GetSecinc(uid,sid,newAct);
			if (ret && ret!=R_ERR_NO_DATA)
			{
				LOGIC_ERROR_RETURN_MSG("get_secinc_error");
			}
			if (ret == R_ERR_NO_DATA || newAct["v"].asUInt() != actconfig.Version())
			{
				unsigned max_id = 0;
				for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
					if (max_id < config.huodong[i].equip[j].id)
						max_id = config.huodong[i].equip[j].id;
				ResetNewAct(newAct, sid, actconfig.Version(),max_id);
			}
			for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
				if (config.huodong[i].equip[j].ishuode == ishuode)
				{
					if (strlen(config.huodong[i].equip[j].code) && code != string(config.huodong[i].equip[j].code))
						continue;
					if (eqid == config.huodong[i].equip[j].eqid)
					{
						newAct["a"][j][0u] = newAct["a"][j][0u].asUInt() + count;
						break;
					}
					if (eqid == config.huodong[i].equip[j].eqid2)
					{
						newAct["a"][j][0u] = newAct["a"][j][0u].asUInt() + count * config.huodong[i].equip[j].value2;
						break;
					}
				}
			ret = logicSecinc.SetOneSecinc(uid,newAct);
			if (ret)
			{
				LOGIC_ERROR_RETURN_MSG("set_secinc_error");
			}
		}
	return 0;
}

void CLogicChongBang::ResetNewAct(Json::Value & newAct, unsigned sid, unsigned version, unsigned len)
{
	debug_log("sid=%u,version=%u,len=%u",sid,version,len);
	newAct["id"] = sid;
	newAct["v"] = version;
	newAct["a"] = Json::Value(Json::arrayValue);
	for (unsigned j=0;j<len;j++)
	{
		Json::Value t;
		t[0u] = 0;
		t[1u] = 0;
		newAct["a"].append(t);
	}
}

unsigned CLogicChongBang::FindSid(string key)
{
	if (key == CONFIG_ZHENGBASHADI_CHONGBANG)
		return NAT_xianshi_mubiao_1;
	if (key == CONFIG_LUEDUOTONGQIAN_CHONGBANG)
		return NAT_xianshi_mubiao_2;
	if (key == CONFIG_chongbang_3)
		return NAT_xianshi_mubiao_3;
	return 0;
}

void CLogicChongBang::Save(bool stop)
{
	Json::Value jsonData;
	//jsonData["upTime"] = m_nTime/*Time::GetGlobalTime()*/;
	jsonData["stop"] = m_nStop;
	jsonData["reset"] = m_nReset;
	jsonData["version"] = m_Version;

	multimap<unsigned, unsigned> killhero;
	map<unsigned, string> heroname;
	for(map<unsigned, Json::Value>::iterator it=m_mapData.begin();it!=m_mapData.end();++it)
	{
		killhero.insert(pair<unsigned, unsigned>((it->second)["kill"].asUInt(), (it->second)["uid"].asUInt()));
		heroname[(it->second)["uid"].asUInt()] = (it->second)["name"].asString();
	}

	unsigned i = 0;
	DataUser user;
	CLogicUser logicUser;
	Json::Value rank;

	int ret;

	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLXianShiMuBiao config;
	dataXML->GetXianShiMuBiaoReward(config);

	for(multimap<unsigned, unsigned>::reverse_iterator it=killhero.rbegin();it!=killhero.rend();++it)
	{
		if(it->first == 0)
			break;

		++i;
		//if (i <= 100)
		{
			logicUser.GetUserLimit(it->second, user);
			rank[i-1]["uid"] = it->second;
			rank[i-1]["name"] = heroname[it->second];
			rank[i-1]["kingdom"] = user.kingdom;
			rank[i-1]["kill"] = it->first;
			rank[i-1]["level"] = user.level;
			if (stop)
			{
				if (i == 1)//冲榜王者
					SetUser(1, it->second);

				CLogicUpdates logicUpdates;
				for (unsigned loop = 0;loop < MAX_XIANSHI_MUBIAO_RANK_NUM;loop++)
					if (config.huodong[0].rank[loop].rank1 <= i && i <=config.huodong[0].rank[loop].rank2)
					{
						Json::Value equip;
						vector<GiftEquipItem> reward;
						string code = "zhengbashadi_chongbang_rank_"+CTrans::ITOS(i);
						for (int k=0;k<XML_XIANSHI_MUBIAO_RANK_REWARD_NUM;k++)
							reward.push_back(config.huodong[0].rank[loop].reward[k]);
						BaseCmdUnit basecmdUnit(it->second);
						basecmdUnit.AddGiftEquips(reward, code, equip);

						Json::Value updates;
						updates["s"] = "ZHENGBASHADICHONGBANGRANK";
						updates["uid"] = it->second;
						updates["ts"] = Time::GetGlobalTime();
						updates["rank"] = i;
						logicUpdates.AddUpdate(it->second,updates,true);
					}
			}
		}
		unsigned sid = FindSid(CONFIG_ZHENGBASHADI_CHONGBANG);
		CLogicSecinc logicSecinc;
		Json::Value newAct;
		ret = logicSecinc.GetSecinc(it->second,sid,newAct);
		if (ret == R_ERR_NO_DATA  || newAct["v"].asUInt() != m_Version) {
			unsigned max_id = 0;
			for (unsigned j=0;j<XML_XIANSHI_MUBIAO_PER_EQUIP_NUM;j++)
				if (max_id < config.huodong[0].equip[j].id)
					max_id = config.huodong[0].equip[j].id;
			ResetNewAct(newAct, sid, m_Version, max_id);
		}
		newAct["a"][0u][0u] = it->first;
		ret = logicSecinc.SetOneSecinc(it->second,newAct);
		if (ret)
		{
			error_log("setonesecinc_error. uid=%u", it->second);
		}
	}

	jsonData["data"] = rank;

	//
	ret = File::Write(m_path, Json::ToString(jsonData));
	if(ret)
	{
		error_log("Write_chongbang_data_error. ret=%d", ret);
	}
}

//统计增量
void CLogicChongBang::StatisticsIcrement(
			const std::string& path,
			const std::map<unsigned, unsigned>& mapHerokills,
			const std::map<unsigned, std::string>& mapHeroNames,
			bool check)
{
	//已经停止更新排名列表
	if (m_nStop == 1)
	{
		return ;
	}

	//重置
	if (m_nReset == 1)
	{
		for (std::map<unsigned, unsigned>::const_iterator it = mapHerokills.begin();
							it != mapHerokills.end(); ++it)
		{
			UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
		}

		m_nReset = 0;
	}
	else
	{
		//
		std::string content;
		int ret = File::Read(path, content);
		if (0 != ret)
		{
			std::cerr << "Read data from: " << path << " error. ret: " << ret << std::endl;
			return ;
		}

		Json::Value jsonRankList;
		if (! Json::FromString(jsonRankList, content) || !jsonRankList.isArray())
		{
			std::cerr << "Parae file data error. not json array" << std::endl;
			return ;
		}

		std::map<unsigned, unsigned> mapCopyHeroKills = mapHerokills;

		for (size_t i = 0; i < jsonRankList.size(); ++i)
		{
			Json::Value item;
			unsigned uid =  jsonRankList[i]["uid"].asInt();
			int kills = jsonRankList[i]["kill"].asInt();

			std::map<unsigned, unsigned>::iterator it = mapCopyHeroKills.find(uid);
			if (it != mapCopyHeroKills.end())
			{
				int inc = (int)it->second - kills;
				if (inc < 0)
				{
					error_log("saved kills: %d, cur kills: %d", kills, (int)it->second);
					continue;
				}


				UpdateMapData(it->first, GetName(it->first, mapHeroNames), inc);

				mapCopyHeroKills.erase(it);
			}
			else
			{
				UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
			}
		}

		//没有记录在档的
		for (std::map<unsigned, unsigned>::iterator it = mapCopyHeroKills.begin();
				it != mapCopyHeroKills.end(); ++it)
		{
			UpdateMapData(it->first, GetName(it->first, mapHeroNames), it->second);
		}
	}

	//m_nTime = Time::GetGlobalTime();

	if (check)
		CheckMapData(mapHerokills);
	Save();
}

void CLogicChongBang::Reset()
{
	if (m_nStop)
		return;

	m_nReset = 1;

	//m_nTime = Time::GetGlobalTime();

	Save();
}

void CLogicChongBang::Stop()
{
	if (m_nStop)
		return;

	m_nStop = 1;

	Save(true);
}

void CLogicChongBang::UpdateMapData(unsigned uid, const std::string& name, unsigned incVal)
{
	if (incVal > 0)
	{
		std::map<unsigned, Json::Value>::iterator itData = m_mapData.find(uid);
		if (itData != m_mapData.end())
		{
			itData->second["kill"] = itData->second["kill"].asInt() + incVal;
		}
		else
		{
			Json::Value jsonItem;
			jsonItem["uid"] = uid;
			jsonItem["name"] = name;
			jsonItem["kill"] = incVal;
			//插入新的
			m_mapData[uid] = jsonItem;
		}
	}
}

void CLogicChongBang::CheckMapData(const std::map<unsigned, unsigned>& mapHerokills)
{
	for (map<unsigned, unsigned>::const_iterator it = mapHerokills.begin(); it != mapHerokills.end(); ++it)
	{
		unsigned uid = it->first;
		unsigned kill = it->second;
		std::map<unsigned, Json::Value>::iterator itData = m_mapData.find(uid);
		if (itData != m_mapData.end())
		{
			if (itData->second["kill"].asInt()<kill)
				itData->second["kill"] = kill;
		}
		else
		{
			Json::Value jsonItem;
			jsonItem["uid"] = uid;
			CDataUserBasic userBasicDb;
			string name;
			userBasicDb.GetUserName(uid, OpenPlatform::GetType(), name);
			jsonItem["name"] = name;
			jsonItem["kill"] = kill;
			//插入新的
			m_mapData[uid] = jsonItem;
		}
	}
}

std::string CLogicChongBang::GetName(
		unsigned uid, const std::map<unsigned, string>& mapHeroNames)
{
	std::map<unsigned, std::string>::const_iterator it = mapHeroNames.find(uid);
	if (it != mapHeroNames.end())
	{
		return it->second;
	}

	return "";
}

int CLogicChongBang::Mobai(unsigned uid, unsigned chongbangid, unsigned uid2, Json::Value & result)
{
	if (!chongbangid || chongbangid > MAX_CHONGBANG_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	if (!uid2)
	{
		PARAM_ERROR_RETURN_MSG("uid");
	}
	CLogicSecinc LogicSecinc;
	Json::Value newact;
	int ret = LogicSecinc.GetSecinc(uid,NAT_CONFIG_zhengbashadi_chongbang,newact);
	if (ret && ret!=R_ERR_NO_DATA)
	{
		LOGIC_ERROR_RETURN_MSG("GetSecinc_fail");
	}
	if (ret == R_ERR_NO_DATA)
	{
		newact["id"] = NAT_CONFIG_zhengbashadi_chongbang;
	}
	if (Time::IsToday(newact["m"].asUInt()))
	{
		LOGIC_ERROR_RETURN_MSG("today_has_got");
	}
	newact["m"] = Time::GetGlobalTime();
	result["ts"] = newact["m"].asUInt();
	ret =  LogicSecinc.SetOneSecinc(uid,newact);
	if (ret)
	{
		LOGIC_ERROR_RETURN_MSG("SetOneSecinc_fail");
	}


	CDataXML *dataXML = CDataXML::GetCDataXML();
	DataXMLXianShiMuBiao config;
	dataXML->GetXianShiMuBiaoReward(config);

	vector<GiftEquipItem> reward;
	string code = "MoBaiChongBangWangZhe";
	for (int k=0;k<XML_XIANSHI_MUBIAO_RANK_REWARD_NUM;k++)
		reward.push_back(config.mobai[k]);
	BaseCmdUnit basecmdUnit(uid);
	basecmdUnit.AddGiftEquips(reward, code, result["equipments"]);

	CDataChongBangWangZhe *pData = GetDataChongBangWangZhe();
	if (NULL == pData)
	{
		error_log("Mobai fail");
		return R_ERR_DATA;
	}

	ret = pData->MoBai(chongbangid, uid2);
	if(ret)
		return ret;

	pData->GetInfo(chongbangid, result["info"]);

	return 0;
}

int CLogicChongBang::SetUser(unsigned chongbangid, unsigned uid)
{
	if (!chongbangid || chongbangid > NOW_PERSON_DISPLAY)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	CDataChongBangWangZhe *pData = GetDataChongBangWangZhe();
	if (NULL == pData)
	{
		error_log("SetUser fail");
		return R_ERR_DATA;
	}

	CLogicHero logicHero;
	Json::Value heroData;
	int ret = logicHero.GetHero(uid, heroData);
	unsigned id = 0, level = 0, icon = 0;
	string name;
	if (0 == ret)
	{
		for (int j=0; j<heroData.size(); ++j)
		{
			int def = 0;
			if (Json::GetInt(heroData[j], "def", def) && (1 == def))
			{
				string sid = heroData[j]["id"].asString();
				sid.erase(0,1);
				id = CTrans::STOI(sid);
				level = heroData[j]["l"].asUInt();
				cout << heroData[j]["icon"].asString() << endl;
				icon = CTrans::STOI(heroData[j]["icon"].asString());
				name = heroData[j]["name"].asString();
			}
		}
	}

	Json::Value jsonStats;
	CLogicUser logicUser;
	if ((ret = logicUser.GetUserStat(uid, jsonStats)) != 0)
	{
		DB_ERROR_RETURN_MSG("get_user_stat failed");
	}


	ret = pData->SetUser(chongbangid, uid, id, level, jsonStats["dehp"].asUInt(), icon, name);
	if(ret)
		return ret;

	return 0;
}

int CLogicChongBang::GetInfo(unsigned chongbangid, Json::Value & result)
{
	if (!chongbangid || chongbangid > MAX_CHONGBANG_NUM)
	{
		PARAM_ERROR_RETURN_MSG("id");
	}
	CDataChongBangWangZhe *pData = GetDataChongBangWangZhe();
	if (NULL == pData)
	{
		error_log("GetInfo fail");
		return R_ERR_DATA;
	}

	int ret = pData->GetInfo(chongbangid, result);
	if(ret)
		return ret;

	return 0;
}

void CLogicChongBang::ShowChongBangWangZhe()
{
	CDataChongBangWangZhe *pData = GetDataChongBangWangZhe();
	if (NULL == pData)
	{
		return;
	}

	pData->Show();
}
