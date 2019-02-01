#include "LogicInc.h"

class CCgiAllServerGroupBuying : public CCgiBase
{
public:
	CCgiAllServerGroupBuying() : CCgiBase("AllServerGroupBuying")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);

		int ret = CLogicAllServerGroupBuying::Init(CONFIG_ALLSERVER_GROUPBUYING_PATH, true);
		if(ret)
			exit(ret);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("load", Load)		//加载团购数据
	CGI_SET_ACTION_MAP("join", Join)		//加入团购

	CGI_ACTION_MAP_END

	~CCgiAllServerGroupBuying()
	{
		CLogicAllServerGroupBuying::Exit();
	}

	void ProcessSig(int sig)
	{
		CLogicAllServerGroupBuying::Sig(sig);
	}

	int Load()
	{
		string struid = CCGIIn::GetCGIStr("uid");

		if (struid.empty())
		{
			error_log("param error.");
			return R_ERR_PARAM;
		}

		unsigned uid = CTrans::STOI(struid);

		try
		{
			CLogicAllServerGroupBuying logicgroup;
			int ret = logicgroup.Load(uid, m_jsonResult);

			if (ret != R_SUCCESS) return ret;
		}
		catch(exception &e)
		{
			::SetError(R_ERROR, e.what());
			error_log("%s", e.what());

			return R_ERROR;
		}

		CGI_SEND_LOG("action=Load");

		return R_SUCCESS;
	}

	int Join()
	{
		string struid = CCGIIn::GetCGIStr("uid");
		string sid = CCGIIn::GetCGIStr("id");

		if (struid.empty())
		{
			return R_ERR_PARAM;
		}

		if (struid.empty() || sid.empty())
		{
			error_log("param error.");
			return R_ERR_PARAM;
		}

		unsigned uid = CTrans::STOI(struid);
		unsigned id = CTrans::STOI(sid);

		CLogicAllServerGroupBuying logicgroup;

		try
		{
			int ret = logicgroup.Join(uid, id, m_jsonResult);

			if (ret != R_SUCCESS) return ret;
		}
		catch(exception &e)
		{
			::SetError(R_ERROR, e.what());
			error_log("%s", e.what());

			return R_ERROR;
		}

		CGI_SEND_LOG("action=Join");

		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiAllServerGroupBuying)


