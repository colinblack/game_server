/*
 * DebugUtil.cpp
 *
 *  Created on: 2012-5-15
 *      Author: dada
 */

#include "DebugUtil.h"
#include <execinfo.h>

#define MAX_STACK_DEPTH	10

string Debug::GetStack()
{
	void *stack[MAX_STACK_DEPTH];
	size_t depth = backtrace(stack, MAX_STACK_DEPTH);
	char **pStrings = backtrace_symbols(stack, depth);
	string sStack;
	if(pStrings == NULL)
	{
		return sStack;
	}
	for(size_t i = 1; i < depth; i++)
	{
		sStack.append(pStrings[i]);
		sStack.append("\r\n");
	}
	free(pStrings);
	return sStack;
}
