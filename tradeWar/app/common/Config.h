/*
 * Config.h
 *
 *  Created on: 2011-5-25
 *      Author: dada
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
using std::string;

namespace Config
{
	bool Init(const string & path);
	bool getShareConf(const string& confName);

	//get config value
	bool GetValue(string &value, const string &name);
	string GetValue(const string &name);
	bool GetIntValue(int &value, const string &name);
	int GetIntValue(const string &name);
	unsigned int GetZoneByUID(unsigned int uid);
};

#endif /* CONFIG_H_ */
