/*
 * test.cpp
 *
 *  Created on: 2014-8-29
 *      Author: Ralf
 */

#include "LogicInc.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include "LogicCmdUnits.h"
#include "LogicUnitWrap.h"

void GetHeroInfo(unsigned uid, std::string& heroid, std::string& heroname)
{
	heroid = "";
	heroname = "";
	CDataHero heroDB;
	vector<DataHero> datas;
	int ret = heroDB.GetHero(uid, datas);
	if (ret != 0)
	{
		return ;
	}

	Json::Reader reader;
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value json;
		if (!reader.parse(datas[i].data, json))
		{
			continue;
		}

		int def = json["def"].asInt();

		if (def > 0)
		{
			Json::GetString(json, "id", heroid);
			Json::GetString(json, "name", heroname);
			return ;
		}
	}
}

void TestNewRecharge(unsigned uid, unsigned id)
{

	try
	{
		Json::Value result;

		UserWrap userWrap(uid, true);

		NewRechargeUnit newrechargeUnit(uid);
		newrechargeUnit.GetRewardBagAction(userWrap, id, result);

		std::cout << "Success: " << result << std::endl;

		//userWrap.Save();
	}
	catch (const std::exception& e)
	{
		//error_log("%s", e.what());
		//::SetError(R_ERROR, e.what());
		std::cout << "Fail: " << e.what() << std::endl;

	}
}

void TestGroupBuy(unsigned uid)
{
	try
	{
		Json::Value result;

		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);
		GroupBuyDailyUnit groupBuyDaily(uid, userWrap);
		groupBuyDaily.BuyAction(userWrap, result);

		userWrap.Save();

		std::cout << "Success: " << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Fail: " << e.what() << std::endl;
	}
}

void TestGroupBuyReward(unsigned uid, int index)
{
	try
	{
		Json::Value result;

		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);
		GroupBuyDailyUnit groupBuyDaily(uid, userWrap);
		groupBuyDaily.GetRewardAction(index, userWrap, result);

		userWrap.Save();

		std::cout << "Success: " << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Fail: " << e.what() << std::endl;
	}
}

void TestLittleRecharge(unsigned uid)
{
	try
	{
		Json::Value result;

		AUTO_LOCK_USER(uid);

		UserWrap userWrap(uid, false);

		LittleRechargeUnit littleRecharge(userWrap);
		littleRecharge.GetReward(userWrap, result);

		userWrap.Save();

		std::cout << "Success: " << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Fail: " << e.what() << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "Init kernel fail!" << endl;
		return -1;
	}
	Config::SetDomain(0);
	int ret = 0;

	/*
	if (argc < 2)
	{
		std::cout << "parsms error" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToUInt(argv[1]);
	int index = -1;
	if (argc >= 3)
	{
		index = Convert::StringToUInt(argv[2]);
	}

	if (index < 0)
	{
		//TestGroupBuy(uid);
		TestLittleRecharge(uid);
	}
	else
	{
		TestGroupBuyReward(uid, index);
	}
	*/


	/* ranklist
	uint64_t uidEnd;
	string serverid;
	unsigned zone;
	if (!Config::GetValue(serverid, CONFIG_SERVER_ID))
	{
		cout<<"get start user id fail!"<<endl;
		return 0;
	}

	Convert::StringToUInt(zone, serverid);
	unsigned userid = Config::GetUIDStart(zone);
	CLogicIdCtrl logicIdCtrl;
	ret = logicIdCtrl.GetCurrentId(KEY_UID_CTRL, uidEnd);
	if (ret != 0)
	{
		cout<<"get current user id fail!"<<endl;
		return 0;
	}

	for (; userid <= (unsigned) uidEnd; ++userid)
	{
		DataUser user;
		CLogicUser logicUser;
		ret = logicUser.GetUserLimit(userid, user);
		if(ret)
			continue;
		if(user.refresh || user.memory)
		{
			user.refresh = user.memory = 0;
			logicUser.SetUserLimit(userid,user);
		}
	}
	*/

	/* kingdom
	CDataUser db;
	fstream fin("cdnuid2clean");
	if (!fin.good()) {
		cout << "open cdnuid2clean fail" << endl;
		return 1;
	}
	while (!fin.eof() && fin.good()) {
		unsigned id = 0;
		fin >> id;
		db.SetCDN(id,Job_None);
	}
	*/

	/*
//gift
	fstream fin("newyear");
	if (!fin.good()) {
		cout << "open newyear fail" << endl;
		return 1;
	}
	CLogicEquipment lgEq;
	CLogicEmail logicEmail;
	Json::Value result;
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		lgEq.AddOneItem(uid, 829, 1, "newyear", result);

		DataEmail email;
		vector<uint64_t> toUidList;
		toUidList.push_back(uid);
		email.attach_flag = 0;
		email.attachments = "";
		email.uid = ADMIN_UID;
		email.post_ts = Time::GetGlobalTime();
		email.title = "至尊会员";
		email.text = "值此新春佳节来临之际，《城防三国》项目组恭祝全服同仁新年快乐！为答谢各路诸侯(神将以上玩家）统御三国，热血奋战，特奉上元旦礼包一份。春节期间其他福利请联系vip通道工作人员qq，感谢您对城防三国一直以来的支持和喜爱！";
		logicEmail.AddEmail(email,toUidList);
	}
	*/
/*
#if 0
	if (argc < 2)
	{
		std::cout << "test %uid%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	//unsigned index = Convert::StringToInt(argv[2]);

	std::cout << "GetSignReward Test" << std::endl;
	//std::cout << "Input uid: " << uid << " index: " << index << std::endl;

	CLogicCMD logicCMD;
	Json::Value result;
	ret = logicCMD.SignInReward(uid, result, 0, 0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! result: " << result << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif

#if 0 //邀请奖励
	if (argc < 3)
	{
		std::cout << "test %uid% %rewardid%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	unsigned reward_id = Convert::StringToInt(argv[2]);

	std::cout << "GetInviteReward Test" << std::endl;
	std::cout << "Input uid: " << uid << " reward_id: " << reward_id << std::endl;

	CLogicCMD logicCMD;
	Json::Value result;
	ret = logicCMD.GetInviteReward(uid, reward_id, result, 0, 0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! result: " << result << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif

#if 0 //日常任务奖励
	if (argc < 3)
	{
		std::cout << "test %uid% %index%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	unsigned index = Convert::StringToInt(argv[2]);

	CLogicCMD logicCMD;
	Json::Value result;
	ret = logicCMD.DailyQuestReward(uid, index, result, 0, 0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! Result: " << result << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif

#if 0 //VIP礼包
	if (argc < 3)
	{
		std::cout << "test %uid% %vip_level%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	unsigned viplevel = Convert::StringToInt(argv[2]);

	CLogicCMD logicCMD;
	Json::Value result;
	ret = logicCMD.VipGiftBag(uid, viplevel, result, 0, 0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! Result: " << Json::ToString(result) << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif

#if 0 //充值
	if (argc < 3)
	{
		std::cout << "test %uid% %id%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	unsigned id = Convert::StringToInt(argv[2]);
	CLogicCMD logicCMD;
	Json::Value result;

	ret = logicCMD.RechargeGiftBag(uid, id, result, 0 ,0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! Result: " << Json::ToString(result) << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif

#if 0
	if (argc < 4)
	{
		std::cout << "test %uid% %index% %type%" << std::endl;
		exit(0);
	}

	unsigned uid = Convert::StringToInt(argv[1]);
	unsigned index = Convert::StringToInt(argv[2]);
	unsigned type = Convert::StringToInt(argv[3]);
	CLogicCMD logicCMD;
	Json::Value result;
	ret = logicCMD.IntensifyWeaponBySoul(uid, index, type, result, 0 ,0);
	if (R_SUCCESS == ret)
	{
		std::cout << "Handle success! Result: " << Json::ToString(result) << std::endl;
	}
	else
	{
		std::cout << "Failed ret: " << ret << " error msg: " << ::GetErrorMessage() << std::endl;
	}
#endif
*/
	/* old user bug
	unsigned num = atoi(argv[1]);
	unsigned uid = atoi(argv[2]);
	int set = num*30;
	CLogicEquipment logicEquip;
	Json::Value equip_data;
	ret = logicEquip.GetEquipment(uid, 0, equip_data);
	if(ret == 0)
	{
		for(int i=0; i<equip_data.size(); ++i)
		{
			unsigned eqid = equip_data[i]["id"].asUInt();
			unsigned ud = equip_data[i]["ud"].asUInt();
			int count = equip_data[i]["count"].asInt();
			if(eqid == 4022)
			{
				int use = num*70;
				logicEquip.UseEquipment(uid, eqid, ud, use>count?count:use, "OLD_USER_BUG");
			}
			else if(eqid == 42010)
			{
				int use = num*5;
				logicEquip.UseEquipment(uid, eqid, ud, use>count?count:use, "OLD_USER_BUG");
			}
			else if(eqid == 4065)
			{
				int use = num*50;
				logicEquip.UseEquipment(uid, eqid, ud, use>count?count:use, "OLD_USER_BUG");
			}
			else if(set>0 && (eqid == 50053 || eqid == 51001 || eqid == 51002 || eqid == 51003 || eqid == 51004))
			{
				int use = set>count?count:set;
				set -= use;
				logicEquip.UseEquipment(uid, eqid, ud, use, "OLD_USER_BUG");
			}
		}
	}

	const int exp[120] = {0,32,92,188,328,520,772,1092,1488,1968,2540,3212,3992,4888,5908,7060,8884,11444,14804,19028,24180,30324,37524,45844,55348,66100,78164,91604,106484,122868,140820,161492,185012,211508,241108,273940,310132,349812,393108,440148,491060,545972,605012,668308,735988,808180,887756,974956,1070020,1173188,1284700,1404796,1533716,1671700,1818988,1975820,2142436,2319076,2505980,2703388,2911540,3130676,3361036,3602860,3856388,4121860,4399516,4689596,4992340,5307988,5636780,5978956,6334756,6704420,7088188,7486300,7914796,8374316,8865500,9388988,9945420,10535436,11159676,11818780,12513388,13244140,14011676,14816636,15659660,16541388,17462460,18449836,19504716,20628300,21821788,23086380,24423276,25833676,27318780,28879788,30526651,32264091,34097091,36030906,38071081,40223465,42494230,44889887,47417306,50083733,52896813,55864613,58995642,62298877,65783790,69460373,73339169,77431298,81748494,86303136};
	CLogicUser logicUser;
	DataUser user;
	ret = logicUser.GetUserLimit(uid, user);
	if (ret == 0)
	{
		int p = user.point;
		int level = 1;
		float d;
		for(int i=0;i<num;++i)
		{
			for(int j=119;j>=0;--j)
			{
				if(p > exp[j])
				{
					level = j+1;
					break;
				}
			}
			if(level <= 70)
				d = 3.5f*pow((double)level+10, 2.2f)-600;
			else if(level <= 80)
				d = (3.5f*pow((double)level+10, 2.2f)-600) * (1 - (level - 70)*0.01f);
			else
				d = (3.5f*pow((double)level+10, 2.2f)-600) * 0.9f;
			p -= (int)(d*3);
		}
		RESOURCE_LOG("[OLD_USER_BUG]uid=%u,expchg=%d,exp=%d", uid, user.point-p, p);
		user.point = p>0?p:0;
		logicUser.SetUserLimit(uid, user);
	}
	 */

	//cout<<CTime::GetTimeOfDay().tv_sec<<endl;

	/*
	unsigned uid = atoi(argv[1]);
	DataRank rank;
	rank.uid = uid;
	rank.heroid = "{}";
	CDataRank dataRank;
	dataRank.AddRank(rank);
	 */

	/*
	//flag bug
	CLogicUser logicUser;
	Json::Reader reader;
	Json::FastWriter writer;
	unsigned now = Time::GetGlobalTime();
	fstream fin("flagbug");
	if (!fin.good()) {
		cout << "open flagbug fail" << endl;
		return 1;
	}
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		DataUser user;
		ret = logicUser.GetUser(uid, user);
		if(ret == 0)
		{
			Json::Value userFlag;
			reader.parse(user.user_flag, userFlag);
			userFlag.removeMember("hqchg");
			userFlag.removeMember("hundredDaysPay");
			userFlag.removeMember("consumeRank");
			userFlag.removeMember("pointpay");
			userFlag.removeMember("payTotal");
			userFlag.removeMember("user_pay");
			userFlag["user_pay"][0u][0u] = now;
			userFlag["user_pay"][0u][1u] = 30001;
			userFlag["user_pay"][0u][2u] = 30001;
			user.user_flag = writer.write(userFlag);
			logicUser.SetUser(uid, user);
		}
	}
	*/

	/* hufu bug
	unsigned id = atoi(argv[1]);
	if(IsValidUid(id))
	{
		unsigned num = atoi(argv[2]);
		CLogicEquipment logicEquip;
		Json::Value equip_data;
		ret = logicEquip.GetEquipment(id, 0, equip_data);
		if(ret == 0)
		{
			for(int i=0; i<equip_data.size(); ++i)
			{
				unsigned eqid = equip_data[i]["id"].asUInt();
				unsigned ud = equip_data[i]["ud"].asUInt();
				int count = equip_data[i]["count"].asInt();
				if(eqid == HUFU_ID)
				{
					if(num > count)
					{
						logicEquip.UseEquipment(id, eqid, ud, count, "HUFU_BUG");
						num -= count;
					}
					else
					{
						logicEquip.UseEquipment(id, eqid, ud, num, "HUFU_BUG");
						break;
					}
				}
			}
		}
	}
	else if(IsAllianceId(id))
	{
		CLogicAlliance logicAlliance;
		DataAlliance alliance;
		ret = logicAlliance.GetAlliance(id, alliance);
		if(ret == 0)
		{
			Json::Value data;
			Json::FromString(data, alliance.extra_data);
			data["resource"]["r5"] = 0;
			alliance.extra_data = Json::ToString(data);
			logicAlliance.SetAlliance(alliance);
			RESOURCE_LOG("[HUFU_BUG][aid=%u,r5=0]",id);
		}
	}
	*/

	/*
	unsigned pt = atoi(argv[2]);
	OPUserInfo userinfo;
	userinfo.OpenId = argv[1];
	OPFriendList friendList;
	CLogicUserBasic logicUserBasic;
	bool isNewUser=false;
	string via, iopenid;
	unsigned uid = 0;
	ret = logicUserBasic.LoginPlatformUser((PlatformType)pt, userinfo, friendList, iopenid, uid, isNewUser,via,gm_none);
	if(ret != 0)
		return ret;
		*/


/**********道具发放*********************************
	if (argc < 4)
	{
		std::cout << "parsms error" << std::endl;
		exit(0);
	}
	unsigned id = atoi(argv[1]);
	unsigned c = atoi(argv[2]);
	fstream fin(argv[3]);
	if (!fin.good()) {
		cout << "open file fail" << endl;
		return 1;
	}
	CLogicEquipment lgEq;
	Json::Value result;
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		lgEq.AddOneItem(uid, id, c, "test", result);
	}*/

/*************统计查询************************
	if (argc < 2)
	{
		std::cout << "parsms error" << std::endl;
		exit(0);
	}
	fstream fin(argv[1]);
	if (!fin.good()) {
		cout << "open file fail" << endl;
		return 1;
	}
	CDataPayHistory dbp;
	CDataUserMapping dbm;
	CLogicEquipment lgEq;
	CLogicHero lgHr;
	CLogicPay lgP;
	vector<unsigned> uids;
	map<unsigned, string> u2o;
	while (!fin.eof() && fin.good()) {
		unsigned serverid = 0, uid = 0;
		string openid;
		fin >> serverid >> openid;
		ret = dbm.GetUID(openid, serverid, uid);
		if(ret)
		{
			cout<<openid<<" error"<<endl;
			continue;
		}
		uids.push_back(uid);
		u2o[uid] = openid;
	}
	cout<<"openid,type,channel_pay_id,credit,count,time"<<endl;
	for(int j=0;j<uids.size();++j)
	{
		unsigned uid = uids[j];
		vector<DataPayHistory> datas;
		ret = dbp.GetPayHistory(uid, datas);
		if(ret == 0)
		{
			for(int i=0;i<datas.size();++i)
			{
				if(datas[i].time > 1451577600 && datas[i].time < 1483200000 && datas[i].channel_pay_id.find("-APP") != string::npos)
					cout<<u2o[uid]<<","<<datas[i].type<<","<<datas[i].channel_pay_id<<","<<datas[i].credit<<","<<datas[i].count<<","<<datas[i].time<<endl;
			}
		}
	}
	cout<<"openid,id,count"<<endl;
	for(int j=0;j<uids.size();++j)
	{
		unsigned uid = uids[j];
		Json::Value eq;
		ret = lgEq.GetEquipment(uid, 0, eq);
		if(ret == 0)
		{
			for(unsigned i=0;i<eq.size();++i)
				cout<<u2o[uid]<<","<<eq[i]["id"].asInt()<<","<<max(1, eq[i]["count"].asInt())<<endl;
		}
		Json::Value hr;
		ret = lgHr.GetHero(uid, hr);
		if(ret == 0)
		{
			for(unsigned i=0;i<hr.size();++i)
				cout<<u2o[uid]<<","<<hr[i]["id"].asString()<<",1"<<endl;
		}
	}
	cout<<"openid,cash,coin"<<endl;
	for(int j=0;j<uids.size();++j)
	{
		unsigned uid = uids[j];
		DataPay pay;
		ret = lgP.GetPay(uid, pay);
		if(ret == 0)
			cout<<u2o[uid]<<","<<pay.cash<<","<<pay.coins<<endl;
	}
	return 0;
*******************************************************/

	/*道具查询
	if (argc < 2)
	{
		std::cout << "parsms error" << std::endl;
		exit(0);
	}
	fstream fin(argv[1]);
	if (!fin.good()) {
		cout << "open file fail" << endl;
		return 1;
	}
	CLogicEquipment lgEq;
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		Json::Value eq;
		ret = lgEq.GetEquipment(uid, 0, eq);
		if(ret == 0)
		{
			for(unsigned i=0;i<eq.size();++i)
			{
				if(eq[i]["id"].asInt() == 14001 && eq[i]["hexp"].asInt() >= 10)
				{
					cout<<uid<<endl;
					break;
				}
			}
		}
	}*/

	/*沉迷测试
	string openid = "3E1404200EFE26AE1561EE4FB7D2EB9A";
	string openkey = "46C743D6CE798539398CA7504D4B4291";
	string appid = "100688853";
	string appkey = "a8c1850bb4043bd69bfac68d9f5903be";

	string url = "http://openapi.minigame.qq.com/v3/user/gameapi_real_name_query?";
	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/user/gameapi_real_name_query") + "&";
	string qsig = "appid=" + appid + "&openid=" + openid + "&openkey=" + openkey;
	string qstr = "appid=" + Crypt::UrlEncodeForTX(appid) + "&openid="
			+ Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);
	osig += Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);


	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
		return -1;
	}
	Json::Value value;
	if(!Json::Reader().parse(response, value))
	{
		response = "json_parse_fail";
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
		return -1;
	}
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		Json::GetString(value, "msg", response);
		error_log("[get_info fail][openid=%s,openkey=%s,msg=%s]",
				openid.c_str(), openkey.c_str(), response.c_str());
		error_log("url = %s, qsig=%s",url.c_str(),qsig.c_str());
		return -1;
	}

	debug_log("%s", response.c_str());
	*/

	/*CDataPointsRankAllServer * m = new CDataPointsRankAllServer;砸罐子排行修复
	ret = m->Init("/data/release/sgonline/points_rank_all_server.dat",sem_pointsrankallserver);
	if(ret)
		return ret;
	PointsRankALLServer *pTable = m->_get();
	if (pTable == NULL)
		return 1;
	unsigned p = pTable->all.head;
	for(unsigned i=0;i<pTable->all.num;++i)
	{
		if(p >= POINT_RANK_ALL_SERVER_ALL)
			break;
		if(!IsValidUid(pTable->all.user[p].uid))
			break;
		cout<<i+1<<" "<<pTable->all.user[p].uid<<" "<<pTable->all.user[p].points<<endl;
		p = pTable->all.user[p].next;
	}*/

	/*if(argc < 2)英雄名字
	{
		cout<<"uid error"<<endl;
		return 1;
	}
	unsigned uid = atoi(argv[1]);
	Json::Value h;
	if(CLogicHero().GetHero(uid, h))
	{
		cout<<"load error"<<endl;
		return 1;
	}
	for(int i=0;i<h.size();i++)
	{
		string c = "/data/release/sgonline/s1/webroot/hero/heroname.sh " + h[i]["id"].asString() + " " + CTrans::UTOS(h[i]["l"].asUInt());
		system(c.c_str());
	}*/

	/**************混元技*********************/
	if (argc < 2)
	{
		std::cout << "parsms error" << std::endl;
		exit(0);
	}
	fstream fin(argv[1]);
	if (!fin.good()) {
		cout << "open file fail" << endl;
		return 1;
	}
	CLogicHero lgHr;
	CLogicUser lgUr;
	CLogicUserBasic lgUb;
	while (!fin.eof() && fin.good()) {
		unsigned uid = 0;
		fin >> uid;
		if(!IsValidUid(uid))
			continue;
		DataUser ur;
		lgUr.GetUserLimit(uid, ur);
		if(ur.level < 30)
			continue;
		Json::Value hr;
		lgHr.GetHero(uid, hr);
		map<unsigned, vector<unsigned> > skill;
		for(unsigned i=0;i<hr.size();++i)
		{
			SkillUnit::CheakSkillVer(hr[i]);
			if(hr[i].isMember("tskill") && hr[i]["tskill"].isArray())
			{
				for(unsigned j=0;j<hr[i]["tskill"].size();++j)
				{
					unsigned id = hr[i]["tskill"][j][0u].asUInt();
					if((id >= 13051  && id <= 13053) || (id >= 12051  && id <= 12053) || (id >= 11051  && id <= 11053) || id == 53001)
						skill[id].push_back(hr[i]["tskill"][j][1u].asUInt());
				}
			}
		}
		if(!skill.empty())
		{
			string name;
			lgUb.GetName(uid, name);
			for(map<unsigned, vector<unsigned> >::iterator it=skill.begin();it!=skill.end();++it)
			{
				cout<<it->first<<","<<ur.accCharge<<","<<ur.level<<","<<uid<<",\""<<name<<"\"";
				for(vector<unsigned>::iterator iter=it->second.begin();iter!=it->second.end();++iter)
					cout<<","<<*iter;
				cout<<endl;
			}
		}
	}

	return R_SUCCESS;
}
