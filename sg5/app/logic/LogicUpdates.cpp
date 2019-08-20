#include "LogicUpdates.h"
#include <math.h>

int CLogicUpdates::AddUpdates(unsigned uid, Json::Value &data,bool email, bool isother)
{
	if(!IsValidUid(uid))
		return R_ERR_PARAM;

	if (!data.isArray())
	{
		return AddUpdate(uid,data,email,isother);
	}
	int ret = 0;
	for (unsigned i = 0; i < data.size(); i++)
	{
		ret += AddUpdate(uid,data[i],email,isother);
	}
	return ret;
}

int CLogicUpdates::AddUpdate(unsigned uid, Json::Value &data, bool email, bool isother)
{
	CDataUpdates db;
	int ret = 0;
	Json::FastWriter writer;

	if (!data.isObject() || !data.isMember("ts") || !data["ts"].isIntegral())
	{
		error_log("[updates data error][uid=%u]",uid);
		DATA_ERROR_RETURN_MSG("data_updates_error");
	}

	// 后台发放奖励
	sendReward(uid, data);

	if(isother)
		data["isother"] = 1;
	unsigned ts = data["ts"].asUInt();
	ret = db.AddUpdates(uid, ts, writer.write(data));
	if (ret == R_ERR_DATA)
	{
		unsigned i = 0;
		unsigned oldts = ts;
		while(ret == R_ERR_DATA && i < 10)
		{
			++i;
			ts = oldts + Math::GetRandomInt(7) + i*3;
			data["ts"] = ts;
			ret = db.AddUpdates(uid, ts, writer.write(data));
		}
		error_log("[AddUpdates retry][uid=%u,times=%u,ret=%u]",uid,i,ret);
	}
	else if(ret != 0)
	{
		error_log("[AddUpdates fail][uid=%u,ret=%d]",uid,ret);
		DATA_ERROR_RETURN_MSG("db_add_updates_fail");
	}

	if(email)
	{
		DataEmail email;
		CLogicEmail logicEmail;
		vector<uint64_t> toUidList;
		toUidList.push_back(uid);
		email.attach_flag = 0;
		email.attachments = "";
		email.uid = ADMIN_UID;
		email.post_ts = data.isMember("ts")?data["ts"].asUInt():Time::GetGlobalTime();
		email.title = data.isMember("s")?data["s"].asString():"";
		email.text = Json::ToString(data);
		logicEmail.AddEmail(email,toUidList,true);
	}

	return ret;
}

int CLogicUpdates::GetUpdates(unsigned uid, Json::Value &data, bool onlyother)
{
	Json::Reader reader;
	CDataUpdates db;
	vector<DataUpdates> datas;
	//int ret = db.GetUpdates(uid, datas);
	int ret = db.GetUpdatesBeforeTs(uid, Time::GetGlobalTime(), datas);
	if (ret == R_ERR_NO_DATA)
	{
		data.resize(0);
		return 0;
	}
	if (ret != 0)
	{
		error_log("[GetUpdates fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_get_updates_fail");
	}
	if(onlyother)
	{
		for(vector<DataUpdates>::iterator it = datas.begin();it!=datas.end();)
		{
			Json::Value temp;
			if(!reader.parse((*it).data, temp) || !temp.isMember("isother") || temp["isother"] != 1)
				it = datas.erase(it);
			else
				++it;
		}
	}
	data.resize(datas.size());
	for (unsigned i = 0; i < datas.size(); i++)
	{
		if (!reader.parse(datas[i].data, data[i]))
		{
			error_log("[parse updates fail][uid=%u,i=%d]",uid,i);
			DATA_ERROR_RETURN_MSG("db_updates_data_error");
		}
	}
	return 0;
}

int CLogicUpdates::RemoveUpdatesBeforeTs(unsigned uid, unsigned ts)
{
	CDataUpdates db;
	int ret = db.RemoveUpdatesBeforeTs(uid, ts);
	if (ret != 0)
	{
		error_log("[RemoveUpdatesBeforeTs fail][uid=%u,ret=%d]",uid,ret);
		DB_ERROR_RETURN_MSG("db_rm_updates_fail");
	}
	return 0;
}

int CLogicUpdates::sendReward(unsigned uid, const Json::Value &data){
	string s = data["s"].asString();
	int ret = 0;
	if (s == "boatfinish") {
		// 草船借箭
		ret = sendEndofShipReward(uid, data);
	}
	else if (s == "ALLIANCEBOSSTOP") {
		// 联盟屠魔奖励
		ret = sendAllianceBossAward(uid, data);
	}
	else if (s == "WORLDBOSSTOP") {
		// 世界屠魔奖励
		ret = sendWorldBossAward(uid, data);
	}
	else if (s == "BARBARIANKINGREWARD") {
		// 蛮王发排名奖励
		ret = sendBarbarianKingReward(uid, data);
	}
	else if (s == "QixiJieRank") {
		// 幸运大转盘
		ret = sendQixiRankReward(uid, data);
	}
	else if (s == "IntegralRank") {
		// 乐不思蜀奖励
		ret = sendHundredDaysReward(uid, data);
	}
	else if (s == "activitypointrank") {
		// 砸罐子
		ret = sendPointRankReward(uid, data);
	}
	else if (s == "DRAGONBALLLOSS") {
		// 绣球易主
		ret = sendSnatchDragonballAward(uid, data);
	}
	else if (s == "DRAGONBALLREWARD") {
		// 活动结束
		ret = resetDragonBall(uid, data);
	}
	else if (s == "activityherotop") {
		// 开区活动战力排名奖励
		ret = sendPowerRankReward(uid, data);
	} else if (s == "activityroottop10") {
		// 开区活动掠夺
		ret = sendAttackRankReward(uid, data);
	} else if (s == "allserverpersonmatch") {
		// 周五的跨服武林大会奖励
		ret = sendAllServerPMatchAward(uid, data);
	}
	return ret;
}

// 联盟屠魔奖励
int CLogicUpdates::sendAllianceBossAward(unsigned uid, const Json::Value &data){
	AUTO_LOCK_USER(uid)
	return sendProsperAndCoins(uid,data, "activity_AllianceBoss_get");
}

// 世界屠魔奖励
int CLogicUpdates::sendWorldBossAward(unsigned uid, const Json::Value &data){
	AUTO_LOCK_USER(uid)
	return sendProsperAndCoins(uid,data, "activity_WORLDBOSSDAM_get");
}

// 草船借箭
int CLogicUpdates::sendEndofShipReward(unsigned uid, const Json::Value &data, unsigned uidby, bool win, Json::Value * result){
	// 60 * cfg.reward.value * Math.exp(0.0553 * (level - 24)) * (1 - data.attacktimes.value * 0.2)
	CLogicUser logicUser;
	DataUser dataUser;
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		cout << "[sendEndofShipReward] GetCDataXML fail" << endl;
		return R_ERR_DATA;
	}

	uint32_t id = data["type"].asUInt();
	if (uidby && !win)
		id = 1;
	bool yellow_torch_burning = bool(data["torch"].asUInt());
	int attacktimes = data["attacktimes"].asInt();
	XMLBoat boat;
	ret = pDataXML->GetBoat(id, boat);
	if(ret){
		error_log(" get boat reward  failed,uid = %u",uid);
		return ret;
	}
	double xishu = 0.0553f;
	unsigned classType =  data["classType"].asUInt();
	if (classType == 2)
		xishu = 0.0023f;
	if (classType == 3)
		xishu = 0.0053f;
	double by = 1;
	if (uidby)
		by*=0.2;
	if (!win)
		by*=0.8;
	int res;
	if (!uidby)
		res = 60.0f * (float)boat.reward[classType-1] * exp(xishu * (float)(dataUser.level - 24)) * (1.0f - (float)attacktimes * 0.2f) ;
	else
		res = int(60.0f * (float)boat.reward[classType-1] * exp(xishu * (float)(dataUser.level - 24))) * by;
	if (yellow_torch_burning)
	{
		res *= 1.2;
	}
	CLogicAdmin logicAdmin;
	string code = "activity_boatfinish_get";
	if (uidby)
	{
		uid = uidby;
		code = "activity_boatrob_get";
	}
	AUTO_LOCK_USER(uid)
	if (classType == 1)
		logicAdmin.AddR(uid, code, res, res, res, res);
	else if (classType == 2)//威望
	{
		unsigned balance = 0;
		ret = logicAdmin.ChangeProsper(uid, res, balance);
		if (ret != 0)
			return ret;
		RESOURCE_LOG("[Prosper][%s][uid=%u,chg=%d,Prosper=%u]",code.c_str(),uid,res,balance);
	}
	else//铜钱
	{
		Json::Value equip;
		int ret = CLogicEquipment().AddOneItem(uid, 656, res, code, result!=NULL?(*result)["equipment"]:equip, uidby>0);
		if(ret)
		{
			error_log(" set  user info failed,uid = %u",uid);
			return ret;
		}
	}
	return 0;
}

// 蛮王发排名奖励
int CLogicUpdates::sendBarbarianKingReward(unsigned uid, const Json::Value &data){
	CLogicUser logicUser;
	DataUser dataUser;
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
	{
		error_log(" get  user info failed,uid = %u",uid);
		return ret;
	}

	/*int rank = data["rank"].asInt();
	uint32_t count1 = 0;		// 随机材料
	uint32_t count2 = 0;		// 五行珠
	if (rank >= 251 && rank <= 300) {
			count1 = 5;
			count2 = 5;
	} else if (rank >= 201 && rank <= 250) {
			count1 = 10;
			count2 = 5;
	} else if (rank >= 151 && rank <= 200) {
			count1 = 10;
			count2 = 10;
	} else if (rank >= 101 && rank <= 150) {
			count1 = 15;
			count2 = 10;
	} else if (rank >= 51 && rank <= 100) {
			count1 = 15;
			count2 = 15;
	} else if (rank >= 11 && rank <= 50) {
			count1 = 20;
			count2 = 15;
	} else if (rank >= 4 && rank <= 10) {
			count1 = 20;
			count2 = 20;
	} else if (rank >= 2 && rank <= 3) {
			count1 = 30;
			count2 =20;
	} else if (rank == 1) {
			count1 = 30;
			count2 = 30;
	}
	double base = 1.0;
	int lv = dataUser.level;
	if (lv >= 90 && lv < 110)
	{
		base = 1.5;
	}
	else if (lv >= 110)
	{
		base = 2;
	}
	count1 *= base;
	count2 *= base;

	CLogicEquipment lgEq;
	Json::Value result;
	string reason = "activity_BarbarianKing_get";
	vector<ItemAdd> vecEqs;
	vecEqs.push_back(ItemAdd(ID_SUIJI_CAILIAO_BAO,count1, reason));
	vecEqs.push_back(ItemAdd(ID_WUXINGZHU,count2, reason));
	AUTO_LOCK_USER(uid)
	lgEq.AddItems(uid,vecEqs,result);*/

	int rank = data["rank"].asInt();
	unsigned count = 0;		//选择包
	if (rank >= 251 && rank <= 300)
		count = 1;
	else if (rank >= 201 && rank <= 250)
		count = 2;
	else if (rank >= 151 && rank <= 200)
		count = 3;
	else if (rank >= 101 && rank <= 150)
		count = 4;
	else if (rank >= 51 && rank <= 100)
		count = 5;
	else if (rank >= 11 && rank <= 50)
		count = 6;
	else if (rank >= 4 && rank <= 10)
		count = 7;
	else if (rank >= 2 && rank <= 3)
		count = 8;
	else if (rank == 1)
		count = 10;
	double base = 1.0;
	int lv = dataUser.level;
	if (lv >= 90 && lv < 110)
		base = 1.5;
	else if (lv >= 110)
		base = 2;
	count = (unsigned)ceil(double(count)*base);
	Json::Value result;
	AUTO_LOCK_USER(uid)
	CLogicEquipment().AddOneItem(uid, 10141, count, "activity_BarbarianKing_get", result);
	return 0;
}

int CLogicUpdates::sendProsperAndCoins(unsigned uid, const Json::Value &update, const string &reason){
	// 威望。由于命名不规范，威望有些地方用bs，有些地方用prosper
	int prosper = 0;
	if(update.isMember("bs")) {
		prosper += update["bs"].asInt();
	}
	if(update.isMember("prosper1")) {
		prosper += update["prosper1"].asInt();
	}
	if (update.isMember("prosper2")) {
		prosper += update["prosper2"].asInt();
	}
	if (update.isMember("prosper3")) {
		prosper += update["prosper3"].asInt();
	}

	CLogicAdmin logicAdmin;
	uint32_t balance;
	int retProsper = logicAdmin.ChangeProsper(uid, prosper,balance);
	RESOURCE_LOG("[%s][uid=%u,chgProsper=%d,prosper=%u]",reason.c_str(), uid,prosper,balance);

	if(retProsper) {
		error_log("change prorsper fail, uid=%u, prosper=%d", uid, prosper);
	}

	// 金币
	int coins = 0;
	if(update.isMember("coins")) {
		coins = update["coins"].asInt();
		if(coins > 0) {
			CLogicPay logicPay;
			int retCoins = logicPay.ChangePay(uid, 0, coins, reason);
			if(retCoins) {
				error_log("change coin fail, uid=%u, coins=%d", uid, coins);
			}
		}
	}

	if(update.isMember("c")) {
		unsigned c = update["c"].asUInt();
		if(c > 0)
		{
			Json::Value t;
			CLogicEquipment().AddOneItem(uid, 2034, c, reason, t);
		}
	}

	return 0;
}

// 幸运大转盘奖励
int CLogicUpdates::sendQixiRankReward(unsigned uid, const Json::Value &data){
	int rank = data["rank"].asInt();
	uint32_t itemId;
	switch(rank) {
	case 1:
		itemId = 4359;
		break;
	case 2:
		itemId = 4329;
		break;
	case 3:
		itemId = 4338;
		break;
	case 4:
		itemId = 4347;
		break;
	case 5:
		itemId = 4307;
		break;
	default:
		itemId = 0;
	}

	if (itemId == 0) {
		error_log("send qixijie Rank fail, uid=%u, rank=%d", uid, rank);
		return R_ERR_PARAM;
	}

	CLogicEquipment lgEq;
	Json::Value result;
	AUTO_LOCK_USER(uid)
	lgEq.AddOneItem(uid, itemId, 1, "activity_QixiJieRank_get", result);
	return 0;
}


// 乐不思蜀奖励
int CLogicUpdates::sendHundredDaysReward(unsigned uid, const Json::Value &update){
	int rank = update["rank"].asInt();
	int pay  = update["pay"].asInt();
	uint32_t prosper = 0;		// 威望
	uint32_t danCount = 0;	// 成长丹个数
	switch(rank) {
	case 1:
		prosper = 100000;
		danCount = 10;
		break;
	case 2:
		prosper = 80000;
		danCount = 8;
		break;
	case 3:
		prosper = 50000;
		danCount = 5;
		break;
	case 4:
		prosper = 30000;
		danCount = 3;
		break;
	case 5:
		prosper = 10000;
		danCount = 2;
		break;
	}
	AUTO_LOCK_USER(uid)
	CLogicAdmin logicAdmin;
	uint32_t banlance;
	int ret = logicAdmin.ChangeProsper(uid, prosper,banlance);
	if(ret != 0) {
		error_log("change prorsper fail, uid=%u, prosper=%d", uid, prosper);
	}
	RESOURCE_LOG("[sendHundredDaysReward][uid=%u,chgProsper=%d,prosper=%u]", uid,prosper,banlance);

	CLogicEquipment lgEq;
	Json::Value result;
	int item = 40162; // 五阶中级成长丹
	ret =lgEq.AddOneItem(uid, 40162, danCount, "activity_HundredDay_get", result);
	if(ret != 0) {
		error_log("add item fail, uid=%u, item=%d", uid, item);
	}
	if (rank == 1 && pay >= 100000) {   // 若修改武将，请通知前台做相应修改
		/*
		CLogicHero logicHero;
		logicHero.AddOneHero(uid, "H3215", "activity_HundredDay_get", result);
		*/
		ret =lgEq.AddOneItem(uid, 760, 1, "activity_HundredDay_get", result);
	}
	return ret;
}

// 周五的跨服武林大会奖励
int CLogicUpdates::sendAllServerPMatchAward(unsigned uid, const Json::Value &update){
	int rank = update["rank"].asInt();
	int level = update["level"].asInt();

	int eqNum;
	int res = 0;
	switch(rank)
	{
		case 1:
			eqNum = 500;
			switch(level)
			{
				case 1:
					res = 40000000;
					break;
				case 2:
					res = 80000000;
					break;
				case 3:
					res = 120000000;
					break;
			}

			break;
		case 2:
			eqNum = 300;
			switch(level)
			{
				case 1:
					res = 32000000;
					break;
				case 2:
					res = 64000000;
					break;
				case 3:
					res = 96000000;
					break;
			}

			break;
		case 3:
		case 4:
			eqNum = 200;
			switch(level)
			{
				case 1:
					res = 24000000;
					break;
				case 2:
					res = 48000000;
					break;
				case 3:
					res = 72000000;
					break;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			eqNum = 100;
			switch(level)
			{
				case 1:
					res = 16000000;
					break;
				case 2:
					res = 32000000;
					break;
				case 3:
					res = 48000000;
					break;
			}
			break;
		case 1000:
			eqNum = 10;
			switch(level)
			{
				case 1:
					res = 3000000;
					break;
				case 2:
					res = 5000000;
					break;
				case 3:
					res = 8000000;
					break;
			}
			break;
		default:
			res = 0;
	}

	if(res == 0) {
		error_log("sendAllServerPMatchAward fail,uid=%u, rank=%d", uid, rank);
		return R_ERR_PARAM;
	}

	CLogicEquipment lgEq;
	Json::Value result;
	lgEq.AddOneItem(uid, ID_ZHAO_MU_LING, eqNum, "activity_AllServerPMatch_get", result);
	CLogicAdmin logicAdmin;
	logicAdmin.AddR(uid, "activity_AllServerPMatch_get", res, res, res, res);
	return 0;
}

// 砸罐子奖励
int CLogicUpdates::sendPointRankReward(unsigned uid, const Json::Value &update){
//	CDataXML *pDataXML = CDataXML::GetCDataXML();
	CLogicEquipment lgEq;
	Json::Value result;
	uint32_t rank = update["rank"].asUInt();
//	uint32_t itemId = pDataXML->GetPointRank(rank);
	uint32_t itemId = 0;
	switch(rank) {
		case 1: itemId = 4438; break;
		case 2: itemId = 4427; break;
		case 3: itemId = 4436; break;
		case 4: itemId = 4456; break;
		case 5: itemId = 4446; break;
	}
	AUTO_LOCK_USER(uid)
	if (itemId != 0) {
		lgEq.AddOneItem(uid, itemId, 1, "activity_PointRank_get", result);
	} else {
		error_log("sendPointRankReward fail uid=%u,rank=%u",uid,rank);
		return R_ERR_PARAM;
	}
	return 0;
}

// 绣球结束
int CLogicUpdates::resetDragonBall(unsigned uid, const Json::Value &update){
	int deltaTime = std::min(ACTIVITY_XIUQIU_MAX,update["tm"].asInt()) + 3*5*60;
	int ballId    = update["ballid"].asInt();
	int count = deltaTime / (5*60);

	float res = 0;
	switch(ballId)
	{
		case 1:
			res = (float)count * 0.65f;
			break;
		case 2:
			res = (float)count * 1.025f;
			break;
		case 3:
			res = (float)count * 1.3f;
			break;
		case 4:
			res = (float)count * 1.45f;
			break;
		case 5:
			res = (float)count * 1.6f;
			break;
		case 6:
			res = (float)count * 1.8f;
			break;
		case 7:
			res = (float)count * 2.0f;
			break;
		default:
			res = 0;
	}

	Json::Value buildData;
	CLogicBuilding logicBuilding;
	logicBuilding.Get(uid, 1,0, true, buildData);
	int mainTownlv = buildData["l"].asInt();
	unsigned resU;
	if (mainTownlv <= 44)
		resU = res * 1.0f * 197432.0f;
	else if (mainTownlv <= 54)
		resU = res * 2.0f * 780244.0f;
	else if (mainTownlv <= 64)
		resU = res * 3.0f * 1441280.0f;
	else if (mainTownlv <= 74)
		resU = res * 4.0f * 2337979.0f;
	else if (mainTownlv <= 84)
		resU = res * 5.0f * 3975841.0f;
	else if (mainTownlv <= 94)
		resU = res * 6.0f * 4178847.0f;
	else if (mainTownlv <= 104)
		resU = res * 7.0f * 5724873.0f;
	else if (mainTownlv <= 114)
		resU = res * 8.0f * 5561200.0f;
	else
		resU = res * 9.0f * 4390365.0f;
	CLogicAdmin logicAdmin;
	AUTO_LOCK_USER(uid)
	logicAdmin.AddR(uid,"activity_xiuqiu_get", resU,resU,resU,resU);

	int eqNum = 0 ;
	if(ballId >= 1 && ballId <= 7){
		eqNum = count * 5;
	}
	CLogicEquipment lgEq;
	Json::Value result;
	lgEq.AddOneItem(uid, ID_ZHAO_MU_LING, eqNum, "activity_xiuqiu_get", result);
	return 0;
}

// 绣球易主
int CLogicUpdates::sendSnatchDragonballAward(unsigned uid, const Json::Value &update){
	int deltaTime = std::min(ACTIVITY_XIUQIU_MAX,update["tm"].asInt());
	int ballId    = update["ballid"].asInt();
	int count = deltaTime / (5*60);

	float res = 0;
	switch(ballId)
	{
		case 1:
			res = (float)count * 0.65f;
			break;
		case 2:
			res = (float)count * 1.025f;
			break;
		case 3:
			res = (float)count * 1.3f;
			break;
		case 4:
			res = (float)count * 1.45f;
			break;
		case 5:
			res = (float)count * 1.6f;
			break;
		case 6:
			res = (float)count * 1.8f;
			break;
		case 7:
			res = (float)count * 2.0f;
			break;
		default:
			res = 0;
	}

	Json::Value buildData;
	CLogicBuilding logicBuilding;
	logicBuilding.Get(uid, 1,0, true, buildData);
	int mainTownlv = buildData["l"].asInt();
	unsigned resU;
	if (mainTownlv <= 44)
		resU = res * 1.0f * 197432.0f;
	else if (mainTownlv <= 54)
		resU = res * 2.0f * 780244.0f;
	else if (mainTownlv <= 64)
		resU = res * 3.0f * 1441280.0f;
	else if (mainTownlv <= 74)
		resU = res * 4.0f * 2337979.0f;
	else if (mainTownlv <= 84)
		resU = res * 5.0f * 3975841.0f;
	else if (mainTownlv <= 94)
		resU = res * 6.0f * 4178847.0f;
	else if (mainTownlv <= 104)
		resU = res * 7.0f * 5724873.0f;
	else if (mainTownlv <= 114)
		resU = res * 8.0f * 5561200.0f;
	else
		resU = res * 9.0f * 4390365.0f;
	CLogicAdmin logicAdmin;
	AUTO_LOCK_USER(uid)
	logicAdmin.AddR(uid,"activity_xiuqiu_get", resU,resU,resU,resU);

	int eqNum = 0 ;
	if(ballId >= 1 && ballId <= 7){
		eqNum = count * 5;
	}
	CLogicEquipment lgEq;
	Json::Value result;
	int ret = lgEq.AddOneItem(uid, ID_ZHAO_MU_LING, eqNum, "activity_xiuqiu_get", result);

	return 0;
}

// 开区活动战力排名奖励
int CLogicUpdates::sendPowerRankReward(unsigned uid, const Json::Value &update) {
//	第2-3名      H3109        40123  10个
//	第4-10名    金币*100      40123  5
//	swise(苏安) 14:12:44
//	 {"hero1" : {"id":3001, "c":1, "q":0}, "equip1" : {"id":40123, "c":20, "q":0}}}]]></reward>
	int rank = update["rank"].asInt();
	string sHero;
	int eqNum = 0;
	int coins = 0;
	if (rank == 1) {
		sHero = "H3001";
		eqNum = 20;
	} else if (rank == 2 || rank == 3) {
		sHero = "H3022";
		eqNum = 10;
	} else if (4 <= rank && rank <= 10) {
		coins = 100;
		eqNum = 5;
	}

	AUTO_LOCK_USER(uid)
	Json::Value result;
	if (!sHero.empty()) {
		CLogicHero logicHero;
		int ret = logicHero.AddOneHero(uid, sHero, "activity_activityherotop_get", result);
		if(ret) {
			error_log("add hero fail, uid=%u, Hero=%s", uid, sHero.c_str());
		}
	}

	CLogicEquipment lgEq;
	int ret = lgEq.AddOneItem(uid, 40123, eqNum, "activity_activityherotop_get", result);
	if(ret) {
		error_log("add equipment fail, uid=%u, eq=%d, count=%d", uid, 40123, eqNum);
	}

	if (coins > 0) {
		CLogicPay logicPay;
		int retCoins = logicPay.ChangePay(uid, 0, coins, "activity_activityherotop_get");
		if(retCoins) {
			error_log("change coin fail, uid=%u, coins=%d", uid, coins);
		}
	}
	return 0;
}

// 开区活动掠夺排名奖励
int CLogicUpdates::sendAttackRankReward(unsigned uid, const Json::Value &update) {

//	reward>
//	<![CDATA[{"reward" : {"equip1":{"id":42010, "c":20, "q":0}, "equip2":{"id":4015, "c":6, "q":0}, "equip3":{"id":4206, "c":10, "q":0}, "equip4":{"id":11112, "c":20, "q":0}}}]]>
//	</reward> -<reward>
//	<![CDATA[{"reward" : {"equip1":{"id":42010, "c":10, "q":0}, "equip2":{"id":4015, "c":3, "q":0}, "equip3":{"id":4204, "c":10, "q":0}, "equip4":{"id":11112, "c":10, "q":0}}}]]>
//	</reward> -<reward>
//	<![CDATA[{"reward" : {"equip1":{"id":42010, "c":5, "q":0}, "equip2":{"id":4015, "c":5, "q":0}, "equip3":{"id":4203, "c":5, "q":0}, "equip4":{"id":11112, "c":5, "q":0}}}]]>
//	</reward>

	int rank = update["rank"].asInt();
	vector<ItemAdd> vecEqs;
	string reason = "activity_activityroottop10_get";
	if (rank == 1) {
		vecEqs.push_back(ItemAdd(42010,20,reason));
		vecEqs.push_back(ItemAdd(4015,6,reason));
		vecEqs.push_back(ItemAdd(4206,10,reason));
		vecEqs.push_back(ItemAdd(11112,20,reason));
	} else if (rank == 2 || rank == 3) {
		vecEqs.push_back(ItemAdd(42010,10,reason));
		vecEqs.push_back(ItemAdd(4015,3,reason));
		vecEqs.push_back(ItemAdd(4204,10,reason));
		vecEqs.push_back(ItemAdd(11112,10,reason));
	} else if (4 <= rank && rank <= 10) {
		vecEqs.push_back(ItemAdd(42010,5,reason));
		vecEqs.push_back(ItemAdd(4015,5,reason));
		vecEqs.push_back(ItemAdd(4203,5,reason));
		vecEqs.push_back(ItemAdd(11112,5,reason));
	}

	Json::Value result;
	CLogicEquipment lgEq;
	AUTO_LOCK_USER(uid)
	int ret = lgEq.AddItems(uid, vecEqs,result);
	if(ret) {
		error_log("add equipment fail, uid=%u", uid);
	}
	return 0;
}
