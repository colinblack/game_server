/*
 * CgiQQHallReport.cpp
 *
 *  Created on: 2016-4-15
 *      Author: dawx62fac
 */

#include "LogicInc.h"
#include "LogicQQReport.h"



class CCgiQQHallReport : public CCgiBase
{
public:
	CCgiQQHallReport() : CCgiBase("qqhallreport")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
	}

	CGI_DIRECT_PROCESS(report);

	int report()
	{
		try
		{
			CLogicQQReport logicReport;

			//登录数据
			QQHallLoginSdk loginApi(*this, m_data);
			logicReport.HallAction(loginApi);

			//基本数据
			QQHallGenerallApi userApi(*this, m_data);
			logicReport.HallAction(userApi);

			//公会数据
			QQHallUnionApi unionApi(*this, m_data);
			logicReport.HallAction(unionApi);

			//全量数据排名
			QQAllRankApi rankApi(*this, m_data, m_data["rank_list"]);
			logicReport.HallAction(rankApi);

		}
		catch (std::exception& e)
		{
			error_log("%s", e.what());
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiQQHallReport)




