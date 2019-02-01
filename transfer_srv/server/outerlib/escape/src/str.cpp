/*
 *  str.cpp
 *  ISDWebCharacter
 *
 *  Created by Xiao Xu on 09-7-14.
 *  Copyright 2009 Tencent.. All rights reserved.
 *
 */
#include <string.h>
#include "str.h"

std::string ISDWebCharacter::escapeCString(const std::string& sourceStr, charsetCheck level){
	std::string re;
	
	escapeCString(re, sourceStr, level);
	
	return re;
}

int ISDWebCharacter::escapeCString(std::string& resultStr, const std::string& sourceStr, charsetCheck level){
	size_t len = sourceStr.size() * 2 + 10;
	char * buff = new char[len];
	
	int res = escapeCString(buff, sourceStr.c_str(), len, level);
	resultStr = buff;
	
	delete [] buff;
	
	return res;
	
}



int ISDWebCharacter::escapeCString(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, charsetCheck level){
	if(sourceStr == NULL || resultBuffer == NULL){
		return ERR_NULL_PARAMS;
	}
	
	register size_t blen = resultBufferSize - 1,
		c = 0;
	register unsigned char * p = (unsigned char *)sourceStr;
	register escapeCStringDefineNode * tmp = NULL;
	int res = OK;
	
	if(level == NO_CHECK){//不做编码检查	
		while(*p != '\0'){
			if(*p < 0x80){
				tmp = &CStringEscapeMap[*p];
				if((*tmp).len < 1){
				}else if(c + (*tmp).len > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}else{
					memcpy(resultBuffer + c, (*tmp).ta, (*tmp).len);
					c += (*tmp).len;
				}
			}else{
				if(c + 1 > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}
				*(resultBuffer + c) = *p;
				++c;
			}
			++p;
		}
	}else if(level == UTF8_CHECK){//不做编码检查	
		while(*p != '\0'){
			if(*p < 0x80){
				tmp = &CStringEscapeMap[*p];
				if((*tmp).len < 1){
				}else if(c + (*tmp).len > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}else{
					memcpy(resultBuffer + c, (*tmp).ta, (*tmp).len);
					c += (*tmp).len;
				}
			}else{
				if(c + 1 > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}

				if((*p >> 5) == 0x6){//可能的 2Bytes 序列
					if((*(p+1) >> 6) == 0x2){//正是
						if(c + 2 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 2);
						p += 2;
						c += 2;
						continue;
					}
				}else if((*p >> 4) == 0xE){//可能的 3Bytes 序列
					if(((*(p+1) >> 6) == 0x2) && ((*(p+2) >> 6) == 0x2)){//正是
						if(c + 3 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 3);
						p += 3;
						c += 3;
						continue;
					}
				}else if((*p >> 3) == 0x1E){//可能的 4Bytes 序列
					if(((*(p+1) >> 6) == 0x2) && ((*(p+2) >> 6) == 0x2) && ((*(p+3) >> 6) == 0x2)){//正是
						if(c + 4 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 4);
						p += 4;
						c += 4;
						continue;
					}
				}

				*(resultBuffer + c) = '?';
				++c;
			}
			++p;
		}
	}else if(level == GBK_CHECK){//不做编码检查	
		while(*p != '\0'){
			if(*p < 0x80){
				tmp = &CStringEscapeMap[*p];
				if((*tmp).len < 1){
				}else if(c + (*tmp).len > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}else{
					memcpy(resultBuffer + c, (*tmp).ta, (*tmp).len);
					c += (*tmp).len;
				}
			}else{
				if(c + 1 > blen){
					res = ERR_BUFFER_TOO_SMALL;
					break;
				}

				if(0x80 < *p && *p < 0xFF){ // GBK level 3
					if(*(p+1) != 0x7F && 0x3F < *(p+1) && *(p+1) < 0xFF){//yes
						if(c + 2 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 2);
						p += 2;
						c += 2;
						continue;
					}
				}else if(*p == 0x80){ // 欧元符号
					*(resultBuffer + c) = 0x80;
					++p;
					++c;
					continue;
				}

				*(resultBuffer + c) = '?';
				++c;
			}
			++p;
		}
	}
	
	
	*(resultBuffer + c) = '\0';
	
	return res;
	
}


std::string ISDWebCharacter::unescapeCString(const std::string& sourceStr, charsetCheck level){
	std::string re;
	
	unescapeCString(re, sourceStr, level);
	
	return re;
}

int ISDWebCharacter::unescapeCString(std::string& resultStr, const std::string& sourceStr, charsetCheck level){
	size_t len = sourceStr.size() + 10;
	char * buff = new char[len];
	
	int res = unescapeCString(buff, sourceStr.c_str(), len, level);
	resultStr = buff;
	
	delete [] buff;
	
	return res;
}



int ISDWebCharacter::unescapeCString(char * resultBuffer, const char * sourceStr, size_t resultBufferSize, charsetCheck level){
	if(sourceStr == NULL || resultBuffer == NULL){
		return ERR_NULL_PARAMS;
	}
	register size_t blen = resultBufferSize - 1,
		c = 0;
	register unsigned char * p = (unsigned char *)sourceStr;
	int res = OK;
	
	if(level == NO_CHECK){
		while(*p != '\0'){
			if(c + 1 > blen){
				res = ERR_BUFFER_TOO_SMALL;
				break;
			}
			
			if('\\' == *p){
				if(*(p + 1) == 't'){
					*(resultBuffer + c) = '\t';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == 'n'){
					*(resultBuffer + c) = '\n';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\\'){
					*(resultBuffer + c) = '\\';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\''){
					*(resultBuffer + c) = '\'';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\"'){
					*(resultBuffer + c) = '\"';
					p += 2;
					++c;
					continue;
				}
				*(resultBuffer + c) = '\\';
			}else{
				*(resultBuffer + c) = *p;
			}
			++p;
			++c;
		}
	}else if(level == UTF8_CHECK){
		while(*p != '\0'){
			if(c + 1 > blen){
				res = ERR_BUFFER_TOO_SMALL;
				break;
			}
			
			if('\\' == *p){
				if(*(p + 1) == 't'){
					*(resultBuffer + c) = '\t';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == 'n'){
					*(resultBuffer + c) = '\n';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\\'){
					*(resultBuffer + c) = '\\';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\''){
					*(resultBuffer + c) = '\'';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\"'){
					*(resultBuffer + c) = '\"';
					p += 2;
					++c;
					continue;
				}
				*(resultBuffer + c) = '\\';
			}else{
				if(*p < 0x80){
					*(resultBuffer + c) = *p;
					++p;
					++c;
					continue;
				}else if((*p >> 5) == 0x6){//可能的 2Bytes 序列
					if((*(p+1) >> 6) == 0x2){//正是
						if(c + 2 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 2);
						p += 2;
						c += 2;
						continue;
					}
				}else if((*p >> 4) == 0xE){//可能的 3Bytes 序列
					if(((*(p+1) >> 6) == 0x2) && ((*(p+2) >> 6) == 0x2)){//正是
						if(c + 3 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 3);
						p += 3;
						c += 3;
						continue;
					}
				}else if((*p >> 3) == 0x1E){//可能的 4Bytes 序列
					if(((*(p+1) >> 6) == 0x2) && ((*(p+2) >> 6) == 0x2) && ((*(p+3) >> 6) == 0x2)){//正是
						if(c + 4 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 4);
						p += 4;
						c += 4;
						continue;
					}
				}
				*(resultBuffer + c) = '?';
			}
			++p;
			++c;
		}
	}else if(level == GBK_CHECK){
		while(*p != '\0'){
			if(c + 1 > blen){
				res = ERR_BUFFER_TOO_SMALL;
				break;
			}
			
			if('\\' == *p){
				if(*(p + 1) == 't'){
					*(resultBuffer + c) = '\t';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == 'n'){
					*(resultBuffer + c) = '\n';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\\'){
					*(resultBuffer + c) = '\\';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\''){
					*(resultBuffer + c) = '\'';
					p += 2;
					++c;
					continue;
				}
				if(*(p + 1) == '\"'){
					*(resultBuffer + c) = '\"';
					p += 2;
					++c;
					continue;
				}
				*(resultBuffer + c) = '\\';
			}else{
				if(0x80 < *p && *p < 0xFF){ // GBK level 3
					if(*(p+1) != 0x7F && 0x3F < *(p+1) && *(p+1) < 0xFF){//yes
						if(c + 2 > blen){
							res = ERR_BUFFER_TOO_SMALL;
							break;
						}
						memcpy(resultBuffer + c, p, 2);
						p += 2;
						c += 2;
						continue;
					}
				}else if(0x81 > *p){
					if(c + 1 > blen){
						res = ERR_BUFFER_TOO_SMALL;
						break;
					}
					*(resultBuffer + c) = *p;
					++p;
					++c;
					continue;
				}
				*(resultBuffer + c) = '?';
			}
			++p;
			++c;
		}
	}
	
	*(resultBuffer + c) = '\0';
	
	
	return res;
}
