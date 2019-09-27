/*
 * FileToJson.h
 *
 *  Created on: 2013-3-12
 *      Author: Administrator
 */

#ifndef FILETOJSON_H_
#define FILETOJSON_H_
//#include "Common.h"
#include "SysCommon.h"
#include "json.h"
namespace FileToJson{
 	 bool fileToJson(const string &path,Json::Value &value);
 	 bool stringToJson(const string &str, Json::Value &value);
}



#endif /* FILETOJSON_H_ */
