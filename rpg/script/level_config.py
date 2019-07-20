#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_level():
    fd = open("src/preloadData.json", "r")
    data = json.load(fd)
    levels = {}
    levels["levels"] = list()
    for i in data["t_level"]:
		item = {}
		item["id"] = i[0]
		item["reincarnExp"] = i[1]
		item["exp"] = i[2]
		levels["levels"].append(item)
    fd.close()
    fd = open("tar/levels.json", "w")
    json.dump(levels, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_level()
