/*
 * LogicDouble11.h
 *
 *  Created on: 2015-10-29
 *      Author: dawx5fsd
 */

#ifndef LOGICDOUBLE11_H_
#define LOGICDOUBLE11_H_


#include "LogicInc.h"


class CLogicDouble11
{
public:

	int GetRemainCount(Json::Value &rcnt, bool allserver);
	int BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt, Json::Value &rcnt, bool allserver);

};



#endif /* LOGICDOUBLE11_H_ */
