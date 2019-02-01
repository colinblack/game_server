/*
 *  str.h
 *  ISDWebCharacter
 *
 *  Created by Xiao Xu on 09-7-13.
 *  Copyright 2009 Tencent.. All rights reserved.
 *
 */

#ifndef _ISDWEBCHARACTER_STR
#define _ISDWEBCHARACTER_STR

#include <string>
#include "common.h"

namespace ISDWebCharacter {

	struct escapeCStringDefineNode {
		size_t len;
		char ta[3];
	};
	
	/**
	 * 主要用于将用户数据封入字符串常量(主要是JSON封装使用)
	 * 由于javascript string 于 C/C++ string 有完全相同的转义关键字，因此称为CString
	 *     策略：
	 *         \        \\
	 *         "        \"
	 *         '        \'
	 *         (0x0A)   \n
	 *         (0x0D)   (丢弃)
	 *
	 */
	std::string escapeCString(const std::string& sourceStr, charsetCheck level = NO_CHECK);
	int escapeCString(std::string& resultStr, const std::string& sourceStr, charsetCheck level = NO_CHECK);
	int escapeCString(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, charsetCheck level = NO_CHECK);
	/**
	 * 反向
	 *
	 */
	std::string unescapeCString(const std::string& sourceStr, charsetCheck level = NO_CHECK);
	int unescapeCString(std::string& resultStr, const std::string& sourceStr, charsetCheck level = NO_CHECK);
	int unescapeCString(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, charsetCheck level = NO_CHECK);
	
	static escapeCStringDefineNode CStringEscapeMap[128] = {
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{2,"\\t"},
	{2,"\\n"},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{0,0},
	{1," "},
	{1,"!"},
	{2,"\\\""},
	{1,"#"},
	{1,"$"},
	{1,"%"},
	{1,"&"},
	{2,"\\\'"},
	{1,"("},
	{1,")"},
	{1,"*"},
	{1,"+"},
	{1,","},
	{1,"-"},
	{1,"."},
	{1,"/"},
	{1,"0"},
	{1,"1"},
	{1,"2"},
	{1,"3"},
	{1,"4"},
	{1,"5"},
	{1,"6"},
	{1,"7"},
	{1,"8"},
	{1,"9"},
	{1,":"},
	{1,";"},
	{1,"<"},
	{1,"="},
	{1,">"},
	{1,"?"},
	{1,"@"},
	{1,"A"},
	{1,"B"},
	{1,"C"},
	{1,"D"},
	{1,"E"},
	{1,"F"},
	{1,"G"},
	{1,"H"},
	{1,"I"},
	{1,"J"},
	{1,"K"},
	{1,"L"},
	{1,"M"},
	{1,"N"},
	{1,"O"},
	{1,"P"},
	{1,"Q"},
	{1,"R"},
	{1,"S"},
	{1,"T"},
	{1,"U"},
	{1,"V"},
	{1,"W"},
	{1,"X"},
	{1,"Y"},
	{1,"Z"},
	{1,"["},
	{2,"\\\\"},
	{1,"]"},
	{1,"^"},
	{1,"_"},
	{1,"`"},
	{1,"a"},
	{1,"b"},
	{1,"c"},
	{1,"d"},
	{1,"e"},
	{1,"f"},
	{1,"g"},
	{1,"h"},
	{1,"i"},
	{1,"j"},
	{1,"k"},
	{1,"l"},
	{1,"m"},
	{1,"n"},
	{1,"o"},
	{1,"p"},
	{1,"q"},
	{1,"r"},
	{1,"s"},
	{1,"t"},
	{1,"u"},
	{1,"v"},
	{1,"w"},
	{1,"x"},
	{1,"y"},
	{1,"z"},
	{1,"{"},
	{1,"|"},
	{1,"}"},
	{1,"~"},
	{1,"\x7F"}
	
	};
	
};

#endif