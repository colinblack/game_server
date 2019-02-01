#include "LogicEquipment.h"
#include "LogicCmdUnits.h"

int CLogicEquipment::InitializeEquipment(unsigned uid)
{
	const Json::Value *pInitJson = 0;
	int ret = CLogicArchive::GetInitArchive(pInitJson);
	if (ret != 0)
		return ret;
	if (!pInitJson->isMember("equipment"))
	{
		return 0;
	}
	const Json::Value &equipment = (*pInitJson)["equipment"];
	if (!equipment.isArray())
	{
		error_log("[init equipment error][uid=%u]",uid);
		DB_ERROR_RETURN_MSG("db_init_equipment_error");
	}

	Json::FastWriter writer;
	CDataEquipment equipmentDB;
	unsigned size = equipment.size();
	for (unsigned i = 0; i < size; i++)
	{
		unsigned id = 0;
		if (!Json::GetUInt(equipment[i], "ud", id))
		{
			error_log("[init equipment error][uid=%u,index=%u]",uid,i);
			DB_ERROR_RETURN_MSG("db_init_equipment_error");
		}
		ret = equipmentDB.AddEquipment(uid, id, writer.write(equipment[i]));
		if (ret != 0)
		{
			error_log("[AddEquipment fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
			DB_ERROR_RETURN_MSG("db_add_equipment_fail");
		}
	}
	return 0;
}

int CLogicEquipment::GetEquipment(unsigned uid, unsigned uidBy, Json::Value &data)
{
	CDataEquipment equipDB;
	vector<DataEquipment> datas;
	int ret = equipDB.GetEquipment(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[db_get_equipment_fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_equipment_fail");
	}
	unsigned maxid = 0;
	Json::Reader reader;
	data.resize(datas.size());
	for (unsigned i = 0; i < datas.size(); i++)
	{
		if (datas[i].id > maxid)
			maxid = datas[i].id;
		if (!reader.parse(datas[i].data, data[i]))
		{
			error_log("[parse fail][uid=%u,id=%u,i=%u]",uid,datas[i].id,i);
		}
		else
		{
			/******20140417 ralf 干掉负数道具*********/
			if(data[i].isMember("count") && data[i]["count"].asInt()<0)
			{
				if(uid == uidBy)
				{
					error_log("[neg count][uid=%u,id=%u]",uid,datas[i].id);
					LOGIC_ERROR_RETURN_MSG("????");
				}
				else
					continue;
			}
			/************************************/
			if(data[i].isMember("newAdd"))
				data[i].removeMember("newAdd");
		}
	}
	maxid++;
	if (uid != uidBy)
		return 0;
	CLogicInventory logicInventory;
	if (datas.size() >= 2000)
	{
		logicInventory.RemoveAllItem(uid);
		return 0;
	}
	Json::FastWriter writer;
	map<string, unsigned> items;
	ret = logicInventory.GetItems(uid, items);
	if (ret == 0 && items.size() > 0)
	{
		logicInventory.RemoveAllItem(uid);
		map<string, unsigned>::const_iterator it = items.begin();
		for (; it != items.end(); it++)
		{
			int eqid = CTrans::STOI(it->first);
			if (eqid <= 0)
			{
				error_log("[equipment id error][uid=%u,seqid=%s]",uid,(it->first).c_str());
				continue;
			}
			for (unsigned count = 0; count < it->second; count++)
			{
				Json::Value json;
				json["ud"] = maxid;
				json["id"] = eqid;
				ret = equipDB.AddEquipment(uid, maxid, writer.write(json));
				if (ret != 0)
				{
					error_log("[AddEquipment fail][uid=%u,ud=%u,id=%d,ret=%d]",uid,maxid,eqid,ret);
					continue;
				}
				maxid++;
				data.append(json);
			}
		}
	}

	return 0;
}

int CLogicEquipment::UpdateEquipment(unsigned uid, unsigned uidBy, Json::Value &data, Json::Value &result, bool merge)
{
	if (!data.isArray())
	{
		error_log("[equipment type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("data_equipment_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataEquipment equipDB;
	map<unsigned, string> oldeq;
	ret = equipDB.GetEquipment(uid, oldeq);
	if (!(ret == 0 || ret == R_ERR_NO_DATA))
	{
		error_log("[GetEquipment fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("get_equpment_fail");
	}
	unsigned maxid = 0;
	if(!oldeq.empty())
		maxid = oldeq.rbegin()->first;
	unsigned totalnew = 0;

	map<int, Json::Value> oldeqbyid;
#if SERVER_EQUIP_ADDABLE == 1
	if(merge)
	{
		Json::Value overlay, unoverlay;
		unsigned overlayindex = 0;
		overlay.resize(0);
		unoverlay.resize(0);
		map<int, unsigned> overlaymap;
		for (unsigned i = 0; i < data.size(); i++)
		{
			int eqid = 0;
			if (!Json::GetInt(data[i], "id", eqid))
			{
				string seqid;
				if (Json::GetString(data[i], "id", seqid))
				{
					eqid = CTrans::STOI(seqid);
				}
			}
			unsigned newAdd = 0;
			Json::GetUInt(data[i], "newAdd", newAdd);
			if(newAdd && !IS_UN_OVERLAY_ID(eqid))
			{
				if(overlaymap.count(eqid))
					overlay[overlaymap[eqid]]["count"] = overlay[overlaymap[eqid]]["count"].asInt() + data[i]["count"].asInt();
				else
				{
					overlay.append(data[i]);
					overlaymap[eqid] = overlayindex;
					++overlayindex;
				}
			}
			else
				unoverlay.append(data[i]);
		}

		if(overlay.size())
		{
			for (unsigned i = 0; i < overlay.size(); i++)
				unoverlay.append(overlay[i]);

			for(map<unsigned, string>::iterator it=oldeq.begin();it!=oldeq.end();++it)
			{
				Json::Value old;
				int oldeqid = 0;
				if(reader.parse(it->second,old)
				&& Json::GetInt(old,"id",oldeqid)
				&& !IS_UN_OVERLAY_ID(oldeqid))
				{
					if(oldeqbyid.count(oldeqid))
						continue;
					else
						oldeqbyid[oldeqid] = old;
				}
			}
		}

		data.clear();
		data = unoverlay;
	}
#endif

	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		int eqid = 0;
		if (!Json::GetInt(data[i], "id", eqid))
		{
			string seqid;
			if (Json::GetString(data[i], "id", seqid))
			{
				eqid = CTrans::STOI(seqid);
			}
		}
		if (!Json::GetUInt(data[i], "ud", id) || eqid <= 0)
		{
			error_log("[equipment data error][uid=%u,index=%u,id=%u]",uid,i,id);
			//DATA_ERROR_RETURN_MSG("data_equipment_error");
			continue;
		}

		bool needLog = false;
		int oldcount = 0, newcount = 0;
		int oldq = 0, newq = 0;
		int oldast = 0, newast = 0;
		int oldhexp = 0, newhexp = 0;
		int oldsexp = 0, newsexp = 0;
		int oldlexp = 0, newlexp = 0;
		int oldstar = 0, newstar = 0;
		int oldyexp = 0, newyexp = 0;
		int oldtts = 0, newtts = 0;
		string logtype;

		Json::GetInt(data[i], "count", newcount);
		Json::GetInt(data[i], "q", newq);
		Json::GetInt(data[i], "ast", newast);
		Json::GetInt(data[i], "hexp", newhexp);
		Json::GetInt(data[i], "sexp", newsexp);
		Json::GetInt(data[i], "lexp", newlexp);
		Json::GetInt(data[i], "star", newstar);
		Json::GetInt(data[i], "yexp", newyexp);
		Json::GetInt(data[i], "tts", newtts);
		string code;
		if (Json::GetString(data[i], "code", code))
		{
			needLog = true;
			logtype = "oth";
		}

		/******20140417 ralf 干掉负数道具*********/
		if(newcount < 0)
		{
			error_log("[neg count][uid=%u,id=%u]",uid,eqid);
			LOGIC_ERROR_RETURN_MSG("????");
		}
		/************************************/

		unsigned newAdd = 0;
#if SERVER_EQUIP_ADDABLE == 1
		Json::GetUInt(data[i], "newAdd", newAdd);
		if(newAdd && id)
		{
			newAdd = 0;
			data[i].removeMember("newAdd");
		}
#endif
		if(newAdd)
		{
			if(IS_UN_OVERLAY_ID(eqid) || !oldeqbyid.count(eqid))
			{
				needLog = true;
				logtype = "new";

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
				needLog = true;
				logtype = "add";

				oldcount = oldeqbyid[eqid]["count"].asInt();
				newcount += oldcount;
				data[i] = oldeqbyid[eqid];
				data[i]["count"] = newcount;
				data[i]["code"] = code;
				++totalnew;
				result.resize(totalnew);
				result[totalnew - 1] = data[i];
				result[totalnew - 1]["merge"] = newcount-oldcount;
				Json::GetUInt(data[i], "ud", id);
			}
		}
		else
		{
			map<unsigned, string>::iterator it = oldeq.find(id);
			if(it != oldeq.end())
			{
				Json::Value old;
				int oldeqid = 0;
				if(reader.parse(it->second,old) && Json::GetInt(old,"id",oldeqid))
				{
					if(oldeqid != eqid)
					{
						error_log("[equip type error][uid=%u,id=%u,oldeqid=%d,eqid=%d]",uid,id,oldeqid,eqid);
						DATA_ERROR_RETURN_MSG("equip_type_error");
					}
					Json::GetInt(old,"ast",oldast);
					if(newast != oldast)
					{
						error_log("[equip ast error][uid=%u,id=%u,oldast=%d,newast=%d]",uid,id,oldast,newast);
						DATA_ERROR_RETURN_MSG("equip_ast_error");
					}
					Json::GetInt(old,"q",oldq);
					if(!OpenPlatform::IsEN() && OpenPlatform::GetType() != PT_TEST)
					{
						if(newq > oldq)
						{
							error_log("[equip q error][uid=%u,id=%u,oldq=%d,newq=%d]",uid,id,oldq,newq);
							DATA_ERROR_RETURN_MSG("equip_q_error");
						}
					}
					Json::GetInt(old,"hexp",oldhexp);
					if(newhexp != oldhexp)
					{
						error_log("[equip hexp error][uid=%u,id=%u,oldhexp=%d,newhexp=%d]",uid,id,oldhexp,newhexp);
						DATA_ERROR_RETURN_MSG("equip_hexp_error");
					}
					Json::GetInt(old,"sexp",oldsexp);
					if(newsexp != oldsexp)
					{
						error_log("[equip sexp error][uid=%u,id=%u,oldsexp=%d,newsexp=%d]",uid,id,oldsexp,newsexp);
						DATA_ERROR_RETURN_MSG("equip_sexp_error");
					}
					Json::GetInt(old,"lexp",oldlexp);
					if(newlexp != oldlexp)
					{
						error_log("[equip lexp error][uid=%u,id=%u,oldlexp=%d,newlexp=%d]",uid,id,oldlexp,newlexp);
						DATA_ERROR_RETURN_MSG("equip_lexp_error");
					}
					Json::GetInt(old, "star", oldstar);
					if (newstar != oldstar){
						data[i]["star"] = oldstar;
						error_log("[equipment star protect][uid = %u,oldstar=%d,newstar=%d]", uid, oldstar, newstar);
					}
					Json::GetInt(old, "yexp", oldyexp);
					if (newyexp != oldyexp){
						data[i]["yexp"] = oldyexp;
						error_log("[equipment yexp protect][uid = %u,oldyexp=%d,newyexp=%d]", uid, oldyexp, newyexp);
					}
					Json::GetInt(old, "tts", oldtts);
					if (newtts != oldtts){
						data[i]["tts"] = oldtts;
						error_log("[equipment tts protect][uid = %u,oldtts=%d,newtts=%d]", uid, oldtts, newtts);
					}

					Json::GetInt(old,"count",oldcount);
					if(oldcount > newcount)
					{
						needLog = true;
						logtype = "use";
					}
					else if(oldcount < newcount)
					{
						needLog = true;
						logtype = "add";
					}

					if(data[i].isMember("sub") && old.isMember("sub"))
					{
						//todo: fix flash equip sub bug
						bool f = false;
						Json::Value::Members members(data[i]["sub"].getMemberNames());
						for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
						{
							if(!old["sub"].isMember(*it) || old["sub"][*it].asUInt() != data[i]["sub"][*it].asUInt())
							{
								error_log("[equip sub error][uid=%u,id=%u]",uid,id);
								//DATA_ERROR_RETURN_MSG("equip_sub_error");
								f = true;
								break;
							}
						}
						if(f)
							continue;
					}
				}
			}
			else
			{
#if SERVER_EQUIP_ADDABLE == 1
				//continue;
				error_log("[no equip id][uid=%u,id=%u,eqid=%d]",uid,id,eqid);
				DATA_ERROR_RETURN_MSG("no_equip_id");
#else
				needLog = true;
				logtype = "new";
#endif
			}
		}

		string equipData = writer.write(data[i]);

		if (data[i].isMember("status")
				&& data[i]["status"].isIntegral()
				&& data[i]["status"].asInt() == 9)
		{
			logtype = "del";
			ret = equipDB.RemoveEquipment(uid, id);
			if (ret != 0)
			{
				error_log("[RemoveEquipment fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_rm_equipment_fail");
			}

			oldeq.erase(id);
			if(oldeqbyid.count(eqid) && oldeqbyid[eqid]["ud"].asUInt() == id)
				oldeqbyid.erase(eqid);
		}
		else
		{
			ret = equipDB.ReplaceEquipment(uid, id, writer.write(data[i]));
			if (ret != 0)
			{
				error_log("[ReplaceEquipment fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
				DB_ERROR_RETURN_MSG("db_set_equipment_fail");
			}

			oldeq[id] = equipData;
			if(oldeqbyid.count(eqid) && oldeqbyid[eqid]["ud"].asUInt() == id)
				oldeqbyid[eqid] = data[i];
		}

		if (needLog)
		{
			EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,id,eqid,
					logtype.c_str(),newcount-oldcount,newcount,code.c_str(),equipData.c_str());
		}
	}
	return 0;
}

int CLogicEquipment::ImportEquipment(unsigned uid, Json::Value &data)
{
	if (!data.isArray())
	{
		error_log("[equipment type error][uid=%u,type=%d]",uid,data.type());
		DATA_ERROR_RETURN_MSG("data_equipment_error");
	}
	int ret = 0;
	Json::FastWriter writer;
	Json::Reader reader;
	CDataEquipment equipDB;

	for (unsigned i = 0; i < data.size(); i++)
	{
		unsigned id = 0;
		int eqid = 0;
		if (!Json::GetInt(data[i], "id", eqid))
		{
			string seqid;
			if (Json::GetString(data[i], "id", seqid))
			{
				eqid = CTrans::STOI(seqid);
			}
		}
		if (!Json::GetUInt(data[i], "ud", id) || eqid <= 0)
		{
			error_log("[equipment data error][uid=%u,index=%u,id=%u]",uid,i,id);
			DATA_ERROR_RETURN_MSG("data_equipment_error");
		}

		string equipData = writer.write(data[i]);

		ret = equipDB.ReplaceEquipment(uid, id, writer.write(data[i]));
		if (ret != 0)
		{
			error_log("[ReplaceEquipment fail][uid=%u,id=%u,ret=%d]",uid,id,ret);
			DB_ERROR_RETURN_MSG("db_set_equipment_fail");
		}
	}
	return 0;
}

int CLogicEquipment::GetEquipmentUsed(unsigned uid, Json::Value &data)
{
	CDataEquipment equipDB;
	vector<DataEquipment> datas;
	int ret = equipDB.GetEquipment(uid, datas);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("[GetEquipment fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_equipment_fail");
	}
	Json::Reader reader;
	data.resize(0);
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value json;
		if (!reader.parse(datas[i].data, json))
		{
			error_log("[parse fail][uid=%u,id=%u,i=%u]",uid,datas[i].id,i);
			continue;
		}
		if(json.isMember("newAdd"))
			json.removeMember("newAdd");
		int status = 0;
		if (Json::GetInt(json, "status", status) && status != 0 && status != 9)
		{
			data.append(json);
		}
	}
	return 0;
}

int CLogicEquipment::UseEquipmentEx(unsigned uid, unsigned eqid, unsigned ud, unsigned count, string reason, int &newcount)
{
	if (IS_UN_OVERLAY_ID(eqid) && count > 1)
		return R_ERR_LOGIC;

	Json::Value data;
	Json::FastWriter writer;
	int ret = Get(uid, ud,data);
	if(ret != 0)
	{
		return ret;
	}

	unsigned id = data["id"].asUInt();
	if(id != eqid)
	{
		error_log("eqid error id=%u, para=%u", id, eqid);
		return R_ERR_LOGIC;
	}
	if(data.isMember("ats") && data["ats"].asUInt() < Time::GetGlobalTime())
	{
		error_log("use equip time passed id=%u", id);
		return R_ERR_LOGIC;
	}

	string logtype;
	if (IS_UN_OVERLAY_ID(eqid) || data["count"].asInt() == count)
	{
		ret = Del(uid,ud);
		newcount = 0;
		logtype = "del";
	}
	else if(data["count"].asInt() < count)
	{
		error_log("use equip not enough id=%u,now_count=%d,count=%u", id, data["count"].asInt(), count);
		return R_ERR_LOGIC;
	}
	else
	{
		newcount = data["count"].asInt()-count;
		data["count"] = newcount;
		ret = Chg(uid, ud, data);
		logtype = "use";
	}
	if(ret == 0) {
		string equipData = writer.write(data);
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=%s,chg=%d,count=%d,code=%s,data=%s",uid,ud,eqid,
						logtype.c_str(),-count,newcount,reason.c_str(),equipData.c_str());
	}
	return ret;
}
int CLogicEquipment::UseEquipment(unsigned uid, unsigned eqid, unsigned ud, unsigned count, string reason)
{
	int newcount;
	return UseEquipmentEx(uid, eqid, ud, count, reason, newcount);
}

// 添加单件装备
// reason: 获得原因
int CLogicEquipment::AddOneItem(unsigned uid, unsigned eqid, unsigned count, string reason,Json::Value &result, bool merge, unsigned ch, unsigned q, unsigned a){
	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	ItemAdd item(eqid,count,reason,ch,q,a);
	genEquip(item,newEqDatas);
	return UpdateEquipment(uid, 0, newEqDatas, result, merge);
}
int CLogicEquipment::AddItems(unsigned uid, vector<ItemAdd> &items, Json::Value &result, bool merge)
{
	if(items.empty())
		return 0;

	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	for(unsigned i=0;i<items.size();++i)
		genEquip(items[i],newEqDatas);
	return UpdateEquipment(uid, 0, newEqDatas, result, merge);
}
int CLogicEquipment::genEquip(ItemAdd &item, Json::Value &data)
{
	if(!data.isArray())
		data.resize(0);
	if(IS_UN_OVERLAY_ID(item.eqid))
	{
		for(int i=0;i<item.count;++i)
		{
			Json::Value res;
			res["count"] = 0;
			res["id"] = item.eqid;
			res["code"] = item.reason;
			res["newAdd"] = 1;
			res["status"] = 0;
			res["ud"] = 0;
			if(IS_EQ_EQID(item.eqid))
			{
				res["ch"] = item.ch;
				res["q"] = item.q;
				if(IS_KEEPSAKE_EQID(item.eqid))
				{
					res["xwexp"] = item.xwexp;
					if(item.xwsub.empty())
					{
						try{
							KeepsakeUnit::UnlockSlave(res);
						}
						catch(const std::exception& e){}
					}
					else
						res["xwsub"] = item.xwsub;
				}
				else if(IS_STAR_STONE_EQID(item.eqid))
					res["sexp"] = item.sexp;
				else if(IS_TOKEN_EQID(item.eqid) ||IS_NEWWORLD_STONE_EQID(item.eqid))
					res["lexp"] = item.lexp;
				else if(IS_HORSE_EQID(item.eqid))
					res["hexp"] = item.hexp;
			}
			if(item.ats)
				res["ats"] = item.ats + Time::GetGlobalTime();

			data.append(res);
		}
	}
	else
	{
		Json::Value res;
		res["count"] = item.count;
		res["id"] = item.eqid;
		res["code"] = item.reason;
		res["newAdd"] = 1;
		res["status"] = 0;
		res["ud"] = 0;
		if(item.ats)
			res["ats"] = item.ats + Time::GetGlobalTime();

		data.append(res);
	}
	return 0;
}

int CLogicEquipment::Get(unsigned uid, unsigned id, Json::Value &data)
{
	string sdata;
	CDataEquipment eqDB;
	Json::Reader reader;
	int ret = 0;
	ret = eqDB.GetEquipment(uid, id,sdata);
	if (ret != 0)
	{
		error_log("[GetEquipment fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("get_Equipment_fail");
	}

	if (!reader.parse(sdata, data))
	{
		error_log("[Equipment error][uid=%u,ud=%u]",uid,id);
		DATA_ERROR_RETURN_MSG("data_Equipment_error");
	}
	else if(data.isMember("newAdd"))
		data.removeMember("newAdd");

	return 0;
}
int CLogicEquipment::Del(unsigned uid, unsigned id)
{
	CDataEquipment eqDB;
	int ret = 0;
	ret = eqDB.RemoveEquipment(uid, id);
	if (ret != 0)
	{
		error_log("[DelEquipment fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("del_Equipment_fail");
	}
	return 0;
}
int CLogicEquipment::Chg(unsigned uid, unsigned id, Json::Value &data)
{
	int ret = 0;
	CDataEquipment eqDB;
	Json::FastWriter writer;

	/*****************************
	Json::Reader reader;
	Json::Value old;
	string sdata;

	unsigned eid = 0, ud = 0;
	if (!Json::GetUInt(data, "id", eid) || !Json::GetUInt(data, "ud", ud))
	{
		error_log("[Equipment data error][uid=%u,ud=%u]",uid,ud);
		DATA_ERROR_RETURN_MSG("Equipment_building_error");
	}

	ret = eqDB.GetEquipment(uid, ud,sdata);
	if (ret != 0)
	{
		error_log("[GetEquipment fail][uid=%u,ud=%u,ret=%d]",uid,ud,ret);
		DB_ERROR_RETURN_MSG("get_Equipment_fail");
	}
	if (!reader.parse(sdata, old))
	{
		error_log("[Equipment error][uid=%u,ud=%u]",uid,ud);
		DATA_ERROR_RETURN_MSG("data_Equipment_error");
	}

	unsigned oldeid = 0;
	if(!Json::GetUInt(old, "id", oldeid) || oldeid != eid)
	{
		error_log("[Equipment type error][uid=%u,ud=%u,id=%u,oldid=%u]",uid,ud,eid,oldeid);
		DATA_ERROR_RETURN_MSG("Equipment_type_error");
	}
	*******************************/

	ret = eqDB.SetEquipment(uid, id, writer.write(data));
	if (ret != 0)
	{
		error_log("[setEquipment fail][uid=%u,ud=%u,ret=%d]",uid,id,ret);
		DB_ERROR_RETURN_MSG("db_set_equipment_fail");
	}
	return 0;
}

int CLogicEquipment::Try(unsigned uid, unsigned eqid, unsigned ud, unsigned count)
{
	Json::Value data;
	Json::FastWriter writer;
	int ret = Get(uid, ud,data);
	if(ret != 0)
		return ret;

	if(data["id"].asUInt() != eqid)
		return R_ERR_LOGIC;
	if(data.isMember("ats") && data["ats"].asUInt() < Time::GetGlobalTime())
		return R_ERR_LOGIC;
	if(data["count"].asInt() < count)
		return R_ERR_LOGIC;

	return 0;
}

int CLogicEquipment::genEquipSet(ItemAdd &item, Json::Value &data, Json::Value &sub, unsigned gemlocks)
{
	if(!data.isArray())
		data.resize(0);
	if(IS_SET_EQID(item.eqid))
	{
		for(int i=0;i<item.count;++i)
		{
			Json::Value res;
			res["count"] = 0;
			res["id"] = item.eqid;
			res["code"] = item.reason;
			res["newAdd"] = 1;
			res["status"] = 0;
			res["ud"] = 0;
			res["ch"] = item.ch;
			res["q"] = item.q;
			res["gemlocks"] = Convert::UIntToString(gemlocks);
			res["sub"] = sub;
			if(item.ats)
				res["ats"] = item.ats + Time::GetGlobalTime();
			data.append(res);
		}
	}

	return 0;
}


int CLogicEquipment::genFashion(ItemAdd &item, bool can_die, unsigned ts, Json::Value &data)
{
	if (!IS_FASHION_EQID(item.eqid))
	{
		LOGIC_ERROR_RETURN_MSG("must be fashion id");
	}
	if (can_die && (0==ts))
	{
		PARAM_ERROR_RETURN_MSG("ts need above 0");
	}
	if ((!can_die) && (0!=ts))
	{
		PARAM_ERROR_RETURN_MSG("ts need equal 0");
	}

	if(!data.isArray())
		data.resize(0);
	for(int i = 0; i < item.count; ++i)
	{
		Json::Value res;
		res["count"] = 0;
		res["id"] = item.eqid;
		res["code"] = item.reason;
		res["newAdd"] = 1;
		res["status"] = 0;
		res["ud"] = 0;
		res["ch"] = item.ch;
		res["q"] = item.q;
		if (can_die)
		{
			res["ats"] = ts;
		}
		data.append(res);
	}

	return 0;
}
