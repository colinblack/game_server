/*
 * ConfigManager.h
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "Common.h"
#include "ConfigPB.h"
#include "ConfigInc.h"

/*
 *  配置文件管理器，增加新配置时，把新的pb文件加入ConfigInc.h，定义新的const成员，构造函数中写入配置文件名
 */
class ConfigManager : public CSingleton<ConfigManager>
{
private:
	friend class CSingleton<ConfigManager>;
	virtual ~ConfigManager(){}
	ConfigManager()
		:demo("demo17.json")
		,activity("ActivityTime.json", false)
	{
		Init();
	}

	void Init();
	static bool m_init;

public:
	static bool Reload();
	static void Fail(){m_init = false;}
	bool Inited(){return m_init;}

	const ConfigPB<Demo::Demo> demo;
	const ConfigPB<User::Activity> activity;


	map<unsigned, unsigned> m_actmap;
	bool GetActivity(unsigned id, User::ActivityItem& act);
};

#endif /* CONFIGMANAGER_H_ */
