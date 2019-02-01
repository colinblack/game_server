#include "LogicInc.h"
#include "DataUserMapping.h"

class CCgiSelectServer : public CCgiBase
{
public:
	string defaultServerCN;
	string defaultServerVN;

	CCgiSelectServer() : CCgiBase("selectserver")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int domainCN=0;
		int domainVN=0;
		set<int> domains;
		MainConfig::GetDomains(domains);
		for(set<int>::iterator it=domains.begin();it!=domains.end();++it)
		{
			if(*it < 101)
			{
				if(*it > domainCN)
					domainCN = *it;
			}
			else
			{
				if(*it > domainVN)
					domainVN = *it;
			}
		}
		domains.clear();
		MainConfig::GetIncludeDomains(domainCN,domains);
		for(set<int>::iterator it=domains.begin();it!=domains.end();++it)
		{
			if(*it > domainCN)
				domainCN = *it;
		}
		domains.clear();
		MainConfig::GetIncludeDomains(domainVN,domains);
		for(set<int>::iterator it=domains.begin();it!=domains.end();++it)
		{
			if(*it > domainVN)
				domainVN = *it;
		}
		defaultServerCN = CTrans::ITOS(domainCN);
		defaultServerVN = CTrans::ITOS(domainVN);
	}

	CGI_DIRECT_PROCESS(SelectServer)

	int SelectServer()
	{
		string last,now;
		const string openid = CCGIIn::GetCGIStr("openid");
		const string locale = CCGIIn::GetCGIStr("locale");

		string defaultServer = defaultServerCN;
		if(locale == "vi_VN")
			defaultServer = defaultServerVN;

		if (openid.empty())
		{
			CgiUtil::PrintText(defaultServer+"_"+defaultServer);
			return 0;
		}

		unsigned serverid = 0;
		unsigned lastlogin = 0;
		CDataUserMapping db;
		vector<server> servers;
		if(db.GetServer(openid, servers) == 0)
		{
			for(vector<server>::iterator it=servers.begin();it!=servers.end();++it)
			{
				if((*it).lastlogin > lastlogin)
				{
					lastlogin = (*it).lastlogin;
					serverid = (*it).serverid;
				}
			}
			if(!serverid)
				CgiUtil::PrintText(defaultServer+"_"+defaultServer);
			else
				CgiUtil::PrintText(CTrans::ITOS(serverid)+"_"+defaultServer);
		}
		else
		{
			CgiUtil::PrintText(defaultServer+"_"+defaultServer);
			error_log("GetServer failed, openid=%s", openid.c_str());
			return 0;
		}

		CGI_SEND_LOG("openid=%s&last=%s&now=%s", openid.c_str(),last.c_str(),now.c_str());
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiSelectServer)
