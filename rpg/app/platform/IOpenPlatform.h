/*
 * IOpenPlatform
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#ifndef _IOPENPLATFORM_H_
#define _IOPENPLATFORM_H_

#include "Common.h"

enum PlatformType {
	PT_UNKNOW = -1,		//未知
	PT_TEST = 0,		//测试平台
	PT_MAX
};

enum Gender {
	GD_UNKNOW = -1,	//未知
	GD_FEMALE = 0,	//女
	GD_MALE = 1		//男
};

//开放平台用户基本信息
struct OPUserInfo {
public:
	string OpenId;	//平台ID
	string Name;	//姓名
	int Gender;	//性别： -1 - 未知; 0 - 女; 1 - 男
	string FigureUrl;	//头像URL
	string Nation;	//国家
	string Province;	//省份
	string City;	//城市
	map<string, int> ExtraIntInfo;	//其他数值信息
	map<string, unsigned> ExtraUIntInfo;	//其他数值信息
	map<string, string> ExtraStrInfo;	//其他字符串信息
public:
	OPUserInfo() {
		Gender = GD_UNKNOW;
	}
	void Clear() {
		OpenId.clear();
		Name.clear();
		Gender = GD_UNKNOW;
		FigureUrl.clear();
		Nation.clear();
		Province.clear();
		City.clear();
		ExtraIntInfo.clear();
		ExtraStrInfo.clear();
	}

};

//开放平台好友列表
typedef vector<string> OPFriendList;

//开放平台接口
class IOpenPlatform {
public:
	//初始化
	//输入参数：appid - 平台应用ID
	//			appkey - 平台应用KEY
	//			params - 其他参数
	//返回值：0 - 成功; 否则失败，错误信息见GetErrorMessage()
	virtual int Initialize(const string &appid, const string &appkey, map<string, string> &params);

	//获取平台类型
	virtual PlatformType GetPlatformType() = 0;

	//获取平台应用ID
	virtual const string &GetAppId() {
		return m_appId;
	}

	//获取平台应用KEY
	virtual const string &GetAppKey() {
		return m_appKey;
	}

	//获取用户信息
	//输入参数：openid - 用户平台ID
	//输入参数： openkey - 用户KEY
	//输出参数：userInfo - 用户信息
	//返回值：0 - 成功; 否则失败，错误信息见GetErrorMessage()
	virtual int GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string &pf, const string &userip) {
		return -1;
	}

	//获取平台VIP等级
	//返回值：0 - 成功; 否则失败，错误信息见GetErrorMessage()
	virtual int GetVipInfo(const string &openid, const string &openkey, const string &pf, const string &userip, uint32_t &vip) {
		return -1;
	}

	//获取应用好友列表
	//输入参数：openid - 用户平台ID
	//			openkey - 用户KEY
	//输出参数：friendList - 应用好友OpenId列表
	//返回值：0 - 成功; 否则失败，错误信息见GetErrorMessage()
	virtual int GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey, const string &pf, const string &userip) {
		return -1;
	}

	//获取全部好友列表
	//返回值：0 - 成功; 否则失败，错误信息见GetErrorMessage()
	virtual int GetFriendList(vector<OPUserInfo> &friendList, const string &openid, const string &openkey) {
		return -1;
	}

	//设置参数
	virtual void SetParameter(const map<string, string> &params) {
	}

	//获取错误信息
	virtual string GetErrorMessage() = 0;

	//获取配置参数
	virtual string GetConfig(const string &name);

	//openkey续期
	virtual int IsLogin(const string &openid, const string &openkey, const string &pf) {
		return -1;
	}

	//敏感词检测
	virtual int WordFilter(const string &openid, const string &openkey, const string &name, const string &pf, const string &userip) {
		return -1;
	}

	//礼包兑换
	virtual int GiftExchange(const string &openid, const string &openkey, const string &pf, const string &userip, const string &giftid, int &code) {
		return -1;
	}

	//发送消息
	virtual int SendGameBarMsg(const string &openid, const string &openkey, const string &pf, const string &userip, const string &frd, int type, const string &msg, const string &qua) {
		return -1;
	}

	virtual ~IOpenPlatform() {
	}

protected:

	string m_appId;
	string m_appKey;
	map<string, string> m_config;

};

#endif	//_IOPENPLATFORM_H_
