#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_card_attr.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["cards"] = []
	for i in data:
		item = {}
		item["attr"] = _parse_attribut(i[0])
		item["id"] = i[2]
		item["exAttr"] = _parse_attribut(i[6])
		item["skill"] = int(i[9])
		dict["cards"].append(item)
	fd.close()
	with io.open("./tar/card_attr.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()