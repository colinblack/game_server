/*
 * DataGem.h
 *
 *  Created on: 2016-9-23
 *      Author: dawx62fac
 */

#ifndef DATAGEM_H_
#define DATAGEM_H_

#include "Kernel.h"

/*
 * 宝石
 */
class DBCGem
{
public:
	uint32_t 	uid;   	//uid
	uint8_t		level; 	//宝石等级
	uint32_t	number;	//数量

	DBCGem();
	DBCGem(unsigned uid, uint8_t level);
};

class DBCGemHandler : public DBCBase<DBCGem, DB_GEM>
{
public:
	virtual int Get(DBCGem &data) ;
	virtual int Get(vector<DBCGem> &data) ;
	virtual int Add(DBCGem &data) ;
	virtual int Set(DBCGem &data) ;
	virtual int Del(DBCGem &data) ;
};



#endif /* DATAGEM_H_ */
