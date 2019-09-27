/*
 * LogicCMD4.cpp
 *
 *  Created on: 2016-11-15
 *      Author: Ralf
 */


#include "LogicCMD.h"
#include "LogicUnitWrap.h"
#include "LogicCmdUnits.h"
#include <math.h>
#include <climits>

int CLogicCMD::BuildEquipSet(unsigned uid, unsigned part, unsigned occupation, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	if(occupation > 2 || part > 9)
	{
		error_log("[BuildEquipSet param error!!!][uid=%u,occupation=%u,part=%u]", uid, occupation, part);
		return R_ERR_PARAM;
	}
	unsigned level = 60;
	int wuxing = Math::GetRandomInt(5);
	unsigned build_id = 151000 + occupation*100 + wuxing*10 + part;

	Json::Value data;
	ret = pDataXML->GetBuildOrUpSetCailiao(level, part, data);
	if(ret)
	{
		error_log("[GetBuildOrUpSetCailiao] [uid=%u,level=%u,part=%u]", uid, level, part);
		return R_ERR_DATA;
	}

	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	if(data["result"].asString() == "success")
	{
		unsigned mar_num = 0;
		Json::Value::Members members(data["json_data"]["material"].getMemberNames());
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			if(type.find("equip") != string::npos )
			{
				unsigned id = data["json_data"]["material"][*it]["id"].asUInt();
				unsigned count = data["json_data"]["material"][*it]["c"].asUInt();
				unsigned people_count = 0;
				unsigned flag = 0;
				for(int i=0; i<equip_data.size(); ++i)
				{
					if(equip_data[i]["id"].asUInt() == id)
					{
						string reason = "BuildEquipSet";
						people_count = equip_data[i]["count"].asUInt();
						equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
						ret = logicEquip.UseEquipment(uid, id, equip_data[i]["ud"].asUInt(), count, reason);
						if(ret)
							return ret;
						result["use_material"][mar_num] = equip_data[i];
						flag = 1;
						++mar_num;
						break;
					}
				}
				if(flag != 1)
				{
					error_log("[BuildEquipSet_Lack_Cailiao] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]", uid, id, count, people_count);
					return R_ERR_DATA;
				}
			}
			else if(type.find("bs") != string::npos)
			{
				string code = "BuildEquipSet";
				unsigned needbs = data["json_data"]["material"][*it].asUInt();
				int battle_spirits = dataUser.battle_spirits - needbs;
				if(battle_spirits < 0)
				{
					error_log("[BuildEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, needbs, dataUser.battle_spirits);
					return R_ERR_DATA;
				}
				dataUser.battle_spirits = battle_spirits;
				result["battle_spirits"] = battle_spirits;
			}
		}
	}
	else
	{
		error_log("olequipset.xml data error");
		return R_ERR_DB;
	}

	unsigned subNum = getSubNumByCh(5);
	vector<EquipSub> sub;
	vector<string> keepstr;
	unsigned stoneID,gold;
	ret = pDataXML->GetEquipSub(level,stoneID,gold,subNum,keepstr,sub);
	Json::Value newSub;
	for(int i=0;i<sub.size();++i)
		newSub[sub[i].id] = sub[i].value;

	string item_reason = "BuildEquipSet";
	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	ItemAdd item(build_id, 1, item_reason, 5,  0);
	logicEquip.genEquipSet(item, newEqDatas, newSub, 1100);

	ret = logicEquip.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	if(ret)
	{
		error_log("build_equip_set_error uid=%u | equip_id=%u", uid, build_id);
		return R_ERR_DATA;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::UpgradeEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned level = unsigned((equip_id - 150000) / 1000) * 10 + 60;
	if(level > 110)
	{
		error_log("[UpgradeEquipSet_level_error][uid=%u,level=%u]", uid, level-10);
		return R_ERR_PARAM;
	}
	unsigned part = equip_id % 10;
	int wuxing = Math::GetRandomInt(5);
	unsigned new_equip_id = unsigned(equip_id / 100) * 100 + 1000 + wuxing*10 + part;

	CLogicEquipment logicEquip;
	Json::Value items_gem;
	logicEquip.Get(uid, ud, items_gem);
	if(equip_id != items_gem["id"].asUInt())
	{
		error_log("[upgradeEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, items_gem["id"].asUInt());
		return R_ERR_PARAM;
	}

	Json::Value data;
	ret = pDataXML->GetBuildOrUpSetCailiao(level, part, data);
	if(ret)
	{
		error_log("[GetBuildOrUpSetCailiao] [uid=%u,level=%u,part=%u]", uid, level, part);
		return R_ERR_DATA;
	}

	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	if(data["result"].asString() == "success")
	{
		unsigned mar_num = 0;
		Json::Value::Members members(data["json_data"]["material"].getMemberNames());
		for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			string type = *it;
			if(type.find("equip") != string::npos )
			{
				unsigned id = data["json_data"]["material"][*it]["id"].asUInt();
				unsigned count = data["json_data"]["material"][*it]["c"].asUInt();
				unsigned people_count = 0;
				unsigned flag = 0;
				for(int i=0; i<equip_data.size(); ++i)
				{
					if(equip_data[i]["id"].asUInt() == id)
					{
						string reason = "UpgradeEquipSet";
						people_count = equip_data[i]["count"].asUInt();
						equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
						ret = logicEquip.UseEquipment(uid, id, equip_data[i]["ud"].asUInt(), count, reason);
						if(ret)
							return ret;
						result["use_material"][mar_num] = equip_data[i];
						flag = 1;
						++mar_num;
						break;
					}
				}
				if(flag != 1)
				{
					error_log("[UpgradeEquipSet_Lack_Cailiao] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]", uid, id, count, people_count);
					return R_ERR_DATA;
				}
			}
			else if(type.find("bs") != string::npos)
			{
				unsigned needbs = data["json_data"]["material"][*it].asUInt();
				int battle_spirits = dataUser.battle_spirits - needbs;
				if(battle_spirits < 0)
				{
					error_log("[UpgradeEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, needbs, dataUser.battle_spirits);
					return R_ERR_DATA;
				}
				dataUser.battle_spirits = battle_spirits;
				result["battle_spirits"] = battle_spirits;
			}

		}
	}
	else
	{
		error_log("olequipset.xml data error");
		return R_ERROR;
	}

	if(items_gem.isMember("gems"))
	{
		if(items_gem["gems"].isMember("1"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, items_gem["gems"]["1"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, items_gem["gems"]["1"].asUInt(), gem_data);
		}
		if(items_gem["gems"].isMember("2"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, items_gem["gems"]["2"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, items_gem["gems"]["2"].asUInt(), gem_data);
		}
		if(items_gem["gems"].isMember("3"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, items_gem["gems"]["3"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, items_gem["gems"]["3"].asUInt(), gem_data);
		}
		if(items_gem["gems"].isMember("4"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, items_gem["gems"]["4"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, items_gem["gems"]["4"].asUInt(), gem_data);
		}
	}

	ret = logicEquip.Del(uid, ud);
	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=del,chg=1,count=0,code=UpgradeEquipSet,data=UpgradeEquipSet",uid,ud,equip_id);
	}

	result["del_equip"] = items_gem;

	unsigned subNum = getSubNumByCh(5);
	vector<EquipSub> sub;
	vector<string> keepstr;
	unsigned stoneID,gold;
	ret = pDataXML->GetEquipSub(level,stoneID,gold,subNum,keepstr,sub);
	Json::Value newSub;
	for(int i=0;i<sub.size();++i)
		newSub[sub[i].id] = sub[i].value;

	string item_reason = "UpgradeEquipSet";
	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	ItemAdd item(new_equip_id, 1, item_reason, 5,  0);
	logicEquip.genEquipSet(item, newEqDatas, newSub, 1100);

	ret = logicEquip.UpdateEquipment(uid, 0, newEqDatas, result["add_equip"], true);
	if(ret)
	{
		error_log("upgrade_equip_set_error uid=%u | equip_id=%u", uid, new_equip_id);
		return R_ERR_DATA;
	}

	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::RefineEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid, unsigned kind)
{
	if (kind >= RefineTypeMax)
		return R_ERR_PARAM;

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	string error_string = (kind == Refine)?"Refine": (kind == ShenZhu ? "ShenZhu":"ShenQi");

	unsigned level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	if((kind == Refine && level != 110) || (kind == ShenZhu && level != 120))
	{
		error_log("[%sEquipSet_level_error][uid=%u,equip_id=%u,level=%u]",error_string.c_str(), uid, equip_id, level);
		return R_ERR_PARAM;
	}
	unsigned new_equip_id = equip_id + 1000;

	CLogicEquipment logicEquip;
	Json::Value refine_data;
	logicEquip.Get(uid, ud, refine_data);
	if(equip_id != refine_data["id"].asUInt())
	{
		error_log("[%sEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]",error_string.c_str(), uid, equip_id, ud, refine_data["id"].asUInt());
		return R_ERR_PARAM;
	}

	Json::Value data;
	ret = pDataXML->GetRefineCailiao(data, kind);
	if(ret)
	{
		error_log("[Get%sCailiao_error] [uid=%u,equip_id=%u]",error_string.c_str(), uid, equip_id);
		return R_ERR_DATA;
	}

	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	unsigned mar_num = 0;
	Json::Value::Members members(data["material"].getMemberNames());
	for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
	{
		string type = *it;
		if(type.find("equip") != string::npos )
		{
			unsigned id = data["material"][*it]["id"].asUInt();
			unsigned count = data["material"][*it]["c"].asUInt();
			unsigned people_count = 0;
			unsigned flag = 0;
			for(int i=0; i<equip_data.size(); ++i)
			{
				if(equip_data[i]["id"].asUInt() == id)
				{
					string reason = (kind == Refine) ? "RefineEquipSet": (kind == ShenZhu ? "ShenZhuEquipSet":"ShenQiEquipSet");
					people_count = equip_data[i]["count"].asUInt();
					equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
					ret = logicEquip.UseEquipment(uid, id, equip_data[i]["ud"].asUInt(), count, reason);
					if(ret)
						return ret;
					result["use_material"][mar_num] = equip_data[i];
					flag = 1;
					++mar_num;
					break;
				}
			}
			if(flag != 1)
			{
				error_log("[%sEquipSet_Lack_Cailiao] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]",error_string.c_str(), uid, id, count, people_count);
				return R_ERR_DATA;
			}
		}
		if(type.find("bs") != string::npos && kind == ShenQi)
		{
			unsigned bs = data["material"][*it].asUInt();
			dataUser.battle_spirits = dataUser.battle_spirits - bs;
		}

	}

	refine_data["ch"] = 6;
	refine_data["id"] = new_equip_id;
	refine_data["code"] = (kind == Refine) ? "back_refine": (kind == ShenZhu ? "back_shenzhu":"back_shenqi");
	ret = logicEquip.Chg(uid, ud, refine_data);;
	if(ret == 0)
	{
		string reason = (kind == Refine) ? "RefineEquipSet": (kind == ShenZhu ? "ShenZhuEquipSet":"ShenQiEquipSet");
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=del,chg=1,count=0,code=%s,data=%s",uid,ud,equip_id,reason.c_str(),reason.c_str());
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=add,chg=1,count=0,code=%s,data=%s",uid,ud,new_equip_id,reason.c_str(),reason.c_str());
	}

	result["refine_equip"] = refine_data;
	result["battle_spirits"] = dataUser.battle_spirits;
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::WuxingEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	if(level < 60 || level >130)
	{
		error_log("[WuxingEquipSet_level_error][uid=%u,equip_id=%u,level=%u]", uid, equip_id, level);
		return R_ERR_PARAM;
	}
	if(level == 120)
		level = 110;
	else if(level == 130)
		level = 120;

	CLogicEquipment logicEquip;
	Json::Value wuxing_data;
	logicEquip.Get(uid, ud, wuxing_data);
	if(equip_id != wuxing_data["id"].asUInt())
	{
		error_log("[WuxingEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, wuxing_data["id"].asUInt());
		return R_ERR_PARAM;
	}

	unsigned count = 0;
	unsigned bs = 0;
	bool wuxingresult = false;
	ret = pDataXML->EquipSetWuxing(level, count, bs, wuxingresult);
	if(ret)
	{
		error_log("[EquipSetWuxing_error] [uid=%u,equip_id=%u]", uid, equip_id);
		return R_ERR_DATA;
	}

	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	unsigned flag = 0;
	unsigned people_count = 0;
	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asUInt() == WUXINGZHU_ID)
		{
			string reason = "WuxingEquipSet";
			people_count = equip_data[i]["count"].asUInt();
			equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
			ret = logicEquip.UseEquipment(uid, WUXINGZHU_ID, equip_data[i]["ud"].asUInt(), count, reason);
			if(ret)
				return ret;
			result["wuxingzhu"] = equip_data[i];
			flag = 1;
			break;
		}
	}
	if(flag != 1)
	{
		error_log("[WuxingEquipSet_Lack_wuxingzhu] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]", uid, WUXINGZHU_ID, count, people_count);
		return R_ERR_DATA;
	}

	int battle_spirits = dataUser.battle_spirits - bs;
	if(battle_spirits < 0)
	{
		error_log("[WuxingEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, bs, dataUser.battle_spirits);
		return R_ERR_DATA;
	}
	dataUser.battle_spirits = battle_spirits;
	result["battle_spirits"] = battle_spirits;

	if(false == wuxingresult)
	{
		result["xilian"] = "fail";
		ret = logicUser.SetUserLimit(uid, dataUser);
		if(ret)
			return ret;
		return 0;
	}
	result["xilian"] = "success";

	unsigned new_wuxing = Math::GetRandomInt(5);
	unsigned part = equip_id % 10;
	unsigned new_equip_id = unsigned(equip_id / 100) * 100 + new_wuxing*10 + part;


	if(wuxing_data.isMember("gems"))
	{
		if(wuxing_data["gems"].isMember("1"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, wuxing_data["gems"]["1"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, wuxing_data["gems"]["1"].asUInt(), gem_data);
		}
		if(wuxing_data["gems"].isMember("2"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, wuxing_data["gems"]["2"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, wuxing_data["gems"]["2"].asUInt(), gem_data);
		}
		if(wuxing_data["gems"].isMember("3"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, wuxing_data["gems"]["3"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, wuxing_data["gems"]["3"].asUInt(), gem_data);
		}
		if(wuxing_data["gems"].isMember("4"))
		{
			Json::Value gem_data;
			logicEquip.Get(uid, wuxing_data["gems"]["4"].asUInt(), gem_data);
			gem_data["status"] = 0;
			logicEquip.Chg(uid, wuxing_data["gems"]["4"].asUInt(), gem_data);
		}
		wuxing_data.removeMember("gems");
	}
	wuxing_data["gemlocks"] = "1100";
	wuxing_data["id"] = new_equip_id;
	wuxing_data["code"] = "change_wuxing_back";
	ret = logicEquip.Chg(uid, ud, wuxing_data);;
	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=0,code=wuxingEquipSet,data=wuxingEquipSet",uid,ud,new_equip_id);
	}

	result["xilian_equip"] = wuxing_data;
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::BlessEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &param, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::Reader reader;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned equip_level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	if(equip_level != 120 && equip_level != 130 && equip_level != 140)
	{
		error_log("[belssEquipSet_level_error][uid=%u,equip_id=%u,level=%u]", uid, equip_id, equip_level);
		return R_ERR_PARAM;
	}

	CLogicEquipment logicEquip;
	Json::Value bless_data;
	logicEquip.Get(uid, ud, bless_data);

	if(equip_id != bless_data["id"].asUInt())
	{
		error_log("[blessEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, bless_data["id"].asUInt());
		return R_ERR_PARAM;
	}
	unsigned bless_level = 0;
	unsigned exp = 0;

	if(bless_data.isMember("ble"))
	{
		exp = bless_data["ble"].asUInt();
	}

	if(bless_data.isMember("bls"))
	{
		bless_level = bless_data["bls"].asUInt();
	}

	//祝福到达最高等级
	if(bless_level >=10)
	{
		error_log("[EquipSet_blesslevel_Reached_the_top][uid=%u,equip_id=%u,bless_level=%u]", uid, equip_id, bless_level);
		return R_ERR_PARAM;
	}

	unsigned use_eqid = 0;
	unsigned count = 0;
	unsigned bs = 0;
	unsigned n_bless_level = 0;
	unsigned n_exp = 0;

	ret = pDataXML->EquipSetBless(bless_level, exp, use_eqid, count, bs, n_bless_level, n_exp);

	if(ret)
	{
		error_log("[EquipSetBless_error][uid=%u,equip_id=%u]", uid, equip_id);
		return R_ERR_DATA;
	}

	bless_data["ble"] = n_exp;
	bless_data["bls"] = n_bless_level;

	//优先消耗0-2级祝福石
	string reason = "blessEquipSet";

	unsigned limit_equd1 = 0;
	Json::GetUInt(param, "limit_equd", limit_equd1);

	if (limit_equd1 > 0 && (bless_level >=0 && bless_level < 3))
	{
		Json::Value limitdata;
		ret = logicEquip.Get(uid, limit_equd1, limitdata);

		if (0 == ret)
		{
			int num = limitdata["count"].asInt();

			if (num > 0)
			{
				unsigned cost_count = min(count, (unsigned)num);

				ret = logicEquip.UseEquipment(uid, BLESS_EQUIP_LIMIT_3, limit_equd1, cost_count, reason);

				if(0 == ret)
				{
					result["use_limit"] = cost_count;
					count -= cost_count;
				}
			}
		}
	}

	//消耗0-4级祝福石
	unsigned limit_equd2 = 0;
	Json::GetUInt(param, "limit_equd2", limit_equd2);

	if (count > 0 && limit_equd2 > 0 && (bless_level >= 0 && bless_level < 5 ))
	{
		Json::Value limitdata;
		ret = logicEquip.Get(uid, limit_equd2, limitdata);

		if (0 == ret)
		{
			int num = limitdata["count"].asInt();

			if (num > 0)
			{
				unsigned cost_count = min(count, (unsigned)num);

				ret = logicEquip.UseEquipment(uid, BLESS_EQUIP_LIMIT_5, limit_equd2, cost_count, reason);

				if(0 == ret)
				{
					result["use_limit2"] = cost_count;
					count -= cost_count;
				}
			}
		}
	}

	//消耗0-6级祝福石
	unsigned limit_equd3 = 0;
	Json::GetUInt(param, "limit_equd3", limit_equd3);

	if (count > 0 && limit_equd3 > 0 && (bless_level >=0 && bless_level < 7 ))
	{
		Json::Value limitdata;
		ret = logicEquip.Get(uid, limit_equd3, limitdata);

		if (0 == ret)
		{
			int num = limitdata["count"].asInt();

			if (num > 0)
			{
				unsigned cost_count = min(count, (unsigned)num);

				ret = logicEquip.UseEquipment(uid, BLESS_EQUIP_LIMIT_7, limit_equd3, cost_count, reason);

				if(0 == ret)
				{
					result["use_limit3"] = cost_count;
					count -= cost_count;
				}
			}
		}
	}

	//消耗普通道具
	if (count > 0)
	{
		unsigned flag = 0;
		unsigned people_count = 0;

		Json::Value equip_data;
		ret = logicEquip.GetEquipment(uid, 0, equip_data);

		if(ret)
			return ret;

		//获取所有道具，然后根据配置遍历查找需要消耗的道具
		for(int i=0; i<equip_data.size(); ++i)
		{
			if(equip_data[i]["id"].asUInt() == use_eqid)
			{
				people_count = equip_data[i]["count"].asUInt();
				equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;

				ret = logicEquip.UseEquipment(uid, use_eqid, equip_data[i]["ud"].asUInt(), count, reason);

				if(ret)
					return ret;

				result["use_bless"] = equip_data[i];
				flag = 1;
				break;
			}
		}

		if(flag != 1)
		{
			error_log("[BlessEquipSet_Lack] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]", uid, use_eqid, count, people_count);
			return R_ERR_DATA;
		}
	}

	int battle_spirits = dataUser.battle_spirits - bs;

	if(battle_spirits < 0)
	{
		error_log("[blessEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, bs, dataUser.battle_spirits);
		return R_ERR_DATA;
	}

	dataUser.battle_spirits = battle_spirits;
	result["battle_spirits"] = battle_spirits;

	Json::FastWriter writer;
	string bless_data_str = writer.write(bless_data);

	ret = logicEquip.Chg(uid, ud, bless_data);

	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=0,code=BlessEquipSet,data=%s",uid, ud, equip_id, bless_data_str.c_str());
	}

	result["bless_equip"] = bless_data;
	ret = logicUser.SetUserLimit(uid, dataUser);

	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::ShenWenEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::Reader reader;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned equip_level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	if(equip_level != 130 && equip_level != 140)
	{
		error_log("[ShenWenEquipSet_level_error][uid=%u,equip_id=%u,level=%u]", uid, equip_id, equip_level);
		return R_ERR_PARAM;
	}

	CLogicEquipment logicEquip;
	Json::Value bless_data;
	logicEquip.Get(uid, ud, bless_data);
	if(equip_id != bless_data["id"].asUInt())
	{
		error_log("[blessEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, bless_data["id"].asUInt());
		return R_ERR_PARAM;
	}
	unsigned bless_level = 0;
	unsigned exp = 0;
	Json::GetUInt(bless_data, "swe", exp);
	Json::GetUInt(bless_data, "swl", bless_level);

	//祝福到达最高等级
	if(bless_level >=10)
	{
		error_log("[EquipSet_ShenWenlevel_Reached_the_top][uid=%u,equip_id=%u,bless_level=%u]", uid, equip_id, bless_level);
		return R_ERR_PARAM;
	}
	unsigned use_eqid = 0;
	unsigned count = 0;
	unsigned bs = 0;
	unsigned n_bless_level = 0;
	unsigned n_exp = 0;
	ret = pDataXML->EquipSetShenWen(bless_level, exp, use_eqid, count, bs, n_bless_level, n_exp);
	if(ret)
	{
		error_log("[EquipSetBless_error][uid=%u,equip_id=%u]", uid, equip_id);
		return R_ERR_DATA;
	}
	bless_data["swe"] = n_exp;
	bless_data["swl"] = n_bless_level;

	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	unsigned flag = 0;
	unsigned people_count = 0;
	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asUInt() == use_eqid)
		{
			string reason = "ShenWenEquipSet";
			people_count = equip_data[i]["count"].asUInt();
			equip_data[i]["count"] = equip_data[i]["count"].asUInt() - count;
			ret = logicEquip.UseEquipment(uid, use_eqid, equip_data[i]["ud"].asUInt(), count, reason);
			if(ret)
				return ret;
			result["use_bless"] = equip_data[i];
			flag = 1;
			break;
		}
	}
	if(flag != 1)
	{
		error_log("[ShenWenEquipSet_Lack] [uid=%u,lack_id=%u,needcount=%u,peoplecount=%u]", uid, use_eqid, count, people_count);
		return R_ERR_DATA;
	}

	int battle_spirits = dataUser.battle_spirits - bs;
	if(battle_spirits < 0)
	{
		error_log("[ShenWenEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, bs, dataUser.battle_spirits);
		return R_ERR_DATA;
	}
	dataUser.battle_spirits = battle_spirits;
	result["battle_spirits"] = battle_spirits;

	Json::FastWriter writer;
	string bless_data_str = writer.write(bless_data);

	ret = logicEquip.Chg(uid, ud, bless_data);;
	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=0,code=ShenWenEquipSet,data=%s",uid, ud, equip_id, bless_data_str.c_str());
	}

	result["bless_equip"] = bless_data;
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}



int CLogicCMD::ShenGeEquipSet(unsigned uid, unsigned equip_id, unsigned ud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	Json::Reader reader;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get_user_info_failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned equip_level = unsigned((equip_id - 150000) / 1000) * 10 + 50;
	if(equip_level != 110 && equip_level != 130 && equip_level != 140)
	{
		error_log("[ShenGeEquipSet_level_error][uid=%u,equip_id=%u,level=%u]", uid, equip_id, equip_level);
		return R_ERR_PARAM;
	}
	CLogicEquipment logicEquip;
	Json::Value shenge_data;
	logicEquip.Get(uid, ud, shenge_data);
	if(equip_id != shenge_data["id"].asUInt())
	{
		error_log("[ShenGeEquipSet_equpid_or_ud_error][uid=%u,equip_id=%u,ud=%u,ud_equipid=%u]", uid, equip_id, ud, shenge_data["id"].asUInt());
		return R_ERR_PARAM;
	}
	unsigned shenge_level = 0;
	unsigned exp = 0;
	Json::GetUInt(shenge_data, "sge", exp);
	Json::GetUInt(shenge_data, "sgl", shenge_level);

	//祝福到达最高等级
	if(shenge_level >=10)
	{
		error_log("[EquipSet_ShenGelevel_Reached_the_top][uid=%u,equip_id=%u,shenge_level=%u]", uid, equip_id, shenge_level);
		return R_ERR_PARAM;
	}
	unsigned use_eqid[3] = {0};
	unsigned count[3] = {0};
	unsigned bs = 0;
	unsigned n_shenge_level = 0;
	unsigned n_exp = 0;
	ret = pDataXML->EquipSetShenGe(shenge_level, exp, use_eqid, count, bs, n_shenge_level, n_exp);
	if(ret)
	{
		error_log("[EquipSetShenGe_error][uid=%u,equip_id=%u]", uid, equip_id);
		return R_ERR_DATA;
	}
	shenge_data["sge"] = n_exp;
	shenge_data["sgl"] = n_shenge_level;

	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	map<int, unsigned> visit;

	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asUInt() == use_eqid[0])
		{
			visit.insert(std::pair<int, unsigned>(i, count[0]));
		}
		else if(equip_data[i]["id"].asUInt() == use_eqid[1])
		{
			visit.insert(std::pair<int, unsigned>(i, count[1]));
		}
		else if( equip_data[i]["id"].asUInt() == use_eqid[2])
		{
			visit.insert(std::pair<int, unsigned>(i, count[2]));
		}
	}

	if(visit.size() != 3)
	{
		error_log("[ShenGeEquipSet_error][uid=%u,equip_id=%u][size= %u], lack eqid", uid, equip_id, visit.size());
			return R_ERR_DATA;
	}
	for(map<int, unsigned>::iterator it = visit.begin(); it != visit.end(); ++it)
	{
		string reason = "ShenGeEquipSet";
		equip_data[it->first]["count"] = equip_data[it->first]["count"].asUInt() - it->second;
		ret = logicEquip.UseEquipment(uid, equip_data[it->first]["id"].asUInt(), equip_data[it->first]["ud"].asUInt(), it->second, reason);
		if(ret)
			return ret;
		result["use_bless"].append(equip_data[it->first]);

	}
	int battle_spirits = dataUser.battle_spirits - bs;
	if(battle_spirits < 0)
	{
		error_log("[ShenGeEquipSet_Lack_battle_spirits] [uid=%u,needchangebs=%u,peoplebs=%u]", uid, bs, dataUser.battle_spirits);
		return R_ERR_DATA;
	}
	dataUser.battle_spirits = battle_spirits;
	result["battle_spirits"] = battle_spirits;

	Json::FastWriter writer;
	string bless_data_str = writer.write(shenge_data);

	ret = logicEquip.Chg(uid, ud, shenge_data);
	if(ret == 0)
	{
		EQUIPMENT_LOG("uid=%u,id=%u,eqid=%d,act=oth,chg=0,count=0,code=ShenGeEquipSet,data=%s",uid, ud, equip_id, bless_data_str.c_str());
	}

	result["bless_equip"] = shenge_data;
	ret = logicUser.SetUserLimit(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::AddSoul(unsigned uid, bool isCash, unsigned type, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	unsigned soul = 0;
	Json::GetUInt(tech, "soul", soul);
	unsigned exp = SOUL_EXP * soul;
	unsigned lvl = 0;
	for(int i=SOUL_LVL-1;i>=0;--i)
	{
		if(exp >= SOUL_LVL_EXP[i])
		{
			lvl = i + 1;
			break;
		}
	}
	unsigned addp = ADD_SOUL_P;
	if(lvl >= SOUL_LVL_ADD)
		addp += (lvl - SOUL_LVL_ADD + 1) * ADD_SOUL_P;
	if(addp > ADD_SOUL_MAX)
		addp = ADD_SOUL_MAX;
	int addc = ADD_SOUL_COIN;

	unsigned prosper_sub_cash = 0;
	if (isCash) //花钻石
	{
		if (lvl >= SOUL_LVL_ADD || dataUser.level < 80)
		{
			return R_ERR_LOGIC;
		}
		//满足条件的
		unsigned soul_times = 0;
		if(!Json::GetUInt(tech, "soultimes", soul_times))
		{
			soul_times = 0;
		}
		prosper_sub_cash = -(floor(soul_times/10)*4 + 1);
		addp = 0;
		tech["soultimes"] = soul_times + 1;
		result["soultimes"] = soul_times + 1;
	} else if (addp > dataUser.prosper) //不花钻
	{
		return R_ERR_LOGIC;
	}

	CLogicPay logicPay;
	DataPay payData;
	unsigned other_sub_cash = type?-addc:0;
	ret = logicPay.ProcessOrderForBackend(uid, other_sub_cash + prosper_sub_cash, type?0:-addc, payData, "play_jiangling_soul",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	dataUser.prosper -= addp;
	result["prosper"] = dataUser.prosper;

	++soul;
	tech["soul"] = soul;
	result["soul"] = soul;

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;
	RESOURCE_LOG("[AddSoul][uid=%u,chgprosper=%d,prosper=%u]",uid,-addp,dataUser.prosper);

	return R_SUCCESS;
}

int CLogicCMD::NewLotteryActivity(unsigned uid, unsigned level, unsigned count, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_E_TS))
	{
		error_log("activity_new_lottery_time_error");
		return R_ERR_REFUSE;
	}
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	if(level >2)
	{
		error_log("[level_error][uid=%u,level=%u]", uid, level);
		return R_ERR_PARAM;
	}

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	vector <unsigned> id;
	vector <unsigned> type_id;
	vector <unsigned> rate;
	vector <unsigned> eqid;
	vector <unsigned> num;
	vector <unsigned> total;
	unsigned openfloor = 0;
	unsigned cash = 0;
	ret =  pDataXML->GetNewLottery(uid, level, id, type_id, rate, eqid, num, total, openfloor, cash);
	if(ret)
	{
		error_log("[XMLNewLottery_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	CDataNewlottery *p_newlottery_data= GetNewLotteryData();
	if(p_newlottery_data == NULL)
	{
		DB_ERROR_RETURN_MSG("init_newlottery_data_fail");
	}

	vector <unsigned> get_id;
	vector <unsigned> over_num;

	vector <unsigned> awards_id;
	vector <unsigned> awards_eqid;
	vector <unsigned> awards_typeid;
	vector <unsigned> awards_num;
	vector <RareItemsWinner> peoples;
	ret = p_newlottery_data->GetNewLotteryActivity(uid, level, count, total, rate, id, type_id, eqid, num
			,  awards_id, awards_eqid, awards_typeid, awards_num
			, get_id, over_num, peoples);
	if(ret)
	{
		error_log("[GetRareItemsNumbers_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}
	CLogicSecinc Secinc;
	Json::Value LotterySecincData;
	ret = Secinc.GetSecinc(uid, NAT_TURN_TABLE, LotterySecincData);
	if(ret!=0 && ret!=R_ERR_NO_DATA)
	{
		return ret;
	}

	unsigned cost_cash = count * cash;
	if(level == 1)
	{
		if(!LotterySecincData.isMember("first"))
		{
			LotterySecincData["id"] = NAT_TURN_TABLE;
			LotterySecincData["firsttotal"] = count;
			LotterySecincData["first"] = count;
			LotterySecincData["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER);
			LotterySecincData["second_num"] = unsigned(count / 5);
		}
		else
		{
			LotterySecincData["firsttotal"] = LotterySecincData["firsttotal"].asUInt() + count;
			LotterySecincData["first"] = LotterySecincData["first"].asUInt() + count;
			LotterySecincData["second_num"] = unsigned(LotterySecincData["first"].asUInt() / 5);
		}
	}
	else if(level == 2)
	{
		if(!LotterySecincData.isMember("first") || LotterySecincData["second_num"].asUInt()<count)
		{
			error_log("[second_layer_lottery_not_enough][uid=%u,]", uid);
			return R_ERR_PARAM;
		}

		LotterySecincData["first"] = LotterySecincData["first"].asUInt() - count*openfloor;
		LotterySecincData["second_num"] = unsigned(LotterySecincData["first"].asUInt() / 5);
	}
	result["firsttotal"] = LotterySecincData["firsttotal"].asUInt();
	result["second_num"] = LotterySecincData["second_num"].asUInt();

	vector<ItemAdd> equip_items;
	vector<string> hero_id;
	vector<string> hero_code;
	for(int i=0; i<awards_id.size(); ++i)
	{
		if(awards_typeid[i]==2)	//抽到英雄
		{
			string code = "activity_new_lottery";
			hero_id.push_back(CDataXML::Hero2Str(awards_eqid[i]));
			hero_code.push_back(code);
		}
		else
		{
			ItemAdd eqip;
			eqip.eqid = awards_eqid[i];
			eqip.count = awards_num[i];
			eqip.q = 0;
			eqip.ch = 0;
			eqip.reason = "activity_new_lottery";
			equip_items.push_back(eqip);
		}
		result["id"][i] = awards_id[i];
	}

	for(int i=0; i<get_id.size(); ++i)
	{
		string type_id = CTrans::ITOS(get_id[i]);
		result["value"][type_id] = over_num[i];
	}

	for(int i=0; i<peoples.size(); ++i)
	{
		result["awards"][i]["eqid"] = peoples[i].eqid;
		result["awards"][i]["num"] = peoples[i].num;
		result["awards"][i]["name"] = peoples[i].name;
		result["awards"][i]["type_id"] = peoples[i].type_id;
		result["awards"][i]["uid"] = peoples[i].uid;
	}

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	CLogicPay logicPay;
	DataPay payData;
	ret = logicPay.ProcessOrderForBackend(uid, -cost_cash, 0, payData, "activity_new_lottery",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	if(equip_items.size() > 0)
	{
		CLogicEquipment Equip;
		ret = Equip.AddItems(uid,equip_items,result["add_equip"], true);
		if(ret)
		{
			error_log("[Add_Equip_error][uid=%u]", uid);
			return ret;
		}
	}

	if(hero_id.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,hero_id,hero_code,result["hero"]);
		if(ret)
		{
			error_log("[Add_hero_error][uid=%u]", uid);
			return ret;
		}
	}

	ret = Secinc.SetOneSecinc(uid, LotterySecincData);
	if(ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::GetNewLotteryData(unsigned uid, Json::Value &result)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_E_TS))
	{
		error_log("activity_new_lottery_time_error");
		return R_ERR_REFUSE;
	}
	int ret = 0;

	CLogicSecinc Secinc;
	Json::Value LotterySecincData;
	ret = Secinc.GetSecinc(uid, NAT_TURN_TABLE, LotterySecincData);
	if(ret!=0 && ret!=R_ERR_NO_DATA)
	{
		return ret;
	}

	if(!LotterySecincData.isMember("firsttotal"))
	{
		LotterySecincData["id"] = NAT_TURN_TABLE;
		LotterySecincData["firsttotal"] = 0;
		LotterySecincData["first"] = 0;
		LotterySecincData["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER);
		LotterySecincData["second_num"] = 0;
		result["firsttotal"] = 0;
		result["second_num"] = 0;
	}
	else
	{
		if(LotterySecincData["ver"].asInt() != Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER))
		{
			LotterySecincData["id"] = NAT_TURN_TABLE;
			LotterySecincData["firsttotal"] = 0;
			LotterySecincData["first"] = 0;
			LotterySecincData["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER);
			LotterySecincData["second_num"] = 0;
			result["firsttotal"] = 0;
			result["second_num"] = 0;
		}
		else
		{
			result["firsttotal"] = LotterySecincData["firsttotal"].asUInt();
			result["second_num"] = LotterySecincData["second_num"].asUInt();
		}
	}

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	vector <unsigned> id;
	vector <unsigned> type_id;
	vector <unsigned> rate;
	vector <unsigned> eqid;
	vector <unsigned> num;
	vector <unsigned> total;
	unsigned openfloor = 0;
	unsigned cash = 0;
	ret =  pDataXML->GetNewLottery(uid, 2, id, type_id, rate, eqid, num, total, openfloor, cash);
	if(ret)
	{
		error_log("[XMLNewLottery_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	CDataNewlottery *p_newlottery_data= GetNewLotteryData();
	if(p_newlottery_data == NULL)
	{
		DB_ERROR_RETURN_MSG("init_newlottery_data_fail");
	}

	vector <unsigned> get_id;
	vector <unsigned> over_num;
	vector <RareItemsWinner> peoples;
	ret = p_newlottery_data->GetRareItemsNumbers(id, total, get_id, over_num, peoples);
	if(ret)
	{
		error_log("[GetRareItemsNumbers_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	for(int i=0; i<get_id.size(); ++i)
	{
		string type_id = CTrans::ITOS(get_id[i]);
		result["value"][type_id] = over_num[i];
	}

	for(int i=0; i<peoples.size(); ++i)
	{
		result["awards"][i]["eqid"] = peoples[i].eqid;
		result["awards"][i]["num"] = peoples[i].num;
		result["awards"][i]["name"] = peoples[i].name;
		result["awards"][i]["type_id"] = peoples[i].type_id;
		result["awards"][i]["uid"] = peoples[i].uid;
	}

	ret = Secinc.SetOneSecinc(uid, LotterySecincData);
	if(ret)
		return ret;

	return R_SUCCESS;
}

CDataNewlottery* CLogicCMD::GetNewLotteryData()
{
	GET_MEM_DATA_SEM(CDataNewlottery, NEW_LOTTERY_PATH, sem_new_lottery,false)
}

int CLogicCMD::JueXueOneKeyFullLevel(unsigned uid, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)

	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
	{
		return ret;
	}
	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
	{
		return ret;
	}

	result["lasttime"] 	 = dataUser.last_save_time;
	result["lastseq"]	 = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value  tech;
	Json::Reader reader;
	Json::FastWriter writer;
	reader.parse(dataUser.user_tech,tech);

	ret = isJsonNameArrSize(tech, "hecheng", 2);
	int extra_ret = isJsonNameArrSize(tech, "hecheng", 3);
	if (ret && extra_ret)
	{
		DATA_ERROR_RETURN_MSG("hecheng is error");
	}

	unsigned synthid = tech["hecheng"][0u].asUInt();  //合成的id
	if ((0 == synthid) || (XML_JUEXUE_EXP_ID == synthid))
	{
		LOGIC_ERROR_RETURN_MSG("synthid is error");
	}
	unsigned character = synthid % 10;
	//经验品质相关数组。
	unsigned qa_max_exp[5] = {25600, 51200, 102400, 819200, 1228800};
	unsigned int qa_exp[5][12] = {
			{0,100,200,400,800,1600,3200,6400,12800,25600, INT_MAX, INT_MAX},
			{0,200,400,800,1600,3200,6400,12800,25600,51200, INT_MAX, INT_MAX},
			{0,400,800,1600,3200,6400,12800,25600,51200,102400, INT_MAX, INT_MAX},
			{0,800,1600,3200,6400,12800,25600,51200,102400,204800, 409600, 819200},
			{0,1200,2400,4800,9600,19200,38400,76800,153600,307200, 614400, 1228800}
	};

	unsigned max_exp = qa_max_exp[character];
    unsigned exp  = tech["hecheng"][1u].asUInt();
    if(exp >= max_exp)
    {
    	exp = max_exp;
    	DATA_ERROR_RETURN_MSG("exp already max");
    }

    unsigned next_exp = exp;
    //寻找下级经验
    for(int i = 0; i < 12; ++i)
    {
    	if(qa_exp[character][i] > exp)
    	{
    		next_exp = qa_exp[character][i];
    		break;
    	}

    }

	//龙鳞
	unsigned left = 0;
	if(tech.isMember("yinliang"))
	{
		left = tech["yinliang"].asUInt();
	}

	while(exp < next_exp)
	{
		if(PER_EXP_DRAGON_SCALE <= left)
		{
			left -= PER_EXP_DRAGON_SCALE;
			++exp;
		}
		else
		{
			break;
		}
	}


	if(Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
	&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_E_TS))
	{
		if (tech["yinliang"].asUInt() - left < 0)
		{
			error_log("yinliang cost < 0? how could this be possible?");
			return R_ERR_LOGIC;
		}
		unsigned yinliangCost = tech["yinliang"].asUInt() - left;
		Json::Value newAct;
		CLogicSecinc logicSecinc;
		unsigned sid = NAT_LONGLIN;
		ret = logicSecinc.GetSecinc(uid, sid, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
			newAct["getTimes"] = 0;
			newAct["useTimes"] = 0;
			newAct["buyTimes"] = 0;
			newAct["cost"] = 0;
			newAct["need"] = DRAGON_SCALE_COST[1];
			newAct["id"] = sid;
		}
		else if (ret != 0)
		{
			return ret;
		}

		if (Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER) != newAct["ver"].asUInt())
		{
			newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
			newAct["getTimes"] = 0;
			newAct["useTimes"] = 0;
			newAct["buyTimes"] = 0;
			newAct["cost"] = 0;
			newAct["need"] = DRAGON_SCALE_COST[1];
			newAct["id"] = sid;
		}

		unsigned costOld = newAct["cost"].asUInt();
		unsigned costNew = newAct["cost"].asUInt() + yinliangCost;
		unsigned indexOld = 0, indexNew = 0;
		for (; indexOld < DRAGON_SCALE_GET_TIMES; indexOld++)
			if ( costOld >= DRAGON_SCALE_COST[indexOld] &&
					costOld < DRAGON_SCALE_COST[indexOld+1])
				break;
		for (; indexNew < DRAGON_SCALE_GET_TIMES; indexNew++)
			if (costNew >= DRAGON_SCALE_COST[indexNew] &&
					costNew < DRAGON_SCALE_COST[indexNew+1])
				break;
		if (indexNew < DRAGON_SCALE_GET_TIMES)
		{
			newAct["getTimes"] = newAct["getTimes"].asUInt() + indexNew - indexOld;
			newAct["need"] = DRAGON_SCALE_COST[indexNew+1] - costNew;
		}
		else if (indexOld == DRAGON_SCALE_GET_TIMES)
		{
			indexNew = (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			indexOld = (costOld - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			newAct["getTimes"] = newAct["getTimes"].asUInt() + indexNew - indexOld;
			newAct["need"] = DRAGON_SCALE_COST_INVARIANT - (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) % DRAGON_SCALE_COST_INVARIANT;
		}
		else
		{
			unsigned getTime1 = (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			unsigned getTime2 = (DRAGON_SCALE_GET_TIMES - indexOld);
			newAct["getTimes"] = newAct["getTimes"].asUInt() + getTime1 + getTime2;
			newAct["need"] = DRAGON_SCALE_COST_INVARIANT - (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) % DRAGON_SCALE_COST_INVARIANT;
		}

		newAct["cost"] = costNew;
		RESOURCE_LOG("[DragonScale add cost][uid=%u&cost=%u&costChg=%u]",uid,costNew,yinliangCost);
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
			return ret;
		result["newAct"] = Json::Value(Json::arrayValue);
		result["newAct"].resize(0);
		result["newAct"].append(newAct);
	}

	tech["hecheng"][1u] = exp;
	result["hecheng"] 	= tech["hecheng"];
	tech["yinliang"] 	= left;
	result["yinliang"] 	= left;

	string a_update = writer.write(result);

	HERO_LOG("uid=%u,act=%s, after update=%s",
			uid, "FullLevelJueXueOneKey", a_update.c_str());

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}

int CLogicCMD::Juexue(unsigned uid, bool all, Json::Value &result, unsigned &lasttime,unsigned &seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;

	unsigned yinliang = 0, isZhaoHuan = 0, firstXL = 0, curNpcId = 0, size = 0, cost, id, next;
	Json::GetUInt(tech, "yinliang", yinliang);
	Json::GetUInt(tech, "isZhaoHuan", isZhaoHuan);
	Json::GetUInt(tech, "firstXL", firstXL);
	Json::GetUInt(tech, "curNpcId", curNpcId);

	unsigned index = JUEXUE_XIULIAN - 1;
	if(tech.isMember("xiulianlist") && tech["xiulianlist"].isArray())
	{
		for(;(int)index>=0;--index)
		{
			if(tech["xiulianlist"][index][0u].asUInt() != 0)
				break;
		}
		size = JUEXUE_XIULIAN - 1 - index;
		++index;
	}
	else
	{
		size = JUEXUE_XIULIAN;
		tech["xiulianlist"].resize(JUEXUE_XIULIAN);
		for(unsigned i=0;i<JUEXUE_XIULIAN;++i)
		{
			tech["xiulianlist"][i][0u] = 0;
			tech["xiulianlist"][i][1u] = 0;
		}
		index = 0;
	}

	if(curNpcId >= XML_JUEXUE_NPC_NUM)
		curNpcId = 0;
	if(isZhaoHuan && curNpcId != XML_JUEXUE_NPC_NUM-2 && curNpcId != XML_JUEXUE_NPC_NUM-1)
		isZhaoHuan = 0;
	if(size == 0)
		return R_ERR_LOGIC;

	result["npc"].resize(0);
	do
	{
		ret = dataXML->GetJuexue(curNpcId, isZhaoHuan?true:false, dataUser.level, cost, id, next);
		if(ret)
			return ret;

		if(firstXL != 0)
		{
			if(yinliang >= cost)
				yinliang -= cost;
			else
				break;
			RESOURCE_LOG("[Juexue xiulian]uid=%u,yinliang=%u,yinliangchg=%d",uid, yinliang, -cost);
		}
		else
			firstXL = 1;

		if(curNpcId == XML_JUEXUE_NPC_NUM - 1 && isZhaoHuan)
			isZhaoHuan = 0;
		curNpcId = next;
		tech["xiulianlist"][index][0u] = id;
		tech["xiulianlist"][index][1u] = 0;
		HERO_LOG("uid=%u,act=xiulian,curNpcId=%u,isZhaoHuan=%u,juexue_id=%u", uid, curNpcId, isZhaoHuan, id);
		result["npc"].append(curNpcId);

		--size;
		if(size == 0)
			break;
		++index;
		if(next == XML_JUEXUE_NPC_NUM - 1)
			break;
	}
	while(all);

	if(Time::GetGlobalTime() >= Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
	&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_E_TS))
	{
		if (tech["yinliang"].asUInt() - yinliang < 0)
		{
			error_log("yinliang cost < 0? how could this be possible?");
			return R_ERR_LOGIC;
		}
		unsigned yinliangCost = tech["yinliang"].asUInt() - yinliang;
		Json::Value newAct;
		CLogicSecinc logicSecinc;
		unsigned sid = NAT_LONGLIN;
		ret = logicSecinc.GetSecinc(uid, sid, newAct);
		if (ret == R_ERR_NO_DATA)
		{
			newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
			newAct["getTimes"] = 0;
			newAct["useTimes"] = 0;
			newAct["buyTimes"] = 0;
			newAct["cost"] = 0;
			newAct["need"] = DRAGON_SCALE_COST[1];
			newAct["id"] = sid;
		}
		else if (ret != 0)
		{
			return ret;
		}

		if (Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER) != newAct["ver"].asUInt())
		{
			newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
			newAct["getTimes"] = 0;
			newAct["useTimes"] = 0;
			newAct["buyTimes"] = 0;
			newAct["cost"] = 0;
			newAct["need"] = DRAGON_SCALE_COST[1];
			newAct["id"] = sid;
		}

		unsigned costOld = newAct["cost"].asUInt();
		unsigned costNew = newAct["cost"].asUInt() + yinliangCost;
		unsigned indexOld = 0, indexNew = 0;
		for (; indexOld < DRAGON_SCALE_GET_TIMES; indexOld++)
			if ( costOld >= DRAGON_SCALE_COST[indexOld] &&
					costOld < DRAGON_SCALE_COST[indexOld+1])
				break;
		for (; indexNew < DRAGON_SCALE_GET_TIMES; indexNew++)
			if (costNew >= DRAGON_SCALE_COST[indexNew] &&
					costNew < DRAGON_SCALE_COST[indexNew+1])
				break;
		if (indexNew < DRAGON_SCALE_GET_TIMES)
		{
			newAct["getTimes"] = newAct["getTimes"].asUInt() + indexNew - indexOld;
			newAct["need"] = DRAGON_SCALE_COST[indexNew+1] - costNew;
		}
		else if (indexOld == DRAGON_SCALE_GET_TIMES)
		{
			indexNew = (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			indexOld = (costOld - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			newAct["getTimes"] = newAct["getTimes"].asUInt() + indexNew - indexOld;
			newAct["need"] = DRAGON_SCALE_COST_INVARIANT - (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) % DRAGON_SCALE_COST_INVARIANT;
		}
		else
		{
			unsigned getTime1 = (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) / DRAGON_SCALE_COST_INVARIANT;
			unsigned getTime2 = (DRAGON_SCALE_GET_TIMES - indexOld);
			newAct["getTimes"] = newAct["getTimes"].asUInt() + getTime1 + getTime2;
			newAct["need"] = DRAGON_SCALE_COST_INVARIANT - (costNew - DRAGON_SCALE_COST[DRAGON_SCALE_GET_TIMES]) % DRAGON_SCALE_COST_INVARIANT;
		}

		newAct["cost"] = costNew;
		RESOURCE_LOG("[DragonScale add cost][uid=%u&cost=%u&costChg=%u]",uid,costNew,yinliangCost);
		ret = logicSecinc.SetOneSecinc(uid, newAct);
		if (ret)
			return ret;
		result["newAct"] = Json::Value(Json::arrayValue);
		result["newAct"].resize(0);
		result["newAct"].append(newAct);
	}

	result["curNpcId"] = curNpcId;
	tech["curNpcId"] = curNpcId;
	result["isZhaoHuan"] = isZhaoHuan;
	tech["isZhaoHuan"] = isZhaoHuan;
	result["firstXL"] = firstXL;
	tech["firstXL"] = firstXL;
	result["yinliang"] = yinliang;
	tech["yinliang"] = yinliang;
	result["xiulianlist"] = tech["xiulianlist"];

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::SellJuexue(unsigned uid, unsigned type, unsigned isell, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (isell >= JUEXUE_XIULIAN)
	{
		DATA_ERROR_RETURN_MSG("isell is error");
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;

	static const unsigned peryl = 400;
	static const string filed_list = "xiulianlist";
	bool cansell = false;

	ret = isJsonNameArrSize(tech, filed_list, JUEXUE_XIULIAN);
	if (ret)
	{
		DATA_ERROR_RETURN_MSG("xiulianlist is error");
	}

	Json::Value &xllist = tech[filed_list];
	unsigned addyl = 0;

	string bxl = writer.write(xllist);

	if (0 == type)
	{
		unsigned id = xllist[isell][0u].asUInt();
		if (XML_JUEXUE_RUBBISH_ID != id)
		{
			LOGIC_ERROR_RETURN_MSG("id is error");
		}

		cansell = true;
		addyl += peryl;
		xllist[isell][0u] = 0;
		xllist[isell][1u] = 0;
	}
	else if (1 == type)
	{

		for (unsigned i = 0; i < xllist.size(); ++i)
		{
			if (XML_JUEXUE_RUBBISH_ID == xllist[i][0u].asUInt())
			{
				xllist[i][0u] = 0;
				xllist[i][1u] = 0;
				addyl += peryl;
				cansell = true;
			}
		}
	}

	if (false == cansell)
	{
		LOGIC_ERROR_RETURN_MSG("xiulianlist dont have rubbish");
	}

	unsigned zcount = 0;

	ret = adjustJuexueList(xllist, zcount);
	if (ret)
	{
		return ret;
	}

	unsigned yinliang = 0;
	Json::GetUInt(tech, "yinliang", yinliang);

	yinliang += addyl;

	tech["yinliang"] = yinliang;

	result["yinliang"] = yinliang;
	result[filed_list] = xllist;

	dataUser.user_tech = writer.write(tech);

	string axl = writer.write(xllist);

	string act = "SellJuexue";
	HERO_LOG("uid=%u,act=%s,before xllist=%s, after xllist=%s", uid, act.c_str(), bxl.c_str(), axl.c_str());
	RESOURCE_LOG("uid=%u,act=%s, yinliang=%u, addyl=%u", uid, act.c_str(), yinliang, addyl);

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::adjustJuexueList(Json::Value &jxlist, unsigned &zcount)
{
	unsigned i = 0;
	zcount = 0;

	while ((i < jxlist.size()) && (0 != jxlist[i][0u].asUInt()))
	{
		++i;
	}

	if (i == jxlist.size())
	{
		return R_SUCCESS;
	}

	++zcount;

	unsigned j = i + 1;

	for (; i < jxlist.size(); ++i)
	{
		while ((j < jxlist.size()) && (0 == jxlist[j][0u].asUInt()))
		{
			++zcount;
			++j;
		}

		if (j < jxlist.size())
		{
			jxlist[i] = jxlist[j];
			jxlist[j][0u] = 0;
			jxlist[j][1u] = 0;
			jxlist[j][2u] = 0;
			++j;
		}
		else
		{
			break;
		}
	}

	return R_SUCCESS;
}


int CLogicCMD::CollectJuexue(unsigned uid, unsigned type, unsigned icoll, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;

	static const string filed_list = "xiulianlist";
	static const string filed_bag = "baglist";

	ret = isJsonNameArrSize(tech, filed_bag, JUEXUE_BAGLIST);
	if (ret)
	{
		if (tech.isMember(filed_bag))
		{
			tech.removeMember(filed_bag);
		}

		for (unsigned i = 0; i < JUEXUE_BAGLIST; ++i)
		{
			tech[filed_bag][i][0u] = 0;
			tech[filed_bag][i][1u] = 0;
			tech[filed_bag][i][2u] = 0;
		}
	}

	ret = isJsonNameArrSize(tech, filed_list, JUEXUE_XIULIAN);
	if (ret)
	{
		DATA_ERROR_RETURN_MSG("xiulianlist is error");
	}

	Json::Value &baglist = tech[filed_bag];
	Json::Value &xllist = tech[filed_list];
	unsigned zcount = 0;

	ret = adjustJuexueList(baglist, zcount);
	if (ret)
	{
		return ret;
	}

	if (0 == zcount)
	{
		LOGIC_ERROR_RETURN_MSG("baglist dont have space");
	}

	string bxl = writer.write(xllist);
	string bbag = writer.write(baglist);

	if (0 == type)
	{
		unsigned ibag = baglist.size() - zcount;

		if (XML_JUEXUE_RUBBISH_ID == xllist[icoll][0u].asUInt())
		{
			DATA_ERROR_RETURN_MSG("id is rubbish");
		}

		baglist[ibag] = xllist[icoll];
		xllist[icoll][0u] = 0;
		xllist[icoll][1u] = 0;
	}
	else if (1 == type)
	{
		// 将 xllist 复制到 baglist 中
		unsigned i = baglist.size() - zcount;
		for (unsigned j = 0, k = 0; (k < zcount) && (j < xllist.size()); ++j)
		{
			if (0 != xllist[j][0u].asUInt() && (XML_JUEXUE_RUBBISH_ID != xllist[j][0u].asUInt()))
			{
				baglist[i] = xllist[j];
				baglist[i][2u] = 0;

				xllist[j][0u] = 0;
				xllist[j][1u] = 0;
				++i;
				++k;
			}
			else if (0 == xllist[j][0u].asUInt())
			{
				break;
			}
		}
	}

	ret = adjustJuexueList(xllist, zcount);
	if (ret)
	{
		return ret;
	}

	result[filed_bag] = baglist;
	result[filed_list] = xllist;

	string axl = writer.write(xllist);
	string abag = writer.write(baglist);

	HERO_LOG("uid=%u,act=%s,before xllist=%s, after xllist=%s, before bag=%s, after bag=%s",
			uid, "CollectJuexue", bxl.c_str(), axl.c_str(), bbag.c_str(), abag.c_str());

	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::isJsonNameArrSize(const Json::Value &data, const string &name, const unsigned size)
{
	if (!data.isMember(name) || !data[name].isArray() || (size != data[name].size()))
	{
		return R_ERR_DATA;
	}

	return R_SUCCESS;
}

int CLogicCMD::SynthJuexue(unsigned uid, unsigned type, unsigned isynth, unsigned iby, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if ((isynth >= JUEXUE_BAGLIST) || (iby >= JUEXUE_BAGLIST) || (1 == type && isynth == iby))
	{
		return R_ERR_PARAM;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;

	static const string filed_bag = "baglist";  //绝学背包
	static const string filed_he = "hecheng";   //合成的绝学

	ret = isJsonNameArrSize(tech, filed_bag, JUEXUE_BAGLIST);
	if (ret)
	{
		DATA_ERROR_RETURN_MSG("baglist is error");
	}

	Json::Value &baglist = tech[filed_bag];

	string bbag = writer.write(baglist);
	string bhc = "";

	static const unsigned addexp[] = {30, 60, 120, 240, 360};

	unsigned exp = 0;
	unsigned synthqu = 0;
	unsigned qu = 0;
	unsigned id = 0;

	if (0 == type)   //批量合成
	{
		ret = isJsonNameArrSize(tech, filed_he, 2);
		int extra_ret = isJsonNameArrSize(tech, filed_he, 3);

		//合成中的绝学长度可能是3，也可能是2,2是旧数据，长度3是新数据.只有当两个都报错的时候，才是真的错误
		if (ret && extra_ret)
		{
			DATA_ERROR_RETURN_MSG("hecheng is error");
		}

		bhc = writer.write(tech[filed_he]);

		unsigned synthid = tech[filed_he][0u].asUInt();  //合成的id

		if ((0 == synthid) || (XML_JUEXUE_EXP_ID == synthid))
		{
			LOGIC_ERROR_RETURN_MSG("synthid is error");
		}

		synthqu = synthid % 10;
		int synth_break = tech[filed_he][2u].asUInt();  //合成的绝学是否已突破

		exp = tech[filed_he][1u].asUInt();
		int isbreak = 0;

		// 将 baglist中所有都加到 hecheng 中
		for (unsigned i = 0; i < baglist.size(); ++i)
		{
			id = baglist[i][0u].asUInt();
			qu = id % 10;  //品质

			if ((qu <= synthqu) && (0 != id))
			{
				if (XML_JUEXUE_EXP_ID == id)
				{
					exp += JUEXUE_ADD_SEXP;
				}
				else if ((1 == synth_break && 1 == baglist[i][2u].asUInt()) || (1 == isbreak && 1 == baglist[i][2u].asUInt() ))
				{
					//不能吞噬的情况
					//1-合成的绝学本身就是已经突破过的，那么不能再吞噬其他突破过的绝学
					//2-合成的绝学本身没有突破，但是在循环吞噬过程中，已经吞噬过了突破的绝学，那么不能再吞噬接下来的突破过的绝学了。
					continue;
				}
				else
				{
					exp += addexp[qu] + baglist[i][1u].asUInt();
				}

				if (1 == baglist[i][2u].asUInt())
				{
					isbreak = 1;
				}

				baglist[i][0u] = 0;
				baglist[i][1u] = 0;
				baglist[i][2u] = 0;
			}
		}

		tech[filed_he][1u] = exp;

		if (isbreak == 1)
		{
			//一键合成中，有已突破的绝学
			tech[filed_he][2u] = 1;  //不管合成的绝学之前有没有突破，都设置已突破标志
		}
	}
	else if (1 == type)  //单个合成
	{
		// isynth 合成后
		// iby 被合成
		unsigned synthid = baglist[isynth][0u].asUInt();
		id = baglist[iby][0u].asUInt();

		if ((0 == synthid) || (0 == id)
				|| (XML_JUEXUE_EXP_ID == synthid && id == synthid))
		{
			LOGIC_ERROR_RETURN_MSG("isynth or iby is error");
		}

		unsigned risynth = isynth;
		unsigned riby = iby;

		// 特殊处理万物生长
		if (XML_JUEXUE_EXP_ID == synthid)  //主动合成的一方是万物生长时，则调换合成的主动方和被动方
		{
			risynth = iby;
			riby = isynth;
		}

		synthid = baglist[risynth][0u].asUInt(); //主动
		synthqu = synthid % 10;
		int synth_break = baglist[risynth][2u].asUInt();  //合成的绝学是否已突破

		id = baglist[riby][0u].asUInt();
		qu = id % 10;

		if (synthqu < qu)
		{
			LOGIC_ERROR_RETURN_MSG("qu greater synthqu");
		}

		if (1 == synth_break && 1 == baglist[riby][2u].asUInt())
		{
			LOGIC_ERROR_RETURN_MSG("two breakthrough's forbidden synth");
		}

		exp = baglist[risynth][1u].asUInt();
		exp += baglist[riby][1u].asUInt();

		if (XML_JUEXUE_EXP_ID == id)
		{
			exp += JUEXUE_ADD_SEXP;
		}
		else
		{
			exp += addexp[qu];
		}

		baglist[isynth][1u] = synthid;  //主动
		baglist[isynth][1u] = exp;

		if (baglist[isynth].size() <= 2 || baglist[isynth][2u].asUInt() == 0)
		{
			baglist[isynth][2u] = baglist[iby][2u].asUInt();
		}

		baglist[iby][0u] = 0;
		baglist[iby][1u] = 0;
		baglist[iby][2u] = 0;  //被动
	}

	unsigned zcount;
	ret = adjustJuexueList(baglist, zcount);
	if (ret)
	{
		return ret;
	}

	result[filed_bag] = tech[filed_bag];
	result[filed_he] = tech[filed_he];

	string abag = writer.write(baglist);
	string ahec = writer.write(tech[filed_he]);

	HERO_LOG("uid=%u,act=%s,before hecheng=%s, after hecheng=%s, before bag=%s, after bag=%s",
			uid, "SynthJuexue", bhc.c_str(), ahec.c_str(), bbag.c_str(), abag.c_str());

	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::checkHeroId(Json::Value &herojx, unsigned id, unsigned ihero)
{
	id /= 10;
	// 判断 hero中是否已有同类
	for (unsigned i = 0; i < herojx.size(); ++i)
	{
		if ((i != ihero) && id == (herojx[i]["id"].asUInt() / 10))
		{
			LOGIC_ERROR_RETURN_MSG("hero jx already exist this juexue");
		}
	}

	return R_SUCCESS;
}


int CLogicCMD::LoadJuexue(unsigned uid, unsigned type, unsigned heroud, unsigned ihero, unsigned ibag, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if (ibag >= JUEXUE_BAGLIST)
	{
		return R_ERR_PARAM;
	}

	//装备绝学
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	reader.parse(dataUser.user_tech,tech);
	Json::FastWriter writer;

	static const string filed_bag = "baglist";
	static const string filed_jx = "juexue";

	CLogicHero logicHero;
	Json::Value hero;

	ret = logicHero.Get(uid, heroud, hero);
	if (ret)
	{
		return ret;
	}

	string shid = "";

	if (!Json::GetString(hero, "id", shid))
	{
		error_log("[target hid or star error], uid=%u", uid);
		return R_ERR_DATA;
	}

	string bjx = writer.write(hero[filed_jx]);  //装备绝学之前，英雄身上的绝学，用于日志记录
	string bbag = writer.write(tech[filed_bag]);  //装备绝学之前，绝学背包内的绝学，用于日志记录

	string stype = "swap";  //类型2交换

	// load
	if (0 == type)
	{
		ret = isJsonNameArrSize(tech, filed_bag, JUEXUE_BAGLIST);
		if (ret)
		{
			DATA_ERROR_RETURN_MSG("baglist is error");
		}

		if (!hero.isMember(filed_jx) || !hero[filed_jx].isArray())
		{
			if (hero.isMember(filed_jx))
			{
				hero.removeMember(filed_jx);
			}
			hero[filed_jx] = Json::Value(Json::arrayValue);
		}

		ihero = hero[filed_jx].size();
		if (ihero > 9)
		{
			LOGIC_ERROR_RETURN_MSG("ihero greater 9");
		}

		//装备时，ihero参数为0，ibag不为0
		hero[filed_jx][ihero]["id"] = 0;
		hero[filed_jx][ihero]["exp"] = 0;
		stype = "load";
	}
	// unload
	else if (1 == type)
	{
		ret = isJsonNameArrSize(tech, filed_bag, JUEXUE_BAGLIST);
		if (ret)
		{
			DATA_ERROR_RETURN_MSG("baglist is error");
		}

		if (!hero.isMember(filed_jx) || !hero[filed_jx].isArray())
		{
			DATA_ERROR_RETURN_MSG("hero juexue is error");
		}

		if (ihero > hero[filed_jx].size())
		{
			LOGIC_ERROR_RETURN_MSG("ihero greater hero juexue");
		}

		unsigned zcount;
		ret = adjustJuexueList(tech[filed_bag], zcount);
		if (ret)
		{
			return ret;
		}

		//卸下时，参数ihero不为0，参数ibag为0
		ibag = tech[filed_bag].size() - zcount;

		if (ibag >= tech[filed_bag].size())
		{
			LOGIC_ERROR_RETURN_MSG("baglist dont have space");
		}

		stype="unload";
	}

	//同一个函数，包含了三种功能，装备、卸载、交换。不符合整洁代码规范
	//绝学背包里面的绝学
	unsigned int bag_id = tech[filed_bag][ibag][0u].asUInt();   //绝学背包中的绝学id
	unsigned int bag_exp = tech[filed_bag][ibag][1u].asUInt();
	unsigned int bag_break = tech[filed_bag][ibag][2u].asUInt();   //突破标志位

	//英雄身上的绝学
	unsigned int hero_juexue_id = hero[filed_jx][ihero]["id"].asUInt(); //英雄穿戴的绝学id
	unsigned int hero_juexue_exp = hero[filed_jx][ihero]["exp"].asUInt();
	unsigned int hero_juexue_break = hero[filed_jx][ihero]["break"].asUInt(); //突破标志位

	//还不单是这样，当操作的是万物生长时，又有吞噬功能
	if (XML_JUEXUE_EXP_ID == bag_id)
	{
		if (0 == hero_juexue_id)
		{
			LOGIC_ERROR_RETURN_MSG("load jx id is exp id");
		}

		if (0 == type)
		{
			bag_exp = hero_juexue_exp + JUEXUE_ADD_SEXP;
			hero_juexue_id = 0;
			hero_juexue_exp = 0;
		}
		else if (1 == type)
		{
			hero_juexue_exp += JUEXUE_ADD_SEXP;
			bag_id = 0;
			bag_exp = 0;
		}
	}
	else if (1 != type)
	{
		//检查英雄身上是否已穿戴同类绝学
		ret = checkHeroId(hero[filed_jx], bag_id, ihero);
		if (ret)
		{
			return ret;
		}
	}

	tech[filed_bag][ibag][0u] = hero_juexue_id;
	tech[filed_bag][ibag][1u] = hero_juexue_exp;
	tech[filed_bag][ibag][2u] = hero_juexue_break;

	hero[filed_jx][ihero]["id"] = bag_id;  //英雄同等部位的绝学，替换成了绝学背包中的绝学
	hero[filed_jx][ihero]["exp"] = bag_exp;
	hero[filed_jx][ihero]["break"] = bag_break;

	unsigned zcount;
	ret = adjustJuexueList(tech[filed_bag], zcount);
	if (ret)
	{
		return ret;
	}

	// hero[filed_jx] 中有id == 0
	if (0 == bag_id)
	{
		unsigned hsz = hero[filed_jx].size() - 1;
		hero[filed_jx][ihero]["id"] = hero[filed_jx][hsz]["id"];
		hero[filed_jx][ihero]["exp"] = hero[filed_jx][hsz]["exp"];
		hero[filed_jx][ihero]["break"] = hero[filed_jx][hsz]["break"];

		hero[filed_jx].resize(hsz);
	}

	ret = logicHero.Chg(uid, heroud, hero);
	if (ret)
	{
		return ret;
	}

	result[filed_bag] = tech[filed_bag];
	result[filed_jx] = hero[filed_jx];

	dataUser.user_tech = writer.write(tech);

	string ajx = writer.write(hero[filed_jx]);
	string abag = writer.write(tech[filed_bag]);

	HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s,type=%s,before data=%s after data=%s,"
			"before bag=%s after bag=%s", uid, heroud, shid.c_str(),
			"LoadJuexue", stype.c_str(), bjx.c_str(), ajx.c_str(), bbag.c_str(), abag.c_str());

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::LoadSynth(unsigned uid, unsigned type, unsigned index, unsigned heroud, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter writer;

	reader.parse(dataUser.user_tech, tech);

	static const string filed_bag = "baglist";
	static const string filed_jx = "juexue";
	static const string filed_hc = "hecheng";

	//设置合成的绝学，来源有两种：绝学背包，英雄
	ret = isJsonNameArrSize(tech, filed_hc, 3);
	if (ret)
	{
		if (tech.isMember(filed_hc) && !tech[filed_hc].isArray())
		{
			//存在该字段，但是该字段类型不是数组，那么删除
			tech.removeMember(filed_hc);
		}

		int startlen = 0;

		if (tech.isMember(filed_hc))
		{
			//包含该字段，且之前是数组,则长度不够，因为后面扩展了数组长度
			startlen = tech[filed_hc].size();
		}

		for (unsigned i = startlen; i < 3; ++i)
		{
			tech[filed_hc][i] = 0;
		}
	}

	string before_bag = writer.write(tech[filed_bag]);
	string before_hc = writer.write(tech[filed_hc]);
	string bjx = "";
	string shid = "";
	string ajx = "";

	unsigned juexue_id = 0;
	unsigned juexue_exp = 0;
	unsigned juexue_break = 0;

	//旧合成框中的绝学
	unsigned hc_juexue_id = tech[filed_hc][0u].asUInt();
	unsigned hc_juexue_exp = tech[filed_hc][1u].asUInt();
	unsigned hc_juexue_break = tech[filed_hc][2u].asUInt();

	// hero
	if (0 == type)
	{
		CLogicHero logicHero;
		Json::Value hero;

		ret = logicHero.Get(uid, heroud, hero);
		if (ret)
		{
			return ret;
		}

		if (!Json::GetString(hero, "id", shid))
		{
			error_log("[target hid or star error], uid=%u", uid);
			return R_ERR_DATA;
		}

		bjx = writer.write(hero[filed_jx]);
		unsigned hero_juexue_size = hero[filed_jx].size();  //英雄装备的绝学长度

		if (index > 9)
		{
			LOGIC_ERROR_RETURN_MSG("index greater hero jx size");
		}

		index = index > hero_juexue_size ? hero_juexue_size : index;

		juexue_id = hero[filed_jx][index]["id"].asUInt();
		juexue_exp = hero[filed_jx][index]["exp"].asUInt();
		juexue_break = hero[filed_jx][index]["break"].asUInt();

		hero[filed_jx][index]["id"] = hc_juexue_id;
		hero[filed_jx][index]["exp"] = hc_juexue_exp;
		hero[filed_jx][index]["break"] = hc_juexue_break;

		if (XML_JUEXUE_EXP_ID == hc_juexue_id)
		{
			LOGIC_ERROR_RETURN_MSG("hcid is exp id");
		}

		if (0 == hc_juexue_id)   //旧的合成框不存在绝学，则要修改英雄中的绝学长度
		{
			if (hero_juexue_size > 0)
			{
				hero_juexue_size--;
				hero[filed_jx][index]["id"] = hero[filed_jx][hero_juexue_size]["id"];
				hero[filed_jx][index]["exp"] = hero[filed_jx][hero_juexue_size]["exp"];
				hero[filed_jx][index]["break"] = hero[filed_jx][hero_juexue_size]["break"];

				hero[filed_jx].resize(hero_juexue_size);
			}
		}
		else
		{
			ret = checkHeroId(hero[filed_jx], hc_juexue_id, index);
			if (ret)
			{
				return ret;
			}
		}

		ret = logicHero.Chg(uid, heroud, hero);
		if (ret)
		{
			return ret;
		}

		ajx = writer.write(hero[filed_jx]);
		result[filed_jx] = hero[filed_jx];
	}
	// baglist
	else
	{
		if (index >= tech[filed_bag].size())
		{
			LOGIC_ERROR_RETURN_MSG("index greater baglist size");
		}

		juexue_id = tech[filed_bag][index][0u].asUInt();
		juexue_exp = tech[filed_bag][index][1u].asUInt();
		juexue_break = tech[filed_bag][index][2u].asUInt();

		if (XML_JUEXUE_EXP_ID == juexue_id)
		{
			if (2 == type)
			{
				juexue_id = hc_juexue_id;
				juexue_exp = hc_juexue_exp + JUEXUE_ADD_SEXP;
				hc_juexue_id = 0;
				hc_juexue_exp = 0;
				hc_juexue_break = 0;
			}
			else if (3 == type)
			{
				hc_juexue_exp += JUEXUE_ADD_SEXP;
				juexue_id = 0;
				juexue_exp = 0;
				juexue_break = 0;
			}
		}

		tech[filed_bag][index][0u] = hc_juexue_id;
		tech[filed_bag][index][1u] = hc_juexue_exp;
		tech[filed_bag][index][2u] = hc_juexue_break;

		result[filed_bag] = tech[filed_bag];

		unsigned zcount;
		ret = adjustJuexueList(tech[filed_bag], zcount);
		if (ret)
		{
			return ret;
		}
	}

	tech[filed_hc][0u] = juexue_id;
	tech[filed_hc][1u] = juexue_exp;
	tech[filed_hc][2u] = juexue_break;

	result[filed_hc] = tech[filed_hc];

	string abag = writer.write(tech[filed_bag]);
	string ahc = writer.write(tech[filed_hc]);

	string act = "LoadSynth";

	if (0 == type)
	{
		HERO_LOG("uid=%u,id=%u,heroid=%s,act=%s, before hecheng=%s, after hecheng=%s, before hjx = %s, after hjx = %s",
				uid, heroud, shid.c_str(), act.c_str(), before_hc.c_str(), ahc.c_str(), bjx.c_str(), ajx.c_str());
	}
	else
	{
		HERO_LOG("uid=%u,act=%s,before hecheng=%s, after hecheng=%s, before bag=%s, after bag=%s,",
				uid, act.c_str(), before_hc.c_str(), ahc.c_str(), before_bag.c_str(), abag.c_str());
	}

	dataUser.user_tech = writer.write(tech);

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicCMD::QixiChoujiangActivity(unsigned uid, unsigned count, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS))
	{
		error_log("activity_qixi_choujiang_time_error");
		return R_ERR_REFUSE;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	CLogicSecinc Secinc;
	Json::Value SecincData;
	ret = Secinc.GetSecinc(uid, NAT_CHOUJIANG, SecincData);
	if(ret!=0 && ret!=R_ERR_NO_DATA)
	{
		return ret;
	}

	if(!SecincData.isMember("id"))
	{
		SecincData["id"] = NAT_CHOUJIANG;
		SecincData["count"] = count;
		SecincData["ver"] = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION);
	}
	else
	{
		if(!SecincData.isMember("ver") || SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION))
		{
			SecincData["count"] = count;
			SecincData["ver"] = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION);
		}
		else
			SecincData["count"] = SecincData["count"].asUInt() + count;
	}
	if(!SecincData.isMember("fts") || !SecincData.isMember("fc") || !Time::IsToday(SecincData["fts"].asUInt()))
	{
		SecincData["fc"] = NAT_CHOUJIANG_FREE_NUM;
		SecincData["fts"] = Time::GetGlobalTime();
	}

	unsigned fc = SecincData["fc"].asUInt();
	vector <unsigned> type_id;
	vector <unsigned> rate;
	vector <unsigned> eqid;
	vector <unsigned> num;
	vector <unsigned> index_id;

	CDataQixijie *p_choujiang= CLogicQixijie::GetQixijieData();
	if(p_choujiang == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixijie_data_fail");
	}

	vector <unsigned> awards_index_id;
	vector <unsigned> awards_type_id;
	vector <unsigned> awards_eqid;
	vector <unsigned> awards_num;
	unsigned integral = SecincData["count"].asUInt() * 10;

	ret = p_choujiang->QixiChoujiang(uid, count, integral, awards_index_id, awards_type_id, awards_eqid, awards_num, result);
	if(ret)
	{
		error_log("[qixi_choujiang_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	vector<ItemAdd> equip_items;
	vector<string> hero_id;
	vector<string> hero_code;
	for(int i=0; i<awards_index_id.size(); ++i)
	{
		if(awards_type_id[i]==2)	//抽到英雄
		{
			string code = "activity_qixichoujiang";
			hero_id.push_back(CDataXML::Hero2Str(awards_eqid[i]));
			hero_code.push_back(code);
		}
		else
		{
			ItemAdd eqip;
			eqip.eqid = awards_eqid[i];
			eqip.count = awards_num[i];
			eqip.q = 0;
			eqip.ch = 0;
			eqip.reason = "activity_qixichoujiang";
			equip_items.push_back(eqip);
		}
		result["id"][i] = awards_index_id[i];
	}

	if(count > fc)
	{
		count -= fc;
		fc = 0;

		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);

		CLogicPay logicPay;
		DataPay payData;
		unsigned cost_cash = 20 * count;
#ifdef SG_USE_CASH
		ret = logicPay.ProcessOrderForBackend(uid, -cost_cash, 0, payData, "activity_qixi_choujiang",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
#else
		CLogicEquipment equipment;
		ret = equipment.UseEquipment(uid, purple_key, equd, cost_cash/5, "QixiChoujiangActivity");
		if(ret)
			return ret;
#endif
	}
	else
		fc -= count;
	SecincData["fc"] = fc;

	if(equip_items.size() > 0)
	{
		CLogicEquipment Equip;
		ret = Equip.AddItems(uid,equip_items,result["add_equip"], true);
		if(ret)
		{
			error_log("[Add_Equip_error][uid=%u]", uid);
			return ret;
		}
	}

	if(hero_id.size() > 0)
	{
		CLogicHero Hero;
		ret = Hero.AddHeros(uid,hero_id,hero_code,result["hero"]);
		if(ret)
		{
			error_log("[Add_hero_error][uid=%u]", uid);
			return ret;
		}
	}

	ret = Secinc.SetOneSecinc(uid, SecincData);
	if(ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}


int CLogicCMD::GetJianglingGrow(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_tech;
	reader.parse(dataUser.user_tech,user_tech);

	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned grow_value = user_tech["sgrowth"].asUInt();
	if(grow_value < 600)
		grow_value += 600;
	unsigned j_exp = user_tech["soul"].asUInt() * 40;
	if(j_exp < 50
	|| (grow_value>=780 && j_exp < 5057)
	|| (grow_value>=960 && j_exp < 20097)
	|| (grow_value>=1516 && j_exp < 45134)
	|| (grow_value>=3476 && j_exp < 80169)
	)
	{
		error_log("jiangling_level_low,exp=%u",j_exp);
		return R_ERR_REFUSE;
	}
	unsigned growth_id = 0;
	unsigned prosper = 0;

	ret = dataXML->GetJianglingGrow(uid, grow_value, growth_id, prosper);
	if(ret)
		return ret;

	int temp = dataUser.prosper - prosper;
	if(prosper < 0)
	{
		error_log("[jianglingchengzhang_Lack_prosper] [uid=%u,needprosper=%u,peopleprosper=%u]", uid, prosper, dataUser.prosper);
		return R_ERR_DATA;
	}
	result["prosper"] = dataUser.prosper = temp;

	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret)
		return ret;

	for(int i=0; i<equip_data.size(); ++i)
	{
		if(equip_data[i]["id"].asUInt() == growth_id)
		{
			string reason = "Jiangling_chengzhang";
			equip_data[i]["count"] = equip_data[i]["count"].asUInt() - 1;
			ret = logicEquip.UseEquipment(uid, growth_id, equip_data[i]["ud"].asUInt(), 1, reason);
			if(ret)
				return ret;
			result["use_grow"] = equip_data[i];
			break;
		}
	}

	result["sgrowth"] = grow_value;
	user_tech["sgrowth"] = grow_value;
	dataUser.user_tech = writer.write(user_tech);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	RESOURCE_LOG("[JianglingChengzhang][uid=%u,chgprosper=%u,prosper=%u,chglonglin=%u,longlin=%u,chgr1=%u,r1=%u,chgr2=%u,r2=%u,chgr3=%u,r3=%u,chgr4=%u,r4=%u]"
					,uid,prosper,dataUser.prosper,0,0,0,0,0,0,0,0,0);

	return R_SUCCESS;
}


int CLogicCMD::GetJianglingSkillsDraw(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_tech;
	reader.parse(dataUser.user_tech,user_tech);

	if(!user_tech.isMember("sfc") || !user_tech.isMember("sbc") || !user_tech.isMember("sexp"))
	{
		DATA_ERROR_RETURN_MSG("skill_json_error");
	}

	unsigned sfc = user_tech["sfc"].asUInt();
	unsigned sbc = user_tech["sbc"].asUInt();

	unsigned rate_1 = Math::GetRandomInt(6);
	unsigned rate_2 = Math::GetRandomInt(6);
	unsigned rate_3 = Math::GetRandomInt(6);

	if(sfc > 0)
	{
		user_tech["sfc"] = sfc - 1;
	}
	else if(sbc > 0)
	{
		user_tech["sbc"] = sbc - 1;
	}
	else
	{
		DATA_ERROR_RETURN_MSG("draw_often_enough");
	}

	if(rate_1 == rate_2 && rate_1 == rate_3 && rate_2 == rate_3)
	{
		user_tech["sexp"][rate_1] = user_tech["sexp"][rate_1].asUInt() + JIANGLING_SKILL * 6;
	}
	else
	{
		user_tech["sexp"][rate_1] = user_tech["sexp"][rate_1].asUInt() + JIANGLING_SKILL;
		user_tech["sexp"][rate_2] = user_tech["sexp"][rate_2].asUInt() + JIANGLING_SKILL;
		user_tech["sexp"][rate_3] = user_tech["sexp"][rate_3].asUInt() + JIANGLING_SKILL;
	}

	result["r1"] = rate_1;
	result["r2"] = rate_2;
	result["r3"] = rate_3;
	result["sfc"] = user_tech["sfc"];
	result["sbc"] = user_tech["sbc"];
	result["sexp"] = user_tech["sexp"];

	dataUser.user_tech = writer.write(user_tech);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	return R_SUCCESS;
}

int CLogicCMD::DragonScaleActivity(unsigned uid, unsigned type, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_E_TS))
	{
		error_log("activity_dragon_scale_time_error");
		return R_ERR_REFUSE;
	}

	// type 0:消耗钻石 1:消耗次数
	if (type > 1)
	{
		error_log("activity_dragon_sacle_type_error");
		return R_ERR_PARAM;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	unsigned sid = NAT_LONGLIN;
	ret = logicSecinc.GetSecinc(uid, sid, newAct);

	if (ret == R_ERR_NO_DATA)
	{
		newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
		newAct["getTimes"] = 0;
		newAct["useTimes"] = 0;
		newAct["buyTimes"] = 0;
		newAct["cost"] = 0;
		newAct["need"] = DRAGON_SCALE_COST[1];
		newAct["id"] = sid;
	}
	else if (ret)
	{
		return ret;
	}

	if (Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER) != newAct["ver"].asUInt())
	{
		newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
		newAct["getTimes"] = 0;
		newAct["useTimes"] = 0;
		newAct["buyTimes"] = 0;
		newAct["cost"] = 0;
		newAct["need"] = DRAGON_SCALE_COST[1];
		newAct["id"] = sid;
	}

	if (type == 0)
	{
		int cost = 0;
		unsigned buyTimes = newAct["buyTimes"].asInt();

		if (buyTimes < DRAGON_SCALE_DIAMOND_GET_TIMES)
		{
			cost = DRAGON_SCALE_COST_DIAMOND[buyTimes];
		}
		else
		{
			cost = DRAGON_SCALE_COST_DIAMOND_INVARIANT;
		}

		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);

		CLogicPay logicPay;
		DataPay payData;

	#ifdef SG_USE_CASH
		ret = logicPay.ProcessOrderForBackend(uid, cost * -1, 0, payData, "dragon_scale_activity",user_flag,bsave);
		result["coins"] = payData.coins;
		result["coins2"] = payData.cash;
	#else
		CLogicEquipment equipment;
		ret = equipment.UseEquipment(uid, blue_key, equd, cost, "dragon_scale_activity");
	#endif

		if(ret)
			return ret;

		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}

		//购买一次抽奖机会
		newAct["getTimes"] = newAct["getTimes"].asUInt()+1;
	}
	else if (type == 1 && (newAct["getTimes"].asInt() <= 0 || newAct["getTimes"].asInt() <= newAct["useTimes"].asInt()))
	{
		error_log("[dragonScale getTimes not enough][uid=%u,count=%d]", uid, newAct["getTimes"].asInt());
		DB_ERROR_RETURN_MSG("newAct error");
	}

	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter write;
	reader.parse(dataUser.user_tech,tech);
	unsigned yinliang = 0;
	Json::GetUInt(tech, "yinliang", yinliang);

	//抽取龙鳞
	int rate = Math::GetRandomInt(1000);
	unsigned index = 0;
	for(;index<8;++index)
	{
		if(rate < DRAGON_SCALE_RATE[index])
		{
			yinliang += DRAGON_SCALE_GET[index];
			break;
		}
	}
	result["lotteryId"] = index;

	//10,20,30···次发送额外奖励
	if ((newAct["useTimes"].asUInt()+1) >= 10 &&
			(newAct["useTimes"].asUInt()+1) % 10 == 0)
	{
		rate = Math::GetRandomInt(100);
		if (rate < DRAGON_SCALE_EXTRA_RATE[0])
		{
			//奖励一次转盘数
			newAct["getTimes"] = newAct["getTimes"].asUInt()+1;
			result["extraAwardId"] = 0;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[1])
		{
			//奖励绝学令
			unsigned itemId = DRAGON_SCALE_EXTRA_ITEM_ID[1];
			CLogicEquipment logicEquipment;
			ret = logicEquipment.AddOneItem(uid, itemId, 1, "dragonScaleActivty", result["equipExtra"], true);
			if (ret)
				return ret;
			result["extraAwardId"] = 1;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[2])
		{

			//奖励五虎重置令
			unsigned itemId = DRAGON_SCALE_EXTRA_ITEM_ID[0];
			CLogicEquipment logicEquipment;
			ret = logicEquipment.AddOneItem(uid, itemId, 1, "dragonScaleActivty", result["equipExtra"], true);
			if (ret)
				return ret;
			result["extraAwardId"] = 2;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[3])
		{
			//奖励龙鳞
			yinliang += DRAGON_SCALE_EXTRA_AWARD_NUM;
			result["extraAwardId"] = 3;
		}
	}

	//抽取全区共享礼包
	CDataDragonScaleGiftBag *pData = GetDragonScaleData();
	if(pData == NULL)
	{
		DB_ERROR_RETURN_MSG("init_dragonScale_data_fail");
	}
	bool succ = false;
	int count = 0;
	Json::Value winners;
	ret = pData->GetGiftBag(uid, winners, count, succ);
	if(ret)
	{
		error_log("[GetRareItemsNumbers_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}
	if (succ)
	{
		CLogicEquipment logicEquipment;
		ret = logicEquipment.AddOneItem(uid, DRAGON_SCALE_ACTIVITY_SHARE_GIFT_ID, 1, "dragonScaleActivty", result["equipGiftBag"], true);
		if (ret)
			return ret;
	}
	result["giftBagSucc"] = succ?1:0;
	result["giftBagCount"] = count;
	result["giftBagWinners"] = winners;

	newAct["useTimes"] = newAct["useTimes"].asUInt() + 1;
	if (type == 0)
	{
		newAct["buyTimes"] = newAct["buyTimes"].asUInt() + 1;
	}
	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(newAct);
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
		return ret;

	RESOURCE_LOG("[DragonScale draw][uid=%u&yiliang=%u&yiliangChg=%u]",uid,yinliang,yinliang-tech["yinliang"].asUInt());
	result["yinliang"] = yinliang;
	tech["yinliang"] = yinliang;
	dataUser.user_tech = write.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::DragonScaleTensActivity(unsigned uid, unsigned type, unsigned equd, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_E_TS))
	{
		error_log("activity_dragon_scale_time_error");
		return R_ERR_REFUSE;
	}

	//十次龙鳞转盘转动，只适用于道具消耗，或者说是钻石消耗
	if (type != 0)
	{
		error_log("activity_dragon_sacle_type_error");
		return R_ERR_PARAM;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)

	ret = logicUser.GetUser(uid,dataUser);

	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);

	if(ret)
		return ret;

	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	unsigned sid = NAT_LONGLIN;
	ret = logicSecinc.GetSecinc(uid, sid, newAct);

	const int TEN_TIMES = 50;

	if (ret == R_ERR_NO_DATA)
	{
		newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
		newAct["getTimes"] = 0;
		newAct["useTimes"] = 0;
		newAct["buyTimes"] = 0;
		newAct["cost"] = 0;
		newAct["need"] = DRAGON_SCALE_COST[1];
		newAct["id"] = sid;
	}
	else if (ret)
	{
		return ret;
	}

	int cost = 0;

	unsigned buyTimes = newAct["buyTimes"].asInt();

	if (buyTimes < DRAGON_SCALE_DIAMOND_GET_TIMES)
	{
		int diff = DRAGON_SCALE_DIAMOND_GET_TIMES - buyTimes;

		for(int i = 0; i < diff; ++i)
		{
			cost += DRAGON_SCALE_COST_DIAMOND[i + buyTimes];
		}

		cost += DRAGON_SCALE_COST_DIAMOND_INVARIANT * (TEN_TIMES - diff);
	}
	else
	{
		cost = DRAGON_SCALE_COST_DIAMOND_INVARIANT * TEN_TIMES;
	}

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);

	CLogicPay logicPay;
	DataPay payData;

#ifdef SG_USE_CASH
	ret = logicPay.ProcessOrderForBackend(uid, cost * -1, 0, payData, "dragon_scale_activity",user_flag,bsave);
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;
#else
	CLogicEquipment equipment;
	ret = equipment.UseEquipment(uid, blue_key, equd, cost, "dragon_scale_activity");
#endif

	if(ret)
		return ret;

	result["pointpay"].resize(0);

	if(bsave)
	{
		result["pointpay"] = user_flag["user_pay"];
		dataUser.user_flag = writer.write(user_flag);
	}

	//购买一次抽奖机会
	newAct["getTimes"] = newAct["getTimes"].asUInt() + TEN_TIMES;

	Json::Value tech;

	reader.parse(dataUser.user_tech,tech);
	unsigned yinliang = 0;
	Json::GetUInt(tech, "yinliang", yinliang);

	unsigned oldyinliang = yinliang;

	//进行十次龙鳞转盘的转动
	for(int i = 0; i < TEN_TIMES; ++i)
	{
		RollDragonTable(uid, newAct, result, yinliang);
	}

	newAct["buyTimes"] = newAct["buyTimes"].asUInt() + TEN_TIMES;

	ret = logicSecinc.SetOneSecinc(uid, newAct);

	if (ret)
		return ret;

	result["newAct"] = newAct;
	tech["yinliang"] = yinliang;

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);

	if (ret)
		return ret;

	RESOURCE_LOG("[DragonScale draw][uid=%u&yiliang=%u&yiliangChg=%u]",uid, yinliang, yinliang - oldyinliang);
	result["yinliang"] = yinliang;

	return R_SUCCESS;
}
int CLogicCMD::DragonScaleAllFree(unsigned uid, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_E_TS))
	{
		error_log("activity_dragon_scale_time_error");
		return R_ERR_REFUSE;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}
	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);

	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	unsigned sid = NAT_LONGLIN;
	ret = logicSecinc.GetSecinc(uid, sid, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["ver"] = Config::GetIntValue(CONFIG_ACTIVITY_DRAGON_SCALE_VER);
		newAct["getTimes"] = 0;
		newAct["useTimes"] = 0;
		newAct["buyTimes"] = 0;
		newAct["cost"] = 0;
		newAct["need"] = DRAGON_SCALE_COST[1];
		newAct["id"] = sid;
	}
	else if (ret)
		return ret;

	unsigned getTimes = newAct["getTimes"].asInt();
	unsigned useTimes = newAct["useTimes"].asInt();
	if(getTimes <= useTimes)
		return R_ERR_LOGIC;
	unsigned c = min(100u, getTimes - useTimes);

	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value tech;
	reader.parse(dataUser.user_tech,tech);
	unsigned yinliang = 0;
	Json::GetUInt(tech, "yinliang", yinliang);
	unsigned oldyinliang = yinliang;

	for(int i = 0; i < c; ++i)
		RollDragonTable(uid, newAct, result, yinliang);

	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
		return ret;
	result["newAct"] = newAct;
	tech["yinliang"] = yinliang;

	dataUser.user_tech = writer.write(tech);
	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;

	RESOURCE_LOG("[DragonScale draw][uid=%u&yiliang=%u&yiliangChg=%u]",uid, yinliang, yinliang - oldyinliang);
	result["yinliang"] = yinliang;

	return R_SUCCESS;
}

int CLogicCMD::RollDragonTable(unsigned uid, Json::Value & newAct, Json::Value & result, unsigned & yinliang)
{
	//抽取龙鳞
	int rate = Math::GetRandomInt(1000);
	unsigned index = 0;

	for(; index < 8;++index)
	{
		if(rate < DRAGON_SCALE_RATE[index])
		{
			yinliang += DRAGON_SCALE_GET[index];
			break;
		}
	}

	if (!result.isMember("lotteryId"))
	{
		result["lotteryId"] = Json::arrayValue;
	}

	result["lotteryId"].append(index);

	int ret = 0;

	//10,20,30···次发送额外奖励
	if ((newAct["useTimes"].asUInt() + 1) >= 10 &&
			(newAct["useTimes"].asUInt() + 1) % 10 == 0)
	{
		rate = Math::GetRandomInt(100);

		if (rate < DRAGON_SCALE_EXTRA_RATE[0])
		{
			//奖励一次转盘数
			newAct["getTimes"] = newAct["getTimes"].asUInt() + 1;
			result["extraAwardId"] = 0;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[1])
		{
			//奖励绝学令
			unsigned itemId = DRAGON_SCALE_EXTRA_ITEM_ID[1];
			CLogicEquipment logicEquipment;
			ret = logicEquipment.AddOneItem(uid, itemId, 1, "dragonScaleActivty", result["equipExtra"], true);

			if (ret)
				return ret;

			result["extraAwardId"] = 1;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[2])
		{
			//奖励五虎重置令
			unsigned itemId = DRAGON_SCALE_EXTRA_ITEM_ID[0];
			CLogicEquipment logicEquipment;
			ret = logicEquipment.AddOneItem(uid, itemId, 1, "dragonScaleActivty", result["equipExtra"], true);

			if (ret)
				return ret;

			result["extraAwardId"] = 2;
		}
		else if (rate < DRAGON_SCALE_EXTRA_RATE[3])
		{
			//奖励龙鳞
			yinliang += DRAGON_SCALE_EXTRA_AWARD_NUM;
			result["extraAwardId"] = 3;
		}
	}

	//抽取全区共享礼包
	CDataDragonScaleGiftBag *pData = GetDragonScaleData();

	if(pData == NULL)
	{
		DB_ERROR_RETURN_MSG("init_dragonScale_data_fail");
	}

	bool succ = false;
	int count = 0;
	Json::Value winners;
	ret = pData->GetGiftBag(uid, winners, count, succ);

	if(ret)
	{
		error_log("[GetRareItemsNumbers_data_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	if (!result.isMember("equipGiftBag"))
	{
		result["equipGiftBag"] = Json::arrayValue;
	}

	if (!result.isMember("giftBagSucc"))
	{
		result["giftBagSucc"] = Json::arrayValue;
	}

	if (succ)
	{
		CLogicEquipment logicEquipment;
		Json::Value giftbag;

		ret = logicEquipment.AddOneItem(uid, DRAGON_SCALE_ACTIVITY_SHARE_GIFT_ID, 1, "dragonScaleActivty", giftbag, true);

		if (ret)
			return ret;

		result["equipGiftBag"].append(giftbag);
	}

	newAct["useTimes"] = newAct["useTimes"].asUInt() + 1;

	result["giftBagSucc"].append(succ?1:0);
	result["giftBagCount"] = count;
	result["giftBagWinners"] = winners;

	return 0;
}

int CLogicCMD::GetDragonScaleData(unsigned uid, Json::Value &result)
{

	CDataDragonScaleGiftBag *pData = GetDragonScaleData();
	if(pData == NULL)
	{
		DB_ERROR_RETURN_MSG("init_dragonScale_data_fail");
	}
	unsigned count = 0;

	int ret = pData->GetData(uid, result["winners"], count);
	if (ret)
		return ret;
	result["count"] = count;

	return R_SUCCESS;
}

CDataDragonScaleGiftBag* CLogicCMD::GetDragonScaleData()
{
	GET_MEM_DATA_SEM(CDataDragonScaleGiftBag, DRAGON_SCALE_PATH, sem_dragon_scale_gift_bag, false)
}

int CLogicCMD::HappyCard(unsigned uid, unsigned type, const Json::Value &iData, Json::Value &result, unsigned lasttime, unsigned seqid)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_HAPPYCARD_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HAPPYCARD_END_TS))
	{
		error_log("happy_card_scale_time_error");
		return R_ERR_REFUSE;
	}

	if (type >= happyCard_ActionTypeMax)
		return R_ERR_PARAM;

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct_1;
	Json::Value newAct_2;
	CLogicSecinc logicSecinc;
	unsigned sid_1 = NAT_HAPPYCARD_1;
	unsigned sid_2 = NAT_HAPPYCARD_2;
	int ret_1 = 0, ret_2 = 0;
	ret_1 = logicSecinc.GetSecinc(uid, sid_1, newAct_1);
	ret_2 = logicSecinc.GetSecinc(uid, sid_2, newAct_2);
	if (ret_1 == R_ERR_NO_DATA || ret_2 == R_ERR_NO_DATA)
	{
		newAct_1["id"] = sid_1;
		newAct_1["ca"] = Json::Value(Json::arrayValue); // choose array
		newAct_1["inter"] = 0; // inter
		newAct_1["ti"] = 0; // time
		newAct_1["ts"] = Time::GetGlobalTime(); // todayTs
		newAct_1["v"] = Config::GetIntValue(CONFIG_HAPPYCARD_VER); //version
		newAct_1["rf"] = 0; // refresh times
		newAct_1["o"] = 0; // openCount

		newAct_2["id"] = sid_2;
		newAct_2["sa"] = Json::Value(Json::arrayValue); // show array
	}
	else if ((ret_1&&ret_1 != R_ERR_NO_DATA) ||
			(ret_2&&ret_2 != R_ERR_NO_DATA))
	{
		return ret_1;
	}

	if ( newAct_1["v"].asInt() != Config::GetIntValue(CONFIG_HAPPYCARD_VER))
	{
		newAct_1["id"] = sid_1;
		newAct_1["ca"] = Json::Value(Json::arrayValue); // choose array
		newAct_1["inter"] = 0; // inter
		newAct_1["ti"] = 0; // time
		newAct_1["ts"] = Time::GetGlobalTime(); // todayTs
		newAct_1["v"] = Config::GetIntValue(CONFIG_HAPPYCARD_VER); //version
		newAct_1["rf"] = 0; // refresh times
		newAct_1["o"] = 0; // openCount

		newAct_2["id"] = sid_2;
		newAct_2["sa"] = Json::Value(Json::arrayValue); // show array
	}
	if (CTime::GetDayInterval(newAct_1["ts"].asUInt(), Time::GetGlobalTime()) != 0)
	{
		newAct_1["inter"] = 0;
		newAct_1["ti"] = 0;
		newAct_1["ts"] = Time::GetGlobalTime();
	}

	if (type == happyCard_BeginGame)
	{
		// 生成8个卡牌
		getHappyCardShowArr(newAct_2);
		newAct_1["ca"].clear();
		newAct_1["rf"] = 6;
		newAct_1["inter"] = newAct_1["inter"].asUInt() + 30;
		newAct_1["ti"] = newAct_1["ti"].asUInt() + 1;

		// 消耗200钻石
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);

		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -200, 0, payData, "happyCard_Cost", user_flag, bsave);
		if (ret != 0)
			return ret;
		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}

		result["coins"] = payData.coins;	//金币
		result["coins2"] = payData.cash;	//钻石
	}
	else if (type == happyCard_Refresh)
	{
		// 生成8个卡牌
		if (newAct_1["rf"].asUInt() == 0)
		{
			return R_ERR_LOGIC;
		}
		getHappyCardShowArr(newAct_2);
		newAct_1["ca"].clear();
		newAct_1["rf"] = newAct_1["rf"].asUInt() - 1;
	}
	else if (type == happyCard_BeginDraw)
	{
		// 抽取4个卡牌
		if (newAct_2["sa"].size() != 8 || newAct_1["ca"].size() == 4)
		{
			return R_ERR_PARAM;
		}

		bool hasOrange = false, hasPruple = false;
		unsigned orangePosition = 0;
		for (int i = 0; i < newAct_2["sa"].size(); i++)
		{
			if (newAct_2["sa"][i][(unsigned)0].asInt() == happyCard_Orange)
			{
				orangePosition = i;
				int rand = Math::GetRandomInt(10000);
				if (rand < newAct_2["sa"][i][3].asUInt())
				{
					hasOrange = true;

					Json::Value item = Json::Value(Json::arrayValue);
					item.append(i);
					item.append(-1);

					newAct_1["ca"].append(item);
				}
				break;
			}
		}

		unsigned total = 0;
		if (hasOrange)
			total = 1;
		while (total < 4)
		{
			int rand = Math::GetRandomInt(8);
			if (rand == orangePosition)
				continue;

			bool hasThisCard = false;
			for (unsigned i = 0; i < newAct_1["ca"].size(); i++)
			{
				if (newAct_1["ca"][i][(unsigned)0].asUInt() == rand)
				{
					hasThisCard = true;
					break;
				}
			}
			if (hasThisCard)
				continue;

			if (newAct_2["sa"][rand][(unsigned)0].asInt() == happyCard_Purple) {
				if (!hasPruple)
					hasPruple = true;
				else
					continue;
			}

			Json::Value item = Json::Value(Json::arrayValue);
			item.append(rand);
			item.append(-1);
			newAct_1["ca"].append(item);
			++total;
		}
	}
	else if (type == happyCard_Draw)
	{
		// 设定抽取牌的位置
		if (!iData["canDraw"].asBool())
		{
			return R_ERR_PARAM;
		}

		unsigned openCount = newAct_1["o"].asUInt();
		unsigned position = iData["position"].asUInt();
		if (newAct_1["ca"].size() != 4 || openCount >= 4 || position >= 8)
		{
			return R_ERR_PARAM;
		}
		newAct_1["ca"][openCount][1] = position;
		newAct_1["o"] = openCount + 1;
	}
	else if (type == happyCard_Collect)
	{
		// 添加4种道具
		if (!newAct_1["ca"].isArray() || newAct_1["ca"].size() != 4
				||!newAct_2["sa"].isArray() || newAct_2["sa"].size() != 8)
		{
			return R_ERR_PARAM;
		}

		CLogicEquipment logicEquip;
		for (unsigned i = 0; i < newAct_1["ca"].size(); i++)
		{
			unsigned index = newAct_1["ca"][i][(unsigned)0].asUInt();
			unsigned eqid = newAct_2["sa"][index][1].asUInt();
			unsigned count = newAct_2["sa"][index][2].asUInt();
			Json::Value equipResult;
			logicEquip.AddOneItem(uid, eqid, count, "happyCard_Get", equipResult);
			result["equipment"].append(equipResult);
		}

		newAct_2["sa"].clear();
		newAct_1["ca"].clear();
		newAct_1["rf"] = 0;
		newAct_1["o"] = 0;
	}
	else if (type == happyCard_ChargeBack)
	{
		// 返回60砖石
		if (!newAct_1["ca"].isArray() || newAct_1["ca"].size() != 4
				||!newAct_2["sa"].isArray() || newAct_2["sa"].size() != 8)
		{
			return R_ERR_PARAM;
		}

		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ChangePay(uid, 60, 0, "happyCard_ChargeBack", payData);
		if (ret != 0)
			return ret;

		result["coins"] = payData.coins;	//金币
		result["coins2"] = payData.cash;	//钻石

		newAct_2["sa"].clear();
		newAct_1["ca"].clear();
		newAct_1["rf"] = 0;
		newAct_1["o"] = 0;
	}

	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(newAct_1);
	result["newAct"].append(newAct_2);
	ret_1 = logicSecinc.SetOneSecinc(uid, newAct_1);
	ret_2 = logicSecinc.SetOneSecinc(uid, newAct_2);
	if (ret_1)
		return ret_1;
	if (ret_2)
		return ret_2;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::getHappyCardShowArr(Json::Value &newAct)
{
	if (!newAct["sa"].isArray())
		newAct["sa"] = Json::Value(Json::arrayValue);
	newAct["sa"].resize(8);

	unsigned size = 8;
	int randArr[8] = {0,1,2,3,4,5,6,7};
	for (int i = size; i > 0; i--)
	{
		int rand = Math::GetRandomInt(i);
		if (rand != i-1)
		{
			unsigned tmp = randArr[rand];
			randArr[rand] = randArr[i-1];
			randArr[i-1] = tmp;
		}
	}
	// 橙色卡牌
	int rand = Math::GetRandomInt(100);
	for (unsigned i = 0; i < 3; ++i)
	{
		if (rand < HAPPY_CARD_ORANGE_RATE[i])
		{
			int rand = Math::GetRandomInt(10000);
			for (unsigned j = 0; j < 21; ++j)
			{
				if (rand < HAPPY_CARD_ORANGE_EACH_RATE[i][j])
				{
					newAct["sa"][randArr[0]] = Json::Value(Json::arrayValue);
					newAct["sa"][randArr[0]].append(happyCard_Orange);
					newAct["sa"][randArr[0]].append(HAPPY_CARD_ORANGE_EACH_ID_COUNT[i][j][0]);
					newAct["sa"][randArr[0]].append(HAPPY_CARD_ORANGE_EACH_ID_COUNT[i][j][1]);
					if (i == 0)
						newAct["sa"][randArr[0]].append(0);
					else if (i == 1)
						newAct["sa"][randArr[0]].append(200);
					else if (i == 2)
						newAct["sa"][randArr[0]].append(100);
					break;
				}
			}
			break;
		}
	}

	// 其余卡牌
	unsigned total = 0;
	unsigned purpleMax = 3;
	int purpleNum = 0;
	while (total < 7)
	{
		unsigned rand = Math::GetRandomInt(10000);
		for (unsigned i = 0; i < 4; i++)
		{
			if (rand < HAPPY_CARD_RATE[i])
			{
				int color;
				if (i == 0)
					color = happyCard_White;
				else if (i == 1)
					color = happyCard_Green;
				else if (i == 2)
					color = happyCard_Blue;
				else if (i == 3)
				{
					color = happyCard_Purple;
					if (purpleNum < purpleMax)
						++purpleNum;
					else
						break;
				}

				unsigned rand = Math::GetRandomInt(10000);
				for (unsigned j = 0; j < 21; ++j)
				{
					if (rand < HAPPY_CARD_EACH_RATE[i][j])
					{
						newAct["sa"][randArr[total+1]] = Json::Value(Json::arrayValue);
						newAct["sa"][randArr[total+1]].append(color);
						newAct["sa"][randArr[total+1]].append(HAPPY_CARD_EACH_ID_COUNT[i][j][0]);
						newAct["sa"][randArr[total+1]].append(HAPPY_CARD_EACH_ID_COUNT[i][j][1]);
						++total;
						break;
					}
				}
				break;
			}
		}
	}
	return R_SUCCESS;
}

int CLogicCMD::Poker21(unsigned uid, unsigned type, const vector<unsigned> &iData, unsigned lasttime, unsigned seqid, Json::Value &result)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_DIANJIANG_BEGIN_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_DIANJIANG_END_TS))
	{
		error_log("poker_scale_time_error");
		return R_ERR_REFUSE;
	}

	if (type >= pokerTypeMax)
	{
		return R_ERR_PARAM;
	}

	int ret = 0;
	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	ret = logicUser.GetUser(uid,dataUser);
	if(ret)
	{
		error_log(" get user info failed,uid = %u",uid);
		return ret;
	}

	ret = checkLastSaveUID(dataUser);
	if(ret)
		return ret;

	ret = checkLastSaveTime(dataUser,lasttime,seqid);
	if(ret)
		return ret;
	result["lasttime"] = dataUser.last_save_time;
	result["lastseq"] = dataUser.lastseq;
	result["saveuserid"] = uid;

	Json::Value newAct;
	CLogicSecinc logicSecinc;
	unsigned sid = NAT_POKER;
	ret = logicSecinc.GetSecinc(uid, sid, newAct);
	if (ret == R_ERR_NO_DATA)
	{
		newAct["id"] = sid;
		newAct["v"] = Config::GetIntValue(CONFIG_DIANJIANG_VER); //version
		newAct["rw"] = Json::Value(Json::arrayValue); //reward [id,count]
		newAct["m"] = 1; //multiple
		newAct["o"] = 0; //openCount
		newAct["ra"] = Json::Value(Json::arrayValue); //resultArray
		newAct["sa"] = Json::Value(Json::arrayValue); //showArray
		newAct["sc"] = 0; //score
		newAct["st"] = poker_BeginGame; //状态机status
	}
	else if (ret)
	{
		return ret;
	}

	if (newAct["v"].asInt() != Config::GetIntValue(CONFIG_DIANJIANG_VER))
	{
		newAct["id"] = sid;
		newAct["v"] = Config::GetIntValue(CONFIG_DIANJIANG_VER);
		newAct["rw"] = Json::Value(Json::arrayValue);
		newAct["m"] = 1;
		newAct["o"] = 0;
		newAct["ra"] = Json::Value(Json::arrayValue);
		newAct["sa"] = Json::Value(Json::arrayValue);
		newAct["sc"] = 0;
		newAct["st"] = poker_BeginGame;
	}

	if (type == poker_BeginGame)
	{
		if (newAct["st"].asUInt() != poker_BeginGame)
		{
			return R_ERR_PARAM;
		}
		//生成最终点数
		unsigned total = 0;
		int rand = Math::GetRandomInt(10000);
		for (int i = 0; i < 9; i++)
		{
			if (rand < POKER_POINT_RATE[i])
			{
				total = 13+i;
				break;
			}
		}
		//生成最终牌数，并排好序列
		unsigned cardNum = 0;
		if (total < 15)
		{
			int rand = Math::GetRandomInt(13);
			for (int i = 0; i < 3; i++)
			{
				if (rand < POKER_CARD_NUM_RATE[0][i])
				{
					cardNum = 2+i;
					break;
				}
			}
		}
		else if (total < 20)
		{
			int rand = Math::GetRandomInt(21);
			for (int i = 0; i < 4; i++)
			{
				if (rand < POKER_CARD_NUM_RATE[1][i])
				{
					cardNum = 2+i;
					break;
				}
			}
		}
		else
		{
			int rand = Math::GetRandomInt(15);
			for (int i = 0; i < 3; i++)
			{
				if (rand < POKER_CARD_NUM_RATE[2][i])
				{
					cardNum = 3+i;
					break;
				}
			}
		}

		Json::Value cardArray(Json::arrayValue);
		Json::Value cardRest(Json::arrayValue);
		switch(cardNum)
		{
		case 2:
		{
			unsigned temp = 0;
			do
			{
				temp = Math::GetRandomInt(21-total) + (total - 10);
			}while(temp == total - temp);
			cardArray.append(temp);
			cardArray.append(total - temp);

			for (unsigned i = 1; i <= 10; i++)
			{
				if(i != temp && i != (total-temp))
					cardRest.append(i);
			}
		}
		break;
		case 3:
		{
			int rand = Math::GetRandomInt(POKER_LIST_3_NUM[total-13]);
			const int *list = POKER_LIST_3[total-13][rand];
			for (int i = 0; i < 3; i++)
			{
				cardArray.append(list[i]);
			}
			for (unsigned i = 1; i <= 10; i++)
			{
				if(i != list[0] && i != list[1] && i != list[2])
					cardRest.append(i);
			}
		}
		break;
		case 4:
		{
			int rand = Math::GetRandomInt(POKER_LIST_4_NUM[total-13]);
			const int *list = POKER_LIST_4[total-13][rand];
			for (int i = 0; i < 4; i++)
			{
				cardArray.append(list[i]);
			}
			for (unsigned i = 1; i <= 10; i++)
			{
				if(i != list[0] && i != list[1] && i != list[2] && i != list[3])
					cardRest.append(i);
			}
		}
		break;
		case 5:
		{
			int rand = Math::GetRandomInt(POKER_LIST_5_NUM[total-15]);
			const int *list = POKER_LIST_5[total-15][rand];
			for (int i = 0; i < 5; i++)
			{
				cardArray.append(list[i]);
			}
			for (unsigned i = 1; i <= 10; i++)
			{
				if(i != list[0] && i != list[1] && i != list[2] && i != list[3] && i != list[4])
					cardRest.append(i);
			}
		}
		break;
		case 6:
		{
			for (int i = 0; i < 6; i++)
			{
				cardArray.append(POKER_LIST_6[i]);
			}
			for (int i = 7; i <= 10; i++)
			{
				cardRest.append(i);
			}
		}
		break;
		default:
		{
			error_log("cardNum > 6?");
			LOGIC_ERROR_RETURN_MSG("cardNum > 6?how could this happen?");
		}
		break;
		}

		//乱序
		for (unsigned i = cardArray.size(); i > 0; i--)
		{
			int rand = Math::GetRandomInt(i);
			if (rand != i-1)
			{
				unsigned tmp = cardArray[rand].asUInt();
				cardArray[rand] = cardArray[i-1].asUInt();
				cardArray[i-1] = tmp;
			}
		}
		//2分之一 末牌最小
		if (Math::GetRandomInt(2) == 0)
		{
			unsigned min = 0;
			unsigned pos = 0;
			unsigned size = cardArray.size();
			for (unsigned i = 0; i < size; i++)
			{
				if (min < cardArray[i].asUInt())
				{
					min = cardArray[i].asUInt();
					pos = i;
				}
			}
			if (pos != size - 1)
			{
				unsigned tmp = cardArray[size-1].asUInt();
				cardArray[size-1] = cardArray[pos].asUInt();
				cardArray[pos] = tmp;
			}
		}
		// 生成剩余牌的序列
		Json::Value cardLast(Json::arrayValue);
		for (unsigned i = 0; i < cardRest.size(); i++)
		{
			if (total + cardRest[i].asUInt() > 21)
				cardLast.append(cardRest[i].asUInt());
		}
		rand = Math::GetRandomInt(cardLast.size());
		unsigned last = cardLast[rand].asUInt();  //最后一张封顶
		cardArray.append(last);

		for (unsigned i = cardRest.size(); i > 0; i--)
		{
			int rand = Math::GetRandomInt(i);
			if (rand != i-1)
			{
				unsigned tmp = cardRest[rand].asUInt();
				cardRest[rand] = cardRest[i-1].asUInt();
				cardRest[i-1] = tmp;
			}
		}
		for (unsigned i = 0; i < cardRest.size(); i++)
		{
			if (cardRest[i].asUInt() != last)
				cardArray.append(cardRest[i].asUInt());
		}

		newAct["ra"] = cardArray;
		newAct["m"] = 1;
		newAct["rw"].clear();
		newAct["sa"].clear();
		newAct["o"] = 0;
		newAct["sc"] = 0;
		newAct["st"] = poker_Draw;
	}
	else if (type == poker_Draw)
	{
		if (newAct["st"].asUInt() != poker_Draw)
		{
			return R_ERR_PARAM;
		}
		//添加牌位置到抽取序列

		if (iData[0u] == 0)
		{
			return R_ERR_PARAM;
		}

		newAct["m"] = iData[0u];
		unsigned pos = iData[1u];

		unsigned openCount = newAct["o"].asUInt();
		if (!newAct["sa"].isArray())
		{
			newAct["sa"] = Json::Value(Json::arrayValue);
		}
		newAct["sa"][openCount] = pos; //pos界面显示位置

		// 增加点数
		unsigned credit = 0;
		if (!Json::GetUInt(newAct["ra"], openCount, credit))
		{
			return R_ERR_DATA;
		}
		unsigned scoreOld = newAct["sc"].asUInt();
		if (scoreOld > 21)
		{
			return R_ERR_PARAM;
		}
		unsigned score = scoreOld + credit;
		newAct["sc"] = score;
		newAct["o"] = ++openCount;

		// 生成奖励
		unsigned rewardId = 0;
		unsigned count = 0;
		if (21 == score && 6 == openCount)
		{
			//超级大奖
			rewardId = POKER_REWARD[10][0][0];
			count = newAct["m"].asUInt() * POKER_REWARD[10][0][1];
		}
		else if (13 <= score && score <= 21)
		{
			int random = Math::GetRandomInt(POKER_REWARD_NUM[score-13]);
			rewardId = POKER_REWARD[score-13][random][0];
			count = newAct["m"].asUInt() * POKER_REWARD[score-13][random][1];
		}
		else if (21 < score)
		{
			int random = Math::GetRandomInt(POKER_REWARD_NUM[9]);
			rewardId = POKER_REWARD[9][random][0];
			count = newAct["m"].asUInt() * POKER_REWARD[9][random][1];
		}

		if (13 <= score)
		{
			newAct["rw"].resize(2);
			newAct["rw"][unsigned(0)] = rewardId;
			newAct["rw"][1] = count;
		}

		// 根据倍数消耗钻石
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);

		int cashCost = newAct["m"].asUInt()*20;
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.ProcessOrderForBackend(uid, -cashCost, 0, payData, "poker21_Cost", user_flag, bsave);
		if (ret != 0)
			return ret;
		result["pointpay"].resize(0);
		if(bsave)
		{
			result["pointpay"] = user_flag["user_pay"];
			dataUser.user_flag = writer.write(user_flag);
		}

		result["coins"] = payData.coins;	//金币
		result["coins2"] = payData.cash;	//钻石

		if (score < 21)
		{
			newAct["st"] = poker_Draw;
		}
		else
		{
			newAct["st"] = poker_GetReward;
		}
	}
	else if (type == poker_GetReward)
	{
		if (newAct["st"].asUInt() == poker_BeginGame ||
				!newAct["rw"].isArray() || newAct["rw"].size() != 2)
		{
			return R_ERR_PARAM;
		}
		// 领奖励
		unsigned rewardId = newAct["rw"][unsigned(0)].asUInt();
		unsigned count = newAct["rw"][1].asUInt();

		CLogicEquipment logicEquip;
		ret = logicEquip.AddOneItem(uid, rewardId, count, "poker21_reward", result["equipment"]);
		if (ret)
			return ret;

		newAct["rw"].clear();
		newAct["ra"].clear();
		newAct["sa"].clear();
		newAct["m"] = 1;
		newAct["o"] = 0;
		newAct["sc"] = 0;
		newAct["st"] = poker_BeginGame;
	}

	result["newAct"] = Json::Value(Json::arrayValue);
	result["newAct"].append(newAct);
	ret = logicSecinc.SetOneSecinc(uid, newAct);
	if (ret)
		return ret;

	ret = logicUser.SetUser(uid, dataUser);
	if (ret)
		return ret;
	return R_SUCCESS;
}

int CLogicCMD::QuestReward(
	unsigned uid,
	Json::Value &data,
	XMLQuestReward &reward_data,
	Json::Value &newEqDatas,
	vector<string> &hero)
{
	int ret = 0;
	if (!data.isArray()) {
		return R_ERR_PARAM;
	}
	string code;
	int olgateconfig = 0;
	for(int i=0; i<data.size(); i++) {
		Json::Value &quest = data[i];

		string configname;
		Json::GetString(quest, "cn", configname);
		if (configname.empty()) {
			error_log("[configname is empty][index=%d]", i);
			continue;
		}

		Json::GetInt(quest, "ud", reward_data.hud);

		if (configname == "activityconfig") {
			string questname;
			Json::GetString(quest, "scn", questname);
			int reward_id;
			Json::GetInt(quest, "id", reward_id);

			ret = GetActivityReward(questname,reward_id,reward_data,newEqDatas,hero);
			if (0 != ret) {
				error_log("[GetActivityReward fail][ret=%d,uid=%d,questname=%s,reward_id=%d]",
						ret,uid,questname.c_str(),reward_id);
				return ret;
			}
			code += "activity_"+questname+"_"+CTrans::ITOS(reward_id);
		} else if (configname == "olgateconfig") {
			int level = -1;
			Json::GetInt(quest, "id", level);
			int sid = 0;
			Json::GetInt(quest, "sid", sid);
			int ch = 0;
			Json::GetInt(quest, "ch", ch); // equipment ch
			int gf = 0;
			Json::GetInt(quest, "gf", gf); // first reward
			olgateconfig++;
			if (olgateconfig > 1)
			{
				gf = -1;
			}
			ret = GetOlGateReward(level,sid,reward_data,newEqDatas,hero,(gf==1),ch);
			if (0 != ret){
				error_log("[GetOlGateReward fail][ret=%d,level=%d,id=%d,gf=%d,ch=%d]",
						ret,level,sid,gf,ch);
				return ret;
			}
			if (code.empty()){
				code = "olgate_";
			}
			code += CTrans::ITOS(level)+"_"+CTrans::ITOS(sid)+"_"+CTrans::ITOS(gf)+":";
		} else if (configname == "questconfig") {
			int id = -1;
			Json::GetInt(quest, "id", id);

			ret = GetQuestReward(id,reward_data,newEqDatas,hero);
			if (0 != ret) {
				error_log("[GetQuestReward fail][uid=%u,ret=%d,id=%d,version=%d]",uid,ret,id);
				return ret;
			}
			code += "quest_"+CTrans::ITOS(id);
		}
	}
	string hero_log = "[";
	if (hero.size()>0) {
		for(vector<string>::iterator itr = hero.begin(); itr!=hero.end(); itr++) {
			hero_log += *itr+",";
		}
	}
	hero_log += "]";
	ORDERS_LOG("uid=%u&code=%s&hex=%u&ud=%u&gol=%u&cas=%u&exp=%u&ene=%u&sou=%u&pro=%u&r1=%u&r2=%u&r3=%u&eq=%s&hero=%s",
			uid,code.c_str(),reward_data.hex,reward_data.hud,reward_data.gol,reward_data.cas,reward_data.exp,
			reward_data.ene,reward_data.sou,reward_data.pro,
			reward_data.rs[0],reward_data.rs[1],reward_data.rs[2],
			Json::ToString(newEqDatas).c_str(),hero_log.c_str());

	return 0;
}

int CLogicCMD::GetActivityReward(const string &questid,
	int rewardid,
	XMLQuestReward &reward_data,
	Json::Value &newEqDatas,
	vector<string> &hero)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML) {
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	map<string, string> config;
	ret = dataXML->GetActivityConfig(questid, config);
	if (0 != ret) {
		error_log("[GetQuestReward fail][ret=%d,questid=%s]", ret, questid.c_str());
		return ret;
	}
	if (!config.count(CTrans::ITOS(rewardid))) {
		error_log("[reward id not exists][rewardid=%d]", rewardid);
		return R_ERR_NO_DATA;
	}
	Json::Value reward;
	if(!Json::FromString(reward, config[CTrans::ITOS(rewardid)])) {
		error_log("[parse data faile][rewardid=%d]", rewardid);
		return R_ERR_DATA;
	}

	if (!reward.isMember("reward")) {
		return R_ERR_DATA;
	}
	string code = "activity_"+questid+"_"+CTrans::ITOS(rewardid);
	return parseQuestReward(reward["reward"],reward_data,newEqDatas,hero,code);
}

int CLogicCMD::GetOlGateReward(int level,
	int id,
	XMLQuestReward &reward_data,
	Json::Value &newEqDatas,
	vector<string> &hero,
	bool freward,
	int ch)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML) {
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	map<string, string> config;
	ret = dataXML->GetOlGateConfig(level, config);
	if (0 != ret) {
		error_log("[GetQuestReward fail][ret=%d,questid=%d]", ret, level);
		return ret;
	}
	string code = "olgate_"+CTrans::ITOS(level)+"_"+CTrans::ITOS(id);
	Json::Reader reader;
	if (config.count("reward")) {
		Json::Value reward;
		if (Json::FromString(reward, config["reward"])) {
			parseQuestReward(reward,reward_data,newEqDatas,hero,code);
		}
	}
	if (freward && config.count("freward")) {
		Json::Value freward;
		if (Json::FromString(freward, config["freward"])) {
			parseQuestReward(freward,reward_data,newEqDatas,hero,code);
		}
	}
	string itemid;
	if (ch == -1)
		ch = 0;
	if (id > 0) {
		String::Format(itemid, "%d_%d",id,ch); // itemid style: equid_ch
		if (config.count(itemid)) {
			Json::Value equpment;
			if (Json::FromString(equpment, config[itemid])) {
				ItemAdd item;
				item.count = 1;
				Json::GetUInt(equpment, "id", item.eqid);
				Json::GetUInt(equpment, "c", item.ch);
				Json::GetUInt(equpment, "q", item.q);
				item.reason = code;
				if (ch == item.ch){
					CLogicEquipment logicEquipment;
					logicEquipment.genEquip(item,newEqDatas);
				}
			} else {
				error_log("[parse equpment faile][data=%s]", config[itemid].c_str());
			}
		} else {
			error_log("[item %s not exists!]", itemid.c_str());
			return R_ERR_NO_DATA;
		}
	}
	return 0;
}

int CLogicCMD::GetQuestReward(int id,
		XMLQuestReward &reward_data,
		Json::Value &newEqDatas,
		vector<string> &hero)
{
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetCDataXML();
	if(!dataXML) {
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}
	Json::Value reward_cofig;
	ret = dataXML->GetQuestConfig(CTrans::ITOS(id), reward_cofig);
	if (0 != ret) {
		error_log("[GetQuestConfig fail][ret=%d,questid=%d]", ret, id);
		return ret;
	}
	string code = "olgate_"+CTrans::ITOS(id);
	return parseQuestReward(reward_cofig,reward_data,newEqDatas,hero,code);
}

int CLogicCMD::parseQuestReward(const Json::Value &data,
		XMLQuestReward &reward_data,
		Json::Value &newEqDatas,
		vector<string> &hero,
		const string &code)
{
	vector<ItemAdd> equp;
	equp.clear();
	for(Json::Value::iterator itr=data.begin(); itr!=data.end(); ++itr)
	{
		string key = itr.key().asString().substr(0,3);
		if (key == "exp"){
			reward_data.exp += (*itr).asInt();
		}else if (key == "hex"){
			reward_data.hex += (*itr).asInt();
		}else if (key == "ene"){
			reward_data.ene += (*itr).asInt();
		}else if (key == "equ"){
			ItemAdd item;
			item.reason = code;
			Json::GetUInt(*itr, "id", item.eqid);
			Json::GetUInt(*itr, "c", item.count);
			equp.push_back(item);
		}else if (key == "gol"){
			reward_data.gol += (*itr).asInt();
		}else if (key == "cas"){
			reward_data.cas += (*itr).asInt();
		}else if (key == "rs1"){
			reward_data.rs[0] += (*itr).asInt();
		}else if (key == "rs2"){
			reward_data.rs[1] += (*itr).asInt();
		}else if (key == "rs3"){
			reward_data.rs[2] += (*itr).asInt();
		}else if (key == "rs4"){
			reward_data.rs[3] += (*itr).asInt();
		}else if (key == "sou"){
			reward_data.sou += (*itr).asInt();
		}else if (key == "pro"){
			reward_data.pro += (*itr).asInt();
		}else if (key == "res"){ // res1,res2,res3
			string tem_key = itr.key().asString().substr(3,4);
			int res = CTrans::STOI(tem_key);
			if (res>0 && res<=MAX_RES)
				reward_data.rs[res-1] += (*itr).asInt();
		}else if (key == "her"){
			unsigned heroid;
			Json::GetUInt(*itr, "id", heroid);
			hero.push_back(CDataXML::Hero2Str(heroid));
		}
	}
	if (equp.size() > 0) {
		CLogicEquipment logicEquipment;
		for(unsigned i=0;i<equp.size();++i)
			logicEquipment.genEquip(equp[i], newEqDatas);
	}
	return 0;
}


int CLogicCMD::GetBarbarReward(unsigned uid, Json::Value &data, Json::Value &newEqDatas)
{
	unsigned gate = 0;
	unsigned lv = 0;

	if (!Json::GetUInt(data, "gate", gate)  || (gate >= XMLBARBARKING_GATE_NUM)
	|| !Json::GetUInt(data, "lv", lv) || (lv >= XMLBARBARKING_NUM))
	{
		error_log("uid=%u, gate=%u, lv=%u", uid, gate, lv);
		return R_ERR_PARAM;
	}

	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		error_log("GetCDataXML fail");
		return R_ERR_DB;
	}

	XMLBarbarItem item;

	int ret = dataxml->GetBarbarKingItem(lv, gate, item);
	if (ret)
	{
		error_log("GetBarbarKingItem failed. uid = %u, ret = %u", uid, ret);
		return ret;
	}

	CLogicEquipment logicEquip;
	ret = logicEquip.AddOneItem(uid, item.eqid, item.c, "GetBarbarReward", newEqDatas, true);
	if (ret)
	{
		error_log("AddOneItem failed. uid = %u, ret = %u", uid, ret);
	}

	return R_SUCCESS;
}


int CLogicCMD::GetFiveTigerReward(unsigned uid, string &user_tech, Json::Value &data, Json::Value &result)
{
	unsigned chapter = 0;
	int egate = 0;
	unsigned type = 0;

	if (!Json::GetUInt(data, "chapter", chapter) || !Json::GetInt(data, "gate", egate)
	|| !Json::GetUInt(data, "type", type) || (type > 1))
	{
		error_log("uid=%u, chapter=%u, gate=%u, type=%u", uid, chapter, egate, type);
		return R_ERR_PARAM;
	}

	// 当前第一关没过
	if (egate < 0)
	{
		result["yinliang"][0u] = 0;
		return 0;
	}

	CDataXML *dataxml = CDataXML::GetCDataXML();
	if (NULL == dataxml)
	{
		error_log("GetCDataXML failed");
		return R_ERR_DB;
	}

	unsigned addyl;

	unsigned sgate = 0;
	if (0 == type)
	{
		sgate = egate;
	}
	else if (1 == type)
	{
		sgate = 0;
	}

	int ret = dataxml->GetFiveTigerItem(chapter, sgate, egate, addyl, result["yinliang"]);
	if (ret)
	{
		error_log("GetFiveTigerItem failed. uid = %u, ret = %u, chapter = %u, gate = %u", uid, ret, chapter, egate);
		return ret;
	}

	unsigned yinliang = 0;
	Json::Value tech;
	Json::Reader reader;
	Json::FastWriter writer;

	reader.parse(user_tech,tech);
	Json::GetUInt(tech, "yinliang", yinliang);

	yinliang += addyl;

	tech["yinliang"] = yinliang;
	user_tech = writer.write(tech);

	RESOURCE_LOG("[GetFiveTigerReward][uid=%u,chgyinliang=%u,yinliang=%u]", uid, addyl, yinliang);

	return R_SUCCESS;
}

