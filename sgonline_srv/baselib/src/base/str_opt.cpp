#include "str_opt.h"

int StrSeparate( char* sSrc, const char* sSep, char** sStart, int iMaxNum )
{
	int iNum = 1;
	int iSepLen = strlen(sSep);

	sStart[0] = sSrc;
	while ( *sSrc )
	{
		if ( 0 != strncmp( sSrc, sSep, iSepLen ) )
		{
			sSrc++;
			continue;
		}

		*sSrc = 0;
		sSrc += iSepLen;
		sStart[iNum++] = sSrc;
		if ( iNum >= iMaxNum )
		{
			break;
		}
	}
	return iNum;
}

int StrSeparate( const char* sSrc, const char* sSep, int* n, int iMaxNum )
{
	int iNum = 1;
	int iSepLen = strlen(sSep);

	n[0] = atoi( sSrc );
	while ( *sSrc )
	{
		if ( 0 != strncmp( sSrc, sSep, iSepLen ) )
		{
			sSrc++;
			continue;
		}

		sSrc += iSepLen;
		n[iNum++] = atoi( sSrc );
		if ( iNum >= iMaxNum )
		{
			break;
		}
	}
	return iNum;
}


void StrReplace( std::string & strBig, const std::string & strsrc, const std::string &strdst )
{
	std::string::size_type pos=0;
	std::string::size_type srclen=strsrc.size();
	std::string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != std::string::npos)
	{ 
		strBig.replace(pos, srclen, strdst); 
		pos += dstlen; 
	} 
}

int StrReplace( const char* sSrc, const char* sFind, const char* sSet, char* sDst )
{
	int iTotal = 0;
	int iFindLen = strlen( sFind );
	int iSetLen = strlen( sSet );

	while ( *sSrc )
	{
		if ( 0 == memcmp( sSrc, sFind, iFindLen ) )
		{
			memcpy( sDst, sSet, iSetLen );
			sSrc += iFindLen;
			sDst += iSetLen;
			iTotal += iSetLen;
			continue;
		}

		*sDst++ = *sSrc++;
		iTotal++;
	}
	*sDst = 0;
	return iTotal;
}

int StrReplaceN(  const char* sSrc, char** ppFind, char** ppSet, int iNum, char* sDst  )
{
	int i;
	int iTotal = 0;
	int iFindLen, iSetLen;

	while ( *sSrc )
	{
		for ( i=0; i<iNum; i++ )
		{
			iFindLen = strlen( ppFind[i] );
			iSetLen = strlen( ppSet[i] );
			if ( 0 == memcmp( sSrc, ppFind[i], iFindLen ) )
			{
				memcpy( sDst, ppSet[i], iSetLen );
				sSrc += iFindLen;
				sDst += iSetLen;
				iTotal += iSetLen;
				goto replaced_continue;
			}
		}
		*sDst++ = *sSrc++;
		iTotal++;

replaced_continue:
		continue;
	}
	*sDst = 0;
	return iTotal;
}

int StrReplace( const char* sSrc, const char* sFind, const int iSet, char* sDst )
{
	char sSet[20];

	snprintf(sSet, sizeof(sSet), "%d", iSet );
	return StrReplace( sSrc, sFind, sSet, sDst );
}

char* StrTrim( char* sSrc, const char* sFilter )
{
	char FilterMap[256] = { 0 };
	char* sTail;

	/* 设置过滤表*/
	while ( *sFilter )
		FilterMap[ (*sFilter++) & 0xff ] = 1;

	/* 过滤头部*/
	while ( *sSrc && FilterMap[ *sSrc & 0xff ] )
		sSrc++;

	/* 找到尾部*/
	for ( sTail = sSrc; *sTail; sTail++ );
	sTail--;

	/* 过滤尾部*/
	while ( ( sTail != sSrc ) && FilterMap[ *sTail & 0xff ] )
		*sTail-- = 0;

	return sSrc;
}

int FileToStream(const char* sPath, std::string &data, int iMoreSize, int iHeadMoreSize)
{
	FILE* pF = fopen(sPath, "r+b");
	if (NULL == pF)
	{
		return -1;
	}

	fseek(pF, 0, SEEK_END);
	long iSize = ftell(pF);
	fseek(pF, 0, SEEK_SET);

	data.resize(iHeadMoreSize + iSize + iMoreSize);
	fread((char*)(data.data()+iHeadMoreSize), iSize, 1, pF);
	fclose(pF);
	return iSize;
}

int StreamToFile(const char* sPath, const std::string &data)
{
	FILE* pF = fopen(sPath, "w+b");
	if (NULL == pF)
	{
		return -1;
	}

	fwrite((char*)(data.data()), data.size(), 1, pF);
	fclose(pF);
	return 0;
}

string from_to( const string& src, const string& enc_from, const string& enc_to )
{
	if ( src.empty() || enc_from==enc_to )
		return src ;

	iconv_t cd = iconv_open( enc_to.c_str(), enc_from.c_str() ) ;
	char dest[1024*6]= {0} ;

	char * in = const_cast<char*>( src.c_str() ) ;
	char * out = dest ;
	size_t ileft = strlen( in ) ;
	size_t oleft = sizeof( dest ) ;
	iconv( cd, &in, &ileft, &out, &oleft ) ;
	iconv_close( cd ) ;
	return string( dest, sizeof(dest) - oleft ) ;
}

string gbk2utf8( const string& src )
{
	return from_to( src, "gbk", "utf-8" ) ;
}

string utf82gbk( const string& src )
{
	return from_to( src, "utf-8", "gbk" ) ;
}

string int2str(int n)
{
    static char buf[32];

    snprintf(buf, sizeof(buf) - 1, "%d", n);
    buf[sizeof(buf) - 1] = 0;

    return buf;
}

