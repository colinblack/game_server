#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut

def parse_fashion():
	fd = io.open("./src/t_fashion.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["fashions"] = []
	for i in data:
		item = {}
		item["id"] = int(i[7])
		item["attr"] = _parse_attribut(i[1])
		item["itemId"] = int(i[3])
		item["itemCount"] = int(i[4])
		item["limitTime"] = int(i[5])
		item["level"] = int(i[8])
		item["modelID"] = int(i[9])
		item["skillID"] = int(i[12])
		item["skillAndLevel"] = []

		arr = i[0].split(r'&')
		obj = list()
		for j in arr:
			tmparr = j.split(r'#')
			if(len(tmparr) < 2):
				continue
			
			item1 = {}
			item1[r'level'] = int(tmparr[1])
			item1[r'SkillId'] = int(tmparr[0])
			obj.append(item1)
		item["skillAndLevel"] = obj
		dict["fashions"].append(item)

	fd.close()
	with io.open("./tar/t_fashion.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_fashion()