#ifndef _BUSINESS_LOG_
#define _BUSINESS_LOG_

#include <string>

#define COINS_LOG(fmt,args...) CBusinessLogHelper::GetInstance("coins")->Log(fmt,##args)
#define RESOURCE_LOG(fmt,args...) CBusinessLogHelper::GetInstance("resource")->Log(fmt,##args)
#define ORDERS_LOG(fmt,args...) CBusinessLogHelper::GetInstance("orders")->Log(fmt,##args)
#define HERO_LOG(fmt,args...) CBusinessLogHelper::GetInstance("hero")->Log(fmt,##args)
#define EQUIPMENT_LOG(fmt,args...) CBusinessLogHelper::GetInstance("equipment")->Log(fmt,##args)
#define OLUSER_LOG(fmt,args...) CBusinessLogHelper::GetInstance("onlineuser")->Log(fmt,##args)

class CBusinessLog
{
public:
	CBusinessLog(const std::string &name);
	void Log(const char* format, ...);

protected:
	std::string m_name;
	int m_fd;
	int m_day;
};

class CBusinessLogHelper
{
public:
	static CBusinessLog * GetInstance(const std::string &name);
};

#endif
