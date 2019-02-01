/*
 * CgiPointsRank.cpp
 *
 *  Created on: 2012-10-17
 *      Author: Administrator
 */

#include "LogicInc.h"
#include "LogicQQPay.h"
#include "stdlib.h"
#include "LogicCMD.h"
#define EXCHANGE_CODE_NOT_EXISIT 3
#define EXCHANGE_CODE_USED 2
#define USER_EXCHANGED_BEFORE 1
#define EXCHANGED_SUCCESS 0;
#define EXCHANGE_CODE_OUT_OF_DATE 4
#define EXCHANGE_CODE_TYPE_MAX 64
class CCgiActivity : public CCgiBase
{
public:

	CCgiActivity() : CCgiBase("activity")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("getqixijiedata", GetQixijieData)
	//CGI_SET_ACTION_MAP("updateqixijiedata", UpdateQixijieData)
	CGI_SET_ACTION_MAP("gethundreddaysactivityrank", GetHundredDaysActivityRank)
	CGI_SET_ACTION_MAP("getpointsrank", GetPointsRank)
	CGI_SET_ACTION_MAP("updatepointsrank", UpdatePointsRank)
	CGI_SET_ACTION_MAP("getpointsrankAllServer", GetPointsRankAllServer)
	CGI_SET_ACTION_MAP("updatepointsrankAllServer", UpdatePointsRankAllServer)
	CGI_SET_ACTION_MAP("exchange", Exchange)
	CGI_SET_ACTION_MAP("getbarbairanrank", GetBarbairanRank)
	CGI_SET_ACTION_MAP("ranklist", GetTopTenUser)
	CGI_SET_ACTION_MAP("viewMysticalShop", ViewMysticalShop)
	CGI_SET_ACTION_MAP("buyMysticalShop", BuyMysticalShop)
	CGI_SET_ACTION_MAP("getgodfb", GetGodFB)
	CGI_SET_ACTION_MAP("viewboat", ViewBoat)
	CGI_SET_ACTION_MAP("getboat", GetBoat)
	CGI_SET_ACTION_MAP("setboat", SetBoat)
	CGI_SET_ACTION_MAP("hitboat", HitBoat)
	CGI_SET_ACTION_MAP("updateboatlog", UpdateBoatAttackLog)
	CGI_SET_ACTION_MAP("qqpanel", ReqQQPanel)
	CGI_SET_ACTION_MAP("getrechargealliancedata", GetRechargellianceData)
	CGI_SET_ACTION_MAP("updaterechargealliancedata", UpdateRechargellianceData)
	CGI_SET_ACTION_MAP("getvipchagrgedata", GetVipChargeData)
	CGI_SET_ACTION_MAP("updatevipchagrgedata", UpdataVipChargeData)
	CGI_SET_ACTION_MAP("getbarbariankingrank", GetbarBarianKingRank)
	CGI_SET_ACTION_MAP("getvipyearchagrgedata", GetVipYearChargeData)
	CGI_SET_ACTION_MAP("updatevipyearchagrgedata", UpdataVipYearChargeData)
	CGI_SET_ACTION_MAP("getdailyfirstchargedata", GetDailyFirstChargeData)
	CGI_SET_ACTION_MAP("gethequaccchargedata", GetHequAccChargeData)
	CGI_SET_ACTION_MAP("getalliancepoint", GetAlliancePoint)
	CGI_SET_ACTION_MAP("getworldattack", GetWorldAttack)
	CGI_SET_ACTION_MAP("getviprebatesdata", GetVipRebatesData)
	CGI_SET_ACTION_MAP("getsrchargerebatesdata", GetSRChargeRebatesData)
	CGI_SET_ACTION_MAP("gethequchanganactivity", GetHequChanganActivity)
	CGI_SET_ACTION_MAP("getlrchargerebatesdata", GetLRChargeRebatesData)
	CGI_SET_ACTION_MAP("getopenareaselfdata", GetOpenAreaSelfData)
	CGI_SET_ACTION_MAP("updateopenareaselfdata", UpdateOpenAreaSelfData)
	CGI_SET_ACTION_MAP("getgalleryaccchargedata", GetGalleryAccChargeData)
	CGI_SET_ACTION_MAP("genewlotterydata", GetNewLotteryData)
//	CGI_SET_ACTION_MAP("setqqgamedingtou", SetQQGameDingTou)
	CGI_SET_ACTION_MAP("getconsumeranklist", GetConsumeRankList)
	CGI_SET_ACTION_MAP("getRechargeRanklist", GetRechargeRankList)
	CGI_SET_ACTION_MAP("getrestriction", GetRestriction)
//  CGI_SET_ACTION_MAP("updaterestriction", UpdateRestriction)
	CGI_SET_ACTION_MAP("DragonScaleActive", DragonScaleActive)
	CGI_SET_ACTION_MAP("getHammerHitList", GetHammerHitList)
	CGI_SET_ACTION_MAP("GetCrowdFunding", GetCrowdFunding)
	CGI_SET_ACTION_MAP("BuyCrowdFunding", BuyCrowdFunding)
	CGI_SET_ACTION_MAP("GetLords", GetLords)
	CGI_SET_ACTION_MAP("GetRankList", GetRankList)
	CGI_SET_ACTION_MAP("RotaryTableInfo", RotaryTableInfo)
	CGI_SET_ACTION_MAP("getchongzhizixuan", getchongzhizixuan)
	CGI_SET_ACTION_MAP("getbeautyinfo", GetBeautyInfo)
	CGI_SET_ACTION_MAP("InvestmentInfo", InvestmentInfo)
	CGI_SET_ACTION_MAP("GetHequbuchangLevel", GetHequbuchangLevel)
	CGI_ACTION_MAP_END

	int GetQixijieData()
	{
		int ret = 0;
		CLogicQixijie qixiRank;

	    ret = qixiRank.GetQixiActivityRankJson(m_uid,m_jsonResult["qixiactivityRank"]);
		if(ret != 0)
		{
			error_log("get ranklist failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getqixiactivityrank&uid=%u", m_uid);
		return R_SUCCESS;
	}

/*
	int UpdateQixijieData()
	{
		int ret = 0;
		CLogicQixijie qixiRank;
		int unsigned uid;

		ret = qixiRank.UpdateQixiActivityRank(m_uid,m_data,m_jsonResult["qixiResult"]);
		if(ret != 0)
		{
			error_log("update ranklist failed uid = %u",m_uid);
			return ret;
		}

		int prize = m_jsonResult["qixiResult"]["mark_reward"].asInt();
		debug_log("qixichoujiang  uid=%u,mark_reward=%d",m_uid,prize);

		CGI_SEND_LOG("action=updateqixiactivityrank&uid=%u", m_uid);
		return R_SUCCESS;

	}
*/

	int GetHundredDaysActivityRank()
	{
		int ret = 0;
		CLogicHundredDaysActivityRank pointsRank;

		 ret = pointsRank.GetHundredDaysActivityRankJson(m_uid,m_jsonResult["hdaysactivityRank"]);
		 if(ret != 0)
		 {
			 error_log("get ranklist failed uid = %u",m_uid);
			 return ret;
		 }
		CGI_SEND_LOG("action=gethundreddaysactivityrank&uid=%u", m_uid);
		return R_SUCCESS;

	}


	int GetPointsRank()
	{
		int ret = 0;
		CLogicPointsRank pointsRank;
		int unsigned uid;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		 ret = pointsRank.GetPointsRankJson(uid,m_jsonResult["pointsRank"]);
		 if(ret != 0)
		 {
			 error_log("get ranklist failed uid = %u",uid);
			 return ret;
		 }
		CGI_SEND_LOG("action=getpointsrank&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpdatePointsRank()
	{
		int unsigned  uid;
		DataPoints points;
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		int ret = 0;
		CLogicPointsRank pointsRank;
		if(!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		if(!Json::GetUInt(m_data, "points", points.points))
		{
			PARAM_ERROR_RETURN_MSG("check_points_fail");
		}
		logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);
		points.uid = uid;
		memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);
		ret = pointsRank.UpdatePointsRank(uid,points);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=updatepointsrank&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetPointsRankAllServer()
	{
		int ret = 0;
		CLogicPointsRank pointsRank;
		int unsigned uid;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		 ret = pointsRank.GetPointsRankJson(uid,m_jsonResult["pointsRank"]);
		 if(ret != 0)
		 {
			 error_log("get ranklist failed uid = %u",uid);
			 return ret;
		 }
		CGI_SEND_LOG("action=getpointsrank&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpdatePointsRankAllServer()
	{
		int unsigned  uid;
		DataPoints points;
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		int ret = 0;
		CLogicPointsRank pointsRank;
		if(!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		if(!Json::GetUInt(m_data, "points", points.points))
		{
			PARAM_ERROR_RETURN_MSG("check_points_fail");
		}
		logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);
		points.uid = uid;
		memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);
		ret = pointsRank.UpdatePointsRank(uid,points);
		if(ret != 0)
		{
			return ret;
		}
		CGI_SEND_LOG("action=updatepointsrank&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int Exchange()
	{
		unsigned uid;
		string exchangeCode;
		if(!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		if(!Json::GetString(m_data, "exchangecode", exchangeCode) || exchangeCode.empty())
		{
			//uid = m_uid;
			return R_ERR_PARAM;
		}

		int length = exchangeCode.length();
		if (length <= CODE_SIZE)
		{
			error_log("[exchangeCode length error][length=%d]",length);
			return R_ERR_PARAM;
		}
		int type_len = exchangeCode.length() - CODE_SIZE;
		if (type_len <= 0)
			return R_ERR_PARAM;
		int iType = atoi(exchangeCode.substr(0,type_len).c_str());

		CLogicExchangeCode logicChangeCode;
		DataExchangeCode dataExchangeCode;
		CLogicPromotionMapping logicPromotionMapping;
		DataPromotionMapping dataPromotionMapping;
		dataExchangeCode.code = exchangeCode.substr(type_len,length - type_len);
		//error_log("[exchangeCode][length=%d,typelen=%d,code=%s]",length,type_len,dataExchangeCode.code.c_str());
		unsigned now = Time::GetGlobalTime();
		int ret = logicChangeCode.GetExchangeCode(dataExchangeCode);
		if(ret != 0)
		{
			m_jsonResult["result"] = EXCHANGE_CODE_NOT_EXISIT;
			return 0;
		}
		if(dataExchangeCode.type != iType)
		{
			m_jsonResult["result"] = EXCHANGE_CODE_NOT_EXISIT;
			return 0;
		}
		if(dataExchangeCode.deadline < now)
		{
			m_jsonResult["result"] = EXCHANGE_CODE_OUT_OF_DATE;
			return 0;
		}
		if(dataExchangeCode.usetime != 0)  // 该兑换码已被使用
		{
			m_jsonResult["result"] = EXCHANGE_CODE_USED;
			return 0;
		}

		if(iType <= EXCHANGE_CODE_TYPE_MAX)
		{
			dataPromotionMapping.uid = uid;
			dataPromotionMapping.useflag = 0;
			ret = logicPromotionMapping.GetPromotionMapping(dataPromotionMapping);
			if(!(ret == R_SUCCESS || ret == R_ERR_NO_DATA))
			{
				return ret;
			}
			if(ret == R_SUCCESS)   // 推广用户
			{
				if(dataPromotionMapping.useflag & iType)    //用户以领取过奖励
				{
					m_jsonResult["result"] = USER_EXCHANGED_BEFORE;
					return 0;
				}
				dataPromotionMapping.useflag |= iType;
				dataPromotionMapping.usetime = Time::GetGlobalTime();
				logicPromotionMapping.SetPromotionMapping(dataPromotionMapping);
			}else{                      //非推广用户
				dataPromotionMapping.useflag |= iType; //登记领取类型标记
				dataPromotionMapping.usetime = now;
				dataPromotionMapping.pid = 0;
				logicPromotionMapping.AddPromotionMapping(dataPromotionMapping);
			}
		}

		dataExchangeCode.usetime = now;
		dataExchangeCode.uid = uid;
		logicChangeCode.SetExchangeCode(dataExchangeCode);
		m_jsonResult["result"] = EXCHANGED_SUCCESS;
		m_jsonResult["type"] = iType;
		return 0;
	}
	int GetBarbairanRank()
	{

		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		CLogicUser logicUser;
		DataUser user;
		int ret = logicUser.GetUserLimit(uid,user);
		if(0 != ret)
		{
			error_log("get user limit failed uid=%u, ret=%d",uid, ret);
			return ret;
		}
		int i = 0;
		CLogicBarbarianInvasion  logicBarbarianInvasion;
		DataPlayersPoints playersRank;
		memset(&playersRank,0x00,sizeof(DataPlayersPoints));
		DataTeamItem teamRank[512];
		memset(teamRank,0x00,sizeof(teamRank));
		int teamNum = 0;
		ret = logicBarbarianInvasion.GetTeamRank(teamRank,teamNum);
		if(0 != ret)
		{
			error_log("get TeamPlayersRank failed uid=%u",uid);
			return ret;
		}
		if(IsAllianceId(user.alliance_id))
		{
			ret = logicBarbarianInvasion.GetTeamPlayersRank(playersRank,user.alliance_id);
			if(0 != ret)
			{
				error_log("get TeamPlayersRank failed uid=%u",uid);
				return ret;
			}
			for(i = 0; i < playersRank.playerNum; i++)
			{
				m_jsonResult["barbairanplayersrank"][i]["uid"]= playersRank.players[i].uid;
				m_jsonResult["barbairanplayersrank"][i]["points"]= playersRank.players[i].points;
				m_jsonResult["barbairanplayersrank"][i]["name"]= playersRank.players[i].name;
				m_jsonResult["barbairanplayersrank"][i]["level"]= playersRank.players[i].rewardCash;
			}
		}
		for(i = 0; i < teamNum; i++)
		{
			m_jsonResult["barbairanteamrank"][i]["aid"]= teamRank[i].aid;
			m_jsonResult["barbairanteamrank"][i]["kingdom"]= teamRank[i].kingdom;
			m_jsonResult["barbairanteamrank"][i]["teampoints"]= teamRank[i].teamPoints;
			m_jsonResult["barbairanteamrank"][i]["name"]= teamRank[i].aname;
		}
		return 0;
	}

	int GetTopTenUser()
	{
		CLogicTopTenUser logicTopTenUser;
		DataTopTenUser topUser;
		int ret = logicTopTenUser.GetInfo(topUser);
		if(0 != ret)
		{
			return ret;
		}
		Json::Value data;
		Json::Value dataLevel = Json::Value(Json::arrayValue);
		Json::Value dataDehp = Json::Value(Json::arrayValue);
		Json::Value dataLoot = Json::Value(Json::arrayValue);
		CDataUserBasic dbUser;
		string userName;
		CLogicHero logicHero;
		Json::Value heroData;
		for (int i=0; i<10; i++)
		{
			if(IsValidUid(topUser.userLevel[i].uid))
			{
				userName.clear();
				ret = dbUser.GetUserName(topUser.userLevel[i].uid, OpenPlatform::GetType(), userName);
				if(0 == ret)
				{
					Json::Value &tempData = dataLevel[dataLevel.size()];
					tempData["uid"] = topUser.userLevel[i].uid;
					tempData["lvl"] = topUser.userLevel[i].level;
					tempData["name"] = userName;
				}
			}

			if(IsValidUid(topUser.userPlunder[i].uid))
			{
				userName.clear();
				ret = dbUser.GetUserName(topUser.userPlunder[i].uid, OpenPlatform::GetType(), userName);
				if (0 == ret)
				{
					Json::Value &tempData = dataLoot[dataLoot.size()];
					tempData["uid"] = topUser.userPlunder[i].uid;
					tempData["loot"] = topUser.userPlunder[i].plunder;
					tempData["name"] = userName;
				}
			}

			if(IsValidUid(topUser.heroPower[i].uid))
			{
				userName.clear();
				heroData.clear();
				ret = logicHero.GetHero(topUser.heroPower[i].uid, heroData);
				if (0 == ret)
				{
					ret = dbUser.GetUserName(topUser.heroPower[i].uid, OpenPlatform::GetType(), userName);
					if (0 == ret)
					{
						Json::Value &tempData = dataDehp[dataDehp.size()];
						tempData["uid"] = topUser.heroPower[i].uid;
						tempData["power"] = topUser.heroPower[i].power;
						tempData["name"] = userName;
						for (int j=0; j<heroData.size(); ++j)
						{
							int def = 0;
							if (Json::GetInt(heroData[j], "def", def) && (1 == def))
							{
								tempData["id"] = heroData[j]["id"];
							}
						}
					}
				}
			}
		}
		m_jsonResult["loot"] = dataLoot;
		m_jsonResult["hero"] = dataDehp;
		m_jsonResult["user"] = dataLevel;
		return 0;
	}
	int ViewMysticalShop()
	{

		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}

		CLogicUser logicUser;
		DataUser user;
		int ret = logicUser.GetUserLimit(uid,user);
		if(0 != ret)
		{
			error_log("get user limit failed uid=%u, ret=%d",uid, ret);
			return ret;
		}
		int i = 0;
		CLogicMysticalShop logicMysticalShop;
		DataEquipItem dataEquipItem[512];
		DataEquipSells dataEquipSells[512];
		memset(&dataEquipItem,0x00,sizeof(DataEquipItem));
		memset(&dataEquipSells,0x00,sizeof(DataEquipItem));

		// 初始化商店
		ret = logicMysticalShop.InitMysticalShop();
		int equipNum = 0;
		ret = logicMysticalShop.GetTopEquipNum(dataEquipItem, equipNum);
		if(0 != ret)
		{
			error_log("get TopEquipNum failed uid=%u",uid);
			return ret;
		}
		string rangeTime = Config::GetValue(CONFIG_MYSTICALSHOP_RANGE_TS);
		Json::Value value;
		Json::Reader().parse(rangeTime, value);
		m_jsonResult["mysticalTime"] = value;

		//int equipNum = 3;
		for(i = 0; i < equipNum; i++)
		{

			m_jsonResult["mysticalshop"][i]["eid"]= dataEquipItem[i].eid;
			m_jsonResult["mysticalshop"][i]["price"]= dataEquipItem[i].price;
			m_jsonResult["mysticalshop"][i]["num"]= dataEquipItem[i].nums;
		}

		// 添加信息栏
		int buyNums;
		ret = logicMysticalShop.GetInfobuys(dataEquipSells, buyNums);
		for (int i=0; i<buyNums; i++)
		{
			m_jsonResult["mysticalBuys"][i]["uid"] = dataEquipSells[i].uid;
			m_jsonResult["mysticalBuys"][i]["eid"] = dataEquipSells[i].buy_Equip.eid;
			m_jsonResult["mysticalBuys"][i]["time"] = dataEquipSells[i].buy_time;
			m_jsonResult["mysticalBuys"][i]["price"] = dataEquipSells[i].buy_Equip.price;
			m_jsonResult["mysticalBuys"][i]["name"] = dataEquipSells[i].name;
		}

		return 0;
	}

	int BuyMysticalShop()
	{
		unsigned uid = 0;
		unsigned eid = 0;
		string name = "";

		Json::GetUInt(m_data, "uid", uid);
		Json::GetUInt(m_data, "eid", eid);
		Json::GetString(m_data, "name", name);

		CLogicMysticalShop logicMysticalShop;
		int ret = logicMysticalShop.PayMysticalEquip(uid, name, eid, m_jsonResult);

		if (0  == ret)
		{
			m_jsonResult["mysticalshopBuyType"] = 0;
		}
		else
		{
			m_jsonResult["mysticalshopBuyType"] = -1;
		}

		return 0;
	}
	int GetGodFB()
	{
		int ret = 0;
		unsigned uid = 0;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}
		CLogicWeapon logicWeapon;
		ret = logicWeapon.GetWeapon(uid, m_jsonResult);
		if (0 != ret)
		{
			return ret;
		}
		return 0;
	}

	int GetBoat()
	{
		int ret = 0;
		CLogicRiver logicRiver;
		unsigned userid;
		if(Json::GetUInt(m_data, "userid", userid))
		{
			Json::Value boats;
			logicRiver.GetShipJson(userid, boats);
			if (0 != ret)
				return ret;
			m_jsonResult["boats"][(unsigned)0] = boats;
			CGI_SEND_LOG("action=GetBoat&operated=%u&operator=%u",userid,m_uid);
		}
		else
		{
			ret = logicRiver.GetAllShipJson(m_jsonResult["boats"]);
			if (0 != ret)
				return ret;
		}
		return 0;
	}

	int SetBoat()
	{
		int ret = 0;
		unsigned uid;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}
		if (!m_data.isMember("data"))
		{
			PARAM_ERROR_RETURN_MSG("data");
		}

		CLogicRiver logicRiver;
		ret = logicRiver.SetShip(uid, m_data["data"]);
		if (0 != ret)
		{
			return ret;
		}
		unsigned userid = 0;
		Json::GetUInt(m_data["data"], "uid", userid);
		CGI_SEND_LOG("action=SetBoat&operated=%u&operator=%u",userid,m_uid);
		return 0;
	}

	int HitBoat()
	{
		unsigned uid;
		if(!Json::GetUInt(m_data["data"], "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}

		unsigned type;
		if(!Json::GetUInt(m_data["data"], "type", type))
		{
			PARAM_ERROR_RETURN_MSG("type");
		}

		unsigned torch;
		if(!Json::GetUInt(m_data["data"], "torch", torch))
		{
			PARAM_ERROR_RETURN_MSG("torch");
		}

		unsigned classType;
		if(!Json::GetUInt(m_data["data"], "classType", classType))
		{
			PARAM_ERROR_RETURN_MSG("classType");
		}

		unsigned win;
		if(!Json::GetUInt(m_data["data"], "win", win))
		{
			PARAM_ERROR_RETURN_MSG("win");
		}

		CLogicRiver logicRiver;
		int ret = logicRiver.HitShip(m_uid, m_data["data"],m_jsonResult["result"]);
		if (0 != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=HitBoat&operated=%u&operator=%u",uid,m_uid);
		return 0;
	}

	int ViewBoat()
	{
		int ret = 0;
		unsigned uid;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}

		CLogicRiver logicRiver;
		ret = logicRiver.GetAllShipJson(m_jsonResult["boats"]);
		if (0 != ret)
		{
			return ret;
		}

		ret = logicRiver.GetAttackLog(uid, m_jsonResult["log"]);
		if (0 != ret)
		{
			return ret;
		}
		return 0;
	}

	int UpdateBoatAttackLog()
	{
		int ret = 0;
		unsigned uid;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}

		if (!m_data.isMember("log"))
		{
			PARAM_ERROR_RETURN_MSG("log");
		}
		CLogicRiver logicRiver;
		ret = logicRiver.SetAttackLog(uid, m_data["log"]);
		if (0 != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=UpdateBoatAttackLog&operated=%u&operator=%u",uid,m_uid);
		return 0;
	}

	int ReqQQPanel()
	{
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN();
		}
		string openkey;
		if(!Json::GetString(m_data, "openkey", openkey))
		{
			PARAM_ERROR_RETURN();
		}
		string pf = "qzone";
		string pfkey;
		if(!Json::GetString(m_data, "pfkey", pfkey))
		{
			PARAM_ERROR_RETURN();
		}
		string appid;
		if(!Json::GetString(m_data, "appid", appid))
		{
			PARAM_ERROR_RETURN();
		}

		CLogicQQPay logicQQPay;
		int ret = logicQQPay.ReqQQPanel(pf, pfkey, openid, openkey, m_ipstr, appid);
		if(ret == 0)
			m_jsonResult["qqpanel"] = 1;
		else
			m_jsonResult["qqpanel"] = 0;
		CGI_SEND_LOG("action=ReqQQPanel&uid=%u&ret=%u",m_uid,ret);
		return 0;
	}

	int GetRechargellianceData()
	{
		int ret = 0;
		CLogicRechargeAlliance recharge;

		ret = recharge.GetRechargeAllianceData(m_uid,m_jsonResult["recharge"]);
		if(ret != 0)
		{
			error_log("get rechargealliancedata failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getrechargealliancedata&uid=%u", m_uid);
		return R_SUCCESS;

	}

	int UpdateRechargellianceData()
	{
		return 0;//改为跨服架构---ralf 20140101

		unsigned uid=0,aid=0,coin=0;
		string name;
		if(!Json::GetUInt(m_data, "uid", uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}
		if(!Json::GetUInt(m_data, "aid", aid))
		{
			PARAM_ERROR_RETURN_MSG("aid");
		}
		if(!Json::GetUInt(m_data, "coin", coin))
		{
			PARAM_ERROR_RETURN_MSG("coin");
		}
		if(!Json::GetString(m_data, "name", name))
		{
			PARAM_ERROR_RETURN_MSG("name");
		}
		int ret = 0;
		CLogicRechargeAlliance logicRecharge;

		AllianceMember recharge;
		recharge.uid = uid;
		recharge.cash = coin;
		strcpy(recharge.name,name.c_str());

		ret = logicRecharge.UpdateRechargeAllianceData(aid,recharge);
		if(ret != 0)
		{
			error_log("[update recharge alliance fail][uid=%d,ret=%d,cash=%d]", uid, ret, coin);
			return ret;
		}
		CGI_SEND_LOG("action=UpdateRechargellianceData&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetVipChargeData()
	{
		int ret = 0;

		int total = 0;
		int used = 0;
		unsigned updatetime = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN_MSG("openid");
		}

		CDataVipCharge charge;
		ret = charge.GetVipCharge(openid,total,used,updatetime);
		if(ret != 0){
			return ret;
		}

		m_jsonResult["total"] = total;
		m_jsonResult["used"] = used;
		CGI_SEND_LOG("action=GetVipChargeData&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpdataVipChargeData()
	{
		int ret = 0;

		int total = 0;
		int used = 0;
		unsigned updatetime = 0;
		string openid;
		int useScore = 0;
		if(!Json::GetString(m_data, "openid", openid) || !Json::GetInt(m_data, "useScore", useScore))
		{
			PARAM_ERROR_RETURN_MSG("openid_or_useScore");
		}

		CDataVipCharge charge;
		ret = charge.GetVipCharge(openid,total,used,updatetime);
		if(ret != 0){
			return ret;
		}

		if(total < used+useScore)
		{
			return R_ERR_REFUSE;
		}

		used = used + useScore;
		ret = charge.UpdateVipChargeUsed(openid,total,used);
		if(ret != 0){
			return ret;
		}

		m_jsonResult["total"] = total;
		m_jsonResult["used"] = used;
		CGI_SEND_LOG("action=UpdataVipChargeData&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetbarBarianKingRank()
	{
		unsigned group;
		if(!Json::GetUInt(m_data, "group", group))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		CLogicBarbarianKing logicBarbarianKing;
		int ret = logicBarbarianKing.GetBKList(group, m_jsonResult);
		if(ret)
			return ret;
		CGI_SEND_LOG("action=getbarbariankingrank&group=%u", group);
		return 0 ;
	}

	int GetVipYearChargeData()
	{
		int ret = 0;

		int total = 0;
		int used = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN_MSG("openid");
		}

		CDataVipCharge charge;
		ret = charge.GetBlueYearVipCharge(openid,total,used);
		if(ret != 0){
			return ret;
		}

		m_jsonResult["hero_total"] = total;
		m_jsonResult["hero_used"] = used;
		CGI_SEND_LOG("action=getvipyearchargedata&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpdataVipYearChargeData()
	{
		int ret = 0;

		int total = 0;
		int used = 0;
		string openid;
		if(!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN_MSG("openid_error");
		}

		CDataVipCharge charge;
		ret = charge.GetBlueYearVipCharge(openid,total,used);
		if(ret != 0){
			return ret;
		}

		if(total < used+1)
		{
			return R_ERR_REFUSE;
		}

		used +=  1;
		ret = charge.UpdateBlueYearVipChargeUsed(openid,total,used);
		if(ret != 0){
			return ret;
		}

		m_jsonResult["hero_total"] = total;
		m_jsonResult["hero_used"] = used;
		CGI_SEND_LOG("action=updatavipyearchargedata&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetDailyFirstChargeData(){
		CLogicUser logicUser;
		Json::Value userFlag;
		int ret = logicUser.GetUserFlag(m_uid, userFlag);
		if(ret != 0){
			return ret;
		}
		uint32_t dfchg_ts = 0;
		uint32_t dfchg_count = 0;
		if(userFlag.isMember("chgs")) {
			uint32_t size = userFlag["chgs"].size();
			for(int i = size -1; i >= 0; --i) {
				uint32_t chgTime = userFlag["chgs"][i][0u].asUInt();
				if(Time::IsToday(chgTime)) {
					dfchg_ts = chgTime;
					dfchg_count = userFlag["chgs"][i][1u].asInt();
					break;
				}
			}
		}
		m_jsonResult["dfchg_ts"] = dfchg_ts;
		m_jsonResult["dfchg_count"] = dfchg_count;
		CGI_SEND_LOG("action=getdailyfirstchargedata&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int GetAlliancePoint()
	{
		int ret = 0;
		CLogicHequActivity alliancepoints;
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		ret = alliancepoints.GetHequAlliancePointRankJson(uid,m_jsonResult["alliance_point"]);
		if(ret != 0)
		{
			error_log("[get_alliance_point_failed] [uid=%u]",uid);
			return ret;
		}
		CGI_SEND_LOG("action=getalliancepoint&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetHequAccChargeData(){
		CLogicUser logicUser;
		Json::Value userFlag;
		int ret = logicUser.GetUserFlag(m_uid, userFlag);
		if(ret != 0){
			return ret;
		}
		uint32_t beginTime = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS);
		uint32_t endTime   = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS);
		uint32_t hqchg_ts = 0;
		int hqchg_count = 0;
		if(userFlag.isMember("chgs")) {
			uint32_t size = userFlag["chgs"].size();
			for(size_t i = 0; i < size; ++i) {
				uint32_t chgTime = userFlag["chgs"][i][0u].asUInt();
				if(beginTime <= chgTime && chgTime <= endTime) {
					hqchg_ts = chgTime;
					hqchg_count += userFlag["chgs"][i][1u].asInt();
				}
			}
			m_jsonResult["hqchg_ts"] = hqchg_ts;
			m_jsonResult["hqchg_count"] = hqchg_count;
		}
		return R_SUCCESS;
	}
	int GetWorldAttack()
	{
		int ret = 0;
		CLogicHequActivity worldattack;

		ret = worldattack.GetHequWorldAttackRankJson(m_uid,m_jsonResult["world_attack"]);
		if(ret != 0)
		{
			error_log("[get_world_attack_failed] [uid=%u]",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getworldattack&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetVipRebatesData(){
		unsigned level = 0;
		if (!Json::GetUInt(m_data, "lv", level))
		{
			return R_ERR_PARAM;
		}
		uint32_t beginTime = Config::GetIntValue(CONFIG_OPEN_TS);
		static int lastTime = 7 * 24 * 60 * 60;
		uint32_t endTime  = beginTime + lastTime;
		uint32_t time_now = Time::GetGlobalTime();
		bool isActivityTime = (beginTime <= time_now && time_now <= endTime);

		if (!isActivityTime) {
			beginTime = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS);
			endTime   = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS);
			isActivityTime = (beginTime <= time_now && time_now <= endTime);
		}

		if (!isActivityTime) {
			return R_SUCCESS;
		}

		CLogicVipRebates logicVipRebates;
		uint32_t oldTime = logicVipRebates.getTime();
		if(!(beginTime<= oldTime && oldTime <= endTime)) {
			return R_SUCCESS;
		}

		vector<VipUser> uids;
		logicVipRebates.getVips(level, uids);
		for(size_t i = 0; i < uids.size(); ++i) {
			m_jsonResult["rebates_vips"][i]["name"] = string(uids[i].name);
		}
		return R_SUCCESS;
	}

	int GetSRChargeRebatesData(){
		CLogicUser logicUser;
		Json::Value userFlag;
		int ret = logicUser.GetUserFlag(m_uid, userFlag);
		if(ret != 0){
			return ret;
		}
		uint32_t beginTime = Config::GetIntValue(CONFIG_SR_CHARGE_REBATES_BEGIN_TS);
		uint32_t endTime   = Config::GetIntValue(CONFIG_SR_CHARGE_REBATES_END_TS);
		uint32_t oldtime = userFlag["srchg"][0u].asUInt();
		if(!(beginTime <= oldtime && oldtime <= endTime)) {
			return R_SUCCESS;
		}

		uint32_t srchg_ts = 0;
		int srchg_count = 0;
		if(userFlag.isMember("chgs")) {
			uint32_t size = userFlag["chgs"].size();
			for(size_t i = 0; i < size; ++i) {
				uint32_t chgTime = userFlag["chgs"][i][0u].asUInt();
				if(beginTime <= chgTime && chgTime <= endTime) {
					srchg_ts = chgTime;
					srchg_count += userFlag["chgs"][i][1u].asInt();
				}
			}
			m_jsonResult["srchg_ts"] = srchg_ts;
			m_jsonResult["srchg_count"] = srchg_count;
		}
		return R_SUCCESS;
	}

	int GetLRChargeRebatesData(){
		CLogicUser logicUser;
		Json::Value userFlag;
		int ret = logicUser.GetUserFlag(m_uid, userFlag);
		if(ret != 0){
			return ret;
		}
		uint32_t beginTime = Config::GetIntValue(CONFIG_LR_CHARGE_REBATES_BEGIN_TS);
		uint32_t endTime   = Config::GetIntValue(CONFIG_LR_CHARGE_REBATES_END_TS);
		uint32_t oldtime = userFlag["lrchg"][0u].asUInt();
		if(!(beginTime <= oldtime && oldtime <= endTime)) {
			return R_SUCCESS;
		}

		uint32_t lrchg_ts = 0;
		int lrchg_count = 0;
		if(userFlag.isMember("chgs")) {
			uint32_t size = userFlag["chgs"].size();
			for(size_t i = 0; i < size; ++i) {
				uint32_t chgTime = userFlag["chgs"][i][0u].asUInt();
				if(beginTime <= chgTime && chgTime <= endTime) {
					lrchg_ts = chgTime;
					lrchg_count += userFlag["chgs"][i][1u].asInt();
				}
			}
			m_jsonResult["lrchg_ts"] = lrchg_ts;
			m_jsonResult["lrchg_count"] = lrchg_count;
		}
		return R_SUCCESS;
	}

	int GetHequChanganActivity()
	{
		int ret = 0;
		CLogicAllianceBattle changan;
		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}

		ret = changan.HequChanganActivity(uid,m_jsonResult["changan"]);
		if(ret != 0)
		{
			error_log("[gethequchanganactivity_failed] [uid=%u]",uid);
			return ret;
		}
		CGI_SEND_LOG("action=gethequchanganactivity&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetOpenAreaSelfData()
	{
		int ret = 0;
		CLogicOpenAreaActivity open_area;

		ret = open_area.GetOpenAreaActivitySelfData(m_uid, m_jsonResult);
		if(ret != 0)
		{
			error_log("[getopenareaselfdata_failed] [uid=%u]",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=gethequchanganactivity&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpdateOpenAreaSelfData()
	{
		int ret = 0;
		CLogicOpenAreaActivity open_area;
		int grade_range = 0;

		if (!Json::GetInt(m_data, "grade_range", grade_range) )
		{
			error_log("[updateopenareaselfdata grade_range error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		ret = open_area.UpdateOpenAreaActivitySelfData( m_uid, grade_range,m_jsonResult);
		if(ret != 0)
		{
			error_log("[updateopenareaselfdata_failed] [uid=%u]",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=updateopenareaselfdata&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetGalleryAccChargeData()
	{
		CLogicUser logicUser;
		Json::Value userFlag;
		int ret = logicUser.GetUserFlag(m_uid, userFlag);
		if(ret)
			return ret;

		unsigned beginTime = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_BEGIN_TS);
		unsigned endTime   = Config::GetIntValue(CONFIG_ACTIVITY_GALLERY_END_TS);
		unsigned gallery_pay = 0;
		if(userFlag.isMember("chgs"))
		{
			unsigned size = userFlag["chgs"].size();
			for(unsigned i = 0; i < size; ++i)
			{
				unsigned chgTime = userFlag["chgs"][i][0u].asUInt();
				if(beginTime <= chgTime && chgTime <= endTime)
				{
					gallery_pay += userFlag["chgs"][i][1u].asInt();
				}
			}
		}
		m_jsonResult["gallery_pay"] = gallery_pay;
        CGI_SEND_LOG("action=GetGalleryAccChargeData&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int GetNewLotteryData()
	{
		CLogicCMD logicCMD;
		int ret = logicCMD.GetNewLotteryData(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=genewlotterydata&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetConsumeRankList()
	{
		int ret = 0;
		CLogicConsumeRank logicConsumeRank;

		ret = logicConsumeRank.GetList(m_uid, m_jsonResult["getconsumeranklist"]);
		if(ret != 0)
		{
			error_log("get getconsumeranklist failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getconsumeranklist&uid=%u", m_uid);
		return R_SUCCESS;

	}

	int GetRechargeRankList()
	{
		int ret = 0;
		CLogicRechargeRank logicRechargeRank;

		ret = logicRechargeRank.GetList(m_uid, m_jsonResult["getRechargeRanklist"]);
		if(ret != 0)
		{
			error_log("get getRechargeRanklist failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getRechargeRanklist&uid=%u", m_uid);
		return R_SUCCESS;

	}

	int GetRestriction()
	{
		int ret = 0;
		CLogicRestric Restric;

	    ret = Restric.GetRestricData(m_uid,m_jsonResult);
		if(ret != 0)
		{
			error_log("GetRestricData failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getrestriction&uid=%u", m_uid);
		return R_SUCCESS;
	}

	/*
	int UpdateRestriction()
	{
		unsigned id = 0;
		if (!Json::GetUInt(m_data, "id", id))
		{
			return R_ERR_PARAM;
		}
		int ret = 0;
		CLogicRestric Restric;

	    ret = Restric.UpdateRestricData(m_uid, id, m_jsonResult);
		if(ret != 0)
		{
			error_log("UpdateRestricData failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=updaterestriction&uid=%u", m_uid);
		return R_SUCCESS;
	}
	*/

	int DragonScaleActive()
	{
		int ret = 0;

		CLogicCMD logicCMD;
		ret = logicCMD.GetDragonScaleData(m_uid, m_jsonResult);
		if (ret)
		{
			error_log("GetDragonScaleData failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=GetDragonScaleData&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetHammerHitList()
	{
		int ret = 0;
		CLogicPointsRank logicPointsRank;

		ret = logicPointsRank.GetList(m_uid, m_jsonResult["getPointsRanklist"]);
		if(ret != 0)
		{
			error_log("get getPointsRanklist failed uid = %u",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=getPointsRanklist&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetCrowdFunding()
	{
		int ret = 0;
		CLogicCrowdFunding logicCrowdFunding;
		ret = logicCrowdFunding.Get(m_uid, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetCrowdFunding&uid=%u", m_uid);
		return ret;
	}

	int BuyCrowdFunding()
	{
		unsigned id = 0;
		if(!Json::GetUInt(m_data, "id", id))
			return R_ERR_PARAM;
		unsigned need = 0;
		if(!Json::GetUInt(m_data, "need", need))
			return R_ERR_PARAM;

		int ret = 0;
		CLogicCrowdFunding logicCrowdFunding;
		ret = logicCrowdFunding.Buy(m_uid, id, need, m_jsonResult);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=BuyCrowdFunding&uid=%u", m_uid);
		return ret;
	}

	int GetLords()
	{
		CLogicLordRamote logicLordRamote;
		int ret = logicLordRamote.GetAllLords(m_uid, m_jsonResult);
		if(ret) return ret;

		CGI_SEND_LOG("action=GetLords&uid=%u", m_uid);
		return ret;
	}

	int GetRankList()
	{
		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}

		CLogicLordRamote logicLordRamote;
		int ret = logicLordRamote.GetRankList(m_uid, type, m_jsonResult);
		if (ret != R_SUCCESS) return ret;

		CGI_SEND_LOG("action=GetRanksList&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int RotaryTableInfo()
	{
		uint32_t beginTime = Config::GetIntValue(CONFIG_ACTIVITY_ROTARY_TABLE_BEGIN_TS);
		uint32_t endTime   = Config::GetIntValue(CONFIG_ACTIVITY_ROTARY_TABLE_END_TS);
		uint32_t version   = Config::GetIntValue(CONFIG_ACTIVITY_ROTARY_TABLE_VER);
		if(endTime < Time::GetGlobalTime() || beginTime > Time::GetGlobalTime())
		{
			LOGIC_ERROR_RETURN_MSG("activity_over");
		}

		//获取抽奖信息
		Json::Value tempdata;
		Json::Value data;
		string url = "action=GetRotaryTableRewardInfo";
		data["version"] = version;
		string datastr = Json::ToString(data);
		url.append("&data=").append(Crypt::UrlEncode(datastr));

		CLogicAllServerBaseMatch logicBaseMatch;
		int ret = logicBaseMatch.RequestBaseMatch(url,tempdata,CONFIG_ALLS_MATCH_SERVER_PATH,true);
		if(ret)
			return ret;
		if (tempdata.isMember("list"))
			m_jsonResult["list"] = tempdata["list"];
		else
			m_jsonResult["list"] = Json::Value(Json::arrayValue);
		return 0;
	}

	int getchongzhizixuan()
	{
		UserWrap user(m_uid, false);
		ChongZhiZiXuan act(user);
		act.Get(user, m_jsonResult);
		return 0;
	}
	int GetBeautyInfo() {
		UserWrap user(m_uid, false);
		ActivityMeiRenUnit act(user);
		act.Get(m_jsonResult);
		return 0;
	}
	int InvestmentInfo() {
		UserWrap user(m_uid, false);
		ActivityInvestment act(user);
		act.Get(m_jsonResult);
		return 0;
	}
	int GetHequbuchangLevel() {
		CLogicCMD logicCMD;
		m_jsonResult["level"] = logicCMD.GetHequbuchangLevel(m_uid);
		return 0;
	}
};

CGI_MAIN(CCgiActivity)



