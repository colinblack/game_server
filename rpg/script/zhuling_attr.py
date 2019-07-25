#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_reward, _parse_attribut


def parse_zhuling():
    fd = io.open("./src/t_zhuling_attr.json", "r", encoding="utf-8")
    data = json.load(fd)
    dict = {}
    dict["zhuLings"] = []
    for i in data:
        item = {}
        item['type'] = i[0]
        item['rate'] = i[1]
        item['consum'] = i[2]
        item['level'] = i[3]
        item['id'] = i[4]
        dict["zhuLings"].append(item)
    fd.close()
    with io.open("./tar/zhuling_attr.json",'w',encoding="utf-8") as outfile:
        outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))



def parse_spet():
    fd = io.open("./src/t_zhuling_spet.json", "r", encoding="utf-8")
    data = json.load(fd)
    dict = {}
    dict["spets"] = []
    for i in data:
        item = {}
        item['type'] = i[0]
        item['attr'] = _parse_attribut(i[1])
        item['rate'] = i[2]
        item['limit'] = i[3]
        item['id'] = i[4]
        item['equip_type'] = i[5]
        dict["spets"].append(item)
    fd.close()
    with io.open("./tar/zhuling_spet.json",'w',encoding="utf-8") as outfile:
        outfile.write(unicode(json.dumps(dict, ensure_ascii=False)))


if __name__ == "__main__":
    parse_zhuling()
    parse_spet()