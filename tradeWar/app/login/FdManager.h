#ifndef _FD_MANAGER_H_
#define _FD_MANAGER_H_

#include "Kernel.h"
#include <map>
#include <string>
#include <stdint.h>

using namespace std;

typedef struct FDINFO
{
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;
	uint32_t spanId;
	uint32_t srvId;
	inline bool operator !=(const FDINFO& fdInfo) const
	{
		return fdInfo.fd != fd || fdInfo.time != time || fdInfo.microTime != microTime;
	}
	inline bool operator ==(const FDINFO& fdInfo) const
	{
		return fdInfo.fd == fd && fdInfo.time == time && fdInfo.microTime == microTime;
	}
} FDINFO;

typedef struct
{
	uint32_t uid;
	uint32_t rid;
} USERINFO;

class FdManager
{
private:
	FdManager();
public:
	static FdManager* getInstance();
public:
	int addMap(uint32_t fd, uint32_t time, uint32_t micorTime, uint32_t uid, uint32_t rid, uint32_t spanId, uint32_t srvId);
	void delMap(uint32_t fd, uint32_t time, uint32_t micorTime);
	bool getFd(uint32_t uid, uint32_t& fd, uint32_t& time, uint32_t& microTime);
	bool getRole(uint32_t fd, uint32_t time, uint32_t micorTime, uint32_t& uid, uint32_t& rid);
	void setChannel(CTcpChannel* pChannel)
	{
		this->pChannel = pChannel;
	}
	bool sendMsg(const IBuffer* pBuffer)
	{
		return pChannel->SendData(pBuffer);
	}
	bool getFdInfo(uint32_t uid, FDINFO& fdInfo);
	bool closeAll();
	bool getAllFd(vector<FDINFO>& vecFd);
	uint32_t getFdCount()
	{
		return roleMap.size();
	}
private:
	map<string, USERINFO> fdMap;
	map<uint32_t, FDINFO> roleMap;
	CTcpChannel* pChannel;
};

#endif
