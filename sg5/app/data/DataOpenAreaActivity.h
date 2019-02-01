/*
 * DataOpenAreaActivity.h
 *
 *  Created on: 2014-09-02
 *      Author: Administrator
 */

#ifndef CDATAOPENAREAACTIVITY_H_
#define CDATAOPENAREAACTIVITY_H_
#include "Kernel.h"

#define GRADE_RANGE 8
#define LEVEL_1_SIZE 2000
#define LEVEL_2_SIZE 1000
#define LEVEL_3_SIZE 500
#define LEVEL_4_SIZE 300
#define LEVEL_5_SIZE 100
#define LEVEL_6_SIZE 5
#define LEVEL_7_SIZE 3
#define LEVEL_8_SIZE 1


struct DataOpenAreaData{

	unsigned uid[GRADE_RANGE][LEVEL_1_SIZE];

public:
	DataOpenAreaData()
	{
		memset(uid,0,sizeof(uid));
	}
};

class CDataOpenAreaActivity {
public:
	CDataOpenAreaActivity();
	virtual ~CDataOpenAreaActivity();
	int Init(const std::string &path, semdat sem=sem_openarea_activity);

	int UpdateOpenAreaActivityList( unsigned uid,int grade_range,Json::Value &result);
	int GetOpenAreaActivityList( unsigned uid,Json::Value &result);

private:
	bool m_init;
	CShareMemory m_sh;
};


#endif /* CDATAOPENAREAACTIVITY_H_ */
