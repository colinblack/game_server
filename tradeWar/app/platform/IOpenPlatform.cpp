/*
 * CPengyouPlatform.cpp
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#include "IOpenPlatform.h"

int IOpenPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params) {
	m_appId = appid;
	m_appKey = appkey;
	m_config = params;
	return 0;
}

string IOpenPlatform::GetConfig(const string &name) {
	map<string, string>::iterator iterFind;
	iterFind = m_config.find(name);
	if (iterFind == m_config.end()) {
		return "";
	}
	return iterFind->second;
}
