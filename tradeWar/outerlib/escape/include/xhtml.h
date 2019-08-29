/*
 *  xhtml.h
 *  ISDWebCharacter
 *
 *  Created by Xiao Xu on 09-7-13.
 *  Copyright 2009 Tencent.. All rights reserved.
 *
 */

#ifndef _ISDWEBCHARACTER_XHTML
#define _ISDWEBCHARACTER_XHTML

#include <string>
#include "common.h"

namespace ISDWebCharacter {
	
	
	/**
	 * 是否处理HTML中的空白字符为实体
	 */
	enum htmlWhiteCharReplace {
		NOT = 0,
		HTML = 1
	};
	
	struct escapeXHTMLDefineNode {
		size_t len;
		char ta[7];
	};
	
	
	
	/**
	 * XML/HTML 实体转义
	 *     策略：
	 *         <        &lt;
	 *         >        &gt;
	 *         "        &quot;
	 *         '        &#39;       (本应该是 &apos; 无奈IE不解析...)
	 *         &        &amp;
	 * 主要用于将文本插入XML/HTML段落时，用户看到的是原文
	 */
	std::string escapeXHTMLEntity(const std::string& sourceStr, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
	int escapeXHTMLEntity(std::string& resultStr, const std::string& sourceStr, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
	int escapeXHTMLEntity(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
	
	/**
	 * 反方向还原
	 *
	 */
	std::string unescapeXHTMLEntity(const std::string& sourceStr, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
	int unescapeXHTMLEntity(std::string& resultStr, const std::string& sourceStr, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
	int unescapeXHTMLEntity(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, htmlWhiteCharReplace procSpace = NOT, charsetCheck level = NO_CHECK);
};

#endif
