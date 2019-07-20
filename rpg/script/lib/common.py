#!/usr/bin/python
# -*- coding: UTF-8 -*-


def _parse_reward(v):
    arr = v.split(r'&')
    obj = list()
    for i in arr:
        arr1 = i.split(r'#')
        if len(arr1) < 2:
            continue
        item = {}
        item[r'item'] = int(arr1[0])
        item[r'num'] = int(arr1[1])
        if len(arr1) > 2:
            item[r'rate'] = int(arr1[2])
        obj.append(item)
    return obj

def _parse_skills(v):
    arr1 = v.split(r'#')
    obj = list()
    for i in arr1:
        item = {}
        item[r'item'] = int(i[0])
        obj.append(item)
    return obj

def _parse_attribut(v):
    attr = list()
    if type(v) != list:
        return attr
    for i in v:
        if type(i) != list:
            continue
        item = {}
        item['group'] = int(i[0])
        item['type'] = int(i[1])
        item['num'] = int(i[2])
        attr.append(item)
    return attr

def _parse_times(v):
    data = v.split(r'&')
    obj = list()
    for j in data:
        times = j.split(r'#')
        item = {}
        if len(times) == 1:
            part1 = times[0].split(':')
            if len(part1) != 2:
                continue
            item['startTs'] =  int(part1[0]) * 3600 + int(part1[1]) * 60
            item['endTs'] = 3600 * 24
        elif len(times) == 2:
            part1 = times[0].split(':')
            part2 = times[1].split(':')
            if len(part1) != 2 | len(part2) != 2:
                continue
            item['startTs'] = int(part1[0]) * 3600 + int(part1[1]) * 60
            item['endTs'] =  int(part2[0]) * 3600 + int(part2[1]) * 60
        obj.append(item)
    return obj
