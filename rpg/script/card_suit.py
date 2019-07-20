#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_card_suit.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["suits"] = []
	for i in data:
		item = {}
		str_tmp = str(i[0])
		list_tmp = str_tmp.split('&')
		item["include"] = []
		for s in list_tmp:
			item["include"].append(int(s))
		item["id"] = int(i[2])
		dict["suits"].append(item)
	fd.close()
	with io.open("./tar/card_suit.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()