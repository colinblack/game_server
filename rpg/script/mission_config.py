#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
from lib.common import _parse_reward
import sys
reload(sys)
sys.setdefaultencoding('utf8')

def parse_contition(arr):
	obj = {}
	for i in range(len(arr)):
		k = 'v{0}'.format(i)
		obj[k] = int(arr[i])
	return obj


def parse_mission():
    fd = open("src/t_mission.json", "r")
    data = json.load(fd)
    missions = {}
    missions["missions"] = list()
    types = {}
    for i in data:
        arr = i[3].split(r'&')
        # if i[19] != 1:
        #    continue
        item = {}
        item["exp"] = i[0]
        item["id"] = i[6]
        item["condition"] = list()
        item["reward"] = _parse_reward(i[15])
        for j in arr:
            cc = parse_contition(j.split(r'#'))
            tt = cc['v1']
            if tt not in types:
                types[tt] = {}
            types[tt][i[9]] = True
            item["condition"].append(cc)
        missions["missions"].append(item)
    fd.close()
    fd = open("tar/missions.json", "w")
    json.dump(missions, fd, ensure_ascii=False, indent=2)
    fd.close()
    # print(json.dumps(types, ensure_ascii=False))
    for k in types.keys():
        print(k)


if __name__ == "__main__":
    parse_mission()
