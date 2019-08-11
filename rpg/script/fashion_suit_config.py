#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut

def parse_fashion_suit():
	fd = io.open("./src/t_fashion_suit.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["fashion_suits"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["count"] = int(i[4])
		item["id"] = int(i[5])
		item["fashionType"] = int(i[6])
		item["needFashion"] = []
		arr = i[2].split(r'#')
		for j in arr:
			item["needFashion"].append(int(j))

		dict["fashion_suits"].append(item)

	fd.close()
	with io.open("./tar/t_fashion_suit.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_fashion_suit()