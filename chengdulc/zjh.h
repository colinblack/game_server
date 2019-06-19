#ifndef _LANDLORD_H_
#define _LANDLORD_H_

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

#include "redis_client.h"
class Game;

class ZJH
{
public:
	std::string         conf_file;
	int                 is_daemonize;
	Json::Value         conf;
	Game                *game;
	struct ev_loop      *loop;
	RedisClient     	*zjh_rc;
};

#endif    /* _LANDLORD_H_ */
