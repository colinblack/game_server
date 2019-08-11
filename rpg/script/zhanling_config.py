#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import io
from lib.common import _parse_attribut, _parse_reward


def _parse_equip(v):
    arr = v.split(r'&')
    obj = list()
    for i in arr:
        arr1 = i.split(r'#')
        if len(arr1) == 2:
            item = {}
            item[r'pos'] = int(arr1[0])
            item[r'id'] = int(arr1[1])
        obj.append(item)
    return obj

def parse_skill_mode(v):
    arr = v.split(r'#')
    obj = list()
    for i in arr:  
        if len(i) > 0:
            obj.append(int(i))
    return obj

def parse_zhanling():
    fd = io.open("./src/t_zhanling.json", "r", encoding="utf-8")
    data = json.load(fd)
    zhanlings = {}
    zhanlings["bases"] = []
    for i in data:
        item = {}
        item['level'] = i[0]
        item['equips'] = _parse_equip(i[1])
        item['skill_mode'] = parse_skill_mode(i[2])    
        item['model'] = int(i[3])
        item['speed'] = int(i[5])
        item['skill'] = int(i[6])
        item['attr'] = _parse_attribut(i[7])
        zhanlings['bases'].append(item)
    fd.close()
    fd = open('tar/zhanling.json', 'w')
    json.dump(zhanlings, fd, ensure_ascii=False, indent=2)


if __name__ == "__main__":
    parse_zhanling()