/*
 * CgiBase.h
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#ifndef CGIBASE_H_
#define CGIBASE_H_

#include "LogicInc.h"

enum CgiFeature
{
	CF_PRINT_JSON = 1,	//Json输出
	CF_GET_REMOTE_IP,	//获取请求方IP
	CF_GET_UID,	//获取用户ID
	CF_CHECK_SESSION,	//检验Session
	CF_CHECK_TIME,	//校验时间
	CF_CHECK_PLATFORM,	//校验平台
	CF_CHECK_HASH,	//校验KEY
	CF_APPEND_HASH,	//增加校验KEY
	CF_PARSE_DATA,	//解析DATA
	CF_CRYPT_DATA, //加密DATA
	CF_DECRYPT_DATA,	//解密DATA
	CF_COMPRESS_OUT,	//压缩输出
	CF_TOTAL	//CGI特性总数
};

class CCgiBase
{

public:

	CCgiBase(const string &cgiName = NULL);
	virtual ~CCgiBase();

	virtual int Run();
	virtual int RunOnce();
	virtual int Process() = 0;

	string GetCgiName();

	void SetFeature(int feature);

	int Initialize();
	int GetRemoteIp();
	int GetUid();
	int CheckSession();
	int CheckTime();
	int CheckHash();
	int ParseData();
	int DecryptData();

	void PrintResult(int result = 0);

	string GetHash(const string &data, const string &hn);

protected:

	int m_features[CF_TOTAL];			/* 校验标志 */

	string m_cgiName;	//CGI名
	string m_actionName;	//操作名

	unsigned int m_remoteip;				/* 请求方IP*/
	string m_ipstr;
	unsigned int m_uid;	//登录用户UID
	string m_skey;	//登录会话KEY

	string m_strData;	//解码数据
	Json::Value m_data;	//输入数据
	Json::Value m_jsonResult;				/* 返回数据 */

};

class CCgiManager
{
public:
	int Run();
	int RegisterCgi(CCgiBase *pCgi);
protected:
	vector<CCgiBase *> m_cgiList;
};

#define MERGE_CGI

#define CGI_SEND_LOG(...) SEND_LOG(m_cgiName.c_str(), CCGIIn::GetStrRemoteIP(), __VA_ARGS__)

#define CGI_DIRECT_PROCESS(ActionCallback)	\
virtual int Process()	\
{	\
	int result = ActionCallback();	\
	return result;	\
}	\

#define CGI_SIMPLE_ACTION_MAP_BEGIN	\
virtual int Process()	\
{	\
	int result = R_SUCCESS;	\
	m_actionName = CCGIIn::GetCGIStr("action");	\

#define CGI_ACTION_MAP_BEGIN	\
virtual int Process()	\
{	\
	int result = R_SUCCESS;	\
	if(!Json::GetString(m_data, "action", m_actionName))	\
	{	\
		SetError(R_ERR_PARAM);	\
		return R_ERR_PARAM;	\
	}	\

#define CGI_SET_ACTION_MAP(ActionName, ActionCallback)	\
	if(m_actionName == ActionName)	\
	{	\
		result = ActionCallback();	\
	}	\
	else	\

#define CGI_ACTION_MAP_END	\
	{	\
		SetError(R_ERR_PARAM);	\
		return R_ERR_PARAM;	\
	}	\
	return result;	\
}	\

#ifdef MERGE_CGI

#define CGI_MAIN(CgiClass)

#define CGI_MAIN_BEGIN	\
int main(int argc, char *argv[])	\
{	\
	if(!Kernel::Init())	\
	{	\
		fatal_log("[Kernel::Init fail][cgi=%s]", argv[0]);	\
		return -1;	\
	}	\
	CCgiManager cgiManager;	\

#define CGI_REGISTER(cgi)	\
	cgi v##cgi;	\
	cgiManager.RegisterCgi(&v##cgi);	\

#define CGI_MAIN_END	\
	int result = cgiManager.Run();	\
	return result;	\
}	\

#else

#define CGI_MAIN(CgiClass)	\
int main()	\
{	\
	if(!Kernel::Init())	\
	{	\
		fatal_log("[Kernel::Init fail][cgi=%s]", #CgiClass);	\
		return -1;	\
	}	\
	CgiClass cgi;	\
	int result = cgi.Run();	\
	return result;	\
}	\

#endif

#endif /* CGIBASE_H_ */