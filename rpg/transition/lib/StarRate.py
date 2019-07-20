#!/usr/bin/python
# -*- coding: UTF-8 -*-


class StarRate(list):
    def __init__(self, v):
        arr = v.split(r'&')
        for i in arr:
            r = i.split(r'#')
            if len(r) == 2:
                item = {}
                item['star'] = int(r[0])
                item['rate'] = int(r[1])
                self.append(item)
