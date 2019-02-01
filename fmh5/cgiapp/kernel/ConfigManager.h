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
#include "Demo.pb.h"

/*
 *  配置文件管理器，增加新配置时，把新的pb文件加入ConfigInc.h，定义新的const成员，构造函数中写入配置文件名
 */
class ConfigManager : public CSingleton<ConfigManager>
{
private:
	friend class CSingleton<ConfigManager>;
	virtual ~ConfigManager(){}
	ConfigManager()
		:demo("demo.json")
	{
		Init();
		serverid = 1;
	}

	void Init();
	static bool m_init;

	unsigned serverid;
public:
	static bool Reload();
	static void Fail(){m_init = false;}
	bool Inited(){return m_init;}

	const ConfigPB<Demo::Demo> demo;

	map<unsigned, unsigned> m_server;
	const Demo::Server& GetServer(unsigned server);
	bool IsServerMergeTogather(unsigned s1, unsigned s2);
	unsigned GetMainServer(unsigned server);
	unsigned GetRandomOpen();
	void GetAllServer(set<unsigned>& allServer);

	void SetServer(unsigned s){serverid = s;}
	unsigned GetServer(){return serverid;}
};

#endif /* CONFIGMANAGER_H_ */
