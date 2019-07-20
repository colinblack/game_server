#!/usr/bin/python
# -*- coding: UTF-8 -*-
import xlrd
import json
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_plan():
	workbook = xlrd.open_workbook(r'src/t_monster_plan.xlsx')
	sheet = workbook.sheet_by_name(r't_monster_plan')
	out = {}
	out["plans"] = []
	for i in range(sheet.nrows):
		if i == 0 or i==1:
			continue
		item = {}
		item['id'] = int(sheet.cell_value(i, 6))
		item['mapid'] = int(sheet.cell_value(i, 0))
		item['boss'] = int(sheet.cell_value(i, 2))
		item['plan'] = int(sheet.cell_value(i, 1))
		item['pos']=[]
		str_tmp= str(sheet.cell_value(i, 4)).split('&')
		if(len(str_tmp)>=1):
			for tmp_i in str_tmp:
				ss ={}
				tmp_ii = tmp_i.split('#')
				if(len(tmp_ii)>=2):
					ss['x']= int(tmp_ii[0])
					ss['y']= int(tmp_ii[1])
					item['pos'].append(ss)
		out["plans"].append(item)
	fd = open("tar/monster_plans.json", "w")
	json.dump(out, fd, ensure_ascii=False, indent=2)
	fd.close()
	


def parse_monster():
    fd = open("src/t_monster.json", "r")
    data = json.load(fd)
    out = {}
    out["monsters"] = list()
    for i in data:
        item = {}
        item["id"] = i[24]
        item["level"] = i[25]
        item["hpPercent"] = i[28]
        item["hp"] = i[29]
        item["attack"] = i[1]
        item["speed"] = i[31]
        item["reward"] = _parse_reward(i[34])
        item["exp"] = i[16]
        item["skill"] = i[33]
        item["skill2"] = i[37]
        item["width"] = i[5]
        item["defence"] = i[11]
        item["wuxing"] = i[40]
        item["alive"] = i[0]
        item["fixDmgDec"] = i[20]
        item["dmgDec"] = i[14]
        item["critBreakRate"] = i[10]
        item["critBreak"] = i[9]
        out["monsters"].append(item)
    fd.close()
    fd = open("tar/monsters.json", "w")
    json.dump(out, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_plan()
    #parse_monster()
