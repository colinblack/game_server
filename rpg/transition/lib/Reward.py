#!/usr/bin/python
# -*- coding: UTF-8 -*-


class Reward(list):
    def __init__(self, v):
        list.__init__(self)
        arr = v.split(r'&')
        for i in arr:
            arr1 = i.split(r'#')
            if len(arr1) < 2:
                continue
            item = {}
            item[r'item'] = int(arr1[0])
            item[r'num'] = int(arr1[1])
            if len(arr1) > 2:
                item[r'rate'] = int(arr1[2])
            self.append(item)
