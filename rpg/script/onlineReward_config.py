#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import  _parse_reward

def parse_online_reward():
	fd = io.open("./src/t_online_reward.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["onlineRewards"] = []
	for i in data:
		item = {}
		item["id"] = int(i[1])
		item["reward"] = _parse_reward(i[4])
		item["onlineTime"] = int(i[6])
		item["registeredDay"] = int(i[0].split(r'#')[1])
		
		dict["onlineRewards"].append(item)
	fd.close()
	with io.open("./tar/t_online_reward.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_online_reward()