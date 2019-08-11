#ifndef _FD_MANAGER_H_
#define _FD_MANAGER_H_

#include "Kernel.h"
#include <map>
#include <string>
#include <stdint.h>

using namespace std;

typedef struct FDINFO {
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;
	bool operator !=(const FDINFO& fdInfo) {
		return fdInfo.fd != fd || fdInfo.time != time || fdInfo.microTime != microTime;
	}

	bool operator ==(const FDINFO& fdInfo) {
		return fdInfo.fd == fd && fdInfo.time == time && fdInfo.microTime == microTime;
	}
} FDINFO;

class FdManager: public CSingleton<FdManager> {
private:
	friend class CSingleton<FdManager> ;
	FdManager();
public:
	void addMap(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t rid);
	void delMap(uint32_t fd, uint32_t time, uint32_t microTime);
	bool getFd(uint32_t rid, uint32_t& fd, uint32_t& time, uint32_t& microTime);
	bool getRole(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t& rid);
	bool getFdInfo(uint32_t rid, FDINFO& fdInfo);
	bool getAllFd(vector<FDINFO>& vecFd);
	bool getAllUid(vector<uint32_t> &uids);
private:
	map<string, uint32_t> fdMap;
	map<uint32_t, FDINFO> roleMap;
};

#endif
