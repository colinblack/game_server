#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_attribut, _parse_reward
import sys 
reload(sys)
sys.setdefaultencoding('utf8')

def parse_star_rate(v):
    arr = v.split(r'&')
    rate = list()
    for i in arr:
        r = i.split(r'#')
        if len(r) == 2:
            item = {}
            item['star'] = int(r[0])
            item['rate'] = int(r[1])
            rate.append(item)
    return rate

def parse_equip():
    fd = open('src/t_item_equip.json', 'r')
    data = json.load(fd)
    equips = {}
    equips['equips'] = list()
    for i in data:
        item = {}
        item['id'] = i[1]
        item['part'] = i[5]
        item['career'] = i[13]
        item['active_min'] = i[14]
        item['smeltAward'] = _parse_reward(i[31])
        item['attr'] = _parse_attribut(i[19])
        item['starRate'] = parse_star_rate(i[20])
        item['sub'] = i[30]
        item['color'] = i[6]
        item['changeLevel'] = i[17]
        arr = i[27].split(r'#')
        if len(arr) == 2:
            sundry = {}
            sundry['id'] = int(arr[0])
            sundry['num'] = int(arr[1])
            item['sundry'] = sundry
        item['type'] = i[4]
        equips['equips'].append(item)
        #if i[30] != 10001 and i[30] > 6:
        #    print(i[1])
        #    return True
    fd.close()
    fd = open('tar/equips.json', 'w')
    json.dump(equips, fd, ensure_ascii=False, indent=2)


def parse_equip_attr():
    fd = open('src/t_equip_attr.json', 'r')
    data = json.load(fd)
    equips = {}
    equips['attrs'] = list()
    for i in data:
        item = {}
        item['id'] = i[6]
        item['star'] = i[5]
        item['rate'] = i[4]
        if i[3] == 1:
            item['best'] = True
        else:
            item['best'] = False
        item['group'] = i[2]
        item['attr'] = _parse_attribut(i[0])
        equips['attrs'].append(item)
    fd.close()
    fd = open('tar/equip_attrs.json', 'w')
    json.dump(equips, fd, ensure_ascii=False, indent=2)


def parse_gift():
    fd = open('src/t_item_gift.json', 'r')
    data = json.load(fd)
    equips = {}
    equips['gifts'] = list()
    for i in data:
        item = {}
        item['id'] = i[1]
        item['subtype'] = i[5]
        item['reward'] = _parse_reward(i[29])
        item['extend'] = _parse_reward(i[30])
        equips['gifts'].append(item)
    fd.close()
    fd = open('tar/gifts.json', 'w')
    json.dump(equips, fd, ensure_ascii=False, indent=2)


def parse_item():
    fd = open('src/preloadData.json', 'r')
    data = json.load(fd)
    items = {}
    items['items'] = list()
    for i in data['t_item']:
		item = {}
		item['id'] = i[1]
		item['type'] = int(i[3])
		item['itemType'] = i[4]
		item['subType'] = i[5]
		item['color'] = i[6]
		item['level']=i[7]
		item['data']=i[14]
		item['attr'] = _parse_attribut(i[19])
		item['smeltAward'] = _parse_reward(i[31])
		items['items'].append(item)
    fd.close()
    fd = open('tar/items.json', 'w')
    json.dump(items, fd, ensure_ascii=False, indent=2)


def parse_shenqi():
    fd = open('src/preloadData.json', 'r')
    data = json.load(fd)
    items = {}
    items['shenqis'] = list()
    for i in data['t_shenqi_piece']:
        item = {}
        item['item'] = i[0]
        item['id'] = i[1]
        items['shenqis'].append(item)
    fd.close()
    fd = open('tar/shenqis.json', 'w')
    json.dump(items, fd, ensure_ascii=False, indent=2)


def parse_equip_strengthen():
    fd = open('src/t_equip_strengthen.json', 'r')
    data = json.load(fd)
    items = {}
    items['strengthens'] = list()
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[0])
        item['type'] = i[1]
        item['cost'] = _parse_reward(i[2])
        item['id'] = i[3]
        items['strengthens'].append(item)
    fd.close()
    fd = open('tar/equip_strengthens.json', 'w')
    json.dump(items, fd, ensure_ascii=False, indent=2)


def parse_equip_purify():
    fd = open('src/t_equip_purify.json', 'r')
    data = json.load(fd)
    items = {}
    items['purifys'] = list()
    for i in data:
        item = {}
        item['attr'] = _parse_attribut(i[1])
        item['level'] = i[5]
        item['useProps'] = _parse_reward(i[4])
        items['purifys'].append(item)
    fd.close()
    fd = open('tar/t_equip_purify.json', 'w')
    json.dump(items, fd, ensure_ascii=False, indent=2)
    
if __name__ == "__main__":
    parse_equip()
    # parse_item()
    #parse_gift()
    # parse_shenqi()
    # parse_equip_attr()
    # parse_equip_strengthen()
    #parse_equip_purify()
