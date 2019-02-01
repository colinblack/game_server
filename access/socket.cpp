#include <socket.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

  /// Error returncodes of the C API functions.
  namespace ErrorReturnValues
  {
    const int SOCKET_ERROR      = -1;
    const int BIND_ERROR        = -1;
    const int CONNECT_ERROR     = -1;
    const int SEND_ERROR        = -1;
    const int RECV_ERROR        = -1;
    const int LISTEN_ERROR      = -1;
    const int ACCEPT_ERROR      = -1;
    const int GETSOCKNAME_ERROR = -1;
    const int GETPEERNAME_ERROR = -1;
    const int GETSOCKOPT_ERROR  = -1;
    const int SETSOCKOPT_ERROR  = -1;
    const int SOCKFCNTL_ERROR  = -1;
    const int SHUTDOWN_ERROR    = -1;
  }

  /// Errormessages of the Socket-class (w/o LibC-Errors)
  namespace ErrorMessages
  {
    const string NOT_OPENED  = "Socket not opened yet";
    const string OPENED      = "Socket already opened";
  }

  /// Methodnames that can throw exceptions.
  namespace MethodNames
  {
    const string OPEN        = "Socket::open()";
    const string CLOSE       = "Socket::close()";
    const string BIND        = "Socket::bind()";
    const string CONNECT     = "Socket::connect()";
    const string SEND        = "Socket::send()";
    const string SENDTO      = "Socket::sendto()";
    const string RECV        = "Socket::recv()";
    const string RECVFROM    = "Socket::recvfrom()";
    const string LISTEN      = "Socket::listen()";
    const string ACCEPT      = "Socket::accept()";
    const string GETSOCKNAME = "Socket::getsockname()";
    const string GETPEERNAME = "Socket::getpeername()";
    const string GETSOCKOPT  = "Socket::getsockopt()";
    const string SETSOCKOPT  = "Socket::setsockopt()";
    const string SOCKFCNTL   = "Socket::fcntl()";
    const string SHUTDOWN    = "Socket::shutdown()";
    const string WAIT        = "Socket::wait()";
  }

  using namespace ErrorReturnValues;
  using namespace ErrorMessages;
  using namespace MethodNames;

  Socket::Socket() throw()
    : descriptor(-1)
  {
  }

  Socket::Socket(int sfd) throw()
    : descriptor(sfd)
  {
  }

  Socket::Socket(Protocol protocol) throw (Exception)
  {
    open(protocol);
  }

  Socket::~Socket() throw()
  {
    if(isOpened())
    {
      ::close(descriptor);
      	
      descriptor = -1;
    }
  }

  void Socket::open(Protocol protocol) throw (Exception)
  {
    if(isOpened())
    {
      throw Exception(OPEN, OPENED, OPENED_CODE);
    }

    descriptor = socket(PF_INET, protocol, 0);

    if(descriptor == SOCKET_ERROR)
    {
      throw LibCException(OPEN);
    }
  }

  void Socket::close() throw (Exception)
  {
    if(!isOpened())
    {
      throw Exception(CLOSE, NOT_OPENED, NOT_OPENED_CODE);
    }

    ::close(descriptor);

    descriptor = -1;
  }

  void Socket::bind(const sockaddr_in& addr) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(BIND, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);

    error = ::bind(descriptor, socketAddress, sizeof(addr));

    if(error == BIND_ERROR)
    {
      throw LibCException(BIND);
    }
  }

  void Socket::bind(const Address& addr) throw (Exception)
  {
    bind(static_cast<const sockaddr_in>(addr));
  }

  void Socket::connect(const sockaddr_in& addr) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(CONNECT, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);
    
    error = ::connect(descriptor, socketAddress, sizeof(addr));

    if(error == CONNECT_ERROR)
    {
    	if( EINPROGRESS == errno ) return ; //非阻塞connect ,表示已经进入连接过程
      throw LibCException(CONNECT);
    }
  }

  void Socket::connect(const Address& addr) throw (Exception)
  {
    connect(static_cast<const sockaddr_in>(addr));
  }

  int Socket::send(const char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(SEND, NOT_OPENED, NOT_OPENED_CODE);
    }
    do{
    	
      bytes = ::send(descriptor, data, size, flags);
     
    }while( bytes<0 && EINTR == errno );

    if(bytes == SEND_ERROR)
    {
      throw LibCException(SEND);
    }

    return bytes;
  }

  int Socket::sendto(const sockaddr_in& addr, const char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(SENDTO, NOT_OPENED, NOT_OPENED_CODE);
    }

    const sockaddr* socketAddress = reinterpret_cast<const sockaddr*>(&addr);
    
    do{

      bytes = ::sendto(descriptor, data, size, flags, socketAddress, sizeof(addr));

    }while( bytes<0 && EINTR == errno );
    
    if(bytes == SEND_ERROR)
    {
      throw LibCException(SENDTO);
    }

    return bytes;
  }

  int Socket::sendto(const Address& addr, const char* data, size_t size, int flags) throw (Exception)
  {
  	return sendto(static_cast<const sockaddr_in>(addr),data,size,flags);
  }	
  
  int Socket::recv(char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(RECV, NOT_OPENED, NOT_OPENED_CODE);
    }
    do{
    	
      bytes = ::recv(descriptor, data, size, flags);
    	
    }while( bytes<0 && EINTR == errno );
    
    if(bytes == RECV_ERROR)
    {
      throw LibCException(RECV);
    }

    return bytes;
  }

  int Socket::recvfrom(sockaddr_in& addr, char* data, size_t size, int flags) throw (Exception)
  {
    int bytes;

    if(!isOpened())
    {
      throw Exception(RECVFROM, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t addrLen = sizeof(addr);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);
    
    do{
    
      bytes = ::recvfrom(descriptor, data, size, flags, socketAddress, &addrLen);

    }while( bytes<0 && EINTR == errno );
    
    if(bytes == RECV_ERROR)
    {
      throw LibCException(RECVFROM);
    }

    return bytes;
  }
  
  int Socket::recvfrom(Address& addr, char* data, size_t size, int flags) throw (Exception)
	{
		sockaddr_in saddr;
		int bytes = recvfrom(saddr,data,size,flags);
		addr = saddr;
		return bytes;
	}
	
  void Socket::listen(int queuelen) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(LISTEN, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::listen(descriptor, queuelen);

    if(error == LISTEN_ERROR)
    {
      throw LibCException(LISTEN);
    }
  }

  Socket::Descriptor Socket::accept(sockaddr_in& addr) throw (Exception)
  {
    Descriptor sfd;

    if(!isOpened())
    {
      throw Exception(ACCEPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t addrLen = sizeof(addr);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&addr);
    	
    do{
    	
      sfd = ::accept(descriptor, socketAddress, &addrLen);
      
    }while(sfd == ACCEPT_ERROR &&(ECONNABORTED == errno || EINTR == errno ));
    
    if(sfd == ACCEPT_ERROR)
    {
    	if( EAGAIN == errno || EMFILE == errno || ENFILE == errno ) return ACCEPT_ERROR ; //The socket is marked non-blocking and no connections are present to be accepted.
      throw LibCException(ACCEPT);
    }

    return sfd;
  }

  Socket::Descriptor Socket::accept(Address& addr) throw (Exception)
  {
    Descriptor tempSocket;

    sockaddr_in address = addr;

    tempSocket = accept(address);

    addr = address;

    return tempSocket;
  }

  Address Socket::getsockname() throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(GETSOCKNAME, NOT_OPENED, NOT_OPENED_CODE);
    }

    sockaddr_in address;
    socklen_t addrLen = sizeof(address);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);

    error = ::getsockname(descriptor, socketAddress, &addrLen);

    if(error == GETSOCKNAME_ERROR)
    {
      throw LibCException(GETSOCKNAME);
    }

    return Address(address);
  }

  Address Socket::getpeername() throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(GETPEERNAME, NOT_OPENED, NOT_OPENED_CODE);
    }

    sockaddr_in address;
    socklen_t addrLen = sizeof(address);

    sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);

    error = ::getpeername(descriptor, socketAddress, &addrLen);

    if(error == GETPEERNAME_ERROR)
    {
      throw LibCException(GETPEERNAME);
    }

    return Address(address);
  }

  int Socket::getsockopt(Descriptor descriptor,Option& option) throw (Exception)
  {
    int error;

    if( descriptor <= 0 )
    {
      throw Exception(GETSOCKOPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    socklen_t optSize = option.size();

    error = ::getsockopt(descriptor, option.level(), option.id(), option.pointer(), &optSize);

    if(error == GETSOCKOPT_ERROR)
    {
      throw LibCException(GETSOCKOPT);
    }

    return optSize;
  }

  void Socket::setsockopt(Descriptor descriptor,const Option& option) throw (Exception)
  {
    int error;

    if( descriptor < 0 )
    {
      throw Exception(SETSOCKOPT, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::setsockopt(descriptor, option.level(), option.id(), option.pointer(), option.size());

    if(error == SETSOCKOPT_ERROR)
    {
      throw LibCException(SETSOCKOPT);
    }
  }
  
  void Socket::fcntl(Descriptor descriptor,int flag) throw (Exception)
  {
  	int error;

    if( descriptor < 0 )
    {
      throw Exception(SOCKFCNTL, NOT_OPENED, NOT_OPENED_CODE);
    }
    
    int iFcntlVal = ::fcntl(descriptor, F_GETFL, 0); 
    	
	  error = ::fcntl(descriptor, F_SETFL, iFcntlVal|flag);
	  	
    if(error == SOCKFCNTL_ERROR)
    {
      throw LibCException(SOCKFCNTL);
    }
    
  }
  
  void Socket::shutdown(Shutdown how) throw (Exception)
  {
    int error;

    if(!isOpened())
    {
      throw Exception(SHUTDOWN, NOT_OPENED, NOT_OPENED_CODE);
    }

    error = ::shutdown(descriptor, how);

    if(error == SHUTDOWN_ERROR && ENOTCONN != errno)
    {
      throw LibCException(SHUTDOWN);
    }
  }
  
  bool Socket::wait(bool& read, bool& write, bool& exception, int seconds, int useconds) throw (Exception)
  {
    if(!isOpened())
    {
      throw Exception(WAIT, NOT_OPENED, NOT_OPENED_CODE);
    }

    struct timeval time;
    time.tv_sec  = seconds;
    time.tv_usec = useconds;

    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;

    if(read)
    {
    	FD_ZERO(&readfds);
      FD_SET(descriptor, &readfds);
    }

    if(write)
    {
    	FD_ZERO(&writefds);
      FD_SET(descriptor, &writefds);
    }

    if(exception)
    {
      FD_ZERO(&exceptfds);
      FD_SET(descriptor, &exceptfds);
    }
    
    int ret = 0;
    
    do{
    
      ret = select(descriptor+1,(read  ? &readfds : NULL), (write ? &writefds : NULL), (exception ? &exceptfds :NULL), &time);
    
    }while( ret < 0 && EINTR == errno );
    
    if( ret <=0 ) return false;
    	
    if(read)
    {
      read = FD_ISSET(descriptor, &readfds);     
    }

    if(write)
    {
      write = FD_ISSET(descriptor, &writefds);
    }

    if(exception)
    {
      exception = FD_ISSET(descriptor, &exceptfds);
    }
/*
    if(ret < 0)
    {
      throw LibCException(WAIT);
    }
*/
    return true;
  }  
  
  bool Socket:: canRead()
  {
	bool r = true;
	bool w = false;
	bool e = true;
	return wait(r,w,e) && r ;
  }
  
  bool Socket:: canWrite()
  {
	bool r = false;
	bool w = true;
	bool e = true;
	return wait(r,w,e) && w;
  }

