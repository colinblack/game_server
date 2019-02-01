/*
 * LogicSyncLords.h
 *
 *  Created on: 2016-7-8
 *      Author: dawx62fac
 */

#ifndef LOGICSYNCLORDS_H_
#define LOGICSYNCLORDS_H_

#include "LogicInc.h"



class CLogicLordExploit
{
public:
	CLogicLordExploit(const std::string& path);

//	void Load();

	void Reset();

	void Stop();

	//统计增量
	void StatisticsIcrement(
			const std::string& path, /*功勋排名数据文件*/
			const std::map<unsigned, unsigned>& mapHerokills,
			const std::map<unsigned, string>& mapHeroNames);

	//
	std::map<unsigned, Json::Value> GetData();
private:
	void Save();

	std::string GetName(unsigned uid, const std::map<unsigned, string>& mapHeroNames);


	void UpdateMapData(unsigned uid, const std::string& name, unsigned incVal);

	//同步数据
	void Sync(const Json::Value& data);

	//Json::Value m_jsonData;
	unsigned m_nTime;  //更新时间
	unsigned m_nStop; 	//是否停止更新
	unsigned m_nReset;  //是否重值
	std::string m_path;
	std::map<unsigned, Json::Value> m_mapData;
};

//----------------------------------------------------------------
class BaseLordUnit
{
public:
	virtual ~BaseLordUnit() {}

	//同步数据
	virtual void Sync(const std::string& cachePath) = 0;
	virtual int Type() const = 0;

	//确立尊主
	virtual void Establish();

protected:
	void HttpRequest(const std::string& action, const std::string& data, Json::Value& result);

	std::string UserName(unsigned uid);
};

class LordExploitUnit : public BaseLordUnit
{
public:
	void Sync(const std::string& cachePath);
	int Type() const; //return 1;
};

class LordTryndamereUnit : public BaseLordUnit
{
public:
	virtual void Sync(const std::string& cahcePath);
	int Type() const; //return 2;
};

class LordPlunderUnit : public BaseLordUnit
{
public:
	virtual void Sync(const std::string& cahcePath);
	int Type() const; //return 3;
};
//============> 掠夺榜更换为水晶榜!!!!!!!
class LordR5Unit : public BaseLordUnit
{
public:
	virtual void Sync(const std::string& cahcePath);
	int Type() const; //return 3;
};

class LordCostUnit : public BaseLordUnit
{
public:
	virtual void Sync(const std::string& cahcePath);
	int Type() const; //return 4;
};

class LordRechargeUnit : public BaseLordUnit
{
public:
	virtual void Sync(const std::string& cahcePath);
	int Type() const; //return 5;
};

//--------------------------------------------------
class CLogicLordRamote
{
private:
	int HttpRequest(const std::string& action, const std::string& data, Json::Value& result);
public:
	int GetAllLords(unsigned uid, Json::Value& result);
	int GetRankList(unsigned uid, int type, Json::Value& result);
};


#endif /* LOGICSYNCLORDS_H_ */
