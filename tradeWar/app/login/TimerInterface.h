/*
 * TimerInterface.h
 *
 *  Created on: 2015-9-14
 *      Author: Administrator
 */

#ifndef TIMERINTERFACE_H_
#define TIMERINTERFACE_H_

class ITimerInterface{
public:
	virtual ~ITimerInterface(){}
	virtual bool onComplelete(uint32_t type) = 0;
};


#endif /* TIMERINTERFACE_H_ */
