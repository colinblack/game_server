#include "FdManager.h"
#include <stdio.h>

FdManager::FdManager() {
}

void FdManager::addMap(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t rid) {
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	FDINFO fi;
	fi.fd = fd;
	fi.time = time;
	fi.microTime = microTime;
	fdMap[buf] = rid;
	roleMap[rid] = fi;
}

void FdManager::delMap(uint32_t fd, uint32_t time, uint32_t microTime) {
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	map<string, uint32_t>::iterator it1 = fdMap.find(buf);
	if (it1 != fdMap.end()) {
		fdMap.erase(it1);
		FDINFO fdInfo;
		fdInfo.fd = fd;
		fdInfo.time = time;
		fdInfo.microTime = microTime;
		map<uint32_t, FDINFO>::iterator it2 = roleMap.find(it1->second);
		if (it2 != roleMap.end() && it2->second == fdInfo) {
			roleMap.erase(it2);
		}
	}
}

bool FdManager::getFd(uint32_t rid, uint32_t& fd, uint32_t& time, uint32_t& microTime) {
	map<uint32_t, FDINFO>::iterator it = roleMap.find(rid);
	if (it == roleMap.end()) {
		return false;
	}
	fd = it->second.fd;
	time = it->second.time;
	microTime = it->second.microTime;
	return true;
}

bool FdManager::getRole(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t& rid) {
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	map<string, uint32_t>::iterator it = fdMap.find(buf);
	if (it == fdMap.end()) {
		return false;
	}
	rid = it->second;
	return true;
}

bool FdManager::getFdInfo(uint32_t rid, FDINFO& fdInfo) {
	map<uint32_t, FDINFO>::iterator it = roleMap.find(rid);
	if (it == roleMap.end()) {
		return false;
	}
	fdInfo = it->second;
	return true;
}

bool FdManager::getAllFd(vector<FDINFO>& vecFd) {
	vecFd.clear();
	for (map<uint32_t, FDINFO>::iterator it = roleMap.begin(); it != roleMap.end(); ++it) {
		vecFd.push_back(it->second);
	}
	return true;
}

bool FdManager::getAllUid(vector<uint32_t> &uids) {
	for (map<uint32_t, FDINFO>::iterator it = roleMap.begin(); it != roleMap.end(); ++it) {
		uids.push_back(it->first);
	}
	return true;
}

