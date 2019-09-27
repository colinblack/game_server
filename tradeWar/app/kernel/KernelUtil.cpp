/*
 * KernelUtil.cpp
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#include "KernelUtil.h"

bool Kernel::InitLog(const string &logName)
{
	int level;
	string path;
	int rewind;
	int size;
	int record_size;
	if(!Config::GetIntValue(level, CONFIG_LOG_LEVEL)	||
			!Config::GetValue(path, CONFIG_LOG_PATH)	||
			!Config::GetIntValue(rewind, CONFIG_LOG_REWIND)	||
			!Config::GetIntValue(size, CONFIG_LOG_SIZE)	||
			!Config::GetIntValue(record_size, CONFIG_LOG_RECORD_SIZE))
	{
		return false;
	}

	CLog::GetInstance()->initalize(level, path.c_str(), logName.c_str(), rewind, size, record_size);
	return true;
}

bool Kernel::Init(const string &configPath)
{
	Time::Init();
	Math::InitRandom();
	if(!Config::Init(configPath))
	{
		return false;
	}
	if(!StringFilter::Init(Config::GetValue(CONFIG_STRING_FILTER_DATA)))
	{
		return false;
	}
	if(!Kernel::InitLog(Config::GetValue(CONFIG_LOG_NAME)))
	{
		return false;
	}
	return true;
}
