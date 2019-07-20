#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import re
import sys
reload(sys)
sys.setdefaultencoding('utf8')


if __name__ == "__main__":
    fd = open("src/clientCfg.json", "r")
    data = json.load(fd)
    scene = {}
    scene["scenes"] = list()
    for k in data.keys():
        ret = re.findall(r'(\d+)_scene', k)
        if len(ret) == 0:
            continue
        data[k]["id"] = int(ret[0])
        scene["scenes"].append(data[k])
    fd.close()

    fd = open("tar/scenes.json", "w")
    json.dump(scene, fd, ensure_ascii=False, indent=2)
    fd.close()
