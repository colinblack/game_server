#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_boss.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["boss"] = []
	for i in data:
		item = {}
		item["bossid"] = int(i[0])
		item["reincarnLevel"] = int(i[1])
		item["bossType"] = int(i[2])
		item["reward"] = _parse_reward((i[3]))
		
		dict["boss"].append(item)
		
	fd.close()
	with io.open("./tar/boss.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()