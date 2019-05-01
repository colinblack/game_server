/*
 * DataScienceMgr.h
 *
 *  Created on: 2016-9-14
 *      Author: dawx62fac
 */

#ifndef DATASCIENCEMGR_H_
#define DATASCIENCEMGR_H_


#include "DataInc.h"



class DataScienceMgr
	: public DataSingleton<DBCScience, DB_SCIENCE, DB_BASE_BUFF*DB_SCIENCE_FACOTR, DBCScienceHandler, DB_SCIENCE_FACOTR>
	, public CSingleton<DataScienceMgr>
{
//
	typedef DataSingleton<DBCScience, DB_SCIENCE, DB_BASE_BUFF*DB_SCIENCE_FACOTR, DBCScienceHandler, DB_SCIENCE_FACOTR> base;
private:
	int FreeIndex();

	void NewItem(unsigned uid, unsigned id);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	void Online(unsigned uid);
	void Offline(unsigned uid);

	int Load(unsigned uid);

	int GetIndex(unsigned uid, unsigned id);
	//根据输入的id集合，获取已经解锁好的科技
	void GetIndexs(unsigned uid, const std::vector<uint16_t>& vIds, std::vector<unsigned>& result);

	void GetSciences(unsigned uid, std::vector<DBCScience>& result);
	void GetSciences(unsigned uid, std::vector<unsigned>& result);

	const std::map<unsigned, std::map<uint16_t, unsigned> >& GetAllMap() const { return m_map;}
private:
	std::map<unsigned, bool> m_new_map; //记录加载过的用户

	std::map<unsigned, std::map<uint16_t, unsigned> > m_map;
};


#endif /* DATASCIENCEMGR_H_ */
