/*
 * DataAttack.cpp
 *
 *  Created on: 2011-7-13
 *      Author: auto
 */

#include "DataGate.h"

int CDataGate::AddGate(const DataGate &data)
{
	DBCREQ_DECLARE(DBC::InsertRequest, data.uid);
	req.SetKey(data.uid);

	req.Set("level", data.level);
	req.Set("is_win", data.is_win);
	req.Set("dare_times", data.dare_times);
	req.Set("win_score", data.win_score);
	req.Set("best_score", data.best_score);
	req.Set("use_time", data.use_time);
	req.Set("use_resource", data.use_resource);
	req.Set("lose_score", data.lose_score);
	req.Set("last_save_time", data.last_save_time);
	req.Set("status", data.status);

	DBCREQ_EXEC;
	return 0;
}

int CDataGate::UpdateGate(const DataGate &data)
{
	DBCREQ_DECLARE( DBC::UpdateRequest, data.uid );

	req.SetKey( data.uid );

	req.Set("is_win", data.is_win);
	req.Set("dare_times", data.dare_times);
	req.Set("win_score", data.win_score);
	req.Set("best_score", data.best_score);
	req.Set("use_time", data.use_time);
	req.Set("use_resource", data.use_resource);
	req.Set("lose_score", data.lose_score);
	req.Set("last_save_time", data.last_save_time);
	req.Set("status", data.status);

	req.EQ( "level", data.level );

	DBCREQ_EXEC;
	return 0;
}

int CDataGate::GetGate(unsigned uid, int level, DataGate &gate)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);

	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(is_win);
	DBCREQ_NEED(dare_times);
	DBCREQ_NEED(win_score);
	DBCREQ_NEED(best_score);
	DBCREQ_NEED(use_time);
	DBCREQ_NEED(use_resource);
	DBCREQ_NEED(lose_score);
	DBCREQ_NEED(last_save_time);
	DBCREQ_NEED(status);

	req.EQ( "level", level );

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(gate, is_win);
	DBCREQ_GET_INT(gate, dare_times);
	DBCREQ_GET_INT(gate, win_score);
	DBCREQ_GET_INT(gate, best_score);
	DBCREQ_GET_INT(gate, use_time);
	DBCREQ_GET_INT(gate, use_resource);
	DBCREQ_GET_INT(gate, lose_score);
	DBCREQ_GET_INT(gate, last_save_time);
	DBCREQ_GET_INT(gate, status);



	gate.uid = uid;
	gate.level = level;

	return 0;
}

int CDataGate::GetGates(unsigned uid, vector<DataGate>& gates)
{
	DBCREQ_DECLARE( DBC::GetRequest, uid );

	req.SetKey( uid );
	req.Need( "level", 1 );
	req.Need( "is_win", 2 );
	req.Need( "dare_times", 3 );
	req.Need( "win_score", 4 );
	req.Need( "best_score", 5 );
	req.Need( "use_time", 6 );
	req.Need( "use_resource", 7 );
	req.Need( "lose_score", 8 );
	req.Need( "last_save_time", 9 );
	req.Need( "status", 10 );



	/*if ( NULL != func )
	{
		func( req );
	}*/

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	gates.resize( m_dbcret.TotalRows() );
	for ( unsigned i=0; i<gates.size(); i++ )
	{
		if ( 0 != m_dbcret.FetchRow() )
		{
			return -1;
		}
		gates[i].uid = uid;
		gates[i].level = m_dbcret.IntValue( 1 );
		gates[i].is_win = m_dbcret.IntValue( 2 );
		gates[i].dare_times = m_dbcret.IntValue( 3 );
		gates[i].win_score = m_dbcret.IntValue( 4 );
		gates[i].best_score = m_dbcret.IntValue( 5 );
		gates[i].use_time = m_dbcret.IntValue( 6 );
		gates[i].use_resource = m_dbcret.IntValue( 7 );
		gates[i].lose_score = m_dbcret.IntValue( 8 );
		gates[i].last_save_time = m_dbcret.IntValue( 9 );
		gates[i].status = m_dbcret.IntValue( 10 );


	}
	return 0;
}

int CDataGate::RemoveGate(unsigned uid, int level)
{
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_SET_CONDITION(EQ, level, level);
	DBCREQ_EXEC;
	return 0;
}
