/*
 * SystemUtil.h
 *
 *  Created on: 2012-1-31
 *      Author: dada
 */

#ifndef SYSTEMUTIL_H_
#define SYSTEMUTIL_H_

#include <Common.h>

typedef void (*SignalCallback)();

namespace System
{
	bool InitDaemon(SignalCallback sigusr1 = NULL, SignalCallback sigusr2 = NULL);
	bool IgnoreSignal(int signum);
	string GetModuleDirectory();
	bool SetCurrentDirectory(const string &path);
}

#endif /* SYSTEMUTIL_H_ */
