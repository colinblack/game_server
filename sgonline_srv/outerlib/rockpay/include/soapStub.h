/* soapStub.h
   Generated by gSOAP 2.8.3 from pockpay.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_ns1	"http://tempuri.org/"
#include "stdsoap2.h"

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns1__ArrayOfString
#define SOAP_TYPE_ns1__ArrayOfString (8)
/* ns1:ArrayOfString */
class SOAP_CMAC ns1__ArrayOfString
{
public:
	std::vector<std::string >string;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique id SOAP_TYPE_ns1__ArrayOfString */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__ArrayOfString() { ns1__ArrayOfString::soap_default(NULL); }
	virtual ~ns1__ArrayOfString() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CheckTransaction
#define SOAP_TYPE__ns1__CheckTransaction (9)
/* ns1:CheckTransaction */
class SOAP_CMAC _ns1__CheckTransaction
{
public:
	std::string *app_USCOREid;	/* optional element of type xsd:string */
	std::string *transaction_USCOREid;	/* optional element of type xsd:string */
	std::string *verify_USCOREcode;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 9; } /* = unique id SOAP_TYPE__ns1__CheckTransaction */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CheckTransaction() { _ns1__CheckTransaction::soap_default(NULL); }
	virtual ~_ns1__CheckTransaction() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CheckTransactionResponse
#define SOAP_TYPE__ns1__CheckTransactionResponse (10)
/* ns1:CheckTransactionResponse */
class SOAP_CMAC _ns1__CheckTransactionResponse
{
public:
	ns1__ArrayOfString *CheckTransactionResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:ArrayOfString */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 10; } /* = unique id SOAP_TYPE__ns1__CheckTransactionResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CheckTransactionResponse() { _ns1__CheckTransactionResponse::soap_default(NULL); }
	virtual ~_ns1__CheckTransactionResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CheckTransactionWithCurrency
#define SOAP_TYPE__ns1__CheckTransactionWithCurrency (11)
/* ns1:CheckTransactionWithCurrency */
class SOAP_CMAC _ns1__CheckTransactionWithCurrency
{
public:
	std::string *app_USCOREid;	/* optional element of type xsd:string */
	std::string *transaction_USCOREid;	/* optional element of type xsd:string */
	std::string *verify_USCOREcode;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 11; } /* = unique id SOAP_TYPE__ns1__CheckTransactionWithCurrency */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CheckTransactionWithCurrency() { _ns1__CheckTransactionWithCurrency::soap_default(NULL); }
	virtual ~_ns1__CheckTransactionWithCurrency() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CheckTransactionWithCurrencyResponse
#define SOAP_TYPE__ns1__CheckTransactionWithCurrencyResponse (12)
/* ns1:CheckTransactionWithCurrencyResponse */
class SOAP_CMAC _ns1__CheckTransactionWithCurrencyResponse
{
public:
	ns1__ArrayOfString *CheckTransactionWithCurrencyResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:ArrayOfString */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 12; } /* = unique id SOAP_TYPE__ns1__CheckTransactionWithCurrencyResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CheckTransactionWithCurrencyResponse() { _ns1__CheckTransactionWithCurrencyResponse::soap_default(NULL); }
	virtual ~_ns1__CheckTransactionWithCurrencyResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CommitTransaction
#define SOAP_TYPE__ns1__CommitTransaction (13)
/* ns1:CommitTransaction */
class SOAP_CMAC _ns1__CommitTransaction
{
public:
	std::string *app_USCOREid;	/* optional element of type xsd:string */
	std::string *transaction_USCOREid;	/* optional element of type xsd:string */
	std::string *verify_USCOREcode;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 13; } /* = unique id SOAP_TYPE__ns1__CommitTransaction */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CommitTransaction() { _ns1__CommitTransaction::soap_default(NULL); }
	virtual ~_ns1__CommitTransaction() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CommitTransactionResponse
#define SOAP_TYPE__ns1__CommitTransactionResponse (14)
/* ns1:CommitTransactionResponse */
class SOAP_CMAC _ns1__CommitTransactionResponse
{
public:
	ns1__ArrayOfString *CommitTransactionResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:ArrayOfString */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 14; } /* = unique id SOAP_TYPE__ns1__CommitTransactionResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CommitTransactionResponse() { _ns1__CommitTransactionResponse::soap_default(NULL); }
	virtual ~_ns1__CommitTransactionResponse() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CommitTransactionNTD
#define SOAP_TYPE__ns1__CommitTransactionNTD (15)
/* ns1:CommitTransactionNTD */
class SOAP_CMAC _ns1__CommitTransactionNTD
{
public:
	std::string *app_USCOREid;	/* optional element of type xsd:string */
	std::string *transaction_USCOREid;	/* optional element of type xsd:string */
	std::string *verify_USCOREcode;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 15; } /* = unique id SOAP_TYPE__ns1__CommitTransactionNTD */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CommitTransactionNTD() { _ns1__CommitTransactionNTD::soap_default(NULL); }
	virtual ~_ns1__CommitTransactionNTD() { }
};
#endif

#ifndef SOAP_TYPE__ns1__CommitTransactionNTDResponse
#define SOAP_TYPE__ns1__CommitTransactionNTDResponse (16)
/* ns1:CommitTransactionNTDResponse */
class SOAP_CMAC _ns1__CommitTransactionNTDResponse
{
public:
	ns1__ArrayOfString *CommitTransactionNTDResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:ArrayOfString */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 16; } /* = unique id SOAP_TYPE__ns1__CommitTransactionNTDResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _ns1__CommitTransactionNTDResponse() { _ns1__CommitTransactionNTDResponse::soap_default(NULL); }
	virtual ~_ns1__CommitTransactionNTDResponse() { }
};
#endif

#ifndef SOAP_TYPE___ns2__CheckTransaction
#define SOAP_TYPE___ns2__CheckTransaction (25)
/* Operation wrapper: */
struct __ns2__CheckTransaction
{
public:
	_ns1__CheckTransaction *ns1__CheckTransaction;	/* optional element of type ns1:CheckTransaction */
};
#endif

#ifndef SOAP_TYPE___ns2__CheckTransactionWithCurrency
#define SOAP_TYPE___ns2__CheckTransactionWithCurrency (29)
/* Operation wrapper: */
struct __ns2__CheckTransactionWithCurrency
{
public:
	_ns1__CheckTransactionWithCurrency *ns1__CheckTransactionWithCurrency;	/* optional element of type ns1:CheckTransactionWithCurrency */
};
#endif

#ifndef SOAP_TYPE___ns2__CommitTransaction
#define SOAP_TYPE___ns2__CommitTransaction (33)
/* Operation wrapper: */
struct __ns2__CommitTransaction
{
public:
	_ns1__CommitTransaction *ns1__CommitTransaction;	/* optional element of type ns1:CommitTransaction */
};
#endif

#ifndef SOAP_TYPE___ns2__CommitTransactionNTD
#define SOAP_TYPE___ns2__CommitTransactionNTD (37)
/* Operation wrapper: */
struct __ns2__CommitTransactionNTD
{
public:
	_ns1__CommitTransactionNTD *ns1__CommitTransactionNTD;	/* optional element of type ns1:CommitTransactionNTD */
};
#endif

#ifndef SOAP_TYPE___ns3__CheckTransaction
#define SOAP_TYPE___ns3__CheckTransaction (39)
/* Operation wrapper: */
struct __ns3__CheckTransaction
{
public:
	_ns1__CheckTransaction *ns1__CheckTransaction;	/* optional element of type ns1:CheckTransaction */
};
#endif

#ifndef SOAP_TYPE___ns3__CheckTransactionWithCurrency
#define SOAP_TYPE___ns3__CheckTransactionWithCurrency (41)
/* Operation wrapper: */
struct __ns3__CheckTransactionWithCurrency
{
public:
	_ns1__CheckTransactionWithCurrency *ns1__CheckTransactionWithCurrency;	/* optional element of type ns1:CheckTransactionWithCurrency */
};
#endif

#ifndef SOAP_TYPE___ns3__CommitTransaction
#define SOAP_TYPE___ns3__CommitTransaction (43)
/* Operation wrapper: */
struct __ns3__CommitTransaction
{
public:
	_ns1__CommitTransaction *ns1__CommitTransaction;	/* optional element of type ns1:CommitTransaction */
};
#endif

#ifndef SOAP_TYPE___ns3__CommitTransactionNTD
#define SOAP_TYPE___ns3__CommitTransactionNTD (45)
/* Operation wrapper: */
struct __ns3__CommitTransactionNTD
{
public:
	_ns1__CommitTransactionNTD *ns1__CommitTransactionNTD;	/* optional element of type ns1:CommitTransactionNTD */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (46)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (47)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (49)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (52)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (53)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */
