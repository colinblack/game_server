#include <errno.h>
#include <string.h>
#include "sock_opt.h"

/*
	一些基础的 socket   操作
*/
void SockAddr( const char* sAddr, const int iPort, sockaddr_in* pAddr )
{
	memset(pAddr, 0, sizeof(*pAddr));
	pAddr->sin_family = AF_INET;
	pAddr->sin_port = htons(iPort);
	pAddr->sin_addr.s_addr = inet_addr(sAddr);
}

int Bind( int iSock, const char* sAddr, const int iPort )
{
	struct sockaddr_in stSvraddr;
	SockAddr( sAddr, iPort, &stSvraddr );
	
	if(bind(iSock, (const struct sockaddr *)&stSvraddr, sizeof(stSvraddr)) < 0) 
	{
		return -1;
	}
	return 0;
}

int Listen( const char* sAddr, const int iPort, int backlog )
{
        int reuse_addr = 1;
        int iSock = socket( AF_INET, SOCK_STREAM, 0 );
        if ( iSock < 0 )
        {
                return -1;
        }

        setsockopt( iSock, SOL_SOCKET,SO_REUSEADDR, &reuse_addr, sizeof( reuse_addr ) );

        if ( Bind( iSock, sAddr, iPort ) != 0 )
        {
                return -2;
        }

        if ( listen( iSock, backlog) < 0 )
        {
                return -3;
        }
        return iSock;
}

int Select(int fd, struct timeval *timeout)
{
	timeval tout = *timeout;
	fd_set set;
	FD_ZERO( &set );
	FD_SET( fd, &set );

	return select( fd+1, &set, NULL, NULL, &tout );
}

int ConnectNoBlock( int sock_fd, struct sockaddr_in& stSvraddr, struct timeval tout )
{	
	int fd_flag = fcntl(sock_fd, F_GETFL);    
	if ( fd_flag == -1 )    
	{        
		return -1;    
	}    	
	
	fd_flag |= O_NONBLOCK;	
	if ( fcntl( sock_fd, F_SETFL, fd_flag ) == -1 )
	{
		return -2;
	}
	
	int ret = connect( sock_fd,  (struct sockaddr *)&stSvraddr, sizeof( stSvraddr ) );
	if ( ret == -1 && errno != EINPROGRESS && errno != EWOULDBLOCK )
	{
		return -3;
	}
	
	fd_set set;
	FD_ZERO( &set );
	FD_SET( sock_fd, &set );
	ret = select( sock_fd+1, NULL, &set, NULL, &tout );
	if ( ret == -1 )
	{
		return -4;
	}
	else if ( ret == 0 )
	{
		errno = ETIME;
		return -5;
	}
	
	int sock_err = 0;
	int sock_err_len = sizeof(sock_err);
	if ( getsockopt( sock_fd, SOL_SOCKET, SO_ERROR, (char*)&sock_err, (socklen_t*)&sock_err_len ) == -1 )
	{
		return -6;
	}
	
	if (sock_err != 0)
	{
		errno = sock_err;
		return -7;
	}
	
	return 0;
}

int SendN( int iSock, const char* data, int size )
{
	int n;

	while (0 < size) 
	{
		n = send( iSock, data, size, 0 );
		if ( 0 >= n )
		{
			return -1;
		}

		size -= n;
		data += n;
	}
	return 0;
}

int RecvN( int iSock, char* data, int size, struct timeval *timeout )
{
	int n;

	while (0 < size) 
	{
		if ( ( NULL != timeout ) && ( 1 != Select( iSock, timeout ) ) )
		{
			return -1;
		}
		
		n = recv( iSock, data, size, 0 );
		if (0 >= n) 
		{
			return -2;
		} 

		size -= n;
		data += n;
	}
	return 0;
}

int recv_until( int fd, char* data, int size, const char* match, timeval* tout )
{
	int n;
	int match_len = strlen( match );
	int rcv_len = 0;

	while ( rcv_len < size ) 
	{
		if ( ( NULL != tout ) && ( 1 != Select( fd, tout ) ) )
		{
			return -1;
		}

		n = recv( fd, data+rcv_len, size-rcv_len, 0 );
		if ( 0 >= n )
		{
			return -2;
		}

		rcv_len += n;
		if ( rcv_len >= match_len )
		{
			if ( 0 == memcmp( data+rcv_len-match_len, match, match_len ) )
			{
				return rcv_len;
			}
		}
	}
	return 0;
}

/*
	UDP 协议的 socket   操作
*/
CSockUdp::CSockUdp()
{
	Create();
}

CSockUdp::~CSockUdp()
{
	Close();
}

int CSockUdp::Create()
{
	m_iSock = socket(AF_INET, SOCK_DGRAM, 0);
	if( m_iSock < 0 ) 
	{
		return -1;
	}
	return 0;
}

int CSockUdp::Close()
{
	int iRet = 0;
	if ( m_iSock > 0 )
	{
		iRet = close( m_iSock );
		m_iSock = -1;
	}
	return iRet;
}

int CSockUdp::Bind(const char* sAddr, int port)
{
	return ::Bind( m_iSock, sAddr, port );
}

int CSockUdp::Send(const char* data, int size, sockaddr_in* pAddr, socklen_t iAddrLen)
{
	return sendto(m_iSock, data, size, 0, (sockaddr*)pAddr, iAddrLen);
}

int CSockUdp::Recv(char* data, int size, sockaddr_in* pAddr, socklen_t* pAddrLen, struct timeval *timeout)
{
	if ( (NULL != timeout) && (1 != Select(m_iSock, timeout)) )
	{
		return -2;
	}

	return recvfrom(m_iSock, data, size, 0, (sockaddr*)pAddr, pAddrLen);
}

int CSockUdp::RecvUntil( char* data, int size, struct timeval *timeout )
{
	int rcv;
	
	while ( 1 )
	{
		rcv = Recv( data, size, NULL, NULL, timeout );
		if ( rcv < 0 )
		{
			return -1;
		}

		if ( rcv != size )
		{/* 收到垃圾包 */
			continue;
		}
		break;
	}
	return 0;
}

/*
	TCP 协议的 socket   操作
*/
CSockTcp::CSockTcp()
{
	m_connTout.tv_sec = 3;
	m_connTout.tv_usec = 0;
	m_iSock = -1;
	//Create();
}

CSockTcp::~CSockTcp()
{
	Close();
}

int CSockTcp::Create()
{
	m_iSock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( m_iSock < 0 )
	{
		return -1;
	}
	return 0;
}

int CSockTcp::Close()
{
	int iRet = 0;
	if ( m_iSock > 0 )
	{
		iRet = close( m_iSock );
		m_iSock = -1;
	}
	return iRet;
}

int CSockTcp::Bind(const char* sAddr, int port)
{
	return ::Bind( m_iSock, sAddr, port );
}

int CSockTcp::Connect(const char* sAddr, int port)
{
	sockaddr_in addr;
	SockAddr( sAddr, port, &addr );

	return Connect( &addr );
}

int CSockTcp::Connect(sockaddr_in* pAddr)
{
	int iRet = ConnectNoBlock( m_iSock, *pAddr, m_connTout );
	if ( 0 != iRet )
	{
		return iRet;
	}
	return 0;
}

int CSockTcp::ReConnect( sockaddr_in* pAddr )
{
	Close();

	if ( 0 != Create() )
	{
		return -2;
	}
	
	return Connect( pAddr );
}

int CSockTcp::SendN( const char* data, int size )
{
	return ::SendN( m_iSock, data, size );
}

int CSockTcp::RecvN(char* data, int size, struct timeval *timeout)
{
	return ::RecvN( m_iSock, data, size, timeout );
}

/*
	长链接的TCP 协议的 socket   操作
*/
CSockTcpEx::CSockTcpEx()
{
	m_bConn = false;
}

CSockTcpEx::CSockTcpEx( const char* sAddr, int port )
{
	m_bConn = false;
	Init( sAddr, port );
}

CSockTcpEx::CSockTcpEx( sockaddr_in* pAddr )
{
	m_bConn = false;
	Init( pAddr );
}

CSockTcpEx::~CSockTcpEx()
{
}

int CSockTcpEx::Init( const char* sAddr, int port )
{
	SockAddr( sAddr, port, &m_addr );
	return 0;
}

int CSockTcpEx::Init( sockaddr_in* pAddr )
{
	memcpy( &m_addr, pAddr, sizeof(m_addr) );
	return 0;
}

int CSockTcpEx::Send( const char* data, int size )
{
	if ( !m_bConn )
	{
		if ( 0 != ReConnect( &m_addr ) )
		{
			return -1;
		}
		m_bConn = true;
	}

	if ( 0 != SendN( data, size ) )
	{
		m_bConn = false;
		return -2;
	}
	return 0;
}

int CSockTcpEx::Recv( char* data, int size, struct timeval *timeout )
{
	if ( !m_bConn )
	{
		return -1;
	}

	if ( 0 != RecvN( data, size, timeout ) )
	{
		m_bConn = false;
		return -2;
	}
	return 0;
}
