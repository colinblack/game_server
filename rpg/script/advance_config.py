#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_attribut
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
        advance['advances'].append(item)
        fd.close()
    fd = open('tar/advances.json', 'w')
    json.dump(advance, fd, ensure_ascii=False, indent=2)
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
    parse_advance()
    parse_dan()
