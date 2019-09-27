/*
 * Logger.h
 *
 *  Created on: 2014年1月23日
 *      Author: Administrator
 */

#ifndef LOGGER_H_
#define LOGGER_H_

//#include "kfc_mysql.h"
//#include "kfc_config_file.h"
#include "bserver.h"
#include "Common.h"
#include <list>

#include "BattleLogWriter.h"

using namespace std;
using namespace kfc;


struct LogMsg {
	string srvId;
	string battleId;
	string logFileName;		// such as online, coin
	string logStr;
};

class Logger {
public:
	static Logger *getInstance(){
		static Logger logger;
		return &logger;
	}

	~Logger(){};
public:
	bool init(const kfc::CConfig& conf);
	bool onReceive(uint64_t, const char* msg,size_t recSize);
	void onTimer();
private:
	CVideoDataWriter *getLogger(uint64_t battleId);

private:
	Logger(){};
private:
	string m_dirPrefix;
//	string m_logInDir;
private:
	map<uint64_t ,CVideoDataWriter *> m_logger;
};

#endif /* LOGGER_H_ */
