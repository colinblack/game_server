/*
 * FileToJson.cpp

 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */
#include<fstream>
#include "FileToJson.h"
#include "Common.h"
bool FileToJson::fileToJson(const string &path,Json::Value &value )
{
	Json::Reader reader;
	string svalue;
	File::Read(path,svalue);
	if(!reader.parse(svalue,value))
	{
		return false;
	}
	return true;
}

bool FileToJson::stringToJson(const string &str, Json::Value &value)
{
	Json::Reader reader;
	if(!reader.parse(str,value))
	{
		return false;
	}
	return true;
}


