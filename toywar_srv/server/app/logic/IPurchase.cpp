#include "IPurchase.h"
#include "LogicInc.h"
#include "RenrenPurchase.h"

IPurchase * IPurchase::g_pPurchase = NULL;

IPurchase * IPurchase::GetInstance()
{
	if (g_pPurchase == NULL)
	{
		if (OpenPlatform::GetType() == PT_RENREN)
		{
			g_pPurchase = new CRenrenPurchase();
		}
	}

	return g_pPurchase;
}
