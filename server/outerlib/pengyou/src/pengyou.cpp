/**
 * C++ SDK for pengyou Open API
 *
 * @version 1.0.0
 * @author dev.opensns@qq.com
 * @copyright ? 2010, Tencent Corporation. All rights reserved.
 */

#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>

#include "json.h"
#include "pengyou.h"

/**
 * API(cgi)名字
 */
//#define APP_GET_USERINFO_CGINAME         "xyoapp_get_userinfo"
//#define APP_GET_RELATION_STAT            "xyoapp_get_isrelation"
//#define APP_GET_RELATION_INFO            "xyoapp_get_relationinfo"
//#define APP_GET_MULTI_INFO               "xyoapp_multi_info"
//#define APP_CHECK_APP_SETUP_STAT         "xyoapp_get_issetuped"
//#define APP_SHOW_VIP_STAT                "xyoapp_pay_showvip"
//#define APP_GET_FRIEND_EMOTION           "xyoapp_get_emotion"

#define APP_GET_USERINFO_CGINAME         "/user/info"
#define APP_GET_RELATION_STAT            "/relation/is_friend"
#define APP_GET_RELATION_INFO            "/relation/friends"
#define APP_GET_MULTI_INFO               "/user/multi_info"
#define APP_CHECK_APP_SETUP_STAT         "/user/is_setuped"
#define APP_SHOW_VIP_STAT                "/pay/is_vip"
#define APP_GET_FRIEND_EMOTION           "/user/emotion"


/**
 * API返回的响应JSON串中，各个key值的名称
 */
#define KEY_RET_CODE                     "ret"
#define KEY_ERR_MSG                      "msg"
#define KEY_NICKNAME                     "nickname"
#define KEY_GENDER                       "gender"
#define KEY_PROVINCE                     "province"
#define KEY_CITY                         "city"
#define KEY_FIGURE_URL                   "figureurl"
#define KEY_ISVIP                        "is_vip"
#define KEY_ISYEARVIP                    "is_year_vip"
#define KEY_VIP_LEVEL                    "vip_level"
#define KEY_ISFRIEND                     "isFriend"
#define KEY_OPENID                       "openid"
#define KEY_ITEMS                        "items"
#define KEY_SETUP_STAT                   "setuped"
#define KEY_CONTENT                      "content"

/*
 * 错误log信息，与错误码一一对应，见E_PY_ErrCode定义
 */
const char * CPengyou::m_ErrMsgArray[] =
{
    "Successful",
    "Illegal function parameters",
    "Get Url failure",
    "Curl library init failure",
    "Curl perform failure",
    "CGI have no response",
    "Json decode failure",
    "Api response error",
    "Unknow error"
};

CPengyou::CPengyou(QQPlatformType type,
		const string & appid,
        const string & appkey,
        const string & appname,
        const vector<string> & domainvec)
: m_type(type)
, m_Appid(appid)
, m_Appkey(appkey)
, m_Appname(appname)
, m_IpVector(domainvec)
{}

CPengyou::CPengyou(QQPlatformType type,
                 const string & appid,
                 const string & appkey,
                 const string & appname,
                 const string & domain)
: m_type(type)
, m_Appid(appid)
, m_Appkey(appkey)
, m_Appname(appname)
{
    if (! domain.empty())
    {
        m_IpVector.push_back(domain);
    }
}

/*********************CPengyou private function****************************/
inline void CPengyou::setErrorMsg(E_PY_ErrCode code)
{
    if (code < 0 || code >= E_PY_CODE_COUNT)
    {
        code = E_PY_UNKOWN_ERROR;
    }
    m_ErrMsg = m_ErrMsgArray[code];
}

inline void CPengyou::setErrorMsg(const char * msg)
{
    m_ErrMsg = msg;
}

inline void CPengyou::setErrorMsg(const string & msg)
{
    m_ErrMsg = msg;
}

#if 0
template<typename T>
inline int CPengyou::errorCode1(T & tObj, int code)
{
    if (code < 0 || code >= E_PY_CODE_COUNT)
    {
        code = E_PY_UNKOWN_ERROR;
    }
    tObj.nRet       = code;
    tObj.strMessage = m_ErrMsgArray[code];

    return -code;
}
#endif

size_t CPengyou::responesWriteCallback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string * ptrStrRes = (string *)userdata;

    unsigned long sizes = size * nmemb;
    if (!ptr)
    {
        return 0;
    }
    (*ptrStrRes).append((char *)ptr, sizes);

    return sizes;
}

int CPengyou::request(string & apires, const string & url, const string & querystr)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (! curl)
    {
        setErrorMsg(E_PY_CURL_INIT_FAIL);
        return -E_PY_CURL_INIT_FAIL;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apires);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responesWriteCallback);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, querystr.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    res = curl_easy_perform(curl);

    /** *NOTE* clearup first, then check the ret status */
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        char msg[512] = {0};
        snprintf(msg, sizeof(msg), "Curl error code:%d, msg: %s", res, curl_easy_strerror(res));
        setErrorMsg(msg);
        return -E_PY_CURL_PERFORM_FAIL;
    }

    if (apires.empty())
    {
        /** Server have no response */
        setErrorMsg(E_PY_SRV_NO_RESPONSE);
        return -E_PY_SRV_NO_RESPONSE;
    }

    return E_PY_SUC;
}

int CPengyou::getApiUrl(string & url, const string & method)
{
    if (m_IpVector.empty())
    {
        setErrorMsg(E_PY_GET_URL_FAIL);
        return -E_PY_GET_URL_FAIL;
    }

    srand(time(NULL));
    int index = rand() % m_IpVector.size();

//    if (method.find("xyoapp") != string::npos)
//    {
//        url = (m_IpVector[index] + "/cgi-bin/xyoapp/" + method + ".cgi");
//    }
//    if (method.find("qzoapp") != string::npos)
//    {
//        url = (m_IpVector[index] + "/cgi-bin/qzoapp/" + method + ".cgi");
//    }
    if(m_type == QPT_QZONE)
    {
    	url = (m_IpVector[index] + "/qzone" + method);
    }
    else if (m_type == QPT_WEIBO)
    {
    	url = (m_IpVector[index] + "/t" + method);
    }
    else
    {
    	url = (m_IpVector[index] + method);
    }
    return E_PY_SUC;
}

inline string & CPengyou::buildHttpQuery(string & querystr,
                                  const string & openid, const string & openkey)
{
    querystr.append("openid=");
    querystr.append(openid);

    querystr.append("&openkey=");
    querystr.append(openkey);

    querystr.append("&appid=");
    querystr.append(GetAppId());

    querystr.append("&appkey=");
    querystr.append(GetAppKey());

    querystr.append("&ref=");
    querystr.append(GetAppName());

    return querystr;
}

template<typename T>
int CPengyou::jsonDecode(T & value, const string & jsonstr)
{
    Json::Reader reader;
    if (!reader.parse(jsonstr, value))
    {
        setErrorMsg(reader.getFormatedErrorMessages());
        return -E_PY_JSON_DECODE_FAIL;
    }
    return E_PY_SUC;
}
/*********************End CPengyou private function**************************/

const string & CPengyou::GetErrorMessage()
{
    return m_ErrMsg;
}

int CPengyou::GetUserInfo(T_UserInfo & tUserinfo, const string & openid, const string & openkey)
{
    int ret;
    if (openid.empty() || openkey.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }

    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_GET_USERINFO_CGINAME);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret >= API_RETURE_ERROR_CODE_BASE)
    {
        /* API返回失败，则保存返回的出错信息 */
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }

    /*else*/
    /* 完全成功或部分成功，则保存返回的用户信息 */
    tUserinfo.strNickName  = value[KEY_NICKNAME].asString();
    tUserinfo.strGender    = value[KEY_GENDER].asString();
    tUserinfo.strProvince  = value[KEY_PROVINCE].asString();
    tUserinfo.strCity      = value[KEY_CITY].asString();
    tUserinfo.strFigureUrl = value[KEY_FIGURE_URL].asString();
    tUserinfo.bIsVip       = value[KEY_ISVIP].asBool();
    tUserinfo.bIsYearVip   = value[KEY_ISYEARVIP].asBool();
    tUserinfo.nVipLevel    = value.get(KEY_VIP_LEVEL, 0).asInt();

    return E_PY_SUC;
}

int CPengyou::IsFriend(T_RelationStat & tRelationSt,
                      const string & openid, const string & openkey,
                      const string & fopenid)
{
    int ret;
    if (openid.empty() || openkey.empty() || fopenid.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }
    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_GET_RELATION_STAT);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);
    strQuery.append("&fopenid=");
    strQuery.append(fopenid);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret)
    {
        /** 非0表明该API执行有错，则保存返回的错误信息 */
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }
    else
    {
        tRelationSt.nIsFriend  = value[KEY_ISFRIEND].asInt();
    }

    return E_PY_SUC;
}

int CPengyou::GetFriendList(T_RelationInfo & tRelationInfo,
                           const string & openid, const string & openkey,
                           int nInfoDetails, int nAppStat, int nPage)
{
    int ret;
    if (openid.empty() || openkey.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }
    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_GET_RELATION_INFO);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);

    /** 是否需要获得详细信息("1"-yes; "0"-no) */
    strQuery.append("&infoed=");
    strQuery.append((nInfoDetails) ? "1" : "0");

    /** 好友应用安装类型("-1"-没安装; "1"-已安装的; "0"-不作区分) */
    strQuery.append("&apped=");
    strQuery.append(((nAppStat) ? ((nAppStat<0) ? "-1" : "1") : "0"));

    /** 指定页码-即请求指定页面的好友列表，0或不传表示全部好友 */
    char pageBuf[32] = {0};
    snprintf(pageBuf, sizeof(pageBuf), "&page=%d", nPage);
    strQuery.append(pageBuf);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret >= API_RETURE_ERROR_CODE_BASE)
    {
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }

    /* else */
    /** 保存请求得到的数据 */
    const Json::Value item = value[KEY_ITEMS];
    for (unsigned int i=0; i<item.size(); ++i)
    {
        tRelationInfo.vecItem.push_back(
                (T_RelationInfo::T_RelationItemInfo){
                item[i][KEY_OPENID].asString(),
                item[i].get(KEY_NICKNAME, "").asString(),
                item[i].get(KEY_GENDER, "").asString(),
                item[i].get(KEY_FIGURE_URL, "").asString()});
    }

    return E_PY_SUC;
}

int CPengyou::GetMultiInfo(T_MultiInfoInfo & tMultiInfoInfo,
                              const string & openid, const string & openkey,
                              const string & fopenids)
{
    int ret;
    if (openid.empty() || openkey.empty() || fopenids.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }
    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_GET_MULTI_INFO);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    // Build http query string
    buildHttpQuery(strQuery, openid, openkey);
    strQuery.append("&fopenids=");
    strQuery.append(fopenids);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret >= API_RETURE_ERROR_CODE_BASE)
    {
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }

    /* else */
    const Json::Value item = value[KEY_ITEMS];
    for (unsigned int i=0; i<item.size(); ++i)
    {
        tMultiInfoInfo.vecItem.push_back(
                (T_MultiInfoInfo::FriendItemInfo){
                item[i][KEY_OPENID].asString(),
                item[i][KEY_NICKNAME].asString(),
                item[i][KEY_GENDER].asString(),
                item[i][KEY_FIGURE_URL].asString(),
                item[i][KEY_ISVIP].asBool(),
                item[i].get(KEY_ISYEARVIP, false).asBool(),
                item[i].get(KEY_VIP_LEVEL, 0).asInt()});
    }

    return E_PY_SUC;
}

int CPengyou::IsSetup(T_AppSetupStatus & tAppSetupStat,
                     const string & openid, const string & openkey)
{
    int ret;
    if (openid.empty() || openkey.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }
    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_CHECK_APP_SETUP_STAT);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret)
    {
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }
    else
    {
        tAppSetupStat.nSetupStat = value[KEY_SETUP_STAT].asInt();
    }

    return E_PY_SUC;
}

int CPengyou::IsVip(T_VipStatInfo & tVipStat,
                   const string & openid, const string & openkey)
{
    int ret;
    if (openid.empty() || openkey.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }

    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_SHOW_VIP_STAT);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret)
    {
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }
    else
    {
        tVipStat.bIsVip = value[KEY_ISVIP].asBool();
    }

    return E_PY_SUC;
}

int CPengyou::GetFriendEmotion(T_EmotionInfo & tEmotionInfo,
                              const string & openid, const string & openkey,
                              const string & fopenids)
{
    int ret;
    if (openid.empty() || openkey.empty() || fopenids.empty())
    {
        setErrorMsg(E_PY_PARAM_INVALID);
        return -E_PY_PARAM_INVALID;
    }
    string strApiResponse = "";
    string strUrl = "";
    string strQuery = "";

    /** 根据API名字获得其空间或校友的url */
    ret = getApiUrl(strUrl, APP_GET_FRIEND_EMOTION);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    buildHttpQuery(strQuery, openid, openkey);
    strQuery.append("&fopenids=");
    strQuery.append(fopenids);

    /** 对API发起http请求 */
    ret = request(strApiResponse, strUrl, strQuery);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /** JSON串解析 */
    Json::Value value;
    ret = jsonDecode(value, strApiResponse);
    if (ret != E_PY_SUC)
    {
        return ret;
    }

    /**
     * 获取API的返回码，如果正常或部分正常则保存解析后的有效数据，否则
     * 保存API返回的错误消息
     */
    ret = value[KEY_RET_CODE].asInt();
    if (ret >= API_RETURE_ERROR_CODE_BASE)
    {
        setErrorMsg(value[KEY_ERR_MSG].asString());
        return -E_PY_API_RESPONSE_ERR;
    }

    /* else */
    const Json::Value item = value[KEY_ITEMS];
    for (unsigned int i=0; i<item.size(); ++i)
    {
        tEmotionInfo.vecItem.push_back(
                (T_EmotionInfo::EmotionItemInfo){
                item[i][KEY_CONTENT].asString(),
                item[i][KEY_OPENID].asString()});
    }

    return E_PY_SUC;
}

