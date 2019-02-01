#include "LogicInc.h"
#include <curl/curl.h>
#include <fstream>
#include <cstdlib>

using namespace std;

int stringsplit(string data, string delim, vector<string> &vctstr);
int StringReplace(string& sData, const string& sSrc, const string& sDst);
int unencode(char *src, char *last, char *dest);

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int len = strlen((char *)ptr);
    if (len > 999999) 
        return 0;

    ((std::string*)stream)->append((char*)ptr, size * nmemb); 

    return size*nmemb;
}

int login(string &openid, string &serverip, unsigned port, unsigned &uid, string &strskey, unsigned &lasttime, unsigned &seqid, unsigned &ts, string &errmsg)
{
    //模拟登陆，就为了获得skey,lasttime,seqid，以及ts
    Json::Value loginpost;
    loginpost["spreadid"] = "null";
    loginpost["ip"] = "null";
    loginpost["pf"] = "";
    loginpost["version"] = "13.09.23";
    loginpost["openid"] = openid;
    loginpost["via"] = "test";
    loginpost["uid"] = 0;
    loginpost["app_appbitmap"] = 0;
    loginpost["openkey"] = "";
    loginpost["ts"] = 0;
    loginpost["iopenid"] = "";
    
    Json::FastWriter writer;
	string data = writer.write(loginpost);
    
    string param ;
    param = "h=fbb080c18d9217d764d0d5927b9353ff&hn=6668496&data=";
    param += data;
    
    char szUrl[100] = {0};
    sprintf(szUrl, "http://%s:%u/cgi/login?ts=0&", serverip.c_str(), port);
    
    CURL *curl;
    CURLcode  res;
    
    curl = curl_easy_init();//对curl进行初始化

    string str;
    
    curl_easy_setopt(curl, CURLOPT_URL, szUrl); //设置访问地址
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 12);//设置超时时间
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//设置写数据的函数
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());    // 指定post内容
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);//设置写数据的变量
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); 
    
    res = curl_easy_perform(curl);//执行登录
    
    if (CURLE_OK != res)
    {
        errmsg = "登录失败";
        return 1;
    }
    
    Json::Reader reader;
    Json::Value value;
    
    string sdata(str);
    
    //判断sdata是否是正常的json格式的数据, {}
    
    if (sdata[0] != '{' || sdata[sdata.size() - 1] != '}')
    {
        errmsg = "登录失败，错误原因:";
        errmsg += sdata;
        
        return 2;
    }
    
    //int len = sdata.size();
    
	if( !reader.parse( sdata, value ) )
	{
		errmsg="解析json失败";

        return 5;
	}
  
    if(!Json::GetString(value, "skey", strskey)
    || !Json::GetUInt(value, "lasttime", lasttime)
    || !Json::GetUInt(value, "lastseq", seqid)
    || !Json::GetUInt(value, "server_ts", ts)
    || !Json::GetUInt(value, "uid", uid))
    {
        errmsg="获取必要参数失败";

        return 6;
    }

    return 0;
}

int send_html_end()
{
    FCGI_printf("</BODY></HTML>\n");
    
    return 0;
}

int send_html_start()
{
    FCGI_printf("Content-type: text/html\r\n\r\n\n");
    
    FCGI_printf("<HTML><HEAD>\n"
        "<TITLE>Simulation Post Result</TITLE>\n"
        "</HEAD>");
        
    FCGI_printf("<meta content=\"text/html; charset=UTF-8\" http-equiv=\"Content-Type\">");
    FCGI_printf("<BODY>\n");
    
    return 0;
}

int main()
{
    if(!Kernel::Init())	
	{	
		fatal_log("[Kernel::Init fail][cgi=%s]", "sendurl");	
		return -1;	
	}	
    
    while(FCGI_Accept() >= 0)
    {   
        send_html_start();
        
        int len;
        char *lenstr, poststr[1000];
        
        lenstr = getenv("CONTENT_LENGTH");

        if (NULL == lenstr)
        {
            FCGI_printf("传递的参数错误!");
            send_html_end();
            continue;
        }
        
        len = atoi(lenstr);
 
        memset(poststr, 0, sizeof(poststr));
        
        FCGI_fread( poststr, len+1, 1, FCGI_stdin );

        //cout<<"上报的内容长度是:"<<len<<"内容是:"<<poststr<<"[]"<<endl;
        
        vector<string> vctstr;
        map<string, string> mapParam;
        
        stringsplit(poststr, "&", vctstr);
        string key;
        string val;
        char dst[1000] = {0};

        //FCGI_printf("长度是:%d,内容是:%s<br/>", len, poststr);
        
        for (vector<string>::iterator itItem = vctstr.begin(); itItem != vctstr.end(); ++itItem)
        {
            string::size_type cpos = itItem->find("=");
            //cout<<"原始内容是:"<<*itItem<<"[]<br/>"<<endl;
            if (cpos != string::npos)
            {
                key = itItem->substr(0, cpos);
                val = itItem->substr(cpos + 1);
            }
            else
            {
                continue;
            }

            
            //cout<<"first:key:"<<key<<",value:"<<val<<"||\n<br/>"<<endl;
            
            //FCGI_printf("first:key:%s,value:%s,\n", key.c_str(), val.c_str());
            StringReplace(key, "+", " ");
            StringReplace(val, "+", " ");

            {
                char * ptemp = const_cast<char*> (key.c_str());
                memset(dst, 0, sizeof(dst));
                unencode(ptemp, ptemp+key.size(), dst);
                key = dst;
                //cout<<key.size()<<"\n";
                //key[key.size()-1] = '\0';
                //cout<<key.size()<<"\n"<<endl;
            }
            
            {
                char * ptemp = const_cast<char*> (val.c_str());
                memset(dst, 0, sizeof(dst));
                unencode(ptemp, ptemp+val.size(), dst);
                val = dst;
                //cout<<val.size()<<"\n";
                //val[val.size()-1] = '\0';
                //cout<<val.size()<<"\n"<<endl;
            }
            
            //cout<<"key:"<<key<<",value:"<<val<<","<<"\n<br/>"<<endl;
            
            //FCGI_printf("key:%s,value:%s,<br/>", key.c_str(), val.c_str());
            mapParam.insert(make_pair(key, val));
        }
        
        //从map中取出key。包括hn,h,uid,cgi
        string cgival = mapParam["cgiaddr"];
        string openid = mapParam["openid"];
        string actval = mapParam["action"];
        string dataval = mapParam["data"];
           
        //判断传过来的参数是否合理
        if (cgival.empty() || openid.empty() || actval.empty())
        {
            FCGI_printf("传递的参数错误!每个参数都必填");
            send_html_end();
            continue;   
        }
        
        //获得服务器ip
        int fpos = cgival.find_first_of(':');  //第一个: //即http://
        int spos = cgival.find(':', fpos+1);   //第二个: 即ip:port
        unsigned port = 80;   //默认80端口
        
        if (spos == string::npos)  //如果不存在端口
        {
            spos = cgival.find('/', fpos+3);
        }
        else
        {
            //存在端口，则取出来
            int nextpos = cgival.find('/', fpos+3);
            port = atoi(cgival.substr(spos+1, nextpos - spos - 1).c_str());
        }
        string serverip = cgival.substr(fpos+3, spos - fpos - 3);
        
        //模拟发送登录包
        string errmsg;
        unsigned uid = 0;
        string skey;
        unsigned lasttime = 0;
        unsigned seqid = 0;
        unsigned ts = 0;
        string strskey;
        int ret = login(openid, serverip, port, uid, strskey, lasttime, seqid, ts, errmsg);
        if (0 != ret)
        {
            FCGI_printf(errmsg.c_str());
        }
        else
        {
            //但是seqid的值，要在原来的基础上加1
            seqid += 1;
            
            //cout<<"result:"<<cgival<<","<<uidval<<","<<hnval<<","<<hval<<", "<<actval<<","<<endl;
            //应去除data前后的{}符号
            if (!dataval.empty() && dataval[0] == '{' && dataval[dataval.size() - 1] == '}')
            {
                dataval = dataval.substr(1, dataval.size() - 2);   //去掉头尾的{}符号
            }
            string allparam = "h=67da41d3deb4e6bdaa3a61afb23e135b&hn=133289039&data={\"version\":\"13.09.23\",\"seqid\":" + CTrans::UTOS(seqid)
            				+ ",\"lastime\":" + CTrans::UTOS(lasttime)
            				+ ",\"ts\":" + CTrans::UTOS(ts)
            				+ ",\"uid\":" + CTrans::UTOS(uid)
							+ ",\"action\":\"" + actval;
            if(dataval.empty())
            	allparam += "\"}";
            else
            	allparam += "\"," + dataval + "}";
            string url= cgival + "?ts=" + CTrans::UTOS(ts) + "&skey=" + strskey + "&uid=" + CTrans::UTOS(uid);
            string res;
            FCGI_printf("url=%s<br/>data=%s<br/>", url.c_str(), allparam.c_str());
            if(Network::HttpPostRequest(res,url,allparam))
                FCGI_printf("res=%s", res.c_str());
            else
                FCGI_printf("send error!");
        }

        send_html_end();
    }
   
    return 0;
}

int stringsplit(string sData, string sDelim, vector<string> &vItems)
{
	vItems.clear();

	string::size_type bpos = 0;
	string::size_type epos = 0;
	string::size_type nlen = sDelim.size();
    
	while ((epos=sData.find(sDelim, epos)) != string::npos)
	{
		vItems.push_back(sData.substr(bpos, epos-bpos));
		epos += nlen;
		bpos = epos;
	}

	vItems.push_back(sData.substr(bpos, sData.size()-bpos));
    
    return 0;
}

int StringReplace(string& sData, const string& sSrc, const string& sDst)
{
	string::size_type pos = 0;
	string::size_type slen = sSrc.size();
	string::size_type dlen = sDst.size();
	while ((pos=sData.find(sSrc, pos)) != string::npos)
	{
		sData.replace(pos, slen, sDst);
		pos += dlen;
	}

	return 0;
}

int unencode(char *src, char *last, char *dest)
{
    for(; src != last; src++, dest++)
    {
        if(*src == '+')
        {
            *dest = ' ';
        }
        else if(*src == '%')
        {
             int code;
             //取两位十六进制，写入到code中。
             if(sscanf(src+1, "%2x", &code) != 1) code = '?';
             *dest = code;
             src +=2; 
        }     
        else
        {
            *dest = *src;
        }
    }
    
    //*dest = '\n';
    *dest = '\0';
    
    return 0;
}
