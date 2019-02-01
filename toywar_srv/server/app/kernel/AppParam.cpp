/*
 * AppParam.cpp
 *
 *  Created on: 2011-7-12
 *      Author: dada
 */

#include "AppParam.h"

const Json::Value &App::GetParams()
{
	static bool s_bInit = false;
	static Json::Value params;
	if(!s_bInit)
	{
		string path;
		if(!Config::GetValue(path, CONFIG_APP_PARAMS))
		{
			fatal_log("[get config fail][config_name=%s]", CONFIG_APP_PARAMS);
		}
		else
		{
			string sParams;
			int ret = File::Read(path, sParams);
			if(ret != 0)
			{
				fatal_log("[app params read fail][ret=%d,path=%s]", ret, path.c_str());
			}
			else
			{
				if(!Json::Reader().parse(sParams, params))
				{
					fatal_log("[app params parse fail][ret=%d,path=%s]", ret, path.c_str());
				}
			}
		}
	}
	return params;
}
