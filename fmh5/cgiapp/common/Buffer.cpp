/*
 * Buffer.cpp
 *
 *  Created on: 2012-2-8
 *      Author: dada
 */

#include "Buffer.h"

uint32_t IBuffer::GetFreeCapacity() const
{
	return GetCapacity() - GetSize();
}

