/*
 * Big.cpp
 *
 *  Created on: 2016-6-23
 *      Author: Ralf
 */

#include "LogicInc.h"

int main(int argc, char* argv[])
{
	/*
	bool f;
	f = BigValue(-18) > BigValue(8.8);
	cout<<f<<endl;
	f = BigValue(-18) < BigValue(8.8);
	cout<<f<<endl;
	f = BigValue(-18) >= BigValue(8.8);
	cout<<f<<endl;
	f = BigValue(-18) <= BigValue(8.8);
	cout<<f<<endl;
	f = BigValue(-18) == BigValue(8.8);
	cout<<f<<endl;
	f = BigValue(-18) != BigValue(8.8);
	cout<<f<<endl;
	*/
	
	/*
	BigValue t;
	t = BigValue(18) + BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) - BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) + BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) - BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) + BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) - BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) + BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) - BigValue(-8.9);
	cout<<t.Real()<<endl;
	*/
	
	/*
	BigValue t, s(double(1) / BIG_VALUE_KEEP);
	t = BigValue(1); t -= s;
	cout<<t.Real()<<endl;
	t = BigValue(1); t += s;
	cout<<t.Real()<<endl;
	*/
	
	/*
	bool f;
	f = BigValue(0.09) > BigValue(0);
	cout<<f<<endl;
	f = BigValue(0.09) < BigValue(0);
	cout<<f<<endl;
	f = BigValue(-0.09) > BigValue(0);
	cout<<f<<endl;
	f = BigValue(-0.09) < BigValue(0);
	cout<<f<<endl;
	f = BigValue(0.09) == BigValue(0);
	cout<<f<<endl;
	f = BigValue(-0.09) == BigValue(0);
	cout<<f<<endl;
	*/
	
	/*
	BigValue t;
	t = BigValue(0.09) + BigValue(0);
	cout<<t.Real()<<endl;
	t = BigValue(0.09) - BigValue(0);
	cout<<t.Real()<<endl;
	t = BigValue(0) + BigValue(-0.09);
	cout<<t.Real()<<endl;
	t = BigValue(0) - BigValue(-0.09);
	cout<<t.Real()<<endl;
	t = BigValue(0.09) + BigValue(-0.09);
	cout<<t.Real()<<endl;
	t = BigValue(-0.09) - BigValue(-0.09);
	cout<<t.Real()<<endl;
	t = BigValue(0.09) + BigValue(-0.09);
	cout<<t.Real()<<endl;
	t = BigValue(0.09) - BigValue(0.09);
	cout<<t.Real()<<endl;
	*/
	
	/*
	BigValue t;
	t = BigValue(4) + BigValue(16);
	cout<<t.Real()<<endl;
	t = BigValue(4) * BigValue(0.05);
	cout<<t.Real()<<endl;
	t = BigValue(18) * BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) / BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) * BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(18) / BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) * BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) / BigValue(8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) * BigValue(-8.9);
	cout<<t.Real()<<endl;
	t = BigValue(-18) / BigValue(-8.9);
	cout<<t.Real()<<endl;
	*/
	
	
	BigValue a(1.2), b("23498779875649872312987563168752"), c("123319875123168789724"), d(60);
	BigValue r;
	r = b / c;	
	cout<<r.Str()<<endl;
	cout<<r.Real()<<endl;
	cout<<r.Int()<<endl;
	r = b * c;
	cout<<r.Str()<<endl;
	cout<<r.Real()<<endl;
	cout<<r.Int()<<endl;
	r = b / 1.3;	
	cout<<r.Str()<<endl;
	cout<<r.Real()<<endl;
	cout<<r.Int()<<endl;	
	r = c * 9980.3;	
	cout<<r.Str()<<endl;
	cout<<r.Real()<<endl;
	cout<<r.Int()<<endl;	

	return 0;
}


