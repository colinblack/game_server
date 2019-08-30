#include "markupstl.h"
#include "commlog.h"
#include "dbc_keepalive.h"
#include <stdlib.h>

CDBCKeepAlive CDBCKeepAlive::_ka;

int CDBCKeepAlive::LoadConfig( const char* tag, const char* path )
{
	static bool bInit = false;
	if (bInit)
	{
		return 0;
	}
	// 不管成功失败只加载1次
	bInit = true;
	
	CMarkupSTL xml;
	if ( !xml.Load( path ) )
	{
		error_log( "load %s failed", path );
		return -1;
	}

	if ( !xml.FindElem( "dbc_keepalive" ) )
	{
		error_log( "no keepalive config" );
		return -2;
	}
	xml.IntoElem();

	if ( xml.FindElem( tag ) )
	{
		_max = atoi( xml.GetAttrib( "max_handle" ).c_str() );
		if ( _max <= 0 )
			_max = DEFAULT_MAX_DBCHANDLE;
	}

	debug_log( "max_dbchandle=%d", _max );
	return 0;
}

