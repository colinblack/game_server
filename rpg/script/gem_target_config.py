#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut

def parse_gem_target():
	fd = io.open("./src/t_gem_target.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["gem_targets"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["gemLV"] =  int(i[2])
		item["count"] = int(i[3])
		item["gemType"] = int(i[4])
		item["id"] = int(i[5])

		dict["gem_targets"].append(item)

	fd.close()
	with io.open("./tar/t_gem_target.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_gem_target()