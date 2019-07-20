#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_ring.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["ring"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["level"] = int(i[1])
		item["exp"] = int(i[4])
		dict["ring"].append(item)
	fd.close()
	with io.open("./tar/t_ring.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()