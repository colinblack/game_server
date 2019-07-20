#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_magic_tower.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["magic_towers"] = []
	for i in data:
		item = {}
		item["id"] = int(i[0])
		item["dailyReward"] = int(i[1])
		item["reward"] = _parse_reward((i[2]))
		dict["magic_towers"].append(item)
	fd.close()
	with io.open("./tar/magic_towers.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()