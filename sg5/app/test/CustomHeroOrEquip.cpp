#include "LogicInc.h"
#include "LogicCMD.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;
#define MAX_LENG (1000)

static 	ofstream logstream("custom.log", ios::out);

#define WRITE_LOG(LOG_LEVEL,format,args...)  \
    { 	char pdata[MAX_LENG] = {0};  \
		sprintf(pdata, "[%u]["#LOG_LEVEL"] %s:%d %s():"format"\n", Time::GetGlobalTime(), __FILE__,__LINE__,__FUNCTION__,args); \
		logstream<<pdata<<endl; \
	}

class CustomHeroEquip
{
public:
	enum LOG_LEVEL     // 日志级别
	{
	    LOG_ERROR = 1,
	    LOG_WARN = 2,
	    LOG_INFO = 3
	};

	int UpdateHero(unsigned uid, unsigned heroud, string & data);

	int UpdateEquip(unsigned uid, unsigned equd, string & data);

	int ReplaceJson(Json::Value & srcdata, Json::Value & lateestdata);

private:

};

int CustomHeroEquip::UpdateHero(unsigned uid, unsigned heroud, string & data)
{
	Json::Reader reader;
	Json::Value jsondata;

	bool isok = reader.parse(data, jsondata);

	if (!isok)
	{
		WRITE_LOG(LOG_ERROR, "data error.can not parse to json. uid=%u,heroud=%u,data=%s", uid, heroud, data.c_str());
		return R_ERROR;
	}

	//根据uid和ud获取英雄数据
	CLogicHero logichero;

	Json::Value herodata;

	int ret = logichero.Get(uid, heroud, herodata);

	if (ret)
	{
		WRITE_LOG(LOG_ERROR, "get hero data error. uid=%u,heroud=%u", uid, heroud);
		return R_ERROR;
	}

	//用传来的数据替换旧的数据
	ReplaceJson(herodata, jsondata);

	//将最新的英雄数据写回档里
	ret = logichero.Chg(uid, heroud, herodata);

	if (ret)
	{
		WRITE_LOG(LOG_ERROR, "update hero data error. uid=%u,heroud=%u", uid, heroud);
		return R_ERROR;
	}

	WRITE_LOG(LOG_INFO, "update hero data success. uid=%u,heroud=%u,data=%s", uid, heroud, data.c_str());

	return 0;
}

int CustomHeroEquip::UpdateEquip(unsigned uid, unsigned equd, string & data)
{
	Json::Reader reader;
	Json::Value latest;

	bool isok = reader.parse(data, latest);

	if (!isok)
	{
		WRITE_LOG(LOG_ERROR, "data error.can not parse to json. uid=%u,equd=%u,data=%s", uid, equd, data.c_str());
		return R_ERROR;
	}

	CLogicEquipment logicEquipMent;
	Json::Value equipdata;

	int ret = logicEquipMent.Get(uid, equd, equipdata);

	if (ret)
	{
		WRITE_LOG(LOG_ERROR, "get equip data error. uid=%u,equd=%u", uid, equd);
		return R_ERROR;
	}

	//用传来的数据替换旧的数据
	ReplaceJson(equipdata, latest);

	//将最新的装备数据写回档里
	ret = logicEquipMent.Chg(uid, equd, equipdata);

	if (ret)
	{
		WRITE_LOG(LOG_ERROR, "update equip data error. uid=%u,equd=%u", uid, equd);
		return R_ERROR;
	}

	WRITE_LOG(LOG_INFO, "update hero data success. uid=%u,equd=%u,data=%s", uid, equd, data.c_str());

	return 0;
}

int CustomHeroEquip::ReplaceJson(Json::Value & srcdata, Json::Value & lateestdata)
{
	//获取json中的key
	vector<string>  keys = lateestdata.getMemberNames();
	string key;

	for(int i = 0; i < keys.size(); ++i)
	{
		key = keys[i];

		if (srcdata.isMember(keys[i].c_str()))
		{
			//key存在，则替换
			srcdata[key] = lateestdata[key];

			/*
			if (lateestdata[key].isString())
			{
				WRITE_LOG(LOG_INFO, "olddata=%s,newdata=%s", srcdata[key].asCString(), lateestdata[key].asCString());
			}
			else
			{

			}
			*/
		}
	}

	return 0;
}

void usage()
{
	cout<<"-t 处理类型,值为hero或者equip"<<endl;
	cout<<"-f 指定文件路径"<<endl;
}

int ReadOption(int argc, char * argv[], string & type, string & path)
{
	char ch;

	while((ch = getopt(argc, argv, "t:f:")) != EOF)
	{
	    switch(ch)
	    {
	        case 't':
	        	type = optarg;
	            break;
	        case 'f':
	        	path = optarg;
	        	break;
	        default:
	            break;
	    }
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	string type, path;

	ReadOption(argc, const_cast<char **>(argv), type, path);

	if (type.empty() || path.empty())
	{
		usage();
		return 1;
	}

	if ("hero" != type && "equip" != type)
	{
		usage();
		return 1;
	}

	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	//读取文件数据，然后根据内容处理
	ifstream fin(path.c_str());

	if (!fin.good())
	{
		cout<<"file error."<<endl;
		return 1;
	}

	string userdata;
	vector<string> separate;
	int line = 0;

	while (!fin.eof() && fin.good())
	{
		getline(fin, userdata);

		++line;
		//忽略空行
		if (userdata.empty())
		{
			continue;
		}

		separate.clear();

		String::Split(userdata, '|', separate);

		if (separate.size() < 3)
		{
			WRITE_LOG(LOG_ERROR, "this line data format error.[line=%d]", line);
			continue;
		}

		CustomHeroEquip custom;

		if ("hero" == type)
		{
			unsigned uid = CTrans::STOI(separate[0u]);
			unsigned heroud = CTrans::STOI(separate[1u]);

			custom.UpdateHero(uid, heroud, separate[2u]);
		}
		else
		{
			unsigned uid = CTrans::STOI(separate[0u]);
			unsigned equd = CTrans::STOI(separate[1u]);

			custom.UpdateEquip(uid, equd, separate[2u]);
		}
	}

	return 0;
}
