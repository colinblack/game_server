/*
 * LogicActQunXing.cpp
 *
 *  Created on: 2019年7月9日
 *      Author: Administrator
 */

#include "LogicQunXing.h"

CLogicQunXing::CLogicQunXing() {
}

CLogicQunXing::~CLogicQunXing() {
}

int CLogicQunXing::GetInfo(unsigned uid, unsigned type, Json::Value &value) {
	int ret = 0;
	CDataQunXing *pdata = GetData();
	if (pdata == NULL) {
		error_log("get data error!");
		return R_ERR_DATA;
	}

	CDataUserBasic dbUserBasic;
	DataUserBasic user_basic;
	ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, user_basic);
	if (0 != ret) {
		error_log("get user basic error uid=%u ret=%d", uid, ret);
	}

	CActQunXing act;
	ret = act.Init(uid, ACTIVITY_TIME_QUNXING);
	if (0 != ret) {
		error_log("act init error uid=%u", uid);
		return ret;
	}

	unsigned charge = act.GetTotalCharge();
	const WuhunActivity::QunXingHuiJu &cfg = WuhunActivityWrap().GetQunXingHuiJu();
	for (int i = 0; i < cfg.yanhui_size(); ++i) {
		if (charge >= cfg.yanhui(i).need()) {
			ret = pdata->AddTable(uid, i, user_basic.name);
			if (0 == ret) {
				ORDERS_LOG("uid=%u&code=addqunxingtable_%d&amount=1&type=0", uid, i);
			}
		}
	}

	ret = pdata->GetInfo(uid, type, value);
	if (0 != ret) {
		return ret;
	}

	act.GetInfo(value);

	return 0;
}

int CLogicQunXing::AddGuest(unsigned uid, unsigned type, unsigned id, unsigned hud, unsigned hid, unsigned power, const string &smid, const string &hname, Json::Value &value) {
	int ret = 0;
	CDataUserBasic dbUserBasic;
	DataUserBasic user_basic;
	ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, user_basic);
	if (0 != ret) {
		error_log("get user basic error uid=%u ret=%d", uid, ret);
	}

	CDataQunXing *pdata = GetData();
	if (pdata == NULL) {
		error_log("get data error!");
		return R_ERR_DATA;
	}

	unsigned ledder = 0;
	QunXingGuest info;
	info.uid = uid;
	info.hid = hid;
	info.smid = smid;
	info.power = power;
	info.name = user_basic.name;
	info.hname = hname;
	ret = pdata->AddGuest(id, type, hud, info, ledder);
	if (0 != ret) {
		error_log("add guest error uid=%u type=%u id=%u", uid, type, id);
		return ret;
	}

	unsigned point = 0;
	pdata->GetPoint(ledder, point);
	if (point != 0) {
		CActQunXing act;
		ret = act.Init(ledder, ACTIVITY_TIME_QUNXING);
		if (0 == ret) {
			AUTO_LOCK_USER(ledder);
			act.SetPoint(point);
		} else {
			error_log("act init error uid=%u", ledder);
		}
	}
	CActQunXing act;
	ret = act.Init(uid, ACTIVITY_TIME_QUNXING);
	if (0 == ret) {
		act.AddJinDu();
	} else {
		error_log("act init error uid=%u", uid);
	}

	ORDERS_LOG("uid=%u&code=addqunxingguest_%u&amount=1&type=0", ledder, uid);

	ret = pdata->GetInfo(uid, type, value);
	if (0 != ret) {
		return ret;
	}

	act.GetInfo(value);
	return 0;
}

int CLogicQunXing::DelGuest(unsigned uid, unsigned type, unsigned id, unsigned userid, Json::Value &value) {
	int ret = 0;
	CDataQunXing *pdata = GetData();
	if (pdata == NULL) {
		error_log("get data error!");
		return R_ERR_DATA;
	}
	ret = pdata->DelGuest(id, type, uid, userid);
	if (0 != ret) {
		error_log("del guest error id=%u type=%u uid=%u userid=%u", id, type, uid, userid);
		return ret;
	}
	ret = pdata->GetInfo(uid, type, value);
	if (0 != ret) {
		return ret;
	}
	CActQunXing act;
	ret = act.Init(uid, ACTIVITY_TIME_QUNXING);
	if (0 == ret) {
		act.GetInfo(value);
	} else {
		error_log("act init error uid=%u", uid);
	}
	return 0;
}
