#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import xlwt
import sys
reload(sys)
sys.setdefaultencoding('utf8')

def parse_preload():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    for k in data:
        to_excel(data[k], k)
    fd.close()


def parse_item_equip():
    fd = open("src/t_item_equip.json", "r")
    data = json.load(fd)
    to_excel(data, r't_item_equip')
    fd.close()


def parse_item_gift():
    fd = open("src/t_item_gift.json", "r")
    data = json.load(fd)
    to_excel(data, r't_item_gift')
    fd.close()


def parse_equip_strengthen():
    fd = open("src/t_equip_strengthen.json", "r")
    data = json.load(fd)
    to_excel(data, r't_equip_strengthen')
    fd.close()


def to_excel(data, name):
    workbook = xlwt.Workbook(encoding="ascii")
    worksheet = workbook.add_sheet(name)
    h1 = 0
    h2 = 1
    col = 0
    if len(data) == 0:
        return False

    for k in data[0]:
        v = type(k)
        v1 = ""
        if v == int:
            v1 = "int"
        elif v == str:
            v1 = "str"

        worksheet.write(h1, col, label=col)
        worksheet.write(h2, col, label=v1)
        col += 1

    row = 2
    for k in data:
        col = 0
        for v in k:
            try:
                t = type(v)
                if t == int or t == str:
                    worksheet.write(row, col, label=v)
                else:
                    worksheet.write(row, col, label=str(v))
                col += 1
            except Exception as e:
                print(name, row, col, e)
                return False
        row += 1
    workbook.save("xls/{0}.xls".format(name))
    return True


if __name__ == "__main__":
    # parse_preload()
    # parse_item_equip()
    # parse_item_gift()
    parse_equip_strengthen()
