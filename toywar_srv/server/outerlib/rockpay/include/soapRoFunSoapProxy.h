/* soapRoFunSoapProxy.h
   Generated by gSOAP 2.8.3 from pockpay.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapRoFunSoapProxy_H
#define soapRoFunSoapProxy_H
#include "soapH.h"

class SOAP_CMAC RoFunSoapProxy : public soap
{ public:
	/// Endpoint URL of service 'RoFunSoapProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	RoFunSoapProxy();
	/// Constructor with copy of another engine state
	RoFunSoapProxy(const struct soap&);
	/// Constructor with endpoint URL
	RoFunSoapProxy(const char *url);
	/// Constructor with engine input+output mode control
	RoFunSoapProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	RoFunSoapProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	RoFunSoapProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~RoFunSoapProxy();
	/// Initializer used by constructors
	virtual	void RoFunSoapProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Force close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'CheckTransaction' (returns error code or SOAP_OK)
	virtual	int CheckTransaction(_ns1__CheckTransaction *ns1__CheckTransaction, _ns1__CheckTransactionResponse *ns1__CheckTransactionResponse) { return CheckTransaction(NULL, NULL, ns1__CheckTransaction, ns1__CheckTransactionResponse); }
	virtual	int CheckTransaction(const char *endpoint, const char *soap_action, _ns1__CheckTransaction *ns1__CheckTransaction, _ns1__CheckTransactionResponse *ns1__CheckTransactionResponse);

	/// Web service operation 'CheckTransactionWithCurrency' (returns error code or SOAP_OK)
	virtual	int CheckTransactionWithCurrency(_ns1__CheckTransactionWithCurrency *ns1__CheckTransactionWithCurrency, _ns1__CheckTransactionWithCurrencyResponse *ns1__CheckTransactionWithCurrencyResponse) { return CheckTransactionWithCurrency(NULL, NULL, ns1__CheckTransactionWithCurrency, ns1__CheckTransactionWithCurrencyResponse); }
	virtual	int CheckTransactionWithCurrency(const char *endpoint, const char *soap_action, _ns1__CheckTransactionWithCurrency *ns1__CheckTransactionWithCurrency, _ns1__CheckTransactionWithCurrencyResponse *ns1__CheckTransactionWithCurrencyResponse);

	/// Web service operation 'CommitTransaction' (returns error code or SOAP_OK)
	virtual	int CommitTransaction(_ns1__CommitTransaction *ns1__CommitTransaction, _ns1__CommitTransactionResponse *ns1__CommitTransactionResponse) { return CommitTransaction(NULL, NULL, ns1__CommitTransaction, ns1__CommitTransactionResponse); }
	virtual	int CommitTransaction(const char *endpoint, const char *soap_action, _ns1__CommitTransaction *ns1__CommitTransaction, _ns1__CommitTransactionResponse *ns1__CommitTransactionResponse);

	/// Web service operation 'CommitTransactionNTD' (returns error code or SOAP_OK)
	virtual	int CommitTransactionNTD(_ns1__CommitTransactionNTD *ns1__CommitTransactionNTD, _ns1__CommitTransactionNTDResponse *ns1__CommitTransactionNTDResponse) { return CommitTransactionNTD(NULL, NULL, ns1__CommitTransactionNTD, ns1__CommitTransactionNTDResponse); }
	virtual	int CommitTransactionNTD(const char *endpoint, const char *soap_action, _ns1__CommitTransactionNTD *ns1__CommitTransactionNTD, _ns1__CommitTransactionNTDResponse *ns1__CommitTransactionNTDResponse);
};
#endif