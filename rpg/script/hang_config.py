#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_plan():
    fd = open("src/t_hang_plan.json", "r")
    data = json.load(fd)
    plans = {}
    plans["plans"] = list()
    for i in data:
        item = {}
        item["boss"] = i[2]
        item["id"] = i[3]
        item["mapid"] = i[4]
        item["plan"] = i[5]
        item["point"] = i[9]
        plans["plans"].append(item)
    fd.close()
    fd = open("tar/hang_plans.json", "w")
    json.dump(plans, fd, ensure_ascii=False, indent=2)
    fd.close()


def parse_hang():
    fd = open("src/t_hang.json", "r")
    data = json.load(fd)
    hangs = {}
    hangs["hangs"] = list()
    for i in data:
        item = {}
        item["coin"] = i[0]
        item["exp"] = i[1]
        item["id"] = i[2]
        item["mapid"] = i[3]
        item["plan"] = i[4]
        item["power"] = i[5]
        hangs["hangs"].append(item)
    fd.close()
    fd = open("tar/hangs.json", "w")
    json.dump(hangs, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_plan()
    parse_hang()
