/*
 * KernelUtil.h
 *
 *  Created on: 2011-5-26
 *      Author: dada
 */

#ifndef KERNELUTIL_H_
#define KERNELUTIL_H_

#include "Kernel.h"

namespace Kernel
{
	bool InitLog(const string &logName);
	bool Init(const string &configPath = APP_CONFIG_PATH);
	GameType GetGameType();
}

#define IsToywar() (Kernel::GetGameType() == GT_TOYWAR)// || OpenPlatform::GetType() == PT_TEST)
#define IsMercenary() (Kernel::GetGameType() == GT_MERCENARY)// || OpenPlatform::GetType() == PT_TEST)

#define CHECK_CALL(call)	\
	ret = call;	\
	if(ret != 0) return ret	\

#define ASSERT_CALL(call)	\
	ret = call;	\
	if(ret != 0)	\
	{	\
		error_log("[assert_call_fail][ret=%d,call=" #call "]", ret);	\
		return ret;	\
	}	\

#endif /* KERNELUTIL_H_ */
