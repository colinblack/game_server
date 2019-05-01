/*
 * DBCWeapon.h
 *
 *  Created on: 2016-9-20
 *      Author: dawx62fac
 */

#ifndef DBCWEAPON_H_
#define DBCWEAPON_H_

#include "Kernel.h"

class DBCWeapon
{
public:
	uint32_t 	uid;
	uint8_t 	id;
	int16_t		level; //等级   为0时表示未解锁
	uint8_t		cast;  //铸造
	uint32_t	gem;   //宝石

	DBCWeapon();
	DBCWeapon(uint32_t uid, uint8_t id);

	bool IsNormal() const;
	void Unlock();
	void Cast(unsigned nMul);

	void FullMessage(ProtoWeapon::WeaponInfoCPP* obj);
};


class DBCWeaponHandler : public DBCBase<DBCWeapon, DB_WEAPON>
{
public:
	virtual int Get(DBCWeapon &data);
	virtual int Get(vector<DBCWeapon> &data);
	virtual int Add(DBCWeapon &data);
	virtual int Set(DBCWeapon &data);
	virtual int Del(DBCWeapon &data);
};


#endif /* DBCWEAPON_H_ */
