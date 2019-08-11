#!/usr/bin/python
# -*- coding: UTF-8 -*-
import xlrd
import json
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_island():
	workbook = xlrd.open_workbook(r'src/t_partner_island.xlsx')
	sheet = workbook.sheet_by_name(r't_partner_island')
	out = {}
	out["partner_islands"] = []
	for i in range(sheet.nrows):
		if i == 0 or i==1:
			continue
		item = {}
		item['layer'] = int(sheet.cell_value(i, 0))
		item['reward'] = _parse_reward(sheet.cell_value(i, 1))
		item['type'] = int(sheet.cell_value(i, 2))
		if(item['type'] ==1 and str(sheet.cell_value(i, 3))):
			item['exReward'] =  _parse_reward(sheet.cell_value(i, 3))
		else:
			item['exReward']=[]

		out["partner_islands"].append(item)
	fd = open("tar/partnerIsland.json", "w")
	json.dump(out, fd, ensure_ascii=False, indent=2)
	fd.close()
	




if __name__ == "__main__":
    parse_island()

