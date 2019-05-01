
#ifndef CPPSOCKET_EXCEPTION_H
#define CPPSOCKET_EXCEPTION_H

#include <errno.h>
#include <netdb.h>
#include <string>
#include <exception>
#include <string.h>

  using std::string;
  using std::exception;

  /** Baseclass for all exceptions in cppsocket-library
    *
    * @author Ralf-Christian Jürgensen
    */
  class Exception : public exception
  {
  public:
    Exception(const string& _method, const string& _message, int _code) throw()
      : method(_method), message(_message), code(_code)
    {}
    
    virtual ~Exception() throw() {}
    
    const string& getMethod()  const throw() { return method;  }
    const string& getMessage() const throw() { return message; }
    int getCode()              const throw() { return code;    }

    virtual const char* what() const throw() { return (method+"[method <--> message ] "+ message).c_str() ; }
    
  protected:
    string method;  ///< Method, which throwed the eception
    string message; ///< Errormessage
    int code;       ///< Errorcode
  };

  /** Special class for @c errno errors.
    *
    * @author Ralf-Christian Jürgensen
    */
  class LibCException : public Exception
  {
  public:
    /// Use @c errno as errorcode and errormessage.
    LibCException(const string& method) throw()
      : Exception(method, strerror(errno), errno)
    {}
  };

  /** Special class for @c h_errno errors.
    *
    * @author Ralf-Christian Jürgensen
    */
  class HLibCException : public Exception
  {
  public:
    /// Use @c h_errno as errorcode and errormessage
    HLibCException(const string& method) throw()
      : Exception(method, hstrerror(h_errno), h_errno)
    {}
  };

#endif
