/*
 * LogicArchive.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicArchive.h"
#include "WeiyouxiPlatform.h"
#include "FacebookPlatform.h"

int CLogicArchive::GetArchive(PlatformType platform, unsigned uid, unsigned baseid, Json::Value &archive)
{
	int ret;
	if(LogicNpc::IsNpc(baseid))
	{
		return LogicNpc::GetArchive(uid, baseid, false, archive);
	}

	CLogicAlliance logicAlliance;
	CLogicInventory logicInventory;
	CLogicPay logicPay;
	DataArchive archiveLoad;
	CHECK_CALL(LogicBase::GetBase(uid, baseid, archiveLoad.Base));
	if(uid != archiveLoad.Base.uid)
	{
		error_log("[user not base owner][uid=%u,baseid=%u,ruid=%u]", uid, baseid, archiveLoad.Base.uid);
		uid = archiveLoad.Base.uid;
	}
	CHECK_CALL(LogicBase::GetBaseExtra(archiveLoad.Base.baseid, archiveLoad.BaseExtra));
	if(IsValidUid(uid))
	{
		CHECK_CALL(LogicUserBasic::GetUserSmart(uid, platform, archiveLoad.UserBasic));
		CHECK_CALL(LogicUser::GetUser(uid, archiveLoad.User));
		CHECK_CALL(LogicUser::GetUserExtra(uid, archiveLoad.UserExtra));
		CHECK_CALL(logicPay.GetCash(uid, archiveLoad.Cash));
		CHECK_CALL(logicInventory.GetItemsJson(uid, archive["logicInventory"]));
		if(IsAllianceId(archiveLoad.User.alliance_id))
		{
			CHECK_CALL(logicAlliance.GetAlliance(archiveLoad.User.alliance_id, archiveLoad.Alliance));
			CHECK_CALL(logicAlliance.GetMember(archiveLoad.User.alliance_id, uid, archiveLoad.Member));
		}
	}
	CHECK_CALL(ArchiveToJson(archiveLoad, archive, true));
	archive["damage"] = archiveLoad.Base.damage;
	archive["destroyed"] = archiveLoad.Base.destroyed;
	archive["empirevalue"] = Convert::UInt64ToString(archiveLoad.Base.value);
	archive["flinger"] = archiveLoad.Base.attack_level;
	archive["catapult"] = archiveLoad.Base.bomb_level;
	Json::FromString(archive["updates"], archiveLoad.BaseExtra.updates);
	return ret;
}

int CLogicArchive::SetArchive(PlatformType platform, unsigned uid, unsigned baseid, const Json::Value &archive)
{
	int ret;
	if(LogicNpc::IsNpc(baseid))
	{
		PARAM_ERROR_RETURN();
	}

	DataUser user;
	DataUserExtra userExtra;
	DataBase base;
	DataBaseExtra baseExtra;

	CHECK_CALL(LogicBase::GetBase(uid, baseid, base));
	if(uid != base.uid)
	{
		error_log("[user not base owner][uid=%u,baseid=%u,ruid=%u]", uid, baseid, base.uid);
		uid = base.uid;
	}
	CHECK_CALL(LogicBase::GetBaseExtra(base.baseid, baseExtra));
	if(IsValidUid(uid))
	{
		CHECK_CALL(LogicUser::GetUser(uid, user));
		CHECK_CALL(LogicUser::GetUserExtra(uid, userExtra));
	}

	Json::GetString(archive, "basename", base.base_name);
	Json::GetInt(archive, "baseseed", base.seed);
	//Json::GetString(archive, "position", base.position);
	Json::GetUInt(archive, "createtime", base.create_time);
	Json::GetUInt(archive, "savetime", base.save_time);
	Json::GetUInt(archive, "savedby", base.saveby_uid);
	Json::GetUInt(archive, "protected", base.protected_time);
	Json::GetUInt(archive, "blat", base.last_active_time);
	Json::GetInt(archive, "damage", base.damage);
	Json::GetInt(archive, "destroyed", base.destroyed);
	Json::GetUInt64(archive, "empirevalue", base.value);
	Json::GetInt(archive, "flinger", base.attack_level);
	Json::GetInt(archive, "catapult", base.bomb_level);
	Json::ToString(archive, "updates", baseExtra.updates);
	Json::ToString(archive, "buildingdata", baseExtra.building);
	Json::ToString(archive, "effects", baseExtra.effect);
	Json::ToString(archive, "aiattacks", baseExtra.aiattack);
	Json::ToString(archive, "monsterbaiter", baseExtra.manoeuvre);
	Json::ToString(archive, "mushrooms", baseExtra.grower);
	Json::ToString(archive, "monsters", baseExtra.military);
	Json::ToString(archive, "champion", baseExtra.hero);
	Json::ToString(archive, "researchdata", baseExtra.recycle);
	Json::ToString(archive, "storedata", baseExtra.consume);
	if(IsValidUid(uid))
	{
		Json::GetInt(archive, "installsgenerated", user.invite_count);
		Json::GetUInt(archive, "lat", user.last_active_time);
		Json::GetInt(archive, "level", user.level);
		Json::GetUInt64(archive, "points", user.point);
		Json::GetUInt64(archive, "basevalue", user.value);
		Json::GetInt(archive, "tutorialstage", user.tutorial_stage);
		if(Json::IsObject(archive, "resources"))
		{
			const Json::Value &jsonResource = archive["resources"];
			Json::GetUInt(jsonResource, "r1", user.r1);
			Json::GetUInt(jsonResource, "r1max", user.r1_max);
			Json::GetUInt(jsonResource, "r2", user.r2);
			Json::GetUInt(jsonResource, "r2max", user.r2_max);
			Json::GetUInt(jsonResource, "r3", user.r3);
			Json::GetUInt(jsonResource, "r3max", user.r3_max);
			Json::GetUInt(jsonResource, "r4", user.r4);
			Json::GetUInt(jsonResource, "r4max", user.r4_max);
		}
		Json::GetInt(archive, "unreadmessages", user.unread_message);
		//Json::GetInt(archive, "world", user.world);
		Json::GetString(archive, "wfstatus", userExtra.wf_status);
		Json::ToString(archive, "stats", userExtra.stat);
		Json::ToString(archive, "academy", userExtra.technology);
		Json::ToString(archive, "lockerdata", userExtra.lock);
		Json::ToString(archive, "bookmarks", userExtra.bookmark);
		Json::ToString(archive, "quests", userExtra.quest);
	}

	CHECK_CALL(LogicBase::SetBase(base));
	CHECK_CALL(LogicBase::SetBaseExtra(baseExtra));
	if(IsValidUid(uid))
	{
		CHECK_CALL(LogicUser::SetUser(user));
		CHECK_CALL(LogicUser::SetUserExtra(userExtra));
	}
	return ret;
}

int CLogicArchive::Load(unsigned uid, unsigned baseid, unsigned uidLoadBy, LoadType type, Json::Value &archive)
{
	int ret;
	CLogicAlliance logicAlliance;
	CLogicInventory logicInventory;
	CLogicMessage logicMessage;
	CLogicUserInteract logicInteract;
	CLogicAttack logicAttack;
	DataArchive archiveLoad;
	DataUser userLoadBy;

	//NPC
	if(LogicNpc::IsNpc(baseid))
	{
		if(uid != uidLoadBy)
		{
			error_log("[attack_other_wf][uid=%u,userid=%u,baseid=%u]", uidLoadBy, uid, baseid);
			PARAM_ERROR_RETURN();
		}
		ret = LogicNpc::GetArchive(uid, baseid, type == LT_ATTACK, archive);
		if(ret != 0)
		{
			return ret;
		}
		ret = LogicUser::UpdateActiveTime(uidLoadBy);
		archive["currenttime"] = Time::GetGlobalTime();
		return ret;
	}

	ret = LogicBase::GetBase(uid, baseid, archiveLoad.Base);
	if(ret != 0)
	{
		return ret;
	}

	if(uid != archiveLoad.Base.uid)
	{
		///TODO: 前台加载世界野怪时需要传0
		//error_log("[user not base owner][action=load,uid=%u,quid=%u,baseid=%u,ruid=%u]",
		//		uidLoadBy, uid, baseid, archiveLoad.Base.uid);
		uid = archiveLoad.Base.uid;
	}

	ret = LogicUser::UpdateActiveTime(uidLoadBy);

	//正在被其他人攻击
	if(archiveLoad.Base.status == BS_FIGHT && archiveLoad.Base.saveby_uid != uidLoadBy &&
		Time::GetGlobalTime() - ATTACK_TIMEOUT < archiveLoad.Base.last_active_time)
	{
//		if(uidLoadBy == archiveLoad.Base.uid)
//		{
//			ret = logicUser.UpdateActiveTime(uidLoadBy, Time::GetGlobalTime() + LOGIN_PROTECT_TIME);
//			ERROR_RETURN_MSG(R_ERR_LOGIC, KEY_ERR_YOU_BEING_ATTACKED);
//		}
		ERROR_RETURN_MSG(R_ERR_LOGIC, KEY_ERR_BEING_ATTACKED);
	}

	//进攻条件检查
	if(type == LT_ATTACK)
	{
		//攻击自己
		if(uidLoadBy == uid)
		{
			error_log("[self_attack][action=load,uid=%u,userid=%u,baseid=%u]", uidLoadBy, uid, baseid);
			PARAM_ERROR_RETURN();
		}

		//保护
		if(IsInProtect(archiveLoad.Base.protected_time))
		{
			error_log("[being_protected][action=load,uid=%u,userid=%u,baseid=%u,protected=%u]",
					uidLoadBy, uid, archiveLoad.Base.baseid, archiveLoad.Base.protected_time);
			ERROR_RETURN_MSG(R_ERR_LOGIC, KEY_ERR_BEING_PROTECTED);
		}
	}
	else if(type == LT_HELP)
	{
		//帮助自己
		if(!IsUserBaseIndex(archiveLoad.Base.base_index) || uid == uidLoadBy)
		{
			error_log("[self help][uid=%d,uidby=%u,baseid=%u,base_index=%u]",
					uid, uidLoadBy, archiveLoad.Base.baseid, archiveLoad.Base.base_index);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "self_help");
		}
	}

	bool isMyMainBase = (uid == uidLoadBy && IsUserBaseIndex(archiveLoad.Base.base_index));
	bool isUser = IsUserBaseIndex(archiveLoad.Base.base_index);
	if(isUser && !IsValidUid(uid))
	{
		error_log("[invalid_base_owner][action=load,uid=%u,uidby=%u,baseid=%u,baseindex=%d]",
				uid, uidLoadBy, archiveLoad.Base.baseid, archiveLoad.Base.base_index);
		PARAM_ERROR_RETURN();
	}

	if(isUser)
	{
		ret = LogicUser::GetUser(uid, archiveLoad.User);
		if(ret != 0)
		{
			return ret;
		}

		if(type == LT_ATTACK)
		{
			//用户在线
			if(archiveLoad.User.last_active_time  + ONLINE_TIMEOUT > Time::GetGlobalTime())
			{
				error_log("[user_online][action=load,uid=%u,userid=%u,baseid=%u,lastactive=%u]",
						uidLoadBy, uid, archiveLoad.Base.baseid, archiveLoad.User.last_active_time);
				ERROR_RETURN_MSG(R_ERR_LOGIC, KEY_ERR_USER_ONLINE);
			}
		}

		ret = LogicUser::GetUserExtra(uid, archiveLoad.UserExtra);
		if(ret != 0)
		{
			return 0;
		}

		//冻结用户
		if(archiveLoad.User.status == US_BAN)
		{
			ERROR_RETURN_MSG(R_ERR_REFUSE, "being_blocked");
		}

		ret = LogicUserBasic::GetUserSmart(uid, OpenPlatform::GetType(), archiveLoad.UserBasic);
		if(ret != 0)
		{
			return ret;
		}

		if(IsAllianceId(archiveLoad.User.alliance_id))
		{
			ret = logicAlliance.GetAlliance(archiveLoad.User.alliance_id, archiveLoad.Alliance);
			if(ret != 0)
			{
				return ret;
			}
			ret = logicAlliance.GetMember(archiveLoad.Alliance.alliance_id, uid, archiveLoad.Member);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			archiveLoad.Alliance.alliance_id = ALLIANCE_ID_NULL;
			archiveLoad.Alliance.flag = 0;
		}
	}
	else
	{
		ret = LogicWorld::RefreshNpc(archiveLoad.Base);
		if(ret != 0)
		{
			return ret;
		}
	}

	ret = LogicBase::GetBaseExtra(archiveLoad.Base.baseid, archiveLoad.BaseExtra);
	if(ret != 0)
	{
		return ret;
	}

	if(Time::GetGlobalTime() > archiveLoad.Base.protected_time)
	{
		archiveLoad.Base.protected_time = 0;
	}

	//记录攻击信息
	if(isUser && type == LT_ATTACK)
	{
		//历史进攻标记已读
		ret = logicAttack.SetAttackRead(uidLoadBy, AT_ATTACK);

		//同联盟进攻
		ret = LogicUser::GetUser(uidLoadBy, userLoadBy);
		if(ret != 0)
		{
			return ret;
		}
		if(archiveLoad.User.world != userLoadBy.world)
		{
			error_log("[not_in_same_world][uid=%u,baseid=%u,uidby=%u,world=%d,worldBy=%d]",
					uid, baseid, uidLoadBy, archiveLoad.User.world, userLoadBy.world);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_same_world");
		}
		if(IsAllianceId(archiveLoad.User.alliance_id) && archiveLoad.User.alliance_id == userLoadBy.alliance_id)
		{
			error_log("[ban_alliance_attack][uid=%u,userid=%u,allianceId=%u,baseid=%u]",
					uidLoadBy, uid, userLoadBy.alliance_id, baseid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "ban_alliance_attack");
		}

		//记录进攻日志
		DataUserBasic userBasicLoadBy;
		ret = LogicUserBasic::GetUser(uidLoadBy, OpenPlatform::GetType(), userBasicLoadBy);
		if(ret != 0)
		{
			return ret;
		}
		DataAlliance allianceLoadBy;
		if(IsAllianceId(userLoadBy.alliance_id))
		{
			ret = logicAlliance.GetAlliance(userLoadBy.alliance_id, allianceLoadBy);
			if(ret != 0)
			{
				return ret;
			}
		}
		else
		{
			allianceLoadBy.alliance_id = ALLIANCE_ID_NULL;
			allianceLoadBy.flag = 0;
		}

		DataAttack attackData;
		attackData.attack_uid = uidLoadBy;
		attackData.defence_uid = uid;
		attackData.defence_baseid = archiveLoad.Base.baseid;
		attackData.attack_platform = userBasicLoadBy.platform;
		attackData.attack_user_name = userBasicLoadBy.name;
		attackData.attack_photo = userBasicLoadBy.figure_url;
		attackData.attack_alliance_id = allianceLoadBy.alliance_id;
		attackData.attack_alliance_name = allianceLoadBy.name;
		attackData.attack_alliance_flag = allianceLoadBy.flag;
		attackData.defence_platform = archiveLoad.UserBasic.platform;
		attackData.defence_user_name = archiveLoad.UserBasic.name;
		attackData.defence_photo = archiveLoad.UserBasic.figure_url;
		attackData.defence_base_name = archiveLoad.Base.base_name;
		attackData.defence_alliance_id = archiveLoad.Alliance.alliance_id;
		attackData.defence_alliance_name = archiveLoad.Alliance.name;
		attackData.defence_alliance_flag = archiveLoad.Alliance.flag;
		ret = logicAttack.AddAttack(attackData);
		if(ret != 0)
		{
			return ret;
		}

		//更新联盟动态
		if(attackData.attack_alliance_id != attackData.defence_alliance_id)
		{
			if(IsAllianceId(attackData.attack_alliance_id))
			{
				Json::Value attackActive;
				attackActive["type"] = "attack";
				attackActive["attackid"] = Convert::UInt64ToString(attackData.attack_id);
				attackActive["a_uid"] = attackData.attack_uid;
				attackActive["a_name"] = attackData.attack_user_name;
				attackActive["a_photo"] = attackData.attack_photo;
				attackActive["d_uid"] = attackData.defence_uid;
				attackActive["d_name"] = attackData.defence_user_name;
				attackActive["d_photo"] = attackData.defence_photo;
				if(IsAllianceId(attackData.defence_alliance_id))
				{
					attackActive["d_aid"] = attackData.defence_alliance_id;
					attackActive["d_aname"] = attackData.defence_alliance_name;
					attackActive["d_aflag"] = attackData.defence_alliance_flag;
				}
				ret = logicAlliance.AddActivity(allianceLoadBy, attackActive);
			}
			if(IsAllianceId(attackData.defence_alliance_id))
			{
				Json::Value defenceActive;
				defenceActive["type"] = "defence";
				defenceActive["attackid"] = Convert::UInt64ToString(attackData.attack_id);
				defenceActive["a_uid"] = attackData.attack_uid;
				defenceActive["a_name"] = attackData.attack_user_name;
				defenceActive["a_photo"] = attackData.attack_photo;
				if(IsAllianceId(attackData.attack_alliance_id))
				{
					defenceActive["a_aid"] = attackData.attack_alliance_id;
					defenceActive["a_aname"] = attackData.attack_alliance_name;
					defenceActive["a_aflag"] = attackData.attack_alliance_flag;
				}
				ret = logicAlliance.AddLastAttack(attackData.defence_alliance_id, attackData.defence_uid, defenceActive);

				defenceActive["d_uid"] = attackData.defence_uid;
				defenceActive["d_name"] = attackData.defence_user_name;
				defenceActive["d_photo"] = attackData.defence_photo;
				ret = logicAlliance.AddActivity(archiveLoad.Alliance, defenceActive);
			}
		}

		//设置连续进攻保护
		if(archiveLoad.Base.base_index == MAIN_BASE_ID)
		{
			archiveLoad.Base.protected_time = logicAttack.GetConAttackProtect(archiveLoad.User.uid, archiveLoad.Base.baseid);
		}
	}

	if(type == LT_ATTACK)
	{
		//记录攻击状态
		archiveLoad.Base.status = BS_FIGHT;
		archiveLoad.Base.saveby_uid = uidLoadBy;
		archiveLoad.Base.last_active_time = Time::GetGlobalTime();
		ret = LogicBase::SetBase(archiveLoad.Base);

		//取消攻击者保护
		DataBase baseLoadBy;
		ret = LogicBase::GetBase(uidLoadBy, MAIN_BASE_ID, baseLoadBy);
		if(ret != 0)
		{
			return ret;
		}
		if(baseLoadBy.protected_time > Time::GetGlobalTime())
		{
			baseLoadBy.protected_time = 0;
			if(baseLoadBy.status == BS_NEW)
			{
				baseLoadBy.status = BS_BUILD;
			}
			ret = LogicBase::SetBase(baseLoadBy);
			if(ret != 0)
			{
				return ret;
			}
		}

		//Weiyouxi
		if(OpenPlatform::GetType() == PT_WEIYOUXI)
		{
			Json::Value userExtraData;
			ret = LogicUser::GetExtraData(uidLoadBy, userExtraData);
			if(ret != 0)
			{
				return ret;
			}
			int attackStatus = 0;
			Json::GetInt(userExtraData, "as", attackStatus);
			if(attackStatus != 0)
			{
				userExtraData["as"] = 0;
				ret = LogicUser::SetExtraData(uidLoadBy, userExtraData);
			}
		}
	}
	else
	{
		//取消进攻状态
		if(archiveLoad.Base.status == BS_FIGHT)
		{
			archiveLoad.Base.status = BS_BUILD;
			ret = LogicBase::SetBase(archiveLoad.Base);
		}
	}

	if(isMyMainBase)
	{
		if(archiveLoad.User.world != 0)
		{
			ret = LogicBase::GetSubBasesJson(uid, archive["outposts"]);
			if(ret != 0)
			{
				return ret;
			}
		}

		CLogicPay logicPay;
		ret = logicPay.GetCash(uid, archiveLoad.Cash);
		if(ret != 0)
		{
			return ret;
		}
	}
	else
	{
		archiveLoad.Cash = 0;
	}

	ret = ArchiveToJson(archiveLoad, archive, isMyMainBase);
	if(ret != 0)
	{
		return ret;
	}

	if(isMyMainBase)
	{
		//读取防守消息
		vector<DataUserAttack> attacks;
		ret = logicAttack.GetUnreadAttacks(attacks, uid, AT_DEFENCE, archiveLoad.Base.baseid);
		if(ret == 0)
		{
			for(vector<DataUserAttack>::iterator itrAttack = attacks.begin(); itrAttack != attacks.end(); itrAttack++)
			{
				Json::Value attackData;
				attackData["userid"] = itrAttack->opposite_uid;
				attackData["starttime"] = itrAttack->start_time;
				attackData["log"] = "";
				DataUserBasic userAttack;
				ret = LogicUserBasic::GetUser(itrAttack->opposite_uid, (PlatformType)itrAttack->opposite_platform, userAttack);
				if(ret == 0)
				{
					attackData["fbid"] = userAttack.open_id;
					attackData["name"] = userAttack.name;
					attackData["pic_square"] = userAttack.figure_url;
					archive["attacks"].append(attackData);
				}
			}
		}
	}
	else if(type != LT_ATTACK)
	{
		//设置进攻许可
		ret = LogicUser::GetUser(uidLoadBy, userLoadBy);
		if(ret != 0)
		{
			return ret;
		}
		CLogicMap logicMap;
		int attackPermit = logicMap.GetAttackPermit(archiveLoad.User, archiveLoad.Base, userLoadBy);
		DataUserInteract userInteract;
		ret = logicInteract.GetInteract(uidLoadBy, uid, userInteract);
		if(ret == 0)
		{
			if(attackPermit == APT_BAN_LEVEL_LOW)
			{
				if(userInteract.retaliate_count > 0)
				{
					attackPermit = APT_ALLOW_REVENGE;
				}
			}
			if(Time::GetGlobalTime() < userInteract.truce_time)
			{
				attackPermit = APT_BAN_TRUCE;
			}
		}
		if(attackPermit == APT_BAN_LEVEL_LOW && IsAllianceId(userLoadBy.alliance_id))
		{
			ret = logicInteract.GetInteract(userLoadBy.alliance_id, uid, userInteract);
			if(ret == 0)
			{
				if(userInteract.retaliate_count > 0)
				{
					attackPermit = APT_ALLOW_ALLIANCE_REVENGE;
				}
			}
		}
		archive["attackpermitted"] = attackPermit;
	}

	if(isMyMainBase)
	{
		//系统消息
		if(archiveLoad.Base.base_index == MAIN_BASE_ID)
		{
			vector<DataMessage> msgVec;
			logicMessage.GetNewSysMessage(uid, msgVec);
			if (msgVec.size() > 0)
			{
				Json::Value &systemMessage = archive["sysmsg"];
				systemMessage.resize(msgVec.size());
				for (unsigned i = 0; i < msgVec.size(); i++)
				{
					Json::FromString(systemMessage[i], msgVec[i].content);
				}
			}
		}

		//inventory
		ret = logicInventory.GetItemsJson(uid, archive["inventory"]);

		//Weiyouxi
		if(OpenPlatform::GetType() == PT_WEIYOUXI)
		{
			Json::Value userExtraData;
			Json::FromString(userExtraData, archiveLoad.UserExtra.extra_data);
			int achvId;
			bool change = false;

			if(archiveLoad.User.invite_count > 0)
			{
				int lastInviteCount = 0;
				Json::GetInt(userExtraData, "lic", lastInviteCount);
				achvId = 0;
				if(lastInviteCount < 2)
				{
					if(archiveLoad.User.invite_count >= 2)
					{
						achvId = WYX_ACHIEVEMENT_INVITE_BASE + 1;
					}
				}
				else if(lastInviteCount < 5)
				{
					if(archiveLoad.User.invite_count >= 5)
					{
						achvId = WYX_ACHIEVEMENT_INVITE_BASE + 2;
					}
				}
				else if(lastInviteCount < 10)
				{
					if(archiveLoad.User.invite_count >= 10)
					{
						achvId = WYX_ACHIEVEMENT_INVITE_BASE + 3;
					}
				}
				else if(lastInviteCount < 30)
				{
					if(archiveLoad.User.invite_count >= 30)
					{
						achvId = WYX_ACHIEVEMENT_INVITE_BASE + 4;
					}
				}
				if(achvId > 0)
				{
					string openid;
					string openkey;
					if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
					{
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
					userExtraData["lic"] = archiveLoad.User.invite_count;
					change = true;
				}
			}

			uint64_t totalLootResource = 0;
			uint64_t lastTotalLootResource = 0;
			Json::GetUInt64(userExtraData, "tlr", totalLootResource);
			Json::GetUInt64(userExtraData, "ltlr", lastTotalLootResource);
			achvId = 0;
			if(lastTotalLootResource < 50000)
			{
				if(totalLootResource >= 50000)
				{
					achvId = WYX_ACHIEVEMENT_LOOT_BASE + 1;
				}
			}
			else if(lastTotalLootResource < 500000)
			{
				if(totalLootResource >= 500000)
				{
					achvId = WYX_ACHIEVEMENT_LOOT_BASE + 2;
				}
			}
			else if(lastTotalLootResource < 5000000)
			{
				if(totalLootResource >= 5000000)
				{
					achvId = WYX_ACHIEVEMENT_LOOT_BASE + 3;
				}
			}
			else if(lastTotalLootResource < 50000000)
			{
				if(totalLootResource >= 50000000)
				{
					achvId = WYX_ACHIEVEMENT_LOOT_BASE + 4;
				}
			}
			else if(lastTotalLootResource < 500000000)
			{
				if(totalLootResource >= 500000000)
				{
					achvId = WYX_ACHIEVEMENT_LOOT_BASE + 5;
				}
			}
			if(achvId > 0 || (totalLootResource - lastTotalLootResource) > 10000)
			{
				string openid;
				string openkey;
				if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
				{
					if(achvId > 0)
					{
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
					unsigned level = totalLootResource / 10000;
					if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(openid, openkey, WYX_LEADERBOARD_ATTACK_ID, level) != 0)
					{
						error_log("[set_leaderboard_fail][uid=%u,lid=%u,value=%u,error=%s]",
								uid, WYX_LEADERBOARD_ATTACK_ID, level, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
					}
				}
				userExtraData["ltlr"] = Convert::UInt64ToString(totalLootResource);
				change = true;
			}

			if(change)
			{
				ret = LogicUser::SetExtraData(uid, userExtraData);
			}
		}
	}

	archive["currenttime"] = Time::GetGlobalTime();

	return 0;
}

int CLogicArchive::Save(unsigned uid, unsigned baseid, unsigned uidSaveBy, const Json::Value &data, Json::Value &result)
{
	int ret;
	CLogicAlliance logicAlliance;
	DataUser userSave;
	DataUserExtra userExtraSave;
	DataBase baseSave;
	DataBaseExtra baseExtraSave;
	Json::Value userExtraData;

	result["needverify"] = LogicSso::Verify(uidSaveBy);

	//攻打NPC
//	if(LogicNpc::IsNpc(baseid))
//	{
//		if(uid != uidSaveBy)	//攻打他人野怪
//		{
//			error_log("[attack_other_wf][uid=%u,userid=%u,baseid=%u]", uidSaveBy, uid, baseid);
//			PARAM_ERROR_RETURN();
//		}
//
//		ret = LogicNpc::UpdateBase(uid, baseid, data, baseSave);
//		if(ret != 0)
//		{
//			return ret;
//		}
//
//		ret = UpdateAttack(uidSaveBy, uid, baseid, data);
//		if(ret != 0)
//		{
//			return ret;
//		}
//
//		result["baseid"] = baseSave.baseid;
//		result["basesaveid"] = baseSave.save_time;
//		result["currenttime"] = Time::GetGlobalTime();
//		return 0;
//	}

	ret = LogicBase::GetBase(uid, baseid, baseSave);
	if(ret != 0)
	{
		return ret;
	}
	if(uid != baseSave.uid)
	{
		//error_log("[user not base owner][action=save,uid=%u,quid=%u,baseid=%u,ruid=%u]",
		//		uidSaveBy, uid, baseid, baseSave.uid);
		uid = baseSave.uid;
	}
	if(!IsValidUid(uid) && IsUserBaseIndex(baseSave.base_index))
	{
		error_log("[invalid_base_owner][uid=%u,uidby=%u,baseid=%u,baseindex=%d]",
				uid, uidSaveBy, baseSave.baseid, baseSave.base_index);
		PARAM_ERROR_RETURN();
	}

	//检查basesaveid
	unsigned saveid;
	if(!Json::GetUInt(data, "basesaveid", saveid))
	{
		error_log("[not save id][uid=%u,userid=%u,baseid=%u]", uidSaveBy, uid, baseSave.baseid);
		PARAM_ERROR_RETURN();
	}
	if(saveid != baseSave.save_time)
	{
		error_log("[save id unequal][uid=%u,userid=%u,baseid=%u,saveid=%u,real_saveid=%u]",
				uidSaveBy, uid, baseSave.baseid, saveid, baseSave.save_time);
		PARAM_ERROR_RETURN();
	}
	bool isUserBase = (IsValidUid(uid) && IsUserBaseIndex(baseSave.base_index));
	bool isOwner = (uid == uidSaveBy && isUserBase);
	bool isMyMainBase = (isOwner && (baseSave.base_index == MAIN_BASE_ID));

	ret = LogicBase::GetBaseExtra(baseSave.baseid, baseExtraSave);
	if(ret != 0)
	{
		return ret;
	}

	if(isUserBase)
	{
		ret = LogicUser::GetUser(uid, userSave);
		if(ret != 0)
		{
			return ret;
		}
		int worldSaveBy;
		CHECK_CALL(LogicUser::GetWorld(uidSaveBy, worldSaveBy));
		if(worldSaveBy != userSave.world)
		{
			error_log("[not_in_same_world][uid=%u,baseid=%u,uidby=%u,world=%d,worldBy=%d]",
					uid, baseid, uidSaveBy, userSave.world, worldSaveBy);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_in_same_world");
		}
		ret = LogicUser::GetUserExtra(uid, userExtraSave);
		if(ret != 0)
		{
			return ret;
		}
		if(OpenPlatform::GetType() == PT_WEIYOUXI && isOwner)
		{
			Json::FromString(userExtraData, userExtraSave.extra_data);
		}
	}

	if(isOwner)
	{
		//build
		userSave.last_active_time = Time::GetGlobalTime();

		//inventory
		if(Json::IsObject(data, "inventory"))
		{
			CLogicInventory logicInventory;
			ret = logicInventory.ChangeItemsJson(uid, data["inventory"]);
			if(ret != 0)
			{
				return ret;
			}
		}

		//purchase
		unsigned cash = 0;
		if(Json::IsArray(data, "purchase"))
		{
			const Json::Value &purchase = data["purchase"];
			Json::Value consume;
			Json::FromString(consume, baseExtraSave.consume);
			ret = ProcessPurchase(userSave, userExtraSave, baseSave, purchase, cash, consume);
			if(ret != 0)
			{
				return ret;
			}
			baseExtraSave.consume = Json::ToString(consume);

			//Weiyouxi
			if(OpenPlatform::GetType() == PT_WEIYOUXI && isMyMainBase)
			{
				if(purchase.size() == 2)
				{
					string item = purchase[0u].asString();
					int mushroomCash = 0;
					if(item == "MUSHROOM1")
					{
						mushroomCash = 100;
					}
					else if(item == "MUSHROOM2")
					{
						mushroomCash = 100;
					}else{
						mushroomCash = 100;
					}
					if(mushroomCash > 0)
					{
						int totalMushroomCash = 0;
						Json::GetInt(userExtraData, "tmc", totalMushroomCash);
						mushroomCash += totalMushroomCash;
						userExtraData["tmc"] = mushroomCash;
						int achvId = 0;
						if(totalMushroomCash < 20)
						{
							if(mushroomCash >= 20)
							{
								achvId = WYX_ACHIEVEMENT_MUSHROOM_BASE + 1;
							}
						}
						else if(totalMushroomCash < 50)
						{
							if(mushroomCash >= 50)
							{
								achvId = WYX_ACHIEVEMENT_MUSHROOM_BASE + 2;
							}
						}
						else if(totalMushroomCash < 200)
						{
							if(mushroomCash >= 200)
							{
								achvId = WYX_ACHIEVEMENT_MUSHROOM_BASE + 3;
							}
						}
						else if(totalMushroomCash < 500)
						{
							if(mushroomCash >= 500)
							{
								achvId = WYX_ACHIEVEMENT_MUSHROOM_BASE + 4;
							}
						}
						if(achvId > 0)
						{
							string openid;
							string openkey;
							if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
							{
								if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
								{
									error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
											uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
								}
							}
						}
					}
				}
			}

		}
		else
		{
			CLogicPay logicPay;
			ret = logicPay.GetCash(uid, cash);
		}
		result["credits"] = cash;
		result["installsgenerated"] = userSave.invite_count;

		//alliance data
		if(IsAllianceId(userSave.alliance_id) && Json::IsObjectOrArray(data, "memberdata"))
		{
			CHECK_CALL(logicAlliance.SetAllianceData(uid, userSave.alliance_id, data["memberdata"]));
		}

		//clear attack message
		if(Json::IsArray(data, "attacks"))
		{
			if(data["attacks"].size() == 0)
			{
				CLogicAttack logicAttack;
				ret = logicAttack.SetAttackRead(uidSaveBy, AT_DEFENCE, baseSave.baseid);
			}
		}
	}
	else
	{
		//attack
		ret = UpdateAttack(uidSaveBy, uid, baseSave, data);
		if(ret != 0)
		{
			return ret;
		}

		if(isUserBase)
		{
			int damage;
			if(Json::GetInt(data, "damage", damage))
			{
				//联盟得分
				if(!IsMercenary() && damage > baseSave.damage)
				{
					DataUser userSaveBy;
					ret = LogicUser::GetUser(uidSaveBy, userSaveBy);
					if(ret == 0)
					{
						if(IsAllianceId(userSaveBy.alliance_id) && userSaveBy.alliance_id != userSave.alliance_id)
						{
							CLogicAlliance logicAlliance;
							ret = logicAlliance.AddAttackPoint(userSaveBy.alliance_id, uidSaveBy,
									damage - baseSave.damage, userSaveBy.level, userSave.level, baseSave.base_index == MAIN_BASE_ID);
						}
					}
				}

				//破坏保护
				if(baseSave.base_index == MAIN_BASE_ID)
				{
					if(damage >= 75)
					{
						baseSave.protected_time = Time::GetGlobalTime() + DAMAGE_PROTECT_NEW;
					}
				}
				else
				{
					if(damage >= 90)
					{
						baseSave.protected_time = 0;
					}
					else if(damage >= 25 && Time::GetGlobalTime() + DAMAGE_PROTECT_SUB_BASE > baseSave.protected_time)
					{
						if(Time::GetGlobalTime() + DAMAGE_PROTECT_SUB_BASE <= baseSave.protected_time + ATTACK_MAX_TIME)
						{
							baseSave.protected_time = Time::GetGlobalTime() + DAMAGE_PROTECT_SUB_BASE;
						}
						else
						{
							CLogicAttack logicAttack;
							if(logicAttack.GetAttackCount(uid, Time::GetGlobalTime() - (60 * 60),
									AT_DEFENCE, baseSave.baseid, uidSaveBy) >= 3)
							{
								baseSave.protected_time = Time::GetGlobalTime() + DAMAGE_PROTECT_SUB_BASE;
							}
						}
					}
				}
//				unsigned protectedTime = 0;
//				if(IsInAntiProtect(baseSave.protected_time))
//				{
//					if(damage >= 90)
//					{
//						baseSave.protected_time = Time::GetGlobalTime() + DAMAGE_PROTECT_LV2;
//					}
//				}
//				else
//				{
//					if(damage >= 75)
//					{
//						protectedTime = Time::GetGlobalTime() + DAMAGE_PROTECT_LV2;
//					}
//					else if(damage >= 50)
//					{
//						protectedTime = Time::GetGlobalTime() + DAMAGE_PROTECT_LV1;
//					}
//					if(protectedTime > baseSave.protected_time)
//					{
//						baseSave.protected_time = protectedTime;
//					}
//				}
			}
		}
	}

	Json::ToString(data, "buildingdata", baseExtraSave.building);
	Json::ToString(data, "effects", baseExtraSave.effect);
	Json::ToString(data, "mushrooms", baseExtraSave.grower);
	Json::ToString(data, "monsters", baseExtraSave.military);
	Json::ToString(data, "champion", baseExtraSave.hero);
	if(isOwner)
	{
		Json::ToString(data, "stats", userExtraSave.stat);
		Json::ToString(data, "quests", userExtraSave.quest);
		Json::ToString(data, "aiattacks", baseExtraSave.aiattack);
		Json::ToString(data, "monsterbaiter", baseExtraSave.manoeuvre);
		Json::ToString(data, "researchdata", baseExtraSave.recycle);
		if(isMyMainBase)
		{
			Json::ToString(data, "academy", userExtraSave.technology);
			Json::ToString(data, "lockerdata", userExtraSave.lock);
		}
		Json::ToString(data, "eggdata", userExtraSave.eggdata);
	}

	if(OpenPlatform::GetType() == PT_WEIYOUXI && isMyMainBase)
	{
		if(data.isMember("buildingdata"))
		{
			int lastCommandLevel = 0;
			Json::GetInt(userExtraData, "lcl", lastCommandLevel);
			if(Json::IsObject(data["buildingdata"], "1"))
			{
				int commandLevel;
				if(Json::GetInt(data["buildingdata"]["1"], "l", commandLevel))
				{
					if(commandLevel > lastCommandLevel && commandLevel % 2 == 0 &&
							commandLevel >= 4 && commandLevel <= 10)
					{
						int achvId = (commandLevel - 2) / 2 + WYX_ACHIEVEMENT_COMMAND_BASE;
						string openid;
						string openkey;
						if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
						{
							if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
							{
								error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
										uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
							}
						}
						userExtraData["lcl"] = commandLevel;
					}
				}
			}
		}
		if(data.isMember("lockerdata"))
		{
			//"id":{"t":2}
			//南瓜头C4，铁悟空C6，大黄蜂C14，蒙奇医生C15，破坏之王C12
			const Json::Value &jsonLock = data["lockerdata"];
			char locks[5][4] = {"C4", "C6", "C14", "C15", "C12"};
			Json::Value &lock = userExtraData["lock"];
			for(int i = 0; i < 5; i++)
			{
				int lastLockStatus = 0;
				if(!Json::GetInt(lock, i, lastLockStatus))
				{
					lock[i] = 0;
				}
				if(lastLockStatus == 0 && jsonLock.isMember(locks[i]))
				{
					int lockStatus;
					if(Json::GetInt(jsonLock[locks[i]], "t", lockStatus))
					{
						if(lockStatus == 2)
						{
							lock[i] = 1;
							int achvId = WYX_ACHIEVEMENT_LOCK_BASE + i + 1;
							string openid;
							string openkey;
							if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
							{
								if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
								{
									error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
											uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
								}
							}
						}
					}
				}
			}
		}
		if(data.isMember("quests"))
		{
			int lastCompleteQuest = 0;
			Json::GetInt(userExtraData, "lcq", lastCompleteQuest);
			int completeQuest = data["quests"].size();
			if(completeQuest > lastCompleteQuest)
			{
				userExtraData["lcq"] = completeQuest;
				if(completeQuest <= 30 && completeQuest % 10 == 0)
				{
					int achvId = completeQuest / 10 + WYX_ACHIEVEMENT_QUEST_BASE;
					string openid;
					string openkey;
					if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
					{
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
				}
			}
		}
	}

	uint64_t oldPoint = userSave.point + userSave.value;
	Json::GetInt(data, "baseseed", baseSave.seed);
	Json::GetInt(data, "damage", baseSave.damage);
	Json::GetInt(data, "destroyed", baseSave.destroyed);
	if(isUserBase)
	{
		Json::GetUInt64(data, "basevalue", userSave.value);
		Json::GetUInt64(data, "empirevalue", baseSave.value);
		Json::GetUInt64(data, "points", userSave.point);
		if(isOwner)
		{
			Json::GetInt(data, "flinger", baseSave.attack_level);
			Json::GetInt(data, "catapult", baseSave.bomb_level);
			if(isMyMainBase && userSave.world == 0)
			{
				Json::GetInt(data, "tutorialstage", userSave.tutorial_stage);
			}
		}
	}

	if(isUserBase)
	{
		uint64_t newPoint = userSave.point + userSave.value;
		if(IsMercenary() && IsAllianceId(userSave.alliance_id) && newPoint > oldPoint)
		{
			logicAlliance.UpdateMemberPoint(userSave.alliance_id, userSave.uid, newPoint);
		}

		unsigned lastUpdateId = 0;
		if(Json::GetUInt(data, "lastupdate", lastUpdateId))
		{
			Json::Value updates;
			Json::FromString(updates, baseExtraSave.updates);
			ret = LogicBase::ClearUpdates(lastUpdateId, updates);
			baseExtraSave.updates = Json::ToString(updates);
			result["updates"] = updates["updates"];
		}
	}

	if(isMyMainBase)
	{
		string email;
		if(Json::GetString(data, "email", email))
		{
			if(OpenPlatform::GetType() != PT_WEIYOUXI)
			{
				Json::FromString(userExtraData, userExtraSave.extra_data);
			}
			userExtraData["email"] = email;
			if(OpenPlatform::GetType() != PT_WEIYOUXI)
			{
				userExtraSave.extra_data = Json::ToString(userExtraData);
			}
		}
	}

	if((OpenPlatform::GetType() == PT_WEIYOUXI || (IsMercenary() && OpenPlatform::GetType() == PT_FACEBOOK)) && isMyMainBase)
	{
		unsigned updatePointTime = 0;
		Json::GetUInt(userExtraData, "upt", updatePointTime);
		uint64_t lastPoint = 0;
		Json::GetUInt64(userExtraData, "lpt", lastPoint);
		uint64_t currPoint = userSave.point + userSave.value;
		if(updatePointTime + 3600 < Time::GetGlobalTime() && (lastPoint / 10000) < (currPoint / 10000))
		{
			string openid;
			string openkey;
			int ret = LogicSso::GetOpenKey(uid, openid, openkey);
			if(ret == 0)
			{
				if(OpenPlatform::GetType() == PT_WEIYOUXI)
				{
					unsigned pointValue = currPoint / 10000;
					if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(
							openid, openkey, WYX_LEADERBOARD_POINT_ID, pointValue) != 0)
					{
						error_log("[set_leaderboard_fail][uid=%u,lid=%u,value=%u,error=%s]",
								uid, WYX_LEADERBOARD_LEVEL_ID, pointValue, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
					}
				}
				else
				{
					//TODO: Enable
//					if(((CFacebookPlatform *)OpenPlatform::GetPlatform())->SetScore(openid, openkey, currPoint) != 0)
//					{
//						error_log("[set_score_fail][uid=%u,value=%llu,error=%s]",
//								uid, currPoint, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
//					}
				}
				userExtraData["lpt"] = Convert::UInt64ToString(currPoint);
				userExtraData["upt"] = Time::GetGlobalTime();
			}
		}
	}

	if(Json::IsObject(data, "resources"))
	{
		const Json::Value &jsonResource = data["resources"];

		if(isUserBase)
		{
#define CHANGE_RESOURCE_MAX(res)	\
			int res = 0;	\
			if(Json::GetInt(jsonResource, #res, res))	\
			{	\
				if(res < 0 && userSave.res < (unsigned)(-res))	\
				{	\
					error_log("[not_enough_resource][uid=%u,resource=%u,change=%d]", uid, userSave.res, res);	\
					ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "not_enough_resource");	\
				}	\
				else	\
				{	\
					userSave.res += res;	\
				}	\
			}	\
			Json::GetUInt(data, #res "max", userSave.res##_max);	\

			CHANGE_RESOURCE_MAX(r1);
			CHANGE_RESOURCE_MAX(r2);
			CHANGE_RESOURCE_MAX(r3);
			CHANGE_RESOURCE_MAX(r4);

			if(OpenPlatform::GetType() == PT_WEIYOUXI && isOwner)
			{
				uint64_t harvest = 0;
				if(!Json::GetUInt64(userExtraData, "thr", harvest))
				{
					harvest = userSave.r1 + userSave.r2 + userSave.r3 + userSave.r4;
				}
				else
				{
					if(r1 > 0)
					{
						harvest += r1;
					}
					if(r2 > 0)
					{
						harvest += r2;
					}
					if(r3 > 0)
					{
						harvest += r3;
					}
					if(r4 > 0)
					{
						harvest += r4;
					}
				}
				unsigned updateHarvestTime = 0;
				Json::GetUInt(userExtraData, "uhrt", updateHarvestTime);
				uint64_t lastHarvest = 0;
				Json::GetUInt64(userExtraData, "lthr", lastHarvest);
				if(harvest > lastHarvest)
				{
					userExtraData["thr"] = Convert::UInt64ToString(harvest);
					if(updateHarvestTime + 3600 < Time::GetGlobalTime() && (lastHarvest / 10000) < (harvest / 10000))
					{
						string openid;
						string openkey;
						int ret = LogicSso::GetOpenKey(uid, openid, openkey);
						if(ret == 0)
						{
							unsigned harvestValue = harvest / 10000;
							if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(openid, openkey, WYX_LEADERBOARD_RESOURCE_ID, harvestValue) != 0)
							{
								error_log("[set_leaderboard_fail][uid=%u,lid=%u,value=%u,error=%s]",
										uid, WYX_LEADERBOARD_RESOURCE_ID, harvestValue, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
							}
							userExtraData["lthr"] = Convert::UInt64ToString(harvest);
							userExtraData["uhrt"] = Time::GetGlobalTime();
						}
					}
				}
			}
		}
		else
		{
			ret = LogicNpc::ChangeResource(uid, baseExtraSave, jsonResource);
			if(ret != 0)
			{
				return ret;
			}
		}
	}

	if(Time::GetGlobalTime() > baseSave.protected_time)
	{
		baseSave.protected_time = 0;
	}
	baseSave.saveby_uid = uidSaveBy;
	baseSave.last_active_time = Time::GetGlobalTime();
	if(baseSave.save_time < Time::GetGlobalTime())	//防重放
	{
		baseSave.save_time = Time::GetGlobalTime();
	}
	else
	{
		baseSave.save_time++;
	}

	if(IsValidUid(uid))
	{
		if(OpenPlatform::GetType() == PT_WEIYOUXI && isOwner)
		{
			userExtraSave.extra_data = Json::ToString(userExtraData);
		}
		ret = LogicUser::SetUserExtra(userExtraSave);
		if(ret != 0)
		{
			return ret;
		}
		ret = LogicUser::SetUser(userSave);
		if(ret != 0)
		{
			return ret;
		}
	}
	ret = LogicBase::SetBaseExtra(baseExtraSave);
	if(ret != 0)
	{
		return ret;
	}
	ret = LogicBase::SetBase(baseSave);
	if(ret != 0)
	{
		return ret;
	}

	result["baseid"] = baseSave.baseid;
	result["basesaveid"] = baseSave.save_time;
	result["currenttime"] = Time::GetGlobalTime();

	return 0;
}

int CLogicArchive::UpdateSave(unsigned uid, unsigned baseid, unsigned uidSaveBy, SaveType type, Json::Value &result)
{
	int ret;

	result["needverify"] = LogicSso::Verify(uidSaveBy);

	if(baseid == NPC_ADMIN_ID)
	{
		ret = LogicUser::UpdateActiveTime(uidSaveBy);
		result["currenttime"] = Time::GetGlobalTime();
		return 0;
	}

	DataBase base;
	ret = LogicBase::GetBase(uid, baseid, base);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA && uid == uidSaveBy && LogicNpc::IsNpc(baseid))
		{
			//未保存的NPC
			ret = LogicUser::UpdateActiveTime(uidSaveBy);
			result["currenttime"] = Time::GetGlobalTime();
			return 0;
		}
		return ret;
	}
	if(uid != base.uid)
	{
		//error_log("[user not base owner][action=updatesave,uid=%u,quid=%u,baseid=%u,ruid=%u]",
		//		uidSaveBy, uid, baseid, base.uid);
		uid = base.uid;
	}

	DataUser userSaveBy;
	ret = LogicUser::GetUser(uidSaveBy, userSaveBy);
	if(ret != 0)
	{
		return ret;
	}

	if(type == ST_ATTACK)
	{
		if(base.status != BS_FIGHT ||
			base.baseid == userSaveBy.main_base_id ||
			base.saveby_uid != uidSaveBy)
		{
			error_log("[base_status_error][action=updatesave,uid=%u,userid=%u,baseid=%u,status=%d,main_baseid=%u,saveby_uid=%u]",
					uidSaveBy, uid, baseid, base.status, userSaveBy.main_base_id, base.saveby_uid);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "base_status_error");
		}
		ret = LogicBase::UpdateActiveTime(base.baseid);
	}
	else if(type == ST_BUILD)
	{
		if(uid != uidSaveBy || !IsUserBaseIndex(base.base_index))
		{
			error_log("[build_other_base][action=updatesave,uid=%u,userid=%u,baseid=%u,baseindex=%u]",
					uidSaveBy, uid, base.baseid, base.base_index);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "not_base_owner");
		}
		ret = LogicBase::UpdateActiveTime(base.baseid);
	}

	ret = LogicUser::UpdateActiveTime(uidSaveBy);

	if(type == ST_BUILD)
	{
		CLogicPay logicPay;
		unsigned cash;
		ret = logicPay.GetCash(uidSaveBy, cash);
		if(ret != 0)
		{
			return ret;
		}
		result["credits"] = cash;
		CLogicInventory logicInventory;
		ret = logicInventory.GetItemsJson(uid, result["inventory"]);
		result["unreadmessages"] = userSaveBy.unread_message;
	}

	if(type == ST_BUILD || type == ST_HELP)
	{
		ret = LogicBase::GetUpdates(base.baseid, result["updates"]);
	}

	//LogicUser::GetResourcesJson(userSaveBy, result["resources"]);

	result["currenttime"] = Time::GetGlobalTime();

	return 0;
}

int CLogicArchive::SaveUpdate(unsigned uid, unsigned baseid, unsigned uidSaveBy, const Json::Value &data, Json::Value &result)
{
	int ret;

	if(uid == uidSaveBy)
	{
		error_log("[self_help][uid=%d,baseid=%u,updates=%s]", uid, baseid, Json::ToString(data).c_str());
		ERROR_RETURN_MSG(R_ERR_LOGIC, "self_help");
	}

	string type;
	if(!data.isArray() || data.size() != 1)
	{
		error_log("[operate_data_error][uid=%u,userid=%u,baseid=%u,data=%s]",
				uidSaveBy, uid, baseid, Json::ToString(data).c_str());
		PARAM_ERROR_RETURN();
	}
	const Json::Value &dataItem = data[0u];
	if(!dataItem.isArray() || dataItem.size() < 2 || !Json::GetString(dataItem, 1, type))
	{
		error_log("[operate_data_error][uid=%u,userid=%u,baseid=%u,data=%s]",
				uidSaveBy, uid, baseid, Json::ToString(data).c_str());
		PARAM_ERROR_RETURN();
	}

	DataBase base;
	ret = LogicBase::GetBase(uid, baseid, base);
	if(ret != 0)
	{
		if(ret == R_ERR_NO_DATA)
		{
			error_log("[operate_base_not_exist][uid=%u,userid=%u,baseid=%u,data=%s]",
				uidSaveBy, uid, baseid, Json::ToString(data).c_str());
		}
		return ret;
	}
	if(!IsUserBaseIndex(base.base_index))
	{
		error_log("[help_not_user][uid=%u,userid=%u,baseid=%u,baseindex=%d,data=%s]",
				uidSaveBy, uid, baseid, base.base_index, Json::ToString(data).c_str());
		PARAM_ERROR_RETURN();
	}
	if(uid != base.uid)
	{
		//error_log("[user not base owner][action=operate,uid=%u,quid=%u,baseid=%u,ruid=%u]", uidSaveBy, uid, baseid, base.uid);
		uid = base.uid;
	}

	ret = LogicUser::UpdateActiveTime(uidSaveBy);

	CLogicUserInteract logicUserInteract;
	if(type == "BH" || type == "BUNK" || type == "BAR")
	{
		//检查好友关系
		if(!LogicFriend::IsFriend(uidSaveBy, OpenPlatform::GetType(), uid))
		{
			CLogicAlliance logicAlliance;
			if(!logicAlliance.IsInSameAlliance(uidSaveBy, uid))
			{
				error_log("[user_no_relation][uid=%u,userid=%u,baseid=%u]", uidSaveBy, uid, baseid);
				ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "param_error");
			}
		}

		if(IsMercenary())
		{
			ret = logicUserInteract.AddFriendInteract(uidSaveBy, uid, type);
			if(ret != 0)
			{
				return ret;
			}
		}
	}
	else
	{
		error_log("[unknow_operate][uid=%u,userid=%u,baseid=%u,data=%s]",
				uidSaveBy, uid, baseid,  Json::ToString(data).c_str());
	}

	ret = LogicBase::AddUpdate(uid, base.baseid, uidSaveBy, data, &result["updates"]);
	if(ret != 0)
	{
		return ret;
	}

	if(type == "BH")
	{
		ret = logicUserInteract.AddHelp(uidSaveBy, uid);

		//Weiyouxi
		if(OpenPlatform::GetType() == PT_WEIYOUXI)
		{
			Json::Value userExtraData;
			ret = LogicUser::GetExtraData(uidSaveBy, userExtraData);
			if(ret == 0)
			{
				int totalHelpCount = 0;
				Json::GetInt(userExtraData, "thc", totalHelpCount);
				totalHelpCount++;
				int achvId = 0;
				if(totalHelpCount == 5)
				{
					achvId = WYX_ACHIEVEMENT_HELP_BASE + 1;
				}
				else if(totalHelpCount == 50)
				{
					achvId = WYX_ACHIEVEMENT_HELP_BASE + 2;
				}
				else if(totalHelpCount == 100)
				{
					achvId = WYX_ACHIEVEMENT_HELP_BASE + 3;
				}
				else if(totalHelpCount == 500)
				{
					achvId = WYX_ACHIEVEMENT_HELP_BASE + 4;
				}
				if(achvId > 0)
				{
					string openid;
					string openkey;
					if(LogicSso::GetOpenKey(uidSaveBy, openid, openkey) == 0)
					{
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uidSaveBy, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
				}
				userExtraData["thc"] = totalHelpCount;
				ret = LogicUser::SetExtraData(uidSaveBy, userExtraData);
			}
		}
	}
	else if(type == "BUNK")
	{
		if(!IsMercenary())
		{
			error_log("[unknow_operate][uid=%u,userid=%u,baseid=%u,data=%s]",
					uidSaveBy, uid, baseid, Json::ToString(data).c_str());
			PARAM_ERROR_RETURN();
		}

		//减少兵
		if(dataItem.size() < 5 || !dataItem[4u].isObject())
		{
			error_log("[operate_bunk_data_error][uid=%u,userid=%u,baseid=%u,data=%s]",
					uidSaveBy, uid, baseid, Json::ToString(data).c_str());
			PARAM_ERROR_RETURN();
		}
		const Json::Value &armyData = dataItem[4u];
		int totalSend = 0;
		map<string, int> armyChange;
		Json::Value::Members keys = armyData.getMemberNames();
		for(Json::Value::Members::iterator itr = keys.begin(); itr != keys.end(); itr++)
		{
			unsigned changeCount;
			if(!Json::GetUInt(armyData, itr->c_str(), changeCount))
			{
				error_log("[operate_bunk_data_illegal][uid=%u,userid=%u,baseid=%u,data=%s]",
					uidSaveBy, uid, baseid, Json::ToString(data).c_str());
				PARAM_ERROR_RETURN();
			}
			armyChange[*itr] = -((int)changeCount);
			totalSend += changeCount;
		}
		if(totalSend > 0)
		{
			ret = LogicBase::ChangeArmy(uidSaveBy, MAIN_BASE_ID, armyChange);
			if(ret != 0)
			{
				return ret;
			}
			ret = logicUserInteract.ChangeInteractStat(uidSaveBy, "tts", totalSend);
		}
		if(dataItem.size() >= 6)
		{
			int r4Add = 0;
			Json::GetInt(dataItem, 5, r4Add);
			if(r4Add > 0)
			{
				ret = LogicUser::ChangeResource(uidSaveBy, 0, 0, 0, r4Add);
			}
		}
	}
	else if(type == "BAR")
	{
		if(!IsMercenary())
		{
			error_log("[unknow_operate][uid=%u,userid=%u,baseid=%u,data=%s]",
					uidSaveBy, uid, baseid, Json::ToString(data).c_str());
			PARAM_ERROR_RETURN();
		}
	}

	result["currenttime"] = Time::GetGlobalTime();

	return 0;
}

int CLogicArchive::UpdateAttack(unsigned uid, unsigned uidDefence, const DataBase &baseDefence, const Json::Value &data)
{
	int ret;
	DataUser user;
	Json::Value userExtraData;
	ret = LogicUser::GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	bool isUser = (IsValidUid(uidDefence) && IsUserBaseIndex(baseDefence.base_index));
	if(OpenPlatform::GetType() == PT_WEIYOUXI && isUser)
	{
		ret = LogicUser::GetExtraData(uid, userExtraData);
		if(ret != 0)
		{
			return ret;
		}
	}

	if(Json::IsObject(data, "lootreport"))
	{
		if(isUser)
		{
			//更新进攻历史
			DataAttack attackData;
			attackData.attack_uid = uid;
			attackData.attack_platform = OpenPlatform::GetType();
			attackData.defence_uid = uidDefence;
			attackData.defence_baseid = baseDefence.baseid;
			attackData.r1_loot = 0;
			attackData.r2_loot = 0;
			attackData.r3_loot = 0;
			attackData.r4_loot = 0;
			const Json::Value &jsonResource = data["lootreport"];
			Json::GetInt(jsonResource, "r1", attackData.r1_loot);
			Json::GetInt(jsonResource, "r2", attackData.r2_loot);
			Json::GetInt(jsonResource, "r3", attackData.r3_loot);
			Json::GetInt(jsonResource, "r4", attackData.r4_loot);
			Json::GetString(data, "attackreport", attackData.log);

			CLogicAttack logicAttack;
			ret = logicAttack.UpdateAttack(attackData);
		}
	}

	//更新资源
	if(Json::IsObject(data, "attackloot"))
	{
		const Json::Value &jsonResource = data["attackloot"];

#define CHANGE_RESOURCE(res)	\
		int res = 0;	\
		if(Json::GetInt(jsonResource, #res, res))	\
		{	\
			if(res < 0 && user.res < (unsigned)(-res))	\
			{	\
				error_log("[not_enough_resource][uid=%u," #res "=%u,change=%d]", uid, user.res, res);	\
				ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "not_enough_resource");	\
			}	\
			else	\
			{	\
				user.res += res;	\
			}	\
		}	\

		CHANGE_RESOURCE(r1);
		CHANGE_RESOURCE(r2);
		CHANGE_RESOURCE(r3);
		CHANGE_RESOURCE(r4);

		if(OpenPlatform::GetType() == PT_WEIYOUXI && isUser)
		{
			uint64_t totalLootResource = 0;
			Json::GetUInt64(userExtraData, "tlr", totalLootResource);
			if(r1 > 0)
			{
				totalLootResource += r1;
			}
			if(r2 > 0)
			{
				totalLootResource += r2;
			}
			if(r3 > 0)
			{
				totalLootResource += r3;
			}
			if(r4 > 0)
			{
				totalLootResource += r4;
			}
			userExtraData["tlr"] = Convert::UInt64ToString(totalLootResource);
		}
	}
	else
	{
		error_log("[key_not_found][uid=%u,baseid=%u,key=attackloot]", uid, baseDefence.baseid);
	}

	user.last_active_time = Time::GetGlobalTime();
	ret = LogicUser::SetUser(user);
	if(ret != 0)
	{
		return ret;
	}

	if(OpenPlatform::GetType() == PT_WEIYOUXI && isUser)
	{
		int attackStatus = 0;
		int totalAttackProtect1 = 0;
		int totalAttackProtect2 = 0;
		Json::GetInt(userExtraData, "as", attackStatus);
		Json::GetInt(userExtraData, "tap1", totalAttackProtect1);
		Json::GetInt(userExtraData, "tap2", totalAttackProtect2);
		int lastTotalAttackProtect1 = totalAttackProtect1;
		int damage;
		if(attackStatus < 2 && Json::GetInt(data, "damage", damage))
		{
			if(damage >= 75)
			{
				if(attackStatus == 0)
				{
					totalAttackProtect1++;
					totalAttackProtect2++;
				}
				else if(attackStatus == 1)
				{
					totalAttackProtect2++;
				}
				attackStatus = 2;
			}
			else if(damage >=50)
			{
				if(attackStatus == 0)
				{
					totalAttackProtect1++;
					attackStatus = 1;
				}
			}

			int achvId = 0;
			if(totalAttackProtect1 > lastTotalAttackProtect1)
			{
				if(totalAttackProtect1 == 5)
				{
					achvId = WYX_ACHIEVEMENT_ATTACK_BASE + 1;
				}
				else if(totalAttackProtect1 == 30)
				{
					achvId = WYX_ACHIEVEMENT_ATTACK_BASE + 2;
				}
				else if(totalAttackProtect1 == 100)
				{
					achvId = WYX_ACHIEVEMENT_ATTACK_BASE + 3;
				}
				else if(totalAttackProtect1 == 200)
				{
					achvId = WYX_ACHIEVEMENT_ATTACK_BASE + 4;
				}
				if(achvId > 0)
				{
					string openid;
					string openkey;
					if(LogicSso::GetOpenKey(uid, openid, openkey) == 0)
					{
						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
						{
							error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
									uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
						}
					}
				}
			}
			userExtraData["as"] = attackStatus;
			userExtraData["tap1"] = totalAttackProtect1;
			userExtraData["tap2"] = totalAttackProtect2;
		}
		ret = LogicUser::SetExtraData(uid, userExtraData);
	}

	//更新野怪状态
	if(LogicNpc::IsWildForce(baseDefence.base_index))
	{
		int destroyed;
		if(Json::GetInt(data, "destroyed", destroyed))
		{
			if(destroyed == 1)
			{
				ret = LogicNpc::SetNpcStatus(uid, baseDefence.base_index, NS_PASS);
				if(ret != 0)
				{
					return ret;
				}
			}
		}
	}

	DataBaseExtra baseExtra;
	if(user.world == 0)
	{
		ret = LogicBase::GetBaseExtra(user.main_base_id, baseExtra);
		if(ret != 0)
		{
			return ret;
		}
		if(Json::IsObject(data, "attackcreatures"))
		{
			baseExtra.military = Json::ToString(data["attackcreatures"]);
		}
		if(Json::IsObject(data, "attackerchampion"))
		{
			baseExtra.hero = Json::ToString(data["attackerchampion"]);
		}
		ret = LogicBase::SetBaseExtra(baseExtra);
		if(ret != 0)
		{
			return ret;
		}
	}
	else
	{
		if(Json::IsArray(data, "monsterupdate"))
		{
			CHECK_CALL(LogicBase::UpdateMilitary(uid, data["monsterupdate"]));
		}
		if(Json::IsObject(data, "attackerchampion"))
		{
			CHECK_CALL(LogicBase::SetHero(user.main_base_id, data["attackerchampion"]));
		}
	}

	return 0;
}

int CLogicArchive::ProcessPurchase(DataUser &user, DataUserExtra &userExtra, DataBase &base, const Json::Value &purchase, unsigned &cash, Json::Value &consume)
{
	int ret;
	if(purchase.size() < 2)
	{
		error_log("[unknow_purchase][uid=%u,baseid=%u,data=%s]",
				base.uid, base.baseid, Json::FastWriter().write(purchase).c_str());
		PARAM_ERROR_RETURN();
	}
	string item = purchase[0u].asString();
	int count = purchase[1u].asInt();
	bool useInventory = false;
	bool useInteractPoint = false;
	if(purchase.size() >= 3)
	{
		if(purchase[2u].asString() == "inv=1")
		{
			useInventory = true;
		}
		else if(purchase[2u].asString() == "rp=1")
		{
			useInteractPoint = true;
		}
	}

	int lastCount = 0;
	if(consume.type() != Json::objectValue)
	{
		consume = Json::Value(Json::objectValue);
	}
	if(consume.isMember(item))
	{
		lastCount = consume[item]["q"].asInt();
	}
	consume[item]["q"] = lastCount + count;

	//攻击保护
	if(item.find("PRO") == 0)
	{
		unsigned protectTime = 0;
		if(item == "PRO1")
		{
			protectTime = 1 * 24 * 60 * 60;
		}
		else if(item == "PRO2")
		{
			protectTime = 7 * 24 * 60 * 60;
		}
		else if(item == "PRO3")
		{
			protectTime = 28 * 24 * 60 * 60;
		}
		if(protectTime != 0)
		{
			if(IsInProtect(base.protected_time))
			{
				base.protected_time += protectTime;
			}
			else
			{
				base.protected_time = Time::GetGlobalTime() + protectTime;
			}
		}
	}
	else if(item == "GAC")
	{
		userExtra.gate_extra_times += BUY_DARE_TIMES_PER_COUNT * count;
	}

	int cashUse = 0;
	if(item == "MUSHROOM1")
	{
		if(IsMercenary())
		{
			cashUse = -1;
		}
		else if(OpenPlatform::GetType() == PT_MOBAGE)
		{
			cashUse = 100;
		}
		else
		{
			cashUse = -3;
		}
	}
	else if(item == "MUSHROOM2")
	{
		if(IsMercenary())
		{
			cashUse = -2;
		}
		else if(OpenPlatform::GetType() == PT_MOBAGE)
		{
			cashUse = 100;
		}
		else
		{
			cashUse = -8;
		}
	}
	else if(item == "MUSHROOM3")
	{
		if(IsMercenary())
		{
			cashUse = -3;
		}
		else if(OpenPlatform::GetType() == PT_MOBAGE)
		{
			cashUse = 100;
		}
	}
	else if(item == "MUSHROOM4")
	{
		if(OpenPlatform::GetType() == PT_MOBAGE)
		{
			cashUse = 100;
		}
	}
	else if(item == "MUSHROOM5")
	{
		if(OpenPlatform::GetType() == PT_MOBAGE)
		{
			cashUse = 100;
		}
	}
	else if(item == "QINVITE1")
	{
		cashUse = -25;
	}
	else if(item == "QINVITE5")
	{
		cashUse = -45;
	}
	else if(item == "QINVITE10")
	{
		cashUse = -65;
	}
	else if(item == "GAC")
	{
		cashUse = 20;
	}
	else
	{
		const Json::Value &storeItems = App::GetParams();
		if(storeItems.isMember(item))
		{
			const Json::Value &price = storeItems[item]["c"];

			//持续时间
			unsigned duration = storeItems[item]["du"].asUInt();
			if(duration != 0)
			{
				consume[item]["e"] = Time::GetGlobalTime() + duration;
			}

			//计算价格
			if(price.size() == 0)
			{
				error_log("[store_item_error][uid=%u,baseid=%u,item=%s]",
						base.uid, base.baseid, item.c_str());
				DATA_ERROR_RETURN_MSG("storeitem_error");
			}
			else if(price.size() == 1)
			{
				if(price[0u].asInt() == 1)
				{
					cashUse = count;
				}
				else
				{
					if(count != 1)
					{
						error_log("[count_error][uid=%u,baseid=%u,item=%s,count=%d]",
								base.uid, base.baseid, item.c_str(), count);
						PARAM_ERROR_RETURN();
					}
					cashUse = price[0u].asInt();
				}
			}
			else
			{
				if(count != 1)
				{
					error_log("[count_error][uid=%u,baseid=%u,item=%s,count=%d]",
							base.uid, base.baseid, item.c_str(), count);
					PARAM_ERROR_RETURN();
				}
				if(lastCount < (int)price.size())
				{
					cashUse = price[lastCount].asInt();
				}
				else
				{
					error_log("[store_item_limit][uid=%u,baseid=%u,item=%s,last_count=%d]",
							base.uid, base.baseid, item.c_str(), lastCount);
					DATA_ERROR_RETURN_MSG("store_item_limit");
				}
			}
		}
		else
		{
			if(count < 0)
			{
				error_log("[invalid_purchase_count][uid=%u,item=%s,count=%d]", base.uid, item.c_str(), count);
				PARAM_ERROR_RETURN_MSG("purchase_count_error");
			}
			bool unknowPurchase = true;
			static char s_consumeItems[][20] = {
					"BRTOPUP", "IU", "ITR", "BUNK", "IUN",
					"IEV", "IHE", "PBALL", "PBUY", "IFD",
					"RSIGN", "BDPRO", "QSKP", "TECHSPCL"
			};
			static char s_revenueItems[][20] = { "DFRW", "BASEHARV", "QUEST" };
			if(String::StartWith(item, "BUILDING") || String::StartWith(item, "BUYBUILD"))
			{
				cashUse = count;
				unknowPurchase = false;
			}
			for(size_t i = 0; i < COUNT_OF(s_consumeItems) && unknowPurchase; i++)
			{
				if(item == s_consumeItems[i])
				{
					cashUse = count;
					unknowPurchase = false;
				}
			}
			if(String::StartWith(item, "PAYRW"))
			{
				cashUse = -count;
				unknowPurchase = false;
			}
			for(size_t i = 0; i < COUNT_OF(s_revenueItems) && unknowPurchase; i++)
			{
				if(item == s_revenueItems[i])
				{
					cashUse = -count;
					unknowPurchase = false;
				}
			}
			if(unknowPurchase)
			{
				error_log("[unknow_purchase_type][uid=%u,data=%s]", base.uid, Json::ToString(purchase).c_str());
				cashUse = count;
			}
		}
	}

	CLogicPay logicPay;
	if(useInventory)
	{
		CLogicInventory logicInventory;
		ret = logicInventory.ChangeItem(base.uid, item, -count);
		if(ret != 0)
		{
			return ret;
		}
		DATA_INFO_LOG("useinventory", "uid=%u&item=%s&count=%d", base.uid, item.c_str(), count);
		ret = logicPay.GetCash(base.uid, cash);
	}
	else if(useInteractPoint)
	{
		DATA_INFO_LOG("rpbuy", "uid=%u&item=%s&count=%d", base.uid, item.c_str(), count);
		ret = logicPay.GetCash(base.uid, cash);
	}
	else
	{
		if((OpenPlatform::GetType() == PT_TEST || OpenPlatform::GetType() ==PT_MOBAGE)&&(
				item == "MUSHROOM3"||
				item == "MUSHROOM1" ||
				item == "MUSHROOM2" ||
				item == "MUSHROOM4" ||
				item == "MUSHROOM5") )
		{
			cashUse = -100;
		}
		ret = logicPay.ChangeCash(base.uid, item,  -cashUse, count, base.base_index, cash);
		if(ret != 0)
		{
			return ret;
		}
	}

	//Weiyouxi Achievement
	if(OpenPlatform::GetType() == PT_WEIYOUXI)
	{
		if(item == "BEW" && lastCount >= 1)
		{
			int achvId = lastCount + WYX_ACHIEVEMENT_WORKER_BASE;
			string openid;
			string openkey;
			if(LogicSso::GetOpenKey(base.uid, openid, openkey) == 0)
			{
				if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, achvId) != 0)
				{
					error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
							base.uid, achvId, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
				}
			}
		}
	}

	return 0;
}

int CLogicArchive::ArchiveToJson(const DataArchive &dataArchive, Json::Value &data, bool isMyMainBase)
{

#define STRING_TO_JSON_REQUIRED(table, field, key)	\
	if(!Json::FromString(data[key], dataArchive.table.field))	\
	{	\
		error_log("[" #field "_parse_error][uid=%u,baseid=%u,baseindex=%d]",	\
				dataArchive.User.uid, dataArchive.Base.baseid, dataArchive.Base.base_index);	\
		DATA_ERROR_RETURN_MSG(#field "_data_error");	\
	}	\

#define STRING_TO_JSON_OPTIONAL(table, field, key)	\
	if(dataArchive.table.field.empty() || !Json::FromString(data[key], dataArchive.table.field))	\
		error_log("[" #field "_parse_error][uid=%u,baseid=%u,baseindex=%d]",	\
				dataArchive.User.uid, dataArchive.Base.baseid, dataArchive.Base.base_index)	\

	STRING_TO_JSON_REQUIRED(BaseExtra, building, "buildingdata");
	STRING_TO_JSON_OPTIONAL(BaseExtra, effect, "effects");
	STRING_TO_JSON_OPTIONAL(BaseExtra, grower, "mushrooms");
	STRING_TO_JSON_OPTIONAL(BaseExtra, military, "monsters");
	STRING_TO_JSON_OPTIONAL(BaseExtra, hero, "champion");

	if(IsUserBaseIndex(dataArchive.Base.base_index))
	{
		Json::Value userExtraData;
		Json::FromString(userExtraData, dataArchive.UserExtra.extra_data);

		if(isMyMainBase)
		{
			if(dataArchive.Base.base_index == MAIN_BASE_ID)
			{
				data["tutorialstage"] = dataArchive.User.tutorial_stage;
				data["gatelefttimes"] = dataArchive.UserExtra.gate_left_times + dataArchive.UserExtra.gate_extra_times;
				if(dataArchive.User.world == 0)
				{
					data["wfstatus"] = dataArchive.UserExtra.wf_status;
				}
				else
				{
					STRING_TO_JSON_OPTIONAL(UserExtra, bookmark, "bookmarks");
				}
			}
			data["installsgenerated"] = dataArchive.User.invite_count;
			data["unreadmessages"] = dataArchive.User.unread_message;

			STRING_TO_JSON_OPTIONAL(UserExtra, quest, "quests");

			if(Json::IsObject(userExtraData, "istat"))
			{
				data["istat"] = userExtraData["istat"];
			}
			unsigned lvt = 0;
			Json::GetUInt(userExtraData, "lvt", lvt);
			unsigned totm = 0;
			if(Time::IsToday(lvt))
			{
				Json::GetUInt(userExtraData, "totm", totm);
			}
			data["totalonline"] = totm;

			STRING_TO_JSON_OPTIONAL(BaseExtra, aiattack, "aiattacks");
			STRING_TO_JSON_OPTIONAL(BaseExtra, manoeuvre, "monsterbaiter");
			STRING_TO_JSON_OPTIONAL(BaseExtra, recycle, "researchdata");
		}

		data["userid"] = dataArchive.UserBasic.uid;
		data["game"] = (int)Kernel::GetGameType();
		data["pt"] = dataArchive.UserBasic.platform;
		data["fbid"] = dataArchive.UserBasic.open_id;
		data["name"] = dataArchive.UserBasic.name;
		data["pic_square"] = dataArchive.UserBasic.figure_url;
		data["viptype"] = dataArchive.UserBasic.vip_type;
		data["viplevel"] = dataArchive.UserBasic.vip_level;

		data["level"] = dataArchive.User.level;
		data["points"] = Convert::UInt64ToString(dataArchive.User.point);
		data["basevalue"] = Convert::UInt64ToString(dataArchive.User.value);
		data["lat"] = dataArchive.User.last_active_time;
		LogicUser::GetResourcesJson(dataArchive.User, data["resources"]);

		STRING_TO_JSON_OPTIONAL(UserExtra, stat, "stats");
		STRING_TO_JSON_OPTIONAL(UserExtra, lock, "lockerdata");
		STRING_TO_JSON_OPTIONAL(UserExtra, technology, "academy");
		STRING_TO_JSON_OPTIONAL(UserExtra, eggdata, "eggdata");

		string email;
		if(Json::GetString(userExtraData, "email", email))
		{
			data["email"] = email;
		}
		else if(!dataArchive.UserBasic.extra_data.empty())
		{
			Json::Value userBasicExtraData;
			if(Json::FromString(userBasicExtraData, dataArchive.UserBasic.extra_data))
			{
				if(Json::GetString(userBasicExtraData, "email", email))
				{
					data["email"] = email;
				}
			}
		}

		STRING_TO_JSON_OPTIONAL(BaseExtra, consume, "storedata");

		Json::Value updates;
		if(Json::FromString(updates, dataArchive.BaseExtra.updates))
		{
			if(updates.isObject() && Json::IsArray(updates, "updates"))
			{
				data["updates"] = updates["updates"];
			}
		}
		else
		{
			error_log("[updates_parse_error][uid=%u,baseid=%u,baseindex=%d]",
					dataArchive.User.uid, dataArchive.Base.baseid, dataArchive.Base.base_index);
		}

		data["baseid"] = dataArchive.Base.baseid;
		data["baseindex"] = dataArchive.Base.base_index;
		data["basename"] = dataArchive.Base.base_name;
		data["baseseed"] = dataArchive.Base.seed;
		data["createtime"] = dataArchive.Base.create_time;
		data["savetime"] = dataArchive.Base.save_time;
		data["savedby"] = dataArchive.Base.saveby_uid;
		data["protected"] = dataArchive.Base.protected_time;
		data["blat"] = dataArchive.Base.last_active_time;

		if(IsAllianceId(dataArchive.User.alliance_id))
		{
			Json::Value &alliance = data["alliance"];
			alliance["id"] = dataArchive.Alliance.alliance_id;
			alliance["name"] = dataArchive.Alliance.name;
			alliance["flag"] = dataArchive.Alliance.flag;;
			Json::FromString(alliance["data"], dataArchive.Alliance.extra_data);
			Json::Value &member = alliance["member"];
			member["type"] = dataArchive.Member.type;
			member["point"] = Convert::UInt64ToString(dataArchive.Member.point);
			Json::FromString(member["data"], dataArchive.Member.extra_data);
		}

		data["credits"] = dataArchive.Cash;
	}
	else
	{
		data["baseid"] = dataArchive.Base.baseid;
		data["npcid"] = dataArchive.Base.base_index;
		data["savetime"] = dataArchive.Base.save_time;
		data["saveby"] = dataArchive.Base.saveby_uid;
		data["blat"] = dataArchive.Base.last_active_time;
		Json::Value extraData;
		if(Json::FromString(extraData, dataArchive.BaseExtra.extra_data))
		{
			data["resources"] = extraData["resources"];
		}
	}

	if(dataArchive.Base.position != 0)
	{
		CWorldPoint point(dataArchive.Base.position);
		data["world"] = point.World;
		data["x"] = point.X;
		data["y"] = point.Y;
		data["terrain"] = LogicWorld::GetTerrain(dataArchive.Base.position);
	}

	return 0;
}

