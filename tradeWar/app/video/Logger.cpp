/*
 * Logger.cpp
 *
 *  Created on: 2014年1月23日
 *      Author: aaron
 */

#include "Logger.h"

bool Logger::init(const kfc::CConfig& conf){
	this->m_dirPrefix = conf["Main\\DayLogPrefix"];
//	this->m_logInDir  = conf["Main\\BusiLogPrefix"];
	return true;
}

bool Logger::onReceive(uint64_t battleId,const char* sRecvBuff,size_t recSize){
//	string prefix = makeDir(logMsg.srvId).append(logMsg.logFileName);
	getLogger(battleId)->onReceive(sRecvBuff,recSize);
	return true;
}

void Logger::onTimer()
{
	for(map<uint64_t ,CVideoDataWriter *>::iterator it = m_logger.begin(); it !=  m_logger.end();)
	{
		it->second->appendText();
		// 删除无用句柄
		if(it->second->isTimeDel())
		{
			it->second->zipWrite();
			delete it->second;
			m_logger.erase(it++);
			continue;
		}
		++it;
	}
}

CVideoDataWriter *Logger::getLogger(uint64_t battleId)
{
	map<uint64_t, CVideoDataWriter*>::iterator it = m_logger.find(battleId);
	if(it != m_logger.end()) {
		return it->second;
	}

	CVideoDataWriter *pLog = new CVideoDataWriter();
	pLog->init(m_dirPrefix, battleId);
	m_logger[battleId] = pLog;
	return m_logger[battleId];
}
