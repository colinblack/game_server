#ifndef LOGICCHONGBANG_H_
#define LOGICCHONGBANG_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicChongBang
{
public:
	CLogicChongBang():m_nReset(0),m_nStop(0),m_Version(-1){};
	CLogicChongBang(const std::string& path,unsigned version);
	~CLogicChongBang(){}

	static CDataChongBangWangZhe* GetDataChongBangWangZhe(void);

	void Reset();

	void Stop();

	void ShowChongBangWangZhe();

	//统计增量
	void StatisticsIcrement(
			const std::string& path, /*功勋排名数据文件*/
			const std::map<unsigned, unsigned>& mapHerokills,
			const std::map<unsigned, string>& mapHeroNames,
			bool check = false);

	int GetXianShiReward(unsigned uid, string key, unsigned id, Json::Value & result);
	int AddUseEquipCnt(unsigned uid, unsigned eqid, unsigned count, string code, bool ishuode=false);

public:
	int Mobai(unsigned uid, unsigned chongbangid, unsigned uid2, Json::Value & result);
	int SetUser(unsigned chongbangid, unsigned uid);
	int GetInfo(unsigned chongbangid, Json::Value & result);

public:
	void ResetNewAct(Json::Value & newact, unsigned sid, unsigned version, unsigned len);

private:
	void Save(bool stop=false);

	std::string GetName(unsigned uid, const std::map<unsigned, string>& mapHeroNames);

	void UpdateMapData(unsigned uid, const std::string& name, unsigned incVal);

	void CheckMapData(const std::map<unsigned, unsigned>& mapHerokills);

	unsigned FindSid(string key);

	unsigned m_nReset;
	unsigned m_nStop; 	//是否停止更新
	std::string m_path;
	int m_Version;
	std::map<unsigned, Json::Value> m_mapData;
};



#endif /* LOGICCHONGBANG_H_*/
