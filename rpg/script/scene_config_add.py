#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/scenes.json", "r", encoding="utf-8")
	fd2 = io.open("./src/t_map_ex.json", "r", encoding="utf-8")
	data = json.load(fd)
	data2 = json.load(fd2)
	dict = {}
	dict["copys"] = []
	for i in data['scenes']:
		for tmp in data2['t_map_ex']:
			if(i['mapId']==tmp["map_id"]):
				i['addEnterPoint_x']= tmp['x']
				i['addEnterPoint_y']= tmp['y']
				break
		
	fd.close()
	with io.open("./tar/scenes.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(data, ensure_ascii=False)))



if __name__ == "__main__":
    parse_grid()