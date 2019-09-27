/*
 * LanguageConfig.h
 *
 *  Created on: 2015-12-28
 *      Author: Administrator
 */

#ifndef LANGUAGECONFIG_H_
#define LANGUAGECONFIG_H_

#include "Kernel.h"

#define GET_LANG(key) LanguageConfig::getInstance()->getLang(key)
class LanguageConfig
{
public:
	static LanguageConfig* getInstance();
	~LanguageConfig(){};
private:
	LanguageConfig(){};
public:
	bool init(const string& path);
	const string& getLang(const string& key) const;
private:
	map<string,string> m_langMap;
};

#endif /* LANGUAGECONFIG_H_ */
