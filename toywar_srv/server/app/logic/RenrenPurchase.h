#ifndef __LOGIC_PURCHASE_H__
#define __LOGIC_PURCHASE_H__

#include "IPurchase.h"

class CRenrenPurchase : public IPurchase
{
public:
	virtual int Purchase(unsigned int uid, short itemId, int count, int price, int cost,
				const string &meta, const string &itemUrl, vector<string> &out);

	virtual int DeliverGood(unsigned int uid, const map<string, string> &params, vector<string> &out);
};

#endif
