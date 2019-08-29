#include "FdManager.h"
#include <stdio.h>

FdManager::FdManager()
{
	pChannel = NULL;
}

FdManager* FdManager::getInstance()
{
	static FdManager manager;
	return &manager;
}

int FdManager::addMap(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t uid, uint32_t rid, uint32_t spanId, uint32_t srvId)
{
	int ret = 0;
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	USERINFO ui;
	ui.rid = rid;
	ui.uid = uid;
	FDINFO fi;
	fi.fd = fd;
	fi.time = time;
	fi.microTime = microTime;
	fi.spanId = spanId;
	fi.srvId = srvId;
	fdMap[buf] = ui;
	roleMap[uid] = fi;
	debug_log("fd=%u,time=%u,microTime=%u,uid=%u,rid=%u,size=[%u,%u]",
			fd, time, microTime, uid, rid, fdMap.size(), roleMap.size());
	return ret;
}

void FdManager::delMap(uint32_t fd, uint32_t time, uint32_t microTime)
{
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	map<string, USERINFO>::iterator it1 = fdMap.find(buf);
	if (it1 != fdMap.end())
	{
		uint32_t uid = it1->second.uid;
		fdMap.erase(it1);
		FDINFO fdInfo;
		fdInfo.fd = fd;
		fdInfo.time = time;
		fdInfo.microTime = microTime;
		map<uint32_t, FDINFO>::iterator it2 = roleMap.find(uid);
		if (it2 != roleMap.end() && it2->second == fdInfo)
		{
			roleMap.erase(it2);
		}
	}
}

bool FdManager::getFd(uint32_t uid, uint32_t& fd, uint32_t& time, uint32_t& microTime)
{
	map<uint32_t, FDINFO>::iterator it = roleMap.find(uid);
	if (it == roleMap.end())
	{
		return false;
	}
	fd = it->second.fd;
	time = it->second.time;
	microTime = it->second.microTime;
	return true;
}

bool FdManager::getRole(uint32_t fd, uint32_t time, uint32_t microTime, uint32_t& uid, uint32_t& rid)
{
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf) - 1, "%u-%u-%u", fd, time, microTime);
	map<string, USERINFO>::iterator it = fdMap.find(buf);
	if (it == fdMap.end())
	{
		return false;
	}
	uid = it->second.uid;
	rid = it->second.rid;
	return true;
}

bool FdManager::getFdInfo(uint32_t uid, FDINFO& fdInfo)
{
	map<uint32_t, FDINFO>::iterator it = roleMap.find(uid);
	if (it == roleMap.end())
	{
		return false;
	}
	fdInfo = it->second;
	return true;
}

bool FdManager::closeAll()
{
	map<uint32_t, FDINFO> allFdMap = roleMap;
	for (map<uint32_t, FDINFO>::iterator it = allFdMap.begin(); it != allFdMap.end(); ++it)
	{
		CStaticBuffer<PACKET_HEADER_SIZE> sendBuffer;
		CFirePacket firePacket;
		firePacket.cmd = PROTOCOL_EVENT_OFFLINE;
		firePacket.fd = it->second.fd;
		firePacket.time = it->second.time;
		firePacket.microTime = it->second.microTime;
		firePacket.Encode(&sendBuffer);
		sendMsg(&sendBuffer);
	}
	return true;
}

bool FdManager::getAllFd(vector<FDINFO>& vecFd)
{
	vecFd.clear();
	for (map<uint32_t, FDINFO>::iterator it = roleMap.begin(); it != roleMap.end(); ++it)
	{
		vecFd.push_back(it->second);
	}
	return true;
}

