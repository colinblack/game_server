#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward, _parse_skills


def parse_grid():
    fd = io.open("./src/t_suit_collect.json", "r", encoding="utf-8")
    data = json.load(fd)
    dict = {}
    dict["suits"] = []
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[0])
        item['level'] = i[1]
        item['color'] = i[2]
        item['id'] = i[4]
        item['skills'] = _parse_skills(i[7])
        item['star'] = i[8]
        item['mode'] = i[6]
        dict["suits"].append(item)
    fd.close()
    with io.open("./tar/role_suit.json",'w',encoding="utf-8") as outfile:
        outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_grid()