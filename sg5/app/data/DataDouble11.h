/*
 * DataDouble11.h
 *
 *  Created on: 2015-10-29
 *      Author: dawx5fsd
 */

#ifndef DATADOUBLE11_H_
#define DATADOUBLE11_H_

#include "Kernel.h"
#include "DataXML.h"



struct Double11Prop
{
	DataXMLDouble11 dataDouble;
	unsigned lastts;
	unsigned version;

	Double11Prop() : lastts(0), version(0)
	{
	}
};


class CDataDouble11
{
public:

	static CDataDouble11 *getCDataDouble11()
	{
		static CDataDouble11 dataDouble;
		return &dataDouble;
	}

	CDataDouble11();

	int GetRemainCount(Json::Value &rcnt);
	int BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt);

private:
	int Init(const string &path, semdat sem = sem_all_server_double11);
	int ResetData();
	int cpRcnt(Json::Value &rcnt);

	bool m_init;
	CShareMemory m_sh;
};



#endif /* DATADOUBLE11_H_ */
