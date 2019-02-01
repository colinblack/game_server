/*
 * DataRank.cpp
 *
 *  Created on: 2015-1-21
 *      Author: Ralf
 */

#include "DataRank.h"

int CDataRank::AddRank(const DataRank &rank)
{
	DBCREQ_DECLARE(DBC::InsertRequest, rank.uid);
	DBCREQ_SET_KEY(rank.uid);
	DBCREQ_SET_INT(rank, level);
	DBCREQ_SET_INT(rank, dehp);
	DBCREQ_SET_STR(rank, heroid);
	DBCREQ_SET_INT(rank, mcity);
	DBCREQ_SET_INT(rank, citylevel);
	DBCREQ_SET_INT(rank, part);
	DBCREQ_SET_INT(rank, soul);
	DBCREQ_SET_INT(rank, book);
	DBCREQ_SET_INT(rank, mac);
	DBCREQ_EXEC;
	return 0;
}

int CDataRank::SetRank(unsigned uid, const DataRank &rank)
{
	if(!rank.uid || (!rank.level && !rank.dehp && rank.heroid.empty() && !rank.mcity && !rank.citylevel && !rank.part && !rank.soul && !rank.book && !rank.mac))
		return 0;

	DBCREQ_DECLARE(DBC::UpdateRequest, uid);
	DBCREQ_SET_KEY(uid);
	if(rank.level)
		DBCREQ_SET_INT(rank, level);
	if(rank.dehp)
		DBCREQ_SET_INT(rank, dehp);
	if(!rank.heroid.empty())
		DBCREQ_SET_STR(rank, heroid);
	if(rank.mcity)
		DBCREQ_SET_INT(rank, mcity);
	if(rank.citylevel)
		DBCREQ_SET_INT(rank, citylevel);
	if(rank.part)
		DBCREQ_SET_INT(rank, part);
	if(rank.soul)
		DBCREQ_SET_INT(rank, soul);
	if(rank.book)
		DBCREQ_SET_INT(rank, book);
	if(rank.mac)
		DBCREQ_SET_INT(rank, mac);
	DBCREQ_EXEC;
	return 0;
}

int CDataRank::GetRank(unsigned uid, DataRank &rank)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(level);
	DBCREQ_NEED(dehp);
	DBCREQ_NEED(heroid);
	DBCREQ_NEED(mcity);
	DBCREQ_NEED(citylevel);
	DBCREQ_NEED(part);
	DBCREQ_NEED(soul);
	DBCREQ_NEED(book);
	DBCREQ_NEED(mac);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(rank, uid);
	DBCREQ_GET_INT(rank, level);
	DBCREQ_GET_INT(rank, dehp);
	DBCREQ_GET_STR(rank, heroid);
	DBCREQ_GET_INT(rank, mcity);
	DBCREQ_GET_INT(rank, citylevel);
	DBCREQ_GET_INT(rank, part);
	DBCREQ_GET_INT(rank, soul);
	DBCREQ_GET_INT(rank, book);
	DBCREQ_GET_INT(rank, mac);
	return 0;
}

int CDataRank::ClearRank(unsigned uid)
{
	DataRank rank;
	rank.uid = uid;
	rank.heroid = "{}";
	DBCREQ_DECLARE(DBC::ReplaceRequest, rank.uid);
	DBCREQ_SET_KEY(rank.uid);
	DBCREQ_SET_INT(rank, level);
	DBCREQ_SET_INT(rank, dehp);
	DBCREQ_SET_STR(rank, heroid);
	DBCREQ_SET_INT(rank, mcity);
	DBCREQ_SET_INT(rank, citylevel);
	DBCREQ_SET_INT(rank, part);
	DBCREQ_SET_INT(rank, soul);
	DBCREQ_SET_INT(rank, book);
	DBCREQ_SET_INT(rank, mac);
	DBCREQ_EXEC;
	return 0;
}

