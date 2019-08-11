#!/usr/bin/python
# -*- coding: UTF-8 -*-
import xlrd
import json
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_drop():
    workbook = xlrd.open_workbook(r'src/t_drop.xlsx')
    sheet = workbook.sheet_by_name(r'Drop')
    drops = {}
    drops['drops'] = list()
    for i in range(sheet.nrows):
		try:
			if i == 0 or i == 1 or i == 2 or i == 3:
				continue
			item = {}
			item['id'] = int(sheet.cell_value(i, 0))
			item['randomCount'] = int(sheet.cell_value(i, 2))
			item['fixedReward'] = _parse_reward(sheet.cell_value(i, 4))
			item['randomReward'] = _parse_reward(sheet.cell_value(i, 5))
			if(str(sheet.cell_value(i, 6))!=""):
			
				item['ownRewardCount'] = int(sheet.cell_value(i, 6))
				item['ownReward'] = _parse_reward(sheet.cell_value(i, 7))
			if(str(sheet.cell_value(i, 8))!=""):
				item['killRewardCount'] = int(sheet.cell_value(i, 8))
				item['killReward'] = _parse_reward(sheet.cell_value(i, 9))
		except:
			print (i)
		drops['drops'].append(item)
    fd = open('tar/drops.json', 'w')
    json.dump(drops, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_drop()
