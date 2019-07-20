#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_times
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_activity():
    fd = open('src/t_daily.json', 'r')
    data = json.load(fd)
    DaliyAct = {}
    DaliyAct['daliy_act'] = list()
    for i in data:
        item = {}
        item['activity'] = i[1]
        item['copyCfg'] = i[3]
        item['count'] = i[4]
        item['type'] = i[8]
        item['actId'] = i[13]
        item['copyId'] = i[21]
        item['limits'] = _parse_times(i[15])
        DaliyAct['daliy_act'].append(item)
        fd.close()
    fd = open('tar/daily_act.json', 'w')
    json.dump(DaliyAct, fd, ensure_ascii=False, indent=2)
    fd.close()

def parse_active():
    fd = open('src/t_daily_activity.json', 'r')
    data = json.load(fd)
    actives = {}
    actives['active'] = list()
    for i in data:
        item = {}
        item['limit'] = i[0]
        item['type'] = i[1]
        item['reward'] = _parse_reward(i[5])
        actives['active'].append(item)
        fd.close()
    fd = open('tar/active.json', 'w')
    json.dump(actives, fd, ensure_ascii=False, indent=2)
    fd.close()

if __name__ == "__main__":
    parse_activity()
    parse_active()