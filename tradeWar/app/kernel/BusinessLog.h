#ifndef _BUSINESS_LOG_
#define _BUSINESS_LOG_

#include <string>

#define COINS_LOG(fmt,args...) CBusinessLogHelper::GetInstance("coins")->Log(fmt,##args)
#define RESOURCE_LOG(fmt,args...) CBusinessLogHelper::GetInstance("resource")->Log(fmt,##args)
#define ORDERS_LOG(fmt,args...) CBusinessLogHelper::GetInstance("orders")->Log(fmt,##args)
#define HERO_LOG(fmt,args...) CBusinessLogHelper::GetInstance("hero")->Log(fmt,##args)
#define EQUIPMENT_LOG(fmt,args...) CBusinessLogHelper::GetInstance("equipment")->Log(fmt,##args)
#define SPEED_LOG(fmt, args...) CBusinessLogHelper::GetInstance("speed")->Log(fmt,##args)
#define EXECTIME_LOG(fmt, args...) CBusinessLogHelper::GetInstance("exectime")->Log(fmt,##args)
#define ATTACK_LOG(fmt, args...) CBusinessLogHelper::GetInstance("attacklog")->Log(fmt,##args)
#define PACKET_LOG(fmt, args...) CBusinessLogHelper::GetInstance("packet")->Log(fmt,##args)
#define ONLINE_LOG(fmt, args...) CBusinessLogHelper::GetInstance("online")->Log(fmt,##args)

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