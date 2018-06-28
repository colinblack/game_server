/*
 * ConfigWrap.h
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#ifndef USERCFGWRAP_H_
#define USERCFGWRAP_H_

#include "DataInc.h"



class ActivityCfgWrap
{
public:
	ActivityCfgWrap();

	const User::ActivityItem& GetItem(unsigned id) const;
private:
	const User::Activity& cfg_;
};


#endif /* USERCFGWRAP_H_ */
