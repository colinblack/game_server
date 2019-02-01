/*
 * CgiTest.cpp
 *
 *  Created on: 2011-10-19
 *      Author: dada
 */

#include "LogicInc.h"

class CCgiDataReport : public CCgiBase
{

public:

	CCgiDataReport() : CCgiBase("datareport")
	{
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_PRINT_JSON);
	}

	CGI_DIRECT_PROCESS(DataReport)

	int DataReport()
	{
		int ret;
		string data = CCGIIn::GetCGIStr("data");
		if(data.size() <= 0 || data.size() > 1000)
		{
			return R_ERR_PARAM;
		}

		//feed奖励
		if(OpenPlatform::GetType() == PT_WEIYOUXI && String::StartWith(data, "sendfeed&"))
		{
			string openid;
			string openkey;
			if( String::FindMatch(openid, data, "openid=", "&", true) &&
				String::FindMatch(openkey, data, "openkey=", "&", true) )
			{
				unsigned uid;
				ret = LogicSso::GetLoginUid(uid, openid, openkey);
				if(ret == 0)
				{
					Json::Value userExtraData;
					ret = LogicUser::GetExtraData(uid, userExtraData);
					if (ret == 0)
					{
						Json::Value &feedReward = userExtraData["fdrw"];
						if (!feedReward.isArray() || feedReward.size() != 2)
						{
							feedReward = Json::Value(Json::arrayValue);
							feedReward[0u] = Time::GetGlobalTime();
							feedReward[1u] = 0;
						}
						unsigned lastTime;
						int lastCount;
						Json::GetUInt(feedReward, 0u, lastTime);
						Json::GetInt(feedReward, 1u, lastCount);
						if (!Time::IsToday(lastTime))
						{
							lastTime = Time::GetGlobalTime();
							lastCount = 0;
						}
						if (lastCount < 5)
						{
							CLogicPay logicPay;
							ret = logicPay.ChangeCash(uid, "FDRW", 1);
							if (ret == 0)
							{
								lastCount++;
								feedReward[0u] = lastTime;
								feedReward[1u] = lastCount;
								LogicUser::SetExtraData(uid, userExtraData);
								CLogicMessage logicMsg;
								string message;
								String::Format(message, "{\"id\":\"feedReward\",\"cash\":1,\"ts\":%u,\"count\":%d}",
										Time::GetGlobalTime(), lastCount);
								ret = logicMsg.AddSysMessage(uid, message);
							}
						}
					}
				}
			}
		}

		CGI_SEND_LOG("platfrom=%d&data=%s", OpenPlatform::GetType(), data.c_str());
		return 0;
	}

};

CGI_MAIN(CCgiDataReport)
