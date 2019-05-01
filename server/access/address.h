
#ifndef CPPSOCKET_ADDRESS_H
#define CPPSOCKET_ADDRESS_H

#include <stdint.h>
#include <string>
#include <vector>
#include <netinet/in.h>


#include <exception.h>

  using std::string;
  class Address
  {
  public:
    /// Errorcodes (Without LibC-errorcodes)
    enum ErrorCode
    {
      NO_IP_CODE     = 0x0101, ///< No valid IP address
      OFF_RANGE_CODE = 0x0102  ///< Index out of valid range
    };

    /// Map CPPSocket Port type to system-dependant port type
    typedef in_port_t Port;

    /// Can be used when no IP-address should be specified
    static const string ANY_IP;

    explicit Address(const string& ip = ANY_IP, Port port = 0);
    
    explicit Address(uint32_t ip , Port port = 0);
    /** Construct an address from a classic sockaddr_in.
      * @b No lookup is made.
      *
      * @param address Address that should be copied.
      */
    Address(const sockaddr_in& address);
    
    Address(const Address& address);

    /** Cast the Address into sockaddr_in.
      * The first found IP is used to create the sockaddr_in.
      *
      * @return Socket-Address in classic format.
      *
      * @exception Exception An exception is thrown when there are no valid IPs.
      */
    operator sockaddr_in() const throw (Exception);

    /** Assignment of sockaddr_in
      *
      * @param address Address that should be copied.
      */
    void operator=(const sockaddr_in& address);

    void operator=(const Address& address);
    
   	bool operator==(const Address& address);
   	
    Port getPort() const throw();
    
    
    string getIP()const throw();
    
    inline unsigned int getIP2INT()const throw(){ return ipAddresses.s_addr; }  // net-order
    unsigned int getIPINT()const throw() ; // host-order
  private:
    in_addr ipAddresses;

    /// The portnumber in netbyteorder
    Port port;

  };

#endif
