#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_copy.json", "r", encoding="utf-8")
	fd2 = io.open("./src/t_copy_ex.json", "r", encoding="utf-8")
	data = json.load(fd)
	data2 = json.load(fd2)
	dict = {}
	dict["copys"] = []
	for i in data:
		item = {}
		item["daily"] = int(i[1])
		item["reincarnLevel"] = int(i[2])
		item["copyId"] = int(i[3])
		
		
		for tmp in data2['t_copy_ex']:
			if(tmp['copy_id']==item["copyId"]):
				item['preapareTime'] = tmp['prepare_time']
				item['duringTime'] = tmp['during_time']
				break
		
		
		item["firstReward"] = _parse_reward((i[4]))
		item["costId"] = int(i[6])
		item["costNum"] = int(i[7])
		item["time"] = int(i[10])
		#
		item["num"] = int(i[13])
		item["type"] = int(i[26])
		item["mapId"] = int(i[15])
		item["needLevel"] = int(i[20])
		item["quickDay"] = int(i[22])
		if(str(i[25]).isdigit()):
			item["reward"]=[]
			reward_tmp={}
			reward_tmp.setdefault('item',int(i[25]))
			reward_tmp.setdefault('num',1)
			item["reward"].append(reward_tmp)
		else:
			item["reward"] = _parse_reward((i[25]))
		dict["copys"].append(item)
	fd.close()
	with io.open("./tar/copy.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()