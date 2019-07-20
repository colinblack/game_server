#!/usr/bin/python
# -*- coding: UTF-8 -*-
import json


class Attr(list):
    def __init__(self, v):
        list.__init__(self)
        arr = list()
        if type(v) == list:
            arr = v
        elif type(v) == str:
            arr = json.loads(v)
        for i in arr:
            if type(i) != list:
                continue
            item = {}
            item['group'] = int(i[0])
            item['type'] = int(i[1])
            item['num'] = int(i[2])
            self.append(item)
