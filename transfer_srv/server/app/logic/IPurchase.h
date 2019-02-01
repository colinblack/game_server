#ifndef __I_PURCHASE_H__
#define __I_PURCHASE_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

class IPurchase
{
public:
	static IPurchase *GetInstance();

	virtual int Purchase(unsigned int uid, short itemId, int count, int price, int cost,
			const string &meta, const string &itemUrl, vector<string> &out) = 0;

	virtual int DeliverGood(unsigned int uid, const map<string, string> &params, vector<string> &out) = 0;

	const string& GetErrMsg() const
	{
		return m_errMsg;
	}

private:
	static IPurchase *g_pPurchase;

protected:
	string m_errMsg;
};

#endif
