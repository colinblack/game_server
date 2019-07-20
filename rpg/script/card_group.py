#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_card_group.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["groups"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["groupId"] = int(i[2])
		item["needNum"] = int(i[3])
		item["type"] = int(i[4])
		dict["groups"].append(item)
	fd.close()
	with io.open("./tar/card_group.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()