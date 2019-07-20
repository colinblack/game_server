#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def parse_grid():
	fd = io.open("./src/t_magic.json", "r", encoding="utf-8")
	data = json.load(fd)
	dict = {}
	dict["magics"] = []
	for i in data:
		item = {}
		item["id"] = int(i[11])
		if(item["id"]<=100004):
			continue
		item["attr"] = _parse_attribut(i[2])
		item["attrType"] = int(i[1])
		item["color"] = int(i[5])
		item["exp"] = int(i[6])
		item["level"] = int(i[7])
		item["lock"] = int(i[8])
		item["smelt"] = int(i[9])
		item["type"] = int(i[10])
		item["attrCal"]=[]
		item["expCal"]=[]
		item["smeltCal"]=[]
		
		arr = i[0].split(r'&')
		for j in arr:
			sss = j.split(r'$')
			j = sss[0]
			tmp = j.split(r'#')
			for w in tmp:
				if(len(tmp)>1):
					tmp=map(int,tmp)
			item["attrCal"].append(tmp[-1])
		item["attrCal"].insert(2,10000)
		arr = i[3].split(r'&')
		for j in arr:
			tmp = j.split(r'#')
			if(len(tmp)>1):
				tmp=map(int,tmp)
			item["expCal"].append(tmp[-1])
		item["expCal"].insert(2,10000)
			
		arr = i[4].split(r'&')
		for j in arr:
			tmp = j.split(r'#')
			if(len(tmp)>1):
				tmp=map(int,tmp)
				a1 =tmp[1]
				a2 =tmp[2]/10000
				a3 =tmp[3]
				value = int(a2*(int(i[9])-a3)+a1)
				item["smeltCal"].append(value)
		item["smeltCal"].insert(2,int(i[9]))
				
		dict["magics"].append(item)
	fd.close()
	with io.open("./tar/t_magic.json",'w',encoding="utf-8") as outfile:
		outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))
	


if __name__ == "__main__":
    parse_grid()