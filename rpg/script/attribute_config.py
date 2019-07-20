#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def parse_attr_def():
    fd = open('src/clientCfg.json', 'r')
    data = json.load(fd)
    attr_defs = {}
    attr_defs['attr_defs'] = list()
    for k in data['gameDefs']['AttributeName'].keys():
        node = data['gameDefs']['AttributeName'][k]
        for i in node:
            item = {}
            item['group'] = int(k)
            item['type'] = node[i]['attrType']
            if node[i]['isTenThousand'] == 1:
                item['percent'] = True
            else:
                item['percent'] = False
            attr_defs['attr_defs'].append(item)
        fd.close()
    fd = open('tar/attr_defs.json', 'w')
    json.dump(attr_defs, fd, ensure_ascii=False, indent=2)
    fd.close()


if __name__ == "__main__":
    parse_attr_def()
