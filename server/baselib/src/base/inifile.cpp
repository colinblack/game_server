#include "inifile.h"
struct analyzeini{
	std::string strsect;
    strMap *pmap;
    analyzeini(strMap & strmap):pmap(&strmap){}
    void operator()( const std::string & strini)
    {
        unsigned int first =strini.find('[');
        unsigned int last = strini.rfind(']');
        if( first != std::string::npos && last != std::string::npos && first != last+1)
        {
            strsect = strini.substr(first+1,last-first-1);
            return ;
        }
        if(strsect.empty())return ;
        if((first=strini.find('='))== std::string::npos)return ;
		std::string strtmp1= strini.substr(0,first);
		std::string strtmp2=strini.substr(first+1,std::string::npos);
		first= strtmp1.find_first_not_of(" \t");
		last = strtmp1.find_last_not_of(" \t");
		if(first == std::string::npos || last == std::string::npos) return ;
		std::string strkey = strtmp1.substr(first, last-first+1);
		first = strtmp2.find_first_not_of(" \t");
		if(((last = strtmp2.find("\t#", first )) != std::string::npos) ||
			((last = strtmp2.find(" #", first )) != std::string::npos) ||
			((last = strtmp2.find("\t//", first )) != std::string::npos)||
			((last = strtmp2.find(" //", first )) != std::string::npos))
		{
			strtmp2 = strtmp2.substr(0, last-first);
		}
		last = strtmp2.find_last_not_of(" \t");
		if(first == std::string::npos || last == std::string::npos)return ;
		std::string value = strtmp2.substr(first, last-first+1);
		std::string mapkey = strsect + MIDDLESTRING;
		mapkey += strkey;
		(*pmap)[mapkey]=value;
		return ;
	}
};

int IniFile::open(std::string pinipath)
{
	 return do_open(pinipath.c_str());
}
int IniFile::do_open(std::string pinipath)
{
	std::ifstream fin(pinipath.c_str());
	if(fin.fail())return -1;
	std::vector<std::string> strvect;
	while(!fin.eof())
	{
		std::string inbuf;
		getline(fin, inbuf,'\n');
		strvect.push_back(inbuf);
	}
	if(strvect.empty())return -2;
	for_each(strvect.begin(), strvect.end(), analyzeini(c_inimap));
	return (c_inimap.empty() ? -3 : 0);
}

std::string IniFile::read(std::string psect, std::string pkey)
{
	std::string mapkey = psect;
	mapkey += MIDDLESTRING;
	mapkey += pkey;
	strMapIt it = c_inimap.find(mapkey);
	if(it == c_inimap.end())return "";
	else
		return it->second;
}


