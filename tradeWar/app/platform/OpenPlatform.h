/*
 * OpenPlatform
 *
 *  Created on: 2011-5-16
 *      Author: dada
 */

#ifndef __OPENPLATFORM_H__
#define __OPENPLATFORM_H__

#include "Kernel.h"
#include "IOpenPlatform.h"

namespace OpenPlatform
{
	bool Init(const string &path);

	//获取当前平台对象
	IOpenPlatform *GetPlatform();

	//获取当前平台类型
	PlatformType GetType();

	//更新当前平台类型
	bool Reset();

	//计算平台类型
	PlatformType GetType(int pf, int platform);
}

#endif	//__OPENPLATFORM_H__
