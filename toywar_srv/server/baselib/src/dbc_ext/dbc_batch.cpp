#include <stdio.h>
#include "trans.h"
#include "dbc_batch.h"

CDBCBatch::~CDBCBatch()
{
	for ( unsigned i=0; i<_dbcreq.size(); i++ )
	{
		delete _dbcreq[i];
		_dbcreq[i] = NULL;
	}

	for ( unsigned i=0; i<_dbcsrv.size(); i++ )
	{
		delete _dbcsrv[i];
		_dbcsrv[i] = NULL;
	}

	for ( unsigned i=0; i<_dbcret.size(); i++ )
	{
		delete _dbcret[i];
		_dbcret[i] = NULL;
	}
}

int CDBCBatch::Init( const char* path, const char* key, int maxkey )
{
	int ret;
	char s[128];

	ret = _route.initialize( path, CRoute::OLD_TAG );
	if ( 0 != ret )
	{
		return -1;
	}

	// 因为是老的DBC配置，没有该配置项
	_route.m_head.tout = 3;

	_dbcsrv.resize( _route.m_info.size() );
	_dbcreq.resize( _route.m_info.size() );
	_dbcret.resize( _route.m_info.size() );
	_reqcnt.resize( _route.m_info.size() );
	for ( unsigned i=0; i<_route.m_info.size(); i++ )
	{
		snprintf( s, sizeof(s), "%s:%d/%s", _route.m_info[i].ip, _route.m_info[i].port, _route.m_info[i].prot  );
		_dbcsrv[i] = new DBC::Server;
		_dbcsrv[i]->SetTableName( _route.m_info[i].table );
		_dbcsrv[i]->SetAddress( s );
		_dbcsrv[i]->SetTimeout( _route.m_head.tout );
		_dbcsrv[i]->AddKey( key, DBC::FieldTypeSigned );
		_dbcreq[i] = new DBC::GetRequest( _dbcsrv[i] );
		_dbcret[i] = new DBC::Result;
	}
	DBC::set_key_value_max(maxkey);
	return 0;
}

void CDBCBatch::Reset()
{
	for ( unsigned i=0; i<_reqcnt.size(); i++ )
	{
		_reqcnt[i] = 0;
	}
	for ( unsigned i=0; i<_dbcreq.size(); i++ )
	{
		_dbcreq[i]->Reset();
	}
}

DBC::Request* CDBCBatch::GetRequest( int uin )
{
	CRoute::_INFO* route_info = _route.GetRouteInfo( uin );
	( _reqcnt[ route_info->index ] )++;
	return _dbcreq[ route_info->index ];
}

void CDBCBatch::SetLsVoteId(int masterid, int slaveid, int interfaceid)
{
	return ;
}

/*
 note: 调用前需要调用SetLsVoteId，以确保模块间调用数据正常上报
*/
int CDBCBatch::Exec( FUNC_FILLDATA func, int argc, void** argv )
{
	for ( unsigned i=0; i<_reqcnt.size(); i++ )
	{
		if ( 0 == _reqcnt[i] )
		{
			continue;
		}

		int ret = _dbcreq[i]->Execute( *(_dbcret[i]) ) ;
		if ( 0 != ret)
		{
			_reqcnt[i] = 0;
			continue;
		}

		if ( 0 == _dbcret[i]->NumRows() )
		{
			_reqcnt[i] = 0;
			continue;
		}

		func( *(_dbcret[i]), argc, argv );
	}
	return 0;
}

