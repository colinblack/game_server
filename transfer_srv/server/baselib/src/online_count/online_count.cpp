#include <errno.h>
#include <stdio.h>
#include "base_comm_define.h"
#include "sock_opt.h"
#include "online_count.h"

COnlineCount* COnlineCount::_pInstance = NULL;

int COnlineCount::Init( int app )
{
	_err[0] = 0;
	if ( 0 != _status )
	{
		_status = _route.initialize( car == app ? PATH_XML_ONLINECOUNT : PATH_XML_ONLINECOUNT_PASTURE );
		if ( 0 != _status )
		{
			snprintf( _err, sizeof(_err), "_route.initialize ret=%d", _status );
		}
	}

	return _status;
}

int COnlineCount::Report( int uin, int domain, int clientip, int app, int extend, const int pn_TJ2AppId )
{
	if ( 0 != Init( app ) )
	{
		return -1;
	}

	CSockUdp udp;
	CRoute::_INFO* addrinfo =  _route.GetRouteInfo( uin );
	if ( NULL == addrinfo )
	{
		snprintf( _err, sizeof(_err), "_route.GetRouteInfo failed uin=%d", uin );
		return -2;
	}

	sockaddr_in addr;
	SockAddr( addrinfo->ip, addrinfo->port, &addr );

	LoginReq req;
	req.head.ver = htonl( ONLINE_VERSION_V2 );
	req.head.len = htonl( sizeof( req ) );
	req.head.cmd = htonl( ONLINE_CMD_LOGIN );
	req.body.time = htonl( time( NULL ) );
	req.body.qq = htonl( uin );
	req.body.ip = htonl( clientip );
	req.body.appid = htonl(pn_TJ2AppId == 0 ? Source(domain, app) : pn_TJ2AppId);
	req.body.extend = htonl( extend );

	if ( sizeof(req) != udp.Send( (const char*)&req, sizeof(req), &addr, sizeof(addr) ) )
	{
		snprintf( _err, sizeof(_err), "send failed, err=%d", errno );
		return -3;
	}

	return 0;
}

int COnlineCount::Source( int domain, int app )
{
	switch ( app )
	{
	case car:
		return DOMAIN_DAWX == domain ? 15 : 9;
	}
	return 0;
}

