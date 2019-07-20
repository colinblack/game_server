
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include "mathematics.h"

int CMath::Random()
{
	struct _RS
	{
		static int Init()
		{
			timeval _tv;
			gettimeofday(&_tv, NULL);
			srand((_tv.tv_sec)^(_tv.tv_usec<<4));
			return 0;
		}
	};
	static int iRS = _RS::Init();
	return (iRS = rand());
}

int CMath::RandomInt(int nMax)
{
    return (int)(double(nMax)*CMath::Random()/(RAND_MAX+1.0));
}

int CMath::RoundInt(int nData, int nBits)
{
	if (nBits<=0)
	{
		return nData;
	}
	
	int nMul = 1;

	for (int iIndex=1; iIndex<nBits; ++iIndex)
	{
		nMul *= 10;
	}

	nData += nMul * ((nData>=0) ? 5 : -5);
	nMul  *= 10;

	return (nData/nMul*nMul);
}

int CMath::RoundInt(double dData, int nBits)
{
	double dPown = pow(10, nBits);
	return int(dPown*floor(0.5+dData/dPown));
}

double CMath::RoundDouble(double dData, int nBits)
{
	double dPown = pow(10, nBits);
	return (dPown*floor(0.5+dData/dPown));
}

