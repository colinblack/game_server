#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward

def parse_title():
	fd = io.open("./src/t_title.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["title"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["limitTime"] = int(i[4])
		item["id"] = int(i[7])
		item["name"] = i[8]
		item["itemId"] = int(i[12])
		dict["title"].append(item)
	fd.close()
	with io.open("./tar/t_title.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_title()