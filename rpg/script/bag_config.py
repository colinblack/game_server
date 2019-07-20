#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_grid():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    grids = {}
    grids["grids"] = list()
    for i in data['t_bag_grid']:
        item = {}
        item["type"] = i[0]
        item["num"] = i[1]
        item["cost"] = i[2]
        grids["grids"].append(item)
    fd.close()
    fd = open("tar/bag_grid.json", "w")
    json.dump(grids, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_grid()
