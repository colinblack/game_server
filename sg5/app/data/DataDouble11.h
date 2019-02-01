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

#define XMLDOUBLE_TYPE_NUM_2018		6
struct DataXMLDouble11_2018
{
	XMLDouble11Prop prop[XMLDOUBLE_TYPE_NUM_2018][XMLDOUBLE_PROP_NUM];
};

struct Double11Prop
{
	DataXMLDouble11_2018 dataDouble;
	unsigned lastts;
	unsigned version;

	Double11Prop() : lastts(0), version(0)
	{
	}
};


class CDataDouble11
{
public:

	static CDataDouble11 *getCDataDouble11(bool allserver)
	{
		static CDataDouble11 dataDouble(allserver);
		return &dataDouble;
	}

	CDataDouble11(bool allserver);

	int GetRemainCount(Json::Value &rcnt);
	int BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt, Json::Value &rcnt);

	static unsigned GetAllServerNum(bool allserver);
private:
	int Init(const string &path, semdat sem);
	int ResetData();
	int cpRcnt(Json::Value &rcnt);

	bool m_init;
	CShareMemory m_sh;
	bool m_allserver;
};



#endif /* DATADOUBLE11_H_ */
