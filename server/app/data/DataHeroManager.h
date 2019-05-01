/*
 * EquipShopManager.h
 *
 *  Created on: 2016-09-5
 *      Author: city
 */

#ifndef DATA_HERO_MANAGER_H_
#define DATA_HERO_MANAGER_H_

#include "Kernel.h"
#include "DataHero.h"


class DataHeroManager : public DataSingleton<DataHero, DB_HERO, DB_BASE_BUFF*DB_HERO_FULL, CDataHero, DB_HERO_FULL>, public CSingleton<DataHeroManager>
{
private:
	friend class CSingleton<DataHeroManager>;
	DataHeroManager(){};
	virtual ~DataHeroManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);

	int AddBuff(DataHero & hero);
	int LoadBuff(unsigned uid);
	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	///////////////////////////////////////////////////////
	//@add oulong
	DataHero& GetHero(unsigned uid, unsigned heroId);
	int  GetHeroIndex(unsigned uid, unsigned heroId);
	DataHero& GetHeroByIndex(unsigned index);
	///////////////////////////////////////////////////////
	//OfflineResourceItemHexp hexp[SG17_HERO_NUM];
	bool isHeroExists(unsigned uid, unsigned heroid);
	DataHero & GetHero(unsigned uid, unsigned heroid, unsigned & index);
	bool UpdateHero(unsigned index);
	int GetUsingHeroNums(unsigned uid);
	int GetHeroPrice(unsigned uid, unsigned heroid, int & price);
	int GetRecruitHero(unsigned uid, vector<DataHero> & vctHeros);
	int GetRecruitHero(unsigned uid, vector<unsigned> & vHeroIndexs);

	//获取所有已解锁的英雄
	int GetHeros(unsigned uid, vector<unsigned> & indexs);

	int FullMessage(unsigned uid, User::Hero * hero);
private:

};
#endif /* DATA_HERO_MANAGER_H_ */
