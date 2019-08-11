#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io

def parse_equip_slot():
	fd = io.open("./src/t_equip_slot.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["equipSlots"] = []
	for i in data:
		item = {} 
		item["type"] = int(i[1])
		item["slot"] = int(i[3])
	
		item["gemType"] = int(i[2])
		item["needVipLv"] = int(i[4])
		item["needReincarnationLv"] = int(i[0])
		
		dict["equipSlots"].append(item)
	fd.close()
	with io.open("./tar/t_equip_slot.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
# career

if __name__ == "__main__":
    parse_equip_slot()