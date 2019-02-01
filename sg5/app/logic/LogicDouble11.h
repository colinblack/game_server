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

	int GetRemainCount(Json::Value &rcnt);
	int BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt);

};



#endif /* LOGICDOUBLE11_H_ */
