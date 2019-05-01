#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string>
#include "netclientex.h"

CNetClientEx::CNetClientEx()
{
	_qos_type = QOS_TYPE_NULL;
}

CNetClientEx::~CNetClientEx()
{
}

int CNetClientEx::SetSendTime(float sendtimeout_usec)
{
	_host_info._sock_send_timeout = sendtimeout_usec;
	
	return 0;
}

int CNetClientEx::SetRecvTime(float recvtimeout_usec)
{
	_host_info._sock_recv_timeout = recvtimeout_usec;
	
	return 0;
}

//默认的接收和发送超时是1秒
int CNetClientEx::Open(const char* ip,unsigned short port,
		float recvtimeout_usec,float sendtimeout_usec)
{
	_host_info._host_ip = HOSTINFO::HostStr2Int((char*)ip);
	_host_info._host_port = port;
	_host_info._sock_recv_timeout = recvtimeout_usec;
	_host_info._sock_send_timeout = sendtimeout_usec;
	
	return _qos_info.AddHost(_host_info,500);
}

int CNetClientEx::Open(const char* ip,unsigned short port,
		float recvtimeout_usec,float sendtimeout_usec,bool keep_cnt,bool reuse)
{
	_host_info._host_ip = HOSTINFO::HostStr2Int((char*)ip);
	_host_info._host_port = port;
	_host_info._sock_recv_timeout = recvtimeout_usec;
	_host_info._sock_send_timeout = sendtimeout_usec;
	_host_info._sock_keepcnt = keep_cnt;
	_host_info._sock_reuse = reuse;
	
	return _qos_info.AddHost(_host_info,500);
}

void CNetClientEx::Close()
{
	if( _host_info._sock_fd > 0 ) close(_host_info._sock_fd);	
	_host_info._sock_fd = -1;
	
	return ;
}

int CNetClientEx::SelectSingleReadEx(int fd, float timeout, fd_set* r_set)
{
	FD_SET(fd, r_set);
	
	struct timeval tv;
	tv.tv_sec = (int)timeout;
	tv.tv_usec = (int) (( timeout-(int)timeout )*1000000) ;
	
	return select (fd+1, r_set, NULL, NULL, &tv);
}

int CNetClientEx::SelectSingleRead(int fd, float timeout)
{
	fd_set r_set;
	FD_ZERO(&r_set);
	return SelectSingleReadEx(fd, timeout, &r_set);
}

int CNetClientEx::SetNonBlock(int fd)
{
	int val = fcntl(fd, F_GETFL, 0);
	if (val == -1) 
		return -1;
	
	if (fcntl(fd, F_SETFL, val | O_NONBLOCK | O_NDELAY) == -1)
		return -1;
	
	return 0;
}

int CNetClientEx::AsyncConnect(unsigned int ip, unsigned short port)
{
	fd_set readfd;
	fd_set writefd;
	int ret;
	
	if ( _host_info._sock_fd > 0 )	
	{
		ret = SelectSingleRead(_host_info._sock_fd,0);
		if ( ret > 0 )
		{
			Close();
			//先关闭,再重新连接
		}
		else
		{
			return _host_info._sock_fd;
		}
	}
	
	struct sockaddr serveraddr;
	struct sockaddr_in *p = (struct sockaddr_in *) &serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	
	p->sin_family = AF_INET;
	unsigned * ptr = (unsigned*)&p->sin_addr;
	*ptr = ip;
	p->sin_port = htons(port);
	_host_info._sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( _host_info._sock_fd <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]create socket ip:%s port:%d err:%s\n",
						__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port,strerror(errno));	
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	//	set non-block
	if ( SetNonBlock(_host_info._sock_fd) < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]fcntl set ip:%s port:%d non-block error\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		return -1;	
	}
	
	if ( _host_info._sock_reuse )
	{	//不是很安全
		linger   _sLinger;
		_sLinger.l_onoff   =   1;
		_sLinger.l_linger   =   0;
		setsockopt(_host_info._sock_fd,SOL_SOCKET,SO_LINGER,(const char*)&_sLinger,sizeof(linger));
	}
	
	//	connect
	ret = ::connect(_host_info._sock_fd, &serveraddr, sizeof(serveraddr));
	if (ret < 0)
	{
		if(errno != EINPROGRESS)
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
						__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			Close();
			return -1;
		}
	}
	if(ret == 0)	return _host_info._sock_fd;
	
	FD_ZERO(&readfd);
	FD_ZERO(&writefd);
	FD_SET(_host_info._sock_fd, &readfd);
	FD_SET(_host_info._sock_fd, &writefd);
	struct timeval tv;
	
	tv.tv_sec = (int)_host_info._sock_recv_timeout;
	tv.tv_usec = (int)((_host_info._sock_recv_timeout-(int)_host_info._sock_recv_timeout)*1000000) ;
	ret = select(_host_info._sock_fd+1, &readfd, &writefd, NULL, &tv);
	if ( ret <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d ret:%d timeout:%f err:%s\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port,ret,_host_info._sock_recv_timeout,strerror(errno));
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		return -1;
	}
	else
	{
		if (FD_ISSET(_host_info._sock_fd, &writefd))		
		{
			int error;
			int len = sizeof(error);
			int bok = getsockopt(_host_info._sock_fd, SOL_SOCKET, SO_ERROR, &error,(socklen_t*)&len);
			if (bok < 0)
			{
				_err_msg.resize(256); _err_msg = "";
				_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
							__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
				if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
				
				Close();
				return -1;
			}
			else if (error)
			{
				_err_msg.resize(256); _err_msg = "";
				_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
							__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
				if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
				
				Close();
				return -1;
			}
		}
	}
	
	return _host_info._sock_fd;
}

int CNetClientEx::AsyncConnect(unsigned int ip, unsigned short port,float time_out)
{
	fd_set readfd;
	fd_set writefd;
	int ret;
	
	if ( _host_info._sock_fd > 0 )	
	{
		ret = SelectSingleRead(_host_info._sock_fd,0);
		if ( ret > 0 )
		{
			Close();
			//先关闭,再重新连接
		}
		else
		{
			return _host_info._sock_fd;
		}
	}
	
	struct sockaddr serveraddr;
	struct sockaddr_in *p = (struct sockaddr_in *) &serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	
	p->sin_family = AF_INET;
	unsigned * ptr = (unsigned*)&p->sin_addr;
	*ptr = ip;
	p->sin_port = htons(port);
	_host_info._sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( _host_info._sock_fd <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]create socket ip:%s port:%d err:%s\n",
						__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port,strerror(errno));	
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	//	set non-block
	if ( SetNonBlock(_host_info._sock_fd) < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]fcntl set ip:%s port:%d non-block error\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		return -1;	
	}
	
	if ( _host_info._sock_reuse )
	{	//不是很安全
		linger   _sLinger;
		_sLinger.l_onoff   =   1;
		_sLinger.l_linger   =   0;
		setsockopt(_host_info._sock_fd,SOL_SOCKET,SO_LINGER,(const char*)&_sLinger,sizeof(linger));
	}
	
	//	connect
	ret = ::connect(_host_info._sock_fd, &serveraddr, sizeof(serveraddr));
	if (ret < 0)
	{
		if(errno != EINPROGRESS)
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
						__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			Close();
			return -1;
		}
	}
	if(ret == 0)	return _host_info._sock_fd;
	
	FD_ZERO(&readfd);
	FD_ZERO(&writefd);
	FD_SET(_host_info._sock_fd, &readfd);
	FD_SET(_host_info._sock_fd, &writefd);
	struct timeval tv;
	
	tv.tv_sec = (int)time_out;
	tv.tv_usec = (int)((time_out-(int)time_out)*1000000) ;
	ret = select(_host_info._sock_fd+1, &readfd, &writefd, NULL, &tv);
	if ( ret <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d ret:%d timeout:%f err:%s\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(ip),port,ret,time_out,strerror(errno));
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		return -1;
	}
	else
	{
		if (FD_ISSET(_host_info._sock_fd, &writefd))		
		{
			int error;
			int len = sizeof(error);
			int bok = getsockopt(_host_info._sock_fd, SOL_SOCKET, SO_ERROR, &error,(socklen_t*)&len);
			if (bok < 0)
			{
				_err_msg.resize(256); _err_msg = "";
				_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
							__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
				if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
				
				Close();
				return -1;
			}
			else if (error)
			{
				_err_msg.resize(256); _err_msg = "";
				_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]asyncconnect ip:%s port:%d error:%s\n",
							__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(ip),port,strerror(errno));
				if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
				
				Close();
				return -1;
			}
		}
	}
	
	return _host_info._sock_fd;	
}

int CNetClientEx::Recv(QzoneProtocolPacket& pack)
{
	if ( _host_info._sock_fd <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv Inalic socket:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						_host_info._sock_fd);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	pack.ResetPacket();
	QzoneProtocolPacket headPack;
	const int nHeadLen = sizeof(char) + sizeof(QzoneProtocolHead);
	char headBuffer[nHeadLen];
	int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
	if(nRet<=0)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv ip:%s port:%d timeout\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),
							_host_info._host_port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	int nRecv = recv(_host_info._sock_fd, headBuffer, nHeadLen, 0);
	if (nRecv < nHeadLen)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv packet ip:%s port:%d head error: len=%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),
							_host_info._host_port,nRecv);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	headPack.MapPacketHeadBuffer(headBuffer, nHeadLen);
	unsigned int iPacketLen = headPack.mappedLen();
	int iPacketBodyLen = headPack.bodySize(iPacketLen);
	if (iPacketBodyLen < 0 || (int)iPacketLen >= pack.bodyMaxLen() )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packetlen ip:%s port:%d error: packetlen=%d, bodylen=%d bodymax:%d\n", 
					__FILE__, __LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						iPacketLen, iPacketBodyLen,pack.bodyMaxLen());
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	
	/// 拷贝协议头,接续接收剩下的数据
	memcpy(pack.packet(), headBuffer, nHeadLen);
	int iRemain = iPacketLen - nHeadLen;
	int iRecv = nHeadLen;
	int iRetCode;
	while (iRemain > 0)
	{
		int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
		if(nRet<=0)
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s] ip:%s port:%d Recv timeout\n",
					__FILE__,__LINE__,__FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),
						_host_info._host_port);
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			Close();
			UpdateHost(-1,false);
			return -1;
		}
		
		iRetCode = recv(_host_info._sock_fd, pack.packet() + iRecv, iRemain, 0);
		if (iRetCode <= 0)
		{
			if (errno == EAGAIN)
				continue;
			else
				break;
		}
		iRecv += iRetCode;
		iRemain -= iRetCode;
	}
	if (iRecv != (int) iPacketLen)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]recv ip:%s port:%d len error: recv:%d != packlen:%d\n", 
				__FILE__, __LINE__, __FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
					iRecv, iPacketLen);	
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	
	/// packet input
	iRetCode = pack.Input(iPacketLen,false);
	if (iRetCode)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet ip:%s port:%d input error ret=%d\n", 
				__FILE__, __LINE__, __FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
					iRetCode);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	if ((pack.serverResponseFlag()) != 0 )
	{
		unsigned short error_code = pack.serverResponseInfo();
		
		if ( !_host_info._sock_keepcnt )	Close();
		UpdateHost(0,false);
		
		return error_code;
	}
	if ( !_host_info._sock_keepcnt )	Close();
	UpdateHost(0,false);
	
	return 0;
}

int CNetClientEx::Send(QzoneProtocolPacket& pack)
{
	_err_msg = "";
	
	if ( AllocHost() < 0 )	return -1;
	
	/*
	printf("$$$$$$$$$$$$$$$$$$$$net client alloc ip:%s port:%d sock_fd:%d\n",
			HOSTINFO::HostInt2Str(_host_info._host_ip),
				_host_info._host_port,
				_host_info._sock_fd);
	*/
	
	QzoneProtocolPtr  _sendPack;
	int			 	  _sendLen=0;
	int ret;
	if ( (ret=pack.Output((char*&)_sendPack,_sendLen,false)) != 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]pack Send error ret:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						ret);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	_host_info._sock_fd=AsyncConnect(_host_info._host_ip,_host_info._host_port);
	if ( _host_info._sock_fd < 0 )
	{
		UpdateHost(-1,true);
		
		return -1;
	}
	
	char* psend = (char*)_sendPack;
	int nsend =0;
	while(1 )
	{
		ret = send(_host_info._sock_fd,psend+nsend,(_sendLen-nsend),0);
		if ( ret <= 0 )
		{
			if ( errno == EAGAIN )	//no socket space erro
				continue;
			else
				break;
		}
		nsend += ret;
		if ( nsend >= _sendLen )
			break;
	}
	
	if ( nsend != _sendLen )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet send ip:%s port:%d error needlen:%d sendlen:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						_sendLen,nsend);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,true);
		return -1;
	}
	
	return 0;
}

int CNetClientEx::Recv(char* pbuf,int buf_size,int& buf_len)
{
	if ( _host_info._sock_fd <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv Inalic socket:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						_host_info._sock_fd);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	QzoneProtocolPacket headPack;
	const int nHeadLen = sizeof(char) + sizeof(QzoneProtocolHead);
	char headBuffer[nHeadLen];
	if ( buf_size < nHeadLen )	return -1;
	int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
	if(nRet<=0)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv ip:%s port:%d timeout\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),
							_host_info._host_port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	int nRecv = recv(_host_info._sock_fd, headBuffer, nHeadLen, 0);
	if (nRecv < nHeadLen)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv ip:%s port:%d packet head error: len=%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						nRecv);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	headPack.MapPacketHeadBuffer(headBuffer, nHeadLen);
	unsigned int iPacketLen = headPack.mappedLen();
	int iPacketBodyLen = headPack.bodySize(iPacketLen);
	if (iPacketBodyLen < 0)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packetlen ip:%s port:%d error: packetlen=%d, bodylen=%d\n", 
					__FILE__, __LINE__, __FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						iPacketLen, iPacketBodyLen);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	
	if ((unsigned int) buf_size < iPacketLen )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s] ip:%s port:%d buf too short:%d  packetlen=%d, bodylen=%d\n", 
					__FILE__, __LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
							 buf_size,iPacketLen, iPacketBodyLen);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	
	/// 拷贝协议头,接续接收剩下的数据	
	memcpy(pbuf, headBuffer, nHeadLen);
	int iRemain = iPacketLen - nHeadLen;
	int iRecv = nHeadLen;
	int iRetCode;
	while (iRemain > 0)
	{
		int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
		if(nRet<=0)
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]ip:%s port:%d Recv timeout\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port);
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			Close();
			UpdateHost(-1,false);
			return -1;
		}
		
		iRetCode = recv(_host_info._sock_fd, pbuf + iRecv, iRemain, 0);
		if (iRetCode <= 0)
		{
			if (errno == EAGAIN)
				continue;
			else
				break;
		}
		iRecv += iRetCode;
		iRemain -= iRetCode;
	}
	if (iRecv != (int) iPacketLen)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]recv ip:%s port:%d len error: recv:%d != packlen:%d\n", 
				__FILE__, __LINE__, __FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
					iRecv, iPacketLen);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	buf_len = iPacketLen;
	if ( !_host_info._sock_keepcnt )	Close();
	UpdateHost(0,false);
	
	return 0;
}

int CNetClientEx::Send(char* pbuf,int buf_len)
{
	_err_msg = "";
	
	if ( AllocHost() < 0 )	return -1;
	
	int ret;
	_host_info._sock_fd=AsyncConnect(_host_info._host_ip,_host_info._host_port);
	if ( _host_info._sock_fd < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]send async connect error ip:%s port:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		UpdateHost(-1,true);
		
		return -1;
	}
	
	char* psend = (char*)pbuf;
	int nsend =0;
	while(1 )
	{
		ret = send(_host_info._sock_fd,psend+nsend,(buf_len-nsend),0);
		if ( ret <= 0 )
		{
			if ( errno == EAGAIN )	//no socket space erro
				continue;
			else
				break;
		}
		nsend += ret;
		if ( nsend >= buf_len )
			break;
	}
	
	if ( nsend != buf_len )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet send ip:%s port:%d error needlen:%d sendlen:%d\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						buf_len,nsend);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,true);
		return -1;
	}
	
	return 0;
}

//无线接口
int CNetClientEx::RecvFromWire(char* pbuf,int buf_size,int& buf_len)
{
	if ( _host_info._sock_fd <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv Inalic socket:%d\n",
				__FILE__,__LINE__,__FUNCTION__,
					_host_info._sock_fd);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	if ( buf_size < (int)sizeof(int) )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv buf-size:%d too short\n",
				__FILE__,__LINE__,__FUNCTION__,
						buf_size);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	int _pack_head_len = sizeof(int);
	int _pack_len = 0 ;
	int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
	if(nRet<=0)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv ip:%s port:%d timeout\n",
				__FILE__,__LINE__,__FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	int nRecv = recv(_host_info._sock_fd, pbuf, _pack_head_len, 0);
	if (nRecv < _pack_head_len)
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]Recv ip:%s port:%d packet head error: len=%d\n",
				__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,nRecv);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	
	_pack_len = ntohl((*(int*)pbuf));
	if ( _pack_len > buf_size || _pack_len < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]invalid ip:%s port:%d Recv packet long:%d max:%d\n",
				__FILE__,__LINE__,__FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						_pack_len,buf_size);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	if ( _pack_len == 0 )
	{
		buf_len = _pack_head_len;
		UpdateHost(0,false);
		
		return 0;
	}
	
	pbuf += _pack_head_len;
	int iRemain = _pack_len - _pack_head_len;
	int iRecv = 0;
	int iRetCode;
	while (iRemain > 0)
	{
		int nRet=SelectSingleRead(_host_info._sock_fd,_host_info._sock_recv_timeout);
		if(nRet<=0)
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]ip:%s port:%d Recv timeout\n",
					__FILE__,__LINE__,__FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port);
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			Close();
			UpdateHost(-1,false);
			return -1;
		}
		
		iRetCode = recv(_host_info._sock_fd, pbuf + iRecv, iRemain, 0);
		if (iRetCode <= 0)
		{
			if (errno == EAGAIN)
				continue;
			else
				break;
		}
		iRecv += iRetCode;
		iRemain -= iRetCode;
	}
	if (iRecv != (_pack_len-_pack_head_len) )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]recv ip:%s port:%d len error: recv:%d != packlen:%d\n", 
				__FILE__, __LINE__,__FUNCTION__,
					HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						 iRecv, (_pack_len-_pack_head_len));
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		Close();
		UpdateHost(-1,false);
		return -1;
	}
	buf_len = _pack_len;
	if ( !_host_info._sock_keepcnt )	Close();
	UpdateHost(0,false);
	
	return 0;
}

int CNetClientEx::HostNum()
{
	return _qos_info.HostNum();
}

int CNetClientEx::HostQos(char* host_ip,short host_port,float& host_wt)
{
	int _ret = _qos_info.HostQos(host_ip,host_port,host_wt);
	if ( _ret < 0 )
	{
		_err_msg = _qos_info.GetErrMsg();
		
		return -1;
	}
	
	return 0;
}

int CNetClientEx::GetHost(int host_idx)
{
	_ret = _qos_info.AllocServer(_host_info,host_idx);
	if ( _ret < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]qos-info alloc server error:%s\n", 
				__FILE__, __LINE__,__FUNCTION__,
							_qos_info.GetErrMsg());
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	return 0;
}

int CNetClientEx::StartQos(int qos_rebuild_sec, float qos_extend_rate ,int req_min,ENUM_QOS_TYPE qos_type)
{
	_qos_type = qos_type;
	return _qos_info.Init(qos_rebuild_sec,qos_extend_rate,req_min,qos_type);
}

int CNetClientEx::AllocHost()
{
	if ( _qos_type != QOS_TYPE_NULL )
	{
		_ret = _qos_info.AllocServer(_host_info);
		if ( _ret < 0 )
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]qos-info alloc server error:%s\n", 
					__FILE__, __LINE__,__FUNCTION__,
								_qos_info.GetErrMsg());
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			
			return -1;
		}
	}
	/*
	printf("alloc ip:%s port:%d keep cnt:%d\n",
			HOSTINFO::HostInt2Str(_host_info._host_ip),
				_host_info._host_port,
				_host_info._sock_keepcnt);
	*/
	return 0;
}

int CNetClientEx::UpdateHost(int ret,bool net_err_flag)
{
	_ret = _qos_info.UpdateHost(_host_info,ret,0);
	if ( _ret < 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]qos-info UpdateHost error:%s\n", 
				__FILE__, __LINE__,__FUNCTION__,
							_qos_info.GetErrMsg());
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	return 0;
}

int CNetClientEx::GetHostInfo(vector<QOSHOSTINFO>& vec_host_info)
{
	return _qos_info.GetHostInfo(vec_host_info);
}

int CNetClientEx::SendAndRecv(QzoneProtocolPacket& send_pack,QzoneProtocolPacket& recv_pack,float time_out,bool& net_err_flag)
{
	int ret;
	QzoneProtocolPtr  _sendPack;
	int			 	  _sendLen=0;
	float	_time_out = time_out;
	float	_cnt_time = 0,_send_time = 0,_recv_time = 0;
	
	net_err_flag = false;
	if ( (ret=send_pack.Output((char*&)_sendPack,_sendLen,false)) != 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]pack Send error ret:%d\n",
					__FILE__,__LINE__,__FUNCTION__,ret);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		
		return -1;
	}
	
	struct timeval _begin_tm;
	struct timeval _end_tm;
	gettimeofday(&_begin_tm,NULL);
	//////////////////////////////////////////////////
	//begin connect server
	_host_info._sock_fd=AsyncConnect(_host_info._host_ip,_host_info._host_port,_time_out);
	if ( _host_info._sock_fd < 0 )
	{
		net_err_flag = true;
		return -1;
	}
	gettimeofday(&_end_tm,NULL);
	_cnt_time = (_end_tm.tv_sec - _begin_tm.tv_sec) + ((float)(_end_tm.tv_usec - _begin_tm.tv_usec))/1000000;
	_begin_tm = _end_tm;
	_time_out -= _cnt_time;
	if ( _time_out <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet send ip:%s port:%d,timeout-all:%f connect time:%f,no free time\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						time_out,_cnt_time);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		net_err_flag = true;
		UpdateHost(-1,true);
		
		return -1;
	}
	
	/////////////////////////////////////////////////
	//begin send data	
	char* psend = (char*)_sendPack;
	int nsend =0;
	while(1 )
	{
		ret = send(_host_info._sock_fd,psend+nsend,(_sendLen-nsend),0);
		if ( ret <= 0 )
		{
			if ( errno == EAGAIN )
				continue;
			else
				break;
		}
		nsend += ret;
		if ( nsend >= _sendLen )
			break;
	}
	
	if ( nsend != _sendLen )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet send ip:%s port:%d,send-len:%d pack-len:%d error\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						nsend,_sendLen);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		net_err_flag = true;
		UpdateHost(-1,true);
		
		return -1;
	}
	
	gettimeofday(&_end_tm,NULL);
	_send_time = (_end_tm.tv_sec - _begin_tm.tv_sec) + ((float)(_end_tm.tv_usec - _begin_tm.tv_usec))/1000000;
	_time_out -= _send_time;
	_begin_tm = _end_tm;
	if ( _time_out <= 0 )
	{
		_err_msg.resize(256); _err_msg = "";
		_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet send ip:%s port:%d,timeout-all:%f cnt-time:%f send-time:%f,no free time\n",
					__FILE__,__LINE__,__FUNCTION__,
						HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
						time_out,_cnt_time,_send_time);
		if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
		net_err_flag = true;
		UpdateHost(-1,true);
		
		return -1;
	}
	
	///////////////////////////////////////////////////
	//begin recv data	
	recv_pack.ResetPacket();
	char* _pack_buf = recv_pack.packet();
	int _pack_buf_size = recv_pack.bodyMaxLen();
	int	_pack_buf_len = 0;
	int _pack_head_len = recv_pack.headSize();
	float _recv_all_timeout = _time_out;
	for ( ; ; )
	{
		_ret = SelectSingleRead(_host_info._sock_fd,_time_out);
		if ( _ret <= 0 )
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet recv ip:%s port:%d,timeout-all:%f cnt-time:%f send-time:%f recv-time:%f timeout\n",
						__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
							time_out,_cnt_time,_send_time,_recv_all_timeout);
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			net_err_flag = true;
			UpdateHost(-1,true);
			
			return -1;
		}
		
		_ret = recv(_host_info._sock_fd,_pack_buf+_pack_buf_len,(_pack_buf_size-_pack_buf_len),0);
		if ( _ret <= 0 )
		{
			if ( errno == EAGAIN || errno == EINTR )
				continue;
			
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet recv ip:%s port:%d,timeout-all:%f cnt-time:%f send-time:%f recv ret:%d error:%s\n",
						__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
							time_out,_cnt_time,_send_time,_ret,strerror(errno));
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			net_err_flag = true;
			UpdateHost(-1,true);
			
			return -1;
		}
		_pack_buf_len += _ret;
		if ( _pack_buf_len >= _pack_head_len )
		{
			QzoneProtocolPacket _tmp_pack;
			if ( _tmp_pack.MapPacketHeadBuffer(_pack_buf,_pack_buf_len) != 0 )
			{
				_err_msg.resize(256); _err_msg = "";
				_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet recv ip:%s port:%d,map qzone-protcol head error\n",
							__FILE__,__LINE__,__FUNCTION__,
								HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port);
				if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
				UpdateHost(-1,true);
				
				return -1;
			}
			
			if ( _pack_buf_len == (int)_tmp_pack.mappedLen() )
			{
				_ret = recv_pack.Input(_pack_buf_len,false);
				if ( _ret != 0 )
				{
					_err_msg.resize(256); _err_msg = "";
					snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet recv ip:%s port:%d,map qzone-protcol buf error:%d\n",
								__FILE__,__LINE__,__FUNCTION__,
									HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,_ret);					
					UpdateHost(-1,true);
					
					return -1;
				}
				UpdateHost(0,false);
				
				return 0;
			}
		};
		
		gettimeofday(&_end_tm,NULL);
		_recv_time = (_end_tm.tv_sec - _begin_tm.tv_sec) + ((float)(_end_tm.tv_usec - _begin_tm.tv_usec))/1000000;
		_time_out -= _recv_time;
		if ( _time_out <= 0 )
		{
			_err_msg.resize(256); _err_msg = "";
			_ret = snprintf((char*)_err_msg.c_str(),255,"[%s][%d][%s]packet recv ip:%s port:%d,timeout-all:%f cnt-time:%f send-time:%f recv-timeout:%f,no free time\n",
						__FILE__,__LINE__,__FUNCTION__,
							HOSTINFO::HostInt2Str(_host_info._host_ip),_host_info._host_port,
							time_out,_cnt_time,_send_time,_recv_all_timeout);
			if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
			net_err_flag = true;
			UpdateHost(-1,true);
			
			return -1;
		}
	};
	
	return 0;
}
