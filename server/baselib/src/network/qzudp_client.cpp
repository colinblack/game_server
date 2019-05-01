#include "qzudp_client.h"
#include "neterrcode.h"


QZONE::CUdpClient::CUdpClient()
{
    _err_msg.reserve(512+1);
    _sock_fd = NE_INVALID_SD;
}

QZONE::CUdpClient::~CUdpClient()
{
    if ( _sock_fd > 0 ) close(_sock_fd);
    _sock_fd = NE_INVALID_SD;	
}

int QZONE::CUdpClient::Init(HOSTADDR host_addr)
{	
    _err_msg = "";
    int _fd = socket(AF_INET,SOCK_DGRAM,0);
    if(_fd < 0)
    {		
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]create socket err:%s\n",
                __FILE__,__LINE__,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_SOCKET;
    }
    if ( _sock_fd > 0 ) close(_sock_fd);
    _sock_fd = _fd;	
    _host_addr = host_addr;

    return 0;
}

int QZONE::CUdpClient::SendBuf(char* buf,int buf_len)
{
    _err_msg = "";
    if ( _sock_fd <= 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]sock-fd is invalid\n",
                __FILE__,__LINE__);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INVALID_SD;
    }

    struct sockaddr_in 	_addr;
    int					_addr_len = sizeof(_addr);

    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    if(inet_aton((char*)_host_addr._host_ip.c_str(),&_addr.sin_addr) < 0)
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]inet_aton socket ip:%s port:%hu err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INVALID_IP;
    }
    _addr.sin_port = htons(_host_addr._host_port);

    _ret = sendto(_sock_fd,buf,buf_len,0,(struct sockaddr*)&_addr,_addr_len);	
    if ( _ret != buf_len )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]socket sendto ip:%s port:%hu buf-len:%d ret:%d err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,buf_len,_ret,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_SEND;
    }

    return 0;
}

int QZONE::CUdpClient::RecvBuf(char* buf,int buf_size,int& buf_len,float time_out)
{
    _err_msg = "";
    if ( _sock_fd <= 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]sock-fd is null\n",
                __FILE__,__LINE__);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INVALID_SD;
    }

    time_out = (time_out>=0)?time_out:_host_addr._time_out;
    struct timeval 		_tv;
    _tv.tv_sec = (int)time_out;
    _tv.tv_usec = (int)((time_out-(int)time_out)*1000000);

    struct sockaddr_in 	_addr;
    int					_addr_len = sizeof(_addr);

    bzero(&_addr,sizeof(_addr));
    /*
       _addr.sin_family = AF_INET;
       if(inet_aton(_host_addr._host_ip.c_str(),&_addr.sin_addr) < 0)
       {
       _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]inet_aton socket ip:%s port:%hu err:%s\n",
       __FILE__,__LINE__,
       _host_addr._host_ip.c_str(),_host_addr._host_port,strerror(errno));
       if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

       return -1;
       }
       _addr.sin_port = htons(_host_addr._host_port);
     */

    setsockopt(_sock_fd , SOL_SOCKET,SO_RCVTIMEO,&_tv,sizeof(_tv));
    _ret = recvfrom(_sock_fd,buf,buf_size,0,(struct sockaddr*)&_addr,(socklen_t *) &_addr_len);
    if ( _ret <= 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]socket recvfrom invalid ip:%s port:%hu ret:%d err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,_ret,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_RECV;
    }
    buf_len = _ret;

    return 0;
}

int QZONE::CUdpClient::BeginTrans(char* buf,int buf_size,int& buf_len,float time_out)
{
    _err_msg = "";
    if ( _sock_fd <= 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]sock-fd is null\n",
                __FILE__,__LINE__);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INVALID_SD;
    }

    struct sockaddr_in 	_addr;
    int					_addr_len = sizeof(_addr);

    bzero(&_addr,sizeof(_addr));
    _addr.sin_family = AF_INET;
    if(inet_aton(_host_addr._host_ip.c_str(),&_addr.sin_addr) < 0)
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]inet_aton socket ip:%s port:%hu err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INVALID_IP;
    }
    _addr.sin_port = htons(_host_addr._host_port);

    time_out = (time_out>=0)?time_out:_host_addr._time_out;
    struct timeval 		_tv;
    _tv.tv_sec = (int)time_out;
    _tv.tv_usec = (int)((time_out-(int)time_out)*1000000);

    _ret = sendto(_sock_fd,buf,buf_len,0,(struct sockaddr*)&_addr,_addr_len);	
    if ( _ret != buf_len )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]socket sendto ip:%s port:%hu buf-len:%d ret:%d err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,buf_len,_ret,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_SEND;
    }

    setsockopt(_sock_fd , SOL_SOCKET,SO_RCVTIMEO,&_tv,sizeof(_tv));
    _ret = recvfrom(_sock_fd,buf,buf_size,0,(struct sockaddr*)&_addr,(socklen_t *) &_addr_len);
    if ( _ret <= 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]socket recvfrom invalid ip:%s port:%hu ret:%d err:%s\n",
                __FILE__,__LINE__,
                _host_addr._host_ip.c_str(),_host_addr._host_port,_ret,strerror(errno));
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_RECV;
    }
    buf_len = _ret;

    return 0;
}

int QZONE::CUdpClient::SendPack(QzoneProtocolPacket& send_pack)
{
    _err_msg = "";

    QzoneProtocolPtr  _send_buf;
    int			 	  _send_len=0;
    _ret = send_pack.Output((char*&)_send_buf,_send_len,false);
    if ( _ret != 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]packet output error:%d\n",
                __FILE__,__LINE__,_ret);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_OUTPUT;
    }

    _ret = SendBuf((char*)_send_buf,_send_len);
    if ( _ret < 0 )	return _ret;

    return 0;
}

int QZONE::CUdpClient::RecvPack(QzoneProtocolPacket& recv_pack,float time_out)
{
    _err_msg = "";
    int _recv_len;

    _ret = RecvBuf(recv_pack.packet(),recv_pack.bodyMaxLen(),_recv_len,time_out);
    if ( _ret != 0 )	return _ret;

    _ret = recv_pack.Input(_recv_len,false);
    if ( _ret != 0 )
    {
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d]recv from host input error:%d\n",
                __FILE__,__LINE__,_ret);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';

        return NE_INPUT;
    }

    if ((recv_pack.serverResponseFlag()) != 0 )
    {
        int error_code = (short)recv_pack.serverResponseInfo();
        _ret = snprintf((char*)_err_msg.c_str(),512,"[%s][%d] server ret:%d\n",
                __FILE__,__LINE__, error_code);
        if ( _ret >= 0 ) *((char*)_err_msg.c_str()+_ret) = '\0';
        return error_code;
    }

    return 0;
}

