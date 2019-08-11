#!/usr/bin/python
# -*- coding: UTF-8 -*-
import xlrd
import json
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_drop():
    workbook = xlrd.open_workbook(r'src/t_item_gift.xlsx')
    sheet = workbook.sheet_by_name(r't_item_gift')
    drops = {}
    drops['gifts'] = list()
    for i in range(sheet.nrows):
        if i == 0 or i == 1 or i == 2:
            continue
        item = {}
        item['id'] = int(sheet.cell_value(i, 1))
        item['subtype'] = int(sheet.cell_value(i, 5))
        item['reward'] = _parse_reward(sheet.cell_value(i, 29))
        item['extend'] = _parse_reward(sheet.cell_value(i, 30))
        drops['gifts'].append(item)

    fd = open('tar/gifts.json', 'w')
    json.dump(drops, fd, ensure_ascii=False, indent=2)
    fd.close()

if __name__ == "__main__":
    parse_drop()
