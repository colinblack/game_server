#ifndef CPPSOCKET_SOCKET_H
#define CPPSOCKET_SOCKET_H

#include <sys/socket.h>
#include <fcntl.h>
#include <string>
#include <vector>

#include <address.h>
#include <option.h>
#include <exception.h>

  using std::string;
  class Socket
  {
  public:
    /// Errorcodes in Socket (witout LibC-errors)
    enum ErrorCode
    {
      NOT_OPENED_CODE = 0x0001,
      OPENED_CODE     = 0x0002
    };

    /// Supported Protocols
    enum Protocol
    {
      TCP = SOCK_STREAM,   ///< connection-oriented
      UDP = SOCK_DGRAM     ///< connectionless
    };

    /** Flags for send(), sendto(), recv() and recvfrom().
      * Can be combined with @e or.
      */
    enum Flags
    {
      OOB       = MSG_OOB,        ///< Out-Of-Band transmit
      DONTROUTE = MSG_DONTROUTE,  ///< Do not send packets over a router but directly
      DONTWAIT  = MSG_DONTWAIT,   ///< Use non-blocking mode      
      NOSIGNAL  = MSG_NOSIGNAL,   ///< Receive no signal when connected host cancels connection.
//      CONFIRM   = MSG_CONFIRM,    ///< Linux 2.3+
      PEEK      = MSG_PEEK,       ///< Do not clear receive buffer
      WAITALL   = MSG_WAITALL,    ///< Wait until all data is received
      TRUNC     = MSG_TRUNC,       ///< Return real packet size
      NONBLOCK  = O_NONBLOCK
    };

    /// How to shutdown the connection.
    enum Shutdown
    {
      READ       = SHUT_RD,       ///< No more data can be read.
      WRITE      = SHUT_WR,       ///< No more data can be written.
      READ_WRITE = SHUT_RDWR      ///< No data transport in both directions.
    };

    typedef int Descriptor;

    /** Create a socket that is closed.
      */
    Socket() throw();

    /** Create a socket with an already created file-descriptor.
      * This is used for descriptors that are returned by accept() which returns an opened socket.
      */
    explicit Socket(Descriptor sfd) throw();

    /** Create a socket and opens it.
      *
      * @param protocol The protocol to be used.
      *
      * @exception Exception An exception is thrown when the socket is already open or when it cannot be opened.
      */
    explicit Socket(Protocol protocol) throw (Exception);

    /** Destroy the socket.
      * If the socket is open close it.
      * @sa close()
      */
    ~Socket() throw();

    /** Opens the Socket.
      * Is like a call to socket() of the C API.
      *
      * @param protocol The protocol to be used.
      *
      * @exception Exception An exception is thrown when the socket is already open or when it cannot be opened.
      */
    void open(Protocol protocol) throw (Exception);

    /** Close the socket.
      *
      * @exception Exception An exception is thrown when the socket is already closed.
      */
    void close() throw (Exception);

    /** The sockets can be used like a file-descriptor.
      */
    operator Descriptor() throw () { return descriptor; }

	Socket& operator=(Descriptor socket) { descriptor = socket; return *this; }	

    bool isOpened() throw () { return descriptor >= 0; } //linux 文件描述符可以为0，切记!!!

    /** Assign this socket an address. (classic)
      *
      * @param addr Address to be assigned.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API bind() returns an error.
      */
    void bind(const sockaddr_in& addr) throw (Exception);

    /** Assign this socket an address.
      *
      * @param addr Address to be assigned.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API bind() returns an error.
      */
    void bind(const Address& addr) throw (Exception);

    /** Connect this sockets to another socket. (classic)
      *
      * @param addr The address of the other socket.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API connect() returns an error.
      */
    void connect(const sockaddr_in& addr) throw (Exception);

    /** Connect this sockets to another socket.
      *
      * @param addr The address of the other socket.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API connect() returns an error.
      */
    void connect(const Address& addr) throw (Exception);

    /** Send data through the socket. (classic)
      * A connection must be established.
      *
      * @param data Pointer to the beginning of the data.
      * @param size How many bytes should be sent.
      * @param flags Optional flags to tune the behaviour.
      *
      * @return How many byte are really sent.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API send() returns an error.
      *
      * @sa recv()
      */
    int send(const char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);

    /** Send data to @e addr (classic).
      *
      * @param addr Address to which the data should be sent.
      * @param data Pointer to the beginning of the data.
      * @param size How many bytes should be sent.
      * @param flags Optional flags to tune the behaviour.
      *
      * @return How many byte are really sent.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API sendto() returns an error.
      *
      * @sa recvfrom()
      */
    int sendto(const sockaddr_in& addr, const char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);
    int sendto(const Address& addr, const char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);
    /** Read data from socket (classic).
      * A connection must be established.
      *
      * @param data Pointer to the buffer that the read data should be put in.
      * @param size Maximum of bytes allowed to be read => size of buffer.
      * @param flags Optional flags to tune the behaviour.
      *
      * @return How many bytes are really read.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API recv() returns an error.
      *
      * @sa send()
      */
    int recv(char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);

    /** Read data from socket (classic).
      * The address of the sender is returned in @e addr.
      *
      * @param addr Address of the sender.
      * @param data Pointer to the buffer that the read data should be put in.
      * @param size Maximum of bytes allowed to be read => size of buffer.
      * @param flags Optional flags to tune the behaviour.
      *
      * @return How many bytes are really read.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API recvfrom() returns an error.
      *
      * @sa sendto()
      */
    int recvfrom(sockaddr_in& addr, char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);
    int recvfrom(Address& addr, char* data, size_t size, int flags = MSG_NOSIGNAL) throw (Exception);
    
    /** Wait for connections.
      *
      * @param queuelen Maximum number of clients in wait-queue.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API listen() returns an error.
      */
    void listen(int queuelen) throw (Exception);

    /** Accept connection (classic).
      * Waits until a connection in established.
      *
      * @param addr Connected client address
      *
      * @return Socket descriptor for new connection. (Data transfer-channel)
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API accept() returns an error.
      */
    Descriptor accept(sockaddr_in& addr) throw (Exception);

    /** Accept connection.
      * Waits until a connection in established.
      *
      * @param addr Connected client address
      *
      * @return Socket descriptor for new connection. (Data transfer-channel)
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API accept() returns an error.
      */
    Descriptor accept(Address& addr) throw (Exception);

    /** Returns the address of the socket.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API getsockname() returns an error.
      *
      * @sa getpeername()
      */
    Address getsockname() throw (Exception);

    /** Returns the address of the connected host.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API getpeername() returns an error.
      *
      * @sa getsockname()
      */
    Address getpeername() throw (Exception);

    /** Read socket option.
      *
      * The options are available as classes in the sub-namespaces of CPPSocket:
      * SocketOption, IPOption and TCPOption.
      *
      * @param option Option to be read.
      *
      * @return How many bytes has the read value.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API getsockopt() returns an error.
      *
      * @sa setsockopt()
      */
    static int getsockopt(Descriptor descriptor,Option& option) throw (Exception);

    /** Set socket option.
      *
      * The options are available as classes in the sub-namespaces of CPPSocket:
      * SocketOption, IPOption and TCPOption.
      *
      * @param option Option to be set.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API setsockopt() returns an error.
      *
      * @sa getsockopt()
      */
    static void setsockopt(Descriptor descriptor,const Option& option) throw (Exception);
    static void fcntl(Descriptor descriptor,int flag) throw (Exception);
    /** Cancel active full-duplex connection.
      * See Shutdown for more info.
      *
      * @param how How to shutdown the connection.
      *
      * @exception Exception An exception is thrown when the socket is not opened or the call to C API shutdown() returns an error.
      */
    void shutdown(Shutdown how) throw (Exception);
    /** Wait for socket can be read, written or for an exception.
      * This is a select for exactly one socket.
      *
      * The read, write and exception flags are set, when the appropriate event occurred.
      * E.g. when the method returns true and read is true, there had some data arrived on the socket.
      *
      * @param read Wait until there is something available to read from the socket.
      * @param write Wait until a write would not block.
      * @param exception Test for exception on the socket.
      * @param seconds Timeout in seconds.
      * @param useconds Timeout in microseconds.
      *
      * @return True, if no timeout occurred.
      */
    bool wait(bool& read, bool& write, bool& exception, int seconds = 0, int useconds = 0) throw (Exception);
	
	bool canRead();
	
	bool canWrite();

  private:
    /// filedescriptor; if >= 0 it is valid; else not opened
    Descriptor descriptor;
    Socket(Socket& socket);  
    Socket& operator=(Socket& socket);
  };

#endif
