#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_attribut, _parse_skills_type
import sys
reload(sys)
sys.setdefaultencoding('utf8')

def parse_advance():
    fd = open('src/t_advance.json', 'r')
    data = json.load(fd)
    advance = {}
    advance['advances'] = list()
    for i in data:
        item = {}
        item['type'] = i[14]
        item['group'] = i[7]
        item['star'] = i[13]
        if len(i[3]) > 0:
            item['cost_item'] = int(i[3].split(r'&')[0])
        else:
            item['cost_item'] = 0
        item['cost_num'] = i[4]
        if len(i[1]) > 0:
            item['bless'] = int(i[1])
        else:
            item['bless'] = 0
        item['max_bless'] = i[2]
        item['mode'] = i[8]
        item['attr'] = _parse_attribut(i[0])
        if len(i[12]) > 0:
            item['skill'] = _parse_skills_type(i[12])
        else:
            item['skill']=[]
        advance['advances'].append(item)
        fd.close()
    fd = open('tar/advances.json', 'w')
    json.dump(advance, fd, ensure_ascii=False, indent=2)
    fd.close()

def parse_advance_equip_strength():
    fd = open('src/t_advance_equip_strength.json', 'r')
    data = json.load(fd)
    advance_equip_strength = {}
    advance_equip_strength['strength'] = list()
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[0])
        item['consumId'] = i[1]
        item['consumCnt'] = i[2]
        item['level'] = i[3]
        item['part'] = i[4]
        item['type'] = i[5]
        advance_equip_strength['strength'].append(item)
        fd.close()
    fd = open('tar/advance_equip_strength.json', 'w')
    json.dump(advance_equip_strength, fd, ensure_ascii=False, indent=2)
    fd.close()

def parse_advance_awaken():
    fd = open('src/t_advance_awaken.json', 'r')
    data = json.load(fd)
    advance_awaken= {}
    advance_awaken['awaken'] = list()
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[0])
        arr = i[1].split(r'#')
        if len(arr) == 2:
            consume = {}
            consume['id'] = int(arr[0])
            consume['num'] = int(arr[1])
            item['consume'] = consume
       
        item['advance'] = i[2]
        item['star'] = i[3]
        item['type'] = i[4]
        advance_awaken['awaken'].append(item)
        fd.close()
    fd = open('tar/advance_awaken.json', 'w')
    json.dump(advance_awaken, fd, ensure_ascii=False, indent=2)
    fd.close()

def parse_advance_target():
    fd = open('src/t_advance_target.json', 'r')
    data = json.load(fd)
    advance_target= {}
    advance_target['target'] = list()
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[0])
        item['advance'] = i[1]
        item['type'] = i[2]
        advance_target['target'].append(item)
        fd.close()
    fd = open('tar/advance_target.json', 'w')
    json.dump(advance_target, fd, ensure_ascii=False, indent=2)
    fd.close()

def parse_dan():
    fd = open('src/t_advance_dan.json', 'r')
    data = json.load(fd)
    dans = {}
    dans['dans'] = list()
    for i in data:
        item = {}
        item['item'] = i[2]
        item['id'] = i[3]
        item['type'] = i[6]
        item['level'] = i[4]
        item['total'] = i[5]
        item['attr'] = _parse_attribut(i[1])
        dans['dans'].append(item)
    fd.close()
    fd = open('tar/advance_dans.json', 'w')
    json.dump(dans, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    #parse_advance()
    #parse_dan()
    #parse_advance_equip_strength()
    #parse_advance_awaken()
    parse_advance_target()