/*
 *  uri.cpp
 *  ISDWebCharacter
 *
 *  Created by Xiao Xu on 09-7-13.
 *  Copyright 2009 Tencent.. All rights reserved.
 *
 */

#include <string.h>
#include "uri.h"



std::string ISDWebCharacter::encodeURIValue(const std::string& sourceStr){
	std::string re;
	
	encodeURIValue(re, sourceStr);
	
	return re;
}

int ISDWebCharacter::encodeURIValue(std::string& resultStr, const std::string& sourceStr){
	
	size_t len = sourceStr.size() * 3 + 10;
	char * buff = new char[len];
	
	int res = encodeURIValue(buff, sourceStr.c_str(), len);
	resultStr = buff;
	
	delete [] buff;
	
	return res;
}



int ISDWebCharacter::encodeURIValue(char * resultBuffer, const char * sourceStr, size_t resultBufferSize){
	if(sourceStr == NULL || resultBuffer == NULL){
		return ERR_NULL_PARAMS;
	}
	
	register size_t blen = resultBufferSize - 1,
		c = 0;
	register unsigned char * p = (unsigned char *)sourceStr;
	register encodeURIDefineNode * tmp = NULL;
	int res = OK;
	
	
	while(*p != '\0'){
		tmp = &URIEncodeMap[*p];
		if(c + (*tmp).len > blen){
			res = ERR_BUFFER_TOO_SMALL;
			break;
		}else{
			memcpy(resultBuffer + c, (*tmp).ta, (*tmp).len);
			c += (*tmp).len;
		}
		++p;
	}
	*(resultBuffer + c) = '\0';
	
	return res;
}

std::string ISDWebCharacter::decodeURIValue(const std::string& sourceStr){
	std::string re;
	
	decodeURIValue(re, sourceStr);
	
	return re;
}

int ISDWebCharacter::decodeURIValue(std::string& resultStr, const std::string& sourceStr){

	size_t len = sourceStr.size() + 10;
	char * buff = new char[len];
	
	int res = decodeURIValue(buff, sourceStr.c_str(), len);
	resultStr = buff;
	
	delete [] buff;
	
	return res;
}


int ISDWebCharacter::decodeURIValue(char * resultBuffer, const char * sourceStr, size_t resultBufferSize){
	if(sourceStr == NULL || resultBuffer == NULL){
		return ERR_NULL_PARAMS;
	}
	
	register size_t blen = resultBufferSize - 1,
		c = 0;
	
	register unsigned char * p = (unsigned char *)sourceStr;
	register decodeURIDefineNode * tmph = NULL;
	register decodeURIDefineNode * tmpl = NULL;
	int res = OK;
	
	while(*p != '\0'){
		if(c + 1 > blen){
			res = ERR_BUFFER_TOO_SMALL;
			break;
		}
		
		if(('%' == *p) && isxdigit(*(p + 1)) && isxdigit(*(p + 2))){
			tmph = &URIDecodeMap[*(p + 1)];
			tmpl = &URIDecodeMap[*(p + 2)];
			*(resultBuffer + c) = (*tmph).highVal + (*tmpl).lowVal;
			p += 3;
		}else{
			*(resultBuffer + c) = (*p == '+') ? 0x20 : *p;
			++p;
		}
		
		c += 1;
	}
	*(resultBuffer + c) = '\0';
	
	return res;
}


