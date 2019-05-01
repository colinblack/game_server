#include <address.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

  /// Errormessages in Address. (without libc-messages)
  namespace ErrorMessages
  {
    static const string NO_IP        = "No IP-Address";
    static const string OFF_RANGE    = "Index out of Range";
  }

  /// Methods where an exception can be thrown
  namespace MethodNames
  {
    static const string ADDRESS      = "Address::Address()";
    static const string SOCKADDR_IN  = "Address::sockaddr_in()";
    static const string LOOKUP       = "Address::lookup()";
    static const string GETALIASNAME = "Address::getAliasName()";
    static const string GETIPSTRING  = "Address::getIPString()";
  }

  using namespace ErrorMessages;
  using namespace MethodNames;

  const string Address::ANY_IP = "0.0.0.0";

  Address::Address(const string & ip, Port _port)
  {
    in_addr address;
    // Try to convert ip-string to binary ip.
    if(inet_aton(ip.c_str(), &address) == 0){
    	throw HLibCException(ADDRESS);
    }else{
      // IP could be converted to binary ip
      ipAddresses = address;
    }
    port = htons(_port);
  }

  Address::Address(uint32_t ip, Port _port)
  {
  		ipAddresses.s_addr = htonl(ip);
  		port = htons(_port);
  }
  
  Address::Address(const sockaddr_in & address) 
  {
    ipAddresses = address.sin_addr;

    port = address.sin_port;
  }

  Address::Address(const Address & address) 
 	{
 		ipAddresses = address.ipAddresses;

    port = address.port;
 	}
	
  Address::operator sockaddr_in() const throw (Exception)
  {
    sockaddr_in address;
    bzero(&address,sizeof(sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = port;
    address.sin_addr = ipAddresses;

    return address;
  }

  void Address::operator=(const sockaddr_in & address)
  {
    ipAddresses = address.sin_addr;

    port = address.sin_port;
  }
  
  void Address:: operator=(const Address& address) 
  {
  	ipAddresses = address.ipAddresses;

    port = address.port;
  }

  bool Address:: operator==(const Address& address)
  {
  		return (ipAddresses.s_addr == address.ipAddresses.s_addr) && (port == address.port) ;
  }

  Address::Port Address::getPort() const throw()
  {
    return ntohs(port);
  }
      
  string Address::getIP()const throw()
  {
    return inet_ntoa(ipAddresses);
  }
    
	unsigned int Address::getIPINT() const throw()
  {
    return ntohl(ipAddresses.s_addr);
  }
  
