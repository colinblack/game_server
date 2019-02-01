#include "LogicNianShou.h"
#include "LogicCmdBase.h"

struct NianShou_Archive
{
	unsigned updateTime;
	Json::Value data;
};

int CLogicNianShou::GetNianShouArchive(unsigned bossId, Json::Value &data)
{
	ActInfoConfig actconfig(CONFIG_NIANSHOU_BOSS);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	static map<int, map<unsigned, NianShou_Archive> > DomainMap;
	map<unsigned, NianShou_Archive> bossMap;
	int domain = 0;
	bool bIsNew = false;
	Config::GetDomain(domain);
	map<int, map<unsigned, NianShou_Archive> >::iterator DomainMapItr = DomainMap.find(domain);
	if (DomainMapItr != DomainMap.end())
	{
		bossMap = DomainMapItr->second;
	}
	else
	{
		bIsNew = true;
	}

	map<unsigned, NianShou_Archive>::iterator it = bossMap.find(bossId);
	if (it == bossMap.end() || Time::GetGlobalTime() - (it->second).updateTime > 1800)
	{
		string path = MainConfig::GetAllServerPath(CONFIG_NPC_DATA);
		if (path.empty())
		{
			error_log("[config error][bossId=%u]",bossId);
			DB_ERROR_RETURN_MSG("read_nianshou_fail");
		}
		if (path[path.length()-1] == '/')
		{
			path.append(CTrans::UTOS(bossId)).append(".dat");
		}
		else
		{
			path.append("/").append(CTrans::UTOS(bossId)).append(".dat");
		}
		string sdata;
		int result = File::Read(path, sdata);
		if(result != 0)
		{
			error_log("[read boss fail][ret=%d,path=%s]", result, path.c_str());
			DB_ERROR_RETURN_MSG("read_nianshou_fail");
		}
		Json::Reader reader;
		if (it == bossMap.end())
		{
			NianShou_Archive archive;
			if (!reader.parse(sdata, archive.data))
			{
				error_log("[parse json fail][path=%s]", path.c_str());
				DB_ERROR_RETURN_MSG("read_nianshou_fail");
			}
			archive.updateTime = Time::GetGlobalTime();
			bossMap[bossId] = archive;
			if (bIsNew)
			{
				DomainMap[domain] = bossMap;
			}
		}
		else
		{
			if (!reader.parse(sdata, (it->second).data))
			{
				error_log("[parse json fail][path=%s]", path.c_str());
				DB_ERROR_RETURN_MSG("read_nianshou_fail");
			}
			(it->second).updateTime = Time::GetGlobalTime();
		}
	}
	data = bossMap[bossId].data;
	return 0;
}

CDataNianShou* CLogicNianShou::GetCDataNianShou()
{
	static map<int, CDataNianShou*> dataMap;
	int serverId = 0;
	Config::GetDomain(serverId);
	if (0 == serverId)
		return NULL;
	map<int, CDataNianShou*>::iterator itr = dataMap.find(serverId);
	if (itr != dataMap.end() && NULL != itr->second)
		return itr->second;

	CDataNianShou *pdata = new CDataNianShou();
	if (pdata->Init(Config::GetPath(CONFIG_NIANSHOU_DIR)) != 0)
	{
		delete pdata;
		pdata = NULL;
		return NULL;
	}
	dataMap[serverId] = pdata;
	return pdata;
}

int CLogicNianShou::GetNianShouInfo(unsigned uid, Json::Value &data, unsigned bossid, unsigned rewardid)
{
	ActInfoConfig actconfig(CONFIG_NIANSHOU_BOSS);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	CDataNianShou* pBoss = GetCDataNianShou();
	if (!pBoss)
	{
		DB_ERROR_RETURN_MSG("init_nianshou_fail");
	}
	int ret = 0;
	unsigned blood = 0;
	unsigned number = 0;
	int selfRank = 0;
	NianShouChallenger self;
	NianShouChallenger last;
	vector<NianShouChallenger> top;
	unsigned fullBlood = 0;
	data.resize(NIAN_SHOU_ID_MAX - NIAN_SHOU_ID_MIN + 1);
	for (unsigned id = NIAN_SHOU_ID_MIN; id <= NIAN_SHOU_ID_MAX; id++)
	{
		blood = 0;
		number = 0;
		top.clear();
		ret = pBoss->LoadNianShou(uid, id, blood, number, selfRank, self, top, last,fullBlood);
		if (ret != 0)
		{
			DB_ERROR_RETURN_MSG("view_nianshou_fail");
		}
		unsigned temp = id - NIAN_SHOU_ID_MIN;
		data[temp]["uid"] = id;
		data[temp]["blood"] = blood;
		data[temp]["number"] = number;
		data[temp]["top"].resize(top.size());
		data[temp]["fullblood"] = fullBlood;
		data[temp]["last"] = last.name;
		for (unsigned i = 0; i < top.size(); i++)
		{
			data[temp]["top"][i]["uid"] = top[i].uid;
			data[temp]["top"][i]["damage"] = top[i].damage;
			data[temp]["top"][i]["name"] = top[i].name;
			data[temp]["top"][i]["kingdom"] = top[i].kingdom;
			data[temp]["top"][i]["level"] = top[i].level;
		}
		data[temp]["nianshou"]["self"]["damage"] = self.damage;
		data[temp]["nianshou"]["self"]["rank"] = selfRank;
		data[temp]["nianshou"]["last"]["uid"] = last.uid;
		data[temp]["nianshou"]["last"]["damage"] = last.damage;
		data[temp]["nianshou"]["last"]["name"] = last.name;
		data[temp]["nianshou"]["last"]["kingdom"] = last.kingdom;
		data[temp]["nianshou"]["last"]["level"] = last.level;

		data[temp]["hero"][(unsigned)0]["hp"] = blood;
		data[temp]["hero"][(unsigned)0]["fhp"] = fullBlood;

		if (id == bossid)
		{
			CLogicSecinc logicsecinc;
			Json::Value newAct;
			ret = logicsecinc.GetSecinc(uid,NAT_NIANSHOU_BOSS,newAct);
			if (ret == R_ERR_NO_DATA || !Time::IsToday(newAct["ts"].asUInt())) {
				newAct["ts"] = Time::GetGlobalTime();
				newAct["id"] = NAT_NIANSHOU_BOSS;
				newAct["data"].clear();
				for (unsigned j=NIAN_SHOU_ID_MIN;j<=NIAN_SHOU_ID_MAX;j++) {
					Json::Value ndata;
					ndata.clear();
					ndata["id"] = j;
					for (unsigned k=0;k<XML_NIANSHOU_BOSS_ITEM_NUM;k++)
						ndata["a"].append(0);
					newAct["data"].append(ndata);
				}
			}

			CDataXML *dataXML = CDataXML::GetCDataXML();
			if(!dataXML)
			{
				error_log("GetInitXML fail");
				return R_ERR_DB;
			}
			XMLNianShouBossItem item;
			ret = dataXML->GetNianShouBossReward(rewardid, item);
			if(ret){
				error_log("[get item error][ret=%d,index=%u]", ret, rewardid);
				return ret;
			}

			if (newAct["data"][bossid-NIAN_SHOU_ID_MIN]["a"][rewardid-1].asUInt())
			{
				LOGIC_ERROR_RETURN_MSG("reward_has_got");
			}
			if (self.damage < item.require)
			{
				error_log("bossid=%u,rewardid=%u,self.damage=%u,item.require=%i",bossid,rewardid,self.damage,item.require);
				LOGIC_ERROR_RETURN_MSG("damage_not_enough");
			}
			newAct["data"][bossid-NIAN_SHOU_ID_MIN]["a"][rewardid-1] = 1;
			ret = logicsecinc.SetOneSecinc(uid,newAct);
			if(ret){
				error_log("[SetOneSecinc error][ret=%d]", ret);
				return ret;
			}

			vector<GiftEquipItem> reward;
			for (int i=0;i<XML_NIANSHOU_BOSS_REWARD_NUM;i++)
				reward.push_back(item.reward[i]);

			string code = "NianShou_"+CTrans::ITOS(rewardid);
			Json::Value temp_data;
			BaseCmdUnit basecmdUnit(uid);
			basecmdUnit.AddGiftEquips(reward, code, temp_data["equipments"]);

			temp_data["newAct"] = newAct;
			data.append(temp_data);
		}
	}

	unsigned now = Time::GetGlobalTime();
	time_t ttt = time(NULL);
	struct tm* stime=localtime(&ttt);

	if (stime->tm_hour >= 13 && !pBoss->SetRewarded(50011))
		rewardNianShou(0, 50011, 0,top,last);

	if (stime->tm_hour >= 19 && !pBoss->SetRewarded(50012))
		rewardNianShou(0, 50012, 0,top,last);

	return 0;
}

int CLogicNianShou::Load(unsigned bossId, unsigned uidBy, Json::Value &result)
{
	ActInfoConfig actconfig(CONFIG_NIANSHOU_BOSS);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	if (!IsValidNianShouId(bossId))
	{
		PARAM_ERROR_RETURN_MSG("param_error");
	}
	int ret = 0;
	ret = GetNianShouArchive(bossId, result);
	if (ret != 0)
		return ret;
	if (!Json::IsArray(result, "hero") || result["hero"].size() == 0)
	{
		DB_ERROR_RETURN_MSG("nianshou_map_err");
	}
	CDataNianShou* pBoss = GetCDataNianShou();
	if (!pBoss)
	{
		DB_ERROR_RETURN_MSG("init_nianshou_fail");
	}
	unsigned blood = 0;
	unsigned number = 0;
	int selfRank = 0;
	unsigned fullBlood = 0;
	NianShouChallenger self;
	NianShouChallenger last;
	vector<NianShouChallenger> top;
	ret = pBoss->LoadNianShou(uidBy, bossId, blood, number, selfRank, self, top, last,fullBlood);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("load_nianshou_fail");
	}
	result["nianshou"]["blood"] = blood;
	result["nianshou"]["fullblood"] = fullBlood;
	result["nianshou"]["number"] = number;
	result["nianshou"]["top"].resize(top.size());
	Json::Value &topJson = result["nianshou"]["top"];
	for (unsigned i = 0; i < top.size(); i++)
	{
		topJson[i]["uid"] = top[i].uid;
		topJson[i]["damage"] = top[i].damage;
		topJson[i]["name"] = top[i].name;
		topJson[i]["kingdom"] = top[i].kingdom;
		topJson[i]["level"] = top[i].level;
	}
	result["nianshou"]["self"]["damage"] = self.damage;
	result["nianshou"]["self"]["rank"] = selfRank;
	result["nianshou"]["last"]["uid"] = last.uid;
	result["nianshou"]["last"]["damage"] = last.damage;
	result["nianshou"]["last"]["name"] = last.name;
	result["nianshou"]["last"]["kingdom"] = last.kingdom;
	result["nianshou"]["last"]["level"] = last.level;

	result["hero"][(unsigned)0]["hp"] = blood;
	result["hero"][(unsigned)0]["fhp"] = fullBlood;

	result["userid"] = bossId;
	return 0;
}

int CLogicNianShou::Save(unsigned bossId, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype)
{
	ActInfoConfig actconfig(CONFIG_NIANSHOU_BOSS);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	if (!IsValidNianShouId(bossId))
	{
		PARAM_ERROR_RETURN_MSG("param_error");
	}
	CDataNianShou* pBoss = GetCDataNianShou();
	if (!pBoss)
	{
		DB_ERROR_RETURN_MSG("init_nianshou_fail");
	}
	int ret = 0;
	string name;
	CDataUserBasic userBasicDb;
	ret = userBasicDb.GetUserName(userBy.uid, OpenPlatform::GetType(), name);
	if (ret != 0)
		return ret;
	CLogicUser logicUser;
	DataUser dataUser;
	ret = logicUser.GetUserLimit(userBy.uid, dataUser);
	if (ret != 0)
		return ret;

	unsigned damage = 0;
	Json::GetUInt(data, "hurt", damage);
	bool dying = false;
	unsigned blood = 0;
	unsigned number = 0;
	int selfRank = 0;
	NianShouChallenger self;
	NianShouChallenger last;
	vector<NianShouChallenger> top;
	vector<NianShouChallenger> lucks;
	vector<NianShouChallenger> dam;
	bool bAll = false;
	int db = 1;
	vector<NianShouChallenger> all;
	unsigned now = Time::GetGlobalTime();
	/*
	if(now >= Config::GetIntValue(CONFIG_ACTIVITY_TUMO_DOUBLE_B_TS) && now <= Config::GetIntValue(CONFIG_ACTIVITY_TUMO_DOUBLE_E_TS))
	{
		bAll = true;
		db = 2;
	}
	*/
	ret = pBoss->AttackNianShou(userBy.uid, bossId, damage, name,  dataUser.level, dataUser.kingdom, dying, blood, number, selfRank, self, top, last, lucks, dam, bAll, all);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("update_nianshou_fail");
	}
	if (dying)	//boss died,reward
	{
		if (!pBoss->SetRewarded(bossId))
			rewardNianShou(userBy.uid, bossId, damage,top,last);
	}
	result["nianshou"]["blood"] = blood;
	result["nianshou"]["number"] = number;
	result["nianshou"]["top"].resize(top.size());
	Json::Value &topJson = result["nianshou"]["top"];
	for (unsigned i = 0; i < top.size(); i++)
	{
		topJson[i]["uid"] = top[i].uid;
		topJson[i]["damage"] = top[i].damage;
		topJson[i]["name"] = top[i].name;
		topJson[i]["kingdom"] = top[i].kingdom;
		topJson[i]["level"] = top[i].level;
	}
	result["nianshou"]["self"]["damage"] = self.damage;
	result["nianshou"]["self"]["rank"] = selfRank;
	result["nianshou"]["last"]["uid"] = last.uid;
	result["nianshou"]["last"]["damage"] = last.damage;
	result["nianshou"]["last"]["name"] = last.name;
	result["nianshou"]["last"]["kingdom"] = last.kingdom;
	result["nianshou"]["last"]["level"] = last.level;

	if (Json::IsObject(data, "attackinfo"))
	{
		CLogicArchive logicArchive;
		ret = logicArchive.ProcessAttackInfo(userBy.uid, data["attackinfo"], result["attackinfo"], bossId, loadtype);
		if (ret != 0)
			return ret;
	}
	return 0;
}

int CLogicNianShou::ViewNianShou(unsigned uid, unsigned bossId, Json::Value &data)
{
	ActInfoConfig actconfig(CONFIG_NIANSHOU_BOSS);
	if (!actconfig.IsActive())
	{
		LOGIC_ERROR_RETURN_MSG("activity is over");
	}
	if (!IsValidNianShouId(bossId))
	{
		PARAM_ERROR_RETURN_MSG("param_error");
	}
	CDataNianShou* pBoss = GetCDataNianShou();
	if (!pBoss)
	{
		DB_ERROR_RETURN_MSG("init_nianshou_fail");
	}
	int ret = 0;
	unsigned blood = 0;
	unsigned fullBlood = 0;
	unsigned number = 0;
	int selfRank = 0;
	NianShouChallenger self;
	NianShouChallenger last;
	vector<NianShouChallenger> top;
	ret = pBoss->ViewNianShou(uid, bossId, blood,fullBlood, number, selfRank, self, top, last);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("view_nianshou_fail");
	}
	data["uid"] = bossId;
	data["blood"] = blood;
	data["fullblood"] = fullBlood;
	data["number"] = number;
	data["top"].resize(top.size());
	for (unsigned i = 0; i < top.size(); i++)
	{
		data["top"][i]["uid"] = top[i].uid;
		data["top"][i]["damage"] = top[i].damage;
		data["top"][i]["name"] = top[i].name;
		data["top"][i]["kingdom"] = top[i].kingdom;
		data["top"][i]["level"] = top[i].level;
	}
	data["self"]["damage"] = self.damage;
	data["self"]["rank"] = selfRank;
	data["last"]["uid"] = last.uid;
	data["last"]["damage"] = last.damage;
	data["last"]["name"] = last.name;
	data["last"]["kingdom"] = last.kingdom;
	data["last"]["level"] = last.level;

	return 0;
}

int CLogicNianShou::ExportNianShouData(unsigned uid, unsigned bossId, const string &dir)
{
	string file(dir);
	if (file[file.length()-1] != '/')
		file.append("/");
	file.append(CTrans::UTOS(bossId)).append(".dat");

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value result;
	result["userid"] = bossId;

	CLogicUser logicUser;
	DataUser user;
	int ret = logicUser.GetUser(uid, user);
	if (ret != 0)
		return ret;
	result["resources"][(unsigned)0]["c"] = 0;
	result["resources"][(unsigned)0]["m"] = user.r1_max;
	result["resources"][(unsigned)1]["c"] = 0;
	result["resources"][(unsigned)1]["m"] = user.r2_max;
	result["resources"][(unsigned)2]["c"] = 0;
	result["resources"][(unsigned)2]["m"] = user.r3_max;
	result["resources"][(unsigned)3]["c"] = 0;
	result["resources"][(unsigned)3]["m"] = user.r4_max;
	result["resources"][(unsigned)4]["c"] = 0;
	result["resources"][(unsigned)4]["m"] = 0;
	result["lasttime"] = Time::GetGlobalTime();
	if (!user.barrackQ.empty() && !reader.parse(user.barrackQ, result["barrackQ"]))
	{
		DB_ERROR_RETURN_MSG("parse brrackQ fail");
	}
	if (!user.soldier.empty() && !reader.parse(user.soldier, result["soldier"]))
	{
		DB_ERROR_RETURN_MSG("parse soldier fail");
	}
	if (!user.soldierlevel.empty() && !reader.parse(user.soldierlevel, result["soldierlevel"]))
	{
		DB_ERROR_RETURN_MSG("parse soldierlevel fail");
	}
	if (!user.user_tech.empty() && !reader.parse(user.user_tech, result["tech"]))
	{
		DB_ERROR_RETURN_MSG("parse user_tech fail");
	}
	if (!user.buildQ.empty() && !reader.parse(user.buildQ, result["buildQ"]))
	{
		error_log("[buildQ parse error][uid=%u]",uid);
	}
	if (!user.skillQ.empty() && !reader.parse(user.skillQ, result["skillQ"]))
	{
		error_log("[skillQ parse error][uid=%u]",uid);
	}
	if (!user.trainQ.empty() && !reader.parse(user.trainQ, result["trainQ"]))
	{
		error_log("[trainQ parse error][uid=%u]",uid);
	}

	CLogicBuilding logicBuiding;
	ret = logicBuiding.GetBuilding(uid,0, result["baseop"],true);
	if (ret != 0)
		return ret;

	CLogicHero logicHero;
	ret = logicHero.GetHero(uid, result["hero"]);
	if (ret != 0)
		return ret;

	CLogicEquipment logicEquip;
	ret = logicEquip.GetEquipmentUsed(uid, result["equipment"]);
	if (ret != 0)
		return ret;

	string sdata = writer.write(result);
	int fd = open(file.c_str(), O_CREAT | O_WRONLY | O_TRUNC );
	if (write(fd, sdata.data(), sdata.size()) == -1)
	{
		DB_ERROR_RETURN_MSG("write file fail");
	}
	return 0;
}

void CLogicNianShou::rewardNianShou(unsigned uid, int bossId,unsigned damage,const vector<NianShouChallenger>& top,
		const NianShouChallenger &last)
{
	int ret;
	CLogicUpdates logicUpdates;
	CLogicEquipment logicEquipment;
	CLogicPay logicPay;
	unsigned canjuan[10] = {260,220,180,160,140,120,100,80,60,50};
	map<unsigned, Json::Value> updatesmap;
	//1%伤害奖励10金币
	/*
	for (unsigned i = 0; i < dam.size(); i++)
	{
		Json::Value updates;
		updates["s"] = "NIANSHOUTOP";
		updates["bossid"] = bossId;
		updates["damage"] = dam[i].damage;
		updates["r"] = i + 1;
		updates["ts"] = Time::GetGlobalTime();
		updates["coins"] = 10;
		updatesmap[dam[i].uid] = updates;
	}
	*/
	Json::Value equip;
	//前十奖励威望
	for (unsigned i = 0; i < top.size(); i++)
	{
		if (i >= 10) break;
		if(updatesmap.count(top[i].uid))
		{
			updatesmap[top[i].uid]["canjuan"] = canjuan[i];
			ret += logicEquipment.AddOneItem(top[i].uid, 4099, canjuan[i], "nianshou_"+CTrans::ITOS(bossId), equip);
		}
		else
		{
			Json::Value updates;
			updates["s"] = "NIANSHOUTOP";
			updates["bossid"] = bossId;
			updates["damage"] = top[i].damage;
			updates["r"] = i+1;
			updates["ts"] = Time::GetGlobalTime();
			updates["canjuan"] = canjuan[i];
			updatesmap[top[i].uid] = updates;
			ret += logicEquipment.AddOneItem(top[i].uid, 4099, canjuan[i], "nianshou_"+CTrans::ITOS(bossId), equip);
		}
	}
	//整十奖励威望
	/*
	for (unsigned i = 0; i < lucks.size(); i++)
	{
		if(updatesmap.count(lucks[i].uid))
			updatesmap[lucks[i].uid]["prosper3"] = 800 * db;
		else
		{
			Json::Value updates;
			updates["s"] = "NIANSHOUTOP";
			updates["bossid"] = bossId;
			updates["damage"] = lucks[i].damage;
			updates["r"] = 20 + i*10;
			updates["ts"] = Time::GetGlobalTime();
			updates["prosper3"] = 800 * db;
			updatesmap[lucks[i].uid] = updates;
		}
	}
	*/
	//最后一击奖励威望
	if(updatesmap.count(last.uid))
	{
		updatesmap[last.uid]["zhekoujuan"] = 200;
		ret += logicEquipment.AddOneItem(last.uid, 2040, 200, "nianshou_jisha_"+CTrans::ITOS(bossId), equip);
	}
	else
	{
		Json::Value updates;
		updates["s"] = "NIANSHOUTOP";
		updates["bossid"] = bossId;
		updates["damage"] = damage;
		updates["ts"] = Time::GetGlobalTime();
		updates["zhekoujuan"] = 200;
		updatesmap[uid] = updates;
		ret += logicEquipment.AddOneItem(last.uid, 2040, 200, "nianshou_jisha_"+CTrans::ITOS(bossId), equip);
	}

	for(map<unsigned, Json::Value>::iterator it=updatesmap.begin();it!=updatesmap.end();++it)
		logicUpdates.AddUpdates(it->first, it->second);
}
