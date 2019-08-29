/*
 * TestPlatfrom.cpp
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#include "TestPlatform.h"

#define KEY_USER_DATA "user_data"

int CTestPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params) {
	IOpenPlatform::Initialize(appid, appkey, params);
	m_userData = params["user_data"];
	if (!File::IsExist(m_userData)) {
		info_log("[user data no exist, create][file=%s]", m_userData.c_str());
		int result = File::Write(m_userData, "\n");
		if (result != 0) {
			error_log("[create user data fail][result=%d]", result);
			return result;
		}
	}
	return 0;
}

int CTestPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string &pf, const string &userip) {
	userInfo.OpenId = openid;
	userInfo.Name = openid;
	userInfo.Gender = GD_UNKNOW;
	string content;
	int result = File::Read(m_userData, content);
	if (result != 0) {
		error_log("[read user data fail][result=%d]", result);
		return result;
	}
	string sFind = string("\n") + openid + "\n";
	if (content.find(sFind) == string::npos) {
		result = File::Append(m_userData, openid + "\n");
		if (result != 0) {
			error_log("[append user data fail][result=%d]", result);
		}
	}
	return 0;
}

int CTestPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey, const string &pf, const string &userip) {
	string content;
	int result = File::Read(m_userData, content);
	if (result != 0) {
		error_log("[read user data fail][result=%d]", result);
		return result;
	}
	OPFriendList allUserList;
	CBasic::StringSplitTrim(content, "\n", allUserList);
	int index = -1;
	for (unsigned i = 0; i < allUserList.size(); i++) {
		if (allUserList[i] == openid) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		error_log("[user data find fail][openid=%s]", openid.c_str());
		return -1;
	}
	int startIndex = index - 5;
	if (startIndex < 0) {
		startIndex = 0;
	}
	int endIndex = index + 5;
	if (endIndex > (int) allUserList.size()) {
		endIndex = allUserList.size();
	}
	friendList.clear();
	for (int i = startIndex; i < endIndex; i++) {
		friendList.push_back(allUserList[i]);
	}
	return 0;
}

int CTestPlatform::GetVipInfo(const string &openid, const string &openkey, const string &pf, const string &userip, uint32_t &vip) {
	vip = CTrans::STOI(GetConfig("vip"));
	return 0;
}

int CTestPlatform::GiftExchange(const string &openid, const string &openkey, const string &pf, const string &userip, const string &giftid, int &code) {
	code = 0;
	return 0;
}
